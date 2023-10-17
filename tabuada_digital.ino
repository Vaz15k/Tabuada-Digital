#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd1(0x3f, 16, 2);  // Endereço 0x3F, 16 colunas, 2 linhas (Limpo) (Pergunta)
LiquidCrystal_I2C lcd2(0x22, 16, 2);  // Endereço 0x22, 16 colunas, 2 linhas (A0 e A2) (Resposta 1 | botao 6)
LiquidCrystal_I2C lcd3(0x26, 16, 2);  // Endereço 0x26, 16 colunas, 2 linhas (A0) (Respota 2 | botao 7)
LiquidCrystal_I2C lcd4(0x27, 16, 2);  // Endereço 0x27, 16 colunas, 2 linhas (lcd amarelo) (Resposta 3 | botao 8)

const int buttonPin1 = 6;  // Botão 1
const int buttonPin2 = 7;  // Botão 2
const int buttonPin3 = 8;  // Botão 3

int rCorreta;  // Armazena a resposta correta

void setup() {
  lcd1.init();  // Inicialize o Display 1
  lcd2.init();  // Inicialize o Display 2
  lcd3.init();  // Inicialize o Display 3
  lcd4.init();  // Inicialize o Display 4

  lcd1.backlight();
  lcd2.backlight();
  lcd3.backlight();
  lcd4.backlight();

  lcd1.setCursor(0, 0);
  lcd2.setCursor(0, 0);
  lcd3.setCursor(0, 0);
  lcd4.setCursor(0, 0);

  lcd1.print("LCD 1 OK");
  delay (500);
  lcd2.print("LCD 2 OK");
  delay (500);
  lcd3.print("LCD 3 OK");
  delay (500);
  lcd4.print("LCD 4 OK");
  delay (2000);

  pinMode(buttonPin1, INPUT_PULLUP);  // Configura o Botão 1
  pinMode(buttonPin2, INPUT_PULLUP);  // Configura o Botão 2
  pinMode(buttonPin3, INPUT_PULLUP);  // Configura o Botão 3

  randomSeed(analogRead(0));  // Inicializa o gerador de números aleatórios

  geraQuestao();  // Gera a primeira pergunta
}

void loop() {
  int b1Stado = digitalRead(buttonPin1);
  int b2Stado = digitalRead(buttonPin2);
  int b3Stado = digitalRead(buttonPin3);

  if (b1Stado == LOW || b2Stado == LOW || b3Stado == LOW) {
    if (b1Stado == LOW && rCorreta == 1) {
      displayResult(true);
    } else if (b2Stado == LOW && rCorreta == 2) {
      displayResult(true);
    } else if (b3Stado == LOW && rCorreta == 3) {
      displayResult(true);
    } else {
      displayResult(false);
    }
    delay(2000);  // Aguarda 2 segundos antes de gerar a próxima pergunta
    geraQuestao();
  }
}

// Gera a pergunta e as respostas
void geraQuestao() {
  int num1 = random(10);
  int num2 = random(10);
  rCorreta = random(1, 4);

  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("Pergunta:");
  lcd1.setCursor(0, 1);
  lcd1.print(num1);
  lcd1.setCursor(5, 1);
  lcd1.print("x");
  lcd1.setCursor(8, 1);
  lcd1.print(num2);

  int result = num1 * num2;
  int rErrado1, rErrado2;

  // Gera valores aleatórios para as respostas erradas
  do {
    rErrado1 = random(0, 100);
  } while (rErrado1 == result);

  do {
    rErrado2 = random(0, 100);
  } while (rErrado2 == result || rErrado2 == rErrado1);

  // Exibe as respostas
  switch (rCorreta) {
    case 1:
      lcd2.clear();
      lcd2.setCursor(0, 0);
      lcd2.print("Resposta 1:");
      lcd2.setCursor(0, 1);
      lcd2.print(result);

      lcd3.clear();
      lcd3.setCursor(0, 0);
      lcd3.print("Resposta 2:");
      lcd3.setCursor(0, 1);
      lcd3.print(rErrado1);

      lcd4.clear();
      lcd4.setCursor(0, 0);
      lcd4.print("Resposta 3:");
      lcd4.setCursor(0, 1);
      lcd4.print(rErrado2);
      break;

    case 2:
      lcd2.clear();
      lcd2.setCursor(0, 0);
      lcd2.print("Resposta 1:");
      lcd2.setCursor(0, 1);
      lcd2.print(rErrado1);

      lcd3.clear();
      lcd3.setCursor(0, 0);
      lcd3.print("Resposta 2:");
      lcd3.setCursor(0, 1);
      lcd3.print(result);

      lcd4.clear();
      lcd4.setCursor(0, 0);
      lcd4.print("Resposta 3:");
      lcd4.setCursor(0, 1);
      lcd4.print(rErrado2);
      break;

    case 3:
      lcd2.clear();
      lcd2.setCursor(0, 0);
      lcd2.print("Resposta 1:");
      lcd2.setCursor(0, 1);
      lcd2.print(rErrado2);

      lcd3.clear();
      lcd3.setCursor(0, 0);
      lcd3.print("Resposta 2:");
      lcd3.setCursor(0, 1);
      lcd3.print(rErrado1);

      lcd4.clear();
      lcd4.setCursor(0, 0);
      lcd4.print("Resposta 3:");
      lcd4.setCursor(0, 1);
      lcd4.print(result);
      break;
  }
}

// Exibe o resultado da pergunta
void displayResult(bool isCorrect) {
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd1.print("Resposta:");

  if (isCorrect) {
    lcd1.setCursor(0, 1);
    lcd1.print("CORRETA!");
  } else {
    lcd1.setCursor(0, 1);
    lcd1.print("ERRADA!");
  }

  lcd2.clear();
  lcd3.clear();
  lcd4.clear();
}
