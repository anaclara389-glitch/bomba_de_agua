void setupDisplay() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando...");
  lcd.setCursor(0, 1);
  lcd.print("Aguarde 5 seg.");
  delay(5000);
  lcd.clear();
}

void atualizarDisplay(unsigned long tempoAtual) {
  if (tempoAtual - tempoAnteriorLCD >= 300) {
    tempoAnteriorLCD = tempoAtual;
    lcd.setCursor(0, 0);
   
    if (erroSensores) {
      lcd.print("ERRO NO SENSOR "); lcd.print(sensorComErro);
    } else {
      lcd.print("N:"); lcd.print(nivel); lcd.print(" ");
      if (porcentagem < 10) lcd.print("0");
      lcd.print(porcentagem); lcd.print("%  V:");
      if (volumeAtual < 10) lcd.print("000");
      else if (volumeAtual < 100) lcd.print("00");
      else if (volumeAtual < 1000) lcd.print("0");
      lcd.print((int)volumeAtual); lcd.print("L ");
    }

    lcd.setCursor(0, 1);
    lcd.print("Cons:");
    unsigned long cons = (unsigned long)consumoTotal;
    if (cons > 9999) lcd.print("+9k ");
    else {
      if (cons < 10) lcd.print("000");
      else if (cons < 100) lcd.print("00");
      else if (cons < 1000) lcd.print("0");
      lcd.print(cons);
    }
    lcd.print("L ");
   
    if (bombaLigada) lcd.print("B:ON ");
    else lcd.print("B:OFF");
  }
}