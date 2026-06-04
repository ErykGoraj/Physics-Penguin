#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <IRremote.h>

// Dlatego unit8 ponieważ przyjmuje wartość od 0 do 255
struct JoystickConfig
{
  uint8_t xPin;
  uint8_t yPin;
  uint8_t swPin;
};

// Dlatego int16_t bo ma szerokie pasmo wartośći dla int
struct JoystickData
{
  int16_t xVal;
  int16_t yVal;
  bool swVal;
};

struct SendData 
{
  JoystickData left;
  JoystickData right;
  uint8_t irCode;
};

JoystickConfig leftJoystick = {A1, A0, 6};
JoystickConfig rightJoystick = {A3, A2, 5};

// Nie potrzebujemy struct bo posiadamy tylko jeden wyświetlacz
const uint8_t rstPin = 8;
const uint8_t dcPin = 9;
const uint8_t csPin = 10;

Adafruit_ST7789 screen = Adafruit_ST7789(csPin, dcPin, rstPin);

const uint8_t irPin = 7;

SendData sendData;

void displayPenguin()
{
  screen.println(R"raw(
          /~~~~~~\
        /`    -s- ~~~~\
       /`::::     ~~~~
      /`:::::     :
     /` :::::...::::
    /`    `:::::::::::
   /`      `:::::::::
  /`       :::::::::
  :        ::::::::::
  :       :::::::::::
  :       :::::::::::
  :   .    ::::::::::
  :   :.   ::::::::'
  :   ::  .:::::::'
  :   ::..:::::::'
  :    ::::::::'
   :    ::::::::
    :..::......::
  )raw");
}

void readIR()
{
  if (IrReceiver.decode()) {
    uint8_t command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    delay(100);
    IrReceiver.resume();
    sendData.irCode = command;
  }
}

void readJoystick()
{
  sendData.left.xVal = analogRead(leftJoystick.xPin);
  sendData.left.yVal = analogRead(leftJoystick.yPin);
  sendData.right.xVal = analogRead(rightJoystick.xPin);
  sendData.right.yVal = analogRead(rightJoystick.yPin);
  sendData.left.swVal = digitalRead(leftJoystick.swPin);
  sendData.right.swVal = digitalRead(rightJoystick.swPin);
}

void setup() 
{
  Serial.begin(115200);
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);
  pinMode(leftJoystick.swPin, INPUT_PULLUP);
  pinMode(rightJoystick.swPin, INPUT_PULLUP);

  // Mój wyświetlacz ma taką rozdziałke dlatego
  screen.init(240, 240);
  screen.setRotation(2);
  screen.fillScreen(ST77XX_BLACK);
  screen.setCursor(0,0);
  screen.setTextSize(1);
  screen.setTextColor(ST77XX_GREEN);
  displayPenguin();
  screen.setTextSize(2);
  screen.setTextColor(ST77XX_WHITE);
  screen.println("PHYSICS PENGUIN");
  delay(2000);
  screen.fillScreen(ST77XX_BLACK);
}

void loop() 
{
  readIR();
  readJoystick();
}
