// Função responsável por inicializar o motor (bomba) e recuperar os dados salvos na memória
void setupMotorEEPROM() {
  // Conecta o objeto do servo motor ao pino físico definido no Arduino (simulando a bomba)
  servoBomba.attach(PINO_SERVO);

   // --- RECUPERAÇÃO DO CONSUMO TOTAL ---
  // Lê da memória EEPROM o valor do "consumoTotal" salvo no endereço correspondente
  EEPROM.get(enderecoConsumoTotal, consumoTotal);
  // Verifica se o valor lido é inválido (NaN - Not a Number), negativo ou maior que o limite aceitável.
  // Se for inválido, reseta o consumo total para 0.0 (evita erros ao ligar o sistema pela primeira vez)
  if (isnan(consumoTotal) || consumoTotal < 0.0 || consumoTotal > 99999.0) consumoTotal = 0.0;

  // --- RECUPERAÇÃO DO VOLUME ATUAL ---
  // Lê da memória EEPROM o valor do "volumeAtual"
  EEPROM.get(enderecoVolumeAtual, volumeAtual);
  // Validações de segurança para o volume: reseta se for inválido ou negativo
  if (isnan(volumeAtual) || volumeAtual < 0.0) volumeAtual = 0.0;
  // Trava o volume no limite máximo da caixa d'água (exemplo: 8500.0) caso o valor salvo seja maior
  if (volumeAtual > 8500.0) volumeAtual = 8500.0;

  // --- RECUPERAÇÃO DA PORCENTAGEM ---
  // Lê a "porcentagem" do nível da água salva na EEPROM
  EEPROM.get(enderecoPorcentagem, porcentagem);
  // Se a porcentagem lida estiver fora da realidade (menor que 0 ou maior que 100), reseta para 0
  if (porcentagem < 0 || porcentagem > 100) porcentagem = 0;

  // --- DEFINIÇÃO DO NÍVEL (CASCATA) ---
  // Define a variável "nivel" (de 0 a 5) com base na porcentagem recuperada da memória.
  // Isso ajuda o sistema a saber em que estado a caixa d'água estava antes de ser desligada.
  if (porcentagem >= 85) nivel = 5;
  else if (porcentagem >= 60) nivel = 4;
  else if (porcentagem >= 45) nivel = 3;
  else if (porcentagem >= 30) nivel = 2;
  else if (porcentagem >= 15) nivel = 1;
  else nivel = 0;
}

// Função responsável por ligar ou desligar a bomba de água (servo motor) com base no nível
void controlarBomba() {
  // s5_valido não existe diretamente aqui, mas sabemos que se nível == 5, a caixa estará cheia.
   // Verifica se a caixa d'água já está no nível máximo (5) ou se o sistema detectou alguma falha nos sensores
  if (nivel == 5 || erroSensores) {  
    bombaLigada = false;  // Atualiza a variável de estado informando que a bomba está desligada
    servoBomba.write(90);   // Move o servo motor para 90 graus (posição que representa a bomba DESLIGADA)
  } else {        
     // Caso a caixa não esteja cheia e os sensores estejam funcionando normalmente:
    bombaLigada = true; // Atualiza o estado informando que a bomba está ligada para encher a caixa
    servoBomba.write(180); // Move o servo motor para 180 graus (posição que representa a bomba LIGADA)
  }
}

// Função para salvar os dados importantes na memória EEPROM periodicamente
// Recebe como parâmetro o tempo atual de execução do Arduino (geralmente a função millis())
void salvarDados(unsigned long tempoAtual) {
  // Verifica se a diferença entre o tempo atual e o tempo do último salvamento é de pelo menos 5000 milissegundos (5 segundos)
  if (tempoAtual - tempoAnteriorSalvar >= 5000) {
     // Utiliza a função put() para gravar os dados atuais na memória não volátil (EEPROM).
    // Assim, se a energia cair, o sistema não perde o volume atual e o consumo registrado.
    EEPROM.put(enderecoConsumoTotal, consumoTotal);
    EEPROM.put(enderecoVolumeAtual, volumeAtual);
    EEPROM.put(enderecoPorcentagem, porcentagem);
      // Atualiza a variável de controle de tempo para iniciar uma nova contagem de 5 segundos
    tempoAnteriorSalvar = tempoAtual;
  }
}
