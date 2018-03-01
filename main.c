#include <stdio.h>
#define PUISSANCE 65

unsigned long long puissanceMod(unsigned long long nombre, unsigned long long exposant, unsigned long long modulo);

int main()
{
    printf("\n=== DECRYPTER CODE RSA ===\n\n\n");

    unsigned long long monN;
    unsigned long long monD;
    unsigned long long autreN;
    unsigned long long autreE;

    unsigned long long exposant1;
    unsigned long long modulo1;
    unsigned long long exposant2;
    unsigned long long modulo2;
    unsigned reponse;
    unsigned long long message;

    do{
        fflush(stdin);
        printf("Voulez vous decrypter :\n (1) une signature\n (2) un message\n");
        scanf("%d", &reponse);
    }while(reponse < 1 || reponse > 2);

    do{
        fflush(stdin);
        printf("\nSaisiez le code a decrypter : ");
        scanf("%I64u", &message);
    }while(message == 0);

    do{
        fflush(stdin);
        printf("Quel est votre d ? ");
        scanf("%I64u", &monD);
    }while(monD == 0);

    do{
        printf("Quel est votre n ? ");
        scanf("%I64u", &monN);
    }while(monN < 2);

    if(reponse == 1){
        do{
            fflush(stdin);
            printf("Quel est l'autre n ? ");
            scanf("%I64u", &autreN);
        }while(autreN < 2);

        do{
            fflush(stdin);
            printf("Quel est l'autre e ? ");
            scanf("%I64u", &autreE);
        }while(autreE < 2);
    }

    if(reponse == 1){
        if(autreN < monN){
            exposant1 = monD;
            modulo1 = monN;
            exposant2 = autreE;
            modulo2 = autreN;
        }
        else{
            exposant2 = autreE;
            modulo2 = autreN;
            exposant1 = monD;
            modulo1 = monN;
        }
    }
    else{
        exposant2 = monD;
        modulo2 = monN;
    }


    if(reponse == 1){
        printf("\nCode decryte : %I64u\n", puissanceMod(puissanceMod(message, exposant1, modulo1), exposant2, modulo2));
    }
    else{
        printf("\nCode decryte : %I64u\n", puissanceMod(message, exposant2, modulo2));
    }
    return 0;
}

unsigned long long puissanceMod(unsigned long long nombre, unsigned long long exposant, unsigned long long modulo)
{
    int decomposition[PUISSANCE];
    unsigned long long recomposition[PUISSANCE];
    unsigned long long tmp;
    int i = 0;
    int j = 0;

    for(i = 0; i < PUISSANCE; i++){
        decomposition[i] = 0;
        recomposition[i] = 1;
    }

    for(i = PUISSANCE - 1; i >= 0; i--){
        if(i == 0) tmp = 1;
        else tmp = 2;
        for(j = 1; j < i; j++){
            tmp *= 2;
        }
        if(exposant >= tmp){
            exposant -= tmp;
            decomposition[i] = 1;
        }
    }
    if(exposant > 0){
        printf("ERREUR : AGRANDIR LA PUISSANCE !\n");
        printf("exposant : %I64u\n", exposant);
    }

    recomposition[0] = nombre;
    while(recomposition[0] > modulo){
        recomposition[0] -= modulo;
    }

    for(i = 1; i < PUISSANCE; i++){
        tmp = recomposition[i-1] * recomposition[i-1];
        while(tmp > modulo){
            tmp -= modulo;
        }
        recomposition[i] = tmp;
    }

    tmp = 1;
    for(i = 0; i < PUISSANCE; i++){
        if(decomposition[i] == 1){
            tmp *= recomposition[i];
            while(tmp > modulo){
                tmp -= modulo;
            }
        }
    }

    return tmp;
}
