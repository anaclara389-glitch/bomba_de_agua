// Função responsável por preparar o Display LCD quando o Arduino é ligado
void setupDisplay() {
  lcd.init();  // Inicializa a comunicação com o display LCD (geralmente via módulo I2C)
  lcd.backlight(); // Liga a luz de fundo do painel para que as letras fiquem visíveis
  // --- MENSAGEM DE BOAS-VINDAS / INICIALIZAÇÃO ---
  lcd.setCursor(0, 0);  // Posiciona o "cursor" na coluna 0, linha 0 (início da primeira linha)
  lcd.print("Inicializando..."); // Escreve o texto na tela
  lcd.setCursor(0, 1); // Muda o cursor para a coluna 0, linha 1 (início da segunda linha)
  lcd.print("Aguarde 5 seg.");
  delay(5000); // Pausa o programa por 5 segundos para que o usuário consiga ler a mensagem
  lcd.clear(); // Limpa a tela inteira para preparar para a exibição dos dados reais
}

// Função responsável por atualizar as informações no display continuamente
// Recebe o "tempoAtual" (millis) para não travar o Arduino com a função delay()
void atualizarDisplay(unsigned long tempoAtual) {
   // Verifica se já se passaram 300 milissegundos desde a última vez que o display foi atualizado.
  // Atualizar a tela rápido demais (a cada ciclo do loop) faria os números "piscarem" ou ficarem ilegíveis.
  if (tempoAtual - tempoAnteriorLCD >= 300) {
    tempoAnteriorLCD = tempoAtual;  // Atualiza a marcação de tempo
    lcd.setCursor(0, 0);  // Volta o cursor para o começo da primeira linha

     // --- VERIFICAÇÃO DE ERROS ---
    if (erroSensores) {
      // Se houver algum erro, a tela avisa qual sensor travou ou desconectou
      lcd.print("ERRO NO SENSOR "); lcd.print(sensorComErro);
    } else {
      // --- EXIBIÇÃO NORMAL DOS DADOS (LINHA 1) ---
      // Mostra o Nível (de 0 a 5)
      lcd.print("N:"); lcd.print(nivel); lcd.print(" ");
       // Formatação da Porcentagem:
      // Adiciona um "0" na frente se for menor que 10 (ex: "09%"). 
      // Isso impede que o texto mude de tamanho e apague caracteres vizinhos.
      if (porcentagem < 10) lcd.print("0");
      lcd.print(porcentagem); lcd.print("%  V:");
       // Formatação do Volume:
      // Mantém sempre 4 dígitos para o volume usando zeros à esquerda (ex: "0050L", "0850L").
      if (volumeAtual < 10) lcd.print("000");
      else if (volumeAtual < 100) lcd.print("00");
      else if (volumeAtual < 1000) lcd.print("0");
      lcd.print((int)volumeAtual); lcd.print("L "); // Converte para inteiro para tirar as casas decimais
    }

     // --- EXIBIÇÃO DE CONSUMO E BOMBA (LINHA 2) ---
    lcd.setCursor(0, 1); // Pula para a segunda linha
    lcd.print("Cons:");
    unsigned long cons = (unsigned long)consumoTotal;  // Converte o consumo para número inteiro
     // Limita a exibição do consumo no display para caber fisicamente na tela
    if (cons > 9999) lcd.print("+9k "); // Se passar de 9999 litros, mostra "+9k"
    else {
       // Formatação do Consumo:
      // Assim como no volume, coloca zeros à esquerda para manter a formatação com 4 dígitos fixos.
      if (cons < 10) lcd.print("000");
      else if (cons < 100) lcd.print("00");
      else if (cons < 1000) lcd.print("0");
      lcd.print(cons);
    }
    lcd.print("L ");
    // --- STATUS DA BOMBA ---
    // Verifica se a variável de controle da bomba está verdadeira (ligada) ou falsa (desligada)
    if (bombaLigada) lcd.print("B:ON ");
    else lcd.print("B:OFF");
  }
}
