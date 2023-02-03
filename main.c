

/**
 * @file       main.c
 * @author     David Encarnacion
 * @brief      Este archivo contiene el codigo principal del juego "Hundir la flota"
 */
// Online C compiler to run C program online
#include <stdio.h>
/**
 * @brief Incluye el tipo de datos booleano en C
 */

#include <stdbool.h>
/**
 * @brief Incluye funciones para trabajar con cadenas de caracteres
 */
#include <string.h>
/**
 * @brief Incluye funciones para reservar memoria dinamicamente y para generar numeros aleatorios
 */
#include <stdlib.h>
/**
 * @brief Incluye funciones para obtener la hora actual y para medir el tiempo transcurrido
 */
#include <time.h>

 /**
  * @brief Tamano del tablero del juego "Hundir la flota"
  */

#define SIZE 10
  /**
   * @brief Etiqueta de color ANSI para imprimir el texto en rojo
   */
#define ANSI_COLOR_RED     "\x1b[31m"
   /**
	* @brief Etiqueta de color ANSI para imprimir el texto en cian
	*/
#define ANSI_COLOR_CYAN    "\x1b[36m"
	/**
	 * @brief Etiqueta de color ANSI para regresar al color original del texto
	 */
#define ANSI_COLOR_RESET   "\x1b[0m"
	 /**
	  * @brief Etiqueta de color ANSI para imprimir el texto en amarillo
	  */
#define ANSI_COLOR_YELLOW  "\x1b[33m"
	  /**
	   * @brief Etiqueta de color ANSI para imprimir el texto en magenta
	   */
#define ANSI_COLOR_MAGENTA "\x1b[35m"


void salirDelJuego();
void puntuaciones();
void iniciarJuego();
// TAMANO DEL TABLERO
// VARIABLES GLOBALES
/**
 * @brief Tablero del jugador
 */
char playerBoard[SIZE][SIZE];
/**
 * @brief Tablero de la computadora
 */
char computerBoard[SIZE][SIZE];

// RELLENAR TABLERO JUGADOR
/**
 * @brief Representa un casillero vacio en el tablero del jugador
 */
const char BLANK = '~';
// SI FALLO EL ATAQUE
/**
 * @brief Representa un ataque fallido en el tablero del jugador
 */
const char MISS = 'O';
// TABLERO DEL ENEMIGO
/**
 * @brief Representa un casillero desconocido en el tablero de la computadora
 */
const char UNKNOWN = '?';
// SI LE DA AL BARCO ENEMIGO
/**
 * @brief Representa un ataque exitoso en el
 */
const char HIT = 'X';

// PUNTUACION DEL JUEGO
/**

*@brief Puntuacion actual del juego
*/
int puntuacion=0;

/**

* @brief Puntero a la puntuacion actual del juego
*/
int *ptrPuntuacion = &puntuacion;


/**
 * @struct Jugador
 * @brief Representa a un jugador del juego "Hundir la flota"
 */
struct Jugador {
	/**
	 * @brief Nombre del jugador
	 */
	char *nombre;
	/**
 * @brief Puntuacion del jugador
 */
	int puntuacion;
};

/**
 * @struct Tablero
 * @brief Representa el tablero del juego "Hundir la flota"
 */
struct Tablero {
	/**
	 * @brief Lista de los 10 mejores jugadores
	 */
	struct Jugador top10[10];
};


/**
 * @brief Estructura del tablero del juego "Hundir la flota"
 */
struct Tablero t1;


/**
 * @struct Barco
 * @brief Representa a un barco en el juego "Hundir la flota"
 */
typedef struct {
	/**
 * @brief Nombre del barco
 */
	char* name;
	/**
	 * @brief Longitud del barco
	 */
	int length;
	/**
	 * @brief Caracter que representa al barco en el tablero
	 */
	char boardCharacter;
	/**
	 * @brief Posicion de fila del barco en el tablero
	 */
	int rowPos;
	/**
 * @brief Posicion de columna del barco en el tablero
 */
	int colPos;
	/**
	 * @brief Indica si el barco esta posicionado de manera horizontal o vertical
	 */
	bool amIHorizontal;
} Barco;



 /**
  * @brief Obtiene el nombre de un barco.
  *
  * @param b Puntero al objeto de tipo Barco del cual se desea obtener el nombre.
  * @return Puntero al nombre del barco.
  */
char* getName(Barco* b) {
	return b->name;
}
/**
 * @brief Obtiene el tamano de un barco.
 *
 * @param b Puntero al objeto de tipo Barco del cual se desea obtener el tamano.
 * @return Tamano del barco.
 */
int getLength(Barco* b) {
	return b->length;
}
/**
 * @brief Obtiene el caracter con el que se representa el barco en el tablero.
 *
 * @param b Puntero al objeto de tipo Barco del cual se desea obtener el caracter.
 * @return Caracter con el que se representa el barco en el tablero.
 */
char getBoardCharacter(Barco* b) {
	return b->boardCharacter;
}
/**
 * @brief Obtiene la posicion en fila del barco en el tablero.
 *
 * @param b Puntero al objeto de tipo Barco del cual se desea obtener la posicion en fila.
 * @return Posicion en fila del barco en el tablero.
 */
int getRowPos(Barco* b) {
	return b->rowPos;
}
/**
 * @brief Obtiene la posicion en columna del barco en el tablero.
 *
 * @param b Puntero al objeto de tipo Barco del cual se desea obtener la posicion en columna.
 * @return Posicion en columna del barco en el tablero.
 */
int getColPos(Barco* b) {
	return b->colPos;
}
/**
 * @brief Indica si el barco esta en posicion horizontal o no.
 *
 * @param b Puntero al objeto de tipo Barco del cual se desea conocer la orientacion.
 * @return true si el barco esta en posicion horizontal, false en caso contrario.
 */
bool isHorizontal(Barco* b) {
	return b->amIHorizontal;
}


/**
 * @brief Establece la posicion y orientacion de un barco en el tablero.
 *
 * @param b Puntero al objeto de tipo Barco al cual se desea establecer la posicion y orientacion.
 * @param row Posicion en fila en el tablero.
 * @param col Posicion en columna en el tablero.
 * @param direction Direccion en la que se colocara el barco. Valores validos son 'w' para arriba, 's' para abajo, 'd' para derecha e 'a' para izquierda.
 */
void setPiece(Barco* b, int row, int col, char direction) {
	switch (direction) {
	case 'w':
		b->rowPos = row - (b->length - 1);
		b->colPos = col;
		b->amIHorizontal = false;
		break;
	case 's':
		b->rowPos = row;
		b->colPos = col;
		b->amIHorizontal = false;
		break;
	case 'd':
		b->rowPos = row;
		b->colPos = col;
		b->amIHorizontal = true;
		break;
	case 'a':
		b->rowPos = row;
		b->colPos = col - (b->length -1);
		b->amIHorizontal = true;
		break;
	default:
		b->rowPos = -1;
		b->colPos = -1;
		break;
	}
}


/**
 * @brief Rellena los tableros del juego con los valores predeterminados.
 *
 * Rellena el tablero del jugador con caracteres BLANK y el tablero del ordenador con caracteres UNKNOWN.
 */
void rellenarTableros() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			playerBoard[i][j] = BLANK;
		}
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			computerBoard[i][j] = UNKNOWN;
		}
	}
}


/**
 * @brief Muestra los tableros del juego en pantalla.
 *
 * @param move1 nombre del primer tablero
 * @param move2 nombre del segundo tablero
 * @param leftBoard tablero izquierdo
 * @param rightBoard tablero derecho
 */
void mostrarTableros(char move1[], char move2[], char leftBoard[SIZE][SIZE], char rightBoard[SIZE][SIZE]) {

	printf("\n\n");
	printf("_ ");
	for (int i = 0; i < SIZE; i++) {

		printf("%d", i + 1);
		printf(" ");
	}

	printf("                         ");
	for (int i = 0; i < SIZE; i++) {

		printf("%d", i + 1);
		printf(" ");
	}
	printf("\n");


	for (int i = 0; i < SIZE; i++) {
		char row = 'A' + i;
		printf(ANSI_COLOR_RESET"%c", row );
		printf(" ");
		for (int j = 0; j < SIZE; j++) {
			if (leftBoard[i][j] == BLANK) {
				printf(ANSI_COLOR_CYAN "%c",  leftBoard[i][j] ,ANSI_COLOR_RESET);
				printf(" ");
			}
			else if(leftBoard[i][j] == 'P' ||leftBoard[i][j] == 'L' || leftBoard[i][j] == 'C') {
				printf(ANSI_COLOR_YELLOW "%c",  leftBoard[i][j] ,ANSI_COLOR_RESET);
				printf(" ");
			}
			else if(leftBoard[i][j] == HIT) {
				printf(ANSI_COLOR_RED "%c",  leftBoard[i][j] ,ANSI_COLOR_RESET);
				printf(" ");
			}
			else {
				printf(ANSI_COLOR_MAGENTA "%c",  leftBoard[i][j] ,ANSI_COLOR_RESET);
				printf(" ");
			}
		}

		printf("                        ");
		printf(ANSI_COLOR_RESET"%c", row);
		printf(" ");
		for (int j = 0; j < SIZE; j++) {
			if (rightBoard[i][j]== UNKNOWN) {
				printf(ANSI_COLOR_CYAN "%c", rightBoard[i][j], ANSI_COLOR_RESET);
				printf(ANSI_COLOR_RESET" ");
			}
			else if (rightBoard[i][j] == HIT) {
				printf(ANSI_COLOR_RED "%c", rightBoard[i][j], ANSI_COLOR_RESET);
				printf(" ");
			}
			else {
				printf(ANSI_COLOR_MAGENTA "%c",  rightBoard[i][j] ,ANSI_COLOR_RESET);
				printf(" ");
			}
		}
		printf("\n");
	}
}

/**
 * @brief Muestra el tablero simple en pantalla.
 */
void mostrarTableroSimple() {
	mostrarTableros("", "", playerBoard, computerBoard);
}

/**
 * @brief Muestra el tablero con informacion adicional en pantalla.
 *
 * @param move1 nombre del primer tablero
 * @param move2 nombre del segundo tablero
 * @param puntuacion puntuacion obtenida en el juego
 */
void mostrarTableroConInformacion(char* move1, char* move2,float puntuacion) {
	printf("\n\n\n\n\n");
	printf("                        ");
	printf("Tu puntuacion es: ");
	printf("%f\n",puntuacion);
	printf("\n");
	mostrarTableros(move1, move2, playerBoard, computerBoard);
}


/**
 * @brief Agrega una pieza al tablero.
 *
 * @param board tablero donde se agregara la pieza.
 * @param pieza puntero a la pieza a agregar.
 */
void agregarPiezaAlTablero(char board[SIZE][SIZE], Barco* pieza) {
	int row = getColPos(pieza);
	int col = getRowPos(pieza);
	for (int i = 0; i < getLength(pieza); i++) {
		board[row][col] = getBoardCharacter(pieza);
		if (isHorizontal(pieza)) {
			col++;
		}
		else {
			row++;
		}
	}
}

/**
 * @brief Verifica si es un lugar valido para agregar una pieza.
 *
 * @param board tablero donde se desea agregar la pieza.
 * @param piece puntero a la pieza que se desea agregar.
 * @return True si el lugar es valido, False en caso contrario.
 */
bool esUnLugarValido(char board[SIZE][SIZE], Barco* piece) {
	int row = getRowPos(piece);
	int column = getColPos(piece);


	if (column < 0 || (column + getLength(piece) - 1 > SIZE - 1 && isHorizontal(piece)))
	{
		return false;
	}
	if (row < 0 || (row + getLength(piece) - 1 > SIZE - 1 && !isHorizontal(piece)))
	{
		return false;
	}

	// verificar si existe otro barco
	for (int i = 0; i < getLength(piece); i++)
	{
		if (board[row][column] != BLANK)
		{
			return false;
		}

		if (isHorizontal(piece))
		{
			column++;
		}
		else
		{
			row++;
		}
	}
	return true;
}

/**
 * @brief Coloca una pieza en el tablero del jugador.
 *
 * @param piece puntero a la pieza que se desea colocar en el tablero.
 * @return True si la pieza se coloco correctamente, False en caso contrario.
 */
bool colocarPieza(Barco* piece) {

	int cord1;
	int cord2;
	char dir;

	printf("\n\n");
	printf("Que coordenadas te gustaria colocar el %s\n", getName(piece));
	scanf_s("%d", &cord1);
	scanf_s("%d", &cord2);
	printf("En que direccion te gustaria colocar tu pieza? (arriba - w, abajo - s, izquierda - a o derecha - d) \n");
	scanf_s(" %c", &dir);
	cord2 = cord2 - 1;
	setPiece(piece, cord1, cord2, dir);
	return esUnLugarValido(playerBoard, piece);
}

/**
 * @brief Coloca las piezas del jugador en el tablero.
 *
 * @param barcosPlayerArr arreglo de piezas del jugador.
 */
void placePlayerPieces(Barco *barcosPlayerArr) {
	for (int i = 0; i < 6; i++) {
	bool correctPlacement;
	do {
		mostrarTableroSimple();
		correctPlacement = colocarPieza(&barcosPlayerArr[i]);
			if (!correctPlacement) {
				printf("\nPor favor ingresa una posicion y direccion valida\n");
			}
	} while (!correctPlacement);

		agregarPiezaAlTablero(playerBoard, &barcosPlayerArr[i]);
	}
}

/**
 * @brief Genera una direccion aleatoria.
 *
 * @param n numero aleatorio utilizado para generar la direccion.
 * @return Caracter representando la direccion generada.
 */

char generateRandomDirection(int n) {
	char randomDirection;
	switch (n)
	{
	case 0:
		randomDirection = 'u';
		return randomDirection;
	case 1:
		randomDirection = 'd';
		return randomDirection;
	case 2:
		randomDirection = 'l';
		return randomDirection;
	case 3:
		randomDirection = 'r';
		return randomDirection;
	default:
		randomDirection = ' ';
		return randomDirection;
	}
}

/**
 * @brief Coloca las piezas del AI en el tablero.
 *
 * @param s Cadena vacia.
 * @param barcosComputerArr puntero al arreglo de barcos del AI.
 */
void colocarPiezasAI(char *s,Barco* barcosComputerArr) {
	srand(time(NULL));
	char tempBoard[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			tempBoard[i][j] = BLANK;
		}
	}
	bool correctPlacement;

	for (int i = 0; i < 6; i++) {
	do {
	int randomCol;
	int randomRow;
	int randomDirection;

		if (s == "") {
			randomCol = rand() % SIZE;
			randomRow = rand() % SIZE;
			int randomDirectionInt = rand() % 4;
			randomDirection = generateRandomDirection(randomDirectionInt);
		}
		setPiece(&barcosComputerArr[i], randomCol, randomRow, randomDirection);
		correctPlacement= esUnLugarValido(tempBoard, &barcosComputerArr[i]);

	} while (!correctPlacement);
		agregarPiezaAlTablero(tempBoard, &barcosComputerArr[i]);

	}
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%c",tempBoard[i][j]);
		}
	}
}

/**
 * @brief Verifica si un barco en el tablero ha sido hundido.
 *
 * @param board tablero en el que se busca el barco.
 * @param piece puntero al barco a verificar.
 * @return True si el barco ha sido hundido, False en caso contrario.
 */
bool estoyHundido(char board[SIZE][SIZE], Barco* piece) {

	int row = getRowPos(piece);
	int col = getColPos(piece);
	for (int i = 0; i < getLength(piece); i++)
	{
		if (board[row][col] != HIT) {
			return false;
		}
		if (isHorizontal(piece)) {
			col++;
		}
		else {
			row++;
		}

	}
	return true;
}

/**
 * @brief esta funcion es usada para colocar las piezas del jugador en el tablero
 *
 * @param barcosPlayerArr es un arreglo de barcos que contiene la informacion de los barcos del jugador
 *
 */
char turnoDelJugador(Barco* barcosComputerArr) {

	int rowAttack;
	int colAttack;
	do {
		printf("\n\n");
		printf("Que coordenadas te gustaria atacar | fila - columna\n");
		scanf_s("%d", &rowAttack);
		scanf_s("%d", &colAttack);
		colAttack += -1;
	} while ((rowAttack<0 || rowAttack > SIZE - 1) || (colAttack<0 || colAttack>SIZE - 1));

for (int i = 0; i < 6; i++) {
		int barcoComputerRow = getRowPos(&barcosComputerArr[i]);
		int barcoComputerCol = getColPos(&barcosComputerArr[i]);

		for (int j = 0; j < getLength(&barcosComputerArr[i]); j++)
		{
			if (barcoComputerRow == rowAttack && barcoComputerCol == colAttack)
			{
				computerBoard[rowAttack][colAttack] = HIT;
				if (!estoyHundido(computerBoard, &barcosComputerArr[i])) {
					*ptrPuntuacion += 20;

				}
				if (estoyHundido(computerBoard, &barcosComputerArr[i]))
				{
					char* result = getName(&barcosComputerArr[i]) + colAttack + rowAttack;
					return result;
				}
				char* result = "Barco Atacado en las coordenadas " + colAttack + rowAttack;
				return result;
			}
			if (isHorizontal(&barcosComputerArr[i]))
			{
				barcoComputerCol++;
			}
			else
			{
				barcoComputerRow++;
			}
			}
		}
	computerBoard[rowAttack][colAttack] = MISS;
	char* result = "Fallo en las coordenadas: " + colAttack + rowAttack;
	return result;
}

/**


*@brief Funcion que simula el turno de la IA en un juego de batalla naval.

*@param Barco* barcosJugadorArr Arreglo de barcos del jugador.

*@return char Resultado del ataque de la IA, puede ser "Barco Atacado en las coordenadas (x,y)", "Miss at (x,y)" o el nombre del barco hundido.
*/
char turnoIA(Barco* barcosJugadorArr) {

		int rowAttack = rand() % SIZE;
		int colAttack = rand() % SIZE;
	for (int i = 0; i < 6; i++)
	{
		int barcoPlayerRow = getRowPos(&barcosJugadorArr[i]);
		int barcoPlayerCol = getColPos(&barcosJugadorArr[i]);

		for (int j = 0; j < getLength(&barcosJugadorArr[i]); j++)
		{
			if (barcoPlayerRow == rowAttack && barcoPlayerCol == colAttack)
			{
				playerBoard[rowAttack][colAttack] = HIT;
				if (estoyHundido(playerBoard, &barcosJugadorArr[i]))
				{
					char* result = getName(&barcosJugadorArr[i]) + colAttack + rowAttack;
					return result;
				}
				char* result = "Barco Atacado en las coordenadas " + colAttack + rowAttack;
				return result;
			}

			if (isHorizontal(&barcosJugadorArr[i]))
			{
				barcoPlayerCol++;
			}
			else
			{
				barcoPlayerRow++;
			}
		}
	}
		playerBoard[rowAttack][colAttack] = MISS;
		char result = "Miss at ";
		return result;
}

// 1) Obtenemos el numero de posiciones ocupadas por el jugador y la ia 
// 2) Obtenemos el numero de aciertos en el tablero del jugador y la ia
// 3) verificamos si el numero de aciertos es igual al numero de posiciones ocupadas

/**
*@brief Funcion que determina si el juego ha terminado.
*@param Barco* computerBarcosArr Arreglo de barcos de la IA.
*@param Barco* playerBarcosArr Arreglo de barcos del jugador.
*@return int Resultado del juego, 0 si el juego sigue, 1 si el jugador gana, 2 si la IA gana, 3 empate.
*/
int gameOver(Barco* computerBarcosArr,Barco* playerBarcosArr) {
	int result = 0;
	int numPosicionesOcupadasIA = 0;
	for (int i = 0; i < 6; i++) {
		numPosicionesOcupadasIA += getLength(&computerBarcosArr[i]);
	}

	int numPosicionesOcupadasPlayer = 0;
	for (int i = 0; i < 6; i++) {
		numPosicionesOcupadasPlayer += getLength(&playerBarcosArr[i]);
	}
	

	int playerBoardHitTotal = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (playerBoard[i][j] == HIT)
			{
				playerBoardHitTotal++;
			}
		}
	}
	printf("%d\n", playerBoardHitTotal);
	if (playerBoardHitTotal == numPosicionesOcupadasPlayer )
	{
		result = result + 1;
	}

	int computerBoardHitTotal = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (computerBoard[i][j] == HIT)
			{
				computerBoardHitTotal++;
			}
		}
	}
	printf("%d\n", computerBoardHitTotal);
	if (computerBoardHitTotal == numPosicionesOcupadasIA )
	{
		result = result + 2;
	}

	return result;
}

/**

*@brief Funcion que anade un nuevo jugador al tablero de puntuaciones de un juego.
*@param struct Tablero* t Puntero al tablero de puntuaciones del juego.
*@param char* name Nombre del jugador a anadir.
*@param int puntuacion Puntuacion obtenida por el jugador.
*@return void.
*/
void anadirJugadorAlTablero(struct Tablero* t, char* name, int puntuacion) {
	for (int i = 0; i < 10; i++) {
		if (puntuacion > t->top10[i].puntuacion) {
			// Desplaza a los demás jugadores hacia abajo
			for (int j = 9; j > i; j--) {
				t->top10[j] = t->top10[j - 1];
			}
			// Añade al nuevo jugador en la posición i
			t->top10[i].nombre = name;
			t->top10[i].puntuacion = puntuacion;
			break;
		}
	}
}


void tableroPrueba() {
	printf("David              300\n");
	printf("Pedro              200\n");
	printf("Carlos             100\n");
	printf("Lucian              50\n\n\n");

	printf("Presiona `q` para volver al Menu Principal\n");

};


/**

*@brief Funcion que muestra el menú principal del juego y permite seleccionar opciones.
*@param void
*@return void
*/
void Menu() {
	int opcion=0;
	printf("\n\n\n\n\n\n\n");

	printf("                                             ");
	printf("##########################################\n");
	printf("                                             ");
	printf("#                                        #\n");
	printf("                                             ");
	printf("#       BIENVENIDO A HUNDIR LA FLOTA     #\n");
	printf("                                             ");
	printf("#                                        #\n");
	printf("                                             ");
	printf("##########################################\n\n");

	printf("                                               ");
	printf("Selecciona una opcion\n");
	printf("\n\n");
	printf("                                             ");
	printf("1) Iniciar Juego\n");
	printf("\n");
	printf("                                             ");
	printf("2) Puntuaciones\n");
	printf("\n");
	printf("                                             ");
	printf("3) Salir\n");
	while (opcion != 3) {
	scanf_s("%d", &opcion);
	if (opcion > 3 || opcion < 1) {
	printf("Opcion Invalida\n");
	}
	switch (opcion) {
	case 1:
		iniciarJuego();
		break;
	case 2:
		tableroPrueba();
		break;
	case 3:
		salirDelJuego();
		}
	}


}

/**

*@brief Funcion que se encarga de cerrar el programa.
*@param void
*@return void
*/
void salirDelJuego() {
	// Limpia la consola
	system("clear");

	// Cierra el programa
	system("exit");
}


/**

*@brief Funcion que determina si se desea volver al menu principal del juego.
*@param char opc Caracter ingresado por el usuario para indicar si desea volver al menu principal ('y' o 'n').
*@return bool True si se desea volver al menu principal, False en caso contrario.
*/
bool salirAlMenuPrincipal(char opc) {
	if (opc == 'y') {
		return true;
	}
	else if (opc == 'n') {
		return false;
	}

}


/**

*@brief Funcion que muestra el tablero de puntuaciones del juego y permite volver al menu principal.
*@param void
*@return void
*/
void puntuaciones() {
	printf("Tablero de Posiciones\n");
	for (int i = 0; i < 10; i++) {
		if (t1.top10[i].nombre && t1.top10[i].puntuacion) {
			printf("%d  ", i + 1);
			printf("%s  ", t1.top10[i].nombre);
			printf("%d\n", t1.top10[i].puntuacion);
		}
	}
	printf("\n");
	printf("\n");
	printf("\n");
	printf("Presiona `q` para volver al Menu Principal\n");
	char opc='o';
	do {
		scanf_s("%c", &opc);
		if (opc == 'q') {
			Menu();
		}
	} while (opc!='q');
}

/**


*@brief Funcion que inicia una partida del juego.

*@param void

*@return void
*/
void iniciarJuego() {
	*ptrPuntuacion = 0;
	rellenarTableros();

	// Piezas jugador
	Barco barcosPlayerArr[6] =
	{ { "Portaviones", 4, 'P', 0, 0, NULL } , { "Crucero", 3, 'C', 0, 0, NULL }, { "Crucero", 3, 'C', 0, 0, NULL } ,
	 { "Patrulleras", 2, 'L', 0, 0, NULL } , { "Patrulleras", 2, 'L', 0, 0, NULL } , { "Patrulleras", 2, 'L', 0, 0, NULL } };

	// Piezas computadora
	Barco barcosComputerArr[6] =
	{ { "Portaviones", 4, 'P', 0, 0, NULL } , { "Crucero", 3, 'C', 0, 0, NULL }, { "Crucero", 3, 'C', 0, 0, NULL } ,
	 { "Patrulleras", 2, 'L', 0, 0, NULL } , { "Patrulleras", 2, 'L', 0, 0, NULL } , { "Patrulleras", 2, 'L', 0, 0, NULL } };


	colocarPiezasAI("", &barcosComputerArr);
	placePlayerPieces(&barcosPlayerArr);

	mostrarTableroSimple();
	do {
		char turnoJugador = turnoDelJugador(&barcosComputerArr);
		char turnoComputer = turnoIA(&barcosPlayerArr);
		mostrarTableroConInformacion(turnoJugador, turnoComputer,*ptrPuntuacion);
	} while (gameOver(&barcosComputerArr, &barcosPlayerArr) == 0);
	int resultadoJuego = gameOver(&barcosComputerArr,&barcosPlayerArr);
	if (resultadoJuego == 1)
	{
		printf("Perdiste necesitas practicar mas!.\n");
		printf("Volver Al menu Principal? y / n.\n");
		char opcion='o';
		do {
		scanf_s("%c", &opcion);
		bool volverAlMenu = salirAlMenuPrincipal(opcion);
		if (volverAlMenu == true) {
			Menu();
		}
		else if (volverAlMenu == false) {
			salirDelJuego();
		}
		} while (opcion != 'y' || opcion != 'n');
	}
	else if (resultadoJuego == 2)
	{
	char name[10];
		printf("Felicidades Ganaste!\n");
		printf("Ingresa tu nombre!\n");

		do {
			scanf_s("%s",name, 10);
		}while (strlen(name) < 5);
	anadirJugadorAlTablero(&t1,name,puntuacion);

		printf("\n");
		printf("Volver Al menu Principal? y / n.\n");
		char opcion='o';
		do {
		scanf_s("%c", &opcion);
		bool volverAlMenu = salirAlMenuPrincipal(opcion);
		if (volverAlMenu == true) {
			Menu();
		}
		else if (volverAlMenu == false) {
			salirDelJuego();
		}
		} while (opcion != 'y' || opcion != 'n');

	}
	else if (resultadoJuego == 3)
	{
		printf("Empate!\n");
		printf("Volver Al menu Principal? y / n.\n");
		char opcion='o';
		do {
		scanf_s("%c", &opcion);
		bool volverAlMenu = salirAlMenuPrincipal(opcion);
		if (volverAlMenu == true) {
			Menu();
		}
		else if (volverAlMenu == false) {
			salirDelJuego();
		}
		} while (opcion != 'y' || opcion != 'n');
	}
}

/**
* @brief Punto de entrada del programa, donde comienza la ejecucion.
* @param void
* @return void
*/
void main() {
	Menu();

};





