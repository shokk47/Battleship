#ifndef BATTAGLIA_NAVALE_STRUTTUREDATI_H
#define BATTAGLIA_NAVALE_STRUTTUREDATI_H

#define RIGHE                   16
#define COLONNE                 16
#define MAX_DIM_STRINGA_NOME    20
#define NUMERO_NAVI             5


typedef char matrice[RIGHE][COLONNE];

typedef struct colpiSpeciali{
    int             bombardamentoAereo;
    int             radar;
    int             largoRaggio;
}colpiSpeciali;

typedef struct player{
    colpiSpeciali   colpiSS;
    matrice         mappaNavi;
    matrice         mappaColpi;
    char            nomePlayer[MAX_DIM_STRINGA_NOME];
    int             naviAffondate;
}player;

typedef struct datiPartita{
    player datiGiocatore_1;
    player datiGiocatore_2;
    int turnoPartita;
    int turniTotali;
    int esitoColpo;
    int endGame;
}datiPartita;

typedef struct nave{
    char            id;
    int             lunghezza;
    int             numero;
}nave;

typedef struct coordinate{
    int             x;
    int             y;
    int             isValid;
}coordinate;

void ottieniDatiNavi(nave navi[NUMERO_NAVI]);

// FUNZIONI DI ACCESSO STRUCT: PLAYER
void    scrivereMappaNavi(player *giocatore, coordinate posizione, char valore);
void    scrivereMappaColpi(player *giocatore, coordinate posizione, char valore);
void    scrivereNaviAffondate(player *giocatore, int valore);
void    incrementareNaviAffondate(player *giocatore);
char    leggereMappaNavi(player giocatore, coordinate posizione);
char    leggereMappaColpi(player giocatore, coordinate posizione);
char*   leggereNomePlayer(player *giocatore);
int     leggereNaviAffondate(player giocatore);

// FUNZIONI DI ACCESSO STRUCT : COLPISPECIALI
void    scrivereColpiSpeciali(player *giocatore, colpiSpeciali struttura);
void    scrivereBombardamentoAereo(player *giocatore, int valore);
void    scrivereRadar(player *giocatore, int valore);
void    scrivereLargoRaggio(player *giocatore, int valore);
void    incrementareBombardamentoAereo(player *giocatore);
void    incrementareRadar(player *giocatore);
void    incrementareLargoRaggio(player *giocatore);
colpiSpeciali leggereColpiSpeciali(player giocatore);
int     leggereBombardamentoAereo(player giocatore);
int     leggereRadar(player giocatore);
int     leggereLargoRaggio(player giocatore);

// FUNZIONI DI ACCESSO STRUCT : NAVE
void    scrivereIdNave(nave *navi, char ID);
void    scrivereLunghezzaNave(nave *navi, int lunghezza);
void    scrivereNumeroNave(nave *navi, int numero);
char    leggereIdNave(nave navi);
int     leggereLunghezzaNave(nave navi);
int     leggereNumeroNave(nave navi);

// FUNZIONI DI ACCESSO STRUCT : COORDINATE
void    scrivereCoordinateX(coordinate *posizione, int x);
void    scrivereCoordinateY(coordinate *posizione, int y);
void    scrivereCoordinateIsValid(coordinate *posizione, int isValid);
void    incrementareCoordinateX(coordinate *posizione);
void    incrementareCoordinateY(coordinate *posizione);
void    decrementareCoordinateX(coordinate *posizione);
void    decrementareCoordinateY(coordinate *posizione);
int     leggereCoordinateX(coordinate posizione);
int     leggereCoordinateY(coordinate posizione);
int     leggereCoordinateIsValid(coordinate posizione);


// FUNZIONI DI ACCESSO STRUCT : SALVATAGGIO
void    scrivereDatiGiocatore1(datiPartita *struttura, player datiGiocatore_1);
void    scrivereDatiGiocatore2(datiPartita *struttura, player datiGiocatore_2);
void    scrivereTurnoPartita(datiPartita *struttura, int turnoPartita);
void    scrivereTurniTotali(datiPartita *struttura, int turniTotali);
void    scrivereEsitoColpi(datiPartita *struttura, int esito);
void    scrivereEndGame(datiPartita *struttura, int endGame);
player  leggereDatiGiocatore1(datiPartita struttura);
player  leggereDatiGiocatore2(datiPartita struttura);
int     leggereTurnoPartita(datiPartita struttura);
int     leggereTurniTotali(datiPartita struttura);
int     leggereEsitoColpi(datiPartita struttura);
int     leggereEndGame(datiPartita struttura);
void    incrementareTurniTotali(datiPartita *struttura);

#endif //BATTAGLIA_NAVALE_STRUTTUREDATI_H
