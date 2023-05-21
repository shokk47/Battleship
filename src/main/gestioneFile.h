#ifndef BATTAGLIA_NAVALE_GESTIONEFILE_H
#define BATTAGLIA_NAVALE_GESTIONEFILE_H

#include "struttureDati.h"

void salvarePartita (datiPartita struttura, char posizione[]);
void caricarePartita (datiPartita *struttura, char posizione[]);
int  verificareCaricamento(char posizione[]);

#endif //BATTAGLIA_NAVALE_GESTIONEFILE_H
