#ifndef ATLAS_H
#define ATLAS_H


typedef enum  {nahoru,dolu,doprava,doleva,pridat,smazat,odejit,enter} t_akce;

typedef struct t_huba
{
    char nazov[50];
    int jedovatost;
    char farba[20];
    int vyskyt;
    struct t_huba* dalsi;
    struct t_huba* predchadzjuci;
} t_huba;

t_huba* atlas[100];
t_huba* filter[100];
int pocet_poloziek;

void listuj(t_huba*);
int zakladne_menu(void);
int hladaj(void);
void uvolni_filter(void);
void pridaj_polozku(void);
void vypis_polozku(t_huba* polozka);
void uloz_do_suboru(void);

#endif
