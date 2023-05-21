#ifndef MAIN_C_INIZIALIZZAZIONI_H
#define MAIN_C_INIZIALIZZAZIONI_H
#include "struttureDati.h"
#include "globali.h"

void inizializzareMappa(player *giocatore, int tipoMappa);
void inizializzarePosScansione(coordinate posizioni[CELLE_LARGO_RAGGIO]);
void inizializzareStruttura(datiPartita *struttura);
player inizializzareGiocatore(player giocatore);

#endif //MAIN_C_INIZIALIZZAZIONI_H
