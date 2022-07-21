#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sottofunzioni.h"

#define MIN_BINARI_STAZIONE 5
#define MAX_BINARI_STAZIONE 10



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
    int turno_partita;
    int tot_treni_generati;
    int tot_treni_spartiti=0;
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
//quanti treni sono comparsi a causa della flip-coin
//quanti treni ho già consegnato in stazione
//per sistemarre delle variabil iniziali
//Binario[0].stato_binario = -5; caso in cui non seleziono alcun binari


    //fase 1: scegliere quanti binari

    printf("Scegliere un numero di binari della stazione compreso tra %d e %d:\n", MIN_BINARI_STAZIONE, MAX_BINARI_STAZIONE);
    b_stazione = scansione(MIN_BINARI_STAZIONE ,MAX_BINARI_STAZIONE);

    int modulo_b_stazione=0-b_stazione;
    int attesa_fuori_stazione = b_stazione-3;
    int attesa_in_stazione = 3*modulo_b_stazione/2;
//per quanti turni il treno può aspettare
//tempo necessario prima di lasciare la stazione

    printf("ISTRUZIONI:\nAd ogni nuovo turno hai il 50/100 di possibilita' dell'arrivo di un nuovo treno che vuole entrare in stazione;\n");
    printf("La stazione ha %d binari;\n",b_stazione);
    printf("I treni impiegano %d turni per libarare il binario\nI treni possono aspettare al massimo %d turni fuori dalla stazione;\n",-attesa_in_stazione, attesa_fuori_stazione);
    printf("Ad ogni turno dovrai indicare ai treni in attesa in quale binario posizionarsi(nel caso si collochino due treni nello stesso binario sara' GAME OVER);\nPuoi indicare a tutti i treni in attesa di aspettare fuori dalla stazione selezionando il binario 0\n\n");
    sleep(10);

    //setting
    for(setting=0;setting<=50;setting++)
    {
        Treno[setting].turni_di_attesa = -10;
    }
    for(setting=0;setting<=b_stazione;setting++){
        Binario[setting].turni_treno_fermo=0;
    }


    turno_partita=1;
    tot_treni_generati=1;
    tot_treni_spartiti=1;

    //fase 2.1: iniziare un turno


    INIZIO_TURNO:
    INIZIO_TURNO_2:


    Sleep(650);
    turno_partita = turno_partita+1;
    printf("LIVELLO %d\n\n",turno_partita-1);

    if (turno_partita > 50)
    {
        printf(" Sei sopravvissuto 50 turni.\n\nHAI VINTO");
        return 1;
    }

    for(h=1; h<=b_stazione; h++){
        Binario[h].turni_treno_fermo = Binario[h].turni_treno_fermo+1;
        //printf("turni che sta fermo %d\n",Binario[h].turni_treno_fermo);
    }

        for(z=0; z<=50; z++)
            {
        Treno[z].turni_di_attesa = Treno[z].turni_di_attesa-1;
        //printf("%d\n",Treno[z].turni_di_attesa);
            }

        //printf("%dtest %d/n",tot_treni_spartiti+1,Treno[tot_treni_spartiti+1].turni_di_attesa);
        if(Treno[tot_treni_spartiti+1].turni_di_attesa == 0)
        {
            //printf("%dtest %d/n",tot_treni_spartiti+1,Treno[tot_treni_spartiti+1].turni_di_attesa);
            printf("Hai fatto aspettare un treno troppo a lungo.\n\n");
            goto FINE;
        }
        printf("Il treno puo' aspettare massimo %d turni\n",Treno[tot_treni_spartiti+1].turni_di_attesa);



    //Fase 2.2: girare la moneta: testa nuovo treno/croce nulla.


   // srand( time(NULL) );
    if (flipCoin() == TESTA) {
            printf("Hai un nuovo treno in attesa\n");
            tot_treni_generati=tot_treni_generati+1;
            Treno[tot_treni_generati].turni_di_attesa=attesa_fuori_stazione;
            printf("Hai %d treni in attesa\n",tot_treni_generati-tot_treni_spartiti);
            printf("Hai %d turni prima di fallire\n\n",Treno[tot_treni_spartiti+1].turni_di_attesa);
    }
    else printf("Nessun nuovo treno in attesa\n\n");

    //fase 3: controllo di tutti i binari


    RIPETI:

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
    printf("\n");

	//fase 4: spartire i treni in sttazione


        f=tot_treni_spartiti+1;
        //printf("%d; %d; %d\n",tot_treni_generati,tot_treni_spartiti,f);

        if (tot_treni_spartiti==tot_treni_generati)
        {
        printf("Non hai piu' treni da portare in stazione\n\n");
        goto INIZIO_TURNO_2;
        }
        else{
        printf("Stai spostando il treno %d nel binario:",f);

        printf("(Selezionare un binario)\n");
        Y=scansione(0 , b_stazione);

        {
        if (Binario[Y].stato_binario == -5)
        {
            printf("Hai saltato il turno\n\n\n");
            //Treno[tot_treni_spartiti+1].turni_di_attesa=Treno[tot_treni_spartiti+1].turni_di_attesa;
            goto INIZIO_TURNO;
        }
        if (Binario[Y].stato_binario == 0)
        {
            printf("Il binario selezionato e': %d\n\n\n", Y);
            Binario[Y].turni_treno_fermo=attesa_in_stazione;
            tot_treni_spartiti = tot_treni_spartiti+1;
            Treno[tot_treni_spartiti].turni_di_attesa=-10;
            goto RIPETI;
        }
        if (Binario[Y].stato_binario == 1)
        {
            printf("Hai causato un incidente \n\n");
            goto FINE;
        }
        }
        }



    FINE:
        printf("GAME OVER\n\n\nSei durato %d turni", turno_partita);
        return 0;
}
