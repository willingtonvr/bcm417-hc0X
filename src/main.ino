#include "bcm417_hcx.h"

bcm417_hcx bt; //  arrancamos con los valores por defecto

void setup(){

bt.beginConf();  // inciamos configuracion
bt.setName("BT_TERMINAL"); // le damos un nombre
bt.setBTMode(BT_MODE_SLAVE);
bt.endConf();


};

void loop() {
  if (bt.available())
      Serial.write(bt.read());

    
    if (Serial.available())
      bt.print(Serial.read());

};
