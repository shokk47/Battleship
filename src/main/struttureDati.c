#include "struttureDati.h"
#include "globali.h"

/*
 *  Funzione: ottieniDatiNavi()
 *  Input  : 1) Navi, array in cui scrivere i dati delle varie navi, vettore di nave, dimensione = NUMERO_NAVI
 *           2) ID_PORTAEREI, id della nave portaerei, carattere, variabile globale
 *           3) ID_CORAZZATA, id della nave corazzata, carattere, variabile globale
 *           4) ID_INCROCIATORE, id della nave incrociatore, carattere, variabile globale
 *           5) ID_CACCIATORPEDINIERE, id della nave cacciatorpediniere, carattere, variabile globale
 *           6) ID_NAVE_SUPPORTO, id della nave supporto, carattere, variabile globale
 *           7) ID_NAVESUPPORTO, id della nave naveSupporto, carattere, variabile globale
 *           8) LEN_PORTAEREI, contiene la lunghezza della nave portaerei, intero, variabile globale
 *           9) LEN_CORAZZATA, contiene la lunghezza della nave corazzata, intero, variabile globale
 *           10) LEN_INCROCIATORE, contiene la lunghezza della nave incrociatore, intero, variabile globale
 *           11) LEN_CACCIATORPEDINIERE, contiene la lunghezza della nave cacciatorpediniere, intero, variabile globale
 *           12) LEN_NAVESUPPORTO, contiene la lunghezza della nave naveSupporto, intero, variabile globale
 *           13) NUM_PORTAEREI, numero massimo di navi portaerei, intero, variabile globale
 *           14) NUM_CORAZZATA, numero massimo di navi corazzata, intero, variabile globale
 *           15) NUM_INCROCIATORE, numero massimo di navi incrociatore, intero, variabile globale
 *           16) NUM_CACCIATORPEDINIERE, numero massimo di navi cacciatorpediniere, intero, variabile globale
 *           17) NUM_NAVESUPPORTO, numero massimo di navi supporto, intero, variabile globale
 *  Output : 1) Navi, array che contiene i dati di tutte le navi modificato, vettore di nave, dimensione = NUMERO_NAVI
 *  Descrizione: La funzione restituisce i dati delle navi
 */
void ottieniDatiNavi(nave navi[NUMERO_NAVI]){
    scrivereIdNave(&navi[0], ID_PORTAEREI);
    scrivereIdNave(&navi[1], ID_CORAZZATA);
    scrivereIdNave(&navi[2], ID_INCROCIATORE);
    scrivereIdNave(&navi[3], ID_CACCIATORPEDINIERE);
    scrivereIdNave(&navi[4], ID_NAVESUPPORTO);

    scrivereLunghezzaNave(&navi[0], LEN_PORTAEREI);
    scrivereLunghezzaNave(&navi[1], LEN_CORAZZATA);
    scrivereLunghezzaNave(&navi[2], LEN_INCROCIATORE);
    scrivereLunghezzaNave(&navi[3], LEN_CACCIATORPEDINIERE);
    scrivereLunghezzaNave(&navi[4], LEN_NAVESUPPORTO);

    scrivereNumeroNave(&navi[0], NUM_PORTAEREI);
    scrivereNumeroNave(&navi[1], NUM_CORAZZATA);
    scrivereNumeroNave(&navi[2], NUM_INCROCIATORE);
    scrivereNumeroNave(&navi[3], NUM_CACCIATORPEDINIERE);
    scrivereNumeroNave(&navi[4], NUM_NAVESUPPORTO);
}

/*
 *      FUNZIONI DI ACCESSO STRUCT : PLAYER
 */

/*
 *  Funzione: scrivereMappaNavi()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Posizione, struttura dati che contiene le coordinate del valore da scrivere in mappaNavi di giocatore, coordinate
 *           3) Valore, carattere da scrivere in mappaNavi, carattere, tutti i caratteri ammessi in mappa navi definiti come variabili globali
 *           4) Righe, contiene il numero della riga di mappaNavi in cui scrivere valore, intero, 0 <= righe < RIGHE
 *           5) Colonne, contiene il numero della colonna di mappaNavi in cui scrivere valore, intero, 0 <= colonne < COLONNE
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione scrive un carattere in coordinate posizione di mappaNavi
 */
void scrivereMappaNavi(player *giocatore, coordinate posizione, char valore){
    int righe;
    int colonne;
    righe   = leggereCoordinateX(posizione);
    colonne = leggereCoordinateY(posizione);
    giocatore->mappaNavi[righe][colonne] = valore;
}
/*
 *  Funzione: scrivereMappaColpi()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore, player
 *           2) Posizione, struttura dati che contiene le coordinate del valore da scrivere in mappaColpi di giocatore, coordinate
 *           3) Valore, valore da scrivere in mappaColpi, carattere, tutti i caratteri ammessi in mappaColpi definiti come variabili globali
 *           4) Righe, contiene il numero della riga di mappaColpi in cui scrivere valore, intero, 0 <= righe < RIGHE
 *           5) Colonne, contiene il numero della colonna di mappaColpi in cui scrivere valore, intero,	0 <= colonne < COLONNE
 *  Output : 1) giocatore, struttura dati con i dati del giocatore, player
 *  Descrizione: La funzione scrive un carattere in coordinate posizione di mappaColpi
 */
void scrivereMappaColpi(player *giocatore, coordinate posizione, char valore) {
    int righe;
    int colonne;
    righe   = leggereCoordinateX(posizione);
    colonne = leggereCoordinateY(posizione);
    giocatore->mappaColpi[righe][colonne] = valore;
}
/*
 *  Funzione: scrivereNaviAffondate()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Valore, valore di navi affondate da scrivere, intero, >= 0
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione scrive valore nel campo naviAffondate di giocatore
 */
void scrivereNaviAffondate(player *giocatore, int valore){
    giocatore->naviAffondate = valore;
}
/*
 *  Funzione: incrementareNaviAffondate()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Valore, valore naviAffondate da incrementare, intero, 0 <= valore <= TOTALE_NAVI
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione incrementa il numero di navi affondate del giocatore
 */
void incrementareNaviAffondate(player *giocatore){
    int valore;
    valore = leggereNaviAffondate(*giocatore);
    valore = valore + 1;
    scrivereNaviAffondate(giocatore, valore);
}
/*
 *  Funzione: leggereMappaNavi()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Posizione, struttura dati con le coordinate di mappaNavi da leggere, coordinate
 *           3) Righe, contiene il numero della riga di mappaNavi in cui è presente il valore da leggere, intero, 0 <= righe < RIGHE
 *           4) Colonne, contiene il numero della colonna di mappaNavi in cui è presente il valore da leggere, intero, 0 <= colonne < COLONNE
 *  Output : 1) Valore, valore letto in coordinate posizione di mappaNavi, carattere, tutti i caratteri ammessi in mappa navi definiti come variabili globali
 *  Descrizione: La funzione restituisce il valore presente in coordinate posizione di mappaNavi
 */
char leggereMappaNavi(player giocatore, coordinate posizione){
    int righe;
    int colonne;
    righe   = leggereCoordinateX(posizione);
    colonne = leggereCoordinateY(posizione);
    char valore = giocatore.mappaNavi[righe][colonne];
    return valore;
}
/*
 *  Funzione: leggereMappaColpi()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore, player
 *           2) Posizione, struttura dati con le coordinate mappaColpi da leggere, coordinate
 *           3) Righe, contiene il numero della riga di mappaColpi in cui è presente il valore da leggere, intero, 0 <= righe < RIGHE
 *           4) Colonne, contiene il numero della colonna di mappaColpi in cui è presente il valore da leggere, intero,	0 <= colonne < COLONNE
 *  Output : 1) Valore, valore letto in coordinate posizione di mappaColpi, carattere, tutti i caratteri ammessi in mappa colpi definiti come variabili globali
 *  Descrizione: La funzione restituisce il valore presente in coordinate posizione di mappaColpi
 */
char leggereMappaColpi(player giocatore, coordinate posizione){
    int righe;
    int colonne;
    righe   = leggereCoordinateX(posizione);
    colonne = leggereCoordinateY(posizione);
    char valore = giocatore.mappaColpi[righe][colonne];
    return valore;
}
/*
 *  Funzione: leggereNomePlayer()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) ptrNome, contiene il nome del giocatore corrente da leggere, vettore di caratteri, dimensione = MAX_DIM_STRINGA_NOME
 *  Output : 1) ptrNome, nome del giocatore letto, vettore di caratteri, dimensione = MAX_DIM_STRINGA_NOME
 *  Descrizione: La funzione restituisce il campo nomePlayer di giocatore
 */
char* leggereNomePlayer(player *giocatore){
    char* ptrNome;
    ptrNome =  giocatore->nomePlayer;
    return ptrNome;
}
/*
 *  Funzione: leggereNaviAffondate()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) naviAffondate, contiene il numero di navi affondate del giocatore corrente, intero,	0 <= naviAffondate <= TOTALE_NAVI
 *  Output : 1) naviAffondate, numero di navi affondate del giocatore corrente letto, intero, 0 <= naviAffondate <= TOTALE_NAVI
 *  Descrizione: La funzione restituisce il numero di navi affondate di giocatore
 */
int leggereNaviAffondate(player giocatore) {
    int naviAffondate = giocatore.naviAffondate;
    return naviAffondate;
}

/*
 *      FUNZIONI DI ACCESSO STRUCT : COLPISPECIALI
 */

/*
 *  Funzione: scrivereColpiSpeciali()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Struttura, struttura che contiene i dati da scrivere nel campo colpiSS di giocatore, colpiSpeciali
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione scrive struttura nel campo colpiSS di giocatore
 */
void scrivereColpiSpeciali(player *giocatore, colpiSpeciali struttura){
    giocatore->colpiSS = struttura;
}
/*
 *  Funzione: scrivereBombardamentoAereo()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Valore, contiene il valore da scrivere nel campo bombardamentoAereo di colpiSS di giocatore, intero, 0 <= valore <= MAX_BOMBARDAMENTO
 *           3) Copia, struttura dati che contiene la copia del campo colpiSpeciali di giocatore, colpiSpeciali
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione scrive valore nel campo bombardamentoAereo di giocatore
 */
void scrivereBombardamentoAereo(player *giocatore, int valore){
    colpiSpeciali copia;
    copia = leggereColpiSpeciali(*giocatore);
    copia.bombardamentoAereo = valore;
    scrivereColpiSpeciali(giocatore, copia);
}
/*
 *  Funzione: scrivereRadar()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Valore, contiene il valore da scrivere nel campo radar di colpiSS di giocatore, intero,	0 <= valore <= MAX_RADAR
 *           3) Copia, struttura dati che conterrà il campo colpiSpeciali di giocatore, colpiSpeciali
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione scrive valore nel campo radar di giocatore
 */
void scrivereRadar(player *giocatore, int valore){
    colpiSpeciali copia;
    copia = leggereColpiSpeciali(*giocatore);
    copia.radar = valore;
    scrivereColpiSpeciali(giocatore, copia);
}
/*
 *  Funzione: scrivereLargoRaggio()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Valore, contiene il valore da scrivere nel campo largoRaggio di colpiSS di giocatore, intero, 0 <= valore <= MAX_LARGO_RAGGIO
 *           3) Copia, struttura dati che conterrà il campo colpiSpeciali di giocatore,	colpiSpeciali
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione scrive valore nel campo largoRaggio di giocatore
 */
void scrivereLargoRaggio(player *giocatore, int valore){
    colpiSpeciali copia;
    copia = leggereColpiSpeciali(*giocatore);
    copia.largoRaggio = valore;
    scrivereColpiSpeciali(giocatore, copia);
}
/*
 *  Funzione: incrementareBombardamentoAereo()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Valore, contiene il valore del campo bombardamentoAereo di colpiSS di giocatore da incrementare, intero, 0 <= valore <= MAX_BOMBARDAMENTO
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione incrementa il valore del campo bombardamentoAereo di giocatore
 */
void incrementareBombardamentoAereo(player *giocatore){
    int valore;
    valore = leggereBombardamentoAereo(*giocatore);
    valore = valore + 1;
    scrivereBombardamentoAereo(giocatore, valore);
}
/*
 *  Funzione: incrementareRadar()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Valore, contiene il valore del campo radar di colpiSS di giocatore da incrementare, intero,	0 <= valore <= MAX_RADAR
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione incrementa il valore del campo radar di giocatore
 */
void incrementareRadar(player *giocatore){
    int valore;
    valore = leggereRadar(*giocatore);
    valore = valore + 1;
    scrivereRadar(giocatore, valore);
}
/*
 *  Funzione: incrementareLargoRaggio()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *           2) Valore, contiene il valore del campo radar di colpiSS di giocatore da incrementare, intero,	0 <= valore <= MAX_RADAR
 *  Output : 1) Giocatore, struttura dati con i dati del giocatore modificati, player
 *  Descrizione: La funzione incrementa il valore del campo largoRaggio di giocatore
 */
void incrementareLargoRaggio(player *giocatore){
    int valore;
    valore = leggereLargoRaggio(*giocatore);
    valore = valore + 1;
    scrivereLargoRaggio(giocatore, valore);
}
/*
 *  Funzione: leggereBombardamentoAereo()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *  Output : 1) Valore, valore del campo bombardamentoAereo di colpiSS  di giocatore, intero, 0 <= valore <= MAX_BOMBARDAMENTO
 *  Descrizione: La funzione restituisce il valore del campo bombardamentoAereo di giocatore
 */
int leggereBombardamentoAereo(player giocatore){
    int valore;
    valore = giocatore.colpiSS.bombardamentoAereo;
    return valore;
}
/*
 *  Funzione: leggereRadar()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *  Output : 1) Valore, valore del campo radar di colpiSS  di giocatore, intero, 0 <= valore <= MAX_RADAR
 *  Descrizione: La funzione restituisce il valore del campo radar di giocatore
 */
int leggereRadar(player giocatore){
    int valore;
    valore = giocatore.colpiSS.radar;
    return valore;
}
/*
 *  Funzione: leggereLargoRaggio()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore corrente, player
 *  Output : 1) Valore, valore del campo largoRaggio di ColpiSS di giocatore, intero, 0 <= valore <= MAX_LARGO_RAGGIO
 *  Descrizione: La funzione restituisce il valore del campo largoRaggio di giocatore
 */
int leggereLargoRaggio(player giocatore){
    int valore;
    valore = giocatore.colpiSS.largoRaggio;
    return valore;
}
/*
 *  Funzione: leggereColpiSpeciali()
 *  Input  : 1) Giocatore, struttura dati che contiene i dati del giocatore, player
 *  Output : 1) Valore, campo ColpiSS di giocatore letto, colpiSpeciali
 *  Descrizione: La funzione restituisce il campo colpiSS di giocatore
 */
colpiSpeciali leggereColpiSpeciali(player giocatore){
    colpiSpeciali valore;
    valore = giocatore.colpiSS;
    return valore;
}

/*
 *      FUNZIONI DI ACCESSO STRUCT : NAVE
 */

/*
 *  Funzione: scrivereIdNave()
 *  Input  : 1) Navi, struttura che contiene i dati della nave presa in considerazione, nave
 *           2) ID, Contiene il valore da scrivere nel campo id di navi, carattere, A <= ID <= E
 *  Output : 1) Navi, struttura che contiene i dati della nave modificati, nave
 *  Descrizione: La funzione scrive ID nel campo id di navi
 */
void scrivereIdNave(nave *navi, char ID){
    navi->id = ID;
}
/*
 *  Funzione: scrivereLunghezzaNave()
 *  Input  : 1) Navi, struttura che contiene i dati della nave presa in considerazione, nave
 *           2) Lunghezza, contiene il valore da scrivere nel campo lunghezza di navi, intero,	1 <= lunghezza <= LEN_PORTAEREI
 *  Output : 1) Navi, struttura che contiene i dati della nave modificati, nave
 *  Descrizione: La funzione scrive lunghezza nel campo lunghezza di navi
 */
void scrivereLunghezzaNave(nave *navi, int lunghezza){
    navi->lunghezza = lunghezza;
}
/*
 *  Funzione: scrivereNumeroNave()
 *  Input  : 1) Navi, struttura che contiene i dati della nave presa in considerazione, nave
 *           2) Numero, contiene il valore da scrivere nel campo numero di navi, intero, 1 <= numero <= NUM_NAVESUPPORTO
 *  Output : 1) Navi, struttura che contiene i dati della nave modificati, nave
 *  Descrizione: La funzione scrive numero nel campo numero di navi
 */
void scrivereNumeroNave(nave *navi, int numero){
    navi->numero = numero;
}
/*
 *  Funzione: leggereIdNave()
 *  Input  : 1) Navi, struttura che contiene i dati della nave presa in considerazione, nave
 *  Output : 1) Id, valore del campo id di navi letto, carattere, A <= id <= E
 *  Descrizione: La funzione restituisce il valore del campo id di navi
 */
char leggereIdNave(nave navi){
    char id;
    id = navi.id;
    return id;
}
/*
 *  Funzione: leggereLunghezzaNave()
 *  Input  : 1) Navi, struttura che contiene i dati della nave presa in considerazione, nave
 *  Output : 1) Lunghezza, valore del campo lunghezza di navi letto, intero, 1 <= lunghezza <= LEN_PORTAEREI
 *  Descrizione: La funzione restituisce il valore del campo lunghezza di navi
 */
int leggereLunghezzaNave(nave navi){
    int lunghezza;
    lunghezza = navi.lunghezza;
    return lunghezza;
}
/*
 *  Funzione: leggereNumeroNave()
 *  Input  : 1) Navi, struttura che contiene i dati della nave presa in considerazione, nave
 *  Output : 1) Numero, valore del campo numero di navi letto, intero, 1 <= lunghezza <= NUM_NAVESUPPORTO
 *  Descrizione: La funzione restituisce il valore del campo numero di navi
 */
int leggereNumeroNave(nave navi){
    int numero;
    numero = navi.numero;
    return numero;
}

/*
 *      FUNZIONI DI ACCESSO STRUCT : COORDINATE
 */

/*
 *  Funzione: scrivereCoordinateX()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da modificare, coordinate
 *           2) x, valore da scrivere nel campo x di posizione, intero, 0 <= x < RIGHE
 *  Output : 1) Posizione, struttura dati che contiene le coordinate con il campo x modificato, coordinate
 *  Descrizione: La funzione scrive x nel campo x di posizione
 */
void scrivereCoordinateX(coordinate *posizione, int x){
    posizione->x = x;
}
/*
 *  Funzione: scrivereCoordinateY()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da modificare, coordinate
 *           2) y, valore da scrivere nel campo y di posizione, intero,	0 <= y < COLONNE
 *  Output : 1) Posizione, struttura dati che contiene le coordinate con il campo y modificato, coordinate
 *  Descrizione: La funzione scrive y nel campo y di posizione
 */
void scrivereCoordinateY(coordinate *posizione, int y){
    posizione->y = y;
}
/*
 *  Funzione: scrivereCoordinateIsValid()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da modificare, coordinate
 *           2) isValid, valore da scrivere nel campo isValid di posizione, intero, 0 <= isValid <= 1
 *  Output : 1) Posizione, struttura dati che contiene le coordinate con il campo isValid modificato, coordinate
 *  Descrizione: La funzione scrive isValid nel campo isValid di posizione
 */
void scrivereCoordinateIsValid(coordinate *posizione, int isValid){
    posizione->isValid = isValid;
}
/*
 *  Funzione: incrementareCoordinateX()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da modificare, coordinate
 *           2) Valore, variabile che contiene il valore di campo x di posizione da incrementare, intero, 0 <= valore < RIGHE
 *  Output : 1) Posizione, struttura dati coordinate con il campo x modificato, coordinate
 *  Descrizione: La funzione incrementa il valore del campo x di posizione
 */
void incrementareCoordinateX(coordinate *posizione){
    int valore;
    valore = leggereCoordinateX(*posizione);
    valore = valore + 1;
    scrivereCoordinateX(posizione, valore);
}
/*
 *  Funzione: incrementareCoordinateY()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da modificare, coordinate
 *           2) Valore, variabile che contiene il valore del campo y di posizione da incrementare, intero,	0 <= valore < COLONNE
 *  Output : 1) Posizione, struttura dati che contiene le coordinate con il campo y modificato, coordinate
 *  Descrizione: La funzione incrementa il valore del campo y di posizione
 */
void incrementareCoordinateY(coordinate *posizione){
    int valore;
    valore = leggereCoordinateY(*posizione);
    valore = valore + 1;
    scrivereCoordinateY(posizione, valore);
}
/*
 *  Funzione: decrementareCoordinateX()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da modificare, coordinate
 *           2) Valore, variabile che contiene il valore di campo x di posizione da decrementare, intero, 0 <= valore < RIGHE
 *  Output : 1) Posizione, struttura dati coordinate con il campo x modificato, coordinate
 *  Descrizione: La funzione decrementa il valore del campo x di posizione
 */
void decrementareCoordinateX(coordinate *posizione){
    int valore;
    valore = leggereCoordinateX(*posizione);
    valore = valore - 1;
    scrivereCoordinateX(posizione, valore);
}
/*
 *  Funzione: decrementareCoordinateY()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da modificare, coordinate
 *           2) Valore, variabile che contiene il valore di campo y di posizione da decrementare, intero, 0 <= valore < COLONNE
 *  Output : 1) Posizione, struttura dati coordinate con il campo y modificato, coordinate
 *  Descrizione: La funzione decrementa il valore del campo y di posizione
 */
void decrementareCoordinateY(coordinate *posizione){
    int valore;
    valore = leggereCoordinateY(*posizione);
    valore = valore - 1;
    scrivereCoordinateY(posizione, valore);
}
/*
 *  Funzione: leggereCoordinateX()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da leggere, coordinate
  *  Output : 1) x, valore del camo x di posizione letto, intero, 0 <= x < RIGHE
 *  Descrizione: La funzione restituisce il valore del campo x di posizione
 */
int leggereCoordinateX(coordinate posizione){
    int x;
    x = posizione.x;
    return x;
}
/*
 *  Funzione: leggereCoordinateY()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da leggere, coordinate
 *  Output : 1) y, valore del campo y di posizione letto, intero, 0 <= y < COLONNE
 *  Descrizione: La funzione restituisce il valore del campo y di posizione
 */
int leggereCoordinateY(coordinate posizione){
    int y;
    y = posizione.y;
    return y;
}
/*
 *  Funzione: leggereCoordinateIsValid()
 *  Input  : 1) Posizione, struttura dati che contiene le coordinate da leggere, coordinate
 *  Output : 1) isValid, valore del campo isValid di posizione letto, intero, 0 <= isValid <= 1
 *  Descrizione: La funzione restituisce il valore del campo isValid di posizione
 */
int leggereCoordinateIsValid(coordinate posizione){
    int isValid;
    isValid = posizione.isValid;
    return isValid;
}

/*
 *      FUNZIONI DI ACCESSO STRUCT : DATIPARTITA
 */

/*
 *  Funzione: scrivereDatiGiocatore1()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da modificare, datiPartita
 *           2) datiGiocatore_1, struttura dati che contiene i dati da scrivere nel campo datiGiocatore_1 di struttura, player
 *  Output : 1) Struttura, struttura dati che contiene i dati della partita modificati,	datiPartita
 *  Descrizione: La funzione scrive datiGiocatore_1 nel campo datiGiocatore_1 di struttura
 */
void scrivereDatiGiocatore1 (datiPartita *struttura, player datiGiocatore_1){
    struttura->datiGiocatore_1 = datiGiocatore_1;
}
/*
 *  Funzione: scrivereDatiGiocatore2()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita, datiPartita
 *           2) datiGiocatore_2, struttura dati che contiene i dati da scrivere nel campo datiGiocatore_2 di struttura, player
 *  Output : 1) Struttura, struttura dati che contiene i dati della partita modificati,	datiPartita
 *  Descrizione: La funzione scrive datiGiocatore_2 nel campo datiGiocatore_1 di struttura
 */
void scrivereDatiGiocatore2 (datiPartita *struttura, player datiGiocatore_2){
    struttura->datiGiocatore_2 = datiGiocatore_2;
}
/*
 *  Funzione: scrivereTurnoPartita()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da modificare, datiPartita
 *           2) turnoPartita, elemento da scrivere nel campo turnoPartita di struttura, intero,	PLAYER_UNO <= turnoPartita <= PLAYER_DUE
 *  Output : 1) Struttura, struttura dati che contiene i dati della partita modificati,	datiPartita
 *  Descrizione: La funzione scrive turnoPartita nel campo turnoPartita di struttura
 */
void scrivereTurnoPartita (datiPartita *struttura, int turnoPartita){
    struttura->turnoPartita = turnoPartita;
}
/*
 *  Funzione: scrivereTurniTotali()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da modificare, datiPartita
 *           2) turniTotali, elemento da scrivere nel campo turniTotali di struttura, intero, >0
 *  Output : 1) Struttura, struttura dati che contiene i dati della partita modificati,	datiPartita
 *  Descrizione: La funzione scrive turniTotali nel campo turniTotali di struttura
 */
void scrivereTurniTotali (datiPartita *struttura, int turniTotali){
    struttura->turniTotali = turniTotali;
}
/*
 *  Funzione: scrivereEsitoColpi()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da modificare, datiPartita
 *           2) Esito, elemento da scrivere nel campo esitoColpo di struttura, intero, =ESITO_COLPO_OK || =ESITO_COLPO_ERR
 *  Output : 1) Struttura, struttura dati che contiene i dati della partita modificati,	datiPartita
 *  Descrizione: La funzione scrive esito nel campo esitoColpo di struttura
 */
void scrivereEsitoColpi(datiPartita *struttura, int esito) {
    struttura->esitoColpo = esito;
}
/*
 *  Funzione: scrivereEndGame()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da modificare, datiPartita
 *           2) endGame, elemento da scrivere nel campo endGame di struttura, intero, =BACK || =ESCI || =SALVARE
 *  Output : 1) Struttura, struttura dati che contiene i dati della partita modificati, datiPartita
 *  Descrizione: La funzione scrive endGame nel campo endGame di struttura
 */
void scrivereEndGame(datiPartita *struttura, int endGame){
    struttura->endGame = endGame;
}
/*
 *  Funzione: leggereDatiGiocatore1()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da leggere,	datiPartita
 *  Output : 1) Giocatore, valore del campo datiGiocatore_1 di struttura letto, player
 *  Descrizione: La funzione restituisce il campo datiGiocatore_1 di struttura
 */
player leggereDatiGiocatore1(datiPartita struttura){
    player giocatore;
    giocatore = struttura.datiGiocatore_1;
    return giocatore;
}
/*
 *  Funzione: leggereDatiGiocatore2()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da leggere,	datiPartita
 *  Output : 1) Giocatore, valore del campo datiGiocatore_2 di struttura letto, player
 *  Descrizione: La funzione restituisce il campo datiGiocatore_2 di struttura
 */
player leggereDatiGiocatore2 (datiPartita struttura){
    player giocatore;
    giocatore = struttura.datiGiocatore_2;
    return giocatore;
}
/*
 *  Funzione: leggereTurnoPartita()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da leggere, datiPartita
 *  Output : 1) Turno, valore del campo turnoPartita di struttura letto, intero, PLAYER_UNO <= turno <= PLAYER_DUE
 *  Descrizione: La funzione restituisce il campo turnoPartita di di struttura
 */
int leggereTurnoPartita (datiPartita struttura){
    int turno;
    turno = struttura.turnoPartita;
    return turno;
}
/*
 *  Funzione: leggereTurniTotali()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita, datiPartita
 *  Output : 1) turniTotali, valore del campo turnoPartita di struttura letto, intero, > 0
 *  Descrizione: La funzione restituisce il valore del campo turniTotali di struttura
 */
int leggereTurniTotali (datiPartita struttura){
    int turniTotali;
    turniTotali = struttura.turniTotali;
    return turniTotali;
}
/*
 *  Funzione: leggereEsitoColpi()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da leggere, datiPartita
 *  Output : 1) Esito, valore del campo esitoColpo di struttura letto, intero,	= ESITO_COLPO_OK  =ESITO_COLPO_ERR
 *  Descrizione: La funzione restituisce il valore del campo esitoColpo di struttura
 */
int leggereEsitoColpi(datiPartita struttura){
    int esito;
    esito = struttura.esitoColpo;
    return esito;
}
/*
 *  Funzione: leggereEndGame()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da leggere, datiPartita
 *  Output : 1) endGame, valore del campo endGame di struttura letto, intero, =BACK || =ESCI || =SALVARE
 *  Descrizione: La funzione restituisce il valore del campo endGame di struttura
 */
int leggereEndGame(datiPartita struttura){
    int endGame;
    endGame = struttura.endGame;
    return endGame;
}
/*
 *  Funzione: incrementareTurniTotali()
 *  Input  : 1) Struttura, struttura dati che contiene i dati della partita da modificare, datiPartita
 *           2) Valore, variabile che contiene il valore di turniTotali da incrementare, intero, > 0
 *  Output : 1) Struttura, struttura dati che contiene i dati della partita modificati,	datiPartita
 *  Descrizione: La funzione incrementa il valore di turniTotali di struttura
 */
void incrementareTurniTotali(datiPartita *struttura) {
    int valore;
    valore = leggereTurniTotali(*struttura);
    valore = valore + 1;
    scrivereTurniTotali(struttura, valore);
}