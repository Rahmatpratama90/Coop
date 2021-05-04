#include <DHT.h> //library DHT
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
#include <Dimmer.h>
#include <PID_v1.h>
#include <LiquidCrystal.h>

const int pin_RS = 30;
const int pin_EN = 32;
const int pin_d4 = 22;
const int pin_d5 = 24;
const int pin_d6 = 26;
const int pin_d7 = 28;
const int pin_BL = A10;

#define ldr_apin1 A4 
#define ldr_apin2 A3
#define DHTPIN1 A0
#define DHTPIN2 A1
#define DHTPIN3 A2
#define DHTTYPE DHT11
#define windPin_1 7 // 6 and 7 Receive the data from sensor
#define windPin_2 6 // 6 and 7 Receive the data from sensor

const int chipSelect = 4;
int pinCS = 53;
int pinSCK = 52;
int pinMOSI = 51;
int pinMISO = 50;

Dimmer pemanas(10);
Dimmer lamp1(9, DIMMER_RAMP, 3 ,50);
Dimmer kipas1(11,DIMMER_RAMP, 3 , 50);
Dimmer kipas2(12,DIMMER_RAMP , 3, 50);

//Pin
byte sensorPin = A0;
byte Pemanas = 2;


LiquidCrystal lcd( pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);

double q;
//Specify the links and initial tuning parameters

unsigned long serialTime; //this will help us know when to talk with processing

int display_number = 1;
double pidkipas1,pidkipas2;
double output_pid_pemanas;
double output_pid_kipas;
double output_pid_lampu;
float speedwind_1= 0;
float speedwind_2 = 0;
float speedwind = 0; // Wind speed (m/s)
double hum_1, temp_1, hum_2, temp_2, hum_3, temp_3;//deklarasi variabel
  //Define Variables we'll be connecting to
double Input, Output , Input2 ,InputP1,InputP2,InputP3,InpInputP1 , InputK1,InputK2,InputLDR,InputLDR2,InputLDRMean, InputKMean,lmp1,lmp2,lmp,output_pid,mapping1;

//double windPin_1,windPin_2;
unsigned int Sample = 0; // Sample number
unsigned int counter = 0; // /W counter for sensor
unsigned int RPM = 0; // Revolutions per minute

double output_pid_kipas2;
double mapping;
double Kp=0.1, Ki=0.01, Kd=5;
double Kplampu = 6, Kilampu=1, Kdlampu=1;
double Kppemanas=10, Kipemanas=5, Kdpemanas=1;
double Setpoint_kipas = 30.0;
double Setpoint_pemanas = 31.0;
double Setpoint_Lampu = 500.0;
//double Setpoint_Lampu = 330.0;

DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2,DHTTYPE);
DHT dht3(DHTPIN3,DHTTYPE);
RTC_DS3231 rtc;
File myFile;
String dataString;
String judulData;
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

String nama_file ;
String Date;
String Time;
String dateData;
//LCD pin to Arduino

double  cahaya_1,cahaya_2;
 int output_kipas;

const float pi = 3.14159265; // pi number
int period = 1000; // Measurement period (miliseconds)
int delaytime = 1000; // Time between samples (miliseconds)
int radio = 90; // Distance from center windmill to outer cup (mm)
int jml_celah = 18; // jumlah celah sensor

// Variable definitions
unsigned int counter_1 = 0; // B/W counter for sensor
unsigned int RPM_1 = 0; // Revolutions per minute

unsigned int counter_2 = 0; // B/W counter for sensor
unsigned int RPM_2 = 0; // Revolutions per minute

PID pidPemanas ( &temp_1 , &output_pid_pemanas, &Setpoint_pemanas, Kppemanas, Kipemanas, Kdpemanas, DIRECT);

PID pidLampu( &cahaya_1, &output_pid_lampu, &Setpoint_Lampu,Kplampu,Kilampu,Kdlampu, REVERSE);

PID pidKipas ( &InputK1, &output_pid_kipas, &Setpoint_kipas, Kp, Ki, Kd, DIRECT);
PID pidKipas2 ( &InputK2, &output_pid_kipas2, &Setpoint_kipas, Kp, Ki, Kd, DIRECT);


 
