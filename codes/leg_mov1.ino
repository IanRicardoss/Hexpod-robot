
// --- Mapeamento de Hardware ---
#define central         // motor que realiza abertura de 

#define perna1_coxa 22  //   \  
#define perna1_femur 24 //     \
#define perna1_tibia 26 //       \
                        //         \
#define perna3_coxa 28  //           \
#define perna3_femur 30 //             - Conjunto 1 - eixo esquerdo
#define perna3_tibia 32 //           /
                        //         /
#define perna5_coxa 34  //       /
#define perna5_femur 36 //     /
#define perna5_tibia 38 //   /

#define perna2_coxa 23  //   \  
#define perna2_femur 25 //     \
#define perna2_tibia 27 //       \
                        //         \
#define perna4_coxa 29  //           \
#define perna4_femur 31 //             - Conjunto 2 - eixo direito
#define perna4_tibia 33 //           /
                        //         /
#define perna6_coxa 35  //       /
#define perna6_femur 37 //     /
#define perna6_tibia 39 //   /


// --- Protótipo das Funções Auxialiares ---
void servo0graus();
void servo45graus();
void servo90graus();
void servo135graus();
void servo180graus();


// --- Configurações Iniciais ---
void setup()
{
   pinMode(servo1, OUTPUT); //saída para o servo1
} //end setup

// --- Loop Infinito ---
void loop()
{
  servo45graus(20);    //move o servo para a posição 45º por 2 segundos
  
  servo90graus(20);    //move o servo para a posição 90º por 2 segundos

  servo135graus(20);    //move o servo para a posição 135º por 2 segundos
  
  servo90graus(20);    //move o servo para a posição 90º por 2 segundos
  
} //end loop

// --- Desenvolvimento das Funções Auxialiares ---


void servo0graus(int tempo)    //Posiciona o servo em 0 graus
{                              //O tempo esta em 0.1s
   tempo = tempo * 5;          //multiplica os 20ms por 5 para virar 0.1s
   for(int i=0;i<tempo;i++)    //laço para fechar 0.1s
   {
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(600);      //0.6ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<32;i++)delayMicroseconds(600);
                               // 20ms = 20000us
                               // 20000us - 600us = 19400us
                               // 19400/600 = ~~32
   }
} //end servo45graus


void servo45graus(int tempo)   //Posiciona o servo em 45 graus
{                              //O tempo esta em 0.1s
   tempo = tempo * 5;          //multiplica os 20ms por 5 para virar 0.1s
   for(int i=0;i<tempo;i++)    //laço para fechar 0.1s
   {
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(1050);     //1.05ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<18;i++)delayMicroseconds(600);
                               // 20ms = 20000us
                               // 20000us - 1050us = 18950us
                               // 18950/1050 = ~~18
   }
} //end servo45graus

void servo90graus(int tempo)    //Posiciona o servo em 90 graus
{                               //O tempo esta em 0.1s
   tempo = tempo * 5;           //multiplica os 20ms por 5 para virar 0.1s
   for(int i=0;i<tempo;i++)     //laço para fechar 0.1s
   {
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(1500);     //1.5ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<12;i++)delayMicroseconds(1500);
                               // 20ms = 20000us
                               // 20000us - 1500us = 18500us
                               // 18500/1500 = ~~12 
   }
} //end servo90graus

void servo135graus(int tempo)   //Posiciona o servo em 135 graus
{                               //O tempo esta em 0.1s
   tempo = tempo * 5;           //multiplica os 20ms por 5 para virar 0.1s
   for(int i=0;i<tempo;i++)     //laço para fechar 0.1s
   {
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(1950);      //1.95ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<9;i++)delayMicroseconds(600);
                               // 20ms = 20000us
                               // 20000us - 1950us = 18050us
                               // 18050/1950 = ~~9
   }
} //end servo135graus

void servo180graus(int tempo)   //Posiciona o servo em 180 graus
{                               //O tempo esta em 0.1s
   tempo = tempo * 5;           //multiplica os 20ms por 5 para virar 0.1s
   for(int i=0;i<tempo;i++)     //laço para fechar 0.1s
   {
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(2400);     //2.4ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<7;i++)delayMicroseconds(2400);
                               // 20ms = 20000us
                               // 20000us - 2400us = 17600us
                               // 17600/2400 = ~~7
   }
} //end servo180graus
