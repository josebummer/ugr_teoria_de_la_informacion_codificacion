#include "ArduTIC.h"

#define U 15 // Umbral
#define T 3
#define TAM 501
#define NBITS 5

char recvBit(){
    char salida;
    while(digitalRead(8) == LOW);
    int contador = 0;
    while(digitalRead(8) == HIGH){
        contador++;
        delay(U/T);
    }
    if(contador > U/T)
        return '1';
    else
        return '0';
}

int main(void)
{
    pinMode(8,INPUT);
    Serial.begin(9600);
    char letra[NBITS+1] = "";
    char cadena[TAM] = "";
    int c = 0;

    while(1){
        char bit = recvBit();
        letra[c] = bit;
        c++;
        
        if(c == NBITS){
            letra[c] = '\0';
            strcat(cadena,letra);
            if(strcmp(letra,"11111") == 0){
                Serial.print(cadena);
                cadena[0] = '\0';
            }
            letra[0] = '\0';
            c = 0;
        }

    }
    return 0;
}