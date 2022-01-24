#include <Servo.h>

Servo motor1;
Servo motor2;  
Servo motor3;                           

 void setup()
{
   motor1.attach(1);
   motor2.attach(2); 
   motor3.attach(3); 

   motor1.write(90);
   motor2.write(90); 
   motor3.write(90);

}

void loop () {

}
