#ifndef ATLAS_H
#define ATLAS_H


typedef enum  {nahoru,dolu,doprava,doleva,pridat,smazat,odejit,enter} t_akce;

typedef struct t_huba
{
    char nazev[50];
    int jedovatost;
    char barva[20];
    int vyskyt;
    struct t_huba* dalsi;
    struct t_huba* predchadzjici;
} t_huba;

t_huba* atlas[100];
t_huba* filter[100];
int pocet_polozek;

void listuj(t_huba*);
int zakladni_menu(void);
int hledej(void);
void uvolni_filter(void);
void pridej_polozku(void);
void vymaz_polozku(t_huba* polozka);
void vypis_polozku(t_huba* polozka);
void uloz_do_souboru(void);

#endif
