/*

--------------------------------------------------------------------------
|                                  Jazdci                                |
|                               Martin Szabo                             |
|                                  116304                                |
--------------------------------------------------------------------------

*/

//---------------------------------------------------- Preprocesor ---------------------------------------------------

// Program bol naprogramovany v Visual Studio Code s GCC kompilatorom

// !Vypne scanf depricated warning pre GCC kompilator
#define _CRT_SECURE_NO_DEPRECATE
// !Vypne scanf depricated warning pre MSVC kompilator
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//----------------------------------------------------- Štruktúry ----------------------------------------------------

typedef struct jazdec{
    char *meno;
    char *priezvisko;
    char *znacka;
    char pohlavie;
    int rok;
    float casy[5];
}jazdec;

//-------------------------------------------------- Pomocné funkcie -------------------------------------------------

void nacitatJazdcov(jazdec ** tabulka);
int pocetMedzier(char retazec[]); // Ziska pocet medzier v retazci

//-------------------------------------------------- Hlavné funkcie --------------------------------------------------

void podpis(char const* zadanie, char const* meno, char const* aisID);
void sum();


int main() {

//----------------------------------------------------- Premenné -----------------------------------------------------

    char vyber;
    jazdec * tabulka = NULL;

//-------------------------------------------------- Inicializácia ---------------------------------------------------

    podpis("Jazdci", "Martin Szabo", "116304");
    nacitatJazdcov(&tabulka);

    for(int i=0; tabulka[i].meno != NULL; i++) { // TODO Remove
        printf("\nMENO: %s", tabulka[i].meno);
        printf("\nPRIEZVISKO: %s", tabulka[i].priezvisko);
    }

//------------------------------------------------------- Menu -------------------------------------------------------

    do {
        printf("\n\ne - Exit\ns - Sum\nd - Driver\nl - Lap\ng - Gender\nb - Brand\ny - Year\na - Average\nu - Under\nc - Change\nn - New Driver\nr - Remove Driver");
        printf("\nVolba: ");
        scanf("%c", &vyber);
        getchar(); // Odstrani medzeru od scanfu na konci buffera
        switch (vyber) {
            case 's':
                sum();
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

//-------------------------------------------------- Dĺžka reťazca ---------------------------------------------------

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

//----------------------------------------------- Veľkosť ohraničenia ------------------------------------------------

    size_t velkostOhranicenia = 50 + dlzkaZadania + dlzkaMena + dlzkaAisID;
    if(velkostOhranicenia % 2 == 1) {velkostOhranicenia++;}
    
    if(dlzkaZadania == 0 && dlzkaMena == 0 && dlzkaAisID == 0) {
        printf("Nezadali ste ziadne udaje");
        return;
    }

//--------------------------------------------------- Vrchný rám -----------------------------------------------------

    for (size_t i = 0; i < velkostOhranicenia; i++) {
        printf("-");
    }
    printf("\n");
    
//----------------------------------------------------- Zadanie ------------------------------------------------------

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

//------------------------------------------------------- Meno -------------------------------------------------------

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
    
//----------------------------------------------------- Premenné -----------------------------------------------------

    FILE* subor;
    char riadok[100];
    size_t velkost = 0;

//-------------------------------------------------- Inicializácia ---------------------------------------------------

    // TODO ? fix garbage na konci pola ?
    (*tabulka) = (jazdec*)malloc(velkost * sizeof(jazdec)); // Inicializujem dynamicke pole jazdcov 
    
    if(!(subor = fopen("jazdci.csv", "r+"))){
        printf("Error: %d", errno);
        exit(EXIT_FAILURE);
    }

//------------------------------------------------ Čítanie zo súboru -------------------------------------------------

    while(fgets(riadok, 100, subor)){
        velkost++;
        (*tabulka) = (jazdec*)realloc((*tabulka),velkost * sizeof(jazdec));
        
        
        char *udaj = strtok(riadok, ";"); // Strtok rozdeli reťazec na niekolko častí oddelene ";".

        char kopia[100];
        strcpy(kopia, udaj);

        // Kontrola ci nema jazdec stredne meno
        if(pocetMedzier(kopia)>1){

            udaj = strtok(riadok, " ");  // Rozseknem si meno na mensie

            for (size_t i = 0; udaj != NULL; i++) { 
                // Iterujem tak ze prve dve casti dam pod meno...
                if(i < 1){
                    (*tabulka)[velkost-1].meno = (char*) calloc(strlen(udaj), sizeof(char)); 
                    strcpy((*tabulka)[velkost-1].meno, udaj);
                }
                else if(i < 2){
                    strcat((*tabulka)[velkost-1].meno, " ");
                    strcat((*tabulka)[velkost-1].meno, udaj);
                }
                // ...zvysok ide pod priezvisko
                else{
                    (*tabulka)[velkost-1].priezvisko = (char*) calloc(strlen(udaj), sizeof(char)); 
                    strcpy((*tabulka)[velkost-1].priezvisko, udaj);
                }
                udaj = strtok(NULL, " "); // Strtok s argumentom NULL nám bude pokračovať v tokenizácií reťazca.
            }
        }
        else{
            (*tabulka)[velkost-1].meno = (char*) calloc(strlen(udaj), sizeof(char));
            (*tabulka)[velkost-1].priezvisko = (char*) calloc(strlen(udaj), sizeof(char));
            udaj = strtok(riadok, " ");
            strcpy((*tabulka)[velkost-1].meno, udaj);
            udaj = strtok(NULL, ";");
            strcpy((*tabulka)[velkost-1].priezvisko, udaj);

        }

        for (size_t i = 0; udaj != NULL; i++) {

            // TODO nahrať dalšie údaje do pola jazdcov
            //printf("%s\n", udaj);
            udaj = strtok(NULL, ";");
        }
    }

    fclose(subor);
}

int pocetMedzier(char retazec[]){
    int medzera = 0;  
    for(size_t i = 0; i < strlen(retazec); i++){
        if(retazec[i]==' '){
            medzera++;
        }
    }
    return medzera;
}

void sum(){
    
}