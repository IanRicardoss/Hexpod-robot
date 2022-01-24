
// --- Mapeamento de Hardware -----------------------------------------
#define central     

#define perna1_coxa 22  
#define perna1_femur 24 
#define perna1_tibia 26 
                        
#define perna3_coxa 28  
#define perna3_femur 30 
#define perna3_tibia 32 
                        
#define perna5_coxa 34  
#define perna5_femur 36 
#define perna5_tibia 38 

#define perna2_coxa 23  
#define perna2_femur 25 
#define perna2_tibia 27 
                        
#define perna4_coxa 29  
#define perna4_femur 31 
#define perna4_tibia 33 
                        
#define perna6_coxa 35  
#define perna6_femur 37 
#define perna6_tibia 39 



  // --- Protótipo das Funções Auxialiares ----------------------------------
  void mservo(int motor, int grau, int tempo);

  // --- Configurações Iniciais -------------------------------------------
  
  void setup()
  {
    pinMode(perna1_coxa, OUTPUT);
    pinMode(perna1_femur, OUTPUT);
    pinMode(perna1_tibia, OUTPUT);

    pinMode(perna2_coxa, OUTPUT);
    pinMode(perna2_femur, OUTPUT);
    pinMode(perna2_tibia, OUTPUT);

    pinMode(perna3_coxa, OUTPUT);
    pinMode(perna3_femur, OUTPUT);
    pinMode(perna3_tibia, OUTPUT);

    pinMode(perna4_coxa, OUTPUT);
    pinMode(perna4_femur, OUTPUT);
    pinMode(perna4_tibia, OUTPUT);

    pinMode(perna5_coxa, OUTPUT);
    pinMode(perna5_femur, OUTPUT);
    pinMode(perna5_tibia, OUTPUT);

    pinMode(perna6_coxa, OUTPUT);
    pinMode(perna6_femur, OUTPUT);
    pinMode(perna6_tibia, OUTPUT);

  } //fim setup


  // --- Loop Infinito -------------------------------------------------------------
  
  void loop()
  {
    mservo(perna1_coxa, 90, 20);    //move o servo para a posição 90º por 2 segundos
    mservo(perna1_femur, 90, 20);    //move o servo para a posição 90º por 2 segundos

  
    mservo(perna1_coxa, 45, 20);    //move o servo para a posição 45º por 2 segundos
    mservo(perna1_femur, 45, 20);    //move o servo para a posição 45º por 2 segundos


    mservo(perna1_coxa, 90, 20);    //move o servo para a posição 90º por 2 segundos
    mservo(perna1_femur, 90, 20);    //move o servo para a posição 90º por 2 segundos


    mservo(perna1_coxa, 135, 20);    //move o servo para a posição 135º por 2 segundos
    mservo(perna1_femur, 135, 20);    //move o servo para a posição 135º por 2 segundos


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

   

