#include <PS3BT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

//bibliotecas para motores
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside

BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
//PS3BT PS3(&Btd); // This will just create the instance
PS3BT PS3(&Btd, 0x00, 0x15, 0x83, 0x3D, 0x0A, 0x57); // This will also store the bluetooth address - this can be obtained from the dongle when running the sketch

bool printTemperature, printAngle;

//#################################################################

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  540 // this is the 'maximum' pulse length count (out of 4096)

#define abertura 12

#define perna1_coxa 0
#define perna1_femur 1
#define perna1_tibia 2

#define perna2_coxa 4
#define perna2_femur 5
#define perna2_tibia 6
                    
#define perna3_coxa 8
#define perna3_femur 9
#define perna3_tibia 10

#define perna4_coxa 0
#define perna4_femur 1
#define perna4_tibia 2
                    
#define perna5_coxa 4
#define perna5_femur 5
#define perna5_tibia 6
                    
#define perna6_coxa 8
#define perna6_femur 9
#define perna6_tibia 10 

//----------------------------------------------------------

int triangulo = 0;
int quadrado = 0;
int cruza = 0;
int bolinha = 0;

int tempo = 200;

//-------------Posicoes dos servos -------------------------

int ge_0 = map(0, 0, 180, SERVOMIN, SERVOMAX);       int gd_0 = map(0, 180, 0, SERVOMIN, SERVOMAX); 
int ge_10 = map(10, 0, 180, SERVOMIN, SERVOMAX);     int gd_10 = map(10, 180, 0, SERVOMIN, SERVOMAX);
int ge_20 = map(20, 0, 180, SERVOMIN, SERVOMAX);     int gd_20 = map(20, 180, 0, SERVOMIN, SERVOMAX);
int ge_30 = map(30, 0, 180, SERVOMIN, SERVOMAX);     int gd_30 = map(30, 180, 0, SERVOMIN, SERVOMAX);
int ge_45 = map(45, 0, 180, SERVOMIN, SERVOMAX);     int gd_45 = map(45, 180, 0, SERVOMIN, SERVOMAX);
int ge_50 = map(50, 0, 180, SERVOMIN, SERVOMAX);     int gd_50 = map(50, 180, 0, SERVOMIN, SERVOMAX);
int ge_60 = map(60, 0, 180, SERVOMIN, SERVOMAX);     int gd_60 = map(60, 180, 0, SERVOMIN, SERVOMAX);
int ge_70 = map(70, 0, 180, SERVOMIN, SERVOMAX);     int gd_70 = map(70, 180, 0, SERVOMIN, SERVOMAX);
int ge_75 = map(75, 0, 180, SERVOMIN, SERVOMAX);     int gd_75 = map(75, 180, 0, SERVOMIN, SERVOMAX);
int ge_90 = map(85, 0, 180, SERVOMIN, SERVOMAX);     int gd_90 = map(85, 180, 0, SERVOMIN, SERVOMAX);
int ge_105 = map(105, 0, 180, SERVOMIN, SERVOMAX);   int gd_105 = map(105, 180, 0, SERVOMIN, SERVOMAX);
int ge_110 = map(110, 0, 180, SERVOMIN, SERVOMAX);   int gd_110 = map(110, 180, 0, SERVOMIN, SERVOMAX);
int ge_120 = map(120, 0, 180, SERVOMIN, SERVOMAX);   int gd_120 = map(120, 180, 0, SERVOMIN, SERVOMAX);
int ge_135 = map(135, 0, 180, SERVOMIN, SERVOMAX);   int gd_135 = map(135, 180, 0, SERVOMIN, SERVOMAX);
int ge_150 = map(150, 0, 180, SERVOMIN, SERVOMAX);   int gd_150 = map(150, 180, 0, SERVOMIN, SERVOMAX);
int ge_160 = map(160, 0, 180, SERVOMIN, SERVOMAX);   int gd_160 = map(160, 180, 0, SERVOMIN, SERVOMAX);
int ge_170 = map(170, 0, 180, SERVOMIN, SERVOMAX);   int gd_170 = map(170, 180, 0, SERVOMIN, SERVOMAX);
int ge_180 = map(180, 0, 180, SERVOMIN, SERVOMAX);   int gd_180 = map(180, 180, 0, SERVOMIN, SERVOMAX);

//----------------------------------------------------------

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  
  //PCA9685
  pwm1.begin();
  pwm1.setPWMFreq(60);  // This is the maximum PWM frequency
 
  pwm2.begin();
  pwm2.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  delay(10);
}

//----------------------------------------------------------


void loop() {
  Usb.Task();

  //-----------------------------------------------------------------
  
  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
    if (PS3.getAnalogHat(LeftHatX) > 137 || PS3.getAnalogHat(LeftHatX) < 117 || PS3.getAnalogHat(LeftHatY) > 137 || PS3.getAnalogHat(LeftHatY) < 117 || PS3.getAnalogHat(RightHatX) > 137 || PS3.getAnalogHat(RightHatX) < 117 || PS3.getAnalogHat(RightHatY) > 137 || PS3.getAnalogHat(RightHatY) < 117) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(PS3.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(PS3.getAnalogHat(LeftHatY));
      if (PS3.PS3Connected) { // The Navigation controller only have one joystick
        Serial.print(F("\tRightHatX: "));
        Serial.print(PS3.getAnalogHat(RightHatX));
        Serial.print(F("\tRightHatY: "));
        Serial.print(PS3.getAnalogHat(RightHatY));
      }
    }
  
//-----------------------------------------------------------------

    // Analog button values can be read from almost all buttons
    if (PS3.getAnalogButton(L2)  || PS3.getAnalogButton(R2)) {
      Serial.print(F("\r\nL2: "));
      Serial.print(PS3.getAnalogButton(L2));
      if (PS3.PS3Connected) {
        Serial.print(F("\tR2: "));
        Serial.print(PS3.getAnalogButton(R2));
      }
    }
  
//-----------------------------------------------------------------

    if (PS3.getButtonClick(PS)) 
  {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
  
//-----------------------------------------------------------------

    else {
      if (PS3.getButtonClick(TRIANGLE)) 
    {
        Serial.print(F("\r\nTriangulo"));
        
        if (!triangulo && !bolinha)
        {
          pwm1.setPWM(perna1_coxa, 0, ge_90);
          pwm1.setPWM(perna1_femur, 0, ge_90);
          pwm1.setPWM(perna1_tibia, 0, ge_90);

          pwm1.setPWM(perna3_coxa, 0, ge_90);
          pwm1.setPWM(perna3_femur, 0, ge_90);
          pwm1.setPWM(perna3_tibia, 0, ge_90);

          pwm2.setPWM(perna5_coxa, 0, gd_90);
          pwm2.setPWM(perna5_femur, 0, ge_90);
          pwm2.setPWM(perna5_tibia, 0, ge_90);

          triangulo = 1;
      }
      else
      {
          pwm1.setPWM(perna1_coxa, 0, ge_90);
          pwm1.setPWM(perna1_femur, 0, ge_20);
          pwm1.setPWM(perna1_tibia, 0, ge_110);

          pwm1.setPWM(perna3_coxa, 0, ge_90);
          pwm1.setPWM(perna3_femur, 0, ge_20);
          pwm1.setPWM(perna3_tibia, 0, ge_110);

          pwm2.setPWM(perna5_coxa, 0, gd_90);
          pwm2.setPWM(perna5_femur, 0, ge_20);
          pwm2.setPWM(perna5_tibia, 0, ge_110);

          triangulo = 0;
      }
    }
    
    
      if (PS3.getButtonClick(CIRCLE)) 
    {
        Serial.print(F("\r\nBolinha"));

        if (!bolinha && !triangulo)
        {

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_90);
        pwm1.setPWM(perna2_tibia, 0, gd_90);


        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_90);
        pwm2.setPWM(perna4_tibia, 0, gd_90);


        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_90);
        pwm2.setPWM(perna6_tibia, 0, gd_90);

          bolinha = 1;
      }
      else
      {
        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);


        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);


        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_110);

        bolinha = 0;
      }
      
      }
    
    
      if (PS3.getButtonClick(CROSS))
    {
        Serial.print(F("\r\nCross"));
        

    }
    
    
      if (PS3.getButtonClick(SQUARE))
    {
        Serial.print(F("\r\nSquare"));

        
    }
  
//-----------------------------------------------------------------


      if (PS3.getButtonClick(UP)) {
        Serial.print(F("\r\nUp"));

        pwm1.setPWM(perna1_coxa, 0, ge_70);
        pwm1.setPWM(perna1_femur, 0, ge_45);
        pwm1.setPWM(perna1_tibia, 0, ge_110);
        delay(tempo);
        pwm1.setPWM(perna1_coxa, 0, ge_50);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);
        delay(tempo);

        pwm1.setPWM(perna3_coxa, 0, ge_105);
        pwm1.setPWM(perna3_femur, 0, ge_45);
        pwm1.setPWM(perna3_tibia, 0, ge_110);
        delay(tempo);
        pwm1.setPWM(perna3_coxa, 0, ge_120);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);
        delay(tempo);
        
        pwm2.setPWM(perna4_coxa, 0, gd_70);
        pwm2.setPWM(perna4_femur, 0, gd_45);
        pwm2.setPWM(perna4_tibia, 0, gd_110);
        delay(200);
        pwm2.setPWM(perna4_coxa, 0, gd_50);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);
        delay(tempo);

        pwm2.setPWM(perna6_coxa, 0, gd_105);
        pwm2.setPWM(perna6_femur, 0, gd_45);
        pwm2.setPWM(perna6_tibia, 0, gd_120);
        delay(tempo);
        pwm2.setPWM(perna6_coxa, 0, gd_120);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);
        delay(tempo);

        }

      if (PS3.getButtonClick(RIGHT)) {
        Serial.print(F("\r\nRight"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED1);
        }
      }
      if (PS3.getButtonClick(DOWN)) {
        Serial.print(F("\r\nDown"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED2);
        }
      }
      if (PS3.getButtonClick(LEFT)) {
        Serial.print(F("\r\nLeft"));
        if (PS3.PS3Connected) {
          PS3.setLedOff();
          PS3.setLedOn(LED3);
        }
      }
    
    
////----------------------------------------------------------


      if (PS3.getButtonClick(L1))
      {
        Serial.print(F("\r\nL1"));
        pwm1.setPWM(perna1_coxa, 0, ge_90);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_90);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_90);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

       delay(tempo);
       
        pwm1.setPWM(perna1_coxa, 0, ge_70);
        pwm1.setPWM(perna1_femur, 0, ge_45);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_70);
        pwm1.setPWM(perna3_femur, 0, ge_45);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_70);
        pwm2.setPWM(perna5_femur, 0, ge_45);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo);

        pwm1.setPWM(perna1_coxa, 0, ge_45);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_45);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_45);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo); //---------------------------------- parte dois da rotação
       
        pwm1.setPWM(perna1_coxa, 0, ge_45);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_70);
        pwm1.setPWM(perna2_femur, 0, gd_45);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_45);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_70);
        pwm2.setPWM(perna4_femur, 0, gd_45);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_45);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_70);
        pwm2.setPWM(perna6_femur, 0, gd_45);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo);

        pwm1.setPWM(perna1_coxa, 0, ge_45);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_45);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_45);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_45);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_45);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_45);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo); //---------------------------------- parte Três da rotação

        pwm1.setPWM(perna1_coxa, 0, ge_90);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_90);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_90);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo); //---------------------------------- finaliza

       }
        
//----------------------------------------------------------
        
      if (PS3.getButtonClick(R1)){
        Serial.print(F("\r\nR1"));
        pwm1.setPWM(perna1_coxa, 0, ge_90);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_90);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_90);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

       delay(tempo);
       
        pwm1.setPWM(perna1_coxa, 0, ge_110);
        pwm1.setPWM(perna1_femur, 0, ge_45);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_110);
        pwm1.setPWM(perna3_femur, 0, ge_45);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_110);
        pwm2.setPWM(perna5_femur, 0, ge_45);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo);

        pwm1.setPWM(perna1_coxa, 0, ge_135);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_135);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_135);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo); //---------------------------------- parte dois da rotação
       
        pwm1.setPWM(perna1_coxa, 0, ge_135);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_110);
        pwm1.setPWM(perna2_femur, 0, gd_45);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_135);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_110);
        pwm2.setPWM(perna4_femur, 0, gd_45);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_135);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_110);
        pwm2.setPWM(perna6_femur, 0, gd_45);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo);

        pwm1.setPWM(perna1_coxa, 0, ge_135);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_135);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_135);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_135);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_135);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_135);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo); //---------------------------------- parte Três da rotação

        pwm1.setPWM(perna1_coxa, 0, ge_90);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);

        pwm1.setPWM(perna3_coxa, 0, ge_90);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, ge_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, ge_90);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, ge_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);

        delay(tempo); //---------------------------------- finaliza
          
        }

//----------------------------------------------------------
     
      
      if (PS3.getButtonClick(L3))
      {
        Serial.print(F("\r\nL3"));
        
        pwm1.setPWM(perna1_coxa, 0, ge_90);
        pwm1.setPWM(perna1_femur, 0, ge_20);
        pwm1.setPWM(perna1_tibia, 0, ge_110);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_tibia, 0, gd_20);
        pwm1.setPWM(perna2_tibia, 0, gd_110);


        pwm1.setPWM(perna3_coxa, 0, ge_90);
        pwm1.setPWM(perna3_femur, 0, ge_20);
        pwm1.setPWM(perna3_tibia, 0, ge_110);

        pwm2.setPWM(perna4_coxa, 0, gd_90);
        pwm2.setPWM(perna4_femur, 0, gd_20);
        pwm2.setPWM(perna4_tibia, 0, gd_110);

        pwm2.setPWM(perna5_coxa, 0, gd_90);
        pwm2.setPWM(perna5_femur, 0, ge_20);
        pwm2.setPWM(perna5_tibia, 0, ge_110);

        pwm2.setPWM(perna6_coxa, 0, gd_90);
        pwm2.setPWM(perna6_femur, 0, gd_20);
        pwm2.setPWM(perna6_tibia, 0, gd_120);
      
      }

//----------------------------------------------------------

        
      if (PS3.getButtonClick(R3))
      {
        Serial.print(F("\r\nR3"));
        
        pwm1.setPWM(perna1_coxa, 0, ge_90);
        pwm1.setPWM(perna1_femur, 0, ge_30);
        pwm1.setPWM(perna1_tibia, 0, ge_135);

        pwm1.setPWM(perna2_coxa, 0, ge_90);
        pwm1.setPWM(perna2_femur, 0, gd_30);
        pwm1.setPWM(perna2_tibia, 0, gd_135);

        pwm1.setPWM(perna3_coxa, 0, ge_90);
        pwm1.setPWM(perna3_femur, 0, ge_30);
        pwm1.setPWM(perna3_tibia, 0, ge_135);

        pwm2.setPWM(perna4_coxa, 0, gd_90);
        pwm2.setPWM(perna4_femur, 0, gd_30);
        pwm2.setPWM(perna4_tibia, 0, gd_135);

        pwm2.setPWM(perna5_coxa, 0, gd_90);
        pwm2.setPWM(perna5_femur, 0, ge_30);
        pwm2.setPWM(perna5_tibia, 0, ge_135);

        pwm2.setPWM(perna6_coxa, 0, gd_90);
        pwm2.setPWM(perna6_femur, 0, gd_30);
        pwm2.setPWM(perna6_tibia, 0, gd_135);      
      
      }

//-----------------------------------------------------------------


      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect - "));
        PS3.printStatusString();
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
    }
  
  
//----------------------------------------------------------


#if 0 // Set this to 1 in order to see the angle of the controller
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
#endif
  }
  
//----------------------------------------------------------


#if 0 // Set this to 1 in order to enable support for the Playstation Move controller

  else if (PS3.PS3MoveConnected) {
    if (PS3.getAnalogButton(T)) {
      Serial.print(F("\r\nT: "));
      Serial.print(PS3.getAnalogButton(T));
    }
    if (PS3.getButtonClick(PS)) {
      Serial.print(F("\r\nPS"));
      PS3.disconnect();
    }
    else {
      if (PS3.getButtonClick(SELECT)) {
        Serial.print(F("\r\nSelect"));
        printTemperature = !printTemperature;
      }
      if (PS3.getButtonClick(START)) {
        Serial.print(F("\r\nStart"));
        printAngle = !printAngle;
      }
      if (PS3.getButtonClick(TRIANGLE)) {
        Serial.print(F("\r\nTriangle"));
        PS3.moveSetBulb(Red);
      }
      if (PS3.getButtonClick(CIRCLE)) {
        Serial.print(F("\r\nCircle"));
        PS3.moveSetBulb(Green);
      }
      if (PS3.getButtonClick(SQUARE)) {
        Serial.print(F("\r\nSquare"));
        PS3.moveSetBulb(Blue);
      }
      if (PS3.getButtonClick(CROSS)) {
        Serial.print(F("\r\nCross"));
        PS3.moveSetBulb(Yellow);
      }
      if (PS3.getButtonClick(MOVE)) {
        PS3.moveSetBulb(Off);
        Serial.print(F("\r\nMove"));
        Serial.print(F(" - "));
        PS3.printStatusString();
      }
    }
    if (printAngle) {
      Serial.print(F("\r\nPitch: "));
      Serial.print(PS3.getAngle(Pitch));
      Serial.print(F("\tRoll: "));
      Serial.print(PS3.getAngle(Roll));
    }
    else if (printTemperature) {
      Serial.print(F("\r\nTemperature: "));
      Serial.print(PS3.getTemperature());
    }
  }
#endif
}
