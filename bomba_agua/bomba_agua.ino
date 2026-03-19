#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Servo.h>

// --- VARIÁVEIS GLOBAIS ---
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servoBomba;

const int PINO_POT_NIVEL = A0;  
const int PINO_SERVO = 8;        
const int PINO_S1 = 6;  
const int PINO_S2 = 7;  
const int PINO_S3 = 9;  
const int PINO_S4 = 10; 
const int PINO_S5 = 11; 

const int enderecoConsumoTotal = 0;
const int enderecoVolumeAtual = 4;
const int enderecoPorcentagem = 8;

float consumoTotal = 0.0;
float volumeAtual = 0.0;
int porcentagem = 0;
int nivel = 0;

unsigned long tempoAnteriorSalvar = 0;
bool bombaLigada = false;
bool erroSensores = false;
int sensorComErro = 0;
bool s5_valido = false; // Necessário para a bomba

void setup() {
  Serial.begin(9600); // Inicia a comunicação com o Serial Monitor
  Serial.println("Iniciando o Sistema da Caixa D'agua...");
  
  iniciarPinos();
  iniciarDisplay();
  iniciarMemoria();
}

void loop() {
  processarSensores();
  controlarBomba();
  salvarMemoria();
  atualizarDisplay();
  delay(50);
}
