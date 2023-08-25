#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "studente.h"
#include "funzionifile.h"

void menustud(FILE *file) //menu studente
{
    int scelta;
    char scelta_str[10];

    do {
        printf("\nMenu studente:\n");
        printf("1. Aggiungi una nuova tesi\n");
        printf("2. Cancella la tua tesi\n");
        printf("3. Modifica la tua tesi\n");
        printf("4. Cerca una tesi\n");
        printf("5. Visualizza le tesi ordinate per valutazione\n");
        printf("6. Scarica e valuta una tesi\n");
        printf("7. Visualizza il traffico dati delle varie tesi\n");
        printf("8. Torna al menu principale\n");
        printf("Scelta: ");
        scanf("%s", scelta_str);
        scelta = atoi(scelta_str);
        printf("\n");
        switch (scelta) {
            case 1: {
                nuovatesi(file);
                break;
            }
            case 2: {
                cancellatesi(file);
                break;
            }
            case 3: {
               aggiornatesi(file);            
                break;
            }
            case 4: {
                ricerca(file);                
                break;
            }
            case 5: {
                stampa(file);
                break;
            }
            case 6: {
                 download(file);
                break;
            }
            case 7: {
                statistiche(file);
                break;
            }
            case 8:
                printf("\nTorno al menu principale.\n");
                main();
                break;
            default:
                printf("\nScelta non valida. Riprova.\n");
                
        } 
    }while (scelta != 8);
}

void menudocente(FILE *file) //menu docente
{
    int scelta;
    char scelta_str[10];
    do {
        printf("\nMenu docente:\n");
        printf("1. Cerca \n");
        printf("2. Scarica tesi e valuta tesi\n");
        printf("3. Torna al menu principale\n");
        printf("Scelta: ");
        scanf("%s", scelta_str);
        scelta = atoi(scelta_str);
        printf("\n");

        switch (scelta) {
            case 1: {
                ricerca(file);
                break;
            }
            case 2: {
                download(file);
                break;
            }
            case 3:
                printf("\nTorno al menu principale.\n");
                main();
                break;
            default:
                printf("\nScelta non valida. Riprova.\n");
                
        }
    } while (scelta != 3);
}

void ricerca(FILE *file) //richiesta del meto
{   
    char scelta_str[3];
    unsigned int scelta;
    do
    {
    printf("\nRicerca per: \n"); // Scelta di come deve avvenire la ricerca della tesi 
    printf("1. Parola \n");
    printf ("2. Codice \n");
    printf("Scelta: ");
    scanf("%s",scelta_str);
    scelta = atoi(scelta_str);
    if (scelta==1)
    {
        trovaparola(file);  //con le stringhe 
    }
    else if(scelta==2)
    {
        trovacodice(file); //con il numero della tesi 
    }
    else if (scelta == 0 && scelta_str[0] != '0') 
    {
        printf("Input non valido. L'opzione deve essere un numero intero.\n");
    }

    } while ((scelta == 0 && scelta_str[0] != '0') || (scelta != 1 && scelta != 2));   
    
}
    
//restiuisce un valore per trovare il file
int ricercaCodice(FILE* file, unsigned int codice, studente* risultato)
{
    studente stud;
    int trovato = 0; // Flag per indicare se il codice è stato trovato

    while (fread(&stud, sizeof(studente), 1, file) == 1) {
        if (stud.n_tesi == codice && stud.cancellato == 0 && stud.n_tesi > 0) {
            *risultato = stud;
            trovato = 1; // Imposta il flag a 1 se il codice è stato trovato
        }
    }
    // Restituisce il valore del flag (0 o 1)
    return trovato;
}

//funzione per convertire una stringa in caratteri minuscoli
void minuscolo(char *str) 
{
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

//inizio funzioni delle operazioni

void nuovatesi(FILE* file) //funzione per l'inserimento della tesi nel file
{
    studente stud;
    int scelta;
    
    FILE* codice_tesi = fopen("codice_tesi.bin", "rb+");  //apertura del file per determinare il numero della tesi in maniera univoca
    if (codice_tesi == NULL) {
        printf("Il file delle tesi non e' stato aperto correttamente.\n");
    }
    else
    {
        stud.n_tesi = 0;  //assegnazione del valore per il primo valore
        fread(&stud.n_tesi, sizeof(unsigned int), 1, codice_tesi); 
        stud.n_tesi++; // Incrementa il valore di n_tesi

        printf("\nInserisci il nome dello studente: "); //inserimento del nome
        scanf("%s", stud.nome);
        printf("Inserisci il cognome dello studente: "); //inserimento del cognome
        getchar(); 
        fgets(stud.cognome, sizeof(stud.cognome), stdin);
        printf("Inserisci il titolo della tesi: "); //inserimetno del titolo
        fgets(stud.titolo_tesi, sizeof(stud.titolo_tesi), stdin);
        do {
            printf("Inserisci la materia della tesi: 1. Informatica, 2. Biotecnologie, 3. Ingegneria Meccanica, 4. Ingegneria Gestionale, 5. Ingegneria Informatica, 6. Psicologia\n"); //inserimento della materia 
            char scelta_str[10];
            scanf("%s", scelta_str);
            scelta = atoi(scelta_str);
            if (scelta < 1 || scelta > 6) 
            {
                printf("\nScelta non valida.\n");
            }
        } while (scelta < 1 || scelta > 6);

        switch (scelta) {
            case 1:
                stud.mat = Informatica;
                break;
            case 2:
                stud.mat = Biotecnologie;
                break;
            case 3:
                stud.mat = IngegneriaMeccanica;
                break;
            case 4:
                stud.mat = IngegneriaGestionale;
                break;
            case 5:
                stud.mat = IngegneriaInformatica;
                break;
            case 6:
                stud.mat = Psicologia;
                break;
            default:
                break;
        }

        printf("Inserisci la prima parola chiave della tesi: "); //inserimento delle parole chiave della tesi
        getchar();
        scanf("%s", stud.parole_chiave);
        printf("Ora la seconda: ");
        getchar();
        scanf("%s", stud.parole_chiave1);
        printf("Ora la terza: ");
        getchar();
        scanf("%s", stud.parole_chiave2);

        do {
            printf("Inserisci l'anno accademico (inserire un anno compreso tra 2005 e 2030): "); //inserimento dell primo anno che viene preso in considerazione
            char anno_accademico_str[10];
            scanf("%s", anno_accademico_str);
            stud.anno_accademico = atoi(anno_accademico_str);
            if (stud.anno_accademico < 2005 || stud.anno_accademico > 2030) {
                printf("Anno accademico non valido. Riprova.\n");
            }
        } while (stud.anno_accademico < 2005 || stud.anno_accademico > 2030);

        stud.anno_accademico2 = stud.anno_accademico + 1; //determinazione del secondo anno 
        printf("Anno accademico: %u - %u\n", stud.anno_accademico, stud.anno_accademico2);

        printf("Inserisci un piccolo riassunto della tesi: "); //inserimento abstract
        getchar();
        fgets(stud.abstract, sizeof(stud.abstract), stdin);
        printf("Inserisci il nome del tuo relatore: "); //inserimento nome del relatore
        fgets(stud.relatore, sizeof(stud.relatore), stdin);
        printf("Il numero della tesi e': %d\n", stud.n_tesi); //scrittura del numero della tesi 
        stud.totdownload = 0; //assegnazione del totale dei download
        stud.totale = 0; //totale del voto utile per calcolare la media
        stud.voto = 0.0; //voto medio
        stud.totdownloadvot = 0; //totatale votanti
        stud.cancellato = 0; //flag per le tesi cancellate
        fseek(file, 0, SEEK_END);
        fwrite(&stud, sizeof(studente), 1, file); //scrittura sul file della tesi
        fseek(codice_tesi, 0, SEEK_SET);
        fwrite(&stud.n_tesi, sizeof(unsigned int), 1, codice_tesi); //scrittura del numero della tesi sul file codice_tesi
        fclose(codice_tesi);
    }
    
    
}

void aggiornatesi(FILE *file) //funzione per l'aggiornamento di una specifica tesi
{
    studente stud;
    char codice_str[LUNGH_CODICE];
    unsigned int codice;
    unsigned int scelta;
    char mod_str[3];
    unsigned int mod;
    char risposta[3];
    int trovato = 0;
    long posizione; // Salva la posizione del record da modificare

    do
    {
        printf("Inserisci il codice della tesi che vuoi modificare: ");
        scanf("%s", codice_str);
        codice = atoi(codice_str);
        if (codice == 0 && codice_str[0] != '0')
        {
            printf("Input non valido. L'opzione deve essere un numero intero.\n");
        }
    } while (codice == 0 && codice_str[0] != '0');

    rewind(file);
     trovato= ricercaCodice(file, codice, &stud);
        if (trovato) 
        {
            posizione = (codice - 1) * sizeof(studente); // Salva la posizione del record da modificare

            do 
            {
                do
                {
                    printf("1. Modifica il titolo della tesi\n");
                    printf("2. Modifica la materia della tesi\n");
                    printf("3. Modifica le tre parole chiave\n");
                    printf("4. Modifica l'anno accademico\n");
                    printf("5. Modifica l'abstract\n");
                    printf("6. Modifica il relatore\n");
                    printf("Scelta: ");
                    scanf("%s", mod_str);
                    mod = atoi(mod_str);
                    if (mod < 1 || mod > 6)
                    {
                        printf("\nScelta non valida.\n");
                    }
                } while (mod < 1 || mod > 7);

                if (mod == 1)
                {
                    printf("\nTitolo tesi: %s\n", stud.titolo_tesi);
                    printf("Inserisci il titolo della tesi modificato: ");
                    getchar(); 
                    fgets(stud.titolo_tesi, sizeof(stud.titolo_tesi), stdin);
                }
                else if (mod == 2)
                {
                    printf("\nMateria: ");
                    switch (stud.mat)
                    {
                        case Informatica:
                            printf("Informatica\n");
                            break;
                        case Biotecnologie:
                            printf("Biotecnologie\n");
                            break;
                        case IngegneriaMeccanica:
                            printf("Ingegneria Meccanica\n");
                            break;
                        case IngegneriaGestionale:
                            printf("Ingegneria Gestionale\n");
                            break;
                        case IngegneriaInformatica:
                            printf("Ingegneria Informatica\n");
                            break;
                        case Psicologia:
                            printf("Psicologia\n");
                            break;
                        default:
                            printf("Sconosciuta\n");
                            break;
                    }

                    do
                    {
                        printf("\nInserisci la materia modificata della tesi: 1. informatica, 2. biotecnologie, 3. ingegneria meccanica, 4. Ingegneria Gestionale, 5. Ingegneria Informatica, 6. Psicologia\n");
                        char scelta_str[3];
                        scanf("%s", scelta_str);
                        scelta = atoi(scelta_str);
                        if (scelta < 1 || scelta > 6)
                        {
                            printf("\nScelta non valida.\n");
                        }
                    } while (scelta < 1 || scelta > 6);

                    switch (scelta)
                    {
                        case 1:
                            stud.mat = Informatica;
                            break;
                        case 2:
                            stud.mat = Biotecnologie;
                            break;
                        case 3:
                            stud.mat = IngegneriaMeccanica;
                            break;
                        case 4:
                            stud.mat = IngegneriaGestionale;
                            break;
                        case 5:
                            stud.mat = IngegneriaInformatica;
                            break;
                        case 6:
                            stud.mat = Psicologia;
                            break;
                        default:
                            break;
                    }
                }
                else if (mod == 3) //modifica delle parole chiave
                {   
                    printf("\nParole chiave: %s, %s, %s\n", stud.parole_chiave, stud.parole_chiave1, stud.parole_chiave2); //scrittura del valore prima della modifica

                    printf("Inserisci la prima parola chiave modificata della tesi: ");
                    getchar();
                    scanf("%s", stud.parole_chiave);
                    printf("Ora la seconda: ");
                    getchar();
                    scanf("%s", stud.parole_chiave1);
                    printf("Ora la terza: ");
                    getchar();
                    scanf("%s", stud.parole_chiave2);
                }
                else if (mod == 4)
                {
                    printf("\nAnno accademico: %u - %u\n", stud.anno_accademico, stud.anno_accademico2);
                    do
                    {
                        printf("Inserisci l'anno accademico modificato (inserire un anno compreso tra 2005 e 2030): ");
                        char anno_accademico_str[10];
                        scanf("%s", anno_accademico_str);
                        stud.anno_accademico = atoi(anno_accademico_str);
                        if (stud.anno_accademico < 2005 || stud.anno_accademico > 2030)
                        {
                            printf("Anno accademico non valido. Riprova.\n");
                        }
                    } while (stud.anno_accademico < 2005 || stud.anno_accademico > 2030);

                    stud.anno_accademico2 = stud.anno_accademico + 1;
                    printf("Anno accademico: %u - %u\n", stud.anno_accademico, stud.anno_accademico2);
                }
                else if (mod == 5)
                {
                    printf("\nAbstract: %s\n", stud.abstract);
                    printf("Modifica il riassunto della tesi: ");
                    getchar(); 
                    fgets(stud.abstract, sizeof(stud.abstract), stdin);
                }
                else if (mod == 6)
                {
                    printf("\nRelatore: %s ", stud.relatore);
                    printf("Inserisci il nome del tuo relatore modificato: ");
                    getchar(); 
                    fgets(stud.relatore, sizeof(stud.relatore), stdin);
                }

                fseek(file, posizione, SEEK_SET); 
                fwrite(&stud, sizeof(studente), 1, file); // Sovrascrive il record nel file
                printf("Tesi aggiornata con successo.\n");
                fflush(file);
            do
                {
                    printf("\nHai altro da modificare? (si/no) ");
                    scanf("%s", risposta);
                    minuscolo(risposta);
                    if (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0)
                    {
                        printf("Inserire si o no.\n");
                    }
                } while (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0);

            } while (strcmp(risposta, "si") == 0);
            
        }

    else 
    {
        printf("Tesi non trovata.\n");
        do //controllo del valore inserito
            {
                printf("Vuoi riprovare la ricerca (si/no)? "); //riprovare la ricerca 
                scanf("%s", risposta);
                minuscolo(risposta);
                if (strcmp(risposta, "si") == 0)
                {
                    aggiornatesi(file);
                }
                else if (strcmp(risposta, "no") == 0) //nel caso in cui l'utente non abbia voluto valutare la tesi 
                {
                    printf("\n");
                }
                else if (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0) //nel caso in cui il valore non corrisponda a si o no
                {
                    printf("Inserire si o no.\n");
                }
                } while (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0);
    }

}

void cancellatesi(FILE* file) //funzione per cancellare una tesi
{
    studente stud;
    int trovato = 0;
    char codice_str[LUNGH_CODICE];
    unsigned int codice;
    char risposta[3];

    do
    {
        printf("Inserisci il codice della tesi che vuoi cancellare: ");
        scanf("%s", codice_str);
        codice = atoi(codice_str);
        if (codice == 0 && codice_str[0] != '0')
        {
            printf("Input non valido. L'opzione deve essere un numero intero.\n");
        }
    } while (codice == 0 && codice_str[0] != '0');

    rewind(file);
    trovato = ricercaCodice(file, codice, &stud);
    if (trovato)
    {
        stud.cancellato = 1;
        long posizione = (codice - 1) * sizeof(studente);
        fseek(file, posizione, SEEK_SET);
        fwrite(&stud, sizeof(studente), 1, file);
        fflush(file);

        printf("Tesi cancellata correttamente.\n");
    }

    else 
    {
        printf("Tesi non trovata.\n");
        do //controllo del valore inserito
            {
                
                printf("Vuoi riprovare la ricerca (si/no)? "); //riprovare la ricerca 
                scanf("%s", risposta);
                minuscolo(risposta);
                if (strcmp(risposta, "si") == 0)
                {
                    cancellatesi(file);
                }
                else if (strcmp(risposta, "no") == 0) //nel caso in cui l'utente non abbia voluto valutare la tesi 
                {
                    printf("\n");
                }
                else if (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0) //nel caso in cui il valore non corrisponda a si o no
                {
                    printf("Inserire si o no.\n");
                }
                } while (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0);
        
    }
}

void trovaparola(FILE *file) //ricerca della parola scelta dall'utente secondo alcuni valori 
{   
    studente stud;
    char opzione_str[10];
    unsigned int opzione;
    enum materie materiaCercata;
    int materia;
    char stringaCercata[LUNGH_MAX_TITOLOTESI];
    int trovato = 0;
    char risposta[3];
    
    

    do { //controllo dell'opzione scelta
        printf("\nSeleziona un'opzione per la ricerca:\n");
        printf("1. Ricerca per nome\n");
        printf("2. Ricerca per cognome\n");
        printf("3. Ricerca per titolo tesi\n");
        printf("4. Ricerca per materia\n");
        printf("5. Ricerca per parole chiave\n");
        printf("Opzione: ");
        scanf("%s", opzione_str);

        opzione = atoi(opzione_str);
        if ((opzione == 0 && opzione_str[0] != '0') || (opzione != 1 && opzione != 2 && opzione != 3 && opzione != 4 && opzione != 5)) {
            printf("Input non valido. L'opzione deve essere un numero intero o un numero compreso tra 1 e 5.\n");
        }
    } while (opzione != 1 && opzione != 2 && opzione != 3 && opzione != 4 && opzione != 5);

    if (opzione == 4) { // Se l'utente ha selezionato l'opzione per la ricerca per materia
        do {
            printf("\nSeleziona la materia:\n");
            printf("1. Informatica\n");
            printf("2. Biotecnologie\n");
            printf("3. Ingegneria Meccanica\n");
            printf("4. Ingegneria Gestionale\n");
            printf("5. Ingegneria Informatica\n");
            printf("6. Psicologia\n");
            printf("Materia: ");
            scanf("%s", opzione_str);

            materia = atoi(opzione_str);
            if (materia < 1 || materia > 6) {
                printf("Input non valido. Seleziona un numero compreso tra 1 e 6 per la materia.\n");
            }
            materiaCercata = (enum materie)materia;
        } while (materia < 1 || materia > 6);
    } else {
        printf("Inserisci la stringa da cercare: "); //inserimento della stringa che l'utente cerca
        scanf("%s", stringaCercata);
        // Converti la stringa da cercare in caratteri minuscoli
        minuscolo(stringaCercata);
    }

    rewind(file);

    while (fread(&stud, sizeof(studente), 1, file) == 1) {
        // Converti i campi del record in caratteri minuscoli prima di confrontarli
        minuscolo(stud.nome);
        minuscolo(stud.cognome);
        minuscolo(stud.titolo_tesi);
        minuscolo(stud.parole_chiave);
        minuscolo(stud.parole_chiave1);
        minuscolo(stud.parole_chiave2);

        if ((opzione == 1 && strstr(stud.nome, stringaCercata) != NULL && stud.cancellato == 0 && stud.n_tesi > 0) ||
            (opzione == 2 && strstr(stud.cognome, stringaCercata) != NULL && stud.cancellato == 0 && stud.n_tesi > 0) ||
            (opzione == 3 && strstr(stud.titolo_tesi, stringaCercata) != NULL && stud.cancellato == 0 && stud.n_tesi > 0) ||
            (opzione == 4 && stud.mat == materiaCercata && stud.cancellato == 0 && stud.n_tesi > 0) ||
            (opzione == 5 &&
             (strstr(stud.parole_chiave, stringaCercata) != NULL ||
              strstr(stud.parole_chiave1, stringaCercata) != NULL ||
              strstr(stud.parole_chiave2, stringaCercata) != NULL) && stud.cancellato == 0 && stud.n_tesi > 0)) {
            trovato = 1;
            printf("\n--------Trovato--------\n");
            printf("Nome: %s\n", stud.nome);
            printf("Cognome: %s", stud.cognome);
            printf("Numero tesi: %u \n", stud.n_tesi);
            printf("Titolo tesi: %s", stud.titolo_tesi);
            printf("Materia: ");
            switch (stud.mat) {
            case Informatica:
                printf("Informatica\n");
                break;
            case Biotecnologie:
                printf("Biotecnologie\n");
                break;
            case IngegneriaMeccanica:
                printf("Ingegneria Meccanica\n");
                break;
            case IngegneriaGestionale:
                printf("Ingegneria Gestionale\n");
                break;
            case IngegneriaInformatica:
                printf("Ingegneria Informatica\n");
                break;
            case Psicologia:
                printf("Psicologia\n");
                break;
            default:
                printf("Sconosciuta\n");
                break;
            }
            printf("Parole chiave: %s, %s, %s \n", stud.parole_chiave, stud.parole_chiave1, stud.parole_chiave2);
            printf("Anno accademico: %u - %u\n", stud.anno_accademico, stud.anno_accademico2);
            printf("Abstract: %s", stud.abstract);
            printf("Relatore: %s", stud.relatore);
            printf("Totale Download: %u\n", stud.totdownload);
            printf("Totale Recensioni: %u\n",stud.totdownloadvot);
           printf("Voto Medio: " );
             if (stud.voto>0)
                {
                    for (int i = 0; i < stud.voto; i++) 
                     {
                        printf("* ");
                     }
                     if (stud.voto<10)
                     {
                        for (int i = stud.voto; i < 10; i++) 
                            {
                                printf("- ");
                            }
                     }
                     
                        printf("/10 \n");
                }       
                 else
                {
                    printf(" nessuna valutazione\n");
                }           
                  
                printf("---------------------------------------\n");
        }
    }

    if (!trovato) {
        printf("\n La ricerca non ha prodotto risultati.\n");
        do //controllo del valore inserito
            {
                
                printf("Vuoi riprovare la ricerca (si/no)? "); //riprovare la ricerca 
                scanf("%s", risposta);
                minuscolo(risposta);
                if (strcmp(risposta, "si") == 0)
                {
                    trovaparola(file);
                }
                else if (strcmp(risposta, "no") == 0) //nel caso in cui l'utente non abbia voluto valutare la tesi 
                {
                    printf("\n");
                }
                else if (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0) //nel caso in cui il valore non corrisponda a si o no
                {
                    printf("Inserire si o no.\n");
                }
                } while (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0);
    }
}

void trovacodice(FILE *file) //funzione per la ricerca attraverso il codice scelto dall'utente
{
    unsigned int codice;
    char codice_str[10];
    studente stud;
    int trovato = 0; 
    do{
        printf("\nInserisci il codice della tesi che ti interessa : ");
        scanf("%s", codice_str);
        codice = atoi(codice_str);
        if (codice == 0 && codice_str[0] != '0') 
        {
        printf("Input non valido. Il codice deve essere un numero intero.\n");
        }
    } while (codice == 0 && codice_str[0] != '0'); 

    rewind(file);

    trovato = ricercaCodice(file, codice, &stud);

    if (trovato) // Stampa i dettagli del record trovato se trovato e' uguale a 1
    {
        printf("\n--------Trovato--------\n");        
        printf("Nome: %s\n", stud.nome);
        printf("Cognome: %s", stud.cognome);
        printf("Numero tesi: %u \n", stud.n_tesi);
        printf("Titolo tesi: %s", stud.titolo_tesi);
        printf("Materia: ");
        switch (stud.mat)
        {
            case Informatica:
                printf("Informatica\n");
                break;
            case Biotecnologie:
                printf("Biotecnologie\n");
                break;
            case IngegneriaMeccanica:
                printf("Ingegneria Meccanica\n");
                break;
            case IngegneriaGestionale:
                printf("Ingegneria Gestionale\n");
                break;
            case IngegneriaInformatica:
                printf("Ingegneria Informatica\n");
                break;
            case Psicologia:
                printf("Psicologia\n");
                break;
            default:
                printf("Sconosciuta\n");
                break;
        }
        printf("Parole chiave: %s, %s, %s \n", stud.parole_chiave, stud.parole_chiave1, stud.parole_chiave2);
        printf("Anno accademico: %u - %u\n", stud.anno_accademico, stud.anno_accademico2);
        printf("Abstract: %s", stud.abstract);
        printf("Relatore: %s", stud.relatore);
        printf("Totale Download: %u\n", stud.totdownload);
        printf("Totale Recensioni: %u\n",stud.totdownloadvot);
        printf("Voto Medio: " );
             if (stud.voto>0)
                {
                    for (int i = 0; i < stud.voto; i++) 
                     {
                        printf("* ");
                     }
                     if (stud.voto<10)
                     {
                        for (int i = stud.voto; i < 10; i++) 
                            {
                                printf("- ");
                            }
                     }
                     
                        printf("/10 \n");
                }       
                 else
                {
                    printf(" nessuna valutazione\n");
                }           
                  
                printf("---------------------------------------\n");
    }
    else //altrimenti stampa questo messaggio
    {
        char risposta[3];
        printf("\n La ricerca non ha prodotto risultati.\n");
        do //controllo del valore inserito
            {
                printf("Vuoi riprovare la ricerca (si/no)? "); //riprovare la ricerca 
                scanf("%s", risposta);
                minuscolo(risposta);
                if (strcmp(risposta, "si") == 0)
                {
                    trovacodice(file);
                }
                else if (strcmp(risposta, "no") == 0) //nel caso in cui l'utente non abbia voluto valutare la tesi 
                {
                    printf("\n");
                }
                else if (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0) //nel caso in cui il valore non corrisponda a si o no
                {
                    printf("Inserire si o no.\n");
                }
                } while (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0);
        
    } 
    
}

//funzioni per l'ordinamento
void bubbleSort(studente* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].voto < arr[j + 1].voto) {
                studente temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void stampa(FILE *file) //funzione che stampa il file ordinato secondo l'ordinamento del bubble sort
{
    studente tesiArray[LUNGH_MAX_STUDENTI]; // Assumiamo che ci siano al massimo 100 tesi nel file
    int nTesi = 0; // Contatore delle tesi nel file

    rewind(file);
    while (fread(&tesiArray[nTesi], sizeof(studente), 1, file) == 1) {
        nTesi++;
    }

    bubbleSort(tesiArray, nTesi);

    for (int i = 0; i < nTesi; i++) {
        studente stud = tesiArray[i];

        if (stud.cancellato == 0)
        {

            printf("Generalita: %s %s", stud.nome,stud.cognome);
            printf("Numero tesi: %u \n", stud.n_tesi);
            printf("Titolo tesi: %s", stud.titolo_tesi);
            printf("Materia: ");
            switch (stud.mat)
                {
                    case Informatica:
                    printf("Informatica\n");
                    break;
                    case Biotecnologie:
                    printf("Biotecnologie\n");
                    break;
                    case IngegneriaMeccanica:
                    printf("Ingegneria Meccanica\n");
                    break;
                    case IngegneriaGestionale:
                    printf("Ingegneria Gestionale\n");
                    break;
                    case IngegneriaInformatica:
                    printf("Ingegneria Informatica\n");
                    break;
                    case Psicologia:
                    printf("Psicologia\n");
                    break;
                    default:
                    printf("Sconosciuta\n");
                    break;
                }
            printf("Parole chiave: %s, %s, %s\n", stud.parole_chiave, stud.parole_chiave1, stud.parole_chiave2);
            printf("Anno accademico: %u - %u\n", stud.anno_accademico, stud.anno_accademico2);
            printf("Abstract: %s", stud.abstract);
            printf("Relatore: %s\n", stud.relatore);
            printf("Totale Download: %u\n", stud.totdownload);
            printf("Totale Recensioni: %u\n", stud.totdownloadvot);
            printf("Voto Medio: " );
             if (stud.voto>0)
                {
                    for (int i = 0; i < stud.voto; i++) 
                     {
                        printf("* ");
                     }
                     if (stud.voto<10)
                     {
                        for (int i = stud.voto; i < 10; i++) 
                            {
                                printf("- ");
                            }
                     }
                     
                        printf("/10 \n");
                }       
                 else
                {
                    printf(" nessuna valutazione\n");
                }
            printf("---------------------------\n");
        }
        
        
    }
}

void download(FILE *file) //funzione che simula il download della tesi e che permette di valutare la sua utilità 
{   
    studente stud;
    char codice_str[10];
    char voto_str[2];
    unsigned int voto;
    unsigned int codice;
    unsigned int click = 1; 
    int trovato = 0;
    char risposta[3];
    long posizione;
    
    do
    {
        printf("Inserisci il codice della tesi che vuoi scaricare e valutare: ");
        scanf("%s", codice_str);
        codice = atoi(codice_str);
        if (codice == 0 && codice_str[0] != '0') 
        {
            printf("Input non valido. L'opzione deve essere un numero intero.\n");
        }
    } while (codice == 0 && codice_str[0] != '0');

        rewind(file);
        trovato= ricercaCodice(file, codice, &stud);
        if (trovato) 
        {   
            posizione = (codice - 1) * sizeof(studente); // Salva la posizione del record da modificare
            trovato=1;
            temposcaricamento();
            printf("Nome: %s\n", stud.nome);
            printf("Cognome: %s", stud.cognome);
            printf("Numero tesi: %u \n", stud.n_tesi);
            printf("Titolo tesi: %s", stud.titolo_tesi);
            printf("Materia: ");
                switch (stud.mat)
                {
                    case Informatica:
                        printf("Informatica\n");
                            break;
                    case Biotecnologie:
                        printf("Biotecnologie\n");
                            break;
                    case IngegneriaMeccanica:
                        printf("Ingegneria Meccanica\n");
                            break;
                    case IngegneriaGestionale:
                        printf("Ingegneria Gestionale\n");
                            break;
                    case IngegneriaInformatica:
                        printf("Ingegneria Informatica\n");
                            break;
                    case Psicologia:
                        printf("Psicologia\n");
                            break;
                    default:
                        printf("Sconosciuta\n");
                            break;
                }
            printf("Parole chiave: %s, %s, %s \n", stud.parole_chiave, stud.parole_chiave1, stud.parole_chiave2);
            printf("Anno accademico: %u - %u\n", stud.anno_accademico, stud.anno_accademico2);
            printf("Abstract: %s", stud.abstract);
            printf("Relatore: %s", stud.relatore);
            printf("Totale Download: %u\n", stud.totdownload);
            printf("Totale Recensioni: %u\n", stud.totdownloadvot);
            printf("Voto Medio: " );
             if (stud.voto>0)
                {
                    for (int i = 0; i < stud.voto; i++) 
                     {
                        printf("* ");
                     }
                     if (stud.voto<10)
                     {
                        for (int i = stud.voto; i < 10; i++) 
                            {
                                printf("- ");
                            }
                     }
                     
                        printf("/10 \n");
                }       
                 else
                {
                    printf(" nessuna valutazione\n");
                }           
                  
                printf("---------------------------------------\n");

                fread(&stud, sizeof(studente), 1, file);                
                stud.totdownload= stud.totdownload + click;
                fseek(file, posizione, SEEK_SET); // Posizionamento all'inizio del record
                fwrite(&stud, sizeof(studente), 1, file); // Scrittura dati aggiornati nel file
                fflush(file);

                do //controllo del valore inserito
                {   
                    
                    printf("Vuoi valutare questa tesi (si/no)? "); //richiesta di valutazione della tesi 
                    scanf("%s", risposta);
                    minuscolo(risposta);
                    if (strcmp(risposta, "si") == 0)
                    {
                        do
                        {
                            printf("Inserisci un voto da 1 a 10 per la tesi in base a quanto l'hai reputata utile: "); //inserimento della valutazione della tesi
                            scanf("%s", voto_str);
                            voto = atoi(voto_str);
                            if ((voto == 0 && voto_str[0] != '0') || (voto < 1 || voto > 10)) 
                            {
                                printf("Input non valido. L'opzione deve essere un numero intero compreso tra uno e 10.\n");
                            }
                        } while (voto < 1 || voto > 10);
                        stud.totdownloadvot=stud.totdownloadvot+click; //calcolo dei download effettuati da coloro che recensiscono
                        stud.totale = stud.totale + voto; //calcolo del totale utile per andare a calcolare la media 
                        stud.voto = stud.totale / stud.totdownloadvot; //calcolo del voto medio sulla base delle recensioni
                        fseek(file, posizione, SEEK_SET); 
                        fwrite(&stud, sizeof(studente), 1, file); // Scrive i dati modificati nel file
                        fflush(file);
                    }
                    else if (strcmp(risposta, "no") == 0) //nel caso in cui l'utente non abbia voluto valutare la tesi 
                    {
                        printf("Non valuterai questa tesi.\n");
                    }
                    else if (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0) //nel caso in cui il valore non corrisponda a si o no
                    {
                        printf("Inserire si o no.\n");
                    }
                } while (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0);               
                
            }

        if(!trovato)
        {
            printf("Tesi non trovata.\n");
            do //controllo del valore inserito
            {
                printf("Vuoi riprovare il download (si/no)? "); //tentativo del download
                scanf("%s", risposta);
                minuscolo(risposta);
                if (strcmp(risposta, "si") == 0)
                {
                    download(file);
                }
                else if (strcmp(risposta, "no") == 0) //nel caso in cui l'utente non abbia voluto valutare la tesi 
                {
                    printf("\n");
                }
                else if (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0) //nel caso in cui il valore non corrisponda a si o no
                {
                    printf("Inserire si o no.\n");
                }
            } while (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0);
        }
}
    
void statistiche(FILE *file) //funzione che scrive le statistiche dei download 
{
    rewind(file);
    studente stud;
    int maggdieci = 0, seinove = 0, trecinque = 0, menotre = 0; //valori che useremo per tener conto delle tesi con il range dei download
    while (fread(&stud, sizeof(studente), 1, file) == 1) //lettura del file 
    {   
        if (stud.cancellato == 0)
        {
            if (stud.totdownload>10)
            {
                maggdieci++;
            }
            else if (stud.totdownload<=9 && stud.totdownload>=6)
            {
                seinove++;
            }
            else if (stud.totdownload<=5 && stud.totdownload>=3)
            {
                trecinque++;
            }
            else if (stud.totdownload<3 && stud.totdownload>=1)
            {
                menotre++;
            }
        }
    }
    printf("Tesi con piu' di 10 download: %d\n",maggdieci); //scrittura delle statistiche 
    printf("Tesi con 6 o piu' download: %d\n",seinove);
    printf("Tesi con 3-5 download: %d\n",trecinque);
    printf("Tesi con meno di 3 download: %d\n",menotre);
        
        
}

void temposcaricamento() //funzione che serve a creare l'idea di download
{
   int tempo;
    srand(time(NULL)); //funzione random per rendere casuale i secondi che il soggetto deve attendere per scaricare il file 

    tempo = rand() % 5 + 1;

    printf("Download in corso");
    for (int i = 0; i < tempo; i++) //scrive i puntini che rappresenteno i secondi 
    { 
        printf(".");
        sleep(1); // Attendi un secondo
    }

    printf(" Completato!\n");
}
