#include "gameLoop.h"
#include "stampe.h"
#include "globali.h"
#include "verifiche.h"
#include "inizializzazioni.h"

void lanciareColpo(datiPartita *struttura, coordinate colpo);
void lanciareColpoClassico(datiPartita *struttura);
void lanciareBombardamentoAereo(datiPartita *struttura);
void lanciareRadar(datiPartita *struttura);
void lanciareLargoRaggio(datiPartita *struttura);
void switchGiocatori(datiPartita *struttura);
void scrivereColpo(player *giocatore, coordinate posizione, int tipologia);
void aumentareCoordinate(coordinate *colpo, int direzione, int linea, int valore);
void calcolareScansione(coordinate colpo, coordinate posizioni[CELLE_LARGO_RAGGIO]);
int leggereTipoColpo(player giocatore, int turno);
int leggereLinea(int direzione);
int finePartita(datiPartita struttura);

/*
 *  Funzione: gameLoop()
 *  Input  : 1) struttura, Struttura che contiene i dati della partita, DatiParita
 *           2) endgame, Valore di controllo  che indica lo stato della partita, =CONTINUA, =ESCI, =SALVARE, =BACK
 *           2) turniTotali, Turni totali della partita, Intero, > 0
 *           3) tipoColpo, Valore che indica il tipo di colpo che l’utente vuole lanciare, Intero, 1 <= tipoColpo <= 4
 *           4) inizioTurno, Valore che l’utente sceglie di inserire quando si trova nel menu’ di inizio turno, Intero, 0 <= inizioTurno <= 1
 *           5) fineTurno, Valore che l’utente sceglie di inserire quando si trova nel menu’ di fine turno, Intero, 0 <= fineTurno <= 2
 *           6) BACK, Valore che identifica il ritorno al menu principale, Intero, Variabile globale
 *           7) ESCI, Valore che identifica l’uscita dal gioco, Intero, Variabile globale
 *           8) SALVARE, Valore che identifica il salvataggio della partita e l’uscita, Intero, Variabile globale
 *  Output : 1) struttura, Struttura che contiene i dati della partita con i campi modificati, datiParita
 *  Descrizione: La funzione gestisce il loop della partita, cioe':
 *               1) permette di salvare la partita o tornare al menu principale
 *               2) permette di lanciare colpi
 */
void gameLoop(datiPartita *struttura){
    int endGame     =0;
    int turniTotali;
    int tipoColpo;
    int inizioTurno;
    int fineTurno;

    do {
        turniTotali = leggereTurniTotali(*struttura);
        inizioTurno = confermareInizioTurno(leggereDatiGiocatore1(*struttura));

        if(inizioTurno == 0){                   // TORNARE AL MENU PRINCIPALE
            scrivereEndGame(struttura, BACK);
            endGame = 1;
        }else{                                  // CONTINUA PARTITA
            stampareInizioTurno(leggereDatiGiocatore1(*struttura), turniTotali);
            tipoColpo = leggereTipoColpo(leggereDatiGiocatore1(*struttura), turniTotali);

            if(tipoColpo == 1)      lanciareColpoClassico(struttura);
            else if(tipoColpo == 2) lanciareLargoRaggio(struttura);
            else if(tipoColpo == 3) lanciareRadar(struttura);
            else                    lanciareBombardamentoAereo(struttura);

            switchGiocatori(struttura);
            fineTurno = confermareFineTurno(leggereDatiGiocatore1(*struttura));
            if(fineTurno == 0) {         // TORNARE AL MENU PRINCIPALE
                scrivereEndGame(struttura, BACK);
                endGame = 1;
            }else if(fineTurno == 1){   // CONTINUA PARTITA
                endGame = finePartita(*struttura);
                if(endGame) scrivereEndGame(struttura, ESCI);
            }else{                      // SALVA ED ESCI
                scrivereEndGame(struttura, SALVARE);
                endGame = 1;
            }
        }
    }while(!endGame);
}
/*
 *  Funzione: lanciareColpo()
 *  Input  : 1) struttura, Struttura che contiene i dati della partita, datiPartita
 *           2) colpo, Coordinate del colpo da lanciare, Coordinate
 *           3) giocatore, Struttura che contiene i dati del giocatore corrente, Player
 *           4) avversario, Struttura che contiene i dati del giocatore in attesa del turno, Player
 *           5) esitoPresenzaNave, Esito della verifica presenza nave, Intero, 0 <= esitoPresenzaNave <= 1
 *           6) esitoNaveAffondata, Esito della verifica Nave affondata, Intero, 0 <= esitoNaveAffondata <= 1
 *           7) esitoPresenza, Esito della verifica presenza elemento, Intero, 0 <= esitoPresenza <= 1
 *           8) ESITO_COLPO_OK, id esito colpo riuscito, Intero, Variabile globale
 *           9) ESITO_COLPO_ERR, id esito colpo non riuscito, Intero, Variabile globale
 *           10) SEGNA_COLPO, id scrivere colpo in mappa giocatore, Intero, Variabile globale
 *           11) SEGNA_NAVE, id scrivere colpo in mappa avversario, Intero, Variabile globale
 *           12) SEGNA_COLPO_MANCATO, id scrivere colpo mancato in mappa giocatore, Intero, Variabile globale
 *           13) AFFONDATO, id nave affondata, Intero, Variabile globale
 *           14) COLPITO, id nave colpita, Intero, Variabile globale
 *           15) ACQUA, id acqua in coordinate colpo, Intero, Variabile globale
 *           16) SAS, id errore "Colpo gia' lanciato", Intero, Variabile globale
 *  Output : 1) struttura, Struttura che contiene i dati della partita con i campi modificati, datiPartita
 *  Descrizione: La funzione lancia un colpo al giocatore 2 in coordinate colpo
 */
void lanciareColpo(datiPartita *struttura, coordinate colpo){
    player giocatore;
    player avversario;
    int esitoPresenzaNave;
    int esitoNaveAffondata;
    int esitoPresenza;

    giocatore = leggereDatiGiocatore1(*struttura);
    avversario = leggereDatiGiocatore2(*struttura);
    scrivereEsitoColpi(struttura, ESITO_COLPO_OK);

    esitoPresenzaNave = verificarePresenzaNave(avversario, colpo);
    if(esitoPresenzaNave){                                              // se Ã¨ presente una nave in pos:colpo di mappaNavi di supp2
        scrivereColpo(&giocatore, colpo, SEGNA_COLPO);                  // Aggiorna la sua mappa con nave colpita
        scrivereColpo(&avversario, colpo, SEGNA_NAVE);                  // Aggiorna la mappa del nemico con nave colpita
        esitoNaveAffondata = verificareNaveAffondata(avversario, colpo);
        if(esitoNaveAffondata){                                         // Verifica se la nave del nemico Ã¨ affondata
            incrementareNaviAffondate(&giocatore);                      // Allora incrementa contatore navi affondate del giocatore
            stampareEsitoColpo(colpo, AFFONDATO);
        }else stampareEsitoColpo(colpo, COLPITO);
    }else{
        esitoPresenza = verificarePresenza(avversario, colpo, ACQUA);
        if(esitoPresenza){
            scrivereColpo(&giocatore, colpo, SEGNA_COLPO_MANCATO);     // Aggiorna la mappa con acqua trovata
            scrivereColpo(&avversario, colpo, SEGNA_NAVE_MANCATO);     // Aggiorna la mappa del nemico con colpo lanciato in acqua
            stampareEsitoColpo(colpo, ACQUA);
        }else{
            stampareErrore(SAS);                                        // Colpo gia' lanciato
            scrivereEsitoColpi(struttura, ESITO_COLPO_ERR);
        }
    }
    scrivereDatiGiocatore1(struttura, giocatore);
    scrivereDatiGiocatore2(struttura, avversario);
}
/*
 *  Funzione: lanciareColpoClassico()
 *  Input  : 1) struttura, dati della partita, datiPartita
 *           2) colpo, Coordinate del colpo da lanciare, Coordinate
 *           3) esitoColpo, Esito del colpo lanciato, intero, =ESITO_COLPO_OK, =ESITO_COLPO_ERR
 *           4) ESITO_COLPO_OK, Id esito del colpo riuscito, Intero, Variabile globale
 *  Output : 1) struttura, Struttura che contiene i dati della partita con i campi modificati, datiPartita
 *  Descrizione: La funzione lancia un colpo classico al giocatore 2
 */
void lanciareColpoClassico(datiPartita *struttura) {
    coordinate colpo;
    int esitoColpo;
    do{
        ottenereCoordinate(&colpo);                                         // Chiede all'utente d'inserire le coordinate del colpo
        lanciareColpo(struttura, colpo);
        esitoColpo = leggereEsitoColpi(*struttura);
    }while(esitoColpo!=ESITO_COLPO_OK);                                     // Ripeti il ciclo fino a quando il giocatore non lancia un colpo valido
}
/*
 *  Funzione: lanciareBombardamentoAereo()
 *  Input  : 1) struttura, Struttura che contiene i dati della partita, datiPartita
 *           2) giocatore, Struttura che contiene i dati del giocatore corrente, player, =datiGiocatore1 di struttura
 *           2) colpo, Coordinate del colpo da lanciare, Coordinate
 *           3) linea, Orientamento bombardamento, Intero, 0 <= linea <= 15
 *           4) direzione, Direzione del colpo, Intero, VERTICALE <= direzione <= ORIZZONTALE
 *           5) esitoColpo, Esito del colpo lanciato, Intero, =ESITO_COLPO_OK, =ESITO_COLPO_ERR
 *           6) SRC_DIREZIONE, Percorso del file menu direzione, Vettore di caratteri, Variabile globale
 *           7) ESITO_COLPO_ERR, id colpo gia' lanciato in coordinate colpo, Intero, Variabile globale
 *           8) RIGHE, Numero di righe della mappaNavi, Intero, Variabile globale
 *           9) ECS, id dell'errore "tutte le coordinate sono state gia' colpite", Intero, Variabile globale
 *  Output : 1) struttura, Struttura che contiene i dati della partita con i campi modificati, datiPartita
 *  Descrizione: La funzione lancia un bombardamentoAereo al giocatore 2
 */
void lanciareBombardamentoAereo(datiPartita *struttura) {
    player giocatore;
    coordinate colpo;
    int errColpo        = 0;
    int colpiLanciati   = 0;
    int k;
    int linea;
    int direzione;
    int esitoColpo;
    do {
        stampareFile(SRC_DIREZIONE);
        direzione = leggereRispostaValida(1, 2);
        linea = leggereLinea(direzione);

        k = 0;                              // Azzera contatore per il ciclo

        do {
            aumentareCoordinate(&colpo, direzione, linea, k);
            lanciareColpo(struttura, colpo);
            colpiLanciati++;
            esitoColpo = leggereEsitoColpi(*struttura);
            if(esitoColpo==ESITO_COLPO_ERR) errColpo++;
            k++;
        } while (k < RIGHE);            // ripete RIGHE volte
        if(errColpo == colpiLanciati) stampareErrore(ECS);      // tutte le coordinate sono state giÃ  colpite, riprova
    }while(errColpo == colpiLanciati);
    giocatore = leggereDatiGiocatore1(*struttura);
    incrementareBombardamentoAereo(&giocatore);
    scrivereDatiGiocatore1(struttura, giocatore);
}
/*
 *  Funzione: lanciareRadar()
 *  Input  : 1) struttura, Struttura che contiene i dati della partita, datiPartita
 *           2) giocatore, Struttura che contiene i dati del giocatore corrente, Player
 *           3) avversario, Struttura che contiene i dati del giocatore in attesa del turno, Player
 *           4) posizioniScansionate, Vettore di posizioni calcolate per il radar, Vettore di coordinate, Dim CELLE_SCANSIONARE
 *           5) esitoVerificaScansione, Esito del controllo verificaScansione, Intero, 0 <= esitoVerificaScansione <= 1
 *           6) esitoPresenzaNave, Esito del controllo presenzaNave, Intero, 0 <= esitoPresenzaNave <= 1
 *           7) esitoPresenza, Esito del controllo presenza elemento, Intero, 0 <= esitoPresenza <= 1
 *           8) CELLE_RADAR, Valore che indica l’area o il numero di celle massimo che il radar può scansionare, Intero, Variabile globale
 *           9) SEGNA_RADAR_NAVE, Id scrivi nave trovata, Intero, Variabile globale
 *           10) SEGNA_RADAR_VUOTO, Id scrivi no nave trovata, Intero, Variabile globale
 *           10) RADAR_NAVE, Id esito del colpo radar, Carattere, Variabile globale
 *           11) RADAR_VUOTO, Id esito del colpo no nave, Carattere, Variabile globale
 *           12) ACQUA, Id acqua in MappaNavi, Carattere, Variabile globale
 *           13) EAL, Id errore "Tutte le coordinate sono state gia' scansionate", Intero, Variabile globale
 *  Output : 1) struttura, Struttura che contiene i dati della partita con i campi modificati, datiPartita
 *  Descrizione: La funzione lancia un colpo radar al giocatore 2
 */
void lanciareRadar(datiPartita *struttura){
    player giocatore  = leggereDatiGiocatore1(*struttura);
    player avversario = leggereDatiGiocatore2(*struttura);
    coordinate posizioniScansionate[CELLE_SCANSIONARE];
    coordinate colpo;
    int errColpo        = 0;
    int colpiLanciati   = 0;
    int k;
    int esitoVerificaScansione;
    int esitoPresenzaNave;
    int esitoPresenza;

    do {
        ottenereCoordinate(&colpo);
        inizializzarePosScansione(posizioniScansionate);                  // Azzera vettore di Posizioni con elementi neutri
        calcolareScansione(colpo,posizioniScansionate);                  // restituisce il vettore di posizioni da scansionare (raggio 1, tot 9 posizioni)

        k = 0;
        while (k < CELLE_RADAR) {
            esitoVerificaScansione = verificareScansione(posizioniScansionate[k]);
            if (esitoVerificaScansione) {
                colpiLanciati++;
                esitoPresenzaNave = verificarePresenzaNave(avversario,posizioniScansionate[k]);
                if (esitoPresenzaNave) {                        // Se colpo non corrisponde a una cella con stato "NO NAVE"
                    scrivereColpo(&giocatore, posizioniScansionate[k],SEGNA_RADAR_NAVE);               // Se la condizioni precedente Ã¨ vera, allora registra il colpo nella mappa Colpi di Giocatore_1
                    stampareEsitoColpo(posizioniScansionate[k], RADAR_NAVE);
                } else{
                    esitoPresenza = verificarePresenza(avversario, posizioniScansionate[k],ACQUA);
                    if (esitoPresenza) {                                                                                     // Se in xy Ã¨ presente acqua vuol dire che non Ã¨ presente nessuna nave quindi:
                        scrivereColpo(&giocatore, posizioniScansionate[k],SEGNA_RADAR_VUOTO);              // registra il colpo mancato nella mappa Colpi di giocatore_1
                        stampareEsitoColpo(posizioniScansionate[k], RADAR_VUOTO);
                    }else errColpo++;
                }
            }
            k++;                                                            // Aumenta il contatore del vettore posizioni
        }
        if(errColpo == colpiLanciati) stampareErrore(EAL);                  // Tutte le coordinate sono state gia' scansionate
    }while(errColpo == colpiLanciati);
    incrementareRadar(&giocatore);
    scrivereDatiGiocatore1(struttura, giocatore);
    scrivereDatiGiocatore2(struttura, avversario);
}
/*
 *  Funzione: lanciareLargoRaggio()
 *  Input  : 1) struttura, Struttura che contiene i dati della partita, datiPartita
 *           2) posizioniScansionate, vettore di posizioni calcolate per il largoRaggio, Vettore di coordinate, Dim CELLE_LARGO_RAGGIO
 *           3) colpo, Coordinate del singolo colpo da lanciare, Coordinate
 *           4) giocatore, struttura dati del giocatore che ha lanciato il colpo a largo raggio, Player
 *           5) esitoColpo, Esito del colpo lanciato, Intero, ESITO_COLPO_OK <= esitoColpi <= ESITO_COLPO_ERR
 *           6) esitoVerificaScansiome, Indica se il colpo puo' essere lanciato o meno in quella posizione, Intero, 0 <= esitoVerificaScansione <= 1
 *           6) CELLE_LARGO_RAGGIO, Valore che indica l’area o numero di caselle massimo che il largo raggio puo' colpire, Intero, Variabile globale
 *           7) ESITO_COLPO_ERR, Valore che indica che una delle caselle colpite da largo raggio è già stata precedentemente colpita, Intero, Variabile globale
 *           8) ECS, Id dell'errore "Tutte le coordinate scelte sono state gia colpite", Intero, Variabile globale
 *  Output : 1) struttura, Struttura che contiene i dati della partita con i campi modificati, datiPartita
 *  Descrizione: La funzione lancia un colpo largoRaggio al giocatore 2
 */
void lanciareLargoRaggio(datiPartita *struttura){
    coordinate posizioniScansionate[CELLE_SCANSIONARE];
    coordinate colpo;
    player giocatore;
    int errColpo        =0;
    int colpiLanciati   =0;
    int k;
    int esitoColpo;
    int esitoVerificaScansione;


    do {
        ottenereCoordinate(&colpo);

        inizializzarePosScansione(posizioniScansionate);
        calcolareScansione(colpo, posizioniScansionate);

        k = 0;
        while (k < CELLE_LARGO_RAGGIO) {
            esitoVerificaScansione = verificareScansione(posizioniScansionate[k]);
            if (esitoVerificaScansione) {
                lanciareColpo(struttura, posizioniScansionate[k]);
                colpiLanciati++;
                esitoColpo = leggereEsitoColpi(*struttura);
                if(esitoColpo == ESITO_COLPO_ERR) errColpo++;
            }
            k++;
        }
        giocatore = leggereDatiGiocatore1(*struttura);
        if(errColpo == colpiLanciati) stampareErrore(ECS);  // Tutte le coordinate già colpite
    }while(errColpo == colpiLanciati);
    incrementareLargoRaggio(&giocatore);
    scrivereDatiGiocatore1(struttura, giocatore);
}
/*
 *  Funzione: switchGiocatori()
 *  Input  : 1) struttura, Struttura che contiene i dati della partita, DatiPartita
 *           2) giocatore, Struttura che contiene i dati del giocatore corrente, Player
 *           3) avversario, Struttura che contiene i dati del giocatore in attesa del turno, Player
 *           4) turnoPartita, Valore che indica il turno del giocatore 1 o giocatore 2, Intero, PLAYER_UNO <= turnoPartita <= PLAYER_DUE
 *           5) PLAYER_UNO, Turno del giocatore 1, Intero, Variabile globale
 *           6) PLAYER_DUE, Turno del giocatore 2, Intero, Variabile globale
 *  Output : 1) struttura, Struttura che contiene i dati della partita con i campi modificati, datiPartita
 *  Descrizione: La funzione effettua uno switch dei giocatori della struttura datiPartita
 *               permettendo il cambio turno e lasciando in:
 *               - datiGiocatore1 sempre il giocatore in turno
 *               - datiGiocatore2 sempre l'avversario
 */
void switchGiocatori(datiPartita *struttura){
    player giocatore = leggereDatiGiocatore1(*struttura);
    player avversario = leggereDatiGiocatore2(*struttura);
    int turnoPartita;

    scrivereDatiGiocatore1(struttura, avversario);
    scrivereDatiGiocatore2(struttura, giocatore);

    turnoPartita = leggereTurnoPartita(*struttura);
    if(turnoPartita == PLAYER_UNO){
        scrivereTurnoPartita(struttura, PLAYER_DUE);
    }else{
        scrivereTurnoPartita(struttura, PLAYER_UNO);
        incrementareTurniTotali(struttura);
    }
}
/*
 *  Funzione: scrivereColpo()
 *  Input  : 1) giocatore, Struttura dati che contiene i dati del giocatore, Player
 *           2) posizione, Coordinate xy in cui scrivere il colpo, Coordinate
 *           3) tipologia, Tipo di colpo da scrivere nella mappa del giocatore, intero
 *           4) SEGNA_COLPO, Id segna COLPITO in mappaColpi giocatore, Intero, Variabile globale
 *           5) SEGNA_NAVE, Id segna COLPITO in mappaNavi giocatore, Intero, Variabile globale
 *           6) SEGNA_COLPO_MANCATO, Id segna MANCATO in mappaColpi giocatore, Intero, Variabile globale
 *           7) SEGNA_NAVE_MANCATO, Id segna MANCATO in mappaNavi giocatore, Intero, Variabile globale
 *           8) SEGNA_RADAR_NAVE, Id segna RADAR_NAVE in mappaColpi giocatore, Intero, Variabile globale
 *           9) SEGNA_RADAR_VUOTO, Id segna RADAR_VUOTO in mappaColpi giocatore, Intero, Variabile globale
 *           10) COLPITO, Id colpito, Carattere, Variabile globale
 *           11) MANCATO, Id colpo a vuoto, Carattere, Variabile globale
 *           13) RADAR_NAVE, Id presenza nave durante scansione radar, Carattere, Variabile globale
 *           14) RADAR_VUOTO, Id nessuna presenza nave durante scansione radar, Carattere, Variabile globale
 *  Output : 1) giocatore, Struttura dati che contiene i dati del giocatore con i campi modificati, Player
 *  Descrizione: La funzione scrivere il colpo di tipo tipologia nella mappa del giocatore
 */
void scrivereColpo(player *giocatore, coordinate posizione, int tipologia){
    if(tipologia      == SEGNA_COLPO)            scrivereMappaColpi(giocatore, posizione, COLPITO);
    else if(tipologia == SEGNA_NAVE)             scrivereMappaNavi(giocatore, posizione, COLPITO);
    else if(tipologia == SEGNA_COLPO_MANCATO)    scrivereMappaColpi(giocatore, posizione, MANCATO);
    else if(tipologia == SEGNA_NAVE_MANCATO)     scrivereMappaNavi(giocatore, posizione, MANCATO);
    else if(tipologia == SEGNA_RADAR_NAVE)       scrivereMappaColpi(giocatore, posizione, RADAR_NAVE);
    else if(tipologia == SEGNA_RADAR_VUOTO)      scrivereMappaColpi(giocatore, posizione, RADAR_VUOTO);
}
/*
 *  Funzione: aumentareCoordinate()
 *  Input  : 1) colpo, Coordinate del colpo in cui scrivere linea e valore, Coordinate
 *           2) direzione, Valore che indica la direzione in cui lanciare il colpo, VERTICALE, ORIZZONTALE, Intero, VERTICALE <= Direzione <= ORIZZONTALE
 *           3) linea, linea scelta dall'utente, intero, 0 <= linea <= 15
 *           4) valore, Valore da incrementare per variare la posizione all’interno delle righe o colonne della mappa, Intero, 0 <= valore <= 15
 *           5) VERTICALE, Valore che indica l’orientamento verticale, Intero, Variabile globale
 *  Output : 1) colpo, Coordinate del colpo aumentate, Coordinate
 *  Descrizione: La funzione varia i campi X e Y di colpo in base alla direzione
 *               1) se direzione=VERTICALE, fissa le colonne a linea e permette la variazione alle righe
 *               2) se direzione=ORIZZONTALE, fissa le righe a linea e permette la variazione delle colonne
 */
void aumentareCoordinate(coordinate *colpo, int direzione, int linea, int valore){
    if (direzione == VERTICALE) {               // VERTICALE
        scrivereCoordinateX(colpo, valore);     // In verticale le righe variano
        scrivereCoordinateY(colpo, linea);      // le colonne sono fisse
    } else {                                    // ORIZZONTALE
        scrivereCoordinateX(colpo, linea);      // In orizzontale le righe sono fisse
        scrivereCoordinateY(colpo, valore);     // le colonne variano
    }
}
/*
 *  Funzione: calcolareScansione()
 *  Input  : 1) colpo, Contiene le coordinate x, y del colpo, Coordinate
 *           2) posizioni, Coordinate delle nove posizioni da calcolare a partire dalla coordinata colpo, Vettore di coordinate, Dim CELLE_LARGO_RAGGIO
 *           3) righe, Valore del campo x di colpo, Intero, 0 <= righe <= 15
 *           4) colonne, Valore del campo y di colpo, Intero, 0 <= colonne <= 15
 *           5) AREA_LARGO_RAGGIO, lunghezza del colpo largo raggio, Intero, Variabile globale
 *           6) x, coordinate x di colpo, intero, 0 <= x <= 15
 *           7) y, coordinate y di colpo, intero, 0 <= y <= 15
 *  Output : 1) posizioni, Coordinate delle nove posizioni calcolate a partire dalla coordinata colpo, vettore di coordinate, Dim CELLE_LARGO_RAGGIO
 *  Descrizione: La funzione riceve le coordinate e calcola le posizioni intorno di raggio 1
 */
void calcolareScansione(coordinate colpo, coordinate posizioni[CELLE_LARGO_RAGGIO]){
    int conta   = 0;    // contatore del vettore posizioni
    int i       = 0;
    int j;
    int x;
    int y;
    while(i<AREA_LARGO_RAGGIO){
        j = 0;
        while (j < AREA_LARGO_RAGGIO) {
            x = leggereCoordinateX(colpo);
            y = leggereCoordinateY(colpo);
            scrivereCoordinateX(posizioni+conta, (x-1)+i);
            scrivereCoordinateY(posizioni+conta, (y-1)+j);
            conta++;
            j++;
        }
        i++;
    }
}
/*
 *  Funzione: leggereTipoColpo()
 *  Input  : 1) giocatore, Struttura dati che contiene i dati del giocatore, Player
 *           2) turno, Indica il turno del giocatore, Intero, PLAYER_UNO <= turno <= PLAYER_DUE
 *           3) scelta, Scelta utente del colpo, Intero, 1 <= scelta <= 4
 *           4) MAX_LARGO_RAGGIO, Numero massimo di colpi largoRaggio che l'utente puo' lanciare, Intero, Variabile globale
 *           5) MAX_BOMBARDAMENTO, Numero massimo di colpi bombardamento che l'utente puo' lanciare, Intero, Variabile globale
 *           6) MAX_RADAR, Numero massimo di colpi radar che l'utente puo' lanciare, Intero, Variabile globale
 *           7) TURNO_BOMBARDAMENTO, Valore che indica il turno dopo il quale l’utente può lanciare il bombardamento aereo, Intero, Variabile globale
 *           8) SNA, Id dell'errore "Non puoi usare questo tipo di colpo", Intero, Variabile globale
 *           9) c_largoRaggio, numero di colpi largoRaggio che l'utente puo' lanciare, Intero, 0 <= c_largoRaggio <= 3
 *           10) c_bombardamento, numero di colpi bombardamento che l'utente puÃ² lanciare, intero, 0<=c_bombardamento<=1
 *           11) c_radar, numero di colpi radar che l'utente puo' lanciare, intero, 0<=c_radar<=3
 *  Output : 1) scelta, Tipo di colpo scelto dall'utente, Intero, 1 <= scelta <= 4
 *  Descrizione: La funzione legge il tipo di colpo che l'utente vuole lanciare
 */
int leggereTipoColpo(player giocatore, int turno){
    int c_largoRaggio   = MAX_LARGO_RAGGIO  - leggereLargoRaggio(giocatore);
    int c_bombardamento = MAX_BOMBARDAMENTO - leggereBombardamentoAereo(giocatore);
    int c_radar         = MAX_RADAR         - leggereRadar(giocatore);
    int errore;
    int scelta;

    do{
        printf("\nSeleziona tipologia colpo \n");
        printf("1) Colpo classico           \n");
        printf("2) Colpo a largo raggio     [n: %d]\n", c_largoRaggio);
        printf("3) Radar                    [n: %d]\n", c_radar);
        if(turno>TURNO_BOMBARDAMENTO)   printf("4) Bombardamento aereo      [n: %d]\n", c_bombardamento);
        printf("Scelta: ");

        scelta = leggereRispostaValida(1,4);

        if(scelta==1)                                                           errore = 0;
        else if(scelta==2 && c_largoRaggio>0)                                   errore = 0;
        else if(scelta==3 && c_radar>0)                                         errore = 0;
        else if(scelta==4 && c_bombardamento>0 && turno>TURNO_BOMBARDAMENTO)    errore = 0;
        else                                                                    errore = 1;
        if(errore == 1) stampareErrore(SNA);        // Non puoi usare questo tipo di colpo
    }while(errore != 0);
    return scelta;
}
/*
 *  Funzione: leggereLinea()
 *  Input  : 1) direzione, Valore che indica se la direzione indicata è orizzontale o verticale, Intero, 1 <= direzione <= 2
 *           2) lettura, Valore della colonna che l’utente sceglie in caso di direzione verticale, Carattere, A <= lettura <= P
 *           3) VERTICALE, Id orientamento verticale, Intero, Variabile globale
 *  Output : 1) linea, numero di linea o colonna letta, Intero, 0 <= linea <= 15
 *  Descrizione: La funzione legge il numero di linea o di colonne in base alla direzione ricevuta
 */
int leggereLinea(int direzione){
    int linea=0;
    int errore;
    char lettura;

    printf("\n");
    if(direzione == VERTICALE){                                 // direzione = VERTICALE
        do {
            errore = 0;
            printf("Inserisci lettera colonna: ");
            scanf("%c", &lettura);
            fflush(stdin);
            if(lettura>='A' && lettura<='P'){
                linea = (lettura - 64)-1;               // -1 perchÃ© le posizioni nei vettori partono da 0
            }
            else if(lettura>='a' && lettura<='p'){
                linea = (lettura - 96)-1;               // -1 perchÃ© le posizioni nei vettori partono da 0
            }else errore = 1;
        }while(errore);
    }else{                                              // direzione = ORIZZONTALE
        printf("Inserisci numero riga: ");
        linea = leggereRispostaValida(1,16);
        linea--;                                        // -1 perchÃ¨ le posizioni nei vettori partono da 0
    }
    return linea;
}
/*
 *  Funzione: finePartita()
 *  Input  : 1) struttura, Struttura che contiene i dati della partita, datiPartita
 *           2) giocatore, Struttura dati del giocatore1 di struttura, Player
 *           3) avversario, Struttura dati del giocatore2 di struttura, Player
 *           4) naviAffondate, Valore che indica le navi in quel momento affondate dal giocatore, Intero, 0 <= naviAffondate <= 15
 *           5) TOTALE_NAVI, numero totale di navi possibili, Intero, Variabile globale
 *  Output : 1) finePartita, esito della verifica finePartita, Intero, 0 <= finePartita <= 1
 *  Descrizione: La funzione verifica se le navi affondate sono >= di TOTALE_NAVI
 *               in caso di esito positivo la partita e' terminata
 */
int finePartita(datiPartita struttura){
    player giocatore;
    player avversario;
    int finePartita = 1;
    int naviAffondate;
    giocatore = leggereDatiGiocatore1(struttura);
    avversario = leggereDatiGiocatore2(struttura);

    naviAffondate = leggereNaviAffondate(giocatore);
    if(naviAffondate>=TOTALE_NAVI){
        printf("\n%s HAI VINTO :)\n", leggereNomePlayer(&giocatore));
    }else{
        naviAffondate = leggereNaviAffondate(avversario);
        if(naviAffondate>=TOTALE_NAVI) {
            printf("\n%s HAI VINTO :)\n", leggereNomePlayer(&avversario));
        }else finePartita = 0;
    }
    return finePartita;
}
