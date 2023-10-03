// Função para escrever uma tag RFID na memória EEPROM, se ainda não estiver cadastrada
void writeRFIDTagToEEPROM(const String &tag) {
  if (isTagRegistered(receivedText)) {
    // Se a tag já estiver cadastrada, exibe uma mensagem e informa que a tag já existe
    escreve("TAG cadastrada", 0, 0, 1); // Exibe "TAG cadastrada" no LCD
    escreve(receivedText, 0, 1, 0); // Exibe o conteúdo da tag RFID no LCD
    Serial.println("Tag RFID já cadastrada.");
  } else {
    // Se a tag não estiver cadastrada, exibe uma mensagem e adiciona a tag à EEPROM
    escreve("TAG adicionada", 1, 0, 1); // Exibe "TAG adicionada" no LCD
    escreve(receivedText, 0, 1, 0); // Exibe o conteúdo da tag RFID no LCD
    Serial.println("Tag RFID adicionada");

    // Encontra o próximo endereço disponível na EEPROM
    int addr = findNextAvailableAddress();

    // Escreve a tag RFID na EEPROM
    for (int i = 0; i < RFID_TAG_LENGTH; i++) {
      EEPROM.write(addr + i, tag[i]);
    }
  }
}