/*
demo test
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
//MUX 1
int muxPin1 = 2; //pin 4 on ATMega328 (A for 72ac11238d)
int muxPin2 = 3; //pin 5 on ATMega328 (B)
int muxPin3 = 4; //pin 6 on ATMega328 (C)
//MUX 2
int muxPin4 = 5; //pin 11 on ATMega328 (A for 72ac11238d)
int muxPin5 = 6; //pin 12 on ATMega328 (B)
int muxPin6 = 7; //pin 13 on ATMega328 (C)
//MUX 3
int muxPin7 = 8; //pin 14 on ATMega328 (A for 72ac11238d)
int muxPin8 = 9; //pin 15 on ATMega328 (B)
int muxPin9 = 10;//pin 16 on ATMega328 (C)


int hotmin;
int hothr;
uint8_t time[8];

//functions
void displaytime(void);
void checknum(int num);
void printbintime(int ihour, int iminute);
void turnonLED22(void);
void clearLEDs(void);
void demotest(void);
void clearLEDs(void)
{
      digitalWrite(muxPin1, LOW); // off
      digitalWrite(muxPin2, LOW); // off
      digitalWrite(muxPin3, LOW); // 0ff
      digitalWrite(muxPin4, LOW); // off
      digitalWrite(muxPin5, LOW); // off
      digitalWrite(muxPin6, LOW); // 0ff
      digitalWrite(muxPin7, HIGH); // off
      digitalWrite(muxPin8, HIGH); // off
      digitalWrite(muxPin9, HIGH); // 0ff
      delay(1000);
}
void checknum(int num)
{
    if(num > 12)
    {
        num = num - 12;
    }
    if(num == 1){
      Serial.print("Light up LED 12(1) ");
      //Send msg to LED12 (100)
      digitalWrite(muxPin4, LOW); // on
      digitalWrite(muxPin5, LOW); // on
      digitalWrite(muxPin6, HIGH); // off
    }
    else if(num == 2){
      Serial.print("Light up LED 10(2) ");
      //Send msg to LED10 (010)
      digitalWrite(muxPin4, LOW); // off
      digitalWrite(muxPin5, HIGH); // on
      digitalWrite(muxPin6, LOW); // 
    }
    else if(num == 3){
      Serial.print("Light up LED 11(3) ");
      //Send msg to LED11 (011)
      digitalWrite(muxPin4, HIGH); // on
      digitalWrite(muxPin5, HIGH); // on
      digitalWrite(muxPin6, LOW); // oFF
    }
    else if(num == 4){
      Serial.print("Light up LED 13(4) ");
      //Send msg to LED13 (101)
      digitalWrite(muxPin4, HIGH); // on
      digitalWrite(muxPin5, LOW); // off
      digitalWrite(muxPin6, HIGH); // on
    }
    else if(num == 5){
      Serial.print("Light up LED 14(5) ");
      //Send msg to LED14 (110)
      digitalWrite(muxPin4, LOW); // on
      digitalWrite(muxPin5, HIGH); // off
      digitalWrite(muxPin6, HIGH); // on
    }
    else if(num == 6){
      Serial.print("Light up LED 15(6) ");
      //Send msg to LED15 (111)
      digitalWrite(muxPin4, HIGH); // on
      digitalWrite(muxPin5, HIGH); // on
      digitalWrite(muxPin6, HIGH); // on
    }
    else if(num == 7){
      Serial.print("Light up LED 16(7) ");
      //Send msg to LED16 (000)
      digitalWrite(muxPin7, LOW); // off
      digitalWrite(muxPin8, LOW); // off
      digitalWrite(muxPin9, LOW); // off
    }
    else if(num == 8){
      Serial.print("Light up LED 17(8) ");
      //Send msg to LED17 (001)
      digitalWrite(muxPin7, HIGH); // onn
      digitalWrite(muxPin8, LOW); // off
      digitalWrite(muxPin9, LOW); // 0ff
    }
    else if(num == 9){
      Serial.print("Light up LED 18(9) ");
      //Send msg to LED18 (010)
      digitalWrite(muxPin7, LOW); // 
      digitalWrite(muxPin8, HIGH); // 
      digitalWrite(muxPin9, LOW); //
    }
    else if(num == 10){
      Serial.print("Light up LED 19(10) ");
      //Send msg to LED19 (011)
      digitalWrite(muxPin7, HIGH); // 
      digitalWrite(muxPin8, HIGH); // 
      digitalWrite(muxPin9, LOW); //
    }
    else if(num == 11){
      Serial.print("Light up LED 20(11) ");
      //Send msg to LED20 (100)
      digitalWrite(muxPin7, LOW); // 
      digitalWrite(muxPin8, LOW); // 
      digitalWrite(muxPin9, HIGH); //
    }
    else if(num == 12){
      Serial.print("Light up LED 21(12) ");
      //Send msg to LED21 (101)
      digitalWrite(muxPin7, HIGH); // 
      digitalWrite(muxPin8, LOW); // 
      digitalWrite(muxPin9, HIGH); //
    }
    delay(1000);
    Serial.print("Light up LED 22(o'clock)~ ");
    turnonLED22();
    clearLEDs();  
    delay(1000); //delay a second
}
void turnonLED22(void)
{
        //Send msg to LED22 (110)
        digitalWrite(muxPin7, LOW); // 
        digitalWrite(muxPin8, HIGH); // 
        digitalWrite(muxPin9, HIGH); //  
        delay(1000);
}
void printbintime(int ihour, int iminute)
{
 /* char nums[][10] = { "zero", "one", "two", "three", "four",
                         "five", "six", "seven", "eight", "nine",
                         "ten", "eleven", "twelve", "thirteen",
                         "fourteen", "fifteen", "sixteen", "seventeen",
                         "eighteen", "nineteen", "twenty", "thirty", "forty",
                         "fifty", "O'Clock" ,"half", "quarter", "past", "to"
                      };*/
  if( ihour == 0 ){
    ihour = 12;}
  displaytime();
  if(iminute < 15){
      if(iminute < 15){
        //printf("%s o'clock\n", nums[ihour]);
        checknum(ihour);
//        Serial.print("Light up LED 22(o'clock)~ ");
//        turnonLED22();
      }
      else if(iminute == 0){
        //printf("%s o'clock\n", nums[ihour]);
//        Serial.print("Light up LED 22(o'clock) ");
//        turnonLED22();
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
        //Send msg to LED4 (011)
        digitalWrite(muxPin1, HIGH); // on
        digitalWrite(muxPin2, HIGH); // on
        digitalWrite(muxPin3, LOW); // off
        delay(1000);
        //Send msg to LED9 (001)
        digitalWrite(muxPin4, HIGH); // on
        digitalWrite(muxPin5, LOW); // off
        digitalWrite(muxPin6, LOW); // off
        delay(1000);
        checknum(ihour);
//        Serial.print("Light up LED 22(o'clock)~ ");
//        turnonLED22();

  }
  if((iminute >= 30) ){
       if(iminute < 45){
        //printf("half past %s\n", nums[ihour]);
        Serial.print("Light up LED 2 & 9(half past)~ ");
        //Send msg to LED2 (001)
        digitalWrite(muxPin1, HIGH); // on
        digitalWrite(muxPin2, LOW); // on
        digitalWrite(muxPin3, LOW); // off
        delay(1000);
        //Send msg to LED9 (001)
        digitalWrite(muxPin4, HIGH); // on
        digitalWrite(muxPin5, LOW); // off
        digitalWrite(muxPin6, LOW); // off
        delay(1000);
        checknum(ihour);
 //       Serial.print("Light up LED 22(o'clock)~ ");
//        turnonLED22();

       }
       else if(iminute == 30){
        //printf("half past %s\n", nums[ihour]);
        Serial.print("Light up LED 2 & 9(half past) ");
        //Send msg to LED2 (001)
        digitalWrite(muxPin1, HIGH); // on
        digitalWrite(muxPin2, LOW); // on
        digitalWrite(muxPin3, LOW); // off
        delay(1000);
        //Send msg to LED9 (001)
        digitalWrite(muxPin4, HIGH); // on
        digitalWrite(muxPin5, LOW); // off
        digitalWrite(muxPin6, LOW); // off
        delay(1000);
        checknum(ihour);
//        Serial.print("Light up LED 22(o'clock)~ ");
//        turnonLED22();
        }
  }
 
 if(iminute >= 45){
     if (iminute < 60){
        //printf("quarter to %s\n", nums[(ihour % 12) + 1]);
        Serial.print("Light up LED 4 & 8(quarter to)~  ");
        //Send msg to LED4 (011)
        digitalWrite(muxPin1, HIGH); // on
        digitalWrite(muxPin2, HIGH); // on
        digitalWrite(muxPin3, LOW); // off
        delay(1000);
        //Send msg to LED8 (111)
        digitalWrite(muxPin1, HIGH); // on
        digitalWrite(muxPin2, HIGH); // on
        digitalWrite(muxPin3, HIGH); // onn
        delay(1000);
        checknum((ihour % 12) + 1);
//        Serial.print("Light up LED 22(o'clock)~ ");
//        turnonLED22();

      }
      else if(iminute == 45){
        //printf("quarter to %s\n", nums[(ihour % 12) + 1]);
        Serial.print("Light up LED 4 & 8(quarter to) ");
        //Send msg to LED4 (011)
        digitalWrite(muxPin1, HIGH); // on
        digitalWrite(muxPin2, HIGH); // on
        digitalWrite(muxPin3, LOW); // off
        delay(1000);
        //Send msg to LED8 (111)
        digitalWrite(muxPin1, HIGH); // on
        digitalWrite(muxPin2, HIGH); // on
        digitalWrite(muxPin3, HIGH); // onn
        delay(1000);
        checknum((ihour % 12) + 1);


      }
 }
 // clearLEDs();

  Serial.print("\n-------------");
}

void displaytime(void){
  // Now, turn on the "It is" leds
  //Serial.print("It is \n");
  Serial.print("Light up LED 1(It is) "); 
  //Send msg to LED1 (000)
//  digitalWrite(muxPin1, LOW); // off
//  digitalWrite(muxPin2, LOW); // off
//  digitalWrite(muxPin3, LOW); // off
  delay(5000);
}
void setup() {
  // Start the I2C interface
  Wire.begin();
  // initialize digital pins as an output.
  
  pinMode(muxPin1, OUTPUT);
  pinMode(muxPin2, OUTPUT);
  pinMode(muxPin3, OUTPUT);
  pinMode(muxPin4, OUTPUT);
  pinMode(muxPin5, OUTPUT);
  pinMode(muxPin6, OUTPUT);
  pinMode(muxPin7, OUTPUT);
  pinMode(muxPin8, OUTPUT);
  pinMode(muxPin9, OUTPUT);


  // Start the serial interface
  Serial.begin(9600);
}
void demotest(void)
{
    //Variables
    int h = 0;
    int m = 0;
    int i = 0;
    int j = 0;
     // use for demo test later?
     
     for(i=0;i<12;i++)
     {
         for(j=0;j<4;j++)
         {
             printbintime(h, m); 
            m = m + 15;
            delay(250);
            Serial.print("Time change\n");
         }
         h++;
         m = 0;
     }
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
 // printbintime(hothr,hotmin);
  demotest();
  DS3231_get(&t);

        snprintf(buff, 128, "%d.%02d.%02d %02d:%02d:%02d", t.year,
            t.mon, t.mday, t.hour, t.min, t.sec);

  Serial.print('\n');
  Serial.print('\n');
  delay(1000);
}
