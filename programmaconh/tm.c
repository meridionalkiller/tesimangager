#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "studente.h"
#include "funzionifile.h"

int main()
{   

    char scelta_str[3];
    unsigned int scelta;

    printf("\n----  Benvenuto su Thesis Manager  ----\n");
    FILE *file = fopen("studente.bin", "rb+");
    if (file == NULL)
    {
        printf("Il file non e' stato aperto correttamente.\n");
    }
    else
    {
        do //scelta del menu 
    {
        printf("\nInserire 1 per accedere al menu' per gli studenti.\n");
        printf("Inserire 2 per accedere al menu' per i docenti.\n");
        printf("Inserire 3 per uscire dal programma. \n");
        scanf("%s",scelta_str);
        scelta=atoi(scelta_str);
 
        if ((scelta == 0 && scelta_str[0] != '0') && (scelta != 1 && scelta != 2 && scelta != 3))
        {
            printf("\nIl numero inserito non e' accettabile. Inserire 1 o 2 o, se vuoi uscire, 3.\n");
            
        }

    } while (scelta != 1 && scelta != 2 && scelta != 3);

    if (scelta == 1)
    {
        menustud(file); //scelta del menu dello studente 
    }
    else if (scelta == 2)
    {
        menudocente(file); //scelta del menu del docente 
    }
    else if (scelta == 3) 
    {
        printf("\n------ Chiusura del programma effettuata correttamente ------\n"); //messaggi di chiusura del programma 
    }
    }

    fclose(file);
    return 0;
}



