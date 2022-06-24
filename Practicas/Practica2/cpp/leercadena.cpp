#include "PCSerialUSB.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <cctype>
#include <stack>
#include <fstream>
#include <list>

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

    bool operator < (NodoParcial otro){
        return frecuencia >= otro.frecuencia;
    }
};

void codificar(char frase[],char cadena[], int matriz[FILAS][COLUMNAS]){
    int c = 0;  //Lleva el indice para la cadena aux
    int cf = 0; //Lleva el indice de la frase que se devuelve
    int padre = 0;
    int actual;
    char aux[200];    //Lleva cada una de las letras

    for(int k = 0; k < strlen(cadena); k++){
        bool encontrado = false;
        aux[0] = '\0';
        c = 0;
        for(int j = 0; j < COLUMNAS && !encontrado; j++){
            if(matriz[ALFABETO][j] == (int)(cadena[k])){
                actual = j;
                padre = matriz[PADRE][j];

                encontrado = true;
            }
        }

        if(encontrado){
            while(padre != -1){

                if(matriz[HIJOIZ][padre] == actual){
                    aux[c] = '1';
                }
                else{
                    aux[c] = '0';
                }
                c++;
                actual = padre;
                padre = matriz[PADRE][actual];
            }
            aux[c] = '\0';

            if(strlen(aux) != 0){
                

                for(int i = strlen(aux)-1; i>=0; i--){
                    frase[cf++]= aux[i];
                }
            }
        }
    }
    frase[cf] = '\0';
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
        lista.sort();

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
    res.sort();

    return res;
}

int main(void)
{
    char cadena[101];
    char frase[700];
    int matriz[FILAS][COLUMNAS];
    char fin[2];
    list<NodoParcial> valores;

    valores = leerFichero("./doc/quijote.txt");

    //MOSTRAR LISTA
    /*for(auto it = valores.begin(); it != valores.end(); ++it){
        cout << it -> simbolo << " " << it -> frecuencia << " " << it -> pos << endl;
    }

    cout << endl << valores.size() << endl;*/

    int raiz = crearMatriz(matriz,valores);

    //MOSTRAR MATRIZ
    /*for(int i = 0; i < FILAS; i++){
        for(int j = 0; j < COLUMNAS; j++){
            cout << matriz[i][j] << ",";
        }
        cout << endl;
    }*/

    //MOSTRAR RESULTADO
    /*for(int i = 0; i < strlen(frase); i++){
        cout << frase[i];
    }
    cout << endl;*/

    //MOSTRAR CODIFICACION DE CADA CARACTER
    /*for(auto it = valores.begin(); it != valores.end(); ++it){
        char aux[100];
        char aux2[2];

        aux2[1] = it->simbolo;
        aux2[2] = '\0';
        codificar(aux,aux2,matriz);

        cout << it->simbolo << " -> " << aux << endl;
    }*/

    int p = InicializarUSB("/dev/ttyACM0");

    if(p < 0){
        cout << "Error" << endl;
        return -1;
    }

    while(1){
        cin.getline(cadena,100);
        for(int i = 0; i < strlen(cadena); i++){
            cadena[i] = toupper(cadena[i]);
        }
        codificar(frase,cadena,matriz);

        sendUSB(p,frase);

        receiveUSB(p,fin);
        fin[0] = '\0';
        frase[0] = '\0';
    }


    CerrarUSB(p);
    return 0;
}