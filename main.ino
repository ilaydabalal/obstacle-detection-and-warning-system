#define echoPin 6       // Ultrasonik sensörün Echo pini için D6 tanımlanıyor
#define trigPin 7       // Ultrasonik sensörün Trig pini için D7 tanımlanıyor
#define buzzerPin 8     // Buzzer cihazı için D8 pini tanımlanıyor

int maximumRange = 60;  // Maksimum ölçüm mesafesi (30 cm)
int minimumRange = 0;   // Minimum ölçüm mesafesi (0 cm)

void setup() {
  pinMode(trigPin, OUTPUT);   // Trig pini çıkış olarak ayarlanıyor (sinyal göndermek için)
  pinMode(echoPin, INPUT);    // Echo pini giriş olarak ayarlanıyor (sinyali almak için)
  pinMode(buzzerPin, OUTPUT); // Buzzer çıkış olarak ayarlanıyor (ses üretmek için)
}

void loop() {
  // Mesafeyi ölç ve sonucu 'olcum' değişkenine ata
  int olcum = mesafe(maximumRange, minimumRange);

  // Ölçülen mesafeye göre buzzer'ı çalıştır
  melodi(olcum * 10);
}

// Mesafe ölçümü yapan fonksiyon
int mesafe(int maxrange, int minrange) {
  long duration, distance;

  // Trig pinine kısa bir LOW-HIGH sinyali gönderilir
  digitalWrite(trigPin, LOW);   // Trig pinini sıfırla
  delayMicroseconds(2);         // 2 mikrosaniye bekle
  digitalWrite(trigPin, HIGH);  // Trig pinini HIGH yap (sinyal gönder)
  delayMicroseconds(10);        // 10 mikrosaniye boyunca sinyal gönder
  digitalWrite(trigPin, LOW);   // Trig pinini tekrar LOW yap

  // Echo pininden gelen sinyal süresi ölçülüyor
  duration = pulseIn(echoPin, HIGH); // Echo'dan gelen sinyal süresini ölç
  
  // Sinyal süresini santimetreye çevir (58.2 sabiti kullanılarak)
  distance = duration / 58.2;       

  delay(50); // Ölçümler arasında gecikme koy
  
  // Eğer mesafe maksimum veya minimum aralığın dışındaysa
  if (distance >= maxrange || distance <= minrange)
    return 0; // Geçersiz bir mesafe için 0 döndür

  return distance; // Geçerli mesafeyi döndür
}

// Buzzer melodisini çalan fonksiyon
int melodi(int dly) {
  tone(buzzerPin, 440); // 440 Hz frekansında bir ses üret (A4 notası)
  delay(dly);           // Verilen süre kadar sesi açık tut
  noTone(buzzerPin);    // Sesi kapat
  delay(dly);           // Ses kapalı haldeyken bekle
}
