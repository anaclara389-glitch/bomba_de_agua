void setupMotorEEPROM() {
  servoBomba.attach(PINO_SERVO);
 
  EEPROM.get(enderecoConsumoTotal, consumoTotal);
  if (isnan(consumoTotal) || consumoTotal < 0.0 || consumoTotal > 99999.0) consumoTotal = 0.0;

  EEPROM.get(enderecoVolumeAtual, volumeAtual);
  if (isnan(volumeAtual) || volumeAtual < 0.0) volumeAtual = 0.0;
  if (volumeAtual > 8500.0) volumeAtual = 8500.0;

  EEPROM.get(enderecoPorcentagem, porcentagem);
  if (porcentagem < 0 || porcentagem > 100) porcentagem = 0;
 
  if (porcentagem >= 85) nivel = 5;
  else if (porcentagem >= 60) nivel = 4;
  else if (porcentagem >= 45) nivel = 3;
  else if (porcentagem >= 30) nivel = 2;
  else if (porcentagem >= 15) nivel = 1;
  else nivel = 0;
}

void controlarBomba() {
  // s5_valido não existe diretamente aqui, mas sabemos que se nível == 5, a caixa tá cheia.
  // Vamos usar a lógica de porcentagem para ser mais seguro, ou checar o erro.
  if (nivel == 5 || erroSensores) {  
    bombaLigada = false;
    servoBomba.write(90);
  } else {        
    bombaLigada = true;
    servoBomba.write(180);
  }
}

void salvarDados(unsigned long tempoAtual) {
  if (tempoAtual - tempoAnteriorSalvar >= 5000) {
    EEPROM.put(enderecoConsumoTotal, consumoTotal);
    EEPROM.put(enderecoVolumeAtual, volumeAtual);
    EEPROM.put(enderecoPorcentagem, porcentagem);
    tempoAnteriorSalvar = tempoAtual;
  }
}
