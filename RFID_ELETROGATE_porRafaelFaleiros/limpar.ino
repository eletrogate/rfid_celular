// Função para limpar (apagar) todos os dados na memória EEPROM
void clearEEPROM() {
  for (int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 0); // Escreve o valor zero em cada endereço da EEPROM
  }
  Serial.println("EEPROM limpa."); // Imprime uma mensagem indicando que a EEPROM foi apagada
}