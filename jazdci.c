/*

--------------------------------------------------------------------------
|                                  Jazdci                                |
|                               Martin Szabo                             |
|                                  116304                                |
--------------------------------------------------------------------------

*/

//*---------------------------------------------------- Preprocesor ---------------------------------------------------

// Program bol naprogramovaný v Visual Studio Code s GCC kompilátorom

#include <stdio.h>
#include "funkcie.h"

int main(){

//*----------------------------------------------------- Premenné -----------------------------------------------------

    char vyber;
    size_t velkost = 0;
    jazdec* tabulka = NULL;

//*-------------------------------------------------- Inicializácia ---------------------------------------------------

    podpis("Jazdci", "Martin Szabo", "116304");
    nacitatJazdcov(&tabulka, &velkost);

//*------------------------------------------------------- Menu -------------------------------------------------------

    do{

        //*----------------------------------------------- Inicializácia ----------------------------------------------
        
        printf("\n\n-------------------------------------");
        printf("\n\t\t\t\t    |");
        if(velkost == 0){
            printf("\nn - New Driver\t\t\t    |");
        }
        else{
            printf("\ns - Sum\t\t\t\t    |");
            printf("\nd - Driver\t\t\t    |");
            printf("\nl - Lap\t\t\t\t    |");
            printf("\ng - Gender\t\t\t    |");
            printf("\nb - Brand\t\t\t    |");
            printf("\ny - Year\t\t\t    |");
            printf("\na - Average\t\t\t    |");
            printf("\nu - Under\t\t\t    |");
            printf("\nc - Change\t\t\t    |");
            printf("\nn - New Driver\t\t\t    |");
            printf("\nr - Remove Driver\t\t    |");
        }
        printf("\nq - Reload\t\t\t    |");
        printf("\nx - Exit\t\t\t    |");
        printf("\n\t\t\t\t    |");
        printf("\n-------------------------------------");
        
        printf("\nVolba: ");
        // Medzerou pri "%c" odstránim nadbytočnú medzeru v bufferi pri návrate z funkcie do mainu po zadaní písmenka
        scanf_s(" %c", &vyber, 1);
        getchar(); // Odstráni medzeru od scanfu na konci buffera

        //*---------------------------------------------- Výber možnosti ----------------------------------------------
        
        printf("\n--------------------------------------------------------------------------\n");

        if(velkost == 0){
            switch (vyber){
                case 'n':
                    newdriver(&tabulka, &velkost);
                    break;
                case 'q':
                    uvolnenieJazdcov(&tabulka);
                    nacitatJazdcov(&tabulka, &velkost);
                    printf("\nObnovujem zoznam jazdcov...");
                    break;
                case 'x':
                    uvolnenieJazdcov(&tabulka);
                    printf("\nUkoncujem...");
                    break;
                default:
                    printf("\nChyba: Zly vyber");
                    break;
            }
        }
        else{
            switch (vyber){
                case 's':
                    sum(tabulka, velkost);
                    break;
                case 'd':
                    driver(tabulka, velkost);
                    break;
                case 'l':
                    lap(tabulka, velkost);
                    break;
                case 'g':
                    gender(tabulka, velkost);
                    break;
                case 'b':
                    brand(tabulka, velkost);
                    break;
                case 'y':
                    year(tabulka, velkost);
                    break;
                case 'a':
                    average(tabulka, velkost);
                    break;
                case 'u':
                    under(tabulka, velkost);
                    break;
                case 'c':
                    change(&tabulka, velkost);
                    break;
                case 'n':
                    newdriver(&tabulka, &velkost);
                    break;
                case 'r':
                    rmdriver(&tabulka, &velkost);
                    break;
                case 'q':
                    uvolnenieJazdcov(&tabulka);
                    nacitatJazdcov(&tabulka, &velkost);
                    printf("\nObnovujem zoznam jazdcov...");
                    break;
                case 'x':
                    uvolnenieJazdcov(&tabulka);
                    printf("\nUkoncujem...");
                    break;
                default:
                    printf("\nChyba: Zly vyber");
                    break;
            }
        }

        printf("\n\n--------------------------------------------------------------------------");

    } while (vyber != 'x');

    return 0;
}