#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27, 16, 2);

#define BUZZER 10 // пин подключения зуммера
#define BUTTON 8  // пин подключения кнопки

// динозаврик
byte dino[8] = {
  0b01110, 0b11011, 0b11111, 0b11100, 0b11111, 0b01100, 0b10010, 0b11011
};
// дерево
byte tree[8] = {
  0b00000, 0b00000, 0b00000, 0b11011, 0b11011, 0b11011, 0b01100, 0b01100
};
// камень
byte stone[8] = {
  0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b01110, 0b11111
};
// птица
byte bird[8] = {
  0b00100, 0b00101, 0b01111, 0b11111, 0b10100, 0b00100, 0b00000, 0b00000
};

bool buttonWasUp = true;
bool buttonIsUp;
int level = 1;
int pause = 400;
byte p = 0;

void setup() {
  pinMode (BUZZER, OUTPUT);
  pinMode (BUTTON, INPUT_PULLUP);
  LCD.init();
  LCD.backlight();

  LCD.createChar(0, dino);
  LCD.createChar(1, tree);
  LCD.createChar(2, stone);
  LCD.createChar(3, bird);

  LCD.setCursor(7, 0);
  LCD.print("GO!");
  delay(400);
  tone(BUZZER, 600);
  delay(100);
  noTone(BUZZER);
  LCD.clear();
}

void loop() {
  byte d = 1;
  byte x = 15;
  byte y = 1;

  byte i = random (1, 4);
  if (i == 3) y = 0;
  else y = 1;

  while (x > 0) {
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(level);

    buttonIsUp = digitalRead(BUTTON);
    if (buttonWasUp && !buttonIsUp) {
      delay(10);
      buttonIsUp = digitalRead(BUTTON);
      if (!buttonIsUp) { d = 0; }
      else { d = 1; }
    }
    buttonWasUp = buttonIsUp;
     
    if (p > 3) d = 1;

    LCD.setCursor(4, d);
    LCD.print(char(0));
    LCD.setCursor(x, y);
    tone(BUZZER, 50);
    LCD.print(char(i));
    noTone(10);

    if (x == 4 && y == d) {
      delay(400);
      tone(BUZZER, 50);
      delay(100);
      noTone(BUZZER);
      delay(100);
      tone(BUZZER, 20);
      delay(300);
      noTone(BUZZER);
      LCD.clear();
      delay(200);
      LCD.setCursor(3, 0);
      LCD.print("GAME OVER!");
      delay(600);
      LCD.clear();
      delay(400);
      LCD.setCursor(3, 0);
      LCD.print("GAME OVER!");
      delay(600);
      LCD.clear();
      LCD.setCursor(3, 1);
      LCD.print("LEVEL: ");
      LCD.print(level);
      delay(400);
      LCD.setCursor(3, 0);
      LCD.print("GAME OVER!");
      delay(3000);
      LCD.clear();

      LCD.setCursor(7, 0);
      LCD.print("GO!");
      delay(400);
      tone(BUZZER, 600);
      delay(100);
      noTone(BUZZER);
      LCD.clear();

      level = 0;
      pause = 400;
      p = 0;
      y = 1;
      x = 0;
      break;
    }

    if (d == 0) {
      tone(BUZZER, 200);
      delay(100);
      noTone(BUZZER);
    }
    else {
      delay(100);
    }

    delay(pause);
    x = x - 1;
    p = p + 1;
    if (p > 4) p = 0;
  }

  tone(10, 800);
  delay(20);
  level = level + 1;
  pause = pause - 20;
  if (pause < 0) pause = 0;
}
