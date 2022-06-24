#include "PCSerialUSB.h"
#include <iostream>
#include <cstring>

using namespace std;

int main(void)
{
    int p = InicializarUSB("/dev/ttyACM0");
    if(p < 0){
        cout << "Error" << endl;
        return -1;
    } 

    char m[1000];
    char r[1000];
    while(strcmp(m,"exit") != 0){
        cin.getline(m,1000);
        sendUSB(p,m);
    }

    strcpy(m,"off");
    sendUSB(p,m);
    CerrarUSB(p);
    
    return 0;
}