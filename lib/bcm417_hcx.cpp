#include <Arduino.h>  /* Importar todas las funciones de Arduino*/
#include "bcm417_hcx.hpp"
#include <SoftwareSerial.h>
#include <stdio.h> // for size_t
/* Constructores */
bcm417_hcx::bcm417_hcx(){
  /* el puerto por defecto es el 1*/

  bcm417_hcx((uint8_t) 9,(uint8_t) 9600, (uint8_t)5,(uint8_t) 6,(uint8_t)2,(uint8_t) 3);

}
bcm417_hcx::bcm417_hcx(uint8_t port,uint8_t baud,uint8_t power_pin,uint8_t key_pin,uint8_t sser_rx, uint8_t sser_tx ){
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
            HSerial = &Serial;
            curSerial= &Serial;
            break;
    case 9:
            *SSerial = SoftwareSerial(sser_rx,sser_tx);
            curSerial = SSerial;
            break;

#if  defined(   __AVR_ATmega2560__ ) || defined( __AVR_ATmega328__)  //mega o Nano
    case 1: Serial1.begin(baud_rate);
            HSerial = &Serial;
            curSerial= &Serial1;
            break;
#endif
#ifdef __AVR_ATmega2560__ // si es un MEGA tiene estos puertos

    case 2: Serial2.begin(baud_rate);
            HSerial = &Serial;
            curSerial= &Serial2;
            break;
    case 3: Serial3.begin(baud_rate);
            HSerial = &Serial;
            curSerial= &Serial3;
            break;
#endif


  }


};
void bcm417_hcx::beginConf(){
/* comienza el ciclo de configuracion */


  /* colocamos el modulo en modo AT completo*/
  digitalWrite(pin_power,LOW);
  digitalWrite(pin_key,HIGH);
  delay(5);
  digitalWrite(pin_power,HIGH);
  delay(10);
  /* la clase stream no tiene begin por eso se necesita una referencia especifica*/
  if (s_port==9) {
    SSerial->begin(MASTER_BAUDRATE);
  }else{
    HSerial->begin(MASTER_BAUDRATE);
  }
  curSerial->print("AT");
  curSerial->print(CR_LF);
  on_config = wait_response();


};
int bcm417_hcx::getBTMode(){
  return mode;
};
void bcm417_hcx::setBTMode(int smode){
  switch (smode) {
    case BT_MODE_MASTER:
    setMaster();
    break;
    case BT_MODE_SLAVE:
    setSlave();
    break;
  }

};
bool bcm417_hcx::wait_response(){
  int time_out=1000;
  String buff;
  while (curSerial->available()>3 ){   //deberia ser 'OK\r\n'

      buff = curSerial->readStringUntil('\n');
      if (buff.equals("OK")){
          // respusta correcta
        return true;
        break;
      } else
      {

        return false;
        break;
      };
      if (--time_out<1) {
        return false;
        break;
      };
  }
}
void bcm417_hcx::setMaster(){
  curSerial->print("AT+RMAAD");
  curSerial->print(CR_LF);
  curSerial->print("AT+ROLE=1");
  curSerial->print(CR_LF);
  curSerial->print("AT+RESET");
  curSerial->print(CR_LF);
  delay(10);
  curSerial->print("AT+CMODE=0");
  curSerial->print(CR_LF);
  curSerial->print("AT+INQM=0,5,5");
  curSerial->print(CR_LF);
  curSerial->print("AT+INIT"); // debe retorna la lista de dispositivos
  curSerial->print(CR_LF);
  /*
  AT+RMAAD Clear any paired devices
  AT+ROLE=1 Set mode to Master
  AT+RESET After changing role, reset is required
  AT+CMODE=0 Allow connection to any address (I have been told this is wrong and CMODE=1 sets "any address"
  AT+INQM=0,5,5 Inquire mode - Standard, stop after 5 devices found or after 5 seconds
  AT+PSWD=1234 Set PIN. Should be same as slave device
  AT+INIT Start Serial Port Profile (SPP) ( If Error(17) returned - ignore as profile already loaded)
  AT+INQ Start searching for devices
  */
};
void bcm417_hcx::setSlave(){
  curSerial->print("AT+ORGL");
  curSerial->print("AT+RMAAD");
  curSerial->print("AT+ROLE=0");
  curSerial->print("AT+ADDR");
  BTAddr = curSerial->readString();
/*
AT+ORGL Reset to defaults
AT+RMAAD Clear any paired devices
AT+ROLE=0 Set mode to SLAVE
AT+ADDR Display SLAVE addres
*/
};
int bcm417_hcx::available(){
  if (conectado) return curSerial->available();
  return 0;
};
char bcm417_hcx::read(){
  if (conectado) return curSerial->read();
  return 0;
};
void bcm417_hcx::setName(String name){
  if (on_config){
      this->name=name;
      curSerial->print("AT+NAME=");
      curSerial->print(name);
      curSerial->print(CR_LF);

  }

};
String bcm417_hcx::getName(){
  return this->name;

};
void bcm417_hcx::scanBT(){
  // falta implementar

};
String bcm417_hcx::listDevices(){
  // falta implementar
  return "No implementado";
};
String bcm417_hcx::getBTAddr(){
  return this->BTAddr;
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
