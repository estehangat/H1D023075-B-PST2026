# Jawaban Pertanyaan 5.5.4 - Multitasking RTOS

## 1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Ketiga task tidak benar-benar berjalan secara bersamaan karena Arduino Uno hanya memiliki satu inti prosesor. Namun, task berjalan secara concurrent menggunakan scheduler pada FreeRTOS.

Scheduler akan mengatur pembagian waktu eksekusi CPU kepada setiap task secara bergantian dengan sangat cepat sehingga terlihat berjalan bersamaan. Mekanisme ini disebut multitasking.

Pada program:
- `TaskBlink1` mengontrol LED pada pin 8
- `TaskBlink2` mengontrol LED pada pin 7
- `Taskprint` menampilkan counter pada Serial Monitor

Fungsi `vTaskDelay()` digunakan agar task memberikan kesempatan kepada task lain untuk dijalankan oleh scheduler.

---

## 2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!

Langkah menambahkan task keempat:

1. Membuat fungsi task baru

```cpp
void TaskBlink3(void *pvParameters) {
  pinMode(6, OUTPUT);

  while(1) {
    digitalWrite(6, HIGH);
    vTaskDelay(400 / portTICK_PERIOD_MS);

    digitalWrite(6, LOW);
    vTaskDelay(400 / portTICK_PERIOD_MS);
  }
}
```

2. Menambahkan `xTaskCreate()` pada `setup()`

```cpp
xTaskCreate(
  TaskBlink3,
  "task4",
  128,
  NULL,
  1,
  NULL
);
```

3. Menghubungkan LED tambahan ke pin 6.

Setelah task dibuat, scheduler FreeRTOS akan otomatis mengatur eksekusinya bersama task lainnya.

---

## 3. Modifikasi program dengan potensiometer untuk mengontrol kecepatan LED

### Program

```cpp
#include <Arduino_FreeRTOS.h>

int potPin = A0;
int delayLed;

void TaskBlink1(void *pvParameters);

void setup() {
  Serial.begin(9600);

  xTaskCreate(
    TaskBlink1,
    "task1",
    128,
    NULL,
    1,
    NULL
  );

  vTaskStartScheduler();
}

void loop() {
}

void TaskBlink1(void *pvParameters) {

  pinMode(8, OUTPUT);

  while(1) {

    int nilaiADC = analogRead(potPin);

    delayLed = map(nilaiADC, 0, 1023, 100, 1000);

    digitalWrite(8, HIGH);
    vTaskDelay(delayLed / portTICK_PERIOD_MS);

    digitalWrite(8, LOW);
    vTaskDelay(delayLed / portTICK_PERIOD_MS);

    Serial.print("ADC: ");
    Serial.println(nilaiADC);
  }
}
```

### Penjelasan Program

- `analogRead()` digunakan untuk membaca nilai potensiometer.
- Fungsi `map()` digunakan untuk mengubah nilai ADC menjadi delay LED.
- Semakin besar nilai potensiometer, maka delay semakin besar sehingga LED berkedip lebih lambat.
- `vTaskDelay()` digunakan agar scheduler tetap dapat menjalankan task lain.

### Hasil

Hasil percobaan menunjukkan bahwa kecepatan kedipan LED berubah sesuai posisi potensiometer. Sistem tetap berjalan stabil karena FreeRTOS mengatur eksekusi task secara terjadwal.
