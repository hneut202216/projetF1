#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "transit_seconde.c"

#define RESET   "\x1b[0m"
#define BLACK   "\x1b[30m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define WHITE   "\x1b[37m"


#define BG_BLACK      "\x1b[40m"
#define BG_RED        "\x1b[41m"
#define BG_GREEN      "\x1b[42m"
#define BG_YELLOW     "\x1b[43m"
#define BG_BLUE       "\x1b[44m"
#define BG_MAGENTA    "\x1b[45m"
#define BG_CYAN       "\x1b[46m"
#define BG_WHITE      "\x1b[47m"

void afficheMeilleurTemps(struct Pilote pilotes[],int lignes){
    printf("\n\n%s",MAGENTA);
    int colonnes = 4;
    int largeurs[colonnes];
    char* titres[] = {"Meilleur temps" , "Meilleurs Secteur 1", "Meilleurs Secteur 2" , "Meilleurs Secteur 3" };
    //char* repTemps[] = { pilotes[21].temps,pilotes[21].tempsTour[1],pilotes[21].tempsTour[2],pilotes[21].tempsTour[3]};
    for(int j = 0; j < colonnes; ++j){
        largeurs[j] = strlen(titres[j]);
    }
    for (int i = 0; i < lignes; ++i) {
        if (strlen(pilotes[i].nom) > largeurs[1]) {
            largeurs[1] = strlen(pilotes[i].nom);
        }
        for (int j = 0; j < 3; ++j) {
            int longueur = snprintf(NULL, 0, "%d", pilotes[i].tempsTour[j]);
            if (longueur > largeurs[j + 2]) {
                largeurs[j + 2] = longueur;
            }
        }
        int longueur = snprintf(NULL, 0, "%d", pilotes[i].temps);
        if (longueur > largeurs[4]) {
            largeurs[4] = longueur;
        }
    }

        printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    printf("|");
    for (int j = 0; j < colonnes; ++j) {
        printf("%-*s |", largeurs[j], titres[j]);
    }
    printf("\n");

    printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    
    printf("|");
    lap_time_format(pilotes[21].temps);
    printf("       |"),
    sector_time_format(pilotes[21].tempsTour[0]);
    printf("              |");
    sector_time_format(pilotes[21].tempsTour[1]);
    printf("              |");
    sector_time_format(pilotes[21].tempsTour[2]);
    printf("              |");
    
    printf("\n");

        
        printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n%s",RESET);
        
}
void afficherDonnees(struct Pilote pilotes[], int lignes) {
	system("clear");

    int colonnes = 7; // Nombre de colonnes
    int largeurs[colonnes];
	char* titres[] = {"Classement", "Nom du Pilote", "Temps 1", "Temps 2", "Temps 3", "Temps du tour","Difference"};
    for (int j = 0; j < colonnes; ++j) {
        largeurs[j] = strlen(titres[j]);
    }

    for (int i = 0; i < lignes; ++i) {
        if (strlen(pilotes[i].nom) > largeurs[1]) {
            largeurs[1] = strlen(pilotes[i].nom);
        }
        for (int j = 0; j < 3; ++j) {
            int longueur = snprintf(NULL, 0, "%d", pilotes[i].tempsTour[j]);
            if (longueur > largeurs[j + 2]) {
                largeurs[j + 2] = longueur;
            }
        }
        int longueur = snprintf(NULL, 0, "%d", pilotes[i].temps);
        if (longueur > largeurs[4]) {
            largeurs[4] = longueur;
        }
    }

    printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    printf("|");
    for (int j = 0; j < colonnes; ++j) {
        printf("%-*s |", largeurs[j], titres[j]);
    }
    printf("\n");

    printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");

    for (int i = 0; i < lignes; ++i) {
        char* color = "";
        if(strcmp(pilotes[i].team,"Red Bull") == 0){
            color = BG_BLUE;
            }
        if(strcmp(pilotes[i].team , "Williams") == 0){color =BG_CYAN ;}
        if(strcmp(pilotes[i].team , "AlphaTauri") == 0){color =BG_BLACK;}
        if(strcmp(pilotes[i].team,"McLaren")==0){color =BG_YELLOW;}
        if(strcmp(pilotes[i].team , "Alpine")==0){color =BG_BLUE;}
        if(strcmp(pilotes[i].team ,"Aston Martin") ==0){color =BG_GREEN;}
        if(strcmp(pilotes[i].team, "Ferrari")==0){color = BG_RED;}
        if(strcmp(pilotes[i].team , "Haas")==0){color =BG_BLUE;}
        if(strcmp(pilotes[i].team, "Alfa Romeo")==0){color =BG_RED;}
        if(strcmp(pilotes[i].team, "Mercedes")==0){color =BG_BLUE;}
        printf("%s|",color);
        printf("%-*d |", largeurs[0], i+1 );
        printf("%-*s |", largeurs[1], pilotes[i].nom);
        for (int j = 0; j < 3; ++j) {
            sector_time_format(pilotes[i].tempsTour[j]);
            printf("  |");
        }

        lap_time_format(pilotes[i].temps);
        printf("      |");
        if(i == 0){sector_time_format(0);
                    printf("     |%s\n",RESET);}
        else if(pilotes[i].temps == 0){lap_time_format(pilotes[i-1].temps);
                    printf("    |%s\n",RESET);}
        else{
            int diff = pilotes[i-1].temps - pilotes[i].temps;
            sector_time_format(-diff);
            printf("     |%s\n",RESET);}

        if (i < lignes - 1) {
            printf("+");
            for (int j = 0; j < colonnes; ++j) {
                for (int k = 0; k < largeurs[j] + 1; ++k) {
                    printf("-");
                }
                printf("+");
            }
            printf("\n");
        }
    }

    printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
}

void afficheCourse(struct Course course) {
    int num = course.num;
    char ville[100];
    strcpy(ville, course.ville);
    char pays[100];
    strcpy(pays, course.pays);
    char ci[200];
    strcpy(ci, course.circuit);
    char taille[10];
    strcpy(taille, course.taille);
    char gp[200];
    strcpy(gp, course.gp);
    char date[100];
    strcpy(date, course.date);
    printf("numéro course: %d\n", num);
    printf("ville course: %s\n", ville);
    printf("pays: %s\n", pays);
    printf("circuit: %s\n", ci);
    printf("taille circuit: %s\n", taille);
    printf("Grand prix: %s\n", gp);
    printf("Date: %s\n", date);
}

void affichePilote(struct Pilote pilote) {
    int num = pilote.num;
    printf("Num du Pilote: %d\n", num);
    char prenom[50];
    strcpy(prenom, pilote.prenom);
    printf("Prénom du pilote: %s\n", prenom);
    char nom[50];
    strcpy(nom, pilote.nom);
    printf("Nom du pilote: %s\n", nom);
    char team[50];
    strcpy(team, pilote.team);
    printf("Equipe du coureur: %s \n", team);
    char bday[50];
    strcpy(bday, pilote.bday);
    printf("Date de naissance du Pilote: %s\n", bday);
}

void afficheTemps(struct Pilote pilote) {
    int temps = pilote.temps;
    int num = pilote.num;
    // printf("temps du pilote:%d",temps);
    printf("Le temps du pilote num %d est de : %d \n", num, temps);
    printf("Le temps du tour 1 : %d\n",pilote.tempsTour[0]);
    printf("Le temps du tour 2 : %d\n",pilote.tempsTour[1]);
    printf("Le temps du tour 3 : %d\n",pilote.tempsTour[2]);
}