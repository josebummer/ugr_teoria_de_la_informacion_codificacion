#include "PCSerialUSB.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;

void crearMap(unordered_map<char,string> &map){
    map['A'] = "00000";
    map['B'] = "00001";
    map['C'] = "00010";
    map['D'] = "00011";
    map['E'] = "00100";
    map['F'] = "00101";
    map['G'] = "00110";
    map['H'] = "00111";
    map['I'] = "01000";
    map['J'] = "01001";
    map['K'] = "01010";
    map['L'] = "01011";
    map['M'] = "01100";
    map['N'] = "01101";
    map['O'] = "01110";
    map['P'] = "01111";
    map['Q'] = "10000";
    map['R'] = "10001";
    map['S'] = "10010";
    map['T'] = "10011";
    map['U'] = "10100";
    map['V'] = "10101";
    map['W'] = "10110";
    map['X'] = "10111";
    map['Y'] = "11000";
    map['Z'] = "11001";
    map[' '] = "11010";
    map['.'] = "11011";
    map[','] = "11100";
    map[';'] = "11101";
    map[':'] = "11110";
    map['\0'] = "11111";
}

void codificar(char frase[], char cadena[], unordered_map<char,string> map){
    int k = 0;

    for(int i = 0; i < strlen(frase); i++){
        string parte = map[toupper(frase[i])];

        for(int j = 0; j < parte.size(); j++){
            cadena[k] = parte[j];
            k++;
        }
    }
    for(int i = 0; i < 5; i++){
        cadena[k] = '1';
        k++;
    }
    cadena[k] = '\0';
}

int main(void)
{
    char frase[101];
    char cadena[501];
    unordered_map<char,string> mapa;
    char fin[2];

    int p = InicializarUSB("/dev/ttyACM0");

    if(p < 0){
        cout << "Error" << endl;
        return -1;
    } 

    crearMap(mapa);

    while(1){
        cin.getline(frase,100);
        codificar(frase,cadena,mapa);

        sendUSB(p,cadena);

        receiveUSB(p,fin);
        fin[0] = '\0';
        frase[0] = '\0';
    }

    CerrarUSB(p);
    return 0;
}