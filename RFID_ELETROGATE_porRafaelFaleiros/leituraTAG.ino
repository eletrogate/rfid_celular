// Função para ler e processar uma tag RFID
void leituraTAG() {
   escreve("Aproxime a TAG", 0, 0, 1); // Exibe "TAG cadastrada" no LCD
   escreve("do leitor", 0, 1, 0); // Exibe "TAG cadastrada" no LCD
   digitalWrite(ledAzul,HIGH);
  // Verifica se uma tag RFID está presente no leitor
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Lê a tag RFID e a armazena em uma string
    String rfidTag = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag += String(mfrc522.uid.uidByte[i], HEX);
      digitalWrite(ledAzul,LOW);
    }

    // Verifica se a tag lida está cadastrada na EEPROM
    if (isTagRegistered(rfidTag)) {
      escreve("TAG cadastrada", 0, 0, 1); // Exibe "TAG cadastrada" no LCD
      escreve(rfidTag, 0, 1, 0); // Exibe o conteúdo da tag RFID no LCD
      Serial.println("Tag RFID cadastrada.");
      Serial.println("Tag RFID lida: " + rfidTag); // Imprime a tag RFID no monitor serial 
    // aciona a trava por 3seg
     digitalWrite(trava,LOW);
     digitalWrite(ledVerde,HIGH);
     delay(3000);
     digitalWrite(trava,HIGH);
     digitalWrite(ledVerde,LOW);
    } else {
      escreve("TAG incorreta", 0, 0, 1); // Exibe "TAG incorreta" no LCD
      escreve(rfidTag, 0, 1, 0); // Exibe o conteúdo da tag RFID no LCD
      Serial.println("Tag RFID não cadastrada.");
      Serial.println("Tag RFID lida: " + rfidTag); // Imprime a tag RFID no monitor serial 
      digitalWrite(ledVermelho, HIGH);
      delay(3000);
      digitalWrite(ledVermelho, LOW);
    }
    // Aguarda um momento para evitar leituras múltiplas da mesma tag
    delay(1000);
  }
}
