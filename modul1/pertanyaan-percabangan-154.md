# README – Percobaan 1A: Percabangan (if / if-else)

## Kode Program Dasar (dari Modul)

```cpp
const int ledPin = 6;   // LED terhubung ke pin digital 6
int timeDelay = 1000;   // delay awal 1000 ms (1 detik)

void setup() {
  pinMode(ledPin, OUTPUT); // atur pin 6 sebagai OUTPUT
}

void loop() {
  // Nyalakan LED
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);

  // Matikan LED
  digitalWrite(ledPin, LOW);
  delay(timeDelay);

  // Evaluasi kondisi setelah 1 siklus kedip selesai
  if (timeDelay <= 100) {
    delay(3000);       // jeda 3 detik sebelum reset
    timeDelay = 1000;  // kembalikan delay ke nilai awal
  } else {
    timeDelay -= 100;  // kurangi delay 100 ms (LED makin cepat)
  }
}
```

---

## Jawaban Pertanyaan Praktikum 1.5.4

### 1. Pada kondisi apa program masuk ke blok `if`?

Program masuk ke blok `if` ketika nilai variabel `timeDelay` **kurang dari atau sama dengan 100** (ms).

```cpp
if (timeDelay <= 100) { ... }
```

Kondisi ini terjadi setelah LED berkedip berulang kali dan setiap siklus delay-nya dikurangi 100 ms, hingga akhirnya mencapai nilai 100 ms atau lebih kecil. Pada titik ini LED sudah berkedip sangat cepat, dan program masuk ke blok `if` untuk memberikan jeda 3 detik lalu mereset `timeDelay` ke 1000 ms.

---

### 2. Pada kondisi apa program masuk ke blok `else`?

Program masuk ke blok `else` ketika nilai `timeDelay` **lebih besar dari 100** (ms).

```cpp
} else {
  timeDelay -= 100;
}
```

Setiap kali kondisi `if` tidak terpenuhi, program masuk ke `else` dan mengurangi `timeDelay` sebesar 100 ms. Ini menyebabkan kecepatan kedip LED bertambah secara bertahap di setiap siklus berikutnya (dari lambat → semakin cepat).

---

### 3. Apa fungsi dari perintah `delay(timeDelay)`?

Perintah `delay(timeDelay)` berfungsi untuk **menghentikan eksekusi program sementara** selama `timeDelay` milidetik sebelum melanjutkan ke perintah berikutnya.

Dalam konteks percobaan ini:
- `delay(timeDelay)` setelah `digitalWrite(ledPin, HIGH)` → membuat LED **tetap menyala** selama `timeDelay` ms.
- `delay(timeDelay)` setelah `digitalWrite(ledPin, LOW)` → membuat LED **tetap mati** selama `timeDelay` ms.

Karena nilai `timeDelay` terus berkurang setiap siklus, durasi nyala dan mati LED semakin pendek, sehingga LED tampak berkedip semakin cepat.

---

### 4. Modifikasi: Alur Mati → Lambat → Cepat → Sedang → Mati (tanpa langsung reset)

Perubahan dari spesifikasi awal:
- **Sebelum (modul):** mati → lambat → cepat → reset (langsung mati)
- **Sesudah (modifikasi):** mati → lambat → cepat → sedang → mati (bertahap)

Untuk mewujudkan hal ini, ditambahkan **fase perlambatan kembali** setelah LED mencapai kecepatan maksimum, sebelum akhirnya berhenti.

#### Kode Program Modifikasi

```cpp
const int ledPin = 6;     // LED terhubung ke pin digital 6
int timeDelay = 1000;     // delay awal: 1000 ms (lambat)
bool percepat = true;     // flag arah perubahan delay

void setup() {
  // Inisialisasi pin 6 sebagai output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // === Fase Mati Awal (hanya saat pertama / setelah reset) ===
  // Tidak perlu kode khusus; LED mati secara default saat reset

  // Nyalakan LED selama timeDelay ms
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);

  // Matikan LED selama timeDelay ms
  digitalWrite(ledPin, LOW);
  delay(timeDelay);

  // === Logika Percabangan: tentukan arah perubahan delay ===

  if (percepat) {
    // Fase: Lambat → Cepat
    // Selama flag percepat = true, kurangi delay setiap siklus
    if (timeDelay > 100) {
      timeDelay -= 100;   // percepat kedipan (kurangi delay 100 ms)
    } else {
      // Kecepatan maksimum tercapai, mulai fase perlambatan
      percepat = false;   // balik arah: sekarang perlambat
    }
  } else {
    // Fase: Cepat → Sedang → Mati
    // Selama flag percepat = false, tambah delay setiap siklus
    if (timeDelay < 600) {
      timeDelay += 100;   // perlambat kedipan (tambah delay 100 ms)
    } else {
      // Kecepatan "sedang" (600 ms) tercapai, masuk fase mati
      digitalWrite(ledPin, LOW);  // pastikan LED mati
      delay(3000);                 // jeda 3 detik (fase mati)

      // Reset semua variabel ke kondisi awal
      timeDelay = 1000;
      percepat = true;
    }
  }
}
```

#### Penjelasan Baris per Baris

| Baris / Bagian | Penjelasan |
|---|---|
| `const int ledPin = 6;` | Mendefinisikan pin 6 sebagai pin LED; `const` agar nilai tidak berubah. |
| `int timeDelay = 1000;` | Nilai delay awal 1000 ms → LED berkedip lambat di awal. |
| `bool percepat = true;` | Flag boolean untuk menentukan arah: `true` = sedang mempercepat, `false` = sedang memperlambat. |
| `pinMode(ledPin, OUTPUT);` | Mengatur pin 6 sebagai output agar bisa mengendalikan LED. |
| `digitalWrite(ledPin, HIGH);` | Menyalakan LED dengan memberi tegangan HIGH pada pin 6. |
| `delay(timeDelay);` | Menunggu selama `timeDelay` ms sebelum lanjut (lamanya LED menyala). |
| `digitalWrite(ledPin, LOW);` | Mematikan LED. |
| `delay(timeDelay);` | Menunggu selama `timeDelay` ms (lamanya LED mati). |
| `if (percepat)` | Cek apakah program sedang dalam fase percepatan. |
| `if (timeDelay > 100)` | Jika delay masih di atas 100 ms, masih ada ruang untuk mempercepat. |
| `timeDelay -= 100;` | Kurangi delay 100 ms → LED berkedip 100 ms lebih cepat dari siklus sebelumnya. |
| `percepat = false;` | Saat delay mencapai 100 ms (maksimum cepat), ubah arah ke perlambatan. |
| `if (timeDelay < 600)` | Jika delay belum mencapai 600 ms (titik "sedang"), terus perlambat. |
| `timeDelay += 100;` | Tambah delay 100 ms → LED berkedip lebih lambat. |
| `delay(3000);` | Jeda 3 detik dalam kondisi LED mati sebelum siklus baru dimulai. |
| `timeDelay = 1000; percepat = true;` | Reset semua variabel ke kondisi awal sehingga siklus berulang dari awal. |

#### Alur Eksekusi Program

```
[Mulai]
   ↓
LED berkedip lambat (1000 ms) 
   ↓
Setiap siklus: delay dikurangi 100 ms
   ↓
LED berkedip cepat (100 ms) ← titik balik
   ↓
Setiap siklus: delay ditambah 100 ms
   ↓
LED berkedip sedang (600 ms) ← titik berhenti
   ↓
LED mati → jeda 3 detik
   ↓
[Reset → ulang dari awal]
```
