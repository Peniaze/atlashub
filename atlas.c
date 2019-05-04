#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include "atlas.h"



t_akce vyber() //vrací enumerativni typ možností kláves výbìru akcí

{
int ch1=0, ch2 =0; // musi byt integer, nikoli char
fflush(stdin);
ch1 = getch();
ch2 = 0;
if (ch1 == 0xE0)
    {
    ch2 = getch();

   switch(ch2)
        {
        case 72: return nahoru;//sipka nahoru
        case 80: return dolu;//sipka dolu
        case 75: return doleva;//sipka doleva
        case 77: return doprava;//sipka doprava
        // zde je mozne pridat dalsi varianty specialnich znaku, PgUp, PgDn, End atd...
        };
    }
else
    {
        switch (ch1)
        {
        case 'd': return pridat;
        case 'q': return odejit;
        case 13: return enter;
        }
    }
return pridat;
}

int hledej(void)
{
    char vyraz[50];
    system("cls");
    printf("Zadaj vyraz na vyhladanie: ");
    fflush(stdin);
    scanf("%50[^\n]", vyraz);
    t_huba* polozka = atlas[0];
    int i=0;
    while (polozka)
    {
	if (strstr(polozka->nazev, vyraz) || strstr(polozka->barva, vyraz))
	{
	    filter[i] = malloc(sizeof(t_huba));
	    (*filter[i]) = (*polozka);
	    if (i == 0)
	    {
		filter[i]->predchadzjici = 0;
		filter[i]->dalsi = 0;
	    }
	    else
	    {
		filter[i]->predchadzjici = filter[i-1];
		filter[i]->dalsi = 0;
		filter[i-1]->dalsi = filter[i];
	    }
	    i++;
	}
	    

	polozka = polozka->dalsi;
    }
    printf("Bolo najdenych %d poloziek obsahujucich '%s'", i, vyraz);
    Sleep(3000);
    if (i == 0)
	return 1;
    listuj(filter[0]);
    return 0;
}


void uvolni_filter(void)
{
    t_huba* polozka = filter[0];
    while (polozka->dalsi)
    {
	polozka = polozka->dalsi;
	free(polozka->predchadzjici);
    }
    free(polozka);
}


void vypis_polozku(t_huba* polozka)
{
    printf("Nazov huby: %s\n", polozka->nazev);
    switch (polozka->jedovatost)
    {
	case 0:
	    printf("Tato huba je jedovata.\n");
	    break;
	case 1:
	    printf("Tato huba je jedla.\n");
	    break;
	case 2:
	    printf("Tato huba nie je jedla.\n");
	    break;
    }
    printf("Farba klobuka: %s\nHuba sa najcastejsie vyskytuje v mesiaci ", polozka->barva);	
    switch (polozka->vyskyt)
    {
	case 1:printf("Leden.\n");break;
	case 2:printf("Unor.\n");break;
	case 3:printf("Brezen.\n");break;
	case 4:printf("Duben.\n");break;
	case 5:printf("Kveten.\n");break;
	case 6:printf("Cerven.\n");break;
	case 7:printf("Cervenec.\n");break;
	case 8:printf("Srpen.\n");break;
	case 9:printf("Zari.\n");break;
	case 10:printf("Rijen.\n");break;
	case 11:printf("Listopad.\n");break;
	case 12:printf("Prosinec.\n");break;
    }
    printf("\n\n");
    if (polozka->dalsi)
	printf("Nasledujici huba -> %s\n", (polozka->dalsi)->nazev);
    if (polozka->predchadzjici)
	printf("Predchadzajici huba -> %s\n", (polozka->predchadzjici)->nazev);
}

void listuj(t_huba* prva_polozka)
{
    t_huba* polozka = prva_polozka;
    t_akce key;
    do
    {
	system("cls");
	printf("Stiskni 'q' pro opusteni\nStiskni 'd' pro vymazani polozky\n\n");
	vypis_polozku(polozka);
	key = vyber();
	if ((key == nahoru) && (polozka->predchadzjici))
	    polozka = polozka->predchadzjici;
	if ((key == dolu) && (polozka->dalsi))
	    polozka = polozka->dalsi;
	if (key == pridat)
	{
	    if (polozka->dalsi)
	    {
		polozka = polozka->dalsi;
		vymaz_polozku(polozka->predchadzjici);
	    }
	    else
	    {
		polozka = polozka->predchadzjici;
		vymaz_polozku(polozka->dalsi);
	    }
	}
    } while(key != odejit);
}



void uloz_do_souboru(void)
{
    FILE* subor;
    subor = fopen("atlas.txt", "w");
    for (int i=0; i<pocet_polozek; i++)
    {
	fprintf(subor, "%s,%d,%s,%d;\n", atlas[i]->nazev, (atlas[i]->jedovatost), atlas[i]->barva, (atlas[i]->vyskyt));
    }
    fclose(subor);
}

void vymaz_polozku(t_huba* polozka)
{
    if (polozka->dalsi)
	(polozka->dalsi)->predchadzjici = polozka->predchadzjici;
    else
	(polozka->predchadzjici)->dalsi = 0;
    if (polozka->predchadzjici)
	(polozka->predchadzjici)->dalsi = polozka->dalsi;
    else
	(polozka->dalsi)->predchadzjici = 0;
    free(polozka);
    polozka = 0;
    pocet_polozek--;
}


void pridej_polozku(void)
{
    atlas[pocet_polozek] = malloc(sizeof(t_huba));
    system("cls");
    printf("Pridej polozku.\n\nNazev huby:");
    char buff[50];
    fflush(stdin);
    scanf("%50[^\n]", buff);
    strcpy(atlas[pocet_polozek]->nazev, buff);
    printf("Jedovata: \n");
    char temp_jedovatost = 0;
    t_akce key;
   do
    {
         switch (temp_jedovatost)
	{
	    case 0: printf ("\b\b\b\b\b\b\b\b        \b\b\b\b\b\b\b\bjedovata"); break;
	    case 1: printf ("\b\b\b\b\b\b\b\b        \b\b\b\b\b\b\b\bjedla"); break;
	    case 2:printf ("\b\b\b\b\b\b\b\b        \b\b\b\b\b\b\b\bnejedla"); break;
	}
        key=vyber();
        if ((key==nahoru)&&(temp_jedovatost>0)) temp_jedovatost--;
        if ((key==dolu)&&(temp_jedovatost<2)) temp_jedovatost++;
    }
    while (key!=enter);
    atlas[pocet_polozek]->jedovatost = temp_jedovatost;
    printf("\nBarva: ");
    scanf("%20[^\n]", atlas[pocet_polozek]->barva);
    printf("Mesic vyskytu: ");
    scanf("%d", &(atlas[pocet_polozek]->vyskyt));
    printf("%s",atlas[pocet_polozek]->nazev);
    atlas[pocet_polozek]->predchadzjici = atlas[pocet_polozek-1];
    atlas[pocet_polozek]->dalsi = 0;
    atlas[pocet_polozek-1]->dalsi = atlas[pocet_polozek];
    pocet_polozek++;
    return;
}
