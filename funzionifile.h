#ifndef FUNZIONIFILE_H
#define FUNZIONIFILE_H


int main();

//sottoprogrammi per aprire i file 
void aggiungi();
void modifica();
void ricerca();
void cancellazione();
void quicksort(studente *records, int piccolo, int grande);
int partizionaFile(studente *records, int piccolo, int grande);
void ordinamento();
void installazione();
void totstatistiche();

//funzioni
int ricercaCodice(FILE* file, unsigned int codice, studente* risultato);
void menustud();
void menudocente();
void nuovatesi(FILE *file);
void aggiornatesi(FILE *file);
void cancellatesi(FILE *file);
void trovaparola(FILE *file);
void trovacodice(FILE *file);
void scambia(studente *a, studente *b);
void stampa(FILE *file);
void statistiche(FILE *file);
void download(FILE *file);
void temposcaricamento();

// void menu
void menustud() //menu studente
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
                aggiungi();
                break;
            }
            case 2: {
                cancellazione();
                break;
            }
            case 3: {
                modifica();                
                break;
            }
            case 4: {
                ricerca();                
                break;
            }
            case 5: {
                ordinamento();
                break;
            }
            case 6: {
                installazione();
                break;
            }
            case 7: {
                totstatistiche();
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

void menudocente() //menu docente
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
                ricerca();
                break;
            }
            case 2: {
                installazione();
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

//apertura del file nei vari metodi
void aggiungi() //apertura del file per inserire la nuova tesi
{
     FILE *file = fopen("studente.bin", "ab");
    if (file == NULL)
    {
        printf("Il file non e' stato aperto correttamente.\n");
        return;
    }
    nuovatesi(file);
    fclose(file);
}

void modifica() //apertura del file per modificare la tesi dell'utente
{
    FILE *file = fopen("studente.bin", "rb");
    if (file == NULL)
    {
        printf("Il file non e stato aperto correttamente. \n");
        return;
    }
    aggiornatesi(file);
    fclose(file);
}

void cancellazione() //apertura del file per andare a cancellare la tesi dell'utente
{   
    FILE *file = fopen("studente.bin", "rb");
    if (file == NULL)
    {
        printf("Il file non e stato aperto correttamente. \n");
        return;
    }
    cancellatesi(file);
    fclose(file);
}

void ricerca() //apertura del file per andare a ricercare la tesi di un'utente in base a due metodi
{   
    char scelta_str[3];
    unsigned int scelta;
    FILE *file = fopen("studente.bin", "rb");
    if (file == NULL)
    {
        printf("Il file non e' stato aperto correttamente.\n");
        return;
    }
    do
    {
    printf("Se non sei a conoscenza del numero di tesi premi 1 altrimenti premi 2 \n");  // Scelta di come deve avvenire la ricerca della tesi 
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
        return;
    }

    } while ((scelta == 0 && scelta_str[0] != '0') && (scelta != 1 && scelta != 2));   
    
    fclose(file);
}

void ordinamento() //apertura del file in diverso modo affinche possa scrivere la struttura ordinata
{
    FILE *file = fopen("studente.bin", "rb");
    if (file == NULL) {
        printf("Impossibile aprire il file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long numRecords = ftell(file) / sizeof(studente);
    rewind(file);

    studente *records = malloc(numRecords * sizeof(studente));
    if (records == NULL) {
        printf("Errore di allocazione della memoria.\n");
        fclose(file);
        return;
    }

    fread(records, sizeof(studente), numRecords, file);

    quicksort(records, 0, numRecords - 1);

    fclose(file);

    file = fopen("studente.bin", "wb");
    if (file == NULL) {
        printf("Impossibile aprire il file.\n");
        free(records);
        return;
    }

    fwrite(records, sizeof(studente), numRecords, file);

    fclose(file);
    free(records);

    printf("Ordinamento completato.\n");
    
    
    file = fopen("studente.bin", "rb");
    if (file == NULL) {
        printf("Impossibile aprire il file.\n");
        return;
    }
    stampa(file);
    fclose(file);

}

void installazione() //apertura del file per il download e la valutazione
{
    FILE *file = fopen("studente.bin", "rb+");
    if (file == NULL)
    {
        printf("Il file non e' stato aperto correttamente. \n");
        return;
    }
    download(file);
    fclose(file);
}

void totstatistiche() //apertura del file per la visualizzazione delle statistiche
 {
    FILE *file = fopen("studente.bin", "rb");
    if (file == NULL)
    {
        printf("Il file non e' stato aperto correttamente. \n");
        return;
    }
    statistiche(file);
    fclose(file);
 }

//restiuisce un valore per trovare il file
int ricercaCodice(FILE* file, unsigned int codice, studente* risultato) {
    studente stud;
    int trovato = 0; // Flag per indicare se il codice è stato trovato

    while (fread(&stud, sizeof(studente), 1, file) == 1) {
        if (stud.n_tesi == codice) {
            *risultato = stud;
            trovato = 1; // Imposta il flag a 1 se il codice è stato trovato
        }
    }
    // Restituisce il valore del flag (0 o 1)
    return trovato;
}

//inizio funzioni
void nuovatesi(FILE* file) //funzione per l'inserimento della tesi nel file
{
    studente stud;
    int scelta;
   

    FILE* codice_tesi = fopen("codice_tesi.bin", "rb+");  //apertura del file per determinare il numero della tesi in maniera univoca
    if (codice_tesi == NULL) {
        printf("Il file delle tesi non e' stato aperto correttamente.\n");
        return;
    }
    
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

    fwrite(&stud, sizeof(stud), 1, file); //scrittura sul file della tesi

    fseek(codice_tesi, 0, SEEK_SET);
    fwrite(&stud.n_tesi, sizeof(unsigned int), 1, codice_tesi); //scrittura del numero della tesi sul file codice_tesi

    fclose(codice_tesi);
}

void aggiornatesi(FILE *file) //funzione per l'aggiornamento della tesi dell'utente
{   
    studente stud;
    char codice_str[3]; 
    unsigned int codice;
    unsigned int scelta;
    char mod_str[3];
    unsigned int mod;
    char risposta[3];
    int trovato = 0;

    do
    {
        printf("Inserisci il codice della tesi che vuoi modificare: "); 
        scanf("%s", codice_str);
        codice = atoi(codice_str);
        if (codice == 0 && codice_str[0] != '0') 
        {
            printf("Input non valido. L'opzione deve essere un numero intero.\n");
            return;
        }
    } while (codice == 0  && codice_str[0] != '0');   
    
    FILE *tempFile = fopen("temp.bin", "wb"); // Apri un nuovo file temporaneo che sostituirà studente.bin nel caso venga trovata la tesi
    if (tempFile == NULL)
    {
        printf("Impossibile aprire il file temporaneo.\n");
        return;
    }

        while (fread(&stud, sizeof(studente), 1, file) == 1) 
        {
            if (stud.n_tesi == codice) 
            {
                trovato = 1;
                if (trovato)
        {   
            do //primo do while nel caso in cui l'utente voglia modificare piu cose
            {   
                do // do while per la verifica dell'inserimento corretto del codice
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
                if (mod < 1 || mod > 7) 
                    {
                        printf("\nScelta non valida.\n");
                    }
                } while (mod < 1 || mod > 7);

                if (mod == 1) //modifica del titolo
                {   
                    printf("\nTitolo tesi: %s", stud.titolo_tesi); //scrittura del valore prima della modifica

                    printf("Inserisci il titolo della tesi modificato: ");
                    getchar();
                    fgets(stud.titolo_tesi, sizeof(stud.titolo_tesi), stdin);
                }
                
                else if (mod == 2) //modifica della materia
                {   
                    printf("\nMateria: "); //scrittura del valore prima della modifica
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

                    do { //do while per verificare l'inserimento corretto del valore
                    printf("\nInserisci la materia modificata della tesi: 1. informatica, 2. biotecnologie, 3. ingegneria meccanica, 4. Ingegneria Gestionale, 5. Ingegneria Informatica, 6. Psicologia\n");
                    char scelta_str[3];
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

                else if (mod == 4) // modifica dell'anno accademico 
                {
                    printf("\nAnno accademico: %u - %u \n", stud.anno_accademico, stud.anno_accademico2); //scrittura del valore prima della modifica

                    do //verifica del valore che e' stato inserito
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
                
                else if (mod == 5) //modifica dell'abstract
                {   
                    printf("\nAbstract: %s\n", stud.abstract); //scrittura del valore prima della modifica

                    printf("Modifica il riassunto della tesi: ");
                    getchar();
                    fgets(stud.abstract, sizeof(stud.abstract), stdin);
                }
                
                else if (mod == 6) //modifica del relatore
                {   
                    printf("\nRelatore: %s ", stud.relatore); //scrittura del valore prima della modifica

                    printf("Inserisci il nome del tuo relatore modificato: ");
                    getchar();
                    fgets(stud.relatore, sizeof(stud.relatore), stdin);
                }             
                
                do //do while per controllare se la parola inserita e' corretta
                {
                    printf("\nHai altro da modificare?(si/no) "); //richiesta di ripetizione del ciclo
                    scanf("%s", risposta);
                    if (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0)
                    {
                        printf("Inserire si o no in minuscolo.");
                    }
                } while (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0);
                
                
            } while (strcmp(risposta, "si") == 0 );   
        
        
            fwrite(&stud, sizeof(studente), 1, tempFile); // Scrivi il record nel file temporaneo 
        }
            }
            else
            {
                fwrite(&stud, sizeof(studente), 1, tempFile); // Scrivi il record nel file temporaneo 
            }
        }
        
        
        fclose(file);
        fclose(tempFile);     

        remove("studente.bin");// Rimuovi il file originale
        rename("temp.bin", "studente.bin");// Rinomina il file temporaneo come il file originale
    
    if(!trovato) //tesi non trovata
        {
            printf("Tesi non trovata.\n");
        }
}

void cancellatesi(FILE* file) //funzione per la cancellazione della tesi dell'utente
{   
    studente stud;
    char codice_str[10];
    unsigned int codice;    
    int trovato = 0;
     
    do
    {
        printf("Inserisci il codice della tesi da rimuovere: ");
        scanf("%s", codice_str);
        codice = atoi(codice_str);
    if (codice == 0 && codice_str[0] != '0') 
        {
            printf("Input non valido. Il codice della tesi deve essere un numero intero.\n");
            return;
        }
    } while (codice == 0 && codice_str[0] != '0');  //verifica del codice inserito 
    
    FILE* tempFile = fopen("temp.bin", "wb"); //apertura del file temporaneo
    if (tempFile == NULL) {
        printf("Impossibile aprire il file temporaneo.\n");
        return;
    }

    while (fread(&stud, sizeof(studente), 1, file) == 1) //legge il file fino alla fine
    {
        if (stud.n_tesi != codice) //se non lo trova lo scrive nel file temporaneo altrimenti assegna a trovato 1
        {
            fwrite(&stud, sizeof(studente), 1, tempFile); 
        } else { 
            trovato = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (trovato) {  //se trovato uguale a 1 sostituisce il file altrimenti elimina il file temporaneo 
        remove("studente.bin");
        rename("temp.bin", "studente.bin");
        printf("Tesi rimossa con successo.\n");
    } else {
        remove("temp.bin");
        printf("Tesi non trovata.\n");
    }
}

void trovaparola(FILE *file)  //funzione per trovare la parola o la sottostringa di una parola al fine della ricerca di un file
{
    char opzione_str[10];
    unsigned int opzione;
    enum materie materiaCercata;
    int materia;
    char stringaCercata[LUNGH_MAX_TITOLOTESI];
    int trovato = 0;
    studente stud;

    do { //controllo dell'opzione scelta
        printf("Seleziona un'opzione per la ricerca:\n");
        printf("1. Ricerca per nome\n");
        printf("2. Ricerca per cognome\n");
        printf("3. Ricerca per titolo tesi\n");
        printf("4. Ricerca per materia\n");
        printf("5. Ricerca per parole chiave\n");
        printf("Opzione: ");
        scanf("%s", opzione_str);

        opzione = atoi(opzione_str);
        if ((opzione == 0 && opzione_str[0] != '0') || (opzione != 1 && opzione != 2 && opzione != 3 && opzione != 4 && opzione != 5) ) {
            printf("Input non valido. L'opzione deve essere un numero intero o un numero compreso tra 1 e 5.\n");
        }
    } while (opzione != 1 && opzione != 2 && opzione != 3 && opzione != 4 && opzione != 5);
    
    
     if (opzione == 4)   // Se l'utente ha selezionato l'opzione per la ricerca per materia
        {
            do
            {                                      
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
        }
    
    else
    {
        printf("Inserisci la stringa da cercare: "); //inserimento della stringa che l'utente cerca
        scanf("%s", stringaCercata);
    }
    

    rewind(file);

    while (fread(&stud, sizeof(studente), 1, file) == 1) {
        if ((opzione == 1 && strstr(stud.nome, stringaCercata) != NULL) ||
            (opzione == 2 && strstr(stud.cognome, stringaCercata) != NULL) ||
            (opzione == 3 && strstr(stud.titolo_tesi, stringaCercata) != NULL) ||
            (opzione == 4 && stud.mat == materiaCercata) ||
            (opzione == 5 &&
            (strstr(stud.parole_chiave, stringaCercata) != NULL ||
            strstr(stud.parole_chiave1, stringaCercata) != NULL ||
            strstr(stud.parole_chiave2, stringaCercata) != NULL))) {
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
            printf("Voto Medio: %.2f\n", stud.voto);
            printf("------------------------\n");
        }
    }
    
    if (!trovato) {  //nel caso in cui trovato non sia 1 
        printf("\n La ricerca non ha prodotto risultati.\n");
    }
}

void trovacodice(FILE *file) //funzione per la ricerca attraverso il codice scelto dall'utente
{
    unsigned int codice;
    char codice_str[10];
    studente stud;
    int trovato = 0; 

    do
    {
        printf("Inserisci il codice della tesi che ti interessa: ");
        scanf("%s", codice_str);
        codice = atoi(codice_str);
        if (codice == 0 && codice_str[0] != '0') 
        {
        printf("Input non valido. Il codice deve essere un numero intero.\n");
        return;
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
        printf("Voto Medio: %.2f\n", stud.voto);
        printf("------------------------\n");
    } 
    else //altrimenti stampa questo messaggio
    {
        printf("\n La ricerca non ha prodotto risultati.\n");
    }
}

//funzioni per l'ordinamento
void quicksort(studente *records, int piccolo, int grande) 
{
    if (piccolo < grande) 
    {
        int pivot = partizionaFile(records, piccolo, grande);
        quicksort(records, piccolo, pivot - 1);
        quicksort(records, pivot + 1, grande);
    }
}

int partizionaFile(studente *records, int piccolo, int grande) 
{
    studente pivot = records[grande];
    int i = piccolo - 1;

    for (int j = piccolo; j <= grande - 1; j++) {
        if (records[j].voto >= pivot.voto) {
            i++;
            scambia(&records[i], &records[j]);
        }
    }

    scambia(&records[i + 1], &records[grande]);

    return (i + 1);
}

void scambia(studente *a, studente *b) 
{
    studente temp = *a;
    *a = *b;
    *b = temp;
}

void stampa(FILE *file) //stampa il file ordinato 
{

    studente stud;
    while (fread(&stud, sizeof(studente), 1, file) == 1) {
        printf("------------------------\n");
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
        printf("Parole chiave: %s, %s, %s\n", stud.parole_chiave, stud.parole_chiave1, stud.parole_chiave2);
        printf("Anno accademico: %u - %u\n", stud.anno_accademico, stud.anno_accademico2);
        printf("Abstract: %s\n", stud.abstract);
        printf("Relatore: %s\n", stud.relatore);
        printf("Totale Download: %u\n", stud.totdownload);
        printf("Voto Medio: %.2f\n", stud.voto);
        printf("------------------------\n");
    }

}

void download(FILE *file) //funzione che simula il download della tesi e che permette di valutare la sua utilità 
{   
    studente stud;
    char codice_str[10];
    char voto_str[2];
    unsigned int voto;
    unsigned int codice;
    unsigned int click = 0; 
    int trovato = 0;
    char risposta[3]; 

    do
    {
        printf("Inserisci il codice della tesi che vuoi scaricare e valutare: ");
        scanf("%s", codice_str);
        codice = atoi(codice_str);
        if (codice == 0 && codice_str[0] != '0') 
        {
            printf("Input non valido. L'opzione deve essere un numero intero.\n");
            return;
        }
    } while (codice == 0 && codice_str[0] != '0');

    FILE *tempFile = fopen("temp.bin", "wb"); //apertura del file temporaneo che andra sostituire il file studente.bin
    if (tempFile == NULL)
    {
        printf("Impossibile aprire il file temporaneo.\n");
        return;
    }

    while (fread(&stud, sizeof(studente), 1, file) == 1) 
        {
            if (stud.n_tesi == codice) 
            {
                trovato = 1;
                if (trovato)
                {   
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
                    printf("Voto Medio: %.2f\n", stud.voto);
                    printf("------------------------\n");

                    click = 1; //utile per calcolare il totdownload
                    stud.totdownload = stud.totdownload + click; //calcolo del totale dei download            
                            
                do //controllo del valore inserito
                {
                    printf("Vuoi valutare questa tesi (si/no)? "); //richiesta di valutazione della tesi 
                    scanf("%s", risposta);
                    
                    if (strcmp(risposta, "si") == 0)
                    {
                        do
                        {
                            printf("Inserisci un voto da 1 a 10 per la tesi in base a quanto l'hai reputata utile: "); //inserimento della valutazione della tesi
                            scanf("%s", voto_str);
                            voto = atoi(voto_str);
                            if ((voto == 0 && voto_str[0] != '0') || (voto < 1 || voto > 10)) 
                            {
                                printf("Input non valido. L'opzione deve essere un numero intero.\n");
                            }
                        } while (voto < 1 || voto > 10);
            
                        stud.totale = stud.totale + voto; //calcolo del totale utile per andare a calcolare la media 
                        stud.voto = stud.totale / stud.totdownload; //calcolo del voto medio
                    }
                    else if (strcmp(risposta, "no") == 0) //nel caso in cui l'utente non abbia voluto valutare la tesi 
                    {
                        printf("Non valuterai questa tesi.\n");
                    }
                    else if (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0) //nel caso in cui il valore non corrisponda a si o no
                    {
                        printf("Inserire si o no in minuscolo.\n");
                    }
                } while (strcmp(risposta, "si") != 0 && strcmp(risposta, "no") != 0);
                
                
            fwrite(&stud, sizeof(studente), 1, tempFile); // Scrivi il record nel file temporaneo
            }
            }
            else
            {
                fwrite(&stud, sizeof(studente), 1, tempFile); // Scrivi il record nel file temporaneo 
            }
        }
        
    fclose(file);
    fclose(tempFile);
    
    remove("studente.bin"); // Rimuovi il file originale
    rename("temp.bin", "studente.bin"); // Rinomina il file temporaneo come il file originale

    if(!trovato)
    {
        printf("Tesi non trovata.\n");
    }
}

void statistiche(FILE *file) //funzione che scrive le statistiche dei download 
{
    rewind(file);
    studente stud;
    int maggdieci = 0, seinove = 0, trecinque = 0, menotre = 0; //valori che useremo per tener conto delle tesi con il range dei download
    while (fread(&stud, sizeof(studente), 1, file) == 1) //lettura del file 
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

#endif