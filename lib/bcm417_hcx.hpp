// encabezado
#ifndef BCM417_HCX_H
#include <Arduino.h>
#include <stdio.h> // for size_t
#include <SoftwareSerial.h>
#define BCM417_HCX_H
#define DEFAULT_BAUDRATE 9600  // Baud rate por defecto del modulo
#define MASTER_BAUDRATE 38400  // baud rate para reconfigurar el modulo
#define CR_LF "\r\n"

/* Modos Bluetooth*/
#define BT_MODE_MASTER 1
#define BT_MODE_SLAVE  0
/* Tipos de conexion Bluetooth*/
#define BT_CMODE_ANY   1
#define BT_CMODE_ALONE 0
/* copiadas de print.h
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
*/

class bcm417_hcx {
public:
      /* Constructor por defecto */
      bcm417_hcx();
      /* Constructor para seleccionar el puerto, el puerto de encendido y el KEY */
      bcm417_hcx(uint8_t port,uint8_t baud,uint8_t power_pin,uint8_t key_pin,uint8_t sser_rx, uint8_t sser_tx );

      /* funcion de configuracion*/
      void setup(int baud_rate,int parity, int stopbit);
      // nombre del dispositivo Bluetooth
      int getBTMode();
      void setBTMode(int smode);
      int getCMODE();
      void setCMODE(int cmode);
      String getName();
      void setName(String name);
      void scanBT(); // busca dispositivo Bluetooth almacena el dato en una lista
      String listDevices(); // devuelve una lista seprarda por comas de los dispositivos
      void beginConf();  //lamar esta funcion para iniciar la configuracion
      void endConf(); // Al llamar esta funcion se envian las nuevas confuraciones al modulo
      String getBTAddr(); // obtiene la direccion del dispositivo
      bool pair(String pair_device, String passwd);  // en modo master indica a que modulo aparerse


      /* function wrappers del puerto serie*/ //
      int available();
      /* reads Copiados de Stream.h */
      char read();
      String readString();
      String readStringUntil(char terminator);
      size_t readBytesUntil( char terminator, char *buffer, size_t length); // as readBytes with terminator character
      size_t readBytesUntil( char terminator, uint8_t *buffer, size_t length);
      /* todos los sabores de print */
      /* tomados de Print.h*/
      size_t print(const String &dato);
      size_t print(const char dato[]);
      size_t print(char dato);
      size_t print(unsigned char dato, int base = DEC);
      size_t print(int dato , int base = DEC);
      size_t print(unsigned int dato, int base = DEC);
      size_t print(long dato, int base = DEC);
      size_t print(unsigned long dato, int base = DEC);
      size_t print(double dato, int digits = 2);

      size_t println(const String &dato);
      size_t println(const char dato[]);
      size_t println(char dato);
      size_t println(unsigned char dato, int base = DEC);
      size_t println(int dato , int base = DEC);
      size_t println(unsigned int dato, int base = DEC);
      size_t println(long dato, int base = DEC);
      size_t println(unsigned long dato, int base = DEC);
      size_t println(double dato, int digits = 2);
      size_t println();
      /**/


private:
  bool conectado;
  bool encendido;
  int pin_key;
  int pin_power;
  int s_port;
  int baud_rate;
  HardwareSerial *HSerial;
  SoftwareSerial *SSerial;
  Stream *curSerial;

  const char *passwd="1234";
  String name;
  String BTAddr;
  int mode;
  int cmode;
  bool on_config;  // flag para saber si esta en modo confugracion
  void setMaster();
  void setSlave();
  bool wait_response();

};


#endif
