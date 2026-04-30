# Jawaban Pertanyaan ADC

## 1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?
Fungsi `analogRead()` digunakan untuk membaca nilai tegangan analog dari pin analog Arduino (misalnya A0) dan mengubahnya menjadi nilai digital dalam rentang 0 sampai 1023. Pada rangkaian praktikum, fungsi ini digunakan untuk membaca posisi potensiometer sehingga dapat digunakan sebagai input untuk mengontrol perangkat lain seperti servo.

## 2. Mengapa diperlukan fungsi map() dalam program tersebut?
Fungsi `map()` digunakan untuk mengubah rentang nilai dari satu skala ke skala lain. Karena nilai ADC berada pada rentang 0–1023, sedangkan servo bekerja pada sudut tertentu (misalnya 30–150 derajat), maka diperlukan konversi nilai agar sesuai. Tanpa fungsi ini, pergerakan servo tidak akan proporsional.

## 3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada file README.md
Program dimodifikasi dengan menggunakan fungsi `map()` untuk membatasi sudut servo.

```cpp
#include <Servo.h>

Servo myServo;
int potPin = A0;
int nilaiADC;
int sudut;

void setup() {
  myServo.attach(9);
}

void loop() {
  nilaiADC = analogRead(potPin);
  sudut = map(nilaiADC, 0, 1023, 30, 150);
  myServo.write(sudut);
  delay(15);
}
```

## Penjelasan
- `analogRead()` membaca nilai potensiometer
- `map()` mengubah nilai ADC menjadi sudut servo 30–150
- `write()` menggerakkan servo sesuai sudut
- `delay()` memberi waktu stabilisasi
