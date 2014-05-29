

void setup() {
  // put your setup code here, to run once:
  pinMode(34, OUTPUT); //PWM L0
  pinMode(36, OUTPUT); //PWM L1
  pinMode(38, OUTPUT); //PWM L2
  pinMode(40, OUTPUT); //PWM L3   
  pinMode(9, OUTPUT);  //PWM L4 
  pinMode(8, OUTPUT);  //PWM L5
  pinMode(7, OUTPUT);  //PWM L6 
  pinMode(6, OUTPUT);  //PWM L7 
  pinMode(35, OUTPUT);  //PWM H0 
  pinMode(37, OUTPUT);  //PWM H1   
  pinMode(39, OUTPUT);  //PWM H2     
  pinMode(41, OUTPUT);  //PWM H3    
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for(int pos = 1100; pos <= 1900; pos += 1) 
  {                                  
    commandAllMotors(pos);               
    delayMicroseconds(400);                      
  } 
  for(int pos = 1900; pos>=1100; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    commandAllMotors(pos);               
    delayMicroseconds(400);    
  } 
}

void commandMotor(int pin, int command) {
  digitalWrite(pin, 1); //PWM L0
  delayMicroseconds(command);
  digitalWrite(pin, 0); //PWM L0
}



void commandAllMotors(int command) {
  commandMotor(34, command); //PWM L0
  commandMotor(36, command); //PWM L1
  commandMotor(38, command); //PWM L2
  commandMotor(40, command); //PWM L3   
  commandMotor( 9, command);  //PWM L4 
  commandMotor( 8, command);  //PWM L5
  commandMotor( 7, command);  //PWM L6 
  commandMotor( 6, command);  //PWM L7 
  commandMotor(35, command); //PWM H0 
  commandMotor(37, command); //PWM H1   
  commandMotor(39, command); //PWM H2     
  commandMotor(41, command); //PWM H3    
  delayMicroseconds(10000);
     
}
