// RGB strip Mosfets pins
#define RED_PIN 11
#define GREEN_PIN 10
#define BLUE_PIN 9

// button used to change mode
#define BTN_PIN 2
// Leds have 3 mode
#define MENU_SIZE 2
// Used to know the current mode
volatile int posMenu = 0;

// Used to know if btn has been pressed
volatile boolean isBtnDown = false;
// to avoid kickback
#define REBOND 1

// ===============================
//    Interrupt Method
// ===============================

void interruptBtn()
{
  static unsigned long dateLastChange = 0;
  unsigned long date =  millis();

  if ((date - dateLastChange) > REBOND)
  {
    if (++posMenu > MENU_SIZE)
      posMenu = 0;
    isBtnDown = true;
    dateLastChange = date;
  }
}

// ===============================
//    Setup Method
// ===============================

void setup()
{
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_PIN), interruptBtn, LOW);
  pinMode(BTN_PIN, INPUT_PULLUP);
}

// ===============================
//    Loop Method
// ===============================

void loop()
{
  //menu();
  Serial.println("PosMenu : " + posMenu);
  if (isBtnDown)
    isBtnDown = false;

  switch (posMenu)
  {
    case 0 : whiteColor(HIGH);
      break;
    case 1 : whiteColor(LOW);
      breath();
      break;
    case 2 : smoothBlink();
      break;

    default : break;
  }
}

// ===============================
//    Used to switch mode
// ===============================

void menu()
{
  if (!digitalRead(BTN_PIN))
  {
    do {
      delay(50); /*anti rebond*/
    }
    while (!digitalRead(BTN_PIN));

    if (++posMenu > MENU_SIZE)
      posMenu = 0;
  }
}

// ===============================
//    White color mode
// ===============================

void whiteColor(int mode)
{
  digitalWrite(RED_PIN, mode);
  digitalWrite(GREEN_PIN, mode);
  digitalWrite(BLUE_PIN, mode);
}

// ===============================
//    Breath mode
// ===============================

void breath()
{
  positiveLoop(RED_PIN);
  negativeLoop(RED_PIN);

  positiveLoop(GREEN_PIN);
  negativeLoop(GREEN_PIN);

  positiveLoop(BLUE_PIN);
  negativeLoop(BLUE_PIN);

  for (int i = 0; i < 255; i++)
  {
    if (isBtnDown)
      break;

    analogWrite(RED_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }
  for (int i = 255; i >= 0; i--)
  {
    if (isBtnDown)
      break;

    analogWrite(RED_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }

  for (int i = 0; i < 255; i++)
  {
    if (isBtnDown)
      break;

    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }
  for (int i = 255; i >= 0; i--)
  {
    if (isBtnDown)
      break;

    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }

  for (int i = 0; i < 255; i++)
  {
    if (isBtnDown)
      break;

    analogWrite(RED_PIN, i);
    analogWrite(GREEN_PIN, i);
    delay(5);
  }
  for (int i = 255; i >= 0; i--)
  {
    if (isBtnDown)
      break;

    analogWrite(RED_PIN, i);
    analogWrite(GREEN_PIN, i);
    delay(5);
  }

  for (int i = 0; i < 255; i++)
  {
    if (isBtnDown)
      break;

    analogWrite(RED_PIN, i);
    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }
  for (int i = 255; i >= 0; i--)
  {
    if (isBtnDown)
      break;

    analogWrite(RED_PIN, i);
    analogWrite(GREEN_PIN, i);
    analogWrite(BLUE_PIN, i);
    delay(5);
  }
}

// ===============================
//    Smooth color blink mode
// ===============================

void smoothBlink()
{
  positiveLoop(RED_PIN);
  positiveLoop(GREEN_PIN);
  positiveLoop(BLUE_PIN);

  negativeLoop(RED_PIN);
  negativeLoop(BLUE_PIN);
  negativeLoop(GREEN_PIN);
}

// ===============================
//    Increase PWM Value
// ===============================

void positiveLoop(int pin)
{
  for (int i = 0; i <= 255; i++)
  {
    if (isBtnDown)
      break;
    analogWrite(pin, i);
    delay(5);
  }
}

// ===============================
//    Decrease PWM Value
// ===============================

void negativeLoop(int pin)
{
  for (int i = 255; i >= 0; i--)
  {
    if (isBtnDown)
      break;
    analogWrite(pin, i);
    delay(5);
  }
}
