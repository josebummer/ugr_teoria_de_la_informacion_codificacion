#include "ArduTIC.h"

int main(void)
{
    char cadena[1000];
    char res[1000];
    Serial.begin(9600);
    pinMode(9,OUTPUT);

    while(1){
        if(Serial.available()){
            Serial.readString(cadena);

            if(strcmp(cadena, "on") == 0){
                digitalWrite(9,HIGH);
            }
            else if(strcmp(cadena, "off") == 0){
                digitalWrite(9,LOW);
            }
            else if(strcmp(cadena, "blinker") == 0){
                while(strcmp(res, "stop") != 0){
                    digitalWrite(9,HIGH);
                    delay(1000);
                    digitalWrite(9,LOW);
                    delay(1000);
                    if(Serial.available())
                        Serial.readString(res);
                }
            }
        }
        else{
            delay(500);
        }
    }
    return 0;
}