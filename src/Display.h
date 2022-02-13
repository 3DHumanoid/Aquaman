#include "Control.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <string.h>
#include "Lato_Heavy_12.h"
#include "Lato_Black_12.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

class Display: public OLEDControl
{
    private:
        String title;
        String line1_1;
        String line1_2;
        String line2_1;
        String line2_2;
        String line3_1;
        String line3_2;
        String val1_1;
        String val1_2;
        String val2_1;
        String val2_2;
        String val3_1;
        String val3_2;

        int enterButtonState;
        int upButtonState;
        int downButtonState;

        bool value1SelectActive;
        bool value2SelectActive;
        bool lineSelectActive;

        int value1SelectValue;
        int value2SelectValue;
        int lineSelectValue;

        int modeActive;

        bool camModeSelActive;
        bool numPicsActive;
        bool camDelayActive;
        bool numDropsActive;
        bool dropDelaySelActive;
        bool dropDelayActive;
        bool dropSizeSelActive;
        bool dropSizeActive;

        int camModeSelValue;
        int numPicsValue;
        int camDelayValue;
        int numDropsValue;
        int dropDelaySelValue;
        int dropDelayValue;
        int dropSizeSelValue;
        int dropSizeValue;

        int valueActive;

    public:

        Display();
        ~Display();

        void checkButtonState(); 

        void controlTest();
        int upControl();
        int downControl();
        int enterControl();

        void lineControl();
        void pgControl();
        void valControl();

        void valueInit();
        void modeInit();

        /***Pages***/
        void pgInit();
        void copyRightPg();
        void mainPg();
        void waterDropPg();
        void cameraPg();
        void startPg();
        void infoPg();
        void instructionPg(); 

        void checkValueActive(int valueActive);
        void checkModeActive(int modeActive);
    
};

Display::Display()
{
    title = "Title";
    line1_1 = "Line 1_1";
    line1_2 = "Line 1_2";
    line2_1 = "Line 2_1";
    line2_2 = "Line 2_2";
    line3_1 = "Line 3_1";
    line3_2 = "Line 3_2";

    val1_1 = "val1_1";
    val1_2 = "val1_2";
    val2_1 = "val2_1";
    val2_2 = "val2_2";
    val3_1 = "val3_1";
    val3_2 = "val3_2";

    value1SelectActive = false;
    value2SelectActive = false;
    lineSelectActive = true;

    value1SelectValue = 1;
    value2SelectValue = 2;
    lineSelectValue = 3;

    camModeSelActive = false;
    numPicsActive = false;
    camDelayActive = false;
    numDropsActive = false;
    dropDelaySelActive = false;
    dropDelayActive = false;
    dropSizeSelActive = false;
    dropSizeActive = false;

    camModeSelValue = 1;
    numPicsValue = 2;
    camDelayValue = 3;
    numDropsValue = 4;
    dropDelaySelValue = 5;
    dropDelayValue = 6;
    dropSizeSelValue = 7;
    dropSizeValue = 8;

    enterButtonState = 0;
    upButtonState = 0;
    downButtonState = 0;

    
}

Display::~Display()
{

}

void Display::checkButtonState()
{
    this->enterButtonState = digitalRead(ENTERBUTTON);
    this->upButtonState = digitalRead(UPBUTTON);
    this->downButtonState = digitalRead(DOWNBUTTON);

    if(enterButtonState)
    {
        Serial.println("Enter Press");
        enterControl();    
    }
    else if(upButtonState)
    {
        Serial.println("Up Press");
        upControl();   
    }
    else if(downButtonState)
    {
        Serial.println("Down Press");
        downControl();
    }
    delay(DEBOUNCE);
}

void Display::controlTest()
{
   
}

int Display::upControl()
{
    if(lineSelectActive)
    {
        setLineNum(getLineNum() - 1);
        lineControl();
    }
    else if(value1SelectActive)
    {
        switch(getPgNum())
        {
            case 2: //water drop pg
                switch(getLineNum())
                {
                    case 1:
                        setNumOfDrops(getNumOfDrops() + 1);
                        break;

                    case 2:
                        setDropSizeSel(getDropSizeSel() + 1);
                        break;

                    case 3:
                        setDropDelaySel(getDropDelaySel() + 1);
                        break;
                }
            case 3: //camera pg
                switch(getLineNum())
                {
                    case 1:
                        setCameraModeSel(getCameraModeSel() + 1);
                        break;

                    case 2:
                        setCameraDelay(getCameraDelay() + CAMERADELAYMULTIPLE);
                        break;

                    case 3:
                        setNumOfPics(getNumOfPics() + 1);
                        break;
                }
        }
    }
    else if(value2SelectActive)
    {
        switch(getPgNum())
        {
            case 2: //water drop pg
                switch(getLineNum())
                {
                    case 2:
                        drop[getDropSizeSel()].dropSize = drop[getDropSizeSel()].dropSize + DROPSIZEMULTIPLE;
                        break;

                    case 3:
                        drop[getDropDelaySel()].dropDelay = drop[getDropDelaySel()].dropDelay + DROPDELAYMULTIPLE;
                        break;
                }
        }
    }
    return 0;
}

int Display::downControl()
{
    if(lineSelectActive)
    {
        setLineNum(getLineNum() + 1);
        lineControl();
    }
    else if(value1SelectActive)
    {
        switch(getPgNum())
        {
            case 2: //water drop pg
                switch(getLineNum())
                {
                    case 1:
                        setNumOfDrops(getNumOfDrops() - 1);
                        break;

                    case 2:
                        setDropSizeSel(getDropSizeSel() - 1);
                        break;

                    case 3:
                        setDropDelaySel(getDropDelaySel() - 1);
                        break;
                }
            case 3: //camera pg
                switch(getLineNum())
                {
                    case 1:
                        setCameraModeSel(getCameraModeSel() - 1);
                        break;

                    case 2:
                        setCameraDelay(getCameraDelay() - CAMERADELAYMULTIPLE);
                        break;

                    case 3:
                        setNumOfPics(getNumOfPics() - 1);
                        break;
                }
        }
    }
    else if(value2SelectActive)
    {
        switch(getPgNum())
        {
            case 2: //water drop pg
                switch(getLineNum())
                {
                    case 2:
                        drop[getDropSizeSel()].dropSize = drop[getDropSizeSel()].dropSize - DROPSIZEMULTIPLE;
                        break;

                    case 3:
                        drop[getDropDelaySel()].dropDelay = drop[getDropDelaySel()].dropDelay - DROPDELAYMULTIPLE;
                        break;
                }
        }
    }
    return 0;
}

int Display::enterControl()
{
    /***Enter button Held***/
    long enterHeld = 0;
    long enterPressed = 0;

    enterPressed = millis();
    while(digitalRead(ENTERBUTTON))
    {
        enterHeld = millis();

        //If enter Button is held for more than 3 seconds
        if((enterHeld - enterPressed > 3000) && getPgNum() != MAINPGNUM)
        {
            Serial.println("Enter Button Held");
            checkModeActive(lineSelectValue);
            mainPg();
            do{
                //Pause until enter button is realeased
            } while (digitalRead(ENTERBUTTON));   
            delay(DEBOUNCE);    
            return 0;
        }
    }
    /**********************/

    /***MAIN PAGE***/
    if(getPgNum() == MAINPGNUM)
    {
        switch(getLineNum())
        {
            case 1:
                cameraPg();
                break;
            case 2:
                waterDropPg();
                break;
            case 3:
                startPg();
                break;
            default:
                mainPg();
                break;
        }
        return 0;
    }    
    /***CAMERA PAGE***/
    else if(getPgNum() == CAMERAPGNUM)
    {
        switch(getLineNum())
        {
            case 1:
                if(lineSelectActive)
                {
                    checkModeActive(value1SelectValue);
                    checkValueActive(camModeSelValue);
                    lineControl();
                }
                else if(value1SelectActive)
                {
                    checkModeActive(lineSelectValue);
                    checkValueActive(0); //Reset Values
                    lineControl();
                }
                break;
            case 2:
                if(lineSelectActive)
                {
                    checkModeActive(value1SelectValue);
                    checkValueActive(camDelayValue);
                    lineControl();
                }
                else if(value1SelectActive)
                {
                    checkModeActive(lineSelectValue);
                    checkValueActive(0); //Reset Values
                    lineControl();
                }
                break;
            case 3:
                if(lineSelectActive)
                {
                    checkModeActive(value1SelectValue);
                    checkValueActive(numPicsValue);
                    lineControl();

                }
                else if(value1SelectActive)
                {
                    checkModeActive(lineSelectValue);
                    checkValueActive(0); //Reset Values
                    lineControl();
                }
                break;
        }
    }
    /***DROP PAGE***/
    else if(getPgNum() == WATERDROPPGNUM)
    {
        switch(getLineNum())
        {
            case 1:
                if(lineSelectActive)
                {
                    value1SelectActive = true;
                    numDropsActive = true;
                    checkModeActive(value1SelectValue);
                    checkValueActive(numDropsValue);
                    lineControl();
                }
                else if(value1SelectActive)
                {
                    lineSelectActive = true;
                    numDropsActive = false;
                    checkModeActive(lineSelectValue);
                    checkValueActive(0); //Reset Values
                    lineControl();
                }
                break;
            case 2:
                if(lineSelectActive)
                {
                    value1SelectActive = true;
                    dropSizeSelActive = true;
                    checkModeActive(value1SelectValue);
                    checkValueActive(dropSizeSelValue);
                    lineControl();
                }
                else if(value1SelectActive)
                {
                    value2SelectActive = true;
                    dropSizeActive = true;
                    checkModeActive(value2SelectValue);
                    checkValueActive(dropSizeValue);
                    lineControl();
                }
                else if(value2SelectActive)
                {
                    lineSelectActive = true;
                    dropSizeActive = false;
                    checkModeActive(lineSelectValue);
                    checkValueActive(0); //Reset Values
                    lineControl();
                }
                break;
            case 3:
                if(lineSelectActive)
                {
                    value1SelectActive = true;
                    dropDelaySelActive = true;
                    checkModeActive(value1SelectValue);
                    checkValueActive(dropDelaySelValue);
                    lineControl();

                }
                else if(value1SelectActive)
                {
                    value2SelectActive = true;
                    dropDelayActive = true;
                    checkModeActive(value2SelectValue);
                    checkValueActive(dropDelayValue);
                    lineControl();
                }
                else if(value2SelectActive)
                {
                    lineSelectActive = true;
                    dropDelayActive = false;
                    checkModeActive(lineSelectValue);
                    checkValueActive(0); //Reset Values
                    lineControl();
                }
                break;
        }
    }
    
    return 0;
}

void Display::pgControl()
{
    switch(getPgNum())
    {
        case 0:
            copyRightPg();
            break;
        case 1:
            mainPg();
            break;
        case 2:
            waterDropPg();
            break;
        case 3:
            cameraPg();
            break;
        case 4:
            startPg();
            break;
        case 5:
            infoPg();
            break;
        case 6:
            instructionPg();
            break;
        default:
            mainPg();
            break; 
    }
}

void Display::lineControl()
{
    if(lineSelectActive)
    {
        switch(getLineNum())
            {
                case 1:
                    display.drawFastHLine(0, 27, SCREEN_WIDTH, BLACK); //Line 1
                    display.drawFastHLine(0, 42, SCREEN_WIDTH, BLACK); //Line 2
                    display.drawFastHLine(0, 57, SCREEN_WIDTH, BLACK); //Line 3
                    display.drawFastHLine(0, 27, line1_1.length() * 6, WHITE); //Val 1_1
                    break;
                case 2:
                    display.drawFastHLine(0, 27, SCREEN_WIDTH, BLACK); //Line 1
                    display.drawFastHLine(0, 42, SCREEN_WIDTH, BLACK); //Line 2
                    display.drawFastHLine(0, 57, SCREEN_WIDTH, BLACK); //Line 3
                    display.drawFastHLine(0, 42, line2_1.length() * 6, WHITE); //Line 2
                    break;
                case 3:
                    display.drawFastHLine(0, 27, SCREEN_WIDTH, BLACK); //Line 1
                    display.drawFastHLine(0, 42, SCREEN_WIDTH, BLACK); //Line 2
                    display.drawFastHLine(0, 57, SCREEN_WIDTH, BLACK); //Line 3
                    display.drawFastHLine(0, 57, line3_1.length() * 6, WHITE); //Line 3
                    break;
            }
            
    }
    else if(!lineSelectActive)
    {
        switch(getLineNum())
        {
                case 1:
                    display.drawFastHLine(0, 27, SCREEN_WIDTH, BLACK); //Line 1
                    display.drawFastHLine(0, 42, SCREEN_WIDTH, BLACK); //Line 2
                    display.drawFastHLine(0, 57, SCREEN_WIDTH, BLACK); //Line 3
                    if(value1SelectActive)
                    {
                        display.drawFastHLine(line1_1.length() * 6, 27, val1_1.length(), WHITE); //Val 1_1
                    }
                    else if(value2SelectActive)
                    {
                        display.drawFastHLine(0, 27, SCREEN_WIDTH, BLACK); //Val 1_1
                        display.drawFastHLine(line1_1.length() * 6 + line1_2.length() + val1_1.length(), 27, val1_1.length(), WHITE); //Val 1_2
                    }
                    break;
                case 2:
                    display.drawFastHLine(0, 27, line1_1.length() * 6, BLACK); //Line 1
                    display.drawFastHLine(0, 42, line2_1.length() * 6, BLACK); //Line 2
                    display.drawFastHLine(0, 57, line3_1.length() * 6, BLACK); //Line 3
                    if(value1SelectActive)
                    {
                        display.drawFastHLine(line2_1.length() * 6, 27, val2_1.length() * 6, WHITE); //Val 2_1
                    }
                    else if(value2SelectActive)
                    {
                        display.drawFastHLine(line2_1.length() * 6, 27, val2_1.length() * 6, BLACK); //Val 2_1
                        display.drawFastHLine(line2_1.length() * 6 + line2_2.length() + val2_1.length(), 27, val2_2.length() * 6, WHITE); //Val 2_2
                    }
                    break;
                case 3:
                    display.drawFastHLine(0, 27, line1_1.length() * 6, BLACK); //Line 1
                    display.drawFastHLine(0, 42, line2_1.length() * 6, BLACK); //Line 2
                    display.drawFastHLine(0, 57, line3_1.length() * 6, BLACK); //Line 3
                    if(value1SelectActive)
                    {
                        display.drawFastHLine(line3_1.length() * 6, 27, val3_1.length() * 6, WHITE); //Val 3_1
                    }
                    else if(value2SelectActive)
                    {
                        display.drawFastHLine(line3_1.length() * 6, 27, val3_1.length() * 6, BLACK); //Val 3_1
                        display.drawFastHLine(line3_1.length() * 6 + line3_2.length() + val3_1.length(), 27, val3_2.length() * 6, WHITE); //Val 3_2
                    }
                    break;   
        }
    }
    display.display();

}

void Display::checkModeActive(int modeActive)
{
    switch(modeActive)
    {
        case 1:
            modeInit();
            this->lineSelectActive = true;
            break;
        case 2:
            modeInit();
            this->value1SelectActive = true;
            break;
        case 3:
            modeInit();
            this->value2SelectActive = true;
            break;
    }
}

void Display::checkValueActive(int valueActive)
{

    switch(valueActive)
    {
        case 0:
            valueInit();
            break;
        case 1:
            valueInit();
            this->camModeSelActive = true;
            break;
        case 2:
            valueInit();
            this->numPicsActive = true;
            
            break;
        case 3:
            valueInit();
            this->camDelayActive = true;
            break;
        case 4:
            valueInit();
            this->numDropsActive = true;
            break;
        case 5:
            valueInit();
            this->dropDelaySelActive = true;
            break;
        case 6:
            valueInit();
            this->dropDelayActive = true;
            break;
        case 7:
            valueInit();
            this->dropSizeSelActive = true;
            break;
        case 8:
            valueInit();
            this->dropSizeActive = true;
            break;
    }
}

void Display::modeInit()
{
    this->lineSelectActive = false;
    this->value1SelectActive = false;
    this->value2SelectActive = false;
}

void Display::valueInit()
{
    this->camModeSelActive = false;
    this->numPicsActive = false;
    this->camDelayActive = false;
    this->numDropsActive = false;
    this->dropDelaySelActive = false;
    this->dropDelayActive = false;
    this->dropSizeSelActive = false;
    this->dropSizeActive = false;
}

/***Pages***/
void Display::pgInit()
{
    display.setFont(&Lato_Black_12);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.clearDisplay();
    setLineNum(1); //Set Line to top when new page.
    lineControl();
}

void Display::instructionPg()
{
    setPgNum(INSTRUCTIONPGNUM);
    display.setFont(&Lato_Black_12);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.setCursor(0,10);
    display.println("Instructions:");
    display.setCursor(0,26);
    display.setFont(&Lato_Heavy_12);
    display.println("1.Enter to select");
    display.println("2.Hold Enter");
    display.println("  to Return");
    display.display();
}

void Display::copyRightPg()
{
    setPgNum(COPYRIGHTPGNUM);
    display.setFont(&Lato_Black_12);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.clearDisplay();
    display.setCursor(10, 10);
    display.println("Aquaman Drop");
    display.setCursor(0,26);
    display.setFont(&Lato_Heavy_12);
    display.println("  Copyright 2020  ");
    display.println("    Brian Allen   ");
    display.println("All rights reserved");
    display.display();
}

void Display::mainPg()
{
    value1SelectActive = false;
    value2SelectActive = false;
    lineSelectActive = true;

    setPgNum(MAINPGNUM);
    this->title = "Main Page:";
    this->line1_1 = "Camera Page: ";
    this->line2_1 = "Drop Page";
    this->line3_1 = "*Start*";
    this->val1_1 = String(cameraDelayMode[getCameraModeSel()]);
    pgInit();

    display.setCursor(0,10);
    //Title
    display.println(this->title);
    display.setCursor(0,26);
    display.setFont(&Lato_Heavy_12);
    //Line 1
    display.print(line1_1);
    display.println(val1_1);
    //Line 2
    display.println(line2_1);
    //Line 3
    display.println(line3_1);
    display.display();
}


void Display::waterDropPg()
{
    setPgNum(WATERDROPPGNUM);
    this->title = "Drop Page:";
    this->line1_1 = "Drop Num: ";
    this->line2_1 = "Drop: ";
    this->line2_2 = " Size: ";
    this->line3_1 = "Drop: ";
    this->line3_2 = " Delay: ";
    this->val1_1 = String(getNumOfDrops());
    this->val2_1 = String(getDropSizeSel() + 1);
    this->val2_2 = String(drop[getDropSizeSel()].dropSize);
    this->val3_1 = String(getDropDelaySel() + 1);
    this->val3_2 = String(drop[getDropDelaySel()].dropDelay);
    pgInit();

    display.setCursor(0,10);
    //Title
    display.println(title); 
    display.setCursor(0,26);
    display.setFont(&Lato_Heavy_12);
    //Line 1
    display.print(line1_1);
    display.println(val1_1);
    //Line 2
    display.print(line2_1);
    display.print(val2_1);
    display.print(line2_2);
    display.println(val2_2);
    //Line 3
    display.print(line3_1);
    display.print(val3_1);
    display.print(line3_2);
    display.println(val3_2);
    display.display();
}

void Display::cameraPg()
{
    setPgNum(CAMERAPGNUM);
    this->title = "Camera Page:";
    this->line1_1 = "Camera Mode: ";
    this->line2_1 = "Camera Delay: ";
    this->line3_1 = "Number of Pics: ";
    this->val1_1 = String(cameraDelayMode[getCameraModeSel()]);
    this->val2_1 = String(getCameraDelay());
    this->val3_1 = String(getNumOfPics());
    pgInit();

    display.setCursor(0,10);
    //Title
    display.println(title); 
    display.setCursor(0,26);
    display.setFont(&Lato_Heavy_12);
    //Line 1
    display.print(line1_1);
    display.println(val1_1);
    //Line 2
    display.print(line2_1);
    display.println(val2_1);
    //Line 3
    display.print(line3_1);
    display.println(val3_1);
    display.display();
}

void Display::startPg()
{
    setPgNum(STARTPGNUM);
    this->title = "Start PICS...";
    this->line1_1 = "Num of Drops: ";
    this->line2_1 = "Pics Taken: ";
    this->line3_1 = "*Hold Enter to Exit";
    this->val1_1 = String(getNumOfDrops());
    this->val2_1 = String(getPicTaken());
    pgInit();

    display.setCursor(0,10);
    //Title
    display.println(title); 
    display.setCursor(0,26);
    display.setFont(&Lato_Heavy_12);
    //Line 1
    display.print(line1_1); 
    display.println(val1_1);
    //Line 2
    display.print(line2_1); 
    display.println(val2_1);
    display.display();
//Instructions
}

void Display::infoPg()
{
    setPgNum(INFOPGNUM);
    display.setFont(&Lato_Black_12);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.clearDisplay();   
}