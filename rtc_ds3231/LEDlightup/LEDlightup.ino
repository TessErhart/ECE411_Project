/*
DS3231_test
Turn on the serial monitor after loading this to check if things are
working as they should.
411 Code for Word Clock. Need to still add the outputs that ATMega328 would send
*/

#include "ds3231.h"
#include <Wire.h>

//DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
//Pins 5,6,7 are arduino pins which correlate to pins 11, 12, 13
int BIN0 = 5; //pin 11 on ATMega328 (A for 72ac11238d)
int BIN1 = 6; //pin 12 on ATMega328 (B)
int BIN2 = 7; //pin 13 on ATMega328 (C)
int hotmin;
int hothr;
uint8_t time[8];

//functions
void displaytime(void);
void checknum(int num);
void printbintime(int ihour, int iminute);
void checknum(int num)
{
    if(num > 12)
    {
        num = num - 12;
    }
    if(num == 1){
      Serial.print("Light up LED 12(1) ");
    }
    else if(num == 2){
      Serial.print("Light up LED 10(2) ");
    }
    else if(num == 3){
      Serial.print("Light up LED 11(3) ");
    }
    else if(num == 4){
      Serial.print("Light up LED 13(4) ");
    }
    else if(num == 5){
      Serial.print("Light up LED 14(5) ");
    }
    else if(num == 6){
      Serial.print("Light up LED 15(6) ");
    }
    else if(num == 7){
      Serial.print("Light up LED 16(7) ");
    }
    else if(num == 8){
      Serial.print("Light up LED 17(8) ");
    }
    else if(num == 9){
      Serial.print("Light up LED 18(9) ");
    }
    else if(num == 10){
      Serial.print("Light up LED 19(10) ");
    }
    else if(num == 11){
      Serial.print("Light up LED 20(11) ");
    }
    else if(num == 12){
      Serial.print("Light up LED 21(12) ");
    }  
    delay(1000); //delay a second
}
void printbintime(int ihour, int iminute)
{
  char nums[][10] = { "zero", "one", "two", "three", "four",
                         "five", "six", "seven", "eight", "nine",
                         "ten", "eleven", "twelve", "thirteen",
                         "fourteen", "fifteen", "sixteen", "seventeen",
                         "eighteen", "nineteen", "twenty", "thirty", "forty",
                         "fifty", "O'Clock" ,"half", "quarter", "past", "to"
                      };
  if( ihour == 0 ){
    ihour = 12;}
  displaytime();
  if(iminute < 15){
      if(iminute < 15){
        //printf("%s o'clock\n", nums[ihour]);
        checknum(ihour);
        Serial.print("Light up LED 22(o'clock)~ ");

      }
      if(iminute == 0){
        //printf("%s o'clock\n", nums[ihour]);
        Serial.print("Light up LED 22(o'clock) ");
        checknum(ihour);
      }
    }
/*  else if(iminute < 10)
  {
        //printf("%s minutes past %s o'clock\n", nums[iminute], nums[ihour]);
        checknum(iminute);
        Serial.print("Light up LEDs 7 & 9(minutes past)");
        checknum(ihour);
        Serial.print("Light up LED 22(o'clock)");
  }*/
  if((iminute >= 15) && (iminute < 30)){
        //printf("quarter past %s \n", nums[ihour]);
        Serial.print("Light up LED 4 & 9(quarter past) ");
        checknum(ihour);
        Serial.print("Light up LED 22(o'clock)~ ");

  }
  if((iminute >= 30) ){
       if(iminute < 45){
        //printf("half past %s\n", nums[ihour]);
        Serial.print("Light up LED 2 & 9(half past)~ ");
        checknum(ihour);
        Serial.print("Light up LED 22(o'clock)~ ");

       }
        if(iminute == 30){
        //printf("half past %s\n", nums[ihour]);
        Serial.print("Light up LED 2 & 9(half past) ");
        checknum(ihour);
        Serial.print("Light up LED 22(o'clock)~ ");
        }
  }
 
 if(iminute >= 45){
     if (iminute < 60){
        //printf("quarter to %s\n", nums[(ihour % 12) + 1]);
        Serial.print("Light up LED 4 & 8(quarter to)~  ");
        checknum((ihour % 12) + 1);
        Serial.print("Light up LED 22(o'clock)~ ");

      }
      if(iminute == 45){
        //printf("quarter to %s\n", nums[(ihour % 12) + 1]);
        Serial.print("Light up LED 4 & 8(quarter to) ");
        checknum((ihour % 12) + 1);
        Serial.print("Light up LED 22(o'clock)~ ");

      }
 }
  Serial.print("\n-------------");
}

void displaytime(void){
  // Now, turn on the "It is" leds
  //Serial.print("It is \n");
  Serial.print("Light up LED 1(It is) "); 
}
void setup() {
  // Start the I2C interface
  Wire.begin();
  // initialize digital pins as an output.
  pinMode(BIN0, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
    //Variables or registers with Atmel
    int h = 0;
    int m = 0;
    int i = 0;
    int j = 0;
     //internal clock shenanigans maybe
     // use for demo test later?
 /*    for(i=0;i<12;i++)
     {
         for(j=0;j<4;j++)
         {
             printbintime(h, m); 
            m = m + 15;
         }
         h++;
         m = 0;
     }*/
  // Start the serial interface
  Serial.begin(9600);
}

void loop() {
  // send what's going on to the serial monitor.
  //the output should be whatever the decoder expects.( but i'll add stuff to let me light up LEDS
  char buff[128];
//  DS3231_get_a1(&buff[0], 59);
//  Serial.println(buff);
  struct ts t;
  int hotmin = t.min;
  int hothr =  t.hour; 
  Serial.print(hothr);
  Serial.print(":");
  Serial.print(hotmin);
  Serial.print("   ");
  printbintime(hothr,hotmin);
  DS3231_get(&t);

        snprintf(buff, 128, "%d.%02d.%02d %02d:%02d:%02d", t.year,
            t.mon, t.mday, t.hour, t.min, t.sec);

  Serial.print('\n');
  Serial.print('\n');
  delay(1000);
}
