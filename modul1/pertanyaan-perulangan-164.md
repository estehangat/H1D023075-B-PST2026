# Percobaan 2A: Perulangan (for)

## Jawaban Pertanyaan Praktikum 1.6.4

### 1. Gambar Skematik Rangkaian 6 LED Running

```
Arduino Uno
                     220Ω
Pin 2  ──────────┤├────── Anoda LED1 ── Katoda ──┐
                     220Ω                         │
Pin 3  ──────────┤├────── Anoda LED2 ── Katoda ──┤
                     220Ω                         │
Pin 4  ──────────┤├────── Anoda LED3 ── Katoda ──┤
                     220Ω                         │
Pin 5  ──────────┤├────── Anoda LED4 ── Katoda ──┤
                     220Ω                         │
Pin 6  ──────────┤├────── Anoda LED5 ── Katoda ──┤
                     220Ω                         │
Pin 7  ──────────┤├────── Anoda LED6 ── Katoda ──┤
                                                  │
GND    ───────────────────────────────────────────┘
```

**Keterangan:**
- Setiap LED dihubungkan seri dengan resistor 220Ω untuk membatasi arus.
- Anoda (+) LED terhubung ke pin Arduino melalui resistor.
- Katoda (−) semua LED terhubung ke GND bersama (common ground).
- LED 1 s.d. LED 6 berurutan di pin 2, 3, 4, 5, 6, 7.

---

### 2. Bagaimana program membuat efek LED berjalan dari kiri ke kanan?

Efek kiri → kanan dibuat oleh perulangan `for` pertama di dalam `loop()`:

```cpp
for (int ledPin = 2; ledPin < 8; ledPin++) {
  digitalWrite(ledPin, HIGH); // nyalakan LED di pin saat ini
  delay(timer);               // tahan selama 100 ms
  digitalWrite(ledPin, LOW);  // matikan sebelum pindah ke pin berikutnya
}
```

**Cara kerjanya:**
1. Variabel `ledPin` dimulai dari nilai **2** (LED paling kiri).
2. Setiap iterasi, LED pada `ledPin` dinyalakan, ditahan selama `timer` ms, lalu dimatikan.
3. Nilai `ledPin` bertambah 1 (`ledPin++`) setiap iterasi.
4. Perulangan berlanjut selama `ledPin < 8`, artinya hingga pin **7** (LED paling kanan).
5. Karena hanya satu LED yang menyala dalam satu waktu dan posisinya berpindah ke kanan setiap iterasi, tampak seolah cahaya "berjalan" dari kiri ke kanan.

---

### 3. Bagaimana program membuat LED kembali dari kanan ke kiri?

Efek kanan → kiri dibuat oleh perulangan `for` kedua:

```cpp
for (int ledPin = 7; ledPin >= 2; ledPin--) {
  digitalWrite(ledPin, HIGH); // nyalakan LED di pin saat ini
  delay(timer);               // tahan selama 100 ms
  digitalWrite(ledPin, LOW);  // matikan sebelum pindah ke pin sebelumnya
}
```

**Cara kerjanya:**
1. Variabel `ledPin` dimulai dari nilai **7** (LED paling kanan).
2. Setiap iterasi, LED pada `ledPin` dinyalakan, ditahan, lalu dimatikan.
3. Nilai `ledPin` **berkurang** 1 (`ledPin--`) setiap iterasi — ini yang membedakan dari loop pertama.
4. Perulangan berlanjut selama `ledPin >= 2`, artinya hingga pin **2** (LED paling kiri).
5. Karena posisi LED aktif bergerak dari pin tinggi ke pin rendah, tampak seolah cahaya "berjalan" kembali dari kanan ke kiri.

Kedua loop ini berjalan bergantian tanpa henti di dalam `loop()`, sehingga menciptakan efek bolak-balik yang terus-menerus.

---

### 4. Program: Tiga LED Kiri dan Tiga LED Kanan Menyala Bergantian

#### Deskripsi Perilaku
- **Fase A:** LED 1, 2, 3 (pin 2, 3, 4) menyala bersamaan selama 500 ms.
- **Fase B:** LED 4, 5, 6 (pin 5, 6, 7) menyala bersamaan selama 500 ms.
- Kedua fase bergantian terus-menerus tanpa henti.

#### Kode Program

```cpp
int timer = 500; // durasi setiap kelompok LED menyala (ms)

void setup() {
  // Inisialisasi pin 2 hingga 7 sebagai OUTPUT
  // menggunakan perulangan for agar tidak perlu menulis 6 baris pinMode
  for (int ledPin = 2; ledPin < 8; ledPin++) {
    pinMode(ledPin, OUTPUT); // setiap pin diatur sebagai output
  }
}

void loop() {

  // === FASE A: Nyalakan tiga LED kiri (pin 2, 3, 4) ===

  // Perulangan for: menyalakan pin 2, 3, 4 satu per satu secara berurutan
  for (int ledPin = 2; ledPin < 5; ledPin++) {
    digitalWrite(ledPin, HIGH); // nyalakan LED pada pin ledPin
  }

  // Tahan kondisi menyala selama timer ms
  delay(timer);

  // Matikan kembali semua LED kiri (pin 2, 3, 4)
  for (int ledPin = 2; ledPin < 5; ledPin++) {
    digitalWrite(ledPin, LOW); // matikan LED pada pin ledPin
  }

  // === FASE B: Nyalakan tiga LED kanan (pin 5, 6, 7) ===

  // Perulangan for: menyalakan pin 5, 6, 7 satu per satu secara berurutan
  for (int ledPin = 5; ledPin < 8; ledPin++) {
    digitalWrite(ledPin, HIGH); // nyalakan LED pada pin ledPin
  }

  // Tahan kondisi menyala selama timer ms
  delay(timer);

  // Matikan kembali semua LED kanan (pin 5, 6, 7)
  for (int ledPin = 5; ledPin < 8; ledPin++) {
    digitalWrite(ledPin, LOW); // matikan LED pada pin ledPin
  }

  // Setelah fase B selesai, loop() akan dipanggil ulang otomatis
  // sehingga siklus A → B terus berulang tanpa henti
}
```

#### Penjelasan Baris per Baris

| Baris / Bagian | Penjelasan |
|---|---|
| `int timer = 500;` | Mendefinisikan durasi nyala setiap kelompok LED yaitu 500 ms (0,5 detik). Ubah nilai ini untuk mengatur kecepatan pergantian. |
| `for (int ledPin = 2; ledPin < 8; ledPin++)` di `setup()` | Mengulang dari pin 2 hingga 7 untuk mendaftarkan semua pin LED sebagai OUTPUT sekaligus, sehingga tidak perlu menulis `pinMode` 6 kali. |
| `pinMode(ledPin, OUTPUT);` | Mengatur setiap pin yang diiterasi sebagai mode OUTPUT agar dapat mengeluarkan sinyal HIGH/LOW. |
| **FASE A** | |
| `for (int ledPin = 2; ledPin < 5; ledPin++)` | Mengulang dari pin 2 ke 4 (tiga LED kiri). Kondisi `ledPin < 5` memastikan loop berhenti sebelum pin 5. |
| `digitalWrite(ledPin, HIGH);` | Menyalakan LED pada pin yang sedang diiterasi dengan memberi tegangan HIGH. |
| `delay(timer);` | Menahan semua LED kiri tetap menyala selama `timer` ms sebelum dimatikan. |
| `for (int ledPin = 2; ledPin < 5; ledPin++)` (matikan) | Loop kedua yang identik, kali ini mengirim LOW untuk mematikan semua LED kiri. |
| `digitalWrite(ledPin, LOW);` | Mematikan LED pada pin yang sedang diiterasi. |
| **FASE B** | |
| `for (int ledPin = 5; ledPin < 8; ledPin++)` | Mengulang dari pin 5 ke 7 (tiga LED kanan). Logika sama dengan Fase A namun pada kelompok pin yang berbeda. |
| `digitalWrite(ledPin, HIGH);` | Menyalakan LED kanan. |
| `delay(timer);` | Menahan LED kanan menyala selama `timer` ms. |
| `for (int ledPin = 5; ledPin < 8; ledPin++)` (matikan) | Mematikan semua LED kanan. |
| `digitalWrite(ledPin, LOW);` | Mematikan LED pada pin yang diiterasi. |
| Akhir `loop()` | Arduino secara otomatis memanggil `loop()` kembali dari awal, sehingga Fase A dan B berulang terus-menerus. |

#### Alur Eksekusi Program

```
[Mulai / Reset]
      ↓
[setup()] → Inisialisasi pin 2–7 sebagai OUTPUT
      ↓
[loop() – Fase A]
  Nyalakan LED pin 2, 3, 4 → tahan 500 ms → matikan
      ↓
[loop() – Fase B]
  Nyalakan LED pin 5, 6, 7 → tahan 500 ms → matikan
      ↓
[Ulangi terus dari Fase A ...]
```

#### Wiring Rangkaian (sama dengan percobaan utama)

| No | Komponen | Pin Arduino |
|---|---|---|
| 1 | LED 1 (Kiri) | Pin 2 |
| 2 | LED 2 (Kiri) | Pin 3 |
| 3 | LED 3 (Kiri) | Pin 4 |
| 4 | LED 4 (Kanan) | Pin 5 |
| 5 | LED 5 (Kanan) | Pin 6 |
| 6 | LED 6 (Kanan) | Pin 7 |
| 7 | GND semua LED | GND |

Setiap LED dipasang seri dengan resistor 220Ω antara pin Arduino dan anoda LED. Katoda semua LED dihubungkan ke GND bersama.
