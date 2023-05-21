#ifndef BATTAGLIA_NAVALE_STAMPE_H
#define BATTAGLIA_NAVALE_STAMPE_H

#define SRC_REGOLAMENTO        "../files/regolamento.txt"
#define SRC_SCHERMATA_INIZIALE "../files/schermataIniziale.txt"
#define SRC_DIREZIONE          "../files/direzione.txt"
#define SRC_POS_AUTO_NAVI      "../files/posizionareNaviAutomatico.txt"
#define SRC_MOD_POS_NAVI       "../files/modalitaPosizionamentoNavi.txt"
#define SRC_FINE_TURNO         "../files/fineTurno.txt"
#define SRC_INIZIO_TURNO       "../files/inizioTurno.txt"
#define SRC_SALVATAGGIO        "../backup/salvataggio/dati.dat"

#define OFF                     0       // Open file failed
#define WFF                     1       // Write file failed
#define FNE                     2       // File not exists
#define SLO                     3       // String length overflow
#define SOL                     4       // Ship overlap
#define SDS                     5       // Short distance ship
#define ISP                     6       // Invalid ship position
#define SNA                     7       // Shot not allowed
#define SAS                     8       // Shot already shot
#define SOM                     9       // Shot over map
#define ANC                     10      // Answer not correct
#define ECS                     11      // every coordinate shot
#define EAL                     12      // everything coordinate scan

void stampareFile(char nomeFile[]);
void stampareMappaNavi(player giocatore);
void stampareMappe(player giocatore);
void stampareErrore(int id);
void stampareEsitoColpo(coordinate colpo, int esito);
void stampareInizioTurno(player giocatore, int turniTotali);
int  confermareInizioTurno(player giocatore);
int  confermareFineTurno(player giocatore);

#endif //BATTAGLIA_NAVALE_STAMPE_H
