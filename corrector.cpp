
#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#include <stdlib.h>
#include <ctype.h>
#define LONGITUD 32
char abecedario[LONGITUD + 6] = "abcdefghijklmn�opqrstuvwxyz�����";


void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	/* Variable de archivo*/
	FILE* fp;
	iNumElementos = 0;
	/*Variable = i*/
	int i;
	/*Variables ocuparemos para guardar los datos */
	char lectura, array[TAMTOKEN];
	//Para iniciar el arreglo de estadisticas.
	for (i = 0; i < NUMPALABRAS; i++)
		iEstadisticas[i] = 0;
	/*Se abre el archivo en modo lectura*/
	fopen_s(&fp, szNombre, "r");
	/*Variable */
	int contador = 0;
	/*Almacenar palabras de puntuacion */
	char puntuacion[] = " \t\n\r.,;() ";
	/*Comprobamos apertura de archivo*/
	if (fp == NULL)
		return;

	/*Mientras que la lectura sea igual al fichero (sea diferente a fin del documento */
	while ((lectura = fgetc(fp)) != EOF) {

		/*Declaramos una bandera*/
		bool bandera = true;

		/*tolower=funcion para pasar de mayusculas a minusculas*/
		lectura = tolower(lectura);

		/*Comprobar que no hay palabras con signo de puntuaci�n */
		for (i = 0; i < strlen(puntuacion); i++)

			/*Compara si el caracter que recibi� si esta dentro de la lectura o es un signo de puntuaci�n*/
			if (puntuacion[i] == lectura)
				bandera = false;

		/*Si contador es menor que TAMTOKEN Y de la bandera sigue */
		if (contador < TAMTOKEN && bandera) {
			/*De lectura guardarlo al array*/
			array[contador++] = lectura;
			continue;
		}
		/*si es contador igual a cero sigue */
		else if (contador == 0)
			continue;
		/*si es contador igual a 1, asignar 0 a contador sigue */
		else if (contador == 1 && bandera) {
			contador = 0;
			continue;
		}
		/*Cuando las encuentre marcar un espacio*/
		array[contador] = '\0';
		/*Despues de comprobar en el abecedario y la puntuacion */
		for (i = 0; i < iNumElementos && !bandera; i++) {

			/*Aqui se hace la comparacion de las palabras*/
			if (strcmp(szPalabras[i], array) == 0) {
				/*Hacerlo hasta formar la palabra*/
				iEstadisticas[i]++;
				bandera = true;
			}
		}
		/*Si es diferente de la bandera*/
		if (!bandera) {
			/*Pasar todas los palabras que estan en el array a szPalabras[]*/
			strcpy_s(szPalabras[iNumElementos], array);
			iEstadisticas[iNumElementos++]++;

		}/*Para retornar*/
		contador = 0;
	}/*Fin del while o el documento*/
	fclose(fp);
	/*M�todo burbuja para el ordenamiento*/
	for (int j = 0; j < iNumElementos - 1; j++) {

		for (i = j + 1; i < iNumElementos; i++) {

			if (strcmp(szPalabras[j], szPalabras[i]) > 0) {
				strcpy_s(array, szPalabras[j]);
				strcpy_s(szPalabras[j], szPalabras[i]);
				strcpy_s(szPalabras[i], array);
				contador = iEstadisticas[j];
				iEstadisticas[j] = iEstadisticas[i];
				iEstadisticas[i] = contador;
			}
		}
	}
}


	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	sz
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char  szPalabrasSugeridas[][TAMTOKEN], 	    //Lista de palabras clonadas
	int& iNumSugeridas)						    //Numero de elementos en la lista
{
	
	//Pasar el abecedario entre los caracteres
	int k;
	for (k = 1; k < strlen(szPalabraLeida) + 1; k++) {
		auxiliar[k] = szPalabraLeida[k - 1];

		/*Para asignar espacios*/
	} auxiliar[k] = '\0';

	for (int i = 0; i < strlen(szPalabraLeida) + 1; i++) {

		for (int j = 0; j < LONGITUD; j++) {
			auxiliar[i] = abecedario[j];
			/*Numero de elementos en la lista a la Lista de palabras clonadas*/
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxiliar);
		}/*Palabra a clonar es igual auxiliar*/
		auxiliar[i] = szPalabraLeida[i];
	}
	//Para suprimir los caracteres
	int contador = 0;
	for (int i = 0; i < strlen(szPalabraLeida) && strlen(szPalabraLeida) != 1; i++) {

		for (int j = 0; j < strlen(szPalabraLeida); j++) {
			if (j != i)
				auxiliar[contador++] = szPalabraLeida[j];

			/*Para asignar espacios*/
		} auxiliar[contador] = '\0';

		/*Numero de elementos en la lista a la Lista de palabras clonadas*/
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxiliar);

		/*Palabra a clonar */
		strcpy_s(auxiliar, szPalabraLeida);

		contador = 0;
	}
	//Transposici�n de los caracteres.
	for (int i = 0; i < strlen(szPalabraLeida) - 1; i++) {
		auxiliar[i] = szPalabraLeida[i + 1];
		auxiliar[i + 1] = szPalabraLeida[i];

		/*Numero de elementos en la lista a la Lista de palabras clonadas*/
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], auxiliar);
		/*Palabra a clonar */
		strcpy_s(auxiliar, szPalabraLeida);
	}
	strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);


	//M�todo burbuja, para el ordenamiento.
	for (int j = 0; j < iNumSugeridas - 1; j++) {

		for (int i = j + 1; i < iNumSugeridas; i++) {

			if (strcmp(szPalabrasSugeridas[j], szPalabrasSugeridas[i]) > 0) {
				/*Lista de palabras clonadas a auxiliar*/
				strcpy_s(auxiliar, szPalabrasSugeridas[j]);
				strcpy_s(szPalabrasSugeridas[j], szPalabrasSugeridas[i]);
				strcpy_s(szPalabrasSugeridas[i], auxiliar);
			}
		}
	}


}


/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							    //Numero de elementos en la szListaFinal
{
	iNumLista = 0;
	for (int i = 0; i < iNumSugeridas; i++) {
		for (int j = 0; j < iNumElementos; j++) {

			/*Comparar la lista de palabras del diccionario con la lista de palabras clonadas */
			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
				/*Declaramos una bandera*/
				bool bandera = false;
				for (int k = 0; k < iNumLista && !bandera; k++)
					/*Comparar de Lista de palabras del diccionario con Lista final de palabras a sugerir*/
					if (strcmp(szListaFinal[k], szPalabras[j]) == 0)
						bandera = true;
				/*Si es verdad continua*/
				if (bandera) continue;
				/*Pasar de la Lista de palabras clonadas a Lista final de palabras a sugerir*/
				strcpy_s(szListaFinal[iNumLista], szPalabrasSugeridas[i]);
				iPeso[iNumLista++] = iEstadisticas[j];
			}
		}
	}
	/*Comprobar con Numero de elementos en la szListaFinal*/
	//Numero de elementos en la lista de opciones.
	for (int i = 0; i < iNumLista; i++) {
		for (int j = 0; j < iNumLista - 1; j++) {
			/*Asignar la condicion*/
			if (iPeso[j] < iPeso[j + 1]) {
				/*Variables para el metodo de las candidatas*/
				int iaux; char caux[50];
				strcpy_s(caux, szListaFinal[j + 1]); iaux = iPeso[j + 1];
				strcpy_s(szListaFinal[j + 1], szListaFinal[j]); iPeso[j + 1] = iPeso[j];
				strcpy_s(szListaFinal[j], caux); iPeso[j] = iaux;
			}
		}
	}
}


