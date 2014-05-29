#include <Wire.h>
#include <L3G.h>
#include <LSM303.h>

L3G gyro;
LSM303 compass;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
  
  compass.init();  
  compass.enableDefault();
}

void loop() {
  gyro.read();
  compass.read();

  Serial.print("{");
  Serial.print("\"gx\":");
  Serial.print((int)gyro.g.x);
  Serial.print(",\"gy\":");
  Serial.print((int)gyro.g.y);
  Serial.print(",\"gz\":");
  Serial.print((int)gyro.g.z);
  Serial.print(",\"ax\":");
  Serial.print((int)compass.a.x>>4);
  Serial.print(",\"ay\":");
  Serial.print((int)compass.a.y>>4);
  Serial.print(",\"az\":");
  Serial.print((int)compass.a.z>>4);
  Serial.print(",\"mx\":");
  Serial.print((int)compass.m.x);
  Serial.print(",\"my\":");
  Serial.print((int)compass.m.y);
  Serial.print(",\"mz\":");
  Serial.print((int)compass.m.z);  
  Serial.println("}");  

  delay(10);
}
