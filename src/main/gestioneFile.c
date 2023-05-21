#include <stdio.h>
#include <stdlib.h>

#include "gestioneFile.h"
#include "stampe.h"

/*
 *  Funzione: salvarePartita()
 *  Input  : 1) Dati, file su cui salvare i dati della partita,	FILE
 *           2) Struttura, struttura dati da salvare nel file, datiPartita
 *           3) Posizione, percorso del file in cui scrivere, vettore di caratteri, variabili globali che contengono i percorsi ai file
 *  Output : 1) Dati, file che contiene il salvataggio,	FILE

 *  Descrizione: La funzione esegue il backup della partita
 */
void salvarePartita(datiPartita struttura, char posizione[]) {
    FILE *dati = fopen(posizione, "w");
    if (dati != NULL) {
        fwrite (&struttura, sizeof(datiPartita), 1, dati);
    }
    else stampareErrore(WFF);
    fclose (dati);
}
/*
 *  Funzione: caricarePartita()
 *  Input  : 1) Dati, file da cui leggere i dati della partita salvata,	FILE
 *           2) Struttura, struttura dati in cui salvare il backup partita,	datiPartita
 *           3) Posizione, percorso del file in cui scrivere, vettore di caratteri, variabili globali che contengono i percorsi ai file
 *  Output : 1) Struttura, struttura dati con i dati del backup caricati, datiPartita
 *  Descrizione: La funzione carica il backup della partita
 */
void caricarePartita (datiPartita *struttura, char posizione[]) {
    FILE *dati;
    dati = fopen (posizione, "r");
    fread (struttura, sizeof(datiPartita), 1, dati);
    fclose (dati);
}
/*
 *  Funzione: verificareCaricamento()
 *  Input  : 1) Dati, file su cui vengono salvati i dati della partita,	FILE
 *           2) Posizione, percorso del file in cui scrivere, vettore di caratteri, variabili globali che contengono i percorsi ai file
 *  Output : 1) Verifica, esito della verifica di esistenza del file, intero, 0 <= verifica <= 1
 *  Descrizione: La funzione verifica se è il file esiste ed è possibile aprirlo
 */
int verificareCaricamento(char posizione[]){
    FILE *dati;
    int verifica;
    dati = fopen (posizione, "r");
    if (dati == NULL) {
        stampareErrore(FNE);
        verifica = 0;
    }else verifica = 1;
    fclose (dati);
    return verifica;
}