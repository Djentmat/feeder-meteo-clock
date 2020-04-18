// Подключаем библиотеки для работы
#include <GyverTimer.h>
#include <iarduino_RTC.h>
#include <Servo.h>
#include <Adafruit_BMP280.h>

#include <PCF8812_new.h>
#include "cell_blk.h"
#include "cell_wht.h"
#include "feeder_empty.h"
#include "feeder_full.h"
#include "pressure.h"
#include "temperature.h"
#include "timer_off.h"
#include "font_5x8.h"
#include "font_12x16_rus.h"

#define SERVO_PIN A0

// Инициализация переменных
byte feed_hour_1 = 9;
byte feed_minute_1 = 00;
//----------------------|
byte feed_hour_2 = 9;
byte feed_minute_2 = 00;
//----------------------|
byte feed_hour_3 = 9;
byte feed_minute_3 = 00;
//----------------------|
byte time_hour = 14;
byte time_minutes = 43;
byte time_seconds = 00;
byte time_day = 06;
byte time_month = 04;
byte time_year = 20;

boolean butt_flag, flag_set, set_on_flag;
unsigned long pressure_val, aver_pressure,  pressure_array[24];
unsigned long min_mapped_press, max_mapped_press, last_button;
unsigned long sumX, sumY, sumX2, sumXY;
float a;
int aver_temper, Mode_graph, buff_val, buff_val2, buff_val3, buff_val4, delta, temp;
int flag, approx, min_mapped_temp, max_mapped_temp,  buff = 0.0;
int temp_array[24], time_array[24], temp_mapped[24], press_mapped[24];
byte sec_now, sec_buff = 0;

GTimer_ms hour_timer(2000);
//GTimer_ms hour_timer((long)60*60 * 1000);
GTimer_ms draw_scr_timer(1 * 1000);
GTimer_ms buttons_timer(500);


iarduino_RTC time(RTC_DS1302, 13, 12, 11); /*13 PIN - RST
                                          11 PIN - DAT
                                          12 PIN - CLK */
Servo servo;
Adafruit_BMP280 bmp; // I2C

void setup() {

  // Инициализируем часы
  time.begin();
  time.settime(time_seconds,
               time_minutes,
               time_hour,
               time_day,
               time_month,
               time_year);  //сек, мин, час, число, месяц, год, день недели.

  servo.attach(SERVO_PIN);
  servo.write(0);
  servo.detach();

  pinMode(A1, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  LcdInit(10, 9, 8, 7, 6);  /*10 - CS,
                              09 - RESET,
                              08 - D/C,
                              07 - CLK,
                              06 - DATA */

  if (!bmp.begin(0x76)) {
    while (1);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

byte read_btn() {
  boolean button2 = !digitalRead(A2);
  boolean button1 = !digitalRead(A1);
  boolean button3 = !digitalRead(A3);

  if (button2 == 1 && flag_set == 0 && millis() - last_button > 200) {
    flag_set == 1;
    set_on_flag = !set_on_flag;
    Mode_graph += 1;
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    //delay(500);
    last_button = millis();
  }

  if (button2 == 0 && flag_set == 1) {
    flag_set == 0;
    set_on_flag = !set_on_flag;
  }

  if (button1 == 1 && butt_flag == 0 && millis() - last_button > 200) {
    butt_flag = 1;
    flag = flag + 1;
    last_button = millis();
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  }
  if (button1 == 0 && butt_flag == 1) {
    butt_flag = 0;

  }
  if (button3 == 1 && butt_flag == 0 && millis() - last_button > 200) {
    butt_flag = 1;
    flag = flag - 1;
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(500);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    //delay(1000);
    last_button = millis();
  }
  if (button3 == 0 && butt_flag == 1) {
    butt_flag = 0;
  }
  if (flag > 3) {
    flag = 0;
  }
  if (flag < 0) {
    flag = 3;
  }
  if (Mode_graph > 24) {
    Mode_graph = 0;
  }
}

void check_feeder() {

  //Проверяем не пришло ли время покормить животное
  if (((time.Hours == feed_hour_1) && (time.minutes == feed_minute_1) && (time.seconds == 00))
      || ((time.Hours == feed_hour_2) && (time.minutes == feed_minute_2) && (time.seconds == 00))
      || ((time.Hours == feed_hour_3) && (time.minutes == feed_minute_3) && (time.seconds == 00))
     )
  {
    servo.attach(SERVO_PIN);
    servo.write(90);
    delay(500);
    servo.write(0);
    delay(500);
    servo.detach();
  }
  else delay(13);
}

void draw_main_scr() {
  LcdPageONE();
  do {
    LcdRoundRect(0, 0, 101, 64, 3, ON);

    //draw cell
    LcdRoundRect(2, 2, 14, 14, 3, ON);
    LcdBitmap(4, 4, cell_wht, ON);

    //draw feeder
    LcdRoundRect(17, 2, 34, 14, 3, ON);
    LcdBitmap(19, 4, feeder_empty, ON);
    LcdBitmap(29, 4, feeder_empty, ON);
    LcdBitmap(39, 4, feeder_empty, ON);

    //draw timer
    LcdRoundRect(53, 2, 48, 14, 3, ON);
    LcdBitmap(55, 4, timer_off, ON);
    LcdsetFont(font_5x8);
    LcdGotoXY(66, 6);
    LcdPrint(time.gettime("d.m"), ON, 1);

    //draw pressure
    LcdRoundRect(2, 48, 50, 14, 3, ON);
    LcdBitmap(4, 50, pressure, ON);
    LcdsetFont(font_5x8);
    LcdGotoXY(14, 52);
    float press_f = bmp.readPressure() / 133.3;
    char str_press[6];
    dtostrf(press_f, 4, 2, str_press);
    LcdPrint(str_press, ON, 1);

    //draw temp
    LcdRoundRect(54, 48, 45, 14, 3, ON);
    LcdBitmap(56, 50, temperature, ON);
    LcdsetFont(font_5x8);
    LcdGotoXY(67, 52);

    float temp_f = bmp.readTemperature();
    char str_temp[6];
    /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
    dtostrf(temp_f, 4, 2, str_temp);
    LcdPrint(str_temp, ON, 1);

    LcdGotoXY(7, 24);
    LcdsetFont(font_12x16_rus);
    LcdPrint(time.gettime("H:i:s"), ON, 1);
  }
  while (LcdPageTWO());
  delay(1000);
}

void draw_press_graph() {
  LcdPageONE();
  do {
    LcdRoundRect(0, 0, 101, 64, 3, ON);
    LcdsetFont(font_5x8);
    LcdGotoXY(3, 3);
    LcdPrint("Давление:", ON, 1);
    buff_val4 = set_col(press_mapped, Mode_graph, 0);
    LcdGotoXY(56, 3);
    LcdPrint(buff_val4, ON, 1);
    LcdGotoXY(81, 3);
    LcdPrint(min_mapped_press, ON, 1);
    LcdGotoXY(81, 12);
    LcdPrint(max_mapped_press, ON, 1);
  }
  while (LcdPageTWO());
  delay(1000);
}

void draw_temp_graph() {
  LcdPageONE();
  do {
    LcdRoundRect(0, 0, 101, 64, 3, ON);
    LcdsetFont(font_5x8);
    LcdGotoXY(3, 3);
    LcdPrint("Температура:", ON, 1);
    buff_val4 = set_col(temp_mapped, Mode_graph, 1);
    LcdGotoXY(74, 3);
    LcdPrint(buff_val4, ON, 1);
    LcdGotoXY(88, 3);
    LcdPrint(min_mapped_temp, ON, 1);
    LcdGotoXY(88, 12);
    LcdPrint(max_mapped_temp, ON, 1);
  }
  while (LcdPageTWO());
  delay(1000);
}

void draw_settings_scr() {
  LcdPageONE();
  do {
      LcdsetFont(font_5x8);
      LcdRoundRect(0, 0, 101, 64, 3, ON);
      LcdGotoXY(3, 3);
      LcdPrint("Настройки:", ON, 1);
      LcdGotoXY(10, 12);
      LcdPrint("Кормушка", ON, 1);
      LcdGotoXY(10, 21);
      LcdPrint("Время", ON, 1);
  }
  while (LcdPageTWO());
  delay(1000);
}

void temp_graph() {

  temp = aver_temp();                          // найти текущее давление по среднему арифметическому
  for (byte i = 0; i < 23; i++) {                   // счётчик от 0 до 5 (да, до 5. Так как 4 меньше 5)
    temp_array[i] = temp_array[i + 1];     // сдвинуть массив давлений КРОМЕ ПОСЛЕДНЕЙ ЯЧЕЙКИ на шаг назад
  }
  temp_array[23] = temp;

  max_mapped_temp = temp_array[0];
  min_mapped_temp = temp_array[0];

  for (byte i = 0; i < 24; i++) {                   // счётчик от 0 до 5 (да, до 5. Так как 4 меньше 5)
    if (temp_array[i] > max_mapped_temp) {
      max_mapped_temp = temp_array[i];
    }
    if (temp_array[i] < min_mapped_temp) {
      min_mapped_temp = temp_array[i];
    }
  }
  for (byte i = 0; i < 24; i++) {                   // счётчик от 0 до 5 (да, до 5. Так как 4 меньше 5)
    temp_mapped[i] = map(temp_array[i], min_mapped_temp - 10, max_mapped_temp + 10, 7, 63);
  }
}

long aver_temp() {
  temp = 0;
  for (byte i = 0; i < 10; i++) {
    temp += bmp.readTemperature();
  }
  aver_temper = temp / 10;
  return aver_temper;
}

long aver_sens() {
  pressure_val = 0;
  for (byte i = 0; i < 10; i++) {
    pressure_val += bmp.readPressure();
  }
  aver_pressure = pressure_val / 10;
  return aver_pressure;
}

void get_approx() {

  pressure_val = aver_sens();                          // найти текущее давление по среднему арифметическому
  for (byte i = 0; i < 23; i++) {                   // счётчик от 0 до 5 (да, до 5. Так как 4 меньше 5)
    pressure_array[i] = pressure_array[i + 1];     // сдвинуть массив давлений КРОМЕ ПОСЛЕДНЕЙ ЯЧЕЙКИ на шаг назад
  }
  pressure_array[23] = pressure_val;

  min_mapped_press = pressure_array[0] / 133.3;
  max_mapped_press = pressure_array[0] / 133.3;

  for (byte i = 0; i < 24; i++) {                   // счётчик от 0 до 5 (да, до 5. Так как 4 меньше 5)
    if (pressure_array[i] / 133.3 > max_mapped_press) {
      max_mapped_press = pressure_array[i] / 133.3 ;
    }
    if (pressure_array[i] / 133.3  < min_mapped_press) {
      min_mapped_press = pressure_array[i] / 133.3 ;
    }
  }
  for (byte i = 0; i < 24; i++) {                   // счётчик от 0 до 5 (да, до 5. Так как 4 меньше 5)
    press_mapped[i] = map(pressure_array[i] / 133.3, min_mapped_press - 10, max_mapped_press + 10, 7, 63); // сдвинуть массив давлений КРОМЕ ПОСЛЕДНЕЙ ЯЧЕЙКИ на шаг назад
  }


  // последний элемент массива теперь - новое давление
  sumX = 0;
  sumY = 0;
  sumX2 = 0;
  sumXY = 0;
  for (int i = 18; i < 24; i++) {                    // для всех элементов массива
    sumX += time_array[i];
    sumY += (long)pressure_array[i];
    sumX2 += time_array[i] * time_array[i];
    sumXY += (long)time_array[i] * pressure_array[i];
  }
  a = 0;
  a = (long)6 * sumXY;             // расчёт коэффициента наклона приямой
  a = a - (long)sumX * sumY;
  a = (float)a / (6 * sumX2 - sumX * sumX);
  delta = a * 6;                   // расчёт изменения давления
  approx = map(delta, -250, 250, 100, -100);  // пересчитать в угол поворота сервы
  //Serial.println(String(a) + " " + String(sumX));
}

int set_col(int arr[], int num, boolean mode) {
  for (byte i = 0; i < 24; i++) {
    LcdVLine((i + 1) * 4, 8 + (63 - arr[i]), arr[i], ON);
    if (num == i) {
      LcdCircle((i + 1) * 4, 8 + (63 - arr[i]) - 4, 2, ON);
      if (!mode) {
        buff_val3 = pressure_array[i] / 133.3;
      }
      else{
        buff_val3 = temp_array[i];
      }
    }
  }
  return buff_val3;
}

void loop() {

  if (hour_timer.isReady()) {
    get_approx();
    temp_graph();
    //SaveEEPROM();
  }

  if (buttons_timer.isReady()) {
    read_btn();
  }

  if (draw_scr_timer.isReady()) {

    if (flag == 0) {
      draw_main_scr();
    }

    if (flag == 1) {
      draw_press_graph();
    }

    if (flag == 2) {
      draw_temp_graph();
    }

    if (flag == 3) {
      draw_settings_scr();
    }
  }
}
