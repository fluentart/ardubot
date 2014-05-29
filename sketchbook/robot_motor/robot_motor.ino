#include "Arduino.h"
#define PWM_PERIOD 2500   // in us

void setup() {
  // put your setup code here, to run once:
  setPWMpin(34); //PWM L0
  setPWMpin(36); //PWM L1
  setPWMpin(38); //PWM L2
  setPWMpin(40); //PWM L3   
  setPWMpin(9);  //PWM L4 
  setPWMpin(8);  //PWM L5
  setPWMpin(7);  //PWM L6 
  setPWMpin(6);  //PWM L7 
  setPWMpin(35);  //PWM H0 
  setPWMpin(37);  //PWM H1   
  setPWMpin(39);  //PWM H2     
  setPWMpin(41);  //PWM H3    
  
  
  
  PWMC_DisableChannel(PWM, 0);
  PWMC_DisableChannel(PWM, 1);
  PWMC_DisableChannel(PWM, 2);
  PWMC_DisableChannel(PWM, 3);
  PWMC_DisableChannel(PWM, 4);
  PWMC_DisableChannel(PWM, 5);
  PWMC_DisableChannel(PWM, 6);
  PWMC_DisableChannel(PWM, 7);      
  PWMC_DisableChannel(PWM, 8);  
  PWMC_DisableChannel(PWM, 9);  
  PWMC_DisableChannel(PWM, 10);  
  PWMC_DisableChannel(PWM, 11); 
  
  pmc_enable_periph_clk(ID_PWM);
  PWMC_ConfigureClocks(1000000,0,VARIANT_MCK);

  configOneMotor(3, PWM_PERIOD);  
  configOneMotor(2, PWM_PERIOD);
  configOneMotor(1, PWM_PERIOD);
  configOneMotor(0, PWM_PERIOD);  
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

void configOneMotor(uint8_t ch, uint32_t period) {
  PWMC_ConfigureChannel(PWM, ch, PWM_CMR_CPRE_CLKA, 0, 0);
  PWMC_SetPeriod(PWM, ch, period);
  PWMC_SetDutyCycle(PWM, ch, 1000);
  PWMC_EnableChannel(PWM, ch);
}

void setPWMpin(uint32_t pin) {
  PIO_Configure(g_APinDescription[pin].pPort,
                PIO_PERIPH_B, //hack Arduino does not allow high PWM by default
                g_APinDescription[pin].ulPin,
                g_APinDescription[pin].ulPinConfiguration);
}

void commandAllMotors(int command) {
  PWMC_SetDutyCycle(PWM, 0, command);
  PWMC_SetDutyCycle(PWM, 1, command);
  PWMC_SetDutyCycle(PWM, 2, command);
  PWMC_SetDutyCycle(PWM, 3, command);
  PWMC_SetDutyCycle(PWM, 4, command);
  PWMC_SetDutyCycle(PWM, 5, command);
  PWMC_SetDutyCycle(PWM, 6, command);
  PWMC_SetDutyCycle(PWM, 7, command);  
  PWMC_SetDutyCycle(PWM, 8, command);    
  PWMC_SetDutyCycle(PWM, 9, command);      
  PWMC_SetDutyCycle(PWM, 10, command);      
  PWMC_SetDutyCycle(PWM, 11, command);        
}
