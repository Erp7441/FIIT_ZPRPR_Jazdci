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
        
        // TODO oramovať menu (pripadne spraviť reusable funkciu pre menu)
        printf("\n\ns - Sum\nd - Driver\nl - Lap\ng - Gender\nb - Brand\ny - Year\na - Average\nu - Under\nc - Change\nn - New Driver\nr - Remove Driver\nq - Reload\nx - Exit");
        printf("\nVolba: ");

        // Medzerou pri "%c" odstránim nadbytočnú medzeru v bufferi pri návrate z funkcie do mainu po zadaní písmenka
        scanf_s(" %c", &vyber, 1);
        getchar(); // Odstráni medzeru od scanfu na konci buffera

        //*---------------------------------------------- Výber možnosti ----------------------------------------------

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
            case 'q':
                uvolnenieJazdcov(&tabulka);
                nacitatJazdcov(&tabulka, &velkost);
                printf("\nObnovujem zoznam jazdcov...");
                break;
            case 'x':
                uvolnenieJazdcov(&tabulka);
                printf("\nUkoncujem...\n");
                break;
            default:
                printf("\nChyba: Zly vyber");
                break;
        }
    } while (vyber != 'x');

    return 0;
}