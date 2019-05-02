#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "atlas.h"

int zakladne_menu(void)
{
    system("cls");
    printf("Interaktivny atlas hub\n\n1: Listuj v zozname\n2: Hladaj v atlase\n3: Zorad a vypis\n4: Dopln atlas\n5: Uloz atlas do suboru\n\n6: Opusti program\n\n Volba: \n");
    int volba = 0;
    fflush(stdin);
    scanf("%d", &volba);
    switch (volba)
    {
	case 1:
	    listuj(atlas[0]);
	    break;
	case 2:
	    if (!hladaj())
		uvolni_filter();
	    break;
	case 3:
	    break;
	case 4:
	    pridaj_polozku();
	    break;
	case 5:
	    uloz_do_suboru();
	    break;
	case 6:
	    return 1;
	default:
	    system("cls");
	    printf("Wrong input");
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
	fscanf(subor, "%50[^,],%d,%20[^,],%d; ", atlas[i]->nazov, &atlas[i]->jedovatost, atlas[i]->farba, &atlas[i]->vyskyt);
	pocet_poloziek++;
	if (i==0)
	{
	    atlas[i]->dalsi = 0;
	    atlas[i]->predchadzjuci = 0;
	}
	else
	{
	    atlas[i]->predchadzjuci = atlas[i-1];
	    atlas[i-1]->dalsi = atlas[i];
	    atlas[i]->dalsi = 0;
	}
    }

    printf("%d", counter);
    fclose(subor);
    while (!zakladne_menu());
   // printf("Hello world!\n");
    for (i=0; i<pocet_poloziek; i++)
    {
	free(atlas[i]);
    }
    return 0;
}
