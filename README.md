# Battaglia Navale 

## **Regole del gioco classico** ##

La Battaglia Navale è un entusiasmante gioco di strategia in cui due giocatori si sfidano per affondare le navi dell'avversario. Nel gioco al computer, è possibile giocare sia contro un avversario umano che contro il computer stesso.

All'inizio del gioco, ogni giocatore ha due tabelle di dimensioni 16x16 sullo schermo del computer. Queste tabelle rappresentano il campo di battaglia e sono suddivise in celle identificate da coppie di coordinate.

I giocatori posizionano le proprie navi su una delle tabelle, mantenendo la posizione segreta all'avversario. Ogni nave occupa un numero di celle adiacenti in linea retta, sia orizzontalmente che verticalmente. Le navi non possono toccarsi.

La partita procede a turni, dove ogni giocatore sceglie una coordinata da colpire sulla tabella avversaria. Il computer o l'avversario controlla se la cella colpita corrisponde a una nave. Se la nave viene colpita, viene segnalato "colpito!" e la cella colpita viene contrassegnata come colpita sulla tabella del giocatore avversario. Se la nave non viene colpita, viene segnalato "acqua" o "mancato".

Quando un colpo colpisce l'ultima cella di una nave che non è ancora stata affondata, il giocatore avversario dichiara "colpito e affondato!" e la nave viene considerata persa.

Vince il giocatore che riesce a affondare tutte le navi dell'avversario per primo.

## **Variante** ##
Il gioco che è stato realizzato implementa diverse tipologie di navi con dimensioni diverse, come portaerei, navi corazzate, incrociatori, cacciatorpediniere e navi di supporto. Ognuna di queste navi occupa un numero specifico di celle. In particolare:

- 1 PORTAEREI 		da 5 caselle
- 2 NAVI CORAZZATA 	da 4 caselle
- 3 INCROCIATORI 	da 3 caselle
- 4 CACCIATORPEDINIERE 	da 2 caselle
- 5 NAVE DI SUPPORTO	da 1 casella

per un totale di 15 navi.

Inoltre, sono stati introdotti alcuni **colpi speciali** :

- **Colpo a largo raggio** : oltre alla casella indicata (ovvero la casella centrale) ha effetto anche
sulle caselle intorno (raggio 1 per un totale di 9 caselle). Per ogni singola casella colpita
verranno stampate a schermo le coordinate della casella e il messaggio (mancato) se il colpo
non ha colpito alcuna nave, (colpito) se si e' colpita una nave senza affondarla e (colpito e
affondato) se si colpisce l'ultima cella ancora intatta di una nave facendola dunque affondare.
Ogni giocatore ha 3 colpi a largo raggio. I risultati del colpo verranno segnati sulla seconda
griglia del giocatore

- **Bombardamento aereo** : per colpire una riga/colonna a scelta: Dopo 10 turni viene sbloccata
la possibilita' di colpire una riga o una colonna a scelta della griglia dell'avversario. Per ogni
singola casella colpita verranno stampate a schermo le coordinate della casella e il
messaggio (mancato) se il colpo non ha colpito alcuna nave, (colpito) se si e' colpita una nave
senza affondarla e (colpito e affondato) se si colpisce l'ultima cella ancora intatta di una nave
facendola dunque affondare. Utilizzabile solo 1 volta. I risultati del bombardamento aereo
verranno segnati sulla seconda griglia del giocatore

- **Radar** : Utilizzato per scansionare 9 celle (raggio 1), bisogna specificare la casella centrale.
Per ogni casella analizzata verranno stampate a schermo le coordinate della cella e il
messaggio (vuoto) se non vi e' alcuna nave oppure (nave) se vi e' una nave. Utilizzabile fin
da subito per un totale di 3 utilizzi. I risultati della scansione verranno segnati sulla seconda
griglia del giocatore
