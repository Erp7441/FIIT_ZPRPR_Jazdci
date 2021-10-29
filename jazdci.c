/*

--------------------------------------------------------------------------
|                                  Jazdci                                |
|                               Martin Szabo                             |
|                                  116304                                |
--------------------------------------------------------------------------

*/

//*---------------------------------------------------- Preprocesor ---------------------------------------------------

// Program bol naprogramovany v Visual Studio Code s GCC kompilatorom

// !Vypne scanf depricated warning pre GCC kompilator
#define _CRT_SECURE_NO_DEPRECATE
// !Vypne scanf depricated warning pre MSVC kompilator
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//*----------------------------------------------------- Štruktúry ----------------------------------------------------

typedef struct jazdec{
    char *meno;
    char *priezvisko;
    char *znacka;
    char pohlavie;
    int rok;
    float casy[5];
}jazdec;

//*-------------------------------------------------- Pomocné funkcie -------------------------------------------------

void nacitatJazdcov(jazdec ** tabulka);
int pocetMedzier(char retazec[]); // Ziska pocet medzier v retazci

//*-------------------------------------------------- Hlavné funkcie --------------------------------------------------

void podpis(char const* zadanie, char const* meno, char const* aisID);
void sum(jazdec* tabulka);


int main() {

//*----------------------------------------------------- Premenné -----------------------------------------------------

    char vyber;
    jazdec* tabulka = NULL;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    podpis("Jazdci", "Martin Szabo", "116304");
    nacitatJazdcov(&tabulka);

//*------------------------------------------------------- Menu -------------------------------------------------------

    do {
        //TODO oramovať menu (pripadne spraviť reusable funkciu pre menu)
        printf("\n\ns - Sum\nd - Driver\nl - Lap\ng - Gender\nb - Brand\ny - Year\na - Average\nu - Under\nc - Change\nn - New Driver\nr - Remove Driver\nr - Reload\ne - Exit");
        printf("\nVolba: ");
        scanf("%c", &vyber);
        getchar(); // Odstrani medzeru od scanfu na konci buffera
        switch (vyber) {
            case 's':
                sum(tabulka);
                break;
            case 'r':
                nacitatJazdcov(&tabulka);
                break;
            default:
                printf("Zly vyber");
                break;
        }
    } while (vyber != 'e');


    getchar();
    return 0;
}

void podpis(char const* zadanie, char const* meno, char const* aisID) {

//*-------------------------------------------------- Dĺžka reťazca ---------------------------------------------------

    // Zistenie dĺžky reťazcov (vhodne keď nechcem použiť string.h knižnicu)
    size_t dlzkaZadania = 0, dlzkaMena = 0, dlzkaAisID = 0;
    if(zadanie) {
        for (size_t i = 0; zadanie[i] != '\0'; i++) {
            dlzkaZadania++;
        }
    }
    if(meno) {
        for (size_t i = 0; meno[i] != '\0'; i++) {
            dlzkaMena++;
        }
    }
    if(aisID) { 
        for (size_t i = 0; aisID[i] != '\0'; i++) {
            dlzkaAisID++;
        }
    }

//*----------------------------------------------- Veľkosť ohraničenia ------------------------------------------------

    size_t velkostOhranicenia = 50 + dlzkaZadania + dlzkaMena + dlzkaAisID;
    if(velkostOhranicenia % 2 == 1) {velkostOhranicenia++;}
    
    if(dlzkaZadania == 0 && dlzkaMena == 0 && dlzkaAisID == 0) {
        printf("Nezadali ste ziadne udaje");
        return;
    }

//*--------------------------------------------------- Vrchný rám -----------------------------------------------------

    for (size_t i = 0; i < velkostOhranicenia; i++) {
        printf("-");
    }
    printf("\n");
    
//*----------------------------------------------------- Zadanie ------------------------------------------------------

    if(zadanie && dlzkaZadania > 0) {
        printf("|");
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaZadania - 1)/2; i++) {
            printf(" "); // Do polovičky ohraničenia vypíšeme medzeri...
        }
        printf("%s", zadanie); // ...Potom vypíšeme zadanie...
        if(dlzkaZadania % 2 == 1) {dlzkaZadania++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaZadania - 1)/2; i++) {
            printf(" "); // Následne dopíšeme zvyšné medzeri...
        }
        // Na koniec zakončíme riadok
        printf("|\n");
    }

//*------------------------------------------------------- Meno -------------------------------------------------------

    if(meno && dlzkaMena > 0) {
        printf("|");
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaMena - 1)/2; i++) {
            printf(" ");
        }
        printf("%s", meno);
        if(dlzkaMena % 2 == 1) {dlzkaMena++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaMena - 1)/2; i++) {
            printf(" ");
        }
        printf("|\n");
    }

    // AIS ID
    if(aisID && dlzkaAisID > 0) {
        printf("|");
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaAisID - 1)/2; i++) {
            printf(" ");
        }
        printf("%s", aisID);
        if(dlzkaAisID % 2 == 1) {dlzkaAisID++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaAisID - 1)/2; i++) {
            printf(" ");
        }
        printf("|\n");
    }

    // Spodny ram
    for (size_t i = 0; i < velkostOhranicenia; i++) {
        printf("-");
    }
    return;    
}

void nacitatJazdcov(jazdec ** tabulka){
    
//*----------------------------------------------------- Premenné -----------------------------------------------------

    FILE* subor;
    char riadok[100];
    size_t velkost = 0;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    if((*tabulka)!=NULL){ free((*tabulka)); }
    // TODO ? fix garbage na konci pola ?
    (*tabulka) = (jazdec*)malloc(velkost * sizeof(jazdec)); // Inicializujem dynamicke pole jazdcov  // TODO checknúť alokáciu
    
    if(!(subor = fopen("jazdci.csv", "r+"))){
        printf("Error: %d", errno);
        exit(EXIT_FAILURE);
    }

//*------------------------------------------------ Čítanie zo súboru -------------------------------------------------

    while(fgets(riadok, 100, subor)){
        velkost++;
        (*tabulka) = (jazdec*)realloc((*tabulka),velkost * sizeof(jazdec)); // TODO checknúť alokáciu
        
        char *udaj = (char*)calloc(100,sizeof(char)); // TODO checknúť alokáciu
        strcpy(udaj,riadok);
        udaj = strtok(udaj, ";"); // Strtok rozdeli reťazec na niekolko častí oddelene ";".

        //*------------------------------------  Kontrola, či jazdec nemá stredné meno ---------------------------------

        if(pocetMedzier(udaj)>1){
            udaj = strtok(udaj, " ");  // Rozseknem si meno na menšie
            for (size_t i = 0; udaj != NULL; i++){ 
                switch (i){
                case 0: // Iterujem tak že prvé dve časti dám pod meno...
                    (*tabulka)[velkost-1].meno = (char*) calloc(strlen(udaj), sizeof(char)); // TODO checknúť alokáciu
                    strcpy((*tabulka)[velkost-1].meno, udaj);
                    break;
                case 1: //...
                    strcat((*tabulka)[velkost-1].meno, " ");
                    strcat((*tabulka)[velkost-1].meno, udaj);
                    break;
                case 2: // ...zvyšok ide pod priezvisko
                    (*tabulka)[velkost-1].priezvisko = (char*) calloc(strlen(udaj), sizeof(char)); // TODO checknúť alokáciu
                    strcpy((*tabulka)[velkost-1].priezvisko, udaj);
                    break;
                default: //...
                    strcat((*tabulka)[velkost-1].priezvisko, " ");
                    strcat((*tabulka)[velkost-1].priezvisko, udaj);
                    break;
                }
                // Toto prečíta posledný NULL token a zmaže starý...
                udaj = strtok(NULL, " "); // Strtok s argumentom NULL nám bude pokračovať v tokenizácií reťazca.
            }
        }
        else{
            (*tabulka)[velkost-1].meno = (char*) calloc(strlen(udaj), sizeof(char)); // TODO checknúť alokáciu
            (*tabulka)[velkost-1].priezvisko = (char*) calloc(strlen(udaj), sizeof(char)); // TODO checknúť alokáciu
            udaj = strtok(udaj, " ");
            strcpy((*tabulka)[velkost-1].meno, udaj);
            udaj = strtok(NULL, ";");
            strcpy((*tabulka)[velkost-1].priezvisko, udaj);
            udaj = strtok(NULL, ";");
        }
        
        //*----------------------------------------  Nahranie zvyšných údajov -----------------------------------------

        // ...nemusím uvolňovať údaj lebo pri prechádzani tokenov reťazca sa staré sami zmažú
        udaj = (char*)calloc(100,sizeof(char)); // TODO checknúť alokáciu
        strcpy(udaj,riadok);
        udaj = strtok(udaj, ";"); /// Strtok rozdelí reťazec na niekoľko častí oddelene ";".

        for (size_t i = 0; udaj != NULL; i++){
            switch (i) {
            case 1:
                (*tabulka)[velkost-1].pohlavie = udaj[0];
                break;
            case 2:
                (*tabulka)[velkost-1].rok = atoi(udaj);
                break;
            case 3:
                (*tabulka)[velkost-1].znacka = (char*) calloc(strlen(udaj), sizeof(char)); // TODO checknúť alokáciu
                strcpy((*tabulka)[velkost-1].znacka, udaj);
                break;
            case 4: case 5: case 6: case 7: case 8:
                for (size_t j = 0; udaj != NULL && j < 5; j++){
                    (*tabulka)[velkost-1].casy[j] = atof(udaj);
                    udaj = strtok(NULL, ";");
                }
                break;
            default:
                break;
            }
            udaj = strtok(NULL, ";");
        }
    }
    fclose(subor);
}

int pocetMedzier(char retazec[]){ // TODO zmen na dynamicke pole?
    int medzera = 0;  
    for(size_t i = 0; i < strlen(retazec); i++){
        if(retazec[i]==' '){
            medzera++;
        }
    }
    return medzera;
}

void sum(jazdec* tabulka){
    for(int i=0; tabulka[i].meno != NULL; i++) { // TODO Remove
        printf("\nMENO: %s", tabulka[i].meno);
        printf("\nPRIEZVISKO: %s", tabulka[i].priezvisko);
        printf("\nPOHLAVIE: %c", tabulka[i].pohlavie);
        printf("\nROK: %d", tabulka[i].rok);
        printf("\nZNACKA: %s", tabulka[i].znacka);
        for (size_t j = 0; j < 5; j++){
            printf("\nCAS%d: %.3f", j, tabulka[i].casy[j]);
        }
        
    }
}