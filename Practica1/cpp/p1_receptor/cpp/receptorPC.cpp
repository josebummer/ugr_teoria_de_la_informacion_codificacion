#include "PCSerialUSB.h"
#include <iostream>
#include <cstring>
#include <unordered_map>

#define TAM 501

#define NBITS 5

using namespace std;

void crearMap(unordered_map<string,char> &mapa){
    mapa["00000"] = 'A'; mapa["10000"] = 'Q';
    mapa["00001"] = 'B'; mapa["10001"] = 'R';
    mapa["00010"] = 'C'; mapa["10010"] = 'S';
    mapa["00011"] = 'D'; mapa["10011"] = 'T';
    mapa["00100"] = 'E'; mapa["10100"] = 'U';
    mapa["00101"] = 'F'; mapa["10101"] = 'V';
    mapa["00110"] = 'G'; mapa["10110"] = 'W';
    mapa["00111"] = 'H'; mapa["10111"] = 'X';
    mapa["01000"] = 'I'; mapa["11000"] = 'Y';
    mapa["01001"] = 'J'; mapa["11001"] = 'Z';
    mapa["01010"] = 'K'; mapa["11010"] = ' ';
    mapa["01011"] = 'L'; mapa["11011"] = '.';
    mapa["01100"] = 'M'; mapa["11100"] = ',';
    mapa["01101"] = 'N'; mapa["11101"] = ';';
    mapa["01110"] = 'O'; mapa["11110"] = ':';
    mapa["01111"] = 'P'; mapa["11111"] = '\0';
}

void decodificar(string cadena, unordered_map<string,char> &mapa){
    string resultado = "";
    for(int i = 0; i < cadena.size(); i+=NBITS){
        resultado += mapa[cadena.substr(i,NBITS)];
    }
    cout << endl << resultado << endl;
}

int main(void)
{
    int p = InicializarUSB("/dev/cu.usbmodem144301");
    if(p < 0){
        cout << "Error" << endl;
        return -1;
    }
    unordered_map<string,char> mapa;
    crearMap(mapa); 

    while(true){
        char bits[TAM] = "";
        if(receiveUSB(p,bits)){            
            string bits_s(bits);
            cout << bits_s  << endl;
            decodificar(bits_s,mapa);
        }
    }
    
    CerrarUSB(p);
    
    return 0;
}