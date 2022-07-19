#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TestaOCroce.h"

#define MIN_BINARI_STAZIONE 4
#define MAX_BINARI_STAZIONE 8



struct treni{
    char nome[10];
    int codice_numerico;
    int turni_di_attesa;
    int competato;
};

struct binari{
    char nome_treno[10];
    int turni_treno_fermo;
    int stato_binario;
};

typedef struct treni TRENI;
typedef struct binari BINARI;

typedef enum coin {TESTA,CROCE} coin;

int main()
{
    int b_stazione;
    int turno_partita=0;
    int tot_treni_generati=0;
    int tot_treni_spartiti=0;
    int i;
    int k;
    int f;
    int Y;
    int z;
    int h;
    int setting;
    TRENI Treno[50];
    BINARI  Binario[MAX_BINARI_STAZIONE];
    Binario[0].stato_binario = -5;



//binari della stazione
//indica il turno del ciclo (quindi anche lo score del giocatore
//quanti treni sono compars a causa della
//quanti treni ho già consegnato in stazione
//per alcuni cicli for
//per analizzare i casi dello switch-case for
//caso:luce rossa



    //fase 1: scegliere quanti binari

    printf("scegliere un numero di binari della stazione comreo tra %d e %d:\n", MIN_BINARI_STAZIONE, MAX_BINARI_STAZIONE);
    b_stazione = scansione(MIN_BINARI_STAZIONE ,MAX_BINARI_STAZIONE);

    int attesa_fuori_stazione = b_stazione-3;
    int attesa_in_stazione = b_stazione-2;
//per quanti turni il treno può aspettare
//tempo necessario prima di lasciare la stazione

    //setting
    for(setting=0;setting<=50;setting++)
    {
        Treno[setting].turni_di_attesa = -10;
    }


    printf("La stazione ha %d binari\n", b_stazione);
    printf("I treni impiegano %d turni per libarare il binario\nI treni possono aspettare al massimo %d turni fuori dalla stazione\n",attesa_fuori_stazione, attesa_in_stazione);


    //fase 2.1: iniziare un turno


    INIZIO_TURNO:
    INIZIO_TURNO_2:

    turno_partita = turno_partita++;
    printf("Turno:%d\n\n", turno_partita);

    if (turno_partita > 50)
    {
        printf(" sei sopravvissuto 50 turni.\n\nHAI VINTO");
        return 1;
    }

    for(i=0; i<=b_stazione; i++)
    {
        Binario[i].turni_treno_fermo=Binario[i].turni_treno_fermo++;
    }
   // printf("il problema non è al primo agg\n\n");

    //if(tot_treni_generati != 0){
        //printf("il problema non e' alla negazione\n\n");
               // printf("il problema non e' all'if\n\n");
        for(z=0; z<=50; z++)
            {
                //printf("il problema non e' al for\n\n");
        Treno[z].turni_di_attesa = Treno[z].turni_di_attesa-1;
        //printf(" %dtest1 %d",z,Treno[z].turni_di_attesa);
            }

        for(h=0; h<50; h++){
        if(Treno[h].turni_di_attesa == 0)
        {
            printf("%dtest2 %d",h,Treno[h].turni_di_attesa);
            printf("Hai fatto aspettare un treno troppo a lungo.\n\n");
            goto GAME_OVER;
        }
        }
    //}
    //else goto SALTO;


    //Fase 2.2: girare la moneta: testa nuovo treno/croce nulla.

   //SALTO:

   // srand( time(NULL) );
    if (flipCoin() == TESTA) {
            printf("Hai un nuovo treno in attesa\n");
            tot_treni_generati=tot_treni_generati+1;
            Treno[tot_treni_generati].turni_di_attesa=attesa_fuori_stazione;
            printf("Hai %d treni in attesa\n",tot_treni_generati-tot_treni_spartiti);
            //printf("\n%d\n",tot_treni_generati);
    }
    else printf("Nessun nuovo treno in attesa\n");

    //fase 3: controllo di tutti i binari

    for(k=1; k<=b_stazione; k++){
        if (Binario[k].turni_treno_fermo < 0)
        {
            Binario[k].stato_binario = 1;
            printf("Il binario %d e' occupato\n",k);
        }
        else
        {
            Binario[k].stato_binario = 0;
            printf("Il binario %d e' libero\n",k);
        }
	}

	//fase 4: spartire i treni in sttazione

	if(tot_treni_generati-tot_treni_spartiti == 0)
        goto INIZIO_TURNO;


    RIPETI:

    for(f=0; f<=50;f++)
    {
        if(f>tot_treni_spartiti && f<=tot_treni_generati){
        printf("Stai spostando il treno %d nel binario:",f);

        printf("(Selezionare un binario)\n");
        Y=scansione(0 , MAX_BINARI_STAZIONE);

        /*switch(Binario[Y].stato_binario){
            case -5:
            printf("Hai saltato il turno\n");
            break;
            case 0:
            printf("Il binario selezionato e':%d\n",Y);
            Binario[Y].turni_treno_fermo= -attesa_in_stazione;
            break;
            case 1:
            printf("Hai causato un incidente\n\n");
            goto GAME_OVER;
            break;
    }*/
        if (Binario[Y].stato_binario == -5){
            printf("Hai saltato il turno\n");
            goto INIZIO_TURNO;
        }
        if (Binario[Y].stato_binario == 0){
            printf("Il binario selezionato e': %d\n", Y);
            tot_treni_spartiti = tot_treni_spartiti++;
            Treno[tot_treni_spartiti++].turni_di_attesa=-10;
        }
        if (Binario[Y].stato_binario == 1){
            printf("Hai causato un incidente \n\n");
            goto GAME_OVER;
        }
    }
    }


    if (tot_treni_spartiti == tot_treni_generati)
        printf("Non hai piu' treni da portare in stazione\n\n");
    else
    {
        goto RIPETI;
    }


    goto INIZIO_TURNO_2;


    GAME_OVER:
        printf("GAME OVER\n\n\nSei durato %d turni", turno_partita);
        return 0;
}

