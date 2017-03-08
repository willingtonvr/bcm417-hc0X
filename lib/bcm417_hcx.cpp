#include "Arduino.h"  /* Importar todas las funciones de Arduino*/
#include "bcm417_hcx.hpp"
#include <stdio.h> // for size_t
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
  // arrancamos con el modulo apagado
  pinMode(pin_power,OUTPUT);
  pinMode(pin_key, OUTPUT);
  digitalWrite(pin_key, LOW);
  digitalWrite(pin_power, LOW);

  s_port=port;
// segun el puerto elegido se usa una refencia
// para que dentro del objeto se llame a la misma variable
// idependiente del numero de puerto que use
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


};
bool bcm417_hcx::encender(){
    digitalWrite(pin_power,HIGH);
    // se necesita una rutina para verificar si encendió
    return true;
};

int bcm417_hcx::available(){
  if (conectado) return curSerial->available();
  return 0;
};
char bcm417_hcx::read(){
  if (conectado) return curSerial->read();
  return 0;
};

size_t bcm417_hcx::readBytesUntil( char terminator, char *buffer, size_t length) {if (conectado) return curSerial->readBytesUntil( terminator, buffer, length); };  // as readBytes with terminator character
size_t bcm417_hcx::readBytesUntil( char terminator, uint8_t *buffer, size_t length) {if (conectado) return curSerial->readBytesUntil( terminator, buffer, length); };
String bcm417_hcx::readString() {if (conectado) return curSerial->readString();};
String bcm417_hcx::readStringUntil(char terminator) {if (conectado) return curSerial->readStringUntil(terminator);};
/* *todos los sabores de print */
/* implentacion dura y cruda por mapeo con control de conexion*/
size_t bcm417_hcx::print(const String &dato) {if (conectado) return curSerial->print(dato); };
size_t bcm417_hcx::print(const char dato[]) {if (conectado) return  curSerial->print(dato); };
size_t bcm417_hcx::print(char dato) {if (conectado) return  curSerial->print(dato) ;};
size_t bcm417_hcx::print(unsigned char dato, int base) { if (conectado) return  curSerial->print(dato,base); };
size_t bcm417_hcx::print(int dato, int base ) { if (conectado) return  curSerial->print(dato,base) ;};
size_t bcm417_hcx::print(unsigned int dato, int base)  { if (conectado) return  curSerial->print(dato,base); };
size_t bcm417_hcx::print(long dato, int base) { if (conectado) return  curSerial->print(dato,base) ;};
size_t bcm417_hcx::print(unsigned long dato , int base ){ if (conectado) return  curSerial->print(dato,base) ;};
size_t bcm417_hcx::print(double dato , int digits){ if (conectado) return  curSerial->print(dato,digits); };

size_t bcm417_hcx::println(const String &dato) {if (conectado) return  curSerial->println(dato) ;};
size_t bcm417_hcx::println(const char dato[]) {if (conectado) return  curSerial->println(dato) ;};
size_t bcm417_hcx::println(char dato) {if (conectado) return  curSerial->println(dato) ;};
size_t bcm417_hcx::println(unsigned char dato, int base) { if (conectado) return  curSerial->println(dato,base) ;};
size_t bcm417_hcx::println(int dato, int base ) { if (conectado) return  curSerial->println(dato,base) ;};
size_t bcm417_hcx::println(unsigned int dato, int base )  { if (conectado) return  curSerial->println(dato,base); };
size_t bcm417_hcx::println(long dato, int base ) { if (conectado) return  curSerial->println(dato,base) ;};
size_t bcm417_hcx::println(unsigned long dato , int base ){ if (conectado) return  curSerial->println(dato,base) ;};
size_t bcm417_hcx::println(double dato , int digits){ if (conectado) return  curSerial->println(dato,digits); };
size_t bcm417_hcx::println() { if (conectado) return  curSerial->println(); };
