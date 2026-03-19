void iniciarPinos() {
  pinMode(PINO_S1, INPUT_PULLUP);
  pinMode(PINO_S2, INPUT_PULLUP);
  pinMode(PINO_S3, INPUT_PULLUP);
  pinMode(PINO_S4, INPUT_PULLUP);
  pinMode(PINO_S5, INPUT_PULLUP);
}

void processarSensores() {
  bool s1_raw = (digitalRead(PINO_S1) == LOW);
  bool s2_raw = (digitalRead(PINO_S2) == LOW);
  bool s3_raw = (digitalRead(PINO_S3) == LOW);
  bool s4_raw = (digitalRead(PINO_S4) == LOW);
  bool s5_raw = (digitalRead(PINO_S5) == LOW);

  bool s1_valido = s1_raw;
  bool s2_valido = s1_raw && s2_raw;
  bool s3_valido = s1_raw && s2_raw && s3_raw;
  bool s4_valido = s1_raw && s2_raw && s3_raw && s4_raw;
  s5_valido = s1_raw && s2_raw && s3_raw && s4_raw && s5_raw; // Variável global

  erroSensores = false;
  sensorComErro = 0;

  if (s2_raw && !s1_raw) { erroSensores = true; sensorComErro = 1; } 
  else if (s3_raw && !s2_valido) { erroSensores = true; sensorComErro = 2; } 
  else if (s4_raw && !s3_valido) { erroSensores = true; sensorComErro = 3; } 
  else if (s5_raw && !s4_valido) { erroSensores = true; sensorComErro = 4; }

  if (erroSensores) {
    Serial.print("ALERTA: Erro detectado no sensor ");
    Serial.println(sensorComErro);
  }

  if (!erroSensores) {
    float limiteAcionado = 0.0;
    
    if (s5_valido) { nivel = 5; porcentagem = 85; limiteAcionado = 8500.0; }
    else if (s4_valido) { nivel = 4; porcentagem = 60; limiteAcionado = 6000.0; }
    else if (s3_valido) { nivel = 3; porcentagem = 45; limiteAcionado = 4500.0; }
    else if (s2_valido) { nivel = 2; porcentagem = 30; limiteAcionado = 3000.0; }
    else if (s1_valido) { nivel = 1; porcentagem = 15; limiteAcionado = 1500.0; }
    else { nivel = 0; porcentagem = 0; limiteAcionado = 0.0; }

    int potRaw = analogRead(PINO_POT_NIVEL);
    float volumePot = map(potRaw, 0, 1023, 0, 8500);

    float novoVolume = volumePot;
    if (novoVolume > limiteAcionado) {
      novoVolume = limiteAcionado;
    }

    if (novoVolume < volumeAtual) {
      consumoTotal += (volumeAtual - novoVolume);
    }
    
    volumeAtual = novoVolume;
    
    Serial.print("Sensores OK | Nivel: ");
    Serial.print(nivel);
    Serial.print(" | Volume: ");
    Serial.println(volumeAtual);
  }
}
