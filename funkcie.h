/*

--------------------------------------------------------------------------
|                                  Jazdci                                |
|                               Martin Szabo                             |
|                                  116304                                |
--------------------------------------------------------------------------

*/

// TODO Zmazať prebytočne printf("\n"); príkazy kde sa to môže

//*---------------------------------------------------- Preprocesor ---------------------------------------------------

// Program bol naprogramovaný v Visual Studio Code s GCC kompilátorom

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> // Umožňuje lepšie ošetrenie chýb v programe

// TODO definovat konstanty

//*----------------------------------------------------- Štruktúry ----------------------------------------------------

// Dátová štruktúra Jazdec
typedef struct jazdec{
    char* meno;
    char* priezvisko;
    char* znacka;
    char pohlavie;
    int rok;
    float casy[5];
}jazdec;

//*-------------------------------------------------- Pomocné funkcie -------------------------------------------------

// Funkcia na vytlačenie podpisu na obrazovku
void podpis(char const* zadanie, char const* meno, char const* aisID){

    // TODO Potiahnúť si array stringov, tie cyklicky vytlačiť na obrazovku rovnako ako tie 3 stringy predtým.
    // TODO Pridať popis

//*-------------------------------------------------- Dĺžka reťazca ---------------------------------------------------

    // Zistenie dĺžky reťazcov (vhodne keď nechcem použiť string.h knižnicu)
    size_t dlzkaZadania = 0, dlzkaMena = 0, dlzkaAisID = 0;
    if(zadanie){
        for (size_t i = 0; zadanie[i] != '\0'; i++){
            dlzkaZadania++;
        }
    }
    if(meno){
        for (size_t i = 0; meno[i] != '\0'; i++){
            dlzkaMena++;
        }
    }
    if(aisID){ 
        for (size_t i = 0; aisID[i] != '\0'; i++){
            dlzkaAisID++;
        }
    }

//*----------------------------------------------- Veľkosť ohraničenia ------------------------------------------------

    size_t velkostOhranicenia = 50 + dlzkaZadania + dlzkaMena + dlzkaAisID;
    if(velkostOhranicenia % 2 == 1){velkostOhranicenia++;}
    
    if(dlzkaZadania == 0 && dlzkaMena == 0 && dlzkaAisID == 0){
        printf("Nezadali ste ziadne udaje");
        return;
    }

//*--------------------------------------------------- Vrchný rám -----------------------------------------------------

    for (size_t i = 0; i < velkostOhranicenia; i++){
        printf("-");
    }
    printf("\n");
    
//*----------------------------------------------------- Zadanie ------------------------------------------------------

    if(zadanie && dlzkaZadania > 0){
        printf("|");
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaZadania - 1)/2; i++){
            printf(" "); // Do polovičky ohraničenia vypíšeme medzery...
        }
        printf("%s", zadanie); // ...Potom vypíšeme zadanie...
        if(dlzkaZadania % 2 == 1){dlzkaZadania++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaZadania - 1)/2; i++){
            printf(" "); // Následne dopíšeme zvyšné medzery...
        }
        // Na koniec zakončíme riadok
        printf("|\n");
    }

//*------------------------------------------------------- Meno -------------------------------------------------------

    if(meno && dlzkaMena > 0){
        printf("|");
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaMena - 1)/2; i++){
            printf(" ");
        }
        printf("%s", meno);
        if(dlzkaMena % 2 == 1){dlzkaMena++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaMena - 1)/2; i++){
            printf(" ");
        }
        printf("|\n");
    }

//*------------------------------------------------------ AIS ID ------------------------------------------------------

    if(aisID && dlzkaAisID > 0){
        printf("|");
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaAisID - 1)/2; i++){
            printf(" ");
        }
        printf("%s", aisID);
        if(dlzkaAisID % 2 == 1){dlzkaAisID++;}
        for (size_t i = 0; i < (velkostOhranicenia - dlzkaAisID - 1)/2; i++){
            printf(" ");
        }
        printf("|\n");
    }

//*---------------------------------------------------- Spodný rám ---------------------------------------------------

    for (size_t i = 0; i < velkostOhranicenia; i++){
        printf("-");
    }

    return;    
}

// Získa počet medzier v reťazci
int pocetMedzier(char* retazec){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si ukazovateľ "retazec" a premennú "medzera"
        3. Inicializujem premennú a ukazovateľ
            "retazec" -> na hodnotu reťazca ktorý budem kontrolovať
            "medzera" -> 0
        4. Prejdem celý reťazec znak po znaku až do konca reťazca
        5. Je znak medzera?
            TRUE: Tak prirátam k premennej medzera jednotku
            FALSE: Pokračujem ďalej
        6. Vrátim premennú medzera
        7. Stop
    */

//*----------------------------------------------------- Premenné -----------------------------------------------------

    int medzera = 0;  // Sledovanie počtu medzier v reťazci

//*--------------------------------------------- Kontrola znaku v reťazci ---------------------------------------------

    for(size_t i = 0; i < strlen(retazec); i++){
        if(retazec[i]==' '){
            medzera++;
        }
    }

    return medzera;
}

// Získa počet číslic v čísle
int pocetCislic(int cislo){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si premennú "pocet"
        3. Inicializujem premennú
            "pocet" -> 0
        4. Cyklom delím číslo desiatimi dokým nedostanem 0
        5. Vrátim počet otáčok cyklu
        6. Stop
    */

//*----------------------------------------------------- Premenné -----------------------------------------------------

    int pocet = 0;

//*----------------------------------------------- Počet číslic v čísle -----------------------------------------------

    do {
        cislo /= 10;
        pocet++;
    } while (cislo != 0);

    return pocet;
}

// Skontroluje či je reťazec čislo
int bJeCislo(char* retazec, int bFloat){

//*------------------------------------------------------ Postup ------------------------------------------------------

    // TODO Vylepšiť tak aby vedelo vyhodnotiť narp. 10,000 ako 10000

    /*
        1. Štart
        2. Zadeklarujem si ukazovateľ "retazec" a premenné "bFloat", "bodka"
        3. Inicializujem premenné a ukazovateľ
            "retazec" -> na hodnotu reťazca ktorý budem kontrolovať
            "bFloat" -> na hodnotu true (1) alebo false (0) podla toho či pracujem s celým alebo desatinným číslom
            "bodka" -> 0
        4. Prejdem celý reťazec znak po znaku až do konca reťazca
        5. Je znak bodka?
            TRUE: Pripočítam k premennej bodka jednotku a pokračujem ďalej
            FALSE: Pokračujem ďalej
        6. Je znak číslo?
            TRUE: Pokračujem ďalej
            FALSE: Vrátim hodnotu "false"
        7. Mám viacej ako jednu bodku v reťazci?
            TRUE: Vrátim hodnotu "false"
            FALSE: Pokračujem ďalej
        8. Mám bodku pri celom čísle?
            TRUE: Vrátim hodnotu "false"
            FALSE: Pokračujem ďalej
        9. Stop
    */

//*----------------------------------------------------- Premenné -----------------------------------------------------

    int bodka = 0; // Sledovanie počtu bodiek v reťazci

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    // bFloat slúži na kontrolu či pracujem s desatinným čislom 
    if(bFloat != 0 && bFloat != 1){ // Môže nadobúdať hodnotu "true" (1) alebo "false" (0)
        printf("\nNespravny typ cisla");
        getchar();
        exit(EXIT_FAILURE);
    }

//*------------------------------------- Kontrola či každý znak v reťazci je číslo ------------------------------------

    for (size_t i = 0; i < strlen(retazec); i++)
    {
        if(retazec[i] == '.'){ bodka++; } // Kontrolujem počet bodiek v reťazci
        if(
            (retazec[i] > '9' || retazec[i] < '0') // Pokiaľ znak reťazca nie je číslo...
            && (retazec[i] != '.' // ...a nie je ani bodka...
            || bodka > 1  // ...alebo mám viac ako 1 bodku...
            || (bFloat == 0 && bodka != 0)) // ...alebo mám bodku pri celom čísle...
        ){
            return 0; // ...tak false...
        }
        
    }

    return 1; // ...inak true
}

// Načítať jazdcov zo súboru do tabuľky (poľa) jazdcov
void nacitatJazdcov(jazdec** tabulka, size_t* velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si ukazovatele "tabulka", "velkost", "subor" a premennú "riadok"
        3. Inicializujem premenné a ukazovatele
            "subor" -> zatiaľ na prázdnu hodnotu
            "riadok" -> zatiaľ na prázdnu hodnotu
            "tabulka" -> zatiaľ na prázdnu hodnotu
            "velkosť" -> 0
        4. Alokujem si dynamické pole "tabulka"
        5. Otvorím si súbor pomocou ukazovateľa "subor"
        6. Čítam súbor riadok po riadku pričom...
            6.1. Prečítam riadok
            6.2 Mám dosť údajov v riadku?
                TRUE: Pokračujem ďalej
                FALSE: Skončím program
            6.3 Zväčším pomocou premennej "velkost" dynamické pole o jedného jazdca
            6.4. Rozseknem riadok podla bodkočiarky
            6.5. Mám správne zadefinované údaje v riadku?
                TRUE: Zapíšem údaje postupne do poľa "tabulka"
                FALSE: Skončím program
        7. Stop
    */

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
        strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
        printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno, chybovaHlaska);
        free(chybovaHlaska);
        getchar();
        exit(EXIT_FAILURE);
    }

    // Bezpečné otváranie súboru...
        // ..."fopen_s" vygeneruje error code a rovno ho porovná v podmienke...
        // ...Následne sa vypíše na obrazovku chybovú hlásku vygenerovanú podla error kódu
    if((fopen_s(&subor, "jazdci.csv", "r+")) != 0){
        char* chybovaHlaska = (char*)calloc(256, sizeof(char));
        strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
        printf("\nSubor nie je mozne precitat");
        printf("\nNemozno otvorit subor jazdci.csv\nChybovy kod %d -> %s", (int)errno, chybovaHlaska);
        free(chybovaHlaska);
        getchar();
        exit(EXIT_FAILURE);
    }

//*------------------------------------------------ Čítanie zo súboru -------------------------------------------------

    while(fgets(riadok, 100, subor)){
        
        //*---------------------------------------------- Inicializácia -----------------------------------------------
        
        (*velkost)++;
        char* dalsi = NULL;
        char* udaj = NULL;
        int pocetBodkociariek = 0;

        for (size_t i = 0; i < strlen(riadok); i++){
            if(riadok[i] == ';'){
                pocetBodkociariek++;
            }
        }
        if(pocetBodkociariek != 8){
            printf("\nSubor nie je mozne precitat");
            printf("\nChybaju udaje v riadku cislo %zu", (*velkost));
            getchar();
            exit(EXIT_FAILURE);
        }

        // Inicializujem dynamické polia a kontrolujem úspešnosť alokácie
        if(
            !((*tabulka) = (jazdec*)realloc((*tabulka),(*velkost) * sizeof(jazdec))) 
            || !(udaj = (char*)calloc(100,sizeof(char)))
            || !((*tabulka)[(*velkost)-1].meno = (char*) calloc(strlen(udaj), sizeof(char)))
            || !((*tabulka)[(*velkost)-1].priezvisko = (char*) calloc(strlen(udaj), sizeof(char)))
        ){
            char* chybovaHlaska = (char*)calloc(256, sizeof(char));
            strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
            printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno, chybovaHlaska);
            free(chybovaHlaska);
            getchar();
            exit(EXIT_FAILURE);
        }

        strcpy_s(udaj, 100, riadok);
        udaj = strtok_s(udaj, ";", &dalsi); // Strtok rozdelí reťazec na niekoľko častí oddelene ";"

        //*----------------------------------- Kontrola, či jazdec nemá stredné meno -----------------------------------

        if(pocetMedzier(udaj)>1){

            //*---------------------------------------------- Inicializácia --------------------------------------------
            
            char* posledny = NULL;
            if(!(posledny = (char*)calloc(100,sizeof(char)))){
                char* chybovaHlaska = (char*)calloc(256, sizeof(char));
                strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
                printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno, chybovaHlaska);
                free(chybovaHlaska);
                getchar();
                exit(EXIT_FAILURE);
            }

            udaj = strtok_s(udaj, " ", &dalsi);  // Rozseknem si údaj na menšie
            
            //*-------------------------------------- Rozdelenie mena a priezviska -------------------------------------
            
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

        //*---------------------------------------- Nahranie zvyšných údajov ---------------------------------------

        // ...nemusím uvoľňovať údaj lebo pri prechádzaní tokenov reťazca sa staré sami zmažú
        if(!(udaj = (char*)calloc(100,sizeof(char)))){ // TODO Cppcheck false positive...
            char* chybovaHlaska = (char*)calloc(256, sizeof(char));
            strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
            printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno, chybovaHlaska);
            free(chybovaHlaska);
            getchar();
            exit(EXIT_FAILURE);
        }
        strcpy_s(udaj, 100,riadok);
        udaj = strtok_s(udaj, ";", &dalsi);

        for (size_t i = 0; udaj != NULL; i++){
            switch (i){
            case 1:
                if(udaj [0] == 'm' || udaj [0] == 'f' || udaj [0] == 'z'){ (*tabulka)[(*velkost)-1].pohlavie = udaj[0]; }
                else{
                    printf("\nSubor nie je mozne precitat");
                    printf("\nChybne pohlavie pri jazdcovi cislo %zu: %s %s -> '%c'", (*velkost), (*tabulka)[(*velkost)-1].meno, (*tabulka)[(*velkost)-1].priezvisko, udaj[0]);
                    getchar();
                    exit(EXIT_FAILURE);
                }
                break;
            case 2:
                if(bJeCislo(udaj, 0) == 0){
                    printf("\nSubor nie je mozne precitat");
                    printf("\nChybny rok narodenia pri jazdcovi cislo %zu: %s %s -> '%s'", (*velkost), (*tabulka)[(*velkost)-1].meno, (*tabulka)[(*velkost)-1].priezvisko, udaj);
                    getchar();
                    exit(EXIT_FAILURE);
                }
                sscanf_s(udaj, "%d", &(*tabulka)[(*velkost)-1].rok, sizeof(int));
                if(pocetCislic((*tabulka)[(*velkost)-1].rok) != 4){
                    printf("\nSubor nie je mozne precitat");
                    printf("\nChybny rok narodenia pri jazdcovi cislo %zu: %s %s -> '%s'", (*velkost), (*tabulka)[(*velkost)-1].meno, (*tabulka)[(*velkost)-1].priezvisko, udaj);
                    getchar();
                    exit(EXIT_FAILURE);
                }
                break;
            case 3:
                if(!((*tabulka)[(*velkost)-1].znacka = (char*) calloc(strlen(udaj), sizeof(char)))){
                    char* chybovaHlaska = (char*)calloc(256, sizeof(char));
                    strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
                    printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno, chybovaHlaska);
                    free(chybovaHlaska);
                    getchar();
                    exit(EXIT_FAILURE);
                }
                strcpy_s((*tabulka)[(*velkost)-1].znacka, 100, udaj);
                break;
            case 4: case 5: case 6: case 7: case 8:
                for (size_t j = 0; udaj != NULL && j < 5; j++){
                    if(udaj[strlen(udaj) - 1] == '\n'){ // Odstránim "\n" z posledného času aby mohol zistiť či "udaj" číslo
                        udaj[strlen(udaj) - 1] = '\0'; // Nahradím "\n" znakom konca reťazca
                    }
                    if(bJeCislo(udaj, 1) == 0){ // Zistím či je "udaj" číslo
                        printf("\nSubor nie je mozne precitat");
                        printf("\nChybny cas pri jazdcovi cislo %zu: %s %s -> '%s'", (*velkost), (*tabulka)[(*velkost)-1].meno, (*tabulka)[(*velkost)-1].priezvisko, udaj);
                        getchar();
                        exit(EXIT_FAILURE);
                    }
                    sscanf_s(udaj, "%f", &(*tabulka)[(*velkost)-1].casy[j], sizeof(float));
                    udaj = strtok_s(NULL, ";", &dalsi);
                }
                break;
            default:
                break;
            }
            udaj = strtok_s(NULL, ";", &dalsi);
        }
    }

    if(fclose(subor) == EOF){
        printf("\nChyba pri zatvarani suboru");
    }
}

// Uvoľnenie poľa jazdcov
void uvolnenieJazdcov(jazdec** tabulka){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si ukazovateľ "tabulka"
        3. Existuje tabuľka?
            TRUE: Uvoľním dynamické pole "tabulka" a nastavím hodnotu ukazovateľa na prázdnu hodnotu
            FALSE: Skončím program
        4. Stop
    */

//*------------------------------------------------- Uvoľnenie pamäte -------------------------------------------------

    if(*tabulka){
        free(*tabulka);
        *tabulka = NULL;
    }
}

// Alokácia dvojrozmerného poľa
void alokovat2Dpole(char*** zoznam, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si ukazovateľ na dvojrozmerné pole "zoznam" a premennú "velkost"
        3. Alokujem dynamické pole "zoznam"?
        4. Cyklicky alokujem každé políčko dynamického poľa "zoznam"
        5. Stop
    */

//*-------------------------------------------------- Alokácia pamäte -------------------------------------------------

    if(!((*zoznam) = (char**)malloc(velkost * sizeof(char*)))){
        char* chybovaHlaska = (char*)calloc(256, sizeof(char));
        strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
        printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno, chybovaHlaska);
        free(chybovaHlaska);
        getchar();
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < velkost; i++){
        if(!((*zoznam)[i] = (char*)calloc(200, sizeof(char)))){
            char* chybovaHlaska = (char*)calloc(256, sizeof(char));
            strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
            printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno,chybovaHlaska);
            free(chybovaHlaska);
            getchar();
            exit(EXIT_FAILURE);
        }
    }
}

// Dealokácia dvojrozmerného poľa
void dealokovat2Dpole(char*** zoznam, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si ukazovateľ na dvojrozmerné pole "zoznam" a premennú "velkost"
        3. Existuje dvojrozmerné pole "zoznam"?
            TRUE: Tak...
                ...Cyklicky uvoľním každé políčko dynamického poľa "zoznam"...
                ...Potom uvoľním samotné dynamické pole "zoznam"...
                ...a nastavím hodnotu ukazovateľa "zoznam" na prázdnu hodnotu
            FALSE: Skončím program
        4. Stop
    */

//*------------------------------------------------- Uvoľnenie pamäte -------------------------------------------------

    if(*zoznam && **zoznam){
        for (size_t i = 0; i < velkost; i++){
            free((*zoznam)[i]);
        }
        free(*zoznam);
        *zoznam = NULL;
    }
}

//*-------------------------------------------------- Hlavné funkcie --------------------------------------------------

// Formátovaný výpis všetkých jazdcov
void sum(jazdec* tabulka, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Prejdem celé pole jazdcov
        3. Urobím formátovaný výpis každého jazdca
        4. Stop
    */

//*------------------------------------------------- Formátovaný výpis ------------------------------------------------

    if(!tabulka){
        printf("\nData zo suboru neboli nacitane");
        return;
    }
    printf("\n");
    for(size_t i = 0; i < velkost; i++){
        // Vo výpise automobilu kapitalizujem prvé písmenko značky
        printf("%s %s, nar. %d, %s, Automobil: %c%s\nCasy okruhov: ", tabulka[i].meno
        , tabulka[i].priezvisko, tabulka[i].rok, tabulka[i].pohlavie == 'm' ? "muz" : "zena"
        , (tabulka[i].znacka[0]-32),tabulka[i].znacka+1);

        //*------------------------------------------------ Výpis časov -----------------------------------------------
        
        size_t j = 0;
        for (j = 0; j < 5; j++){
            printf("%.3f", tabulka[i].casy[j]);
            if(j == 4){
                printf("\n");
            }
            else{
                printf(";");
            }
        }
    }
}

// Formátovaný výpis a štatistiky konkrétneho jazdca
void driver(jazdec* tabulka, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si ukazovateľ "priezviskoJazdca" a premennú "bUspech"
        3. Inicializujem premennú a ukazovateľ
            "priezviskoJazdca" -> zatiaľ na prázdnu hodnotu
            "bUspech" -> na hodnotu false (0)
        4. Alokujem dynamické pole "priezviskoJazdca"
        5. Načítam priezvisko z klávesnice do poľa "priezviskoJazdca"
        6. Prejdem celé pole jazdcov
        7. Podla priezviska vyhľadám jazdca
        8. Existuje jazdec?
            TRUE: Tak nastavím premennú "bUspech" na true (1) a urobím formátovaný výpis jazdca
            FALSE: Vypíšeme chybovú hlášku napr. "Jazdec nenajdeny"
        9. Stop
    */

//*----------------------------------------------------- Premenné -----------------------------------------------------

    char* priezviskoJazdca = NULL;
    int bUspech = 0;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    if(!tabulka){
        printf("\nData zo suboru neboli nacitane");
        return;
    }
    if(!(priezviskoJazdca = (char *)calloc(100, sizeof(char)))){
        char* chybovaHlaska = (char*)calloc(256, sizeof(char));
        strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
        printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno, chybovaHlaska);
        free(chybovaHlaska);
        getchar();
        exit(EXIT_FAILURE);
    }
    printf("\nZadajte priezvisko jazdca: ");
    scanf_s("%s", priezviskoJazdca, 100);
    getchar();

//*-------------------------------------------------- Hladanie jazdca -------------------------------------------------

    printf("\n");
    for(size_t i = 0; i < velkost; i++){
        if(strcmp(tabulka[i].priezvisko, priezviskoJazdca) == 0){ // TODO Pri parciálnom priezvisku dať návrh čo mohol používateľ myslieť?
            bUspech = 1;
            printf("%s %s\nnar. %d, %s\nAutomobil: %c%s\n\nCasy okruhov: ", tabulka[i].meno, tabulka[i].priezvisko
            , tabulka[i].rok, tabulka[i].pohlavie == 'm' ? "muz" : "zena", (tabulka[i].znacka[0]-32),tabulka[i].znacka+1);

            //*----------------------------------------------- Premenné -----------------------------------------------

            size_t j = 0;
            float najlepsiCas = tabulka[i].casy[0],  priemernyCas = 0.f, najhorsiCas = 0.f;

            //*---------------------------------------------- Výpis časov ---------------------------------------------

            for (j = 0; j < 5; j++){
                if(tabulka[i].casy[j] < najlepsiCas){
                    najlepsiCas = tabulka[i].casy[j];
                }
                if(tabulka[i].casy[j] > najhorsiCas){
                    najhorsiCas = tabulka[i].casy[j];
                }
                priemernyCas += tabulka[i].casy[j];

                printf("%.3f", tabulka[i].casy[j]);
                if(j == 4){
                    printf("\n");
                }
                else{
                    printf(";");
                }
            }

            priemernyCas /= j;
            printf("\nNajlepsie kolo: %.3f", najlepsiCas);
            printf("\nNajhorsie kolo: %.3f", najhorsiCas);
            printf("\nPriemerne kolo: %.3f", priemernyCas);
        }
    }

    if(bUspech != 1){
        printf("Jazdec nenajdeny");
    }

    free(priezviskoJazdca);
}

// Formátovaný výpis najlepšieho kola jazdcov
void lap(jazdec* tabulka, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si premenné "najlepsiCas", "indexJazdca" a "indexCasu"
        3. Inicializujem premennú
            "najlepsiCas" -> na hodnotu 0
            "indexJazdca" -> na hodnotu 0
            "indexCasu" -> na hodnotu 0
        4. Prejdem celé pole jazdcov pričom sledujem ich čas
        5. Nie je premenná "najlepsiCas" inicializovaná alebo je čas menší než môj uložený?
            TRUE: 
                Tak nastavím premennú "najlepsiCas" na aktuálny čas...
                ...nastavím premennú "indexJazdca" na aktuálny index jazdca
                ...a nastavím premennú "indexCasu" na aktuálny index čas
            FALSE: Pokračujem ďalej
        6. Urobím formátovaný výpis jazdca s najlepším časom pomocou indexov
        7. Stop
    */

//*----------------------------------------------------- Premenné -----------------------------------------------------

    float najlepsiCas = 0.f;
    int indexJazdca = 0, indexCasu = 0;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    if(!tabulka){
        printf("\nData zo suboru neboli nacitane");
        return;
    }

//*--------------------------------------------- Hľadanie najlepšieho času --------------------------------------------

    for(size_t i = 0; i < velkost; i++){
        for(size_t j = 0; j < 5; j++){
            if(najlepsiCas == 0.f || tabulka[i].casy[j] < najlepsiCas){
                najlepsiCas = tabulka[i].casy[j];
                indexJazdca = i;
                indexCasu = j;
            }
        }
    }
    printf("\nNajlepsie kolo: %.3f\nJazdec: %s %s\nCislo kola: %d", tabulka[indexJazdca].casy[indexCasu], tabulka[indexJazdca].meno, tabulka[indexJazdca].priezvisko, indexCasu+1);
}

// Formátovaný výpis najlepšieho kola z jazdcov daného pohlavia
void gender(jazdec* tabulka, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si premenné "najlepsiCas", "indexJazdca", "indexCasu" a "pohlavie"
        3. Inicializujem premennú
            "najlepsiCas" -> na hodnotu 0
            "indexJazdca" -> na hodnotu 0
            "indexCasu" -> na hodnotu 0
            "pohlavie" -> zatiaľ na prázdnu hodnotu
        4. Načítam pohlavie z klávesnice do premennej "pohlavie"
        5. Zadal používateľ správnu hodnotu?
            TRUE: Pokračujem ďalej
            FALSE: Skončím program
        6. Prejdem celé pole jazdcov pričom sledujem ich čas a pohlavie
        7. Nie je premenná "najlepsiCas" inicializovaná alebo je čas menší než môj uložený a zároveň...
        ...je pohlavie jazdca rovné premennej "pohlavie"?
            TRUE: 
                Tak nastavím premennú "najlepsiCas" na aktuálny čas...
                ...nastavím premennú "indexJazdca" na aktuálny index jazdca
                ...a nastavím premennú "indexCasu" na aktuálny index čas
            FALSE: Pokračujem ďalej
        8. Urobím formátovaný výpis jazdca s najlepším časom pomocou indexov
        9. Stop
    */

//*----------------------------------------------------- Premenné -----------------------------------------------------

    float najlepsiCas = 0.f;
    int indexJazdca = 0, indexCasu = 0;
    char pohlavie;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    printf("\nZadajte pohlavie jazdca (m/f): ");
    scanf_s("%c", &pohlavie, 1);
    getchar();

    if(!tabulka){
        printf("\nData zo suboru neboli nacitane");
        return;
    }

    if(pohlavie != 'm' && pohlavie != 'f'){
        printf("\nZadali ste nespravne pohlavie");
        return;
    }

//*--------------------------------------------- Hľadanie najlepšieho času --------------------------------------------

    for(size_t i = 0; i < velkost; i++){
        for(size_t j = 0; j < 5; j++){
            if((najlepsiCas == 0.f || tabulka[i].casy[j] < najlepsiCas) && tabulka[i].pohlavie == pohlavie){
                najlepsiCas = tabulka[i].casy[j];
                indexJazdca = i;
                indexCasu = j;
            }
        }
    }
    printf("\nNajlepsie kolo: %.3f\nJazdec: %s %s\nCislo kola: %d", tabulka[indexJazdca].casy[indexCasu], tabulka[indexJazdca].meno, tabulka[indexJazdca].priezvisko, indexCasu+1);
}

// Formátovaný výpis najlepšieho kola pre jednotlivé značky aut
void brand(jazdec* tabulka, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si premenné "indexJazdca", "indexCasu", "vybaveneIndex", "najlepsiCas", "bVypis"...
        ...a dvojitý ukazovateľ "vybaveneZnacky"
        3. Inicializujem premennú
            "indexJazdca" -> na hodnotu 0
            "indexCasu" -> na hodnotu 0
            "vybaveneIndex" -> na hodnotu 0
            "najlepsiCas" -> na hodnotu 0
            "bVypis" -> na hodnotu true (1)
            "vybaveneZnacky" -> zatiaľ na prázdnu hodnotu
        4. Alokujem dvojrozmerné dynamické pole
        5. Cyklom prejdem celé pole jazdcov pričom sledujem ich značku
        6. V cykle prejdem ďalším cyklom celé pole jazdcov pričom sledujem ich čas
        7. Je čas menší než môj uložený a zároveň je značka rovná aktuálnej značke?
            TRUE: 
                Tak nastavím premennú "najlepsiCas" na aktuálny čas...
                ...nastavím premennú "indexJazdca" na aktuálny index jazdca
                ...a nastavím premennú "indexCasu" na aktuálny index čas
            FALSE: Pokračujem ďalej
        8. Prejdem celé pole "vybaveneZnacky"
        9. Je značka v zozname vybavených značiek?
            TRUE: Pokračujem ďalej
            FALSE: Tak...
                ...Urobím formátovaný výpis jazdca s najlepším časom pomocou indexov...
                ...uložím si jeho značku do poľa "vybaveneZnacky"...
                ...pripočítam k premennej "vybaveneIndex" jednotku
        10. Stop
    */

//*----------------------------------------------------- Premenné -----------------------------------------------------

    int indexJazdca = 0, indexCasu = 0, vybaveneIndex = 0;
    char** vybaveneZnacky = NULL;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    if(!tabulka){
        printf("\nData zo suboru neboli nacitane");
        return;
    }

    alokovat2Dpole(&vybaveneZnacky, velkost);

//*--------------------------------------------- Hľadanie najlepšieho času --------------------------------------------

    for (size_t x = 0; x < velkost; x++){ // Prejde pole jazdcov pričom sledujem ich značku

        //*------------------------------------------------- Premenné -------------------------------------------------

        float najlepsiCas = 0.f;
        int bVypis = 1;

        //*--------------------------------------- Prejdenie každého času jazdca --------------------------------------

        for(size_t i = 0; i < velkost; i++){
            for(size_t j = 0; j < 5; j++){
                if((najlepsiCas == 0.f || tabulka[i].casy[j] < najlepsiCas)
                && strcmp(tabulka[i].znacka, tabulka[x].znacka) == 0){
                    najlepsiCas = tabulka[i].casy[j];
                    indexJazdca = i;
                    indexCasu = j;
                }
            }
        }

        //*--------------------------------- Kontrola či som údaje značky už nevypísal --------------------------------

        for (size_t k = 0; k < velkost; k++){
            if(strcmp(tabulka[indexJazdca].znacka, vybaveneZnacky[k]) == 0){
                bVypis = 0;
            }
        }

        //*-------------------------------------------- Vypís údajov značky -------------------------------------------

        if(bVypis == 1){
            printf("\nZnacka: %c%s\nNajlepsie kolo: %.3f\nJazdec: %s %s\nCislo kola: %d", (tabulka[indexJazdca].znacka[0]-32)
            ,tabulka[indexJazdca].znacka+1, tabulka[indexJazdca].casy[indexCasu], tabulka[indexJazdca].meno
            , tabulka[indexJazdca].priezvisko, indexCasu+1);
            strcpy_s(vybaveneZnacky[vybaveneIndex], strlen(tabulka[indexJazdca].znacka)+1, tabulka[indexJazdca].znacka);
            vybaveneIndex++;
            if(x < velkost-2){ // -2 preto lebo "velkost" je indexová hodnota a potrebujem o výpis pred posledným
                printf("\n");
            }
        }
    }

    dealokovat2Dpole(&vybaveneZnacky, velkost);
}

// Formátovaný výpis najlepšieho kola z jazdcov narodených pred určitým rokom
void year(jazdec* tabulka, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*  
        1. Štart
        2. Zadeklarujem si premenné "najlepsiCas", "indexJazdca", "indexCasu" a "rok"
        3. Inicializujem premenné
            "najlepsiCas" -> na hodnotu 0
            "indexJazdca" -> na hodnotu 0
            "indexCasu" -> na hodnotu 0
            "rok" -> na hodnotu 0
        4. Načítam rok z klávesnice do premennej "rok"
        5. Zadal používateľ správnu hodnotu?
            TRUE: Pokračujem ďalej
            FALSE: Skončím program
        6. Prejdem celé pole jazdcov pričom sledujem ich čas a rok narodenia
        7. Nie je premenná "najlepsiCas" inicializovaná alebo je čas menší než môj uložený a zároveň...
        ...je rok jazdca menší ako premenná "rok"?
            TRUE: Tak...
                ...nastavím premennú "najlepsiCas" na aktuálny čas...
                ...nastavím premennú "indexJazdca" na aktuálny index jazdca
                ...a nastavím premennú "indexCasu" na aktuálny index čas
            FALSE: Pokračujem ďalej
        8. Urobím formátovaný výpis jazdca s najlepším časom pomocou indexov
        9. Stop 
    */

//*----------------------------------------------------- Premenné -----------------------------------------------------

    float najlepsiCas = 0.f;
    int indexJazdca = 0, indexCasu = 0, rok = 0;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    printf("\nZadajte rok narodenia jazdca: ");
    scanf_s("%d", &rok, 4);
    getchar();

    if(!tabulka){
        printf("\nData zo suboru neboli nacitane");
        return;
    }

    if(pocetCislic(rok) != 4){
        printf("\nZadali ste nespravny rok");
        return;
    }

//*--------------------------------------------- Hľadanie najlepšieho času --------------------------------------------

    for(size_t i = 0; i < velkost; i++){
        for(size_t j = 0; j < 5; j++){
            if((najlepsiCas == 0.f || tabulka[i].casy[j] < najlepsiCas) && tabulka[i].rok < rok){
                najlepsiCas = tabulka[i].casy[j];
                indexJazdca = i;
                indexCasu = j;
            }
        }
    }
    if(najlepsiCas != 0.f){
        printf("\nNajlepsie kolo: %.3f\nJazdec: %s %s\nCislo kola: %d", tabulka[indexJazdca].casy[indexCasu], tabulka[indexJazdca].meno, tabulka[indexJazdca].priezvisko, indexCasu+1);
    }
    else{
        printf("\nJazdec nenajdeny");
    }
}

// Formátovaný výpis priemerných kôl jazdcov a najlepšieho priemerného kola z jazdcov
void average(jazdec* tabulka, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*
        1. Štart
        2. Zadeklarujem si premenne "najlepsiPriemer", "najlepsiPriemerIndex", "j", "priemernyCas"
        3. Inicializujem premennú a ukazovateľ
            "najlepsiPriemer" -> na hodnotu 0
            "najlepsiPriemerIndex" -> na hodnotu 0
            "j" -> na hodnotu 0
            "priemernyCas" -> na hodnotu 0
        4. Prejdem celé pole jazdcov
        5. Cyklicky sčítam všetky časy jazdca
        6. Vydelím ich počtom otáčok cyklu "j"
        7. Nie je premenná "najlepsiPriemer" inicializovaná alebo je "priemernyCas" menší než "najlepsiPriemer"?
            TRUE: Tak...
                ...nastavím premennú "najlepsiPriemer" na hodnotu premennej "priemernyCas"...
                ...a nastavím premennú "najlepsiPriemerIndex" na hodnotu indexu aktuálneho jazdca
            FALSE: Pokračujem ďalej
        8. Urobím formátovaný výpis všetkých priemerných časov jazdcov
        9. Urobím formátovaný výpis najlepšieho priemerného času zo všetkých jazdcov
        10. Stop
    */

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    if(!tabulka){
        printf("\nData zo suboru neboli nacitane");
        return;
    }

//*-------------------------------------------------- Hladanie jazdca -------------------------------------------------

    float najlepsiPriemer = 0.f;
    int najlepsiPriemerIndex = 0;
    for(size_t i = 0; i < velkost; i++){
        
        //*----------------------------------------------- Premenné -----------------------------------------------

        size_t j = 0;
        float priemernyCas = 0.f;

        //*----------------------------------- Zistenie a výpis priemerného času ----------------------------------

        for (j = 0; j < 5; j++){
            priemernyCas += tabulka[i].casy[j];
        }

        priemernyCas /= j;
        if(najlepsiPriemer == 0.f || priemernyCas < najlepsiPriemer){
            najlepsiPriemer = priemernyCas;
            najlepsiPriemerIndex = i;
        }
        printf("\n%s %s - %.3f", tabulka[i].meno, tabulka[i].priezvisko, priemernyCas);
    }
    printf("\n\nNajlepsie:\n%s %s - %.3f", tabulka[najlepsiPriemerIndex].meno, tabulka[najlepsiPriemerIndex].priezvisko, najlepsiPriemer);
}

// Formátovaný výpis počtu a časov kôl jazdcov ktoré odjazdili do určitého času
void under(jazdec* tabulka, size_t velkost){

//*------------------------------------------------------ Postup ------------------------------------------------------

    /*  
        1. Štart
        2. Zadeklarujem si premenné "pocetKol", "cas"
        3. Inicializujem premenné
            "pocetKol" -> na hodnotu 0
            "cas" -> na hodnotu 0
        4. Načítam čas z klávesnice do premennej "cas"
        5. Prejdem celé pole jazdcov pričom sledujem ich čas
        6. Je čas menší alebo rovný môju uloženému času
            TRUE: Tak spravím formatovany výpis časov
            FALSE: Pokračujem ďalej
        7. Stop 
    */

//*----------------------------------------------------- Premenné -----------------------------------------------------

    float cas = 0.f;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    printf("\nZadajte cas: ");
    scanf_s("%f", &cas, 5);
    getchar();

    if(!tabulka){
        printf("\nData zo suboru neboli nacitane");
        return;
    }

//*--------------------------------------------------- Výpis časov ----------------------------------------------------

    printf("\n");
    for(size_t i = 0; i < velkost; i++){

        //*------------------------------------------------- Premenné -------------------------------------------------

        int pocetKol = 0;

        //*------------------------------------------------ Výpis časov -----------------------------------------------

        for(size_t j = 0; j < 5; j++){ // Zistí počet kôl jazdcov pod určitým časom
            if(tabulka[i].casy[j] <= cas){
                pocetKol++;
            }
        }
        if(pocetKol != 0){ // Pokiaľ máme kolá pod určitým časom
            printf("%s %s - %d kola", tabulka[i].meno, tabulka[i].priezvisko, pocetKol);
            for(size_t j = 0; j < 5; j++){
                if(tabulka[i].casy[j] <= cas){
                    printf(", %zu (%.3f)", j+1, tabulka[i].casy[j]);
                }
            }
            if(i < velkost-1){
                printf("\n");
            }
        }
    }
}

void change(jazdec** tabulka, size_t velkost){
    
//*------------------------------------------------------ Postup ------------------------------------------------------

    // Buď budeš fseekovať a priamo meniť v súbore
    // Alebo môžeš zmeniť údaje v poli a potom ho celé printnúť do súboru
    // Tretia možnosť je printnúť iba zmenený údaj na dánú pozíciu v súbore (ale to bude asi hard)

//*----------------------------------------------------- Premenné -----------------------------------------------------

    char* priezviskoJazdca = NULL;
    int poradoveCislo = 0;
    float novyCas = 0;	
    int bUspech = 0;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    if(!(*tabulka)){
        printf("\nData zo suboru neboli nacitane");
        return;
    }
    if(!(priezviskoJazdca = (char *)calloc(100, sizeof(char)))){
        char* chybovaHlaska = (char*)calloc(256, sizeof(char));
        strerror_s(chybovaHlaska, 256, (int)errno); // Konvertujem error kód na hlášku
        printf("\nNemozno alokovat pamat\nChybovy kod %d -> %s", (int)errno, chybovaHlaska);
        free(chybovaHlaska);
        getchar();
        exit(EXIT_FAILURE);
    }
    printf("\nZadajte priezvisko jazdca: ");
    scanf_s("%s", priezviskoJazdca, 100);
    getchar();
    
    printf("Zadajte poradove cislo kola: ");
    scanf_s("%d", &poradoveCislo, 1);
    getchar();

    printf("Zadajte novy cas: ");
    scanf_s("%f", &novyCas, 1);
    getchar();

//*-------------------------------------------------- Hladanie jazdca -------------------------------------------------

    printf("\n");
    for(size_t i = 0; i < velkost; i++){
        if(strcmp((*tabulka)[i].priezvisko, priezviskoJazdca) == 0){ // TODO Pri parciálnom priezvisku dať návrh čo mohol používateľ myslieť?
            bUspech = 1;
            (*tabulka)[i].casy[poradoveCislo-1] = novyCas;
        }
    }

    if(bUspech != 1){
        printf("Jazdec nenajdeny");
    }

    free(priezviskoJazdca);
}

void newdriver(){
    // Buď budeš fseekovať a priamo meniť v súbore
    // Alebo môžeš zmeniť údaje v poli a potom ho celé printnúť do súboru
    // Tretia možnosť je printnúť iba zmenený údaj na dánú pozíciu v súbore (ale to bude asi hard)
}
void rmdriver(){
    // Buď budeš fseekovať a priamo meniť v súbore
    // Alebo môžeš zmeniť údaje v poli a potom ho celé printnúť do súboru
    // Tretia možnosť je printnúť iba zmenený údaj na dánú pozíciu v súbore (ale to bude asi hard)
}