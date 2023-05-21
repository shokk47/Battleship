#ifndef BATTAGLIA_NAVALE_MAIN_H
#define BATTAGLIA_NAVALE_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "struttureDati.h"

#define MAX_DIM_STRINGA_POS     4
#define MAX_DIM_STRINGA_NOME    20

#define PLAYER_UNO              1
#define PLAYER_DUE              2

#define MAPPA_NAVI              1
#define MAPPA_COLPI             2

#define ERR                    -1
#define VERTICALE               1
#define ORIZZONTALE             2


#define ESCI                    0
#define CONTINUA                1
#define SALVARE                 2
#define BACK                    5

#define SEGNA_COLPO             1
#define SEGNA_NAVE              2
#define SEGNA_COLPO_MANCATO     3
#define SEGNA_NAVE_MANCATO      4
#define SEGNA_RADAR_NAVE        5
#define SEGNA_RADAR_VUOTO       6

#define DISTANZA_NAVI           3
#define CELLE_SCANSIONARE       9

#define MAX_LARGO_RAGGIO        3
#define MAX_BOMBARDAMENTO       1
#define MAX_RADAR               3
#define TURNO_BOMBARDAMENTO     5

#define CELLE_RADAR             9
#define CELLE_LARGO_RAGGIO      9
#define AREA_LARGO_RAGGIO       3

#define ACQUA                   '.'
#define COLPITO                 '#'
#define AFFONDATO               '@'
#define MANCATO                 '~'
#define RADAR_NAVE              '?'
#define RADAR_VUOTO             '*'

#define ID_PORTAEREI            'A'
#define ID_CORAZZATA            'B'
#define ID_INCROCIATORE         'C'
#define ID_CACCIATORPEDINIERE   'D'
#define ID_NAVESUPPORTO         'E'

#define NUM_PORTAEREI           1
#define NUM_CORAZZATA           2
#define NUM_INCROCIATORE        3
#define NUM_CACCIATORPEDINIERE  4
#define NUM_NAVESUPPORTO        5
#define TOTALE_NAVI             15

#define LEN_PORTAEREI           5
#define LEN_CORAZZATA           4
#define LEN_INCROCIATORE        3
#define LEN_CACCIATORPEDINIERE  2
#define LEN_NAVESUPPORTO        1

int leggereRispostaValida(int min, int max);
void ottenereCoordinate(coordinate *posizione);
char convertiPosizioneInLettera(int num);

#endif //BATTAGLIA_NAVALE_MAIN_H
