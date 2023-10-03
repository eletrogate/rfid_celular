// Função para lidar com a comunicação Bluetooth
void bluetooth() {
  if (bluetoothSerial.available() >= 8) {
    // Verifica se há pelo menos 8 caracteres disponíveis para leitura no buffer Bluetooth
    bluetoothSerial.readBytes(receivedText, 8); // Lê os 8 caracteres
    receivedText[8] = '\0'; // Adiciona um caractere nulo para formar uma string válida

    // Exibe o texto recebido no monitor serial
    Serial.println("Texto recebido: " + String(receivedText));

    escreve("Tag adicionada:", 0, 0, 1); // Exibe a mensagem "Tag adicionada" no LCD
    escreve(receivedText, 0, 1, 0); // Exibe o conteúdo da tag RFID no LCD
    writeRFIDTagToEEPROM(receivedText); // Chama uma função para escrever a tag RFID na EEPROM
  }

  if (bluetoothSerial.available() > 0) {
    // Lê o byte mais antigo no buffer serial Bluetooth
    incomingByte = bluetoothSerial.read();
    
    // Se o byte recebido for 'R', realiza uma ação específica (no caso, limpa a EEPROM)
    if (incomingByte == 'R') {
      clearEEPROM(); // Chama uma função para limpar a EEPROM
      escreve("EEPROM limpa.", 0, 0, 1); // Exibe uma mensagem no LCD indicando que a EEPROM foi limpa
    }
  }
}