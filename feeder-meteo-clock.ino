<<<<<<< HEAD
=======
// Подключаем библиотеки для работы
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
#include <GyverTimer.h>
#include <iarduino_RTC.h>
#include <Servo.h>
#include <Adafruit_BMP280.h>

#include <PCF8812_new.h>
<<<<<<< HEAD
=======
#include "cell_blk.h"
#include "cell_wht.h"
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
#include "feeder_empty.h"
#include "feeder_full.h"
#include "pressure.h"
#include "temperature.h"
#include "font_5x8.h"
#include "font_12x16_rus.h"

#define SERVO_PIN A0

// Инициализация переменных
byte feed_hour_1 = 9;
<<<<<<< HEAD
byte feed_minute_1 = 02;
//----------------------|
byte feed_hour_2 = 9;
byte feed_minute_2 = 04;
=======
byte feed_minute_1 = 00;
//----------------------|
byte feed_hour_2 = 9;
byte feed_minute_2 = 00;
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
//----------------------|
byte feed_hour_3 = 9;
byte feed_minute_3 = 00;
//----------------------|
<<<<<<< HEAD
byte time_hour = 8;
byte time_minutes = 59;
=======
byte time_hour = 14;
byte time_minutes = 43;
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
byte time_seconds = 00;
byte time_day = 06;
byte time_month = 04;
byte time_year = 20;

<<<<<<< HEAD
boolean butt_flag, flag_set, set_on_flag, feeder_flag;
=======
boolean butt_flag, flag_set, set_on_flag;
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
unsigned long pressure_val, aver_pressure,  pressure_array[24];
unsigned long min_mapped_press, max_mapped_press, last_button;
unsigned long sumX, sumY, sumX2, sumXY;
float a;
<<<<<<< HEAD
int aver_temper, mode_graph, buff_val, buff_val2, buff_val3, buff_val4, delta, temp;
int approx, min_mapped_temp, max_mapped_temp, servo_delay = 500, time_val, buff = 0.0;
int temp_array[24], time_array[24], temp_mapped[24], press_mapped[24];
byte sec_now, sec_buff = 0, graph_flag = 0, time_selector = 0, feed_selector = 0,  feed_val, feed_mem[3];

//GTimer_ms hour_timer(2000);
GTimer_ms hour_timer((long)60*60 * 1000);
=======
int aver_temper, Mode_graph, buff_val, buff_val2, buff_val3, buff_val4, delta, temp;
int flag, approx, min_mapped_temp, max_mapped_temp,  buff = 0.0;
int temp_array[24], time_array[24], temp_mapped[24], press_mapped[24];
byte sec_now, sec_buff = 0;

GTimer_ms hour_timer(2000);
//GTimer_ms hour_timer((long)60*60 * 1000);
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
GTimer_ms draw_scr_timer(1 * 1000);
GTimer_ms buttons_timer(500);


iarduino_RTC time(RTC_DS1302, 13, 12, 11); /*13 PIN - RST
                                          11 PIN - DAT
                                          12 PIN - CLK */
Servo servo;
Adafruit_BMP280 bmp; // I2C

void setup() {
<<<<<<< HEAD
  for (byte i = 0; i < 3; i++) {
    feed_mem[i] = 0;
  }
=======
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16

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

<<<<<<< HEAD
void read_graph_btn() {
  boolean button2 = !digitalRead(A2);

  if (button2 == 1 && flag_set == 0 && millis() - last_button > 200) {
    flag_set == 1;
    graph_flag += 1;
=======
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
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
    last_button = millis();
  }

  if (button2 == 0 && flag_set == 1) {
    flag_set == 0;
<<<<<<< HEAD
  }
  if (graph_flag > 4) graph_flag = 0;
}

void read_graph_btn_state() {
  boolean btn_left = !digitalRead(A1);
  boolean btn_right = !digitalRead(A3);

  if (btn_left == 1 && butt_flag == 0 && millis() - last_button > 200) {
    butt_flag = 1;
    mode_graph -= 1;
    last_button = millis();
  }
  if (btn_left == 0 && butt_flag == 1) {
    butt_flag = 0;
  }

  if (btn_right == 1 && butt_flag == 0 && millis() - last_button > 200) {
    butt_flag = 1;
    mode_graph += 1;
    last_button = millis();
  }
  if (btn_right == 0 && butt_flag == 1) {
    butt_flag = 0;
  }
}

void read_time_selector() {
  boolean btn_right = !digitalRead(A1);

  if (btn_right == 1 && flag_set == 0 && millis() - last_button > 200) {
    flag_set == 1;
    time_selector += 1;
    if (time_selector > 6) time_selector = 0;
    last_button = millis();
  }

  if (btn_right == 0 && flag_set == 1) {
    flag_set == 0;
  }
}

void read_time_changer() {
  boolean btn_left = !digitalRead(A3);

  if (btn_left == 1 && flag_set == 0 && millis() - last_button > 200) {
    flag_set == 1;
    if (time_selector == 6)time_val += 100;
    else time_val += 1;
    if (time_selector == 0) {
      if (time_val > 24) time_val = 0;
      time.settime(-1,
                   -1,
                   time_val);
    }

    if (time_selector == 1) {
      if (time_val > 59) time_val = 0;
      time.settime(-1,
                   time_val,
                   -1);
    }

    if (time_selector == 2) {
      if (time_val > 59) time_val = 0;
      time.settime(time_val,
                   -1,
                   -1);
    }

    if (time_selector == 3) {
      if (time_val > 31) time_val = 0;
      time.settime(-1,
                   -1,
                   -1,
                   time_val,
                   -1,
                   -1);
    }

    if (time_selector == 4) {
      if (time_val > 12) time_val = 0;
      time.settime(-1,
                   -1,
                   -1,
                   -1,
                   time_val,
                   -1);
    }

    if (time_selector == 5) {
      if (time_val > 99) time_val = 0;
      time.settime(time_val,
                   -1,
                   -1,
                   -1,
                   -1,
                   -1,
                   time_val);
    }

    if (time_selector == 6) {
      if (time_val > 1500) time_val = 0;
      servo_delay = time_val;
    }

    last_button = millis();
  }

  if (btn_left == 0 && flag_set == 1) {
    flag_set == 0;
  }
}

void run_servo() {
  servo.attach(SERVO_PIN);
  servo.write(90);
  delay(servo_delay);
  servo.write(0);
  delay(servo_delay);
  servo.detach();
}

void check_feeder() {

  //Проверяем не пришло ли время покормить животное
  if ((time.Hours == feed_hour_1)
      && (time.minutes == feed_minute_1)
      && (feeder_flag == 0)) {
    feeder_flag = 1;
    run_servo();
    feed_mem[0] = 1;
  }

  if ((time.Hours == feed_hour_2)
      && (time.minutes == feed_minute_2)
      && (feeder_flag == 0)) {
    feeder_flag = 1;
    run_servo();
    feed_mem[1] = 1;
  }

  if ((time.Hours == feed_hour_3)
      && (time.minutes == feed_minute_3)
      && (feeder_flag == 0)) {
    feeder_flag = 1;
    run_servo();
    feed_mem[2] = 1;
  }

  if ((time.minutes == feed_minute_1 + 1)
      || (time.minutes == feed_minute_2 + 1)
      || (time.minutes == feed_minute_3 + 1)) {
    feeder_flag = 0;
  }
=======
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
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
}

void draw_main_scr() {
  LcdPageONE();
  do {
    LcdRoundRect(0, 0, 101, 64, 3, ON);

    //draw feeder
    LcdRoundRect(6, 2, 35, 14, 3, ON);

    if (feed_mem[0] == 0)LcdBitmap(8, 4, feeder_empty, ON);
    if (feed_mem[0] == 1)LcdBitmap(8, 4, feeder_full, ON);
    if (feed_mem[1] == 0)LcdBitmap(18, 4, feeder_empty, ON);
    if (feed_mem[1] == 1)LcdBitmap(18, 4, feeder_full, ON);
    if (feed_mem[2] == 0)LcdBitmap(28, 4, feeder_empty, ON);
    if (feed_mem[2] == 1)LcdBitmap(28, 4, feeder_full, ON);

    //draw date
    LcdRoundRect(43, 2, 51, 14, 3, ON);
    LcdsetFont(font_5x8);
<<<<<<< HEAD
    LcdGotoXY(45, 6);
    LcdPrint(time.gettime("d.m.y"), ON, 1);

    //draw time
    LcdGotoXY(7, 16);
    LcdsetFont(font_12x16_rus);
    LcdPrint(time.gettime("H:i:s"), ON, 1);

    //draw time
    LcdGotoXY(7, 33);
    LcdsetFont(font_5x8);
    LcdPrint(approx, ON, 1);
=======
    LcdGotoXY(66, 6);
    LcdPrint(time.gettime("d.m"), ON, 1);
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16

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

<<<<<<< HEAD

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
    buff_val4 = set_col(press_mapped, mode_graph, 0);
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
    buff_val4 = set_col(temp_mapped, mode_graph, 1);
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

void draw_set_time_scr(byte set_time) {
  LcdPageONE();
  do {
    LcdsetFont(font_5x8);
    LcdRoundRect(0, 0, 101, 64, 3, ON);
    LcdGotoXY(3, 3);
    LcdPrint("Время,дата,корм", ON, 1);
    LcdGotoXY(26, 19);
=======
    LcdGotoXY(7, 24);
    LcdsetFont(font_12x16_rus);
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
    LcdPrint(time.gettime("H:i:s"), ON, 1);
    LcdGotoXY(26, 35);
    LcdPrint(time.gettime("d.m.y"), ON, 1);
    LcdGotoXY(26, 51);
    LcdPrint(servo_delay, ON, 1);

    if (set_time == 0) {
      LcdGotoXY(26 + (18 * set_time), 11);
      LcdPrint("*", ON, 1);
    }

    if (set_time == 1) {
      LcdGotoXY(26 + (18 * set_time), 11);
      LcdPrint("*", ON, 1);
    }

    if (set_time == 2) {
      LcdGotoXY(26 + (18 * set_time), 11);
      LcdPrint("*", ON, 1);
    }

    if (set_time == 3) {
      LcdGotoXY(26 + (18 * 0), 27);
      LcdPrint("*", ON, 1);
    }
    if (set_time == 4) {
      LcdGotoXY(26 + (18 * 1), 27);
      LcdPrint("*", ON, 1);
    }
    if (set_time == 5) {
      LcdGotoXY(26 + (18 * 2), 27);
      LcdPrint("*", ON, 1);
    }
    if (set_time == 6) {
      LcdGotoXY(26 + (18 * 0), 43);
      LcdPrint("*", ON, 1);
    }
  }
  while (LcdPageTWO());
  delay(1000);
}

<<<<<<< HEAD
void read_feed_selector() {

  boolean btn_right = !digitalRead(A1);

  if (btn_right == 1 && flag_set == 0 && millis() - last_button > 200) {
    flag_set == 1;
    feed_selector += 1;
    if (feed_selector > 5) feed_selector = 0;
    last_button = millis();
  }

  if (btn_right == 0 && flag_set == 1) {
    flag_set == 0;
  }
}

void read_feed_changer() {

  boolean btn_left = !digitalRead(A3);

  if (btn_left == 1 && flag_set == 0 && millis() - last_button > 200) {
    flag_set == 1;
    feed_val += 1;

    if (feed_selector == 0) {
      if (feed_val > 24) feed_val = 0;
      feed_hour_1 = feed_val;
    }

    if (feed_selector == 1) {
      if (feed_val > 59) feed_val = 0;
      feed_minute_1 = feed_val;
    }

    if (feed_selector == 2) {
      if (feed_val > 24) feed_val = 0;
      feed_hour_2 = feed_val;
    }

    if (feed_selector == 3) {
      if (feed_val > 59) feed_val = 0;
      feed_minute_2 = feed_val;
    }

    if (feed_selector == 4) {
      if (feed_val > 24) feed_val = 0;
      feed_hour_3 = feed_val;
    }

    if (feed_selector == 5) {
      if (feed_val > 59) feed_val = 0;
      feed_minute_3 = feed_val;
    }

    last_button = millis();
  }

  if (btn_left == 0 && flag_set == 1) {
    flag_set == 0;
  }
}

void draw_feed_scr(byte feed_controller) {
  LcdPageONE();
  do {

    LcdsetFont(font_5x8);
    LcdRoundRect(0, 0, 101, 64, 3, ON);
    LcdGotoXY(25, 2);
    LcdPrint("Настройка", ON, 1);

    LcdGotoXY(30, 8);
    LcdPrint("кормления", ON, 1);

    LcdGotoXY(3, 22);
    LcdPrint("h1 = ", ON, 1);
    LcdGotoXY(32, 22);
    LcdPrint(feed_hour_1, ON, 1);
    if (feed_selector == 0) {
      LcdGotoXY(32, 16);
      LcdPrint("*", ON, 1);
    }

    LcdGotoXY(50, 22);
    LcdPrint("m1 = ", ON, 1);
    LcdGotoXY(79, 22);
    LcdPrint(feed_minute_1, ON, 1);
    if (feed_selector == 1) {
      LcdGotoXY(79, 16);
      LcdPrint("*", ON, 1);
    }

    LcdGotoXY(3, 39);
    LcdPrint("h2 = ", ON, 1);
    LcdGotoXY(32, 39);
    LcdPrint(feed_hour_2, ON, 1);
    if (feed_selector == 2) {
      LcdGotoXY(32, 33);
      LcdPrint("*", ON, 1);
    }

    LcdGotoXY(50, 39);
    LcdPrint("m2 = ", ON, 1);
    LcdGotoXY(79, 39);
    LcdPrint(feed_minute_2, ON, 1);
    if (feed_selector == 3) {
      LcdGotoXY(79, 33);
      LcdPrint("*", ON, 1);
    }

    LcdGotoXY(3, 56);
    LcdPrint("h3 = ", ON, 1);
    LcdGotoXY(32, 56);
    LcdPrint(feed_hour_3, ON, 1);
    if (feed_selector == 4) {
      LcdGotoXY(32, 49);
      LcdPrint("*", ON, 1);
    }

    LcdGotoXY(50, 56);
    LcdPrint("m3 = ", ON, 1);
    LcdGotoXY(79, 56);
    LcdPrint(feed_minute_3, ON, 1);
    if (feed_selector == 5) {
      LcdGotoXY(79, 49);
      LcdPrint("*", ON, 1);
    }

=======
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
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
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
<<<<<<< HEAD
      else {
=======
      else{
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
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
<<<<<<< HEAD
    read_graph_btn();
  }

  if (draw_scr_timer.isReady()) {
    if (feed_mem[0] == 1 && feed_mem[1] == 1 && feed_mem[2] == 1) {
      feed_mem[0] = 0;
      feed_mem[1] = 0;
      feed_mem[2] = 0;
    }
    check_feeder();

    if (graph_flag == 0) {
      draw_main_scr();
    }

    if (graph_flag == 1) {

      read_graph_btn_state();

      if (mode_graph > 24) {
        mode_graph = 0;
      }

      if (mode_graph < 0) {
        mode_graph = 24;
      }

      draw_press_graph();
    }

    if (graph_flag == 2) {
      read_graph_btn_state();

      if (mode_graph > 24) {
        mode_graph = 0;
      }

      if (mode_graph < 0) {
        mode_graph = 24;
      }

      draw_temp_graph();
    }

    if (graph_flag == 3) {
      read_time_selector();
      if (time_selector == 0) {
        time_val = time.Hours;
        read_time_changer();
      }
      if (time_selector == 1) {
        time_val = time.minutes;
        read_time_changer();
      }
      if (time_selector == 2) {
        time_val = time.seconds;
        read_time_changer();
      }

      if (time_selector == 3) {
        time_val = time.day;
        read_time_changer();
      }
      if (time_selector == 4) {
        time_val = time.month;
        read_time_changer();
      }
      if (time_selector == 5) {
        time_val = time.year;
        read_time_changer();
      }
      if (time_selector == 6) {
        time_val = servo_delay;
        read_time_changer();
      }
      draw_set_time_scr(time_selector);
    }

    if (graph_flag == 4) {

      read_feed_selector();

      if (feed_selector == 0) {
        feed_val = feed_hour_1;
        read_feed_changer();
      }
      if (feed_selector == 1) {
        feed_val = feed_minute_1;
        read_feed_changer();
      }

      if (feed_selector == 2) {
        feed_val = feed_hour_2;
        read_feed_changer();
      }
      if (feed_selector == 3) {
        feed_val = feed_minute_2;
        read_feed_changer();
      }

      if (feed_selector == 4) {
        feed_val = feed_hour_3;
        read_feed_changer();
      }
      if (feed_selector == 5) {
        feed_val = feed_minute_3;
        read_feed_changer();
      }

      draw_feed_scr(feed_selector);
=======
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
>>>>>>> f23bed90377a132aca0aeca0aef31af2cdcb7e16
    }
  }
}
