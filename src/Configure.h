#include <SPI.h>
#include <Wire.h>
#include <iostream>
#include <string>
#include <Adafruit_I2CDevice.h>
#include <Arduino.h>

/*********************/
/***PIN DEFFINTIONS***/
/*********************/
#define ONBOARDLED 2
#define ENTERBUTTON 16
#define UPBUTTON 17
#define DOWNBUTTON 15

#define CAMERASHUTTER 2
#define CAMERAFLASH 4
#define SOLENOID 3

/********************/
/*****MAX VALUES*****/
/********************/
#define MAXNUMOFPICS 20
#define MAXCAMERADELAY 995
#define MAXNUMOFDROPS 9
#define MAXPAGENUM 4
#define MAXLINENUM 3

/********************/
/*****MIN VALUES*****/
/********************/
#define MINPICNUMBER 1
#define MINNUMOFPICS 0
#define MINNUMOFDROPS 1
#define MINCAMERADELAY 200
#define MINPAGENUM 1
#define MINLINENUM 1

/**********************/
/*****PAGE NUMBERS*****/
/**********************/
#define COPYRIGHTPGNUM 0
#define MAINPGNUM 1
#define WATERDROPPGNUM 2
#define CAMERAPGNUM 3
#define STARTPGNUM 4
#define INFOPGNUM 5
#define INSTRUCTIONPGNUM 6

/**********************/
/*****OTHER VALUES*****/
/**********************/
#define DEBOUNCE 150
#define NUMBUTTONS 3 

#define CAMERADELAYMULTIPLE 5
#define DROPDELAYMULTIPLE 5
#define DROPSIZEMULTIPLE 5 

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

/*************************/
/*****SETUP FUNCTIONS*****/
/*************************/
/*void pinModeSetup() {
    pinMode(ONBOARDLED, OUTPUT);
    pinMode(CAMERAFLASH, OUTPUT);
    pinMode(CAMERASHUTTER, OUTPUT);
    pinMode(SOLENOID, OUTPUT);

    pinMode(ENTERBUTTON, INPUT);
    pinMode(UPBUTTON, INPUT);
    pinMode(DOWNBUTTON, INPUT);
}*/