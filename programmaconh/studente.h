#ifndef STUDENTE_H
#define STUDENTE_H

#define LUNGH_MAX_NOME 50
#define LUNGH_MAX_COGNOME 50
#define LUNGH_MAX_TITOLOTESI 100
#define LUNGH_MAX_PAROLA 20
#define LUNGH_MAX_ABSTRACT 500
#define N_PAROLE_CHIAVE 3
#define LUNGH_CODICE 5
#define LUNGH_MAX_STUDENTI 100

typedef struct {
    char nome[LUNGH_MAX_NOME];
    char cognome[LUNGH_MAX_COGNOME];
    char titolo_tesi[LUNGH_MAX_TITOLOTESI];
    enum materie {
        Informatica = 1,
        Biotecnologie,
        IngegneriaMeccanica,
        IngegneriaGestionale,
        IngegneriaInformatica,
        Psicologia
    } mat;
    char parole_chiave[LUNGH_MAX_PAROLA];
    char parole_chiave1[LUNGH_MAX_PAROLA];
    char parole_chiave2[LUNGH_MAX_PAROLA];
    unsigned int anno_accademico; 
    unsigned int anno_accademico2;
    char abstract[LUNGH_MAX_ABSTRACT];
    char relatore[LUNGH_MAX_COGNOME];
    unsigned int n_tesi;
    float voto;
    unsigned int totale;
    unsigned int totdownload;
    unsigned int totdownloadvot;
    unsigned int cancellato;
} studente;

#endif


