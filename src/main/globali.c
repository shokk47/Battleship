#include "globali.h"
#include "verifiche.h"
#include "stampe.h"

/*
 *  Funzione: leggereRispostaValida()
 *  Input  : 1) min, valore minimo ammesso come risposta valida, intero
 *           2) max, valore massimo ammesso come risposta valida, intero
 *           3) ANC, id errore “risposta non corretta”, intero, variabile globale
 *  Output : 1) Risposta, dato letto da tastiera che rappresenta la scelta dell’utente, intero,	min <= risposta <= max
 *  Descrizione: La funzione stabilisce la direzione della nave
 */
int leggereRispostaValida(int min, int max){
    int risposta;
    do{
        scanf("%d", &risposta);
        fflush(stdin);                                              // Pulisce il buffer della scanf
        if(risposta<min || risposta>max) stampareErrore(ANC);       // risposta non corretta
    }while(risposta<min || risposta>max);
    return risposta;
}
/*
 *  Funzione: ottenereCoordinate()
 *  Input  : 1) Posizione, struttura usata per contenere i dati del colpo da lanciare, coordinate
 *           2) stringaCoordinate, valore delle coordinate che il giocatore sceglie, lette da tastiera, vettore di caratteri, dim = MAX_DIM_STRINGA_POS
 *           3) isValid, esito della verifica della correttezza di stringaCoordinate, intero, 0 <= isValid <= 1
 *           4) MAX_DIM_STRINGA_POS, dimensione massima della stringa posizione, intero, Variabile globale
 *           5) SOM, id errore “colpo fuori mappa”, intero, variabile globale
 *  Output : 1) Posizione, struttura che contiene le coordinate del colpo in una posizione valida che si vuole lanciare, coordinate
 *  Descrizione: La funzione chiede all'utente d'inserire le coordinate nel formato An
 *               e restituisce il valore intero convertito
 */
void ottenereCoordinate(coordinate *posizione){
    char stringaCoordinate[MAX_DIM_STRINGA_POS] = "";
    int isValid;
    do{
        printf("Inserisci coordinate nel formato An [es: C5]: ");
        scanf("%s", stringaCoordinate);
        printf("\n");
        fflush(stdin);

        verificareCoordinate(stringaCoordinate, posizione);
        isValid = leggereCoordinateIsValid(*posizione);
        if (!isValid) {
            stampareErrore(SOM);  // COLPO FUORI MAPPA
        }
    }while(!isValid);
}
/*
 *  Funzione: convertiPosizioneInLettera()
 *  Input  : 1) num, valore intero da convertire in lettera, intero, 0 <= num <= 15
 *  Output : 1) Lettera, valore convertito in carattere, carattere,	A <= lettera <= P
 *  Descrizione: La funzione riceve un intero e lo converte in un carattere
 */
char convertiPosizioneInLettera(int num){
    char lettera;
    lettera = (num+64)+1;   // perchè la mappa parte da 1, invece i vettori posizione da 0
    return lettera;
}

