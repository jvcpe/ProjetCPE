#include <stdarg.h>
#include <stdio.h>
#include "bsscanf.h"
#include "Putchar_Getchar.h"

int puissance(int nombre, int exposant)
{
    int i=1;

    if (exposant==0)
        return 1;

    for (i=1; i<exposant; i++)
    {
        nombre *= nombre;
    }
    return nombre;
}
/*
int bsscanf(char *stream, char *format, ...)    // à améliorer : virer le tableau de pointeurs et mettre ...
{
    va_list ap; // pointe vers l'argument, <==> iArgs

		char test[40];
    int nbArgLu=0;

    int compteurNombre=0;
    int produit=1;
    int somme=0;

    int indiceChaine=0;
    char *pChaine;

    char *pChar;

    char *iStream = stream;
    char *iFormat = format;
	
		va_start(ap, *format); // indique le dernier paramètre obligatoire

    sprintf (test,"Chaine format : %s\n\n", iFormat);
		Send_String(0,test);
    while(*iFormat != '\0') // on parcourt tout le format
    {
        sprintf(test,"\nformat : %c ==> ", *iFormat);
			Send_String(0,test);
        if (*iFormat != '%') // si le caractère ne fait pas partie d'un format (%c, %d...)
        {
            sprintf(test,"caractere useless\n");
					Send_String(0,test);
            sprintf(test,"iStream : %c\n", *iStream);
					Send_String(0,test);
            while (*iFormat != *iStream)    // tant qu'on élimine pas les caractères "inutiles" du format ou fin de chaine stream
            {
                iStream++;
                sprintf(test,"iStream : %c\n", *iStream);
							Send_String(0,test);
                if (*iStream == '\0') // on arrive à la fin du stream
                    return nbArgLu;
            }
            iStream++; // pour bien éliminer le caractère que l'on a trouvé
            sprintf(test,"iStream : %c\n", *iStream);
						Send_String(0,test);
        }

        else        // on vient d'arriver à un %
        {
            sprintf(test,"POURCENT ==> ");
					Send_String(0,test);
            iFormat++;  // on regarde la caractère après le %

            switch (*iFormat)
            {
            case 'c':   // un caractère
                sprintf(test,"c ==> %c\n", *iStream);
						Send_String(0,test);
                pChar = va_arg(ap, char*);
                sprintf(test,"%c\n",*pChar);
						Send_String(0,test);
                *pChar = *iStream;
                sprintf(test,"%c\n",*pChar);
						Send_String(0,test);
                nbArgLu++;
                break;

            case 'C':   // un caractère autre que espace
                //printf("c ==> %c\n", *iStream);
                while(*iStream == ' ')  // on dégage les espaces
                    iStream++;
                pChar = va_arg(ap, char*);
                //printf("%p\n",pChar);
                *pChar = *iStream;
                nbArgLu++;
                break;


            case 's':   // une chaine de caractères
                //printf("s\n");
                pChaine=va_arg(ap, char*); // contient l'adresse d'une chaine
                while(*iStream == ' ')  // on dégage les espaces
                    iStream++;
                //printf("plus d'espace : %s\n", iStream);

                while (*iStream != ' ' && *iStream != '\0')    // tant qu'on est pas arrivé à un espace
                {
                   // printf("Entree boucle\t %s", pChaine);
                    *(pChaine+indiceChaine) = *iStream;
                    //printf("iStream : %c, **pChaine : %c\n", *iStream, *pChaine);
                    iStream++;
                    indiceChaine++;
                }
                *(pChaine+indiceChaine)='\0';   // fin de chaine de caractère ajoutée manuellement
                nbArgLu++;
                indiceChaine=0;
                //printf("CHAINE : %s\n",*iArgs);
                break;

            case 'd':   // un entier decimal int
                sprintf(test,"d ==> \n");
						Send_String(0,test);
                while(*iStream < '0' || *iStream > '9')  // on dégage les char diff d'un chiffre
                    iStream++;
                while (*iStream >= '0' && *iStream <= '9')    // tant qu'on est pas arrivé à un espace
                {
                    sprintf(test,"n : %c\n", *iStream);
									Send_String(0,test);
                    iStream++;
                    compteurNombre++;
                }

                somme=0;  // la valeur de l'entier est mise à 0
                while(compteurNombre>0)
                {
                    produit = (*(iStream-compteurNombre)-48) * puissance(10,compteurNombre-1);
                    somme += produit;
                    compteurNombre--;
                }
                *va_arg(ap, int*) = somme;
                nbArgLu++;
                compteurNombre=0; // on le remet à zero pour plus tard
                break;

            case 'b':   // un entier decimal BYTE (char)
                //printf("d ==> \n");
                while(*iStream < '0' || *iStream > '9')  // on dégage les char diff d'un chiffre
                    iStream++;
                while (*iStream >= '0' && *iStream <= '9')    // tant qu'on est pas arrivé à un espace
                {
                    //printf("n : %c\n", *iStream);
                    iStream++;
                    compteurNombre++;
                }

                somme=0;  // la valeur de l'entier est mise à 0
                while(compteurNombre>0)
                {
                    produit = (*(iStream-compteurNombre)-48) * puissance(10,compteurNombre-1);
                    somme += produit;
                    compteurNombre--;
                }
                *va_arg(ap, char*) = somme;
                nbArgLu++;
                compteurNombre=0; // on le remet à zero pour plus tard
                break;
								
						case 'u':   // un entier decimal  unsigned BYTE (char)
                //printf("d ==> \n");
                while(*iStream < '0' || *iStream > '9')  // on dégage les char diff d'un chiffre
                    iStream++;
                while (*iStream >= '0' && *iStream <= '9')    // tant qu'on est pas arrivé à un espace
                {
                    //printf("n : %c\n", *iStream);
                    iStream++;
                    compteurNombre++;
                }

                somme=0;  // la valeur de l'entier est mise à 0
                while(compteurNombre>0)
                {
                    produit = (*(iStream-compteurNombre)-48) * puissance(10,compteurNombre-1);
                    somme += produit;
                    compteurNombre--;
                }
                *va_arg(ap, unsigned char*) = somme;
                nbArgLu++;
                compteurNombre=0; // on le remet à zero pour plus tard
                break;

            case '?':   // test la présence d'un caractère
                iFormat++;  // pointe le caractère en question
                pChar = va_arg(ap, char*);
                if (*iFormat == *iStream)
                {
                    *pChar = *iStream;
                }
                nbArgLu++;
                break;
            }
        }

        iFormat++;  // caractère suivant
    }
    va_end(ap);
    //printf("%p ==> %c\n",pChar,*pChar);
    return nbArgLu;
}*/
/*
int main()
{
    //char buffer[40]="RA : chaine A";
    char buffer[100]="RA chaine A:300\r NABIL : 7";
    char chaine[40]="test",chaine2[40];
    char AB = 'B', GD = 'G';
    char nabil=0;
    int angle=500;

    /*void * tab[40];// = malloc(5*sizeof(void*));
    tab[0] = (void*)chaine;
    tab[1] = (void*)&GD;
    tab[2] = (void*)&AB;
    tab[3] = (void*)&angle;
    tab[4] = (void*)chaine2;
    tab[5] = (void*)&nabil;

    ///bsscanf(buffer, "RA %s%?D %C:%d\r%s %b", chaine, &GD, &AB, &angle, chaine2, &nabil);
    //printf("%p ==> %c\n",&GD, GD);
    //bsscanf(buffer,"RA %s %c %c:%d %s", chaine, &GD, &AB, &angle, chaine2);
    //printf("chaine: %s, GD : %c, AB : %c angle : %d chaine2 : %s", chaine, GD, AB, angle, chaine2);
    ///printf("String : %s, GD : %c, char : %c angle : %d chaine 2 :%s %d\n", chaine, GD, AB, angle, chaine2, nabil);
    //free(tab);
   /* while(1);
    return 0;
}*/
int bsscanf(char *stream, char *format, void **args)    // à améliorer : virer le tableau de pointeurs et mettre ...
{
//	char test[40];
    int nbArgLu=0;
    int compteurNombre=0;
    int produit=1;
    int indiceChaine=0;

    char *iStream = stream;
    char *iFormat = format;
    char **iArgs = args;

    //char testiargs='z';

    //sprintf (test,"\nChaine format : %s\n\n", iFormat);
		//Send_String(0,test);
		//sprintf (test,"\nChaine commande : \n%s\n\n", iStream);
		//Send_String(0,test);

    while(*iFormat != '\0') // on parcourt tout le format
    {
       // printf("\nformat : %c ==> ", *iFormat);
        if (*iFormat != '%') // si le caractère ne fait pas partie d'un format (%c, %d...)
        {
            //printf("caractere useless\n");
            //printf("iStream : %c\n", *iStream);
            while (*iFormat != *iStream)    // tant qu'on élimine pas les caractères "inutiles" du format ou fin de chaine stream
            {
                iStream++;
                //printf("iStream : %c\n", *iStream);
                if (*iStream == '\0') // on arrive à la fin du stream
                    return nbArgLu;
            }
            iStream++; // pour bien éliminer le caractère que l'on a trouvé
            //printf("iStream : %c\n", *iStream);
        }

        else        // on vient d'arriver à un %
        {
            //printf("POURCENT ==> ");
            iFormat++;  // on regarde la caractère après le %

            switch (*iFormat)
            {
            case 'c':   // un caractère
                //printf("c ==> %c\n", *iStream);
                **iArgs = *iStream;
                iArgs++;
                nbArgLu++;
                break;

            case 'C':   // un caractère autre que espace
                //printf("c ==> %c\n", *iStream);
                while(*iStream == ' ')  // on dégage les espaces
                    iStream++;
                **iArgs = *iStream;
                iArgs++;
                nbArgLu++;
                break;


            case 's':   // une chaine de caractères
                //printf("s\n");
                while(*iStream == ' ')  // on dégage les espaces
                    iStream++;
                while (*iStream != ' ' && *iStream != '\0')    // tant qu'on est pas arrivé à un espace
                {
                    *(*iArgs+indiceChaine) = *iStream;
                 //   printf("iStream : %c, **iArgs : %c\n", *iStream, **iArgs);
                    iStream++;
                    indiceChaine++;
                }
                *(*iArgs+indiceChaine)='\0';   // fin de chaine de caractère ajoutée manuellement
                iArgs++;
                nbArgLu++;
                indiceChaine=0;
                //printf("CHAINE : %s\n",*iArgs);
                break;

            case 'd':   // un entier decimal
                //sprintf(test,"\nd ==>  %s\n", iStream);
								//Send_String(0,test);
						
                while(*iStream < '0' || *iStream > '9')  // on dégage les espaces
                    iStream++;
                while (*iStream >= '0' && *iStream <= '9')    // tant qu'on est pas arrivé à un espace
                {
                  //  sprintf(test, "n : %c\n", *iStream);
									//	Send_String(0,test);
                    iStream++;
                    compteurNombre++;
                }

                **iArgs=0;  // la valeur de l'entier est mise à 0
                while(compteurNombre>0)
                {
                    produit = (*(iStream-compteurNombre)-48) * puissance(10,compteurNombre-1);
                    **iArgs += produit;
                    compteurNombre--;
                }

                iArgs++;
                nbArgLu++;
                compteurNombre=0; // on le remet à zero pour plus tard
                break;

            case '?':   // test la présence d'un caractère
                iFormat++;  // pointel e caractère en question
                if (*iFormat == *iStream)
                {
                    **iArgs = *iStream;
                }
                iArgs++;
                nbArgLu++;
                break;
            }
        }

        iFormat++;  // caractère suivant
    }

    return nbArgLu;
}

