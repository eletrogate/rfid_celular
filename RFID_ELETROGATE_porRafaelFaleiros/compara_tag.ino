// Função para verificar se uma tag RFID está cadastrada na memória EEPROM
bool isTagRegistered(const String &tag) {
  for (int addr = 0; addr < EEPROM_SIZE; addr += RFID_TAG_LENGTH) {
    bool match = true;

    // Verifica se cada byte da EEPROM corresponde ao conteúdo da tag fornecida
    for (int i = 0; i < RFID_TAG_LENGTH; i++) {
      if (EEPROM.read(addr + i) != tag[i]) {
        match = false;
        break;
      }
    }

    // Se todas as posições da tag coincidirem, a tag está cadastrada
    if (match) {
      return true; // A tag está cadastrada na EEPROM
    }
  }

  // Se a função chegou até aqui, a tag não foi encontrada na EEPROM
  return false; // A tag não está cadastrada na EEPROM
}