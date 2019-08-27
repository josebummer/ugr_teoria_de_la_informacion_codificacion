/**
 * Prácticas de Teoría de la Información y la Codificación
 * Ejemplo de programación del lector de raduifrecuencia RF2272 para escritura y lectura
 * Ver montaje del tarjetero con Arduino UNO en las diapositivas de clase
 * 
 * Este fichero contiene CODIGO ARDUINO
 *
 * Funcionamiento general del programa de ejemplo:
 * 
 * 1. Se inicializa el lector RF2272 y el puerto serie para mandar mensajes al PC.
 * 2. Se ejecuta en un bucle infinito lo siguiente
 *  2.1. Se lee el código del lector
 *  2.2. Se decodifica
 *  2.3. Se envían los botones leídos por USB
 *   
 * 
 */


#include <ArduTIC.h>
#include <ReceptorRF2272.h>
#include <string.h>

#define B_PARIDAD 3
#define LONGITUD 7


/**
 * FUNCION A IMPLEMENTAR POR EL ALUMNO: 
 *
 * Decodifica el mensaje de un código leído del receptor RF 2272 en un vector de bools indicando los botones pulsados
 * @param codigo El código leído desde el receptor
 * @retval pulsados. Parámetro de salida. Vector que indica si los botones A (pulsados[0]), B (pulsados[1]), 
 *     C (pulsados[2]), D (pulsados[3]), están pulsados (valor true) o no (valor false). Todos a false si se devuelve error
 * @return true Si se decodificó adecuadamente, false si se encontraron errores en el código (o que no se pudieron corregir).
 */
bool decodificar(const uint8_t codigo, bool pulsados[4]);
unsigned int sindrome(const uint8_t codigo);


int main() {

	bool botones[4]; // Para saber qué botones hay pulsados
	uint8_t codigoLeido; // Codigo leido desde el receptor 2272

	Serial.begin(9600); //Iniciamos la comunicación del puerto serie (USB) a 9600 baud

	// Inicializamos el receptor 2272
	IniciarRF2272();

	while (true) {

		codigoLeido= leerRF2272();
		unsigned int err = sindrome(codigoLeido);
		if (decodificar( codigoLeido , botones)) {
			if (botones[0] || botones[1] || botones[2] || botones[3]) {
				for (int i=6; i>=0; i--) {
					if ( (codigoLeido&(1<<i)) > 0 )
						Serial.print("1");
					else
						Serial.print("0");
				}
				Serial.print(" ");
				if (botones[0])
					Serial.print("A");
				if (botones[1])
					Serial.print("B");
				if (botones[2])
					Serial.print("C");
				if (botones[3])
					Serial.print("D");
				Serial.println();
			}
		} else{
			char mensaje[200] = "ERROR DETECTADO Y CORREGIDO EN EL BIT ";
			char buffer[33];
			strcat(mensaje, itoa(err, buffer, 10));	

			codigoLeido = codigoLeido^(1<<(err-1));

			if(decodificar(codigoLeido, botones)){
				Serial.print(mensaje);

				if (botones[0] || botones[1] || botones[2] || botones[3]) {
					for (int i=6; i>=0; i--) {
						if ( (codigoLeido&(1<<i)) > 0 )
							Serial.print("1");
						else
							Serial.print("0");
					}
					Serial.print(" ");
					if (botones[0])
						Serial.print("A");
					if (botones[1])
						Serial.print("B");
					if (botones[2])
						Serial.print("C");
					if (botones[3])
						Serial.print("D");
					Serial.println();
				}
			}
			else{
				Serial.print("NO SE HA CORREGIDO");
			}
		}
		delay(500); // Esperamos 100ms
	}	

	return 0;
}

unsigned int sindrome(const uint8_t codigo){
	int valores[7] = {0,0,0,0,0,0,0};

	for (int i = 0; i < 7; i++){
		if((codigo&(1<<i)) > 0){
			valores[i] = 1;
		}
	}

	unsigned int r = 0;
	int p[3];
	p[0] = (valores[3] + valores[4] + valores[5] + valores[6]) % 2;
	p[1] = (valores[6] + valores[5] + valores[2] + valores[1]) % 2;
	p[2] = (valores[6] + valores[4] + valores[2] + valores[0]) % 2;

	r = p[2] | (p[1]<<1) | (p[0]<<2);

	return r;

}



bool decodificar(const uint8_t codigo, bool pulsados[4]) {

	// A IMPLEMENTAR POR EL ALUMNO. BORRAR EL CÓDIGO SIGUIENTE.
	pulsados[0]= ((codigo&(1<<2))>0);
	pulsados[1]= ((codigo&(1<<4))>0);
	pulsados[2]= ((codigo&(1<<5))>0);
	pulsados[3]= ((codigo&(1<<6))>0);

	unsigned int valores[7] = {0,0,0,0,0,0,0};

	for(int i = 0; i < 7;i++){
		if((codigo&(1<<i)) > 0){
			valores[i] = 1;
		}
	}

	// COMPROBAR ERRORES
	if((valores[0]^valores[2]^valores[4]^valores[6]) > 0) return false;
	if((valores[1]^valores[2]^valores[5]^valores[6]) > 0) return false;
	if((valores[3]^valores[4]^valores[5]^valores[6]) > 0) return false;

	return true;
}
