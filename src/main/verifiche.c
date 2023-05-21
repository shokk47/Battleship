#include "verifiche.h"

int verificareSingolaAffondata(player giocatore, coordinate colpo);
int verificareAffondatoVerticale(player giocatore, coordinate colpo);
int verificareAffondatoOrizzontale(player giocatore, coordinate colpo);
int verificareDirezioneNave(player giocatore, coordinate posizione);

/*
 *  Funzione: verificarePresenzaNave()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore corrente, player
 *           2) Posizione, struttura che contiene le coordinate in cui verificare la presenza della nave, coordinate
 *           3) ID_PORTAEREI, id della nave di len5, carattere, variabile globale
 *           4) ID_CORAZZATA, id della nave di len4, carattere, variabile globale
 *           5) ID_INCROCIATORE, id della nave di len3, carattere, variabile globale
 *           6) ID_CACCIATORPEDINIERE, id della nave di len2, carattere, variabile globale
 *           7) ID_NAVESUPPORTO, id della nave di len 1, carattere, variabile globale
 *  Output : 1) presenza, esito della verifica presenzaNave (0 = non Ã¨ presente, 1 = presente), intero, 0 <= presenza <= 1
 *  Descrizione: La funzione verifica se Ã¨ presente una nave in coordinate posizione
 */
int verificarePresenzaNave(player giocatore, coordinate posizione){
    int presenza;

    if(verificarePresenza(giocatore, posizione, ID_PORTAEREI))                   presenza = 1;
    else if(verificarePresenza(giocatore, posizione, ID_CORAZZATA))              presenza = 1;
    else if(verificarePresenza(giocatore, posizione, ID_INCROCIATORE))           presenza = 1;
    else if(verificarePresenza(giocatore, posizione, ID_CACCIATORPEDINIERE))     presenza = 1;
    else if(verificarePresenza(giocatore, posizione, ID_NAVESUPPORTO))           presenza = 1;
    else                                                                         presenza = 0;
    return presenza;
}
/*
 *  Funzione: verificareNave()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore corrente, player
 *           2) Posizione, struttura che contiene le coordinate della nave da posizionare, coordinate
 *           3) Direzione, indica la direzione della nave da posizionare (1 = VERTICALE 2 = ORIZZONTALE), intero, 1 <= direzione <= 2
 *           4) lunghezzaNave, lunghezza della nave da posizionare, intero, 1 <= lunghezzaNave <= 5
 *           5) Lettura, copia di posizione su cui effettuare calcoli, coordinate, = posizione
 *           6) esitoLetturaX, variabile che contiene il valore di x di posizione, intero, 0 <= esitoLetturaX <= RIGHE
 *           7) esitoLetturaY, variabile che contiene il valore di y di posizione, intero, 0 <= esitoLetturaY <= COLONNE
 *           8) esitoPresenza, esito della verifica: verificaPresenza, intero, 0 <= esitoPresenza <= 1
 *           9) DISTANZA_NAVI, Valore della distanza tra le navi, intero, variabile globale
 *           10) ACQUA, id Acqua delle Mappe, intero, variabile globale
 *           11) RIGHE, valore che corrisponde al numero di righe della Mappa, intero, variabile globale
 *           12) COLONNE, valore che corrisponde al numero di colonne della Mappa, intero, variabile globale
 *  Output : 1) errore, esito della verifica verificareNave, intero, 0 <= errore <= 2
 *  Descrizione: La funzione verifica se la nave puÃ² essere posizionata e restituirÃ :
 *               i) 0 SE NAVE PUO' ESSERE POSIZIONATA
 *               ii) 1 SE NAVE NON RIENTRA NELLA MAPPA
 *               iii) 2 SE NAVE NON RISPETTA DISTANZA DI SICUREZZA
 */
int verificareNave(player giocatore, coordinate posizione, int direzione, int lunghezzaNave){
    coordinate lettura  = posizione;
    int errore          = 0;
    int i               = 0;
    int esitoLetturaX;
    int esitoLetturaY;
    int esitoPresenza;
    int j;
    int r;
    int c;

    // IMPOSTO LE COORDINATE IN DIAGONALE-1
    decrementareCoordinateX(&lettura);
    decrementareCoordinateY(&lettura);

    // IMPOSTO SOTTOMATRICE DA SCANSIONARE
    if(direzione == 1){                     // VERTICALE
        r = lunghezzaNave+2;
        c = DISTANZA_NAVI;
    }else{                                  // ORIZZONTALE
        r = DISTANZA_NAVI;
        c = lunghezzaNave+2;
    }

    // CONTROLLO ERRORI
    while(i<r && errore == 0){
        j=0;
        while(j<c && errore == 0){
            esitoLetturaX = leggereCoordinateX(lettura);
            esitoLetturaY = leggereCoordinateY(lettura);
            if((esitoLetturaX>=0 && esitoLetturaX<RIGHE) && (esitoLetturaY>=0 && esitoLetturaY<COLONNE)){
                esitoPresenza = verificarePresenza(giocatore, lettura, ACQUA);
                if(!esitoPresenza){
                    errore=2;       // ERRORE: DISTANZA NAVE NON RISPETTATA
                }
            }else if((esitoLetturaX<-1 || esitoLetturaX>RIGHE) || (esitoLetturaY<-1 || esitoLetturaY>COLONNE)){
                errore=1;           // ERRORE: NAVE NON RIENTRA NELLA MAPPA
            }
            incrementareCoordinateY(&lettura);
            j++;
        }
        scrivereCoordinateY(&lettura, leggereCoordinateY(posizione)-1);
        incrementareCoordinateX(&lettura);
        i++;
    }
    return errore;
}
/*
 *  Funzione: verificareNaveAffondata()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore corrente, player
 *           2) Colpo, struttura che contiene le coordinate della nave colpita, coordinate	/
 *           3) Direzione, valore che indica la direzione della nave -1 = nave singola || 1 = VERTICALE || 2 = ORIZZONTALE , intero, = -1, = 1,  =2
 *           4) VERTICALE, valore che corrisponde alla posizione verticale, intero, variabile globale
 *           5) ORIZZONTALE, valore che corrisponde alla posizione orizzontale, intero, variabile globale
 *  Output : 1) affondato, esito della verifica naveAffondata (0 = non Ã¨ affondata, 1 = Ã¨ affondata), intero, 0 <= affondato <= 1
 *  Descrizione: La funzione verifica se la nave in posizione colpo Ã¨ stata affondata
 */
int verificareNaveAffondata(player giocatore, coordinate colpo){
    int  affondato   = 1;     // STABILISCO PER ASSURDO CHE LA NAVE SIA AFFONDATA
                              // LA FUNZIONE DOVRA' VERIFICARE IL CONTRARIO
    int   direzione;

    direzione    = verificareDirezioneNave(giocatore, colpo);

    if(direzione == VERTICALE){
        affondato = verificareAffondatoVerticale(giocatore, colpo);
    }else if(direzione == ORIZZONTALE){
        affondato = verificareAffondatoOrizzontale(giocatore, colpo);
    }else{
        affondato = verificareSingolaAffondata(giocatore, colpo);
    }
    return affondato;
}
/*
 *  Funzione: verificareScansione()
 *  Input  : 1) Posizione, struttura che contiene le coordinate inserite da scansionare, coordinate
 *           2) r, numero di riga su cui effettuare la scansione, intero, 0 <= r <RIGHE
 *           3) c, numero di colonna su cui effettuare la scansione, intero, 0 <= c < COLONNE
 *           4) RIGHE, valore che corrisponde al numero di righe della Mappa, intero, variabile globale
 *           5) COLONNE, valore che corrisponde al numero di colonne della Mappa, intero, variabile globale
 *  Output : 1) esito, esito della verifica scansione (=0 ERR || =1 OK), intero, 0 <= esito <= 1
 *  Descrizione: La funzione verifica se delle coordinate ricevute in input
 *               rientrano nel range della mappa. Necessaria in radar e largoRaggio
 */
int verificareScansione(coordinate posizione){
    int esito   = 0;
    int r;              // righe
    int c;              // colonne

    r   = leggereCoordinateX(posizione);
    c = leggereCoordinateY(posizione);

    if(r>=0 && r<RIGHE){
        if(c>=0 && c<COLONNE){
            esito = 1;
        }
    }
    return esito;
}
/*
 *  Funzione: verificarePresenza()
 *  Input  : 1) giocatore, struttura che contiene i dati del giocatore corrente, player
 *           2) Posizione, struttura che contiene le coordinate in cui verificare se Ã¨ presente lâ€™elemento â€œverificareâ€�, coordinate
 *           3) Verificare, elemento di cui verificare la presenza in mappaNavi del giocatore, carattere, A <= verificare <= E
 *           4) letturaMappaNavi, elemento presente su mappaNavi nella posizione inserita, carattere, A <= verificare <= E
 *  Output : 1) errore, esito della verificaPresenza (=1 elemento presente || = 0 elemento non presente), intero, 0 <= errore <= 1
 *  Descrizione: La funzione verifica se l'elemento verificare ricevuto Ã¨ presente in MappaNavi in coordinate posizione
 */
int verificarePresenza(player giocatore, coordinate posizione, char verificare){
    char letturaMappaNavi;
    int errore;

    letturaMappaNavi = leggereMappaNavi(giocatore, posizione);
    if(letturaMappaNavi == verificare)  errore = 1;
    else                                errore = 0;
    return errore;
}
/*
 *  Funzione: verificareCoordinate()
 *  Input  : 1) stringaCoordinate, stringa che contiene le coordinate da verificare, vettore di caratteri, dim = MAX_DIM_STRINGA_POS
 *           2) Posizione, struttura che contiene le coordinate da verificare, coordinate
 *           3) Verificare, elemento da verificare in mappaNavi del giocatore, carattere, A <= verificare <= E
 *  Output : 1) posizione, struttura che contiene le coordinate verificate, coordinate
 *  Descrizione: La funzione verifica se la stringa ricevuta rispettano i seguenti requisiti:
 *               1) Nel formato An(A1,A2,A3,...,A16) e non nA(1A,2A,3A,...,16A)
 *               2) A sia compresa tra 'A' e 'P' || 'a' e 'p'
 *               3) n sia compresa tra 1 e 16
 *               4) il terzo elemento di StringaCoordinate deve essere '\0'
 */
void verificareCoordinate(char stringaCoordinate[MAX_DIM_STRINGA_POS], coordinate *posizione){
    int lenStringa = strlen(stringaCoordinate);
    if(lenStringa>=2 && lenStringa<=MAX_DIM_STRINGA_POS) {

        // VERIFICA LETTURA COLONNE
        if (stringaCoordinate[0] >= 'A' && stringaCoordinate[0] <= 'P') {
            scrivereCoordinateY(posizione, stringaCoordinate[0] - 65);
            scrivereCoordinateIsValid(posizione, 1);
        } else if (stringaCoordinate[0] >= 'a' && stringaCoordinate[0] <= 'p') {
            scrivereCoordinateY(posizione, stringaCoordinate[0] - 97);
            scrivereCoordinateIsValid(posizione, 1);
        } else scrivereCoordinateIsValid(posizione, 0);

        // SE VERIFICA PRECEDENTE == 0 ERRORI, PROCEDE VERIFICA LETTURA RIGHE
        if (leggereCoordinateIsValid(*posizione)) {
            if (stringaCoordinate[1] == '1' && (stringaCoordinate[2] >= '0' && stringaCoordinate[2] <= '6') && stringaCoordinate[3] == '\0') {
                scrivereCoordinateX(posizione, 10 + stringaCoordinate[2] - 49);
                scrivereCoordinateIsValid(posizione, 1);
            } else if (stringaCoordinate[1] >= '1' && stringaCoordinate[1] <= '9' && stringaCoordinate[2] == '\0') {
                scrivereCoordinateX(posizione, stringaCoordinate[1] - 49);
                scrivereCoordinateIsValid(posizione, 1);
            } else scrivereCoordinateIsValid(posizione, 0);
        }
    }else scrivereCoordinateIsValid(posizione, 0);
}
/*
 *  Funzione: verificareSingolaAffondata()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore corrente, player
 *           2) Colpo, struttura che contiene le coordinate della nave colpita, coordinate
 *           3) colpoBackup, copia di colpo per effettuare calcoli, coordinate
 *           4) letturaMappaIncrementata, valore mappaNavi in posizione x,y+1 di colpo, carattere, tutti i caratteri ammessi nella mappaNavi
 *           5) letturaMappaDecrementata, valore mappaNavi in posizione x,y-1 di colpo, carattere, tutti i caratteri ammessi nella mappaNavi
 *           6) pos, valore di colpoBackup.x, intero, 0 <= pos <= 15
 *  Output : 1) affondato, esito della verifica naveAffondata (0 = non Ã¨ affondata, 1 = affondata), intero, 0 <= affondato <= 1
 *  Descrizione: La funzione verifica se la nave di len1 in posizione colpo Ã¨ stata affondata
 */
int verificareSingolaAffondata(player giocatore, coordinate colpo){
    coordinate colpoBackup;
    char letturaMappaIncrementata;
    char letturaMappaDecrementata;
    int  pos;
    int  affondato = 1;

    colpoBackup = colpo;
    incrementareCoordinateX(&colpoBackup);
    pos = leggereCoordinateX(colpoBackup);
    letturaMappaIncrementata = leggereMappaNavi(giocatore, colpoBackup);
    scrivereCoordinateX(&colpoBackup, pos-2);
    letturaMappaDecrementata = leggereMappaNavi(giocatore, colpoBackup);

    // VERIFICO I VALORI RIGHE +1 E -1 DI COLPO (VERIFICA VERTICALE)
    if((letturaMappaIncrementata>='A' && letturaMappaIncrementata<='E') || (letturaMappaDecrementata>='A' && letturaMappaDecrementata<='E')){
        affondato = 0;
    }else{
        colpoBackup = colpo;
        incrementareCoordinateY(&colpoBackup);
        pos = leggereCoordinateY(colpoBackup);
        letturaMappaIncrementata = leggereMappaNavi(giocatore, colpoBackup);
        scrivereCoordinateY(&colpoBackup, pos-2);
        letturaMappaDecrementata = leggereMappaNavi(giocatore, colpoBackup);

        // VERIFICO I VALORI COLONNE +1 E -1 DI COLPO (VERIFICA ORIZZONTALE)
        if((letturaMappaIncrementata>='A' && letturaMappaIncrementata<='E') || (letturaMappaDecrementata>='A' && letturaMappaDecrementata<='E')){
            affondato = 0;
        }
    }
    return affondato;
}
/*
 *  Funzione: verificareAffondatoVerticale()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore corrente, player
 *           2) Colpo, struttura che contiene le coordinate della nave colpita,	coordinate
 *           3) letturaMappa, contiene il valore presente su mappaNavi nella posizione colpita, carattere, tutti i caratteri ammessi nella mappaNavi
 *           4) r, numero di riga in cui si trova la parte di nave colpita, intero,	0 <= r < RIGHE
 *           5) ACQUA, id dell'Acqua in mappa, carattere, variabile globale
 *           6) RIGHE, valore che corrisponde al numero di righe della Mappa, intero, variabile globale
 *  Output : 1) affondato, esito della verifica naveAffondata (0 = non affondata, 1 = affondata), intero, 0 <= affondato <= 1
 *  Descrizione: La funzione verifica se una nave verticale Ã¨ stata affondata
 */
int verificareAffondatoVerticale(player giocatore, coordinate colpo){
    char letturaMappa;
    int  affondato = 1;     // Stabilisco per assurdo nave affondata
    int  r;                 // counter della nave

    letturaMappa = leggereMappaNavi(giocatore, colpo);
    r            = leggereCoordinateX(colpo);

    // Posiziono il counter righe in posizione ultima della nave verso il basso
    while(letturaMappa != ACQUA && (r>=0 && r<RIGHE)) {
        r += 1;                                                             // Aumento il counter (verso il basso) fino a quando non trovo acqua
        scrivereCoordinateX(&colpo, r);
        letturaMappa = leggereMappaNavi(giocatore, colpo);
    }
    r--;                                                                    // Diminuisco il counter di 1 rientrare nell'area della nave
    scrivereCoordinateX(&colpo, r);
    letturaMappa = leggereMappaNavi(giocatore, colpo);

    // Verifico fino a quando non trovo acqua, se l'id equivalente corrisponde a una nave
    while(letturaMappa != ACQUA && affondato==1 && (r>=0 && r<RIGHE)){
        if(letturaMappa>='A' && letturaMappa<='E'){                         // Se Ã¨ presente un elemento della nave, la nave non Ã¨ affondata
            affondato = 0;
        }else{
            r--;                                                            // Altrimenti diminuisco il counter (verso su)
            scrivereCoordinateX(&colpo, r);
            letturaMappa = leggereMappaNavi(giocatore, colpo);
        }
    }
    return affondato;
}
/*
 *  Funzione: verificareAffondatoOrizzontale()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore corrente, player
 *           2) Colpo, struttura che contiene le coordinate della nave colpita, coordinate
 *           3) letturaMappa, contiene il valore presente su mappaNavi nella posizione colpita, carattere, tutti i caratteri ammessi nella mappaNavi
 *           4) c, numero di colonna in cui si trova la parte di nave colpita, intero, 0 <= c < COLONNE
 *           5) ACQUA, id dell'acqua in mappa, carattere, variabile globale
 *           6) COLONNE, valore che corrisponde al numero di colonne della Mappa, intero, variabile globale
 *  Output : 1) affondato, esito della verifica naveAffondata (0 = non affondata, 1 = affondata), intero, 0 <= affondato <= 1
 *  Descrizione: La funzione verifica se una nave orizzontale Ã¨ stata affondata
 */
int verificareAffondatoOrizzontale(player giocatore, coordinate colpo){
    char letturaMappa;
    int  affondato = 1;     // Stabilisco per assurdo nave affondata
    int  c;                 // counter della nave

    letturaMappa = leggereMappaNavi(giocatore, colpo);
    c            = leggereCoordinateY(colpo);

    // Posiziono il counter righe in posizione ultima della nave verso il destra
    while(letturaMappa != ACQUA && (c>=0 && c<COLONNE)) {
        c += 1;                                                          // Aumento il counter (verso destra) fino a quando non trovo acqua
        scrivereCoordinateY(&colpo, c);
        letturaMappa = leggereMappaNavi(giocatore, colpo);
    }
    c--;                                                                // Diminuisco il counter di 1 rientrare nell'area della nave
    scrivereCoordinateY(&colpo, c);
    letturaMappa = leggereMappaNavi(giocatore, colpo);

    while(letturaMappa != ACQUA && affondato==1 && (c>=0 && c<COLONNE)) {
        if (letturaMappa >= 'A' && letturaMappa <= 'E') {               // Se Ã¨ presente un elemento della nave, la nave non Ã¨ affondata
            affondato = 0;
        }else {
            c--;                                                        // Altrimenti diminuisco il counter (verso sinistra) e aggiorno i valori
            scrivereCoordinateY(&colpo, c);
            letturaMappa = leggereMappaNavi(giocatore, colpo);
        }
    }
    return affondato;
}
/*
 *  Funzione: verificareDirezioneNave()
 *  Input  : 1) Giocatore, struttura che contiene i dati del giocatore corrente, player
 *           2) Posizione, struttura che contiene le coordinate della nave colpita, coordinate
 *           3) letturaMappa, contiene il valore presente su mappaNavi nella posizione colpita, carattere, tutti i caratteri ammessi nella mappa navi
 *           4) r, numero di riga in cui si trova la parte di nave colpita, intero, 0 <= r < RIGHE
 *           4) c, numero di colonna in cui si trova la parte di nave colpita, intero, 0 <= c < COLONNE
 *           5) RIGHE, valore che corrisponde al numero di righe della Mappa, intero, variabile globale
 *           6) COLONNE, valore che corrisponde al numero di colonne della Mappa, intero, variabile globale
 *           7) VERTICALE, valore che corrisponde alla posizione verticale, intero, variabile globale
 *           8) ORIZZONTALE, valore che corrisponde alla posizione orizzontale, intero, variabile globale
 *           9) COLPITO, valore che indica una parte di nave colpita, carattere, variabile globale
 *  Output : 1) direzione, esito della verifica direzioneNave, intero, = ERR || = VERTICALE || = ORIZZONTALE
 *  Descrizione: La funzione stabilisce la direzione della nave
 */
int verificareDirezioneNave(player giocatore, coordinate posizione){
    coordinate posizioneBackup;
    char letturaMappa;
    int  direzione = ERR;               // se rimane ERR sarÃ  una naveSupporto/acqua/nave non ancora affondata
    int  r;                             // counter delle righe
    int  c;                             // counter delle colonne

    // Copio le coordinate posizione in posizione backup
    posizioneBackup = posizione;
    r = leggereCoordinateX(posizioneBackup);

    // VERIFICA NAVE VERTICALE
    if(r-1 >= 0 || r+1 < RIGHE){                                            // se le coordinate rientrano nel range della mappa
        scrivereCoordinateX(&posizioneBackup, r+1);                      // stabilisco la coordinata come quella x+1 in basso
        letturaMappa = leggereMappaNavi(giocatore, posizioneBackup);
        if(letturaMappa == COLPITO){                                        // se mappa in coordinata .x+1 Ã¨ colpita, allora la nave Ã¨ verticale
            direzione = VERTICALE;
        }else{                                                              // Altrimenti verifico in coordinata .x-1 (quindi +1 verso il basso)
            scrivereCoordinateX(&posizioneBackup, r-1);                  // stabilisco la coordinata come quella .x+1 in alto
            letturaMappa = leggereMappaNavi(giocatore, posizioneBackup);
            if(letturaMappa == COLPITO)                                     // se mappa in coordinata .x-1 Ã¨ colpita, allora la nave Ã¨ verticale
            direzione = VERTICALE;
        }
    }

    // VERIFICA NAVE ORIZZONTALE
    if(direzione != VERTICALE) {                                            // Se la funzione non Ã¨ riuscita a stabilire la direzione verticale, allora:
        posizioneBackup = posizione;                                        // riacquisto le posizioni iniziali del colpo
        c = leggereCoordinateY(posizioneBackup);
        if (c - 1 >= 0 || c + 1 < COLONNE) {                                // se le coordinate rientrano nel range della mappa
            scrivereCoordinateY(&posizioneBackup, c+1);                  // stabilisco la coordinata come quella y+1 a destra
            letturaMappa = leggereMappaNavi(giocatore, posizioneBackup);
            if (letturaMappa == COLPITO) {                                  // se coordinata in .y+1 Ã¨ colpita, allora Ã¨ orizzontale
                direzione = ORIZZONTALE;
            }else{                                                          // Altrimenti verifico in coordinata .y-1 (quindi +1 a sinistra)
                scrivereCoordinateY(&posizioneBackup, c-1);
                letturaMappa = leggereMappaNavi(giocatore, posizioneBackup);
                if(letturaMappa == COLPITO){                                // se mappa in coordinata .y-1 Ã¨ colpita, allora la nave Ã¨ orizzontale
                    direzione = ORIZZONTALE;
                }
            }
        }
    }
    return direzione;
}
