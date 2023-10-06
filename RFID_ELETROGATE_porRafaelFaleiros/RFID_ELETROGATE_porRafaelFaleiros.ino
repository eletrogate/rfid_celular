#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define EEPROM_SIZE 1000 // Escolha o tamanho da EEPROM que deseja usar

#define trava 8 // define pino para trava solenoide da porta
#define ledVerde A5 // define o pino em que está conectado o terminal referente a cor verde do LED RGB
#define ledVermelho A6 // define o pino em que está conectado o terminal referente a cor vermelha do LED RGB
#define ledAzul A2 // define o pino em que está conectado o terminal referente a cor verde do LED RGB

// Define os pinos para a conexão ao display LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Define os pinos RX e TX para o módulo HC-05
const int bluetoothRxPin = 9;  // Conecte o TX do HC-05 ao pino 9 do Arduino
const int bluetoothTxPin = 10; // Conecte o RX do HC-05 ao pino 10 do Arduino
SoftwareSerial bluetoothSerial(bluetoothRxPin, bluetoothTxPin);

char receivedText[9]; // Cria um array para armazenar os 8 caracteres mais o caractere nulo

#define SDA_PIN A4  // Pino SS do MFRC522
#define RST_PIN A3   // Pino RST do MFRC522
#define RFID_TAG_LENGTH 8 // Tamanho da tag RFID (ajuste conforme necessário)
MFRC522 mfrc522(SDA_PIN, RST_PIN);  // Criação de uma instância do MFRC522
int incomingByte;

void setup() {

  //Define os pinos do LED RGB e do módulo relé como saida.
  pinMode(ledAzul,OUTPUT);
  pinMode(ledVerde,OUTPUT);
  pinMode(ledVermelho,OUTPUT);
  pinMode(trava, OUTPUT);
  
  // Inicialização do LCD
  lcd.begin(16, 2);

  // Inicialização das comunicações
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  // Verifica se a EEPROM está limpa ou contém dados
  if (isEEPROMCleared()) {
    // Se limpa, exibe mensagem e imprime no monitor serial
    escreve("EEPROM LIMPA", 0, 0, 1);
    Serial.println("A EEPROM está limpa.");
  } else {
    // Se contém dados, exibe mensagem e imprime no monitor serial
    escreve("EEPROM ESCRITA", 0, 0, 1);
    Serial.println("A EEPROM não está limpa.");
  }
  delay(1000);
}

void loop() {
  digitalWrite(trava,HIGH);
  digitalWrite(ledAzul,HIGH);
  leituraTAG(); // Função para ler as tags RFID
  bluetooth(); // Função para lidar com a comunicação Bluetooth
}

// Função para encontrar o próximo endereço disponível na EEPROM
int findNextAvailableAddress() {
  for (int addr = 0; addr < EEPROM_SIZE; addr += RFID_TAG_LENGTH) {
    bool isEmpty = true;

    // Verifica cada byte na EEPROM no espaço reservado para a tag RFID
    for (int i = 0; i < RFID_TAG_LENGTH; i++) {
      if (EEPROM.read(addr + i) != 0) {
        isEmpty = false;
        break; // Se encontrar um byte não vazio, a tag não está presente
      }
    }

    // Se não foi encontrado nenhum byte não vazio (tag presente), retorna o endereço
    if (isEmpty) {
      return addr;
    }
  }
  return -1; // Retorna -1 se não houver espaço disponível na EEPROM
}

// Função para verificar se a EEPROM está limpa (todos os bytes são 0)
bool isEEPROMCleared() {
  for (int i = 0; i < EEPROM_SIZE; i++) {

    // Verifica cada byte na EEPROM
    if (EEPROM.read(i) != 0) {
      return false; // Se encontrar um byte diferente de zero, a EEPROM não está limpa
    }
  }
  return true; // Se não encontrou nenhum byte diferente de zero, a EEPROM está limpa
}
