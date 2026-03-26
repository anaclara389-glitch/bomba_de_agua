// Função para configurar os pinos dos sensores físicos no Arduino
void setupSensores() {
   // O INPUT_PULLUP ativa um resistor interno do Arduino.
  // Isso significa que, por padrão, o pino lê ALTO (HIGH/1). 
  // Quando a água (ou a boia) fecha o contato do sensor com o GND (Terra), o pino lê BAIXO (LOW/0).
  pinMode(PINO_S1, INPUT_PULLUP);
  pinMode(PINO_S2, INPUT_PULLUP);
  pinMode(PINO_S3, INPUT_PULLUP);
  pinMode(PINO_S4, INPUT_PULLUP);
  pinMode(PINO_S5, INPUT_PULLUP);
}

// Função principal que lê os sensores, detecta erros e calcula volume e consumo
void lerSensores(unsigned long tempoAtual) {
    // --- LEITURA BRUTA (RAW) DOS SENSORES ---
  // Lê o estado físico de cada pino. Como usamos INPUT_PULLUP, == LOW significa que a água atingiu o sensor.
  bool s1_raw = (digitalRead(PINO_S1) == LOW);
  bool s2_raw = (digitalRead(PINO_S2) == LOW);
  bool s3_raw = (digitalRead(PINO_S3) == LOW);
  bool s4_raw = (digitalRead(PINO_S4) == LOW);
  bool s5_raw = (digitalRead(PINO_S5) == LOW);

  // --- LÓGICA EM CASCATA (VALIDAÇÃO) ---
  // Garante que a água obedece às leis da física: a água não pode estar no nível 3 se não estiver no nível 2 e 1.
  // Um sensor só é considerado "válido" se ELE E TODOS OS ABAIXO DELE estiverem acionados.
  bool s1_valido = s1_raw;
  bool s2_valido = s1_raw && s2_raw;
  bool s3_valido = s1_raw && s2_raw && s3_raw;
  bool s4_valido = s1_raw && s2_raw && s3_raw && s4_raw;
  bool s5_valido = s1_raw && s2_raw && s3_raw && s4_raw && s5_raw;

   // Prepara as variáveis de erro para uma nova verificação
  erroSensores = false;
  sensorComErro = 0;

  // --- DETECÇÃO DE FALHAS ---
  // Se um sensor de cima está detectando água, mas o de baixo não, há um problema!
  // Pode ser uma boia travada, sujeira ou um fio desconectado.
  if (s2_raw && !s1_raw) { erroSensores = true; sensorComErro = 1; } 
  else if (s3_raw && !s2_valido) { erroSensores = true; sensorComErro = 2; } 
  else if (s4_raw && !s3_valido) { erroSensores = true; sensorComErro = 3; } 
  else if (s5_raw && !s4_valido) { erroSensores = true; sensorComErro = 4; }

   // Se tudo estiver funcionando perfeitamente (sem erros físicos), prossegue com os cálculos:
  if (!erroSensores) {
    float limiteAcionado = 0.0;
     // De cima para baixo, verifica qual o nível mais alto que a água atingiu
    if (s5_valido) { nivel = 5; porcentagem = 85; limiteAcionado = 8500.0; }
    else if (s4_valido) { nivel = 4; porcentagem = 60; limiteAcionado = 6000.0; }
    else if (s3_valido) { nivel = 3; porcentagem = 45; limiteAcionado = 4500.0; }
    else if (s2_valido) { nivel = 2; porcentagem = 30; limiteAcionado = 3000.0; }
    else if (s1_valido) { nivel = 1; porcentagem = 15; limiteAcionado = 1500.0; }
    else { nivel = 0; porcentagem = 0; limiteAcionado = 0.0; }
    // --- SIMULAÇÃO DO VOLUME FINO (POTENCIÔMETRO) ---
    // Lê o potenciômetro que simula a variação de água ENTRE as marcações dos sensores físicos
    int potRaw = analogRead(PINO_POT_NIVEL);
    // Converte a leitura do potenciômetro (0 a 1023) para a escala do volume do reservatório (0 a 8500 Litros)
    float novoVolume = map(potRaw, 0, 1023, 0, 8500);
    // Medida de segurança: o potenciômetro não pode indicar um volume MAIOR que o teto físico lido pelos sensores
    if (novoVolume > limiteAcionado) novoVolume = limiteAcionado;

    volumeAtual = novoVolume; // Atualiza a variável global do volume
    
    // --- CONFIGURAÇÃO INICIAL (START) ---
    // Na primeira vez que o código roda, marca o volume atual como ponto de partida para o consumo
    if (primeiraLeitura) {
      volumeReferencia = volumeAtual; 
      primeiraLeitura = false;
    }
    // --- CÁLCULO DE CONSUMO (A CADA 1 SEGUNDO) ---
    // Verifica se já passou 1 segundo (1000 ms) para checar se a água baixou
    if (tempoAtual - tempoAnteriorConsumo >= 1000) {
       // Se a água diminuiu em relação à última medição (referência), soma essa diferença ao consumo total
      if (!primeiraLeitura && (volumeAtual < volumeReferencia)) {
        consumoTotal += (volumeReferencia - volumeAtual);
      }
      // Atualiza a referência: a "régua" agora desce para medir as próximas quedas de água
      volumeReferencia = volumeAtual;
      
      // Reseta o cronômetro do consumo
      volumeReferencia = volumeAtual;
      // Reseta o cronômetro do consumo
      tempoAnteriorConsumo = tempoAtual;
    }
  }
}
