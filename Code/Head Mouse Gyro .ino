
// created by Gabry295 
// Edited and tested by Varun Sriram 
//Dated July 2019



#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Mouse.h>

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;
int vz, vy, vz_prec, vy_prec;
int count = 0;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Mouse.begin();
  mpu.initialize();
  if (!mpu.testConnection()) 
  {
    while (1);
  }
}

void loop() {


  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  vz = -(gz + 100) / 200;
  vy = -(gy ) / 200; 
  Mouse.move(vz , vy);
  if ( (vz_prec - 5) <= vz && vz <= vz_prec + 5 && (vy_prec - 5) <= vy && vy <= vy_prec + 5) 
   { 
       count++;
       if (count == 100)
        { 
             if (!Mouse.isPressed(MOUSE_LEFT))
             {
                Mouse.click(MOUSE_LEFT);
                count = 0;
              }
        }
      else 
      {
         if (Mouse.isPressed(MOUSE_LEFT))
            {
              Mouse.release(MOUSE_LEFT);             }
       }
  }
  else
  {
            vz_prec = vz;
            vy_prec = vy;
            count = 0;
  }

  delay(30);
}
