#include <iostream>
#define PUISSANCE 25

using namespace std;

unsigned long long puissanceMod(unsigned long long nombre, unsigned long long exposant, unsigned long long modulo);

int main()
{
    cout << endl << "=== DECRYPTER CODE RSA ===" << endl << endl << endl;

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
        cout << "Quel est votre d ? ";
        cin >> monD;
    }while(monD == 0);
    do{
        cout << "Quel est votre n ? ";
        cin >> monN;
    }while(monN < 2);
    //}while(monN < 1000 || monN > 100000000);
    do{
        cout << "Quel est l'autre e ? ";
        cin >> autreE;
    }while(autreE < 2);
    do{
        cout << "Quel est l'autre n ? ";
        cin >> autreN;
    }while(autreN < 2);
    //}while(autreN < 1000 || autreN > 100000000);

    /*monD = 52;//exposant
    monN = 13;//modulo
    autreE = 17;//exposant
    autreN = 2773;//modulo*/

    do{
        cout << endl << "Voulez vous decrypter :" << endl << " (1) une signature" << endl << " (2) un message" << endl;
        cin >> reponse;
    }while(reponse < 1 || reponse > 2);
    do{
        cout << endl << "Saisier le code a decrypter : ";
        cin >> message;
    }while(message == 0);

    /*reponse = 2;
    message = 7;*/

    if(reponse == 1){
        if(autreN < monN){
            exposant1 = monD;
            modulo1 = monN;
            exposant2 = autreE;
            modulo2 = autreN;
        }
        else{
            exposant1 = autreE;
            modulo1 = autreN;
            exposant2 = monD;
            modulo2 = monN;
        }
    }

    if(reponse == 1){
        cout << endl << "Code decryte : " << puissanceMod(puissanceMod(message, exposant1, modulo1), exposant2, modulo2) << endl;
    }
    else{
        cout << endl << "Code decryte : " << puissanceMod(message, monD, monN) << endl;
    }
    return 0;
}

unsigned long long puissanceMod(unsigned long long nombre, unsigned long long exposant, unsigned long long modulo)
{
    bool decomposition[PUISSANCE];
    unsigned long long recomposition[PUISSANCE];
    unsigned long long tmp;

    for(int i = 0; i < PUISSANCE; i++){
        decomposition[i] = false;
        recomposition[i] = 1;
    }

    for(int i = PUISSANCE - 1; i >= 0; i--){
        if(i == 0) tmp = 1;
        else tmp = 2;
        for(int j = 1; j < i; j++){
            tmp *= 2;
        }
        if(exposant >= tmp){
            exposant -= tmp;
            decomposition[i] = true;
        }
    }
    if(exposant > 0){
        cout << "ERREUR : AGRANDIR LA PUISSANCE !" << endl;
        cout << "exposant : " << exposant << endl;
    }

    recomposition[0] = nombre;
    while(recomposition[0] > modulo){
        recomposition[0] -= modulo;
    }
    for(int i = 1; i < PUISSANCE; i++){
        tmp = recomposition[i-1] * recomposition[i-1];
        while(tmp > modulo){
            tmp -= modulo;
        }
        recomposition[i] = tmp;
    }

    tmp = 1;
    for(int i = 0; i < PUISSANCE; i++){
        if(decomposition[i] == true){
            tmp *= recomposition[i];
            while(tmp > modulo){
                tmp -= modulo;
            }
        }
    }

    return tmp;
}
