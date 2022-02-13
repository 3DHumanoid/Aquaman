#include "Aquaman_BlueTooth_Setup.h"
#include "Display.h"

Display mainDisplay;
long BLEPrevCheck = 0;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
  }

  //pinModeSetup(); //Configure.h function
  pinMode(ONBOARDLED, OUTPUT);
  pinMode(CAMERAFLASH, OUTPUT);
  pinMode(CAMERASHUTTER, OUTPUT);
  pinMode(SOLENOID, OUTPUT);

  pinMode(ENTERBUTTON, INPUT);
  pinMode(UPBUTTON, INPUT);
  pinMode(DOWNBUTTON, INPUT);

  bluetoothSetup(); //Aquaman_BlueTooth_Setup.h function

  mainDisplay.copyRightPg();
  delay(3000);

  if(mainDisplay.getFirstTimeStartUp())
  {
    mainDisplay.instructionPg();
    do
    {
      //Pause until Enter Button is Pressed
    }
    while(!digitalRead(ENTERBUTTON));
    delay(DEBOUNCE); //Debounce after Enter Button Press

    mainDisplay.setFirstTimeStartUp(false);
  }

  mainDisplay.mainPg();
}

void loop() {
 
  bluetoothTestingConnection(); //Aquaman_BlueTooth_Setup.h function
  
  mainDisplay.checkButtonState();
}