#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include <wchar.h>
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
typedef struct date
{
  int j;
  int m;
  int an;
} date;
typedef struct temps
{
  int heure;
  int minute;
} temps;
typedef struct voyage
{
  int num;
  char arriv[100];
  char depart[100];
  char airport[100];
  float prix;
  date datedep;
  temps tdep;
  temps tarr;
  temps duree;
} voyage;

void ajout (voyage t[], int *n);

void affiche (voyage t[], int NUM, int n);

void supprime (voyage t[], int *n);

void modif (voyage t[], int n, int NUM);

void recherche (voyage t[], int n, date d1, date d2);

int smaller(date a,date b);

void show_all(voyage t[],int n);


int
main ()
{
  int n = 0, p = 0, NUM;
  voyage t[100];
  date d1, d2;
  do
    {
         HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }
      printf("\n");
      wprintf(L"\x1b[31;32;33;34;35;36;101;102;103;104;105;106;107m\r\n");
      printf ("Bienvenue! Veuillez choisir un numero:\n");
      printf ("1 Ajouter un voyage\n");
      printf ("2 Afficher la description d un voyage\n");
      printf ("3 Supprimer un voyage\n");
      printf ("4 Modifier un voyage\n");
      printf
	("5 Recherche des voyages disponibles selon des dates precises\n");
	printf ("6 Afficher toutes les voyages \n");
      printf ("7 Quitter le programme\n");
      printf
	("------------------------------------------------------------------------\n");
      printf ("Tapez votre numero choisi :");
      scanf ("%d", &p);

      switch (p)
	{
	case 1:
	  {
	    system ("cls");
	    ajout (t, &n);
        break;
	  }
	case 2:
	  {
	    system ("cls");
	    printf ("Donner numero de voyage :\n");
	    scanf ("%d", &NUM);
	    affiche (t, NUM, n);
	    break;
	  }
	case 3:
	  {
	    system ("cls");
	    supprime (t, &n);
	    break;
	  }
	case 4:
	  {
	    system ("cls");
	    printf ("Donner numero de voyage correspondant :\n");
	    scanf ("%d", &NUM);
	    modif (t, n, NUM);
	    break;
	  }
	case 5:
	  {
	    system ("cls");
	    printf ("Donner la premiere date: (sous la forme ../../....)\n");
	    scanf ("%d/%d/%d", &d1.j, &d1.m, &d1.an);
	    printf ("Donner la deuxieme date: (sous la forme ../../....)\n");
	    scanf ("%d/%d/%d", &d2.j, &d2.m, &d2.an);
	    recherche (t, n, d1, d2);
	    break;
	  }
	  case 6:{
	      system ("cls");
          show_all(t,n);
	      break;
	  }
	case 7:
	  {
	    system ("cls");
	    printf ("AU REVOIR !\n");
	    exit(1);
	    break;
	  }
	default:
	  {
	    printf ("Desole, erreur de saisie ...");
	    break;
	  }
	}
    }
  while (1);
  return 0;
}

void
affiche (voyage t[], int NUM, int n)
{
  int i = 0,tr=0;
  for (i = 0; i < n; i++)
    {
      if (t[i].num == NUM)
	{
	    tr=1;
	  printf ("Voici la description du voyage num %d:\n", n);
	  printf ("* Ville de Depart: %s\n", t[i].depart);
	  printf ("* Ville d'Arrivee: %s\n", t[i].arriv);
	  printf ("* Airport: %s\n", t[i].airport);
	  printf ("* Prix du Voyage: %.2f DT \n", t[i].prix);
	  printf ("* Date de Depart: %d/%d/%d\n", t[i].datedep.j,
		  t[i].datedep.m, t[i].datedep.an);
	  printf ("* Temps de Depart: %d:%d\n", t[i].tdep.heure,
		  t[i].tdep.minute);
	  printf ("* Temps d'Arrivee: %d:%d\n", t[i].tarr.heure,
		  t[i].tarr.minute);
	  printf ("* Duree du Voyage: %d h et %d min", t[i].duree.heure,
		  t[i].duree.minute);
	  break;
	}
    }
    if (tr==0){
  printf ("Voyage n'existe pas...");}
  getch ();
}

int smaller(date a,date b){
    if(a.an < b.an) return 1;//comparer les annees
    if (a.an==b.an && a.m<b.m) return 1;//comparer les mois mais aussi verifier si les annees sont egales
    if (a.an==b.an && a.m==b.m && a.j<b.j)return 1;//comparer les jours mais aussi verifier si les annees et les mois sont egales
    return 0;
}

void
supprime (voyage t[], int *n)
{
  int NUM, i = 0;
  int trouve = 0;
  printf ("Donner le numero de voyage que vous voulez supprimer:\n");
  scanf ("%d", &NUM);
  for (i = 0; i < *n; i++)
    {
      if (t[i].num == NUM)
	{
	  trouve = 1;
	  break;
	}
    }
  if (trouve)
    {
      for (int k = i; k < *n; k++)
	{
	  t[k] = t[k + 1];
	}
      *n--;
      printf ("Suppression complete");
    }
  else
    {
      printf ("Numero de voyage invalide");
    }
  getch ();
}

void
recherche (voyage t[], int n, date d1, date d2)
{
  int k = 1,tr=0;
  for (int i = 0; i < n; i++)
    {

      if (smaller(d1,t[i].datedep) && smaller(t[i].datedep,d2))
	{
	  tr=1;
	  printf ("%d)  Voyage num %d le %d/%d/%d\n", k, t[i].num,
		  t[i].datedep.j, t[i].datedep.m, t[i].datedep.an);
	  affiche (t, t[i].num, n);
	  k++;
	  printf ("\n");
	}
    }
    if (tr==0){
        printf ("Pas de voyages entre ces deux dates,Desole.\n");
    }
  getch ();
}

void
ajout (voyage t[], int *n)
{
  t[*n].num = *n + 1;
  printf ("Ville de Depart: ");
  scanf ("%s", t[*n].depart);
  printf ("Ville d'Arrivee: ");
  scanf ("%s", t[*n].arriv);
  printf ("Airport: ");
  scanf ("%s", t[*n].airport);
  printf ("Date de Depart: (sous forme de ../../....)\n");
  scanf ("%d/%d/%d", &t[*n].datedep.j, &t[*n].datedep.m, &t[*n].datedep.an);
  printf ("Temps de Depart: (sous forme de ..:..)\n ");
  scanf ("%d:%d", &t[*n].tdep.heure, &t[*n].tdep.minute);
  printf ("Temps d Arrivee: (sous forme de ..:..)\n");
  scanf ("%d:%d", &t[*n].tarr.heure, &t[*n].tarr.minute);
  printf ("Duree : (sous forme de ..:..)\n ");
  scanf ("%d:%d", &t[*n].duree.heure, &t[*n].duree.minute);
  printf ("Prix: ");
  scanf ("%f", &t[*n].prix);
  (*n)++;
  printf ("DONE!\n");
  getch ();
}

void
modif (voyage t[], int n, int NUM)
{
  int k, i, ch;
  int tr = 0;
  for (i = 0; i < n; i++)
    {
      if (t[i].num == NUM)
	{
	  tr = 1;
	  k = i;
	  break;
	}
    }
  if (tr == 0)
    {
      printf (" N'EXISTE PAS !! ");
    }
    while (ch!=8)
    {
  printf ("Que voulez-vous modifier ?\n");
  printf ("1* Ville de Depart \n ");
  printf ("2* Ville d'Arrivee \n ");
  printf("3* Airport \n");
  printf ("4* Date de Depart \n ");
  printf ("5* Temps de Depart \n ");
  printf ("6* Temps d'Arrivee \n ");
  printf ("7* Duree \n ");
  printf ("8* Prix \n ");
  printf ("9* Exit \n");
  printf ("Votre Choix:");
  scanf ("%d", &ch);
      switch (ch)
	{
	case 1:
	  {printf ("Ville de Depart : ");
	  fflush (stdin);
	  gets (t[k].depart);
	  printf ("DONE!\n");
	  break;}
	case 2:
	  {printf ("Ville d'Arrivee : ");
	  fflush (stdin);
	  gets (t[k].arriv);
	  printf ("DONE!\n");
	  break;}
    case 3:
        {
            printf("Airport : ");
            fflush (stdin);
	        gets (t[k].airport);
	        printf ("DONE!\n");
	        break;
        }
	case 4:
	  {printf ("Date de Depart : (sous forme de ../../....)\n");
	  fflush (stdin);
	  scanf ("%d/%d/%d", &t[k].datedep.j, &t[k].datedep.m,
		 &t[k].datedep.an);
		 printf ("DONE!\n");
	  break;}
	case 5:
	  {printf ("Temps de Depart : (sous forme de ..:..)\n");
	  scanf ("%d:%d", &t[k].tdep.heure, &t[k].tdep.minute);
	  printf ("DONE!\n");
	  break;}
	case 6:
	  {printf ("Temps d Arrivee : (sous forme de ..:..)\n");
	  scanf ("%d:%d", &t[k].tarr.heure, &t[k].tarr.minute);
	  printf ("DONE!\n");
	  break;}
	case 7:
	  {printf ("Duree: (sous forme de ..:..)\n");
	  scanf ("%d:%d", &t[k].duree.heure, &t[k].duree.minute);
	  printf ("DONE!\n");
	  break;}
	case 8:
	  {printf ("Prix: ");
	  scanf ("%f", &t[k].prix);
	  printf ("DONE!\n");
	  break;}
    case 9:
        {
            break;
        }
    default:
        {
            printf("Erreur de Saisie...");
            break;
        }
	}
    }

}

void show_all(voyage t[], int n){
int i;
for(i=0;i<n;i++){
    printf("Voyage Num %d:\n",t[i].num);
    printf("Ville de Depart:%s \n",t[i].depart);
    printf("Ville d'Arrivee:%s \n",t[i].arriv);
    printf("Airport:%s \n",t[i].airport);
    printf("Prix: %.2f DT \n",t[i].prix);
    printf("Date de Depart :%d/%d/%d \n",t[i].datedep.j,t[i].datedep.m,t[i].datedep.an);
    printf("Temps de Depart: %d:%d \n",t[i].tdep.heure,t[i].tdep.minute);
    printf("Temps d Arrivee: %d:%d \n",t[i].tarr.heure,t[i].tarr.minute);
    printf("Duree: %d:%d \n",t[i].duree.heure,t[i].duree.minute);
    printf("------------------------------------------------------- \n");

}}
