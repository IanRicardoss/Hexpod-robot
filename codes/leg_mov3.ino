#include <Servo.h>

// --- Mapeamento de Hardware -----------------------------------------
Servo central;

Servo perna1_coxa;
Servo perna1_femur; 
#define perna1_tibia 22 
                        
Servo perna3_coxa;  
Servo perna3_femur; 
#define perna3_tibia 26 
                        
Servo perna5_coxa;  
Servo perna5_femur; 
#define perna5_tibia 30 

Servo perna2_coxa;  
Servo perna2_femur; 
#define perna2_tibia 34
                        
Servo perna4_coxa;  
Servo perna4_femur; 
#define perna4_tibia 38
                        
Servo perna6_coxa;  
Servo perna6_femur; 
#define perna6_tibia 40

  // --- Protótipo das Funções Auxialiares ----------------------------------
  void mservo(int motor, int grau, int tempo);


  // --- Configurações Iniciais -------------------------------------------
  
  void setup()
  {
    central.attach(0);
    
    perna1_coxa.attach(1);
    perna1_femur.attach(2);
    pinMode(perna1_tibia, OUTPUT);

    perna2_coxa.attach(3);
    perna2_femur.attach(4);
    pinMode(perna2_tibia, OUTPUT);

    perna3_coxa.attach(5);
    perna3_femur.attach(6);
    pinMode(perna3_tibia, OUTPUT);

    perna4_coxa.attach(7);
    perna4_femur.attach(8);
    pinMode(perna4_tibia, OUTPUT);

    perna5_coxa.attach(9);
    perna5_femur.attach(10);
    pinMode(perna5_tibia, OUTPUT);

    perna6_coxa.attach(11);
    perna6_femur.attach(12);
    pinMode(perna6_tibia, OUTPUT);

  } //fim setup


  // --- Loop Infinito -------------------------------------------------------------
  
  void loop()
  {
    perna1_coxa.write(90);           //move o servo para a posição 90º por 2 segundos
    mservo(perna1_tibia, 90, 20);    //move o servo para a posição 90º por 2 segundos
    delay(2000);
  
    perna1_coxa.write(45);           //move o servo para a posição 45º por 2 segundos
    mservo(perna1_tibia, 45, 20);    //move o servo para a posição 45º por 2 segundos
    delay(2000);

    perna1_coxa.write(90);           //move o servo para a posição 90º por 2 segundos
    mservo(perna1_tibia, 90, 20);    //move o servo para a posição 90º por 2 segundos
    delay(2000);

    perna1_coxa.write(135);           //move o servo para a posição 90º por 2 segundos
    mservo(perna1_tibia, 135, 20);    //move o servo para a posição 135º por 2 segundos
    delay(2000);

  } //end loop

  // --- Desenvolvimento das Funções Auxialiares ---

  void mservo(int motor, int grau, int tempo)
  { 
    int pulso;
    int fecha_periodo;

    pulso = (600 + (grau * 10));
    fecha_periodo = (20000 - pulso);
    tempo = tempo * 5;          //multiplica os 20ms por 5 para virar 0.1s
    
    if (grau >= 0 && grau <= 180)
    {
      for (int i = 0; i < tempo; i++) //laço para fechar 0.1s
      {
        digitalWrite(motor, HIGH);  //pulso do servo
        delayMicroseconds(pulso);     
        digitalWrite(motor, LOW);   //completa periodo do servo
        delayMicroseconds(fecha_periodo);
    }
  }
}

   

