// Подключаем библиотеки для работы
#include <Wire.h>
#include <iarduino_RTC.h> 
#include <Servo.h>

#include <PCF8812_new.h> 
#include "cell_blk.h"
#include "cell_wht.h"
#include "feeder_empty.h"
#include "feeder_full.h"
#include "pressure.h"
#include "font_5x5.h"
#include "font_5x8.h"
#include "font_7x15.h"
#include "font_12x16_rus.h"

// Время первого кормления
#define FEED_HOUR_1     21
#define FEED_MINUTE_1   31
// Время второго кормления
#define FEED_HOUR_2     12
#define FEED_MINUTE_2   0
// Время третьего кормления
#define FEED_HOUR_3     19
#define FEED_MINUTE_3   0
// Пин к которому подключается сервопривод
#define SERVO_PIN A0

// Флаг "Уже покормили"
boolean flag = true;

const int buttonPin = 5;
char time_for_draw;
 /*
 * 13 PIN - RST
   11 PIN - DAT
   12 PIN - CLK 
 */
iarduino_RTC time(RTC_DS1302,13,12,11); 
Servo servo;
 
void setup() {
  Serial.begin(9600); //DEBUG
  // Инициализируем часы
  time.begin();                                    
 // Serial.println(String(__DATE__));
 // Serial.println(String(__TIME__));
  time.settime(00, 30, 16, 15, 03, 20);  //сек, мин, час, число, месяц, год, день недели.
  servo.attach(SERVO_PIN);
  servo.write(0);

  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  servo.detach();  
  pinMode(LED_BUILTIN, OUTPUT);
  LcdInit(10, 9, 8, 7, 6);  //CS, RESET, D/C, CLK, DATA
  LcdsetFont(font_12x16_rus);
}


void loop() {  
  time.gettime();
  LcdPageONE();
  do{
    LcdRoundRect(0, 0, 101, 64, 3, ON);
    LcdRoundRect(2, 2, 97, 14, 3, ON);

    //draw pressure
    LcdRoundRect(2, 48, 50, 14, 3, ON);
    LcdBitmap(4, 50, pressure, ON);
    LcdsetFont(font_5x8);
    LcdGotoXY(13, 53);
    LcdPrint("123.12", ON, 1);

    //draw pressure
    LcdRoundRect(54, 48, 45, 14, 3, ON);
    LcdBitmap(56, 50, pressure, ON);
    LcdsetFont(font_5x8);
    LcdGotoXY(68, 53);
    LcdPrint("23.12", ON, 1);
    
    LcdBitmap(4, 4, cell_blk, ON);
    LcdBitmap(14, 4, cell_wht, ON);
    LcdBitmap(24, 4, feeder_empty, ON);
    LcdBitmap(34, 4, feeder_full, ON);
    LcdGotoXY(10, 25);
    LcdsetFont(font_12x16_rus);
    LcdPrint(time.gettime("H:i:s"), ON, 1);
  }
  while(LcdPageTWO());
  delay(1000);  
  //Serial.println(time_for_draw);  // time.gettime("d-m-Y, H:i:s, D") DEBUG
  int buttonVal = digitalRead(buttonPin);
  //Проверяем не пришло ли время покормить животное
  if (((time.Hours == FEED_HOUR_1) && (time.minutes == FEED_MINUTE_1) && (time.seconds == 00))
  ||((time.Hours == FEED_HOUR_2) && (time.minutes == FEED_MINUTE_2) && (time.seconds == 00))
  ||((time.Hours == FEED_HOUR_3) && (time.minutes == FEED_MINUTE_3) && (time.seconds == 00))
  ||(buttonVal == LOW)) 
  {
      
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    // Если время пришло устанавливаем флаг "Уже покормили"
    servo.attach(SERVO_PIN);
    servo.write(90);
    delay(575);
    servo.write(0);
    delay(1500);
    servo.detach();
    delay(5000);
    
  } 
  else {
    delay(13);
  }
}
