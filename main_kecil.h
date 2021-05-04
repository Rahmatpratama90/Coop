#include "kandang_kecil.h"

void pid_lampu_setup() {
  //Serial.begin(9600);
  lamp1.begin(); 
  pidLampu.SetMode(AUTOMATIC);
}

void pid_lampu_loop(){ 
   cahaya_1 = analogRead(ldr_apin1);
   pidLampu.Compute();
   lmp = map(output_pid_lampu,0,255 , 0, 100);
   lamp1.set(lmp);
   
  
}
 
void pid_kipas_setup() {
  //Serial.begin(9600);
  InputK1 = analogRead(windPin_1);
  InputK2 = analogRead(windPin_2);
  kipas1.begin();
  kipas2.begin();
  //turn the PID on
  pidKipas.SetMode(AUTOMATIC);
}
  
void pid_kipas_loop() { //input anemo 
  Setpoint_kipas = Setpoint_pemanas;
  if (temp_1 < Setpoint_kipas) { //0 
    output_kipas = 50;
    kipas1.set(50);
    kipas2.set(50);
    Serial.println("Kipas = 50");
    speedwind_1 = 50;
    speedwind_2 = 50;
  }
  else {//50
    output_kipas = 100;
    kipas1.set(100);
    kipas2.set(100);
    Serial.println("Kipas = 100");
    speedwind_1 = 100;
    speedwind_2 = 100;
  }
  
  /* InputK1 = analogRead(windPin_1);
    InputK2 = analogRead(windPin_2);
    pidKipas.Compute();
    pidKipas2.Compute();
    pidkipas1  = map(output_pid_kipas,0,255, 25, 100);
    pidkipas2 = map(output_pid_kipas2,0,255,25,100);
    kipas2.set(pidkipas2);
    kipas1.set(pidkipas1); 
    Serial.println(pidkipas1); */
} 

void pid_pemanas_setup(){
  //Serial.begin(9600);
  pidPemanas.SetMode(AUTOMATIC);
  pemanas.begin();
  
  dht1.begin();
  dht2.begin();
  dht3.begin(); 
}

void pid_pemanas_loop(){ //dht input
  hum_1 = dht1.readHumidity();//baca kelembaban
  temp_1 = dht1.readTemperature();//baca suhu
  hum_2 = dht2.readHumidity();//baca kelembaban
  temp_2 = dht3.readTemperature();//baca suhu
  hum_3 = dht3.readHumidity();//baca kelembaban
  temp_3 = dht3.readTemperature();//baca suhu
  
  pidPemanas.Compute();
 
  mapping1 = map(output_pid_pemanas,0,255,0,100);
  pemanas.set(mapping1);
}
  
void LCD_pid_loop() {  
  int x;
  x = analogRead(pin_BL);

  Serial.print("Button : ");
  Serial.println(x);
  Serial.println("");
  lcd.setCursor(10,2);
  lcd.clear();
  
  if (0 < x && x < 200) { //Kanan
    lcd.print("Kanan");
    if (display_number == 3){
      display_number = 1;
    }
    else{
      display_number += 1;
    } 
  }
  
  if ( display_number == 1) {
     lcd.setCursor(0,0);
     lcd.print("Temp");
     
     lcd.setCursor(0,1);
     lcd.print(temp_1); //ambil ini
     
     lcd.setCursor(6,0);
     lcd.print(output_pid_pemanas,1);
    
     lcd.setCursor(12,0);
     lcd.print(Setpoint_pemanas,1);
     
     lcd.setCursor(6,1);
     lcd.print(temp_2,1);
     
     lcd.setCursor(11,1 );
     //lcd.print(temp_3  ,1);
     lcd.print(mapping1,1);
   
  //Serial.println(Setpoint);
     if (701  < x && x < 980 ){ //left 
        Setpoint_pemanas += 1;
     }
     else if ( 600 < x && x < 700){ //select
        Setpoint_pemanas -=1; 
     }
  }
  else if (display_number == 2) {
     lcd.setCursor(0,0);
     lcd.print("Humidity");

     lcd.setCursor(0,1);
     lcd.print(hum_1,1);//ambil ini
     lcd.setCursor(6,1);
     lcd.print(hum_2,1);
     lcd.setCursor(12,1);
     lcd.print(hum_3,1);
  }
     
  else if (display_number == 3) {
     lcd.setCursor(0,0);
     lcd.print("Light");
     lcd.setCursor(0,1);
     lcd.print(cahaya_1 );
     lcd.setCursor(7,1);
     lcd.print(cahaya_2);
     lcd.setCursor(11,0);
     lcd.print(Setpoint_Lampu,1);
     if (701 < x && x < 980 ){ //left 
        Setpoint_Lampu += 100;
     }
     else if ( 600 < x && x < 700){ //select
        Setpoint_Lampu -=100; 
     }
     //ambil ini
  }
 
  /*else if (display_number == 4) {
     lcd.setCursor(0,0);
     lcd.print("Anemo");
     lcd.setCursor(0,1);
    
     lcd.print(speedwind_1);
     lcd.setCursor(8,0);
     lcd.print(q );
     lcd.setCursor(8,2);
     lcd.print(speedwind_2);
     
     if (400 < x && x < 600 ){ //left 
        q += 1;
     }
     else if ( 600 < x && x < 800){ //select
        q -=1; 
     }
  }   */
} 
  
void display_sensor(){
 /*Serial.print("Anemometer \t");
 Serial.print(speedwind_1);
 Serial.print(" [m/s] \t");
 Serial.print(speedwind_2);
 Serial.println(" [m/s] \t"); */
 Serial.print("Display Number : " );
 
 Serial.println(display_number);
 Serial.print("Output PID Lampu ");
 Serial.println(lmp);
 Serial.print("Output PID Kipas1 : ");
 Serial.println(lmp); 
  Serial.print("Output PID Kipas2 : ");
 Serial.println(lmp);
 Serial.print("Output PID Pemanas : ");
 Serial.println(mapping1);
 
  /*Serial.println("dht \t");  
 Serial.println(hum_1);
 Serial.println("% ");
 Serial.println(temp_1);
 Serial.println("c \t");
 Serial.println(hum_2);
 Serial.println("% ");
 Serial.println(temp_2);
 Serial.println("c \t");
 Serial.println(hum_3);
 Serial.println("% ");
 Serial.println(temp_3);
  //Serial.println("c

  //Serial.println(); */

 Serial.print("LDR 1 : \t"); 
 Serial.print(cahaya_1);
 Serial.print(" | ");
 Serial.print("LDR 2 : \t");
 Serial.print(cahaya_2);
 Serial.println();
}

void nama_data(){
  judulData = "";
  judulData += "Date";
  judulData += "/";
  judulData += "Setpoint_kipas";
  judulData += "/";
  judulData += "speedwind_1";
  judulData += "/";
  judulData += "speedwind_2";
  judulData += "/";
  judulData += "Setpoint_pemanas";  
  judulData += "/";
  judulData += "hum_1";
  judulData += "/";
  judulData += "temp_1";
  judulData += "/";
  judulData += "hum_2";
  judulData += "/";
  judulData += "temp_2";
  judulData += "/";
  judulData += "hum_3";
  judulData += "/";
  judulData += "temp_3"; 
  judulData += "/";
  judulData += "Setpoint_Lampu";
  judulData += "/";  
  judulData += "cahaya_1";
  judulData += "/";
  judulData += "cahaya_2";
  judulData += "/";
  judulData += "output_pid_lampu";
  judulData += "/";
  judulData += "lmp";
  judulData += "/";
  judulData += "output_pid_pemanas";
  judulData += "/";
  judulData += "mapping1";
  judulData += "/";
  judulData += "output_kipas";
  
}

void log_data(){
  DateTime now = rtc.now();
  dateData = now.day()+now.month()+now.year()+now.hour()+now.minute()+now.second();
  dataString = "";
  dataString += dateData;
  dataString += "/";
  dataString += Setpoint_kipas;
  dataString += "/";
  dataString += speedwind_1;
  dataString += "/";
  dataString += speedwind_2;
  dataString += "/";
  dataString += Setpoint_pemanas;  
  dataString += "/";
  dataString += hum_1;
  dataString += "/";
  dataString += temp_1;
  dataString += "/";
  dataString += hum_2;
  dataString += "/";
  dataString += temp_2;
  dataString += "/";
  dataString += hum_3;
  dataString += "/";
  dataString += temp_3; 
  dataString += "/";
  dataString += Setpoint_Lampu;
  dataString += "/";  
  dataString += cahaya_1;
  dataString += "/";
  dataString += cahaya_2;
  dataString += "/";
  dataString += output_pid_lampu;
  dataString += "/";
  dataString += lmp;
  dataString += "/";
  dataString += output_pid_pemanas;
  dataString += "/";
  dataString += mapping1;
  dataString += "/";
  dataString += output_kipas;
}

void sd_setup() {    
  pinMode(pinCS, OUTPUT);
  pinMode(pinSCK, INPUT);
  pinMode(pinMOSI , INPUT);
  pinMode(pinMISO , OUTPUT);
  if (SD.begin()){
    Serial.print("SD card is ready to use.");
  } 
  else{
    Serial.print("SD card initialization failed");
    return;
  }
  nama_file = Date+".txt"; 
  myFile = SD.open(nama_file , FILE_WRITE);
  if (myFile) {
    nama_data();
    myFile.println(judulData);
    myFile.close(); // close the file
  }
  else {
    Serial.print("error opening"+nama_file);
  } 
}

void sd_loop() {
  myFile = SD.open(nama_file, FILE_WRITE);
  
  // if the file is available, write to it:
  if (myFile) {
    log_data();
    myFile.println(dataString);
    myFile.close();
    // print to the serial port too:
    // //Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening"+nama_file);
  }
} 

void rtc_setup () {
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
  }
  
  if (rtc.lostPower()) {
    //Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));     // following line sets the RTC to the date & time this sketch was compiled
    //Serial.println("apa gitu");    // Set the current date, and time in the following format:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));     // This line sets the RTC with an explicit date & time, for example to set
  }
  DateTime now = rtc.now();
  Date = now.day()+now.month()+now.year()+now.hour()+now.minute()+now.second();
}

void rtc_loop () {
   DateTime now = rtc.now();
   Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
   Serial.print(',');
   Serial.print(now.day(), DEC);
   Serial.print('/');
   Serial.print(now.month(), DEC);
   Serial.print('/');
   Serial.print(now.year(), DEC);
   Serial.print('\t');
   Serial.print(now.hour(), DEC);
   Serial.print(':');
   Serial.print(now.minute(), DEC);
   Serial.print(':');
   Serial.println(now.second(), DEC);

    //Serial.println();
    ////Serial.println();
}

void dht_loop() {
  float humi1  = dht1.readHumidity();
  float humi2 = dht2.readHumidity();
  float humi3 = dht3.readHumidity();
  // read temperature as Celcius
  float tempC1 = dht1.readTemperature();
  float tempC2 = dht2.readTemperature();
  float tempC3= dht3.readTemperature();
  
  // read temperature as Fahrenheit
  float tempF1 = dht1.readTemperature(true);
  float tempF2 =dht2.readTemperature(true);
  float tempF3 = dht3.readTemperature(true);
  // check if any reads failed
  
  if (isnan(humi1) || isnan(tempC1) || isnan(tempF1)) {
    Serial.println("Failed to read from DHT1 sensor!");
  } 
  else {
   Serial.print("Humidity1 : ");
   Serial.print(humi1);
   Serial.print("%");
   Serial.print("  |  "); 

   Serial.print("Temperature1 : ");
   Serial.print(tempC1);
   Serial.print("°C ~ ");
   Serial.println(tempF1);
    //Serial.println("°F");
  }
  if (isnan(humi2) || isnan(tempC2) || isnan(tempF2)) {
    Serial.println("Failed to read from DHT2 sensor!");
  } 
  else {
   Serial.print("Humidity2 : ");
   Serial.print(humi2);
   Serial.print("%");
   Serial.print("  |  "); 

   Serial.print("Temperature2 : ");
   Serial.print(tempC2);
   Serial.print("°C ~ ");
   Serial.println(tempF2);
    //Serial.println("°F");
  }
  if (isnan(humi3) || isnan(tempC3) || isnan(tempF3)) {
    Serial.println("Failed to read from DHT3 sensor!");
  } else {
   Serial.print("Humidity3 : ");
   Serial.print(humi3);
   Serial.print("%");
   Serial.print("  |  "); 
   Serial.print("Temperature3 : ");
   Serial.print(tempC3);
   Serial.print("°C ~ ");
   Serial.print(tempF3);
    //Serial.println("°F");
   Serial.println( "");
  }
}

void addcount(){
  counter_1++;
}

void addcount_1(){
  counter_1++;
}

void addcount_2(){
  counter_2++;
}

void RPMcalc(){
  RPM=((counter/jml_celah)*60)/(period/1000); // Calculate revolutions per minute (RPM)
}

void WindSpeed(){
  speedwind = ((2 * pi * radio * RPM)/60) / 1000; // Calculate wind speed on m/s
}

void windvelocity(){
  speedwind = 0;
  counter = 0;
  attachInterrupt(0, addcount, CHANGE);
  unsigned long millis();
  long startTime = millis();
  while(millis() < startTime + period) {}
  detachInterrupt(1);
}

/*void windvelocity_2()
{
  speedwind = 0;
  counter = 0;
  attachInterrupt(0, addcount_2, CHANGE);
  unsigned long millis();
  long startTime = millis();
  while(millis() < startTime + period) {}
  detachInterrupt(1);
}*/

void LCD_pid_setup(){
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("Proyek Fikih");
    lcd.setCursor(0,1);
    lcd.print("Press Key:");
}

void anemo_loop(){
  Sample++;
  Serial.println(Sample);
  Serial.println(": Start measurement…");
  windvelocity();
  //Serial.println(" finished.");
  Serial.print("Counter1: ");
  Serial.print(counter_1);
  Serial.print("  |  "); 
  //Serial.println(" finished.");
  Serial.print("Counter2: ");
  Serial.println(counter_2);

  RPMcalc();
    Serial.print("RPM1: ");
  Serial.print(RPM_1);
  Serial.print("  |  "); 
    Serial.print("RPM2: ");
  Serial.println(RPM_2);

  WindSpeed();  
    Serial.print("Wind speed1 : ");
  Serial.print(speedwind_1);
  Serial.print(" [m/s] ");
  Serial.print("  |  "); 
    Serial.print("Wind speed2 : ");
  Serial.print(speedwind_2);
  Serial.println(" [m/s]");
  //Serial.println();
}

void data_sensor(){
  
  
  hum_1 = dht1.readHumidity();//baca kelembaban
  temp_1 = dht1.readTemperature();//baca suhu
  hum_2 = dht2.readHumidity();//baca kelembaban
  temp_2 = dht2.readTemperature();//baca suhu
  hum_3 = dht3.readHumidity();//baca kelembaban
  temp_3 = dht3.readTemperature();//baca suhu

  cahaya_1 = analogRead(ldr_apin1);
  cahaya_2 = analogRead(ldr_apin2);
}
