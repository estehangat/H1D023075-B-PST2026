# Jawaban Pertanyaan 5.6.4 - Komunikasi Task RTOS

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Kedua task berjalan secara concurrent menggunakan scheduler FreeRTOS. Karena Arduino Uno hanya memiliki satu prosesor, task sebenarnya berjalan bergantian tetapi dengan pergantian yang sangat cepat sehingga terlihat berjalan bersamaan.

Task pertama (`read_data`) bertugas mengirim data ke queue, sedangkan task kedua (`display`) bertugas membaca data dari queue dan menampilkannya pada Serial Monitor.

Scheduler mengatur kapan task dijalankan berdasarkan status task dan delay yang diberikan.

---

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!

Program memiliki kemungkinan race condition yang sangat kecil karena komunikasi antar task menggunakan queue.

Queue pada FreeRTOS dirancang untuk mengatur akses data antar task secara aman sehingga:
- hanya satu task yang mengakses data tertentu pada satu waktu
- data dikirim dan diterima secara terstruktur
- konflik akses data dapat dihindari

Jika komunikasi dilakukan menggunakan variabel global tanpa queue atau semaphore, maka race condition lebih mudah terjadi.

---

## 3. Modifikasi program menggunakan sensor DHT sesungguhnya

### Program

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

struct readings {
  float temp;
  float hum;
};

QueueHandle_t my_queue;

void setup() {

  Serial.begin(9600);

  dht.begin();

  my_queue = xQueueCreate(5, sizeof(struct readings));

  xTaskCreate(read_data, "read", 128, NULL, 1, NULL);
  xTaskCreate(display, "display", 128, NULL, 1, NULL);
}

void loop() {
}

void read_data(void *pvParameters) {

  struct readings x;

  while(1) {

    x.temp = dht.readTemperature();
    x.hum = dht.readHumidity();

    xQueueSend(my_queue, &x, portMAX_DELAY);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void display(void *pvParameters) {

  struct readings x;

  while(1) {

    if(xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS) {

      Serial.print("Temperature: ");
      Serial.println(x.temp);

      Serial.print("Humidity: ");
      Serial.println(x.hum);
    }
  }
}
```

### Penjelasan Program

- Library `DHT.h` digunakan untuk membaca sensor suhu dan kelembaban.
- Task `read_data` membaca data sensor DHT11.
- Data dikirim ke queue menggunakan `xQueueSend()`.
- Task `display` menerima data menggunakan `xQueueReceive()`.
- Data kemudian ditampilkan pada Serial Monitor.
- `vTaskDelay()` digunakan agar pembacaan sensor lebih stabil.

### Hasil

Hasil percobaan menunjukkan bahwa data suhu dan kelembaban dapat ditampilkan secara dinamis pada Serial Monitor. Queue berhasil digunakan sebagai media komunikasi antar task tanpa menyebabkan konflik data.
