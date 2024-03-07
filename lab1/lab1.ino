#define LED 13

#define SHORT_BLINK_TIME 100  //100 65
#define LONG_BLINK_TIME  300  //300 195

volatile char serialInput;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while(Serial.available())
  {
    serialInput = Serial.read();
    blinkMorse(serialInput);
  }
}

void blink(uint16_t blinkTime) {
  digitalWrite(LED, HIGH);
  delay(blinkTime);
  digitalWrite(LED, LOW);
}

void noBlink(uint16_t blinkTime) {
  digitalWrite(LED, LOW);
  delay(blinkTime);
}

void blinkMorse(char character) {
  switch(character) {
    case 'k':
      blink(LONG_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(SHORT_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(LONG_BLINK_TIME);
      noBlink(LONG_BLINK_TIME);
      break;
    case 'a':
      blink(SHORT_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(LONG_BLINK_TIME);
      noBlink(LONG_BLINK_TIME);
      break;
    case 'r':
      blink(SHORT_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(LONG_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(SHORT_BLINK_TIME);
      noBlink(LONG_BLINK_TIME);
      break;
    case 'o':
      blink(LONG_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(LONG_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(LONG_BLINK_TIME);
      noBlink(LONG_BLINK_TIME);
      break;
    case 'l':
      blink(SHORT_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(LONG_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(SHORT_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(SHORT_BLINK_TIME);
      noBlink(LONG_BLINK_TIME);
      break;
    case '2':
      blink(SHORT_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(SHORT_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(LONG_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(LONG_BLINK_TIME);
      noBlink(SHORT_BLINK_TIME);

      blink(LONG_BLINK_TIME);
      noBlink(LONG_BLINK_TIME);
      break;
  }
}
