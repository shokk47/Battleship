#include "globali.h"
#include "setupGame.h"
#include "stampe.h"
#include "gameLoop.h"
#include "gestioneFile.h"

int main() {
    datiPartita dati;
    int endgame;
    do {
        setupPartita(&dati);
        endgame = leggereEndGame(dati);
        if(endgame==CONTINUA){
            gameLoop(&dati);
            endgame = leggereEndGame(dati);
        }
        if(endgame==SALVARE)    salvarePartita(dati, SRC_SALVATAGGIO);
        else if(endgame==BACK)  system("cls");
    }while(endgame==BACK);

    printf("\nGRAZIE PER AVER GIOCATO :)\n\n");
    system("pause");
    return 0;
}