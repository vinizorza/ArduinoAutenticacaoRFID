#include <SPI.h>

//Módulo RFID
#include <MFRC522.h>

//LCD
#include <Wire.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define BUZZER 8

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup()
{
  // Inicia a serial
  Serial.begin(9600);
  SPI.begin();
  // Inicia MFRC522
  mfrc522.PCD_Init();
  Serial.println();

  lcd.begin(16, 2);
  lcd.clear();

  pinMode(BUZZER, OUTPUT);
}

void loop() {

  //Aguarda proximidade do cartao/tag
  if ( ! mfrc522.PICC_IsNewCardPresent()) {

    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("APROXIME");
    lcd.setCursor(3, 1);
    lcd.print("O CARTAO");

    return;
  }
  //Seleciona o cartao/tag
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }


  //Caso nao saiba a ID de sua tag/cartao, descomente o comando abaixo e a ID aparecerá no Seria Monitor.
  //Serial.print("\nID: " + get_id());

  // O certo seria percorrer um vetor de Strings, verificando se há uma ID igual a lida, pois num caso real seriam várias.
  // Lembre de mudar esse valor, para a ID referente a sua tag/cartao
  if (get_id() == "7022721972") {

    //Mostrar ACESSO GARANTIDO no display
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("ACESSO");
    lcd.setCursor(3, 1);
    lcd.print("GARANTIDO");

    //Som de acesso garantido
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(100);
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    delay(5000);

  } else {

    //Mostrar ACESSO NEGADO no display
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("ACESSO");
    lcd.setCursor(3, 1);
    lcd.print("NEGADO");

    //Som de acesso negado
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
    delay(5000);

  }
}


//Retorna o ID ta Tag lida pelo RFID
String get_id() {

  String id = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    id.concat(String(mfrc522.uid.uidByte[i]));
  }

  return id;
}




