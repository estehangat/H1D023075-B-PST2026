# Jawaban Pertanyaan 3.6.4 (I2C)

## 1. Cara kerja komunikasi I2C antara Arduino dan LCD

Arduino sebagai master dan LCD sebagai slave.
Komunikasi menggunakan dua jalur:
- SDA (data)
- SCL (clock)

Alur:
1. Arduino mengirim alamat LCD (0x27)
2. LCD merespon
3. Data dikirim
4. LCD menampilkan data

## 2. Konfigurasi pin potensiometer

- Kiri → GND
- Tengah → A0
- Kanan → 5V

Jika kiri dan kanan ditukar:
- Nilai tetap terbaca
- Arah pembacaan terbalik

## 3. Modifikasi UART + I2C

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinPot = A0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int nilai = analogRead(pinPot);

  float volt = nilai * (5.0 / 1023.0);
  int persen = map(nilai, 0, 1023, 0, 100);

  Serial.print("ADC: ");
  Serial.print(nilai);
  Serial.print(" Volt: ");
  Serial.print(volt);
  Serial.print(" V Persen: ");
  Serial.print(persen);
  Serial.println("%");

  int panjangBar = map(nilai, 0, 1023, 0, 16);

  lcd.setCursor(0, 0);
  lcd.print("ADC: ");
  lcd.print(nilai);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < panjangBar) {
      lcd.print((char)255);
    } else {
      lcd.print(" ");
    }
  }

  delay(200);
}
```

## 4. Tabel hasil

| ADC | Volt (V) | Persen (%) |
|-----|----------|-----------|
| 1   | 0.00     | 0%        |
| 21  | 0.10     | 2%        |
| 49  | 0.24     | 4%        |
| 74  | 0.36     | 7%        |
| 96  | 0.47     | 9%        |
