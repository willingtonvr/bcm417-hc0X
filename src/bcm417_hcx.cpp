#include "Arduino.h"  /* Importar todas las funciones de Arduino*/
#include "bcm417_hcx.hpp"

/* Constructores */
bcm417_hcx::bcm417_hcx(){
  /* el puerto por defecto es el 1*/
  bcm417_hcx(1,9600,5,6);
}
bcm417_hcx::bcm417_hcx(int port,int baud,int power_pin,int key_pin ){
  conectado=false;
  encendido=false;
  baud_rate=baud;
  pin_key=key_pin;
  pin_power=power_pin;
  s_port=port;

  switch (s_port) {
    case 0: Serial.begin(baud_rate);
    curSerial= &Serial;
    break;
    case 1: Serial1.begin(baud_rate);
    curSerial= &Serial1;
    break;
#ifdef __AVR_ATmega2560__ // si es un MEGA tiene estos puertos
    case 2: Serial2.begin(baud_rate);
    curSerial= &Serial2;
    break;
    case 3: Serial3.begin(baud_rate);
    curSerial= &Serial3;
    break;
#endif

  }




}
