#include "inizializzazioni.h"
/*
 *  Funzione: inizializzareMappa()
 *  Input  : 1) Giocatore, dati del giocatore da inizializzare, player
 *           2) tipoMappa, valore che identifica MAPPA_NAVI o MAPPA_COLPI, intero,	MAPPA_NAVI <= tipoMappa <= MAPPA_COLPI
 *           3) MAPPA_NAVI, identificativo della mappaNavi di un giocatore, intero, variabile globale
 *           4) RIGHE, numero massimo di righe di una mappa, intero, variabile globale
 *           5) COLONNE, numero massimo di colonne di una mappa, intero, variabile globale
 *           6) ACQUA, id dell'acqua da scrivere in coordinate posizione di mappa, carattere, variabile globale
 *  Output : 1) Giocatore, dati del giocatore con la mappa inizializzata, player
 *  Descrizione: La funzione inizializza il campo mappa di tipo tipoMappa di giocatore
 */
void inizializzareMappa(player *giocatore, int tipoMappa){
    coordinate posizione;
    int r;
    int c;

    scrivereCoordinateX(&posizione, 0);
    scrivereCoordinateY(&posizione, 0);
    r = 0;

    while(r<RIGHE){
        scrivereCoordinateY(&posizione, 0);
        c = 0;
        while(c<COLONNE){
            if(tipoMappa == MAPPA_NAVI) scrivereMappaNavi(giocatore, posizione, ACQUA);
            else                        scrivereMappaColpi(giocatore, posizione, ACQUA);
            incrementareCoordinateY(&posizione);
            c++;
        }
        incrementareCoordinateX(&posizione);
        r++;
    }
}
/*
 *  Funzione: inizializzarePosScansione()
 *  Input  : 1) Posizioni, contiene le posizioni, da inizializzare a –1, per colpo a largo raggio e radar, vettore di coordinate, dimensione = CELLE_LARGO_RAGGIO
 *           2) CELLE_LARGO_RAGGIO, numero di elementi del vettore posizioni, intero, variabile globale
 *  Output : 1) Posizioni, cordinate di posizioni inizializzate a -1, vettore di coordinate, dimensione = CELLE_LAERGO_RAGGIO
 *  Descrizione: La funzione inizializza un vettore di coordinate a -1
 */
void inizializzarePosScansione(coordinate posizioni[CELLE_LARGO_RAGGIO]){
    int i = 0;
    while(i<CELLE_LARGO_RAGGIO){
        scrivereCoordinateX(posizioni+i, -1);
        scrivereCoordinateY(posizioni+1, -1);
        i++;
    }
}
/*
 *  Funzione: inizializzareStruttura()
 *  Input  : 1) Struttura, dati della partita da inizializzare, datiPartita
 *           2) Supporto, copia del giocatore singolo, player
 *           3) PLAYER_UNO, identificativo del player uno, intero, variabile globale
 *  Output : 1) Struttura, dati della partita inizializzata, datiPartita
 *  Descrizione: La funzione inizializza la struttura datiPartita
 */
void inizializzareStruttura(datiPartita *struttura) {
    player supporto;
    scrivereTurniTotali(struttura, 1);
    scrivereTurnoPartita(struttura, PLAYER_UNO);
    scrivereEsitoColpi(struttura, 0);

    supporto = inizializzareGiocatore(leggereDatiGiocatore1(*struttura));
    scrivereDatiGiocatore1(struttura, supporto);

    supporto = inizializzareGiocatore(leggereDatiGiocatore2(*struttura));
    scrivereDatiGiocatore2(struttura, supporto);
}
/*
 *  Funzione: inizializzareGiocatore()
 *  Input  : 1) Giocatore, dati del giocatore da inizializzare, player
 *           2) MAPPA_NAVI, id della mappaNavi di giocatore, intero, variabile globale
 *           3) MAPPA_COLPI, id della mappaColpi di giocatore, intero, variabile globale
 *  Output : 1) Giocatore, dati del giocatore inizializzati, player
 *  Descrizione: La funzione inizializza la struttura player
 */
player inizializzareGiocatore(player giocatore){
    inizializzareMappa(&giocatore, MAPPA_NAVI);
    inizializzareMappa(&giocatore, MAPPA_COLPI);
    scrivereLargoRaggio(&giocatore, 0);
    scrivereBombardamentoAereo(&giocatore,0);
    scrivereRadar(&giocatore, 0);
    scrivereNaviAffondate(&giocatore, 0);
    return giocatore;
}