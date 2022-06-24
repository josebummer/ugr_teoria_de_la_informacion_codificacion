#include "ArduTIC.h"

int main(void)
{
    pinMode(8,INPUT);
    pinMode(12,OUTPUT);

    while(1){
        if(digitalRead(8)==1){
            digitalWrite(12,HIGH);
        }
        else if(digitalRead(8)==0){
            digitalWrite(12,LOW);
        }

    }
    return 0;
}