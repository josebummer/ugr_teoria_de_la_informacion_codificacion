#include "ArduTIC.h"

#define U 15 // Umbral
#define T 3
#define TAM 501
#define NBITS 5
#define PIN 8

bool recvBit(char &dato){
    int c = 0;

    while(digitalRead(PIN) == LOW && c<T+1){
        c++;
        delay(U/T);
    }
    if(c >= T+1)
        return false;
    
    c = 0;
    while(digitalRead(PIN) == HIGH){
        c++;
        delay(U/T);
    }

    dato = (c>T+1)?'1':'0';
    return true;

}

int main(void)
{
    pinMode(PIN,INPUT);
    Serial.begin(9600);
    char cadena[TAM] = "";
    int tamBuf= 0;
    char dato;

    while(1){
        if(recvBit(dato)){
            cadena[tamBuf] = dato;
            tamBuf++;
        }
        else if(tamBuf > 0){
            cadena[tamBuf] = '\0';
            Serial.print(cadena);
            tamBuf = 0;
        }
    }
    return 0;
}