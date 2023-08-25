#ifndef FUNZIONIFILE_H
#define FUNZIONIFILE_H

int ricercaCodice(FILE* file, unsigned int codice, studente* risultato);
void minuscolo(char *str);
void bubbleSort(studente* arr, int n);
void temposcaricamento();

//funzioni dei menu

void menustud(FILE *file);
void menudocente(FILE *file);

//funzioni presenti nei menu

void nuovatesi(FILE *file);
void aggiornatesi(FILE *file);
void cancellatesi(FILE *file);
void ricerca(FILE *file);
void trovaparola(FILE *file);
void trovacodice(FILE *file);
void stampa(FILE *file);
void statistiche(FILE *file);
void download(FILE *file);

#endif

