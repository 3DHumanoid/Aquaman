#include <Configure.h>

struct Drop
{
  int dropSize = 0;
  int dropDelay = 0;
};

class OLEDControl
{
    private:
        bool firstTimeStartUp;

        int lineNum;
        int pgNum;

        int camModeSel;
        int numPics;
        int camDelay;

        int numDrops;
        int dropDelaySel;
        int dropSizeSel;

        int picsTaken;

    public:
        String cameraDelayMode[2] {"Auto", "Cust"};
        Drop* drop;

        OLEDControl();
        ~OLEDControl();

        //***Getters***//
        bool getFirstTimeStartUp() {return firstTimeStartUp;}
        int getCameraModeSel() {return camModeSel;}
        int getNumOfPics() {return numPics;}
        int getPicTaken() {return picsTaken;}
        int getCameraDelay() {return camDelay;}
        int getNumOfDrops() {return numDrops;}
        int getDropDelaySel() {return dropDelaySel;}
        int getDropSizeSel() {return dropSizeSel;}
        int getPgNum() {return pgNum;}
        int getLineNum() {return lineNum;}
        //************//

        //***Setters***//
        void setFirstTimeStartUp(bool firstTimeStartUp);
        void setCameraModeSel(int cameraModeSel);
        void setNumOfPics(int numOfPics);
        void setPicTaken(int picsTaken);
        void setCameraDelay(int cameraDelay);
        void setNumOfDrops(int numDrops);
        void setDropDelaySel(int dropDelaySel);
        void setDropSizeSel(int dropSizeSel);
        void setPgNum(int pgNum);
        void setLineNum(int lineNum);
        //*************//
};

OLEDControl::OLEDControl()
{
    firstTimeStartUp = true;

    lineNum = 1;
  
    //Camera Pg
    camModeSel = 1;
    camDelay = 200;
    numPics = 10;

    //Drop Pg
    numDrops = 1;
    drop = new Drop[MAXNUMOFDROPS];
    dropDelaySel = 0;
    dropSizeSel = 0;

    //Initialize all drops
    for(int i = 0; i < MAXNUMOFDROPS; i++)
    {
      drop[i].dropSize = 100;
      drop[i].dropDelay = 500;
    }
        
    //Start Pg
    picsTaken = 0;
}

OLEDControl::~OLEDControl()
{
  drop = NULL;
  delete drop;
}

//***Setters***//
void OLEDControl::setFirstTimeStartUp(bool firstTimeStartUp)
{
  this->firstTimeStartUp = firstTimeStartUp;
}

void OLEDControl::setCameraModeSel(int camModeSel)
{
  this->camModeSel = camModeSel;
}

void OLEDControl::setNumOfPics(int numOfPics)
{
  if (numOfPics < MINNUMOFPICS)
  {
    this->numPics = MAXNUMOFPICS;
  }
  if (numOfPics > MAXNUMOFPICS)
  {
    this->numPics = MINNUMOFPICS;
  }
}

void OLEDControl::setPicTaken(int picsTaken)
{
  if (picsTaken > this->numPics)
  {
    this->picsTaken = 0;
  }
}

void OLEDControl::setCameraDelay(int cameraDelay)
{
  if (cameraDelay < MINCAMERADELAY)
  {
    this->camDelay = MAXCAMERADELAY;
  }
  if (cameraDelay < MAXCAMERADELAY)
  {
    this->camDelay = MINCAMERADELAY;
  }
}

void OLEDControl::setNumOfDrops(int numDrops)
{
  if (numDrops < MINNUMOFDROPS)
  {
    this->numDrops = MAXNUMOFDROPS;
  }
  if (numDrops > MAXNUMOFDROPS)
  {
    this->numDrops = MINNUMOFDROPS;
  }
}

  void OLEDControl::setDropDelaySel(int dropDelaySel)
{
  if (dropDelaySel < MINNUMOFDROPS)
  {
    this->dropDelaySel = numDrops;
  }
  if (dropDelaySel > numDrops)
  {
    this->dropDelaySel = MINNUMOFDROPS;
  }
}

  void OLEDControl::setDropSizeSel(int dropSizeSel)
{
  if (dropSizeSel < MINNUMOFDROPS)
  {
    this->dropSizeSel = numDrops;
  }
  if (dropSizeSel > numDrops)
  {
    this->dropSizeSel = MINNUMOFDROPS;
  }
}

void OLEDControl::setLineNum(int lineNum)
{
    this->lineNum = lineNum;

    if (lineNum < MINLINENUM)
    {
        this->lineNum = MAXLINENUM;
    }
    if (lineNum > MAXLINENUM)
    {
        this->lineNum = MINLINENUM;
    }

    Serial.print("Line Num: ");
    Serial.println(getLineNum());
}

void OLEDControl::setPgNum(int pgNum)
{
    this->pgNum = pgNum;

    if (pgNum < MINPAGENUM)
    {
        this->pgNum = MAXPAGENUM;
    }
    if (pgNum > MAXPAGENUM)
    {
        this->pgNum = MINPAGENUM;
    }

    Serial.print("Pg Num: ");
    Serial.println(getPgNum());
}