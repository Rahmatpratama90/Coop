#include "main_kecil.h"

void setup()
{
  Serial.begin (9600); 
      LCD_pid_setup();
      rtc_setup();
  sd_setup(); //dht_setup(); apus kynya
  
  pid_pemanas_setup();
  pid_kipas_setup();
  pid_lampu_setup();

//   anemo_setup(); apus kynya
  delay(2000);
}

void loop(){
   rtc_loop();
   sd_loop();
   log_data();

   //anemo_loop(); //bikin dimmer gak jalan
  dht_loop(); //bikin kedip
   data_sensor(); //bikin kedip
   display_sensor(); //bikin kedip

   pid_lampu_loop();//sampe sni
   
   pid_kipas_loop();
   pid_pemanas_loop(); //bikin kedip
   LCD_pid_loop();
  
   
   //Serial.println("");

   delay(100);
}
