#ifndef _ARKANOPI_H_
#define _ARKANOPI_H_

#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h> // A descomentar en posteriores sesiones

#include "kbhit.h" // para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas

#include "arkanoPiLib.h"

typedef enum {
	WAIT_START,
	WAIT_PUSH,
	WAIT_END} tipo_estados_juego;

typedef struct {
	tipo_arkanoPi arkanoPi;
	tipo_estados_juego estado;
	char teclaPulsada;
} tipo_juego;
typedef struct fsm_t fsm_t;

typedef int(*fsm_input_func_t)(fsm_t*);
typedef void(*fsm_output_func_t)(fsm_t*);

typedef struct fsm_trans_t{
	int EstadoOrigen;
	fsm_input_func_t in;
	int EstadoDestino;
	fsm_output_func_t out;
}fsm_trans_t;

struct fsm_t{
	int EstadoActual;
	fsm_trans_t* TransicionesArkano;
	void* user_data;
};

fsm_t* fsm_new(int estado, fsm_trans_t* TransicionesArkano,void* user_data);
void fsm_init(fsm_t* this, int estado, fsm_trans_t* TransicionesArkano,void* user_data);
void fsm_fire(fsm_t* this);
void fsm_destroy(fsm_t* this);




//------------------------------------------------------
// FUNCIONES DE ACCION
//------------------------------------------------------

void InicializaJuego (void);
void MueveRaquetaIzquierda (void);
void MueveRaquetaDerecha (void);
void MovimientoPelota (void);
void FinalJuego (void);
void ReseteaJuego (void);

//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------
int systemSetup (void);

#endif /* ARKANOPI_H_ */
