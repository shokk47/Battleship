#include <stdio.h>
#include <stdlib.h>

#include "struttureDati.h"
#include "stampe.h"
#include "globali.h"

/*
 *  Funzione: stampareFile()
 *  Input  : 1) Posizione, contiene la posizione del file in cui scrivere, vettore di caratteri, tutte le variabili globali che corrispondono al percorso dei file
 *           2) File, file di cui stampare il contenuto, FILE
 *           3) OFF, id dell'errore "Impossibile aprire file", intero, variabile globale
 *  Output : 0) --
 *  Descrizione: La funzione stampa il contenuto di un file per intero
 */
void stampareFile(char posizione[]){
    FILE *file;
    char text;
    file = fopen(posizione, "r");
    if(file != NULL) {
        while ((text = fgetc(file)) != EOF) {
            printf("%c", text);
        }
    }else stampareErrore(OFF);  // Impossibile aprire file
    fclose(file);
}
/*
 *  Funzione: stampareMappaNavi()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore, player
 *           3) letturaMappa, valore in coordinate posizione, carattere, tutti i caratteri ammessi nella mappaNavi
 *           4) RIGHE, numero di righe della mappa, intero, variabile globale
 *           5) COLONNE, numero di colonne della mappa, intero, variabile globale
 *  Output : 0) --
 *  Descrizione: La funzione stampa la mappaNavi
 */
void stampareMappaNavi(player giocatore){
    coordinate posizione;
    char letturaMappa;
    int  r;
    int  c;

    r = 0;
    scrivereCoordinateX(&posizione,r);

    // STAMPA IL NUMERO DI COLONNE
    printf("\n             MAPPA NAVI\n\n");
    printf("   A B C D E F G H I J K L M N O P\n");

    // STAMPA RIGA PER RIGA
    while(r<RIGHE){
        c = 0;
        scrivereCoordinateY(&posizione,c);

        // STAMPA IL NUMERO DI RIGA IN CONTEMPORANEA ALLA STAMPA DELLA RIGA
        if(r < 9){
                printf(" %d ", r+1);
        }else   printf("%d ", r+1);

        // STAMPA DELL'INTERA RIGA
        while(c<COLONNE){
            letturaMappa = leggereMappaNavi(giocatore, posizione);
            printf("%c ", letturaMappa);
            incrementareCoordinateY(&posizione);
            c++;
        }
        printf("\n");
        incrementareCoordinateX(&posizione);
        r++;
    }
}
/*
 *  Funzione: stampareMappe()
 *  Input  : 1) Giocatore, dati del giocatore corrente, player
 *           2) mappaNavi, coordinate per la mappaNavi, coordinate
 *           3) mappaColpi, coordinate per la mappaColpi, coordinate
 *           4) letturaMappa, valore in coordinate mappaNavi/mappaColpi, carattere
 *           5) stampaRighe, valore del numero di riga di mappaNavi/mappaColpi, intero, 0 <= stampareRighe <= 15
 *           4) RIGHE, numero di righe della mappa, intero, variabile globale
 *           5) COLONNE, numero di colonne della mappa, intero, variabile globale
 *  Output : 0) --
 *  Descrizione: La funzione stampa mappaNavi e mappaColpi in contemporanea
 */
void stampareMappe(player giocatore){
    coordinate mappaNavi;
    coordinate mappaColpi;
    char letturaMappa;
    int  r;
    int  c;
    int  stampaRighe;

    r = 0;
    scrivereCoordinateX(&mappaNavi,r);
    scrivereCoordinateX(&mappaColpi,r);

    // STAMPA IL NUMERO DI COLONNE
    printf("\n             MAPPA NAVI                           MAPPA COLPI\n\n");
    printf("   A B C D E F G H I J K L M N O P      A B C D E F G H I J K L M N O P\n");

    // STAMPA RIGA PER RIGA DI MAPPANAVI E MAPPACOLPI
    while(r<RIGHE){
        c = 0;
        scrivereCoordinateY(&mappaNavi, c);
        scrivereCoordinateY(&mappaColpi, c);

        // STAMPA IL NUMERO DI RIGA DI MAPPANAVI IN CONTEMPORANEA ALLA STAMPA DELLA RIGA
        stampaRighe = leggereCoordinateX(mappaNavi);
        if(stampaRighe < 9){
              printf(" %d ", stampaRighe+1);                // +1, PERCHE' LA MATRICE PARTE DA 0, MA LA MAPPA DA 1
        }else printf("%d ", stampaRighe+1);                 // +1, PERCHE' LA MATRICE PARTE DA 0, MA LA MAPPA DA 1

        // STAMPA INTERA RIGA MAPPANAVI
        c = 0;
        while(c<COLONNE){
            letturaMappa = leggereMappaNavi(giocatore, mappaNavi);
            printf("%c ", letturaMappa);
            incrementareCoordinateY(&mappaNavi);
            c++;
        }

        // STAMPA IL NUMERO DI RIGA DI MAPPACOLPI IN CONTEMPORANEA ALLA STAMPA DELLA RIGA
        stampaRighe = leggereCoordinateX(mappaColpi);
        if(stampaRighe < 9){
              printf("   %d ", stampaRighe+1);              // +1, PERCHE' LA MATRICE PARTE DA 0, MA LA MAPPA DA 1
        }else printf("  %d ", stampaRighe+1);               // +1, PERCHE' LA MATRICE PARTE DA 0, MA LA MAPPA DA 1

        // STAMPA INTERA RIGA MAPPACOLPI
        c = 0;
        while(c<COLONNE){
            letturaMappa = leggereMappaColpi(giocatore, mappaColpi);
            printf("%c ", letturaMappa);
            incrementareCoordinateY(&mappaColpi);
            c++;
        }

        printf("\n");
        incrementareCoordinateX(&mappaNavi);
        incrementareCoordinateX(&mappaColpi);
        r++;
    }
}
/*
 *  Funzione: stampareErrore()
 *  Input  : 1) id, valore che identifica il tipo di errore, intero, 0 <= id <= 12
 *           2) MAX_DIM_STRINGA_NOME, dimensione massima della stringa nomePlayer di giocatore, vettore di caratteri, variabile globale
 *  Output : 0) --
 *  Descrizione: La funzione stampa il messaggio corrispondente all'id errore
 */
void stampareErrore(int id){
    printf("[ERRORE] ");
    if(id == OFF)       printf("Impossibile aprire file\n");
    else if(id == WFF)  printf("Impossibile salvare la partita\n");
    else if(id == FNE)  printf("Non esiste una partita salvata\n");
    else if(id == SLO)  printf("Devi inserire un nome di lunghezza MAX: %d\n", MAX_DIM_STRINGA_NOME);
    else if(id == SOL)  printf("Nave non rientra nella mappa\n");
    else if(id == SDS)  printf("Distanza tra le navi non rispettata\n");
    else if(id == ISP)  printf("Posizione nave non valida\n");
    else if(id == SNA)  printf("Non puoi usare questo tipo di colpo\n");
    else if(id == SAS)  printf("Colpo gia' lanciato\n");
    else if(id == SOM)  printf("Le coordinate inserite non corrispondono a una cella della mappa\n");
    else if(id == ANC)  printf("Risposta non valida, riprova : ");
    else if(id == ECS)  printf("Tutte le coordinate scelte sono state gia colpite, riprova\n");
    else if(id == EAL)  printf("Tutte le coordinate sono state gia' scansionate, riprova\n");
}
/*
 *  Funzione: stampareEsitoColpo()
 *  Input  : 1) Colpo, coordinate del colpo lanciato dal giocatore, coordinate
 *           2) Esito, valore che indica l'esito del lancio del colpo, intero, =COLPITO || =AFFONDATO || = MANCATO
 *           3) Righe, valore righe di colpo, intero, 1 <= righe< RIGHE
 *           4) Colonne, valore colonne di colpo, intero, 1 <= colonne< COLONNE
 *           5) COLPITO, id nave colpita, carattere, variabile globale
 *           6) AFFONDATO, id nave affondata, carattere, variabile globale
 *           7) RADAR_NAVE, id nave individuata con il radar, intero, variabile globale
 *           8) RADAR_VUOTO, id acqua individuata con il radar, intero, variabile globale
 *  Output : 0) --
 *  Descrizione: La funzione stampa l'esito del colpo lanciato dal giocatore
 */
void stampareEsitoColpo(coordinate colpo, int esito){
    int righe       = leggereCoordinateX(colpo)+1;
    char colonne    = convertiPosizioneInLettera(leggereCoordinateY(colpo));

    if(esito == COLPITO)            printf("COLPITO in %c%d\n", colonne,righe);
    else if(esito == AFFONDATO)     printf("COLPITO E AFFONDATO IN %c%d\n",colonne,righe);
    else if(esito == RADAR_NAVE)    printf("NAVE in %c%d\n", colonne,righe);
    else if(esito == RADAR_VUOTO)   printf("VUOTO in %c%d\n", colonne,righe);
    else                            printf("ACQUA in %c%d\n", colonne,righe);
}
/*
 *  Funzione: stampareInizioTurno()
 *  Input  : 1) Giocatore, dati del giocatore, player
 *           2) turniTotali, turni totali della partita, intero, > 0
 *           3) nomePlayer, nome del player da stampare, vettore di caratteri, dim = MAX_DIM_STRINGA_NOME
 *           4) naviAffondate, numero di navi affondate dal giocatore, intero, 0 <= naviAffondate <= TOTALE_NAVI
 *  Output : 0) --
 *  Descrizione: La funzione stampa la schermata iniziale del turno
 */
void stampareInizioTurno(player giocatore, int turniTotali){
    char nomePlayer[MAX_DIM_STRINGA_NOME];
    int  naviAffondate;

    strcpy(nomePlayer, leggereNomePlayer(&giocatore));
    naviAffondate = leggereNaviAffondate(giocatore);

    system("cls");
    printf("Turno    : %d\n", turniTotali);
    printf("Giocatore: %s\n", nomePlayer);
    printf("Navi affondate: %d\n\n", naviAffondate);
    stampareMappe(giocatore);
}
/*
 *  Funzione: confermaInizioTurno()
 *  Input  : 1) Giocatore, dati del giocatore, player
 *           2) nomePlayer, nome del player da stampare, stringa, dim = MAX_DIM_STRINGA_NOME
 *           3) inizioTurno, risposta dall'utente, intero, 0 <= inizioTurno <= 1
 *           4) SRC_INIZIO_TURNO, percorso del file inizioTurno da stampare, vettore di caratteri, variabile globale
 *  Output : 1) inizioTurno, risposta dall'utente, intero, 0 <= inizioTurno <= 1
 *  Descrizione: La funzione approva l'inizio del turno giocatore
 */
int confermareInizioTurno(player giocatore) {
    char nomePlayer[MAX_DIM_STRINGA_NOME];
    int  inizioTurno;

    strcpy(nomePlayer, leggereNomePlayer(&giocatore));

    system("cls");
    printf("Giocatore: %s\n", nomePlayer);
    stampareFile(SRC_INIZIO_TURNO);
    inizioTurno = leggereRispostaValida(0,1);
    system("cls");
    return inizioTurno;
}
/*
 *  Funzione: confermaFineTurno()
 *  Input  : 1) Giocatore, dati del giocatore, player
 *           2) fineTurno, risposta dell'utente, intero, 0 <= fineTurno <= 2
 *           3) SRC_FINE_TURNO, percorso del file inizioTurno da stampare, vettore di caratteri, variabile globale
 *  Output : 1) fineTurno, risposta dell'utente, intero, 0 <= fineTurno <= 2
 *  Descrizione: La funzione approva la fine del turno giocatore
 */
int confermareFineTurno(player giocatore){
    int fineTurno;
    stampareFile(SRC_FINE_TURNO);
    fineTurno = leggereRispostaValida(0,2);
    system("cls");
    return fineTurno;
}
