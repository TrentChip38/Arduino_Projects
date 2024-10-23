const int pwm = 3 ; //initializing pin 2 as pwm
const int in_1 = 5 ;
const int in_2 = 6 ;
const int pwm2 = 9 ; //initializing pin 2 as pwm
const int in_3 = 10 ;
const int in_4 = 11 ;
//For providing logic to L298 IC to choose the direction of the DC motor

void setup() {
   pinMode(pwm,OUTPUT) ; //we have to set PWM pin as output
   pinMode(in_1,OUTPUT) ; //Logic pins are also set as output
   pinMode(in_2,OUTPUT) ;
    pinMode(pwm2,OUTPUT) ; //we have to set PWM pin as output
   pinMode(in_3,OUTPUT) ; //Logic pins are also set as output
   pinMode(in_4,OUTPUT) ;
}

void loop() {
   //For Clock wise motion , in_1 = High , in_2 = Low
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,LOW) ;
   analogWrite(pwm,255) ;
   digitalWrite(in_3,HIGH) ;
   digitalWrite(in_4,LOW) ;
   analogWrite(pwm2,100) ;
   /* setting pwm of the motor to 255 we can change the speed of rotation
   by changing pwm input but we are only using arduino so we are using highest
   value to driver the motor */
   //Clockwise for 3 secs
   delay(3000) ;
   //For brake
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,HIGH) ;
   digitalWrite(in_3,HIGH) ;
   digitalWrite(in_4,HIGH) ;
   delay(1000) ;
   //For Anti Clock-wise motion - IN_1 = LOW , IN_2 = HIGH
   digitalWrite(in_1,LOW) ;
   digitalWrite(in_2,HIGH) ;
   digitalWrite(in_3,LOW) ;
   digitalWrite(in_4,HIGH) ;
   delay(3000) ;
   //For brake
   digitalWrite(in_1,HIGH) ;
   digitalWrite(in_2,HIGH) ;
   digitalWrite(in_3,HIGH) ;
   digitalWrite(in_4,HIGH) ;
   delay(1000) ;
}