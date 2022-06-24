#include "PCSerialUSB.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <cctype>
#include <stack>
#include <fstream>
#include <list>

#define USB_PORT "/dev/cu.usbmodem145201"
#define TAM 501
#define NBITS 5

#define FILAS 4
#define COLUMNAS 64
#define ALFABETO 0
#define HIJOIZ 1
#define HIJODE 2
#define PADRE 3

using namespace std;

struct NodoParcial{
    char simbolo;
    int frecuencia;
    int pos;
};

bool Comparador(const NodoParcial &uno, const NodoParcial &dos){
        return uno.frecuencia >= dos.frecuencia;
}

list<NodoParcial> leerFichero(string fich){
    char letra;
    list<NodoParcial> res;
    list<NodoParcial>::iterator it;


    ifstream f(fich);

    //los más " " , a ,e 
    //los menos k,w --> 1

    while(!f.eof()){
        letra = toupper(f.get());
        if(letra != '\n' && letra != EOF){
            NodoParcial aux;

            bool esta = false;
            for(it = res.begin(); it != res.end() && !esta; ++it){
                if(it -> simbolo == letra){
                    esta = true;
                    --it;
                }
            }

            if(esta){
                it -> frecuencia++;
            }
            else{
                aux.simbolo = letra;
                aux.frecuencia = 1;
                aux.pos = res.size();

                res.push_back(aux);
            }
        }
    }
    f.close();

    return res;
}

int crearMatriz(int matriz[FILAS][COLUMNAS],list<NodoParcial> lista){
    int raiz = 0;

    for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            if(i == ALFABETO){
                matriz[i][j] = '*';
            }
            else{
                matriz[i][j] = -1;
            }
        }
    }

    for(list<NodoParcial>::iterator it = lista.begin(); it != lista.end(); ++it){
        int pos = it -> pos;
        matriz[ALFABETO][pos] = it -> simbolo;
        matriz[HIJOIZ][pos] = -1;
        matriz[HIJODE][pos] = -1;
        matriz[PADRE][pos] = -1;
        raiz++;
    }

    while(lista.size() > 1){
        lista.sort(Comparador);

        int freq1, freq2;
        int pos1, pos2;
        
        pos1 = lista.back().pos;
        freq1 = lista.back().frecuencia;
        lista.pop_back();
        pos2 = lista.back().pos;
        freq2 = lista.back().frecuencia;
        lista.pop_back();

        matriz[PADRE][raiz] = -1;
        matriz[HIJOIZ][raiz] = pos1;
        matriz[HIJODE][raiz] = pos2;
        matriz[PADRE][pos1] = matriz[PADRE][pos2] = raiz;

        NodoParcial c;

        c.simbolo = '*';
        c.frecuencia = freq1+freq2;
        c.pos = raiz;
        lista.push_back(c);
        raiz++;
    }

    raiz--;

    return raiz;
}

string decodificar(string cadena, int matriz[FILAS][COLUMNAS], int raiz){
    
    string salida = "";
    int actual = raiz;

    for(int i = 0; i < cadena.length(); i++){
        // Es hijo izquierda
        if(cadena[i] == '1'){
            actual = matriz[HIJOIZ][actual];
        }
        // Es hijo derecha
        else{
            actual = matriz[HIJODE][actual];
        }
        // Es nodo hoja
        if(matriz[ALFABETO][actual] != '*'){
            salida += matriz[ALFABETO][actual];
            actual = raiz;
        }
    }
    
    return salida;

}

int main(void)
{
    int p = InicializarUSB(USB_PORT);

    while(true){
        char bits[TAM] = "";
        if(receiveUSB(p,bits)){          
            string bits_s(bits);
            cout << endl << bits_s  << endl;
        }
    }
    
    CerrarUSB(p);
    
    return 0;
}