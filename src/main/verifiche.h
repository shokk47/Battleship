#ifndef MAIN_C_VERIFICHE_H
#define MAIN_C_VERIFICHE_H

#include "struttureDati.h"
#include "globali.h"

int verificarePresenzaNave(player giocatore, coordinate posizione);
int verificareNave(player giocatore, coordinate posizione, int direzione, int lunghezzaNave);
int verificareNaveAffondata(player giocatore, coordinate colpo);
int verificareScansione(coordinate posizione);
int verificarePresenza(player giocatore, coordinate posizione, char verificare);
void verificareCoordinate(char stringaCoordinate[MAX_DIM_STRINGA_POS], coordinate *posizione);

#endif //MAIN_C_VERIFICHE_H
