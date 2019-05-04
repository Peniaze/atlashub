#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "atlas.h"

int zakladni_menu(void)
{
    system("cls");
    printf("Interaktivní atlas hub\n\n1: Listuj v atlase\n2: Hledej v atlase\n3: Dopln atlas\n4: Uloz atlas do souboru\n\n5: Opusti program\n\n Volba: \n");
    int volba = 0;
    fflush(stdin);
    scanf("%d", &volba);
    switch (volba)
    {
	case 1:
	    listuj(atlas[0]);
	    break;
	case 2:
	    if (!hledej())
		uvolni_filter();
	    break;
	case 3:
	    pridej_polozku();
	    break;
	case 4:
	    uloz_do_souboru();
	    break;
	case 5:
	    return 1;
	default:
	    system("cls");
	    printf("Spatná volba");
	    Sleep(3000);
    }
    return 0;
}




int main()
{
    FILE* subor;

    int counter = 0;
    subor = fopen("atlas.txt", "r");
    char buff[1024];
    while (fgets(buff, 1024, subor))
    {
	counter++;
    }
    rewind(subor);
    int i;
    for (i=0; i<counter; i++)
    {
	atlas[i] = malloc(sizeof(t_huba));
	fscanf(subor, "%50[^,],%d,%20[^,],%d; ", atlas[i]->nazev, &atlas[i]->jedovatost, atlas[i]->barva, &atlas[i]->vyskyt);
	pocet_polozek++;
	if (i==0)
	{
	    atlas[i]->dalsi = 0;
	    atlas[i]->predchadzjici = 0;
	}
	else
	{
	    atlas[i]->predchadzjici = atlas[i-1];
	    atlas[i-1]->dalsi = atlas[i];
	    atlas[i]->dalsi = 0;
	}
    }

    printf("%d", counter);
    fclose(subor);
    while (!zakladni_menu());
   // printf("Hello world!\n");
    for (i=0; i<pocet_polozek; i++)
    {
	free(atlas[i]);
    }
    return 0;
}
