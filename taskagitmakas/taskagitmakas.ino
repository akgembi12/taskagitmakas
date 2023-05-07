
#include <Deneyap_OLED.h>
#include <Keypad.h>
#include "Keypad.h"

const byte satirsayisi = 4;  // satır sayısı
const byte sutunsayisi = 4;  // sütun sayısı

int randNumber = 0;

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


void setup() {
  Serial.begin(115200);
  OLED.begin(0x78);     // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
  OLED.clearDisplay();  // OLED ekrandaki verilerin silinmesi

  OLED.setTextXY(0, 2);  // OLED satır sütun ayarlanması
  OLED.putString(" Tas icin 'A'");

  OLED.setTextXY(2, 1);              // OLED satır sütun ayarlanması
  OLED.putString("Kagit icin 'B'");  // OLED ekrana string türünde ekrana yazı yazdırılması

  OLED.setTextXY(4, 1);  // OLED satır sütun ayarlanması
  OLED.putString("Makas icin 'C'");

  OLED.setTextXY(6, 1);  // OLED satır sütun ayarlanması
  OLED.putString("tas-kagit-makas");

  OLED.setTextXY(7, 5);  // OLED satır sütun ayarlanması
  OLED.putString("v1.0");

  delay(3000);
  OLED.clearDisplay();
}

void loop() {

  int randNumber = random(1, 4);
  char basilantus = keypad.getKey();  // tuş takımından gelen değeri değişkene aktarıyoruz.


  delay(15);
  OLED.setTextXY(1, 0);
  OLED.putString("      Tekrar      ");

  if (basilantus != NO_KEY) {  // basilantus değişkeni ile no_key(key yok ) eşit değilse
    Serial.println(basilantus);
    if (basilantus == 'A') {
      OLED.setTextXY(0, 0);
      OLED.putString("  Secilen:Tas   ");

      if (randNumber == 1) {
        OLED.setTextXY(1, 0);
        OLED.putString(" Bilgisayar:Tas ");
        OLED.setTextXY(2, 0);
        OLED.putString("     Berabere     ");
      } else if (randNumber == 2) {
        OLED.setTextXY(1, 0);
        OLED.putString("Bilgisayar:Kagit");
        OLED.setTextXY(2, 0);
        OLED.putString("   Kaybettiniz    ");
      } else if (randNumber == 3) {
        OLED.setTextXY(1, 0);
        OLED.putString("Bilgisayar:Makas");
        OLED.setTextXY(2, 0);
        OLED.putString("    Kazandiniz    ");
      }


    }

    else if (basilantus == 'B') {
      OLED.setTextXY(0, 0);
      OLED.putString("  Secilen:Kagit   ");

      if (randNumber == 1) {
        OLED.setTextXY(1, 0);
        OLED.putString("  Bilgisayar:Tas  ");
        OLED.setTextXY(2, 0);
        OLED.putString("    Kazandiniz    ");
      } else if (randNumber == 2) {
        OLED.setTextXY(1, 0);
        OLED.putString(" Bilgisayar:Kagit ");
        OLED.setTextXY(2, 0);
        OLED.putString("    Berabere      ");
      } else if (randNumber == 3) {
        OLED.setTextXY(1, 0);
        OLED.putString(" Bilgisayar:Makas ");
        OLED.setTextXY(2, 0);
        OLED.putString("   Kaybettiniz    ");
      }

    }

    else if (basilantus == 'C') {
      OLED.setTextXY(0, 0);
      OLED.putString("  Secilen:Makas   ");

      if (randNumber == 1) {
        OLED.setTextXY(1, 0);
        OLED.putString("  Bilgisayar:Tas  ");
        OLED.setTextXY(2, 0);
        OLED.putString("    Kaybettiniz   ");
      } else if (randNumber == 2) {
        OLED.setTextXY(1, 0);
        OLED.putString(" Bilgisayar:Kagit ");
        OLED.setTextXY(2, 0);
        OLED.putString("   Kazandiniz     ");
      } else if (randNumber == 3) {
        OLED.setTextXY(1, 0);
        OLED.putString(" Bilgisayar:Makas ");
        OLED.setTextXY(2, 0);
        OLED.putString("    Berabere      ");
      }
    }
    delay(3465);
    OLED.clearDisplay();
  }
}



/*
  OLED.setTextXY(0,0);
  OLED.putString("                ");
  OLED.setTextXY(1,0);
  OLED.putString("                ");
  OLED.setTextXY(2,0);
  OLED.putString("                ");
  OLED.setTextXY(3,0);
  OLED.putString("                ");
  OLED.setTextXY(4,0);
  OLED.putString("                ");
  OLED.setTextXY(5,0);
  OLED.putString("                ");
  OLED.setTextXY(6,0);
  OLED.putString("                ");
  OLED.setTextXY(7,0);
  OLED.putString("                ");

*/







/*

| | | |                        | |
| | | |                        | |
| | | |____     | | | |_   | | | |_  
|||||||         |||||||    |||||||
|||||||         |||||||    |||||||

*/