
#include <Deneyap_OLED.h>
#include <Keypad.h>
#include "Keypad.h"

const byte satirsayisi = 4;  // satır sayısı
const byte sutunsayisi = 4;  // sütun sayısı

int randNumber = 0;

int tur = 3;
int turlar = 0;
float pcScore = 0.0;
float userScore = 0.0;

char basilantus;

char tustakimi[satirsayisi][sutunsayisi] = {  // Tuş takımının görüntüsünü
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte satirpinleri[satirsayisi] = { D0, D1, D4, D5 };  // satır pinleri
byte sutunpinleri[sutunsayisi] = { D6, D7, D8, D9 };  //sütun pinleri


Keypad keypad = Keypad(makeKeymap(tustakimi), satirpinleri, sutunpinleri, satirsayisi, sutunsayisi);
OLED OLED;

void tas(int x = 0) {
  int y = 0;
  if (x == 1) y = 11;
  OLED.setTextXY(2, y);
  OLED.putString("||||_");

  OLED.setTextXY(3, y);
  OLED.putString("****");

  OLED.setTextXY(4, y);
  OLED.putString("****");
}

void kgt(int x = 0) {
  int y = 0;
  if (x == 1) y = 11;
  OLED.setTextXY(0, y);
  OLED.putString("||||");

  OLED.setTextXY(1, y);
  OLED.putString("||||");

  OLED.setTextXY(2, y);
  OLED.putString("||||__");

  OLED.setTextXY(3, y);
  OLED.putString("****");

  OLED.setTextXY(4, y);
  OLED.putString("****");
}

void mks(int x = 0) {
  int y = 0;
  if (x == 1) y = 11;
  OLED.setTextXY(0, y);
  OLED.putString("  ||");

  OLED.setTextXY(1, y);
  OLED.putString("  ||");

  OLED.setTextXY(2, y);
  OLED.putString("||||_");

  OLED.setTextXY(3, y);
  OLED.putString("****");

  OLED.setTextXY(4, y);
  OLED.putString("****");
}

void rnd(int s) {
  switch (s) {
    case 1:
      tas(1);
      break;
    case 2:
      kgt(1);
      break;
    case 3:
      mks(1);
      break;
    default:
      break;
  }
}

void snc(char user, int pc) {
  int myNum[4] = { 0, 1, 2, 3 };
  switch (user) {
    case 'A':
      myNum[1] = 1;
      myNum[2] = 2;
      myNum[3] = 3;
      break;
    case 'B':
      myNum[1] = 3;
      myNum[2] = 1;
      myNum[3] = 2;
      break;
    case 'C':
      myNum[1] = 2;
      myNum[2] = 3;
      myNum[3] = 1;
      break;
  }
  sonucuyaz(myNum[pc]);
  //taş kagit ve makas durumlarında beraberlik, galibiyet ve mağlubiyet durumları listeye yazıldı
  //(1=Beraberlik , 2=Mağlubiyet, 3=Galibiyet)
  //klavyeden gelen harf A(taş) ise liste {0,1,2,3} şeklinde oluyor
  //rastgele seçilen sayı 1 (taş) ise listenin 1. elemanı alınıyor (1)
  //sonuç olarak beraberlik sağlanmış oluyor
}

void sonucuyaz(int sonuc) {
  OLED.setTextXY(7, 0);
  switch (sonuc) {
    case 1:
      OLED.putString("    Berabere");
      userScore = userScore + 0.5;
      pcScore = pcScore + 0.5;
      break;
    case 2:
      OLED.putString("  Kaybettiniz");
      pcScore++;
      break;
    case 3:
      OLED.putString("   Kazandiniz");
      userScore++;
      break;
  }
  basilantus = '0';
  for (; basilantus != 'A' && basilantus != 'B' && basilantus != 'C';) {
    basilantus = keypad.getKey();
  }
  //Serial.println(basilantus);
  OLED.clearDisplay();
}

void setup() {
  Serial.begin(9600);
  OLED.begin(0x78);     // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
  OLED.clearDisplay();  // OLED ekrandaki verilerin silinmesi

  OLED.setTextXY(0, 3);  // OLED satır sütun ayarlanması
  OLED.putString("Tas icin 'A'");

  OLED.setTextXY(2, 1);              // OLED satır sütun ayarlanması
  OLED.putString("Kagit icin 'B'");  // OLED ekrana string türünde ekrana yazı yazdırılması

  OLED.setTextXY(4, 1);  // OLED satır sütun ayarlanması
  OLED.putString("Makas icin 'C'");

  OLED.setTextXY(6, 1);  // OLED satır sütun ayarlanması
  OLED.putString("tas-kagit-makas");

  OLED.setTextXY(7, 5);  // OLED satır sütun ayarlanması
  OLED.putString("v1.0");

  for (; basilantus != 'A' && basilantus != 'B' && basilantus != 'C';) {
    basilantus = keypad.getKey();
  }
  OLED.clearDisplay();
}

void loop() {
  Serial.println(basilantus);
  if (turlar == tur) {
    OLED.clearDisplay();
    OLED.setTextXY(1, 3);
    OLED.putInt(tur);
    OLED.setTextXY(1, 4);
    OLED.putString(" tur sonucu");

    OLED.setTextXY(3, 0);
    OLED.putString("Siz:  ");
    OLED.setTextXY(3, 9);
    OLED.putFloat(userScore);

    OLED.setTextXY(4, 0);
    OLED.putString("TKM-bot: ");
    OLED.setTextXY(4, 9);
    OLED.putFloat(pcScore);

    OLED.setTextXY(6, 0);
    if (pcScore == userScore) sonucuyaz(1);
    if (pcScore > userScore) sonucuyaz(2);
    if (pcScore < userScore) sonucuyaz(3);

    pcScore = 0;
    userScore = 0;
    turlar = 0;

    for (; basilantus != 'A' && basilantus != 'B' && basilantus != 'C';) {
      basilantus = keypad.getKey();
    }
    OLED.setTextXY(0, 3);  // OLED satır sütun ayarlanması
    OLED.putString("Tas icin 'A'");

    OLED.setTextXY(2, 1);              // OLED satır sütun ayarlanması
    OLED.putString("Kagit icin 'B'");  // OLED ekrana string türünde ekrana yazı yazdırılması

    OLED.setTextXY(4, 1);  // OLED satır sütun ayarlanması
    OLED.putString("Makas icin 'C'");

    OLED.setTextXY(6, 1);  // OLED satır sütun ayarlanması
    OLED.putString("tas-kagit-makas");

    OLED.setTextXY(7, 5);  // OLED satır sütun ayarlanması
    OLED.putString("v1.0");
    basilantus = '0';
    for (; basilantus != 'A' && basilantus != 'B' && basilantus != 'C';) {
      basilantus = keypad.getKey();
    }
  }
  int randNumber = random(1, 4);
  // tuş takımından gelen değeri değişkene aktarıyoruz.

  OLED.setTextXY(1, 0);
  OLED.putString("      Tekrar      ");
  //  Serial.println(basilantus+"-tekraralti");

  if (basilantus == 'A' || basilantus == 'B' || basilantus == 'C') {
    turlar++;
    OLED.clearDisplay();

    //   Serial.println(basilantus);
    //   Serial.println("vloop if");

    if (basilantus == 'A') tas();
    else if (basilantus == 'B') kgt();
    else if (basilantus == 'C') mks();

    OLED.setTextXY(6, 9);
    OLED.putString("tkm-bot");

    OLED.setTextXY(6, 1);
    OLED.putString("Siz");
    delay(300);
    rnd(randNumber);
    delay(300);
    snc(basilantus, randNumber);
  } else basilantus = keypad.getKey();
}
