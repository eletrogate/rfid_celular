// Função para escrever texto no display LCD
void escreve(String palavra, int linha, int coluna, int apagar) {
  if (apagar == 1) {
    lcd.clear(); // Limpa o conteúdo do LCD se o parâmetro "apagar" for igual a 1
  }
  lcd.setCursor(linha, coluna); // Define a posição de escrita no LCD
  lcd.print(palavra); // Exibe a palavra no LCD na posição definida
}