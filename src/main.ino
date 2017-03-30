#include "bcm417_hcx.h"

bcm417_hcx bt; //  arrancamos con los valores por defecto

void setup(){

  bt.beginConf();  // inciamos configuracion
  bt.setName("BT_TERMINAL"); // le damos un nombre
  bt.setBTMode(BT_MODE_SLAVE);
  bt.endConf();


};

void loop() {
  /* terminal basica de copiar de un puerto a otro*/
  char dato;
  if (bt.available())
      Serial.write(bt.read());


    if (Serial.available())
      dato=Serial.read();
      if (dato='#'){ /* caracter de escape para cambiar parametros*/
        Serial.println("Entrando en modo de control");
        Serial.println("Opciones:");
        Serial.println("NAME=XXXX : cambia nombre");
        Serial.println("PSWD=XXXX : cambia Clave");
        Serial.println("EXIT : sale del modo de control");
        String cmd;
        bool salir=false;
        while (!salir) {
            if (Serial.available()){
                cmd=Serial.readString();  //
                cparam=getParamValue(cmd,'=',0);
                cvalue=getParamValue(cmd,'=',1);
                if(cparam=='NAME') bt.setName(cvalue);
                if(cparam=='PSWD') bt.setPWD(cvalue);
                if(cparam=='EXIT') salir=true;
            }
        }

      }  else {

        bt.print(dato);
      }



};

String getParamValue(String data, char separator, int index)
{
    /* separa la cadena en componentente parametro=valor*/
    /* Index =0 el nombre del parametro*/
    /* Index =1 el valor del parametro*/
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
