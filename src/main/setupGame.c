#include "struttureDati.h"
#include "globali.h"
#include "setupGame.h"
#include "stampe.h"
#include "gestioneFile.h"
#include "verifiche.h"
#include "inizializzazioni.h"

player chiedereNomePlayer(player giocatore, int turno);
player posizionareNavi(player giocatore);
void   posizionareNaviAutomatico(player *giocatore);
void   posizionareNaviManuale(player *giocatore);
void   scrivereNave(player *giocatore, coordinate posizione, int direzione, nave nave);

/*
 *  Funzione: setupPartita()
 *  Input  : 1) Struttura, struttura che contiene idati della partita, datiPartita
 *           2) rispSchermataIniziale, risposta dell'utente al menu della schermata iniziale, intero, 0 <= rispSchermataIniziale <= 3
 *           3) rispInizioTurno, risposta dell'utente al menu del posizionamento navi, intero, 0 <= rispInizioTurno <= 1
 *           4) Supporto, struttura dati del giocatore con le navi posizionate, player
 *           5) SRC_SCHERMATA_INIZIALE, percorso del file “schermataIniziale”, vettore di caratteri, variabile globale
 *           6) SRC_SALVATAGGIO, posizione del file "salvataggio", vettore di caratteri, variabile globale
 *           7) SRC_REGOLAMENTO, posizione del file "regolamento", vettore di caratteri, variabile globale
 *           8) ESCI, corrisponde alla scelta di uscire dal gioco, intero, variabile globale
 *           9) BACK, corrisponde al “torna indietro” all’interno dei menu, intero, variabile globale
 *           10) CONTINUA, corrisponde alla scelta di continuare la partita, intero, variabile globale
 *  Output : 1) Struttura, struttura che contiene i dati della partita con i dati modificati, datiPartita
 *  Descrizione: La funzione esegue il setup della partita, cioè:
 *               1) Carica un'eventuale partita
 *               2) Posizione le navi dei giocatori
 *               3) Permette di leggere il regolamento del gioco
 */
void setupPartita(datiPartita *struttura) {
    int rispSchermataIniziale;
    int rispInizioTurno;
    int loop;
    player supporto;

    system("cls");
    do {
        stampareFile(SRC_SCHERMATA_INIZIALE);
        rispSchermataIniziale = leggereRispostaValida(0, 3);

        if(rispSchermataIniziale==0){                        // ESCI DAL GIOCO
            scrivereEndGame(struttura, ESCI);
            loop = 0;
        }else if (rispSchermataIniziale == 1) {              // NUOVA PARTITA
            system("cls");

            inizializzareStruttura(struttura);
            scrivereDatiGiocatore1(struttura, chiedereNomePlayer(leggereDatiGiocatore1(*struttura), PLAYER_UNO));
            scrivereDatiGiocatore2(struttura, chiedereNomePlayer(leggereDatiGiocatore2(*struttura), PLAYER_DUE));

            // POSIZIONAMENTO PLAYER_UNO
            rispInizioTurno = confermareInizioTurno(leggereDatiGiocatore1(*struttura));
            if(rispInizioTurno == 1) {         // CONTINUA
                supporto = posizionareNavi(leggereDatiGiocatore1(*struttura));
                scrivereDatiGiocatore1(struttura, supporto);

                // POSIZIONAMENTO PLAYER DUE
                rispInizioTurno = confermareInizioTurno(leggereDatiGiocatore2(*struttura));
                if(rispInizioTurno == 1) {
                    supporto = posizionareNavi(leggereDatiGiocatore2(*struttura));
                    scrivereDatiGiocatore2(struttura, supporto);
                    scrivereEndGame(struttura, CONTINUA);
                    loop=0;
                }else scrivereEndGame(struttura, BACK);
            }else scrivereEndGame(struttura, BACK);

        } else if(rispSchermataIniziale == 2) {          // CARICA PARTITA
            system("cls");
            if(verificareCaricamento(SRC_SALVATAGGIO)){
                caricarePartita(struttura, SRC_SALVATAGGIO);
                scrivereEndGame(struttura, CONTINUA);
                loop = 0;
            }else loop = 1;

        }else if(rispSchermataIniziale == 3){            // LEGGI REGOLAMENTO
            system("cls");
            stampareFile(SRC_REGOLAMENTO);
            printf("\n\nDigita '1' per tornare indietro: ");
            rispSchermataIniziale = leggereRispostaValida(1, 1);
            system("cls");
            loop = 1;
        }
    }while(loop);
    system("cls");
}
/*
 *  Funzione: chiedereNomePlayer()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore, player
 *           2) Turno, valore che indica il turno della partita, intero, PLAYER_UNO <= turno PLAYER_DUE
 *           3) lenStringa, valore che indica la lunghezza della stringa, intero, 1 <= lenStringa < MAX_DIM_STRINGA_NOME
 *           4) nomePlayer, stringa letta da tastiera, stringa, vettore di caratteri, 1 <= nomePlayer < MAX_DIM_STRINGA_NOME
 *           3) MAX_DIM_STRINGA_NOME, dimensione massima per la stringa del nome del giocatore, intero, variabile globale
 *           4) PLAYER_UNO, identificativo del turno del giocatore 1, intero, variabile globale
 *           5) PLAYER_DUE, identificativo del turno del giocatore 2, intero, variabile globale
 *           6) SLO, errore che indica che il nome del player deve essere MAX_DIM_STRINGA, intero, variabile globale
 *  Output : 1) Giocatore, struttura che contiene i dati del giocatore con i campi modificati, player
 *  Descrizione: La funzione restituisce il la struttura giocatore con il nomePlayer del giocatore letto da tastiera
 */
player chiedereNomePlayer(player giocatore, int turno){
    int errore      = 1;
    int lenStringa;
    char nomePlayer[MAX_DIM_STRINGA_NOME];

    while(errore) {
        printf("Inserisci nome giocatore ");
        if (turno == PLAYER_UNO) printf("giocatore_1 : ");
        if (turno == PLAYER_DUE) printf("giocatore_2 : ");
        scanf("%s", nomePlayer);
        lenStringa = strlen(nomePlayer);
        if (lenStringa < MAX_DIM_STRINGA_NOME){
            strcpy(leggereNomePlayer(&giocatore), nomePlayer);
            errore = 0;
        }
        else stampareErrore(SLO);
    }
    return giocatore;
}
/*
 *  Funzione: posizionaNavi()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore, player
 *           2) Scelta, valore della scelta del posizionamento navi, intero, 1 <= scelta <= 2
 *           3) SRC_MOD_POS_NAVI, percorso del file modalità posizionamento navi, vettore di caratteri, variabile globale
 *           4) SRC_POS_AUTO_NAVI, percorso del file posizionamento automatico navi, vettore di caratteri, variabile globale
 *           5) MAPPA_NAVI, identificativo della mappa navi, intero, variabile globale
 *  Output : 1) Giocatore, struttura che contiene i dati del giocatore con i campi modificati, player
 *  Descrizione: La funzione restituisce i dati del player con le navi posizionate
 */
player posizionareNavi(player giocatore){
    int scelta;

    stampareFile(SRC_MOD_POS_NAVI);
    scelta = leggereRispostaValida(1,2);
    inizializzareMappa(&giocatore, MAPPA_NAVI);
    system("cls");
    if(scelta == 1){                                                // AUTOMATICO
        while(scelta == 1){                                         // fino a quando utente non conferma la mappa generata
            system("cls");
            posizionareNaviAutomatico(&giocatore);               // Genera mappa con navi posizionate automaticamente
            stampareMappaNavi(giocatore);
            printf("\n\n");
            stampareFile(SRC_POS_AUTO_NAVI);
            scelta = leggereRispostaValida(1,2);
            if(scelta == 1) inizializzareMappa(&giocatore, MAPPA_NAVI);      // Se utente decide di voler generare una nuova mappa, allora inizializza quella vecchia
        }
    }else posizionareNaviManuale(&giocatore);                            // MANUALE
    return giocatore;
}
/*
 *  Funzione: posizionaNaviAutomatico()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore, player
 *           2) Posizione, struttura dati che contiene i dati delle coordinate, coordinate
 *           3) Navi, contiene i dati delle navi, vettore di nave, dimensione = NUMERO_NAVI
 *           4) Direzione, valore che indica la direzione in cui inserire la nave nella mappa, intero, VERTICALE <= direzione <= ORIZZONTALE
 *           5) numeroNavi, numero di navi rimaste da inserire nel vettore di navi in posizione i, vettore di caratteri, NUM_NAVESUPPORTO <= numeroNavi <= NUM_PORTAEREI
 *           6) isValid, valore che indica l’esito della verifica sulle coordinate, intero,	0 <= isValid <= 1
 *           7) esitoVerificaNave, valore che indica l’esito della verifica del posizionamento della nave, intero,	1 <= esitoVerificaNave <= 2
 *           8) NUMERO_NAVI, valore che indica il numero massimo di navi usabili in gioco, intero, variabile globale
 *  Output : 1) Giocatore, struttura che contiene i dati del giocatore con i campi modificati, player
 *  Descrizione: La funzione genera una mappaNavi con le navi posizionate automaticamente
 */
void posizionareNaviAutomatico(player *giocatore){
    coordinate  posizione;
    nave navi[NUMERO_NAVI];
    int  i          = 0;    // Contatore del vettore navi
    int  k;                 // Contatore degli elementi del vettore navi
    int  direzione;
    int  numeroNavi;
    int  isValid;
    int  esitoVerificaNave;

    ottieniDatiNavi(navi);
    srand(time(0));         // Fornisce alla funzione srand un seme: time(0) ovvero il tempo

    numeroNavi = leggereNumeroNave(navi[i]);
    while(i<NUMERO_NAVI){
        k = 0;
        while(k<numeroNavi){
            isValid = 0;
            scrivereCoordinateIsValid(&posizione, isValid);
            while(isValid == 0) {
                scrivereCoordinateX(&posizione, rand()%15);
                scrivereCoordinateY(&posizione, rand()%15);
                direzione = 1+rand()%2;
                esitoVerificaNave = verificareNave(*giocatore, posizione, direzione, leggereLunghezzaNave(navi[i]));
                if(!esitoVerificaNave){
                    scrivereNave(giocatore, posizione, direzione, navi[i]);
                    scrivereCoordinateIsValid(&posizione, 1);
                }else scrivereCoordinateIsValid(&posizione, 0);
                isValid = leggereCoordinateIsValid(posizione);
            }
            k++;
            numeroNavi = leggereNumeroNave(navi[i]);
        }
        i++;
    }
}
/*
 *  Funzione: posizionareNaviManuale()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore, player
 *           2) Posizione, struttura dati che contiene i dati delle coordinate, coordinate
 *           3) Navi, contiene i dati delle navi, vettore di nave, dimensione = NUMERO_NAVI
 *           4) Direzione, valore che indica la direzione in cui inserire la nave nella mappa, intero,	VERTICALE <= direzione <= ORIZZONTALE
 *           5) numeroNavi, numero di navi rimaste da inserire nel vettore di navi in posizione i, vettore di caratteri, NUM_NAVESUPPORTO <= numeroNavi <= NUM_PORTAEREI
 *           6) isValid, valore che indica l’esito della verifica sulle coordinate,	intero,	0 <= isValid <= 1
 *           7) esitoVerificaNave, valore che indica l’esito della verifica del posizionamento della nave, intero, 1 <= esitoVerificaNave <= 2
 *           8) lunghezzaNave, indica la lunghezza della nave da posizionare, intero, 1 <= lunghezzaNave <= 5
 *           9) idNave, id della nave da posizionare, carattere, A <= idNave <= E
 *           10) NUMERO_NAVI, valore che indica il numero massimo di navi usabili in gioco, intero, variabile globale
 *           11) SRC_DIREZIONE, percorso del file direzione, vettore di caratteri, variabile globale
 *           12) ID_NAVESUPPORTO, lettera identificativa della nave di supporto, carattere, variabile globale
 *           13) SOL, numero identificativo dell’errore “nave non rientra nella mappa”, intero, variabile globale
 *           14) SDS, numero identificativo dell’errore “Distanza navi non rispettata”, intero, variabile globale
 *           15) ISP, numero identificativo dell’errore “Posizione nave non valida”, intero, variabile globale
 *  Output : 1) Giocatore, struttura che contiene i dati del giocatore con i campi modificati, player
 *  Descrizione: La funzione consente all'utente di posizionare in modo manuale le sue navi
 */
void posizionareNaviManuale(player *giocatore){
    coordinate  posizione;
    nave navi[NUMERO_NAVI];
    int  i          = 0;    // Contatore del vettore navi
    int  k;                 // Contatore degli elementi del vettore navi
    int  direzione;
    int  numeroNavi;
    int  isValid;
    int  esitoVerificaNave;
    int  lunghezzaNave;
    char idNave;

    ottieniDatiNavi(navi);
    numeroNavi = leggereNumeroNave(navi[i]);

    while(i<NUMERO_NAVI){
        k = 0;
        while(k<numeroNavi){
            isValid = 0;
            scrivereCoordinateIsValid(&posizione, isValid);
            while(!isValid) {
                stampareMappaNavi(*giocatore);
                lunghezzaNave = leggereLunghezzaNave(navi[i]);
                printf("\n\nPosizionamento nave %d' di lunghezza: %d\n", k+1, lunghezzaNave);
                ottenereCoordinate(&posizione);
                isValid = leggereCoordinateIsValid(posizione);
                if (isValid){
                    stampareFile(SRC_DIREZIONE);
                    idNave = leggereIdNave(navi[i]);
                    if(idNave != ID_NAVESUPPORTO)   direzione = leggereRispostaValida(1,2);
                    else                            direzione = VERTICALE;
                    esitoVerificaNave = verificareNave(*giocatore, posizione, direzione, lunghezzaNave);
                    if(esitoVerificaNave == 0){
                        scrivereNave(giocatore, posizione, direzione, navi[i]);
                    }else{
                        system("cls");
                        scrivereCoordinateIsValid(&posizione, 0);
                        if(esitoVerificaNave == 1) stampareErrore(SOL);      // Nave non rientra nella mappa
                        if(esitoVerificaNave == 2) stampareErrore(SDS);      // Distanza tra le navi non rispettata
                    }
                }else{
                    system("cls");
                    stampareErrore(ISP);                          // Posizione nave non valida
                }
                isValid = leggereCoordinateIsValid(posizione);
            }
            system("cls");
            k++;
            numeroNavi = leggereNumeroNave(navi[i]);
        }
        i++;
    }
}
/*
 *  Funzione: scrivereNave()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore, player
 *           2) Posizione, struttura dati che contiene i dati delle coordinate, coordinate
 *           3) Direzione, valore che indica la direzione in cui inserire la nave nella mappa, intero, VERTICALE <= direzione <= ORIZZONTALE
 *           4) Nave, contiene i dati della nave da scrivere, nave
 *           5) lenNave, lunghezza della nave da inserire nella mappa, intero, LEN_NAVESUPPORTO <= lenNave <= LEN_PORTAEREI
 *           6) VERTICALE, valore che corrisponde alla posizione verticale, intero, variabile globale
 *  Output : 1) Giocatore, struttura che contiene i dati del giocatore con i campi modificati, player
 *  Descrizione: La funzione scrive la nave nella mappa navi del giocatore
 */
void scrivereNave(player *giocatore, coordinate posizione, int direzione, nave nave){
    int i       = 0;
    int lenNave;
    lenNave = leggereLunghezzaNave(nave);
    while(i<lenNave) {
        scrivereMappaNavi(giocatore, posizione, leggereIdNave(nave));
        if (direzione == VERTICALE) incrementareCoordinateX(&posizione);        // VERTICALE
        else                        incrementareCoordinateY(&posizione);        // ORIZZONTALE
        lenNave = leggereLunghezzaNave(nave);
        i++;
    }
}