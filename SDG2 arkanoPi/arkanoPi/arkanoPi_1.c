
#include "arkanoPi_1.h"
#define FLAG_TECLA 0x01
#define FLAG_PELOTA 0x02
#define FLAG_JOYSTICK 0x04
#define FLAG_RAQUETA_IZQUIERDA 0x08
#define FLAG_RAQUETA_DERECHA 0X10
#define FLAG_FINAL_JUEGO 0x20

static volatile tipo_juego juego;

//------------------------------------------------------
// FUNCIONES DE ACCION
//------------------------------------------------------

// void InicializaJuego (void): funcion encargada de llevar a cabo
// la oportuna inicialización de toda variable o estructura de datos
// que resulte necesaria para el desarrollo del juego.
void InicializaJuego (void) {
	// A completar por el alumno...
	int Pinicial[MATRIZ_ANCHO][MATRIZ_ALTO] = {
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,1,0,1,0,0},
			{0,1,1,0,0,1,0},
			{0,0,0,0,0,0,1},
			{0,0,0,0,0,0,1},
			{0,1,1,0,0,1,0},
			{0,1,1,0,1,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
	};
	juego.estado = WAIT_PUSH;
	PintaMensajeInicialPantalla((tipo_pantalla*)(&(juego.arkanoPi.pantalla)),(tipo_pantalla*)(&(Pinicial)));
}

// void MueveRaquetaIzquierda (void): funcion encargada de ejecutar
// el movimiento hacia la izquierda contemplado para la raqueta.
// Debe garantizar la viabilidad del mismo mediante la comprobación
// de que la nueva posición correspondiente a la raqueta no suponga
// que ésta rebase o exceda los límites definidos para el área de juego
// (i.e. al menos uno de los leds que componen la raqueta debe permanecer
// visible durante todo el transcurso de la partida).
void MueveRaquetaIzquierda (void) {
	// A completar por el alumno...
	if((juego.arkanoPi.raqueta.x + 2) > 0){
		juego.arkanoPi.raqueta.x -= 1;
	}

}

// void MueveRaquetaDerecha (void): función similar a la anterior
// encargada del movimiento hacia la derecha.
void MueveRaquetaDerecha (void) {
	// A completar por el alumno...
	if(((juego.arkanoPi.raqueta.x) - 2) < 7){
		juego.arkanoPi.raqueta.x += 1;
	}
}


// void MovimientoPelota (void): función encargada de actualizar la
// posición de la pelota conforme a la trayectoria definida para ésta.
// Para ello deberá identificar los posibles rebotes de la pelota para,
// en ese caso, modificar su correspondiente trayectoria (los rebotes
// detectados contra alguno de los ladrillos implicarán adicionalmente
// la eliminación del ladrillo). Del mismo modo, deberá también
// identificar las situaciones en las que se dé por finalizada la partida:
// bien porque el jugador no consiga devolver la pelota, y por tanto ésta
// rebase el límite inferior del área de juego, bien porque se agoten
// los ladrillos visibles en el área de juego.
void MovimientoPelota (void) {
	// A completar por el alumno...
	int siguientex = juego.arkanoPi.pelota.x + juego.arkanoPi.pelota.xv;
	int siguientey = juego.arkanoPi.pelota.y + juego.arkanoPi.pelota.yv;
	if ((siguientey == 6 && juego.arkanoPi.pantalla.matriz[siguientex][siguientey] == 0) || CalculaLadrillosRestantes((tipo_pantalla*)(&(juego.arkanoPi.ladrillos))) == 0){
		FinalJuego_isr();
	}
	else{
		if ((juego.arkanoPi.pantalla.matriz[siguientex][siguientey] == 1 && siguientey < 2) || siguientey < 0 ){ //golpe ladrillos %falta borrar
			juego.arkanoPi.ladrillos.matriz[siguientex][siguientey] = 0;
			juego.arkanoPi.pelota.yv = 1;

		}
		if (siguientex < 0 || siguientex > 9) { //golpe pared lado
			juego.arkanoPi.pelota.xv = -juego.arkanoPi.pelota.xv;

		}

		if (juego.arkanoPi.pantalla.matriz[siguientex][siguientey] == 1 && siguientey == 6){
			if(siguientex == (juego.arkanoPi.raqueta.x + 1)){ //raqueta centro
				juego.arkanoPi.pelota.xv = 0;
				juego.arkanoPi.pelota.yv = -1;
			}
			if (siguientex == (juego.arkanoPi.raqueta.x)){ //raqueta izda

				juego.arkanoPi.pelota.xv = -1;
				juego.arkanoPi.pelota.yv = -1;
			}
			if (siguientex == (juego.arkanoPi.raqueta.x + 2)){ //raqueta dcha
				juego.arkanoPi.pelota.xv = 1;
				juego.arkanoPi.pelota.yv = -1;
			}
		}

		juego.arkanoPi.pelota.x += juego.arkanoPi.pelota.xv;
		juego.arkanoPi.pelota.y += juego.arkanoPi.pelota.yv;
	}
}

// void FinalJuego (void): función encargada de mostrar en la ventana de
// terminal los mensajes necesarios para informar acerca del resultado del juego.
void FinalJuego (void) {
	// A completar por el alumno...

	int Perdido[MATRIZ_ANCHO][MATRIZ_ALTO] = {
				{0,0,0,0,0,0,0},
				{0,0,1,1,1,0,0},
				{0,0,0,1,0,0,0},
				{0,0,1,0,1,0,0},
				{0,0,0,0,0,0,0},
				{0,0,1,1,1,0,0},
				{0,0,1,0,1,0,0},
				{0,0,1,1,1,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
		};
		int Ganado[MATRIZ_ANCHO][MATRIZ_ALTO] = {
				{0,0,0,0,0,0,0},
				{0,0,1,1,1,0,0},
				{0,0,1,0,1,0,0},
				{0,0,1,1,1,0,0},
				{0,0,0,0,0,0,0},
				{0,0,1,1,1,0,0},
				{0,0,0,1,0,0,0},
				{0,0,1,0,1,0,0},
				{0,0,0,0,0,0,0},
				{0,0,0,0,0,0,0},
		};
		if(CalculaLadrillosRestantes((tipo_pantalla*)(&(juego.arkanoPi.ladrillos))) == 0){
			PintaPantallaPorTerminal((tipo_pantalla*)(&(Ganado)));
			printf("YOU WIN");
			printf("\n");
		}
		else {
			PintaPantallaPorTerminal((tipo_pantalla*)(&(Perdido)));
			printf("GAME OVER");
			printf("\n");
		}
		ReseteaJuego();
	}


//void ReseteaJuego (void): función encargada de llevar a cabo la
// reinicialización de cuantas variables o estructuras resulten
// necesarias para dar comienzo a una nueva partida.
void ReseteaJuego (void) {
	// A completar por el alumno...
	InicializaArkanoPi((tipo_arkanoPi*)(&(juego.arkanoPi)));
}
//------------------------------------------------------
// FUNCIONES DE COMPROBACION
//------------------------------------------------------
volatile int flags= 0;

void RaquetaIzquierda_isr(void){flags |= FLAG_RAQUETA_IZQUIERDA;}
void RaquetaDerecha_isr(void){flags |= FLAG_RAQUETA_DERECHA;}
void Tecla_isr(void){flags |= FLAG_TECLA;}
void Pelota_isr(void){flags |= FLAG_PELOTA;}
void Joystick_isr(void){flags |= FLAG_JOYSTICK;}
void FinalJuego_isr(void){flags |= FLAG_FINAL_JUEGO;}

int CompruebaTeclaRaquetaIzquierda(fsm_t* this){
	return (flags & FLAG_RAQUETA_IZQUIERDA) ;
}
int CompruebaTeclaRaquetaDerecha(fsm_t* this){
	return (flags & FLAG_RAQUETA_DERECHA);
}
int CompruebaTeclaPulsada(fsm_t* this){
	return (flags & FLAG_TECLA);
}
int CompruebaJoystick(fsm_t* this){
	return (flags & FLAG_JOYSTICK);
}
int CompruebaTeclaPelota(fsm_t* this){
	return (flags & FLAG_PELOTA);
}
int CompruebaFinalJuego(fsm_t* this){
	return (flags & FLAG_FINAL_JUEGO);
}


//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------

// int systemSetup (void): procedimiento de configuracion del sistema.
// Realizará, entra otras, todas las operaciones necesarias para:
// configurar el uso de posibles librerías (e.g. Wiring Pi),
// configurar las interrupciones externas asociadas a los pines GPIO,
// configurar las interrupciones periódicas y sus correspondientes temporizadores,
// crear, si fuese necesario, los threads adicionales que pueda requerir el sistema
int systemSetup (void) {
	// A completar por el alumno...
return 0;
}

int main (){
	// Configuracion e inicializacion del sistema
	// A completar por el alumno...


InicializaJuego();
InicializaArkanoPi((tipo_arkanoPi*)(&(juego.arkanoPi)));
PintaPantallaPorTerminal((tipo_pantalla*)(&(juego.arkanoPi.pantalla)));

void InicializaJuego (fsm_t* this){
	InicializaJuego(void a);}

fsm_trans_t TransicionesArkano[] = {
		{WAIT_START,CompruebaTeclaPulsada,WAIT_PUSH,InicializaJuego},
		{WAIT_PUSH,CompruebaJoystick,WAIT_PUSH,ControlJoystick},
		{WAIT_PUSH,CompruebaTeclaPelota,WAIT_PUSH,MovimientoPelota},
		{WAIT_PUSH,CompruebaTeclaRaquetaIzquierda,WAIT_PUSH,MueveRaquetaIzquierda},
		{WAIT_PUSH,CompruebaTeclaRaquetaDerecha,WAIT_PUSH,MueveRaquetaDerecha},
		{WAIT_PUSH,CompruebaFinalJuego,WAIT_END,FinalJuego},
		{WAIT_END,CompruebaTeclaPulsada,WAIT_START,ReseteaJuego},
		{-1,NULL,-1,NULL},
};
fsm_t* arkanoPi_fsm = fsm_new(WAIT_START,TransicionesArkano,NULL);

	while (1) {
		if(kbhit()) { // Funcion que detecta si se ha producido pulsacion de tecla alguna
			juego.teclaPulsada = kbread(); // Funcion que devuelve la tecla pulsada

			// Interpretacion de las pulsaciones para cada posible estado del sistema
			if( juego.estado == WAIT_START ) { // Cualquier pulsacion da comienzo al juego...
				// Descomente ambas lineas y sustituya cada etiqueta XXXXXXX por lo que corresponda en cada caso...
				InicializaJuego();
				juego.estado = WAIT_PUSH;
			}
			else if( juego.estado == WAIT_END ) { // Cualquier nos devuelve al estado inicial...
				// Descomente ambas lineas y sustituya cada etiqueta XXXXXXX por lo que corresponda en cada caso...
				ReseteaJuego();
				juego.estado = WAIT_START;
			}
			else { // Si estamos jugando...
				switch(juego.teclaPulsada) {
					case 'i':
						// A completar por el alumno...
						MueveRaquetaIzquierda();
						MovimientoPelota();
						if(CompruebaFinalJuego() == 1){
							FinalJuego();
						}
						else{
							ActualizaPantalla((tipo_arkanoPi*)(&(juego.arkanoPi)));
							PintaPantallaPorTerminal((tipo_pantalla*)(&(juego.arkanoPi.pantalla)));
						}

						break;

					case 'o':
						// A completar por el alumno...
						MueveRaquetaDerecha();
						MovimientoPelota();
						ActualizaPantalla((tipo_arkanoPi*)(&(juego.arkanoPi)));
						PintaPantallaPorTerminal((tipo_pantalla*)(&(juego.arkanoPi.pantalla)));


						break;

					case 'p':
						// A completar por el alumno...
						MovimientoPelota();

						ActualizaPantalla((tipo_arkanoPi*)(&(juego.arkanoPi)));
						PintaPantallaPorTerminal((tipo_pantalla*)(&(juego.arkanoPi.pantalla)));


						break;

					case 'q':
						exit(0);
						break;

					default:
						printf("INVALID KEY!!!\n");
						break;
				}
			}
		}
	}
}
