// Função para ler e processar uma tag RFID
void leituraTAG() {
  // Verifica se uma tag RFID está presente no leitor
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Lê a tag RFID e a armazena em uma string
    String rfidTag = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      rfidTag += String(mfrc522.uid.uidByte[i], HEX);
    }

    // Verifica se a tag lida está cadastrada na EEPROM
    if (isTagRegistered(rfidTag)) {
      escreve("TAG cadastrada", 0, 0, 1); // Exibe "TAG cadastrada" no LCD
      escreve(rfidTag, 0, 1, 0); // Exibe o conteúdo da tag RFID no LCD
      Serial.println("Tag RFID cadastrada.");
    // aciona a trava por 3seg
      digitalWrite(trava,HIGH);
      delay(3000);
      digitalWrite(trava,LOW);
    } else {
      escreve("TAG incorreta", 0, 0, 1); // Exibe "TAG incorreta" no LCD
      escreve(rfidTag, 0, 1, 0); // Exibe o conteúdo da tag RFID no LCD
      Serial.println("Tag RFID não cadastrada.");
    }

    // Imprime a tag RFID no monitor serial e no LCD
    Serial.println("Tag RFID lida: " + rfidTag);


    // Aguarda um momento para evitar leituras múltiplas da mesma tag
    delay(1000);
  }
}
