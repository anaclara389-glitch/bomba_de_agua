#include <Wire.h>
#include <LiquidCrystal_I2C.h>       //Bibliotecas
#include <EEPROM.h>
#include <Servo.h>

// --- OBJETOS E CONSTANTES GLOBAIS ---
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoBomba;

const int PINO_POT_NIVEL = A0;  
const int PINO_SERVO = 8;        
const int PINO_S1 = 6, PINO_S2 = 7, PINO_S3 = 9, PINO_S4 = 10, PINO_S5 = 11;
const int enderecoConsumoTotal = 0, enderecoVolumeAtual = 4, enderecoPorcentagem = 8;

// --- VARIÁVEIS GLOBAIS COMPARTILHADAS ---
float consumoTotal = 0.0;
float volumeAtual = 0.0;
float volumeReferencia = 0.0;
int porcentagem = 0;
int nivel = 0;
bool bombaLigada = false;
bool primeiraLeitura = true;
bool erroSensores = false;
int sensorComErro = 0;

unsigned long tempoAnteriorSalvar = 0;
unsigned long tempoAnteriorLCD = 0; 
unsigned long tempoAnteriorConsumo = 0; 

void setup() {
  setupMotorEEPROM(); // Arquivo Bomba.ino
  setupSensores();    // Arquivo Sensores.ino
  setupDisplay();     // Arquivo Display.ino
}

void loop() {
  unsigned long tempoAtual = millis();
  
  lerSensores(tempoAtual);      // Arquivo Sensores.ino
  controlarBomba();             // Arquivo Bomba.ino
  salvarDados(tempoAtual);      // Arquivo Bomba.ino
  atualizarDisplay(tempoAtual); // Arquivo Display.ino
  
  delay(10);
}
