/*

--------------------------------------------------------------------------
|                                  Jazdci                                |
|                               Martin Szabo                             |
|                                  116304                                |
--------------------------------------------------------------------------

*/

//*---------------------------------------------------- Preprocesor ---------------------------------------------------

// Program bol naprogramovaný v Visual Studio Code s GCC kompilátorom

// !Vypne scanf depricated warning pre GCC kompilátor
// TODO Remove?
//#define _CRT_SECURE_NO_DEPRECATE
// !Vypne scanf depricated warning pre MSVC kompilátor
// TODO Remove?
//#pragma warning(disable : 4996) //? Odkomentovat v pripade potreby

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//*----------------------------------------------------- Štruktúry ----------------------------------------------------

typedef struct jazdec{
    char* meno;
    char* priezvisko;
    char* znacka;
    char pohlavie;
    int rok;
    float casy[5];
}jazdec;

//*-------------------------------------------------- Pomocné funkcie -------------------------------------------------

void nacitatJazdcov(jazdec** tabulka, size_t* velkost);
int pocetMedzier(char* retazec); // Získa počet medzier v reťazci

//*-------------------------------------------------- Hlavné funkcie --------------------------------------------------

void podpis(char const* zadanie, char const* meno, char const* aisID);
void sum(jazdec* tabulka, size_t velkost);

int main() {

//*----------------------------------------------------- Premenné -----------------------------------------------------

    char vyber;
    size_t velkost = 0;
    jazdec* tabulka = NULL;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    podpis("Jazdci", "Martin Szabo", "116304");
    nacitatJazdcov(&tabulka, &velkost);

//*------------------------------------------------------- Menu -------------------------------------------------------

    do {
        //TODO oramovať menu (pripadne spraviť reusable funkciu pre menu)
        printf("\n\ns - Sum\nd - Driver\nl - Lap\ng - Gender\nb - Brand\ny - Year\na - Average\nu - Under\nc - Change\nn - New Driver\nr - Remove Driver\nr - Reload\ne - Exit");
        printf("\nVolba: ");
        scanf_s("%c", &vyber, 1);
        getchar(); // Odstráni medzeru od scanfu na konci buffera
        switch (vyber) {
            case 's':
                sum(tabulka, velkost);
                break;
            case 'r':
                nacitatJazdcov(&tabulka, &velkost);
                break;
            case 'e':
                free(tabulka);
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
            printf(" "); // Do polovičky ohraničenia vypíšeme medzery...
        }
        printf("%s", zadanie); // ...Potom vypíšeme zadanie...
        if(dlzkaZadania % 2 == 1) {dlzkaZadania++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaZadania - 1)/2; i++) {
            printf(" "); // Následne dopíšeme zvyšné medzery...
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

    // Spodný rám
    for (size_t i = 0; i < velkostOhranicenia; i++) {
        printf("-");
    }
    return;    
}

void nacitatJazdcov(jazdec** tabulka, size_t* velkost){
    
//*----------------------------------------------------- Premenné -----------------------------------------------------

    FILE* subor;
    char riadok[100];
    // Veľkosť tabuľky je nutné ukladať do premennej lebo nie je známa počas kompilácie.
    // vytváram ju v maine a robím pass by reference aby som s ňou vedel pracovať aj v ďalších funkciách
    (*velkost) = 0;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    if((*tabulka)!=NULL){ free((*tabulka)); }
    // TODO ? fix garbage na konci pola ?

    // Inicializujem dynamické pole jazdcov, kontrolujem úspešnosť alokácie a otvorenie súboru
    if(!((*tabulka) = (jazdec*)malloc((*velkost) * sizeof(jazdec)))){
        char* chybovaHlaska = (char*)calloc(256, sizeof(char));
        strerror_s(chybovaHlaska,256,(int)errno); // Konvertujem error kód na hlášku
        printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno,chybovaHlaska);
        free(chybovaHlaska);
        exit(EXIT_FAILURE);
    }

    // Bezpečné otváranie súboru...
        // ..."fopen_s" vygeneruje error code a rovno ho porovná v podmienke...
        // ...Následne sa vypíše na obrazovku chybovú hlásku vygenerovanú podla error kódu
    if((fopen_s(&subor, "jazdci.csv", "r+")) != 0){
        char* chybovaHlaska = (char*)calloc(256, sizeof(char));
        strerror_s(chybovaHlaska,256,(int)errno); // Konvertujem error kód na hlášku
        printf("\nNemozno otvorit subor jazdci.csv\nChybovy kod %d -> %s", (int)errno,chybovaHlaska);
        free(chybovaHlaska);
        exit(EXIT_FAILURE);
    }

//*------------------------------------------------ Čítanie zo súboru -------------------------------------------------

    while(fgets(riadok, 100, subor)){

        //*---------------------------------------------- Inicializácia -----------------------------------------------
        
        (*velkost)++;
        char* dalsi = NULL;
        char* udaj = NULL;
        

        // Inicializujem dynamické polia a kontrolujem úspešnosť alokácie
        if(
            !((*tabulka) = (jazdec*)realloc((*tabulka),(*velkost) * sizeof(jazdec))) 
            || !(udaj = (char*)calloc(100,sizeof(char)))
            || !((*tabulka)[(*velkost)-1].meno = (char*) calloc(strlen(udaj), sizeof(char)))
            || !((*tabulka)[(*velkost)-1].priezvisko = (char*) calloc(strlen(udaj), sizeof(char)))
        ){
            char* chybovaHlaska = (char*)calloc(256, sizeof(char));
            strerror_s(chybovaHlaska,256,(int)errno); // Konvertujem error kód na hlášku
            printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno,chybovaHlaska);
            free(chybovaHlaska);
            exit(EXIT_FAILURE);
        }

        strcpy_s(udaj, 100, riadok);
        udaj = strtok_s(udaj, ";", &dalsi); // Strtok rozdelí reťazec na niekoľko častí oddelene ";"

        //*------------------------------------  Kontrola, či jazdec nemá stredné meno ---------------------------------

        if(pocetMedzier(udaj)>1){

            //*---------------------------------------------- Inicializácia --------------------------------------------
            
            char* posledny = NULL;
            if(!(posledny = (char*)calloc(100,sizeof(char)))){
                char* chybovaHlaska = (char*)calloc(256, sizeof(char));
                strerror_s(chybovaHlaska,256,(int)errno); // Konvertujem error kód na hlášku
                printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno,chybovaHlaska);
                free(chybovaHlaska);
                exit(EXIT_FAILURE);
            }

            udaj = strtok_s(udaj, " ", &dalsi);  // Rozseknem si údaj na menšie
            
            //*--------------------------------------- Rozdelenie mena a priezviska ------------------------------------
            
            for (size_t i = 0; udaj != NULL; i++){
                // Spravím si kópiu aktuálneho údaja
                posledny = udaj;

                // Skontrolujem či existuje ďalší
                udaj = strtok_s(NULL, " ", &dalsi); // Strtok s argumentom NULL nám bude pokračovať v tokenizácií reťazca.

                // Pokiaľ ďalší nebude existovať tak sme na poslednom, tak sa if nevykoná a rovno vyskočíme von z cyklu...
                if(udaj != NULL){ 
                    if(i == 0){
                        // Pre prvú otáčku nerobíme medzeru a kopírujeme prvý token...
                        strcpy_s((*tabulka)[(*velkost)-1].meno, 100, posledny);
                        continue;
                    }
                    // ...inak pripájame token na koniec stringu
                    strcat_s((*tabulka)[(*velkost)-1].meno, 100, " ");
                    strcat_s((*tabulka)[(*velkost)-1].meno, 100, posledny);
                }
            }

            // ...keďže sme vyskočil von z cyklu keď sa ďalší údaj rovná NULL tak posledný údaj uložím do priezviska
            strcpy_s((*tabulka)[(*velkost)-1].priezvisko, 100, posledny);
        }
        else{
            udaj = strtok_s(udaj, " ", &dalsi);
            strcpy_s((*tabulka)[(*velkost)-1].meno, 100, udaj);
            udaj = strtok_s(NULL, ";", &dalsi);
            strcpy_s((*tabulka)[(*velkost)-1].priezvisko, 100, udaj);
            udaj = strtok_s(NULL, ";", &dalsi);
        }
        
        //*----------------------------------------  Nahranie zvyšných údajov -----------------------------------------

        // ...nemusím uvoľňovať údaj lebo pri prechádzaní tokenov reťazca sa staré sami zmažú
        if(!(udaj = (char*)calloc(100,sizeof(char)))){ // TODO Cppcheck false positive...
            char* chybovaHlaska = (char*)calloc(256, sizeof(char));
            strerror_s(chybovaHlaska,256,(int)errno); // Konvertujem error kód na hlášku
            printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno,chybovaHlaska);
            free(chybovaHlaska);
            exit(EXIT_FAILURE);
        }
        strcpy_s(udaj, 100,riadok);
        udaj = strtok_s(udaj, ";", &dalsi);

        for (size_t i = 0; udaj != NULL; i++){
            switch (i) {
            case 1:
                (*tabulka)[(*velkost)-1].pohlavie = udaj[0];
                break;
            case 2:
                (*tabulka)[(*velkost)-1].rok = strtol(udaj, NULL, 0); // Tretí argument je typ číselnej sústavy 0 = automaticky
                break;
            case 3:
                if(!((*tabulka)[(*velkost)-1].znacka = (char*) calloc(strlen(udaj), sizeof(char)))){
                    char* chybovaHlaska = (char*)calloc(256, sizeof(char));
                    strerror_s(chybovaHlaska,256,(int)errno); // Konvertujem error kód na hlášku
                    printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno,chybovaHlaska);
                    free(chybovaHlaska);
                    exit(EXIT_FAILURE);
                }
                strcpy_s((*tabulka)[(*velkost)-1].znacka, 100, udaj);
                break;
            case 4: case 5: case 6: case 7: case 8:
                for (size_t j = 0; udaj != NULL && j < 5; j++){
                    (*tabulka)[(*velkost)-1].casy[j] = strtod(udaj, NULL);
                    udaj = strtok_s(NULL, ";", &dalsi);
                }
                break;
            default:
                break;
            }
            udaj = strtok_s(NULL, ";", &dalsi);
        }
    }
    fclose(subor);
}

int pocetMedzier(char* retazec){
    int medzera = 0;  
    for(size_t i = 0; i < strlen(retazec); i++){
        if(retazec[i]==' '){
            medzera++;
        }
    }
    return medzera;
}

void sum(jazdec* tabulka, size_t velkost){
    for(size_t i=0; i < velkost; i++) { // TODO Remove
        printf("\nMENO: %s", tabulka[i].meno);
        printf("\nPRIEZVISKO: %s", tabulka[i].priezvisko);
        printf("\nPOHLAVIE: %c", tabulka[i].pohlavie);
        printf("\nROK: %d", tabulka[i].rok);
        printf("\nZNACKA: %s", tabulka[i].znacka);
        for (int j = 0; j < 5; j++){
            printf("\nCAS%d: %.3f", j, tabulka[i].casy[j]);
        }
        
    }
}