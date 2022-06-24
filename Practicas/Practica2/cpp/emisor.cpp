#include "ArduTIC.h"

using namespace std;

#define U 15
#define TAM 100

void SendBit(char bit){
    if(bit == '0'){
        digitalWrite(12,HIGH);
        delay(U);
        digitalWrite(12,LOW);
        delay(U);
    }
    else{
        digitalWrite(12,HIGH);
        delay(2*U);
        digitalWrite(12,LOW);
        delay(U);
    }
}

int main(void)
{
    pinMode(12,OUTPUT);
    char cadena[501];
    Serial.begin(9600);

    while(1){
        if(Serial.available()){
            Serial.readString(cadena);

            for(int i = 0; i < strlen(cadena); i++){
                SendBit(cadena[i]);
            }
            Serial.print("0");
            cadena[0] = '\0';
        }
    }
    return 0;
}