// encabezado
#ifndef BCM417_HCX_H
#include "Arduino.h"
#define BCM417_HCX_H
#define DEFAULT_BAUDRATE 9600  // Baud rate por defecto del modulo
#define MASTER_BAUDRATE 38400  // baud rate para reconfigurar el modulo

class bcm417_hcx {
public:
      /* Constructor por defecto */
      bcm417_hcx();
      /* Constructor para seleccionar el puerto, el puerto de encendido y el KEY */
      bcm417_hcx(int port,int baud,int power_pin,int key_pin );

      /* funcion de configuracion*/
      void setup(int baud_rate,int parity, int stopbit);
      /* funcion de encendido devuelve true si encendió*/
      bool encender();
      /* function wrappers del puerto serie*/
      void println(char *dato);
      void print(char *dato);
      int available();
      char read();



private:
  bool conectado;
  bool encendido;
  int pin_key;
  int pin_power;
  int s_port;
  int baud_rate;
  HardwareSerial * curSerial;
  const char *passwd="1234";

};


#endif
