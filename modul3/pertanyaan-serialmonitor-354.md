# Jawaban Pertanyaan 3.5.4 (UART)

## 1. Proses dari input keyboard hingga LED menyala/mati

Prosesnya sebagai berikut:

1. User mengetik karakter pada Serial Monitor (misalnya '1' atau '0').
2. Data dikirim dari komputer ke Arduino melalui komunikasi serial (USB → UART).
3. Arduino membaca data menggunakan:
   Serial.available()
4. Jika ada, data dibaca menggunakan:
   char data = Serial.read();
5. Program melakukan percabangan:
   - Jika '1' → LED menyala (HIGH)
   - Jika '0' → LED mati (LOW)
6. Arduino mengirim feedback ke Serial Monitor menggunakan:
   Serial.println()

## 2. Fungsi Serial.available() dan jika dihilangkan

Fungsi:
- Mengecek apakah ada data yang tersedia di buffer serial.
- Mencegah pembacaan data kosong.

Jika dihilangkan:
- Arduino tetap mencoba membaca data meskipun tidak ada input.
- Bisa menghasilkan nilai acak atau tidak valid.
- Program menjadi tidak stabil atau tidak responsif.

## 3. Modifikasi: LED berkedip saat input '2'

```cpp
const int PIN_LED = 12;
bool blinking = false;
unsigned long previousMillis = 0;
const long interval = 500;
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();

    if (data == '1') {
      blinking = false;
      digitalWrite(PIN_LED, HIGH);
    } 
    else if (data == '0') {
      blinking = false;
      digitalWrite(PIN_LED, LOW);
    } 
    else if (data == '2') {
      blinking = true;
    }
  }

  if (blinking) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(PIN_LED, ledState);
    }
  }
}
```

## 4. Delay() vs millis()

delay():
- Menghentikan seluruh program sementara
- Tidak bisa membaca input saat delay berjalan

millis():
- Tidak menghentikan program
- Bisa multitasking (LED tetap kedip + tetap bisa baca input)

Kesimpulan:
Lebih baik menggunakan millis() karena sistem menjadi responsif dan tidak blocking.
