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
    
    for(int j = 0; j < colonnes; ++j){
        largeurs[j] = strlen(titres[j]);
    } 
        for (int j = 0; j < 3; ++j) {
            int longueur = snprintf(NULL, 0, "%d", pilotes[21].tempsTour[j]);
            if (longueur > largeurs[j+1]) {
                largeurs[j+1] = longueur;
            }
        }
        int longueur = snprintf(NULL, 0, "%d", pilotes[21].temps);
        if (longueur > largeurs[0]) {
            largeurs[1] = longueur;
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

    
    char* bestTemps = lap_time_format(pilotes[21].temps);
    printf("|%s",bestTemps);
    for(int i = 0;i< largeurs[0] - strlen(bestTemps)+1; i++){printf(" ");}
    char* bestT1 = sector_time_format(pilotes[21].tempsTour[0]);
    printf("|%s",bestT1);
    for(int i = 0;i< largeurs[1] - strlen(bestT1)+1; i++){printf(" ");}
    char* bestT2 = sector_time_format(pilotes[21].tempsTour[1]);
    printf("|%s",bestT2);
    for(int i = 0;i< largeurs[2] - strlen(bestT2)+1; i++){printf(" ");}
    char* bestT3 = sector_time_format(pilotes[21].tempsTour[2]);
    printf("|%s",bestT3);
    for(int i = 0;i< largeurs[3] - strlen(bestT3)+1; i++){printf(" ");}
    printf("|");
    
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

/*void affichePoint(struct Pilote pilotes[],int lignes){
    char* titres[]={"Nom du Pilote","Points"};
    int colonnes = 2;
    int largeurs[colonnes];
    for (int j = 0; j < colonnes; ++j) {
        largeurs[j] = strlen(titres[j]);
    }
    for (int i = 0; i < lignes; ++i) {
        if(strlen(pilotes[i].nom)>largeurs[0]){
            largeurs[0] = strlen(pilotes[i].nom);
        };
        int longueurN = snprintf(NULL, 0, "%d", pilotes[i].point);
        if (longueurN > largeurs[1]) {
            largeurs[1] = longueurN;
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
    printf("|%-*s   |\n",largeurs[0]+largeurs[1],"Point");
    printf("+");
    for (int j = 0; j < colonnes; ++j) {
        for (int k = 0; k < largeurs[j] + 1; ++k) {
            printf("-");
        }
        printf("+");
    }
    printf("\n");
       for (int i = 0; i < lignes; ++i) {
        
        printf("|%-*s |", largeurs[0], pilotes[i].nom);
        
        
        printf("%d",pilotes[i].point);
        char str_point[20]; 
        sprintf(str_point, "%d", pilotes[i].point);
        for(int j = 0;j< largeurs[1] - strlen(str_point)+1; j++){printf(" ");}
        printf("|\n");
        
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
    
    
}*/

void afficherDonnees(struct Pilote pilotes[], int lignes, int typetourChiffre) {
	system("clear");
    char* TypeTour[] = {"Essaie 1","Essaie 2","Essaie 3","Qualif 1","Qualif 2","Qualif 3","Course  ",};

    int colonnes = 8; // Nombre de colonnes
    int largeurs[colonnes];
	char* titres[] = {"Classement", "Nom du Pilote", "Temps 1", "Temps 2", "Temps 3", "Temps du tour","Difference","nbr Tour"};
    for (int j = 0; j < colonnes; ++j) {
        largeurs[j] = strlen(titres[j]);
    }
    
    /*int maxTemps = strlen(titres[5]);
    for(int i = 0; i< lignes ; i++){
        
        int longueurTemps = strlen(pilotes[i].temps);

        if (longueurTemps > maxTemps) maxTemps = longueurTemps;
    }*/

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
        int longueurT = snprintf(NULL, 0, "%d", pilotes[i].temps);
        if (longueurT > largeurs[5]) {
            largeurs[5] = longueurT;
        }
        int longueurN = snprintf(NULL, 0, "%d", pilotes[i].nbrTour);
        if (longueurN > largeurs[7]) {
            largeurs[7] = longueurN;
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
    printf("|%-*s       |\n",largeurs[0]+largeurs[1]+largeurs[2]+largeurs[3]+largeurs[4]+largeurs[5]+largeurs[6]+largeurs[7]+largeurs[8],TypeTour[typetourChiffre]);
    

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

            char* tempsTour = sector_time_format(pilotes[i].tempsTour[j]);
            printf("%s",tempsTour);
            for(int i = 0;i< largeurs[j+2] - strlen(tempsTour)+1; i++){printf(" ");}
            printf("|");
        }

        char* temps = lap_time_format(pilotes[i].temps);
        printf("%s",temps);
        for(int i = 0;i< largeurs[5] - strlen(temps)+1; i++){printf(" ");}
        printf("|");

        if(i == 0){char* diff = sector_time_format(0);
                    printf("%s",diff);
                    for(int i = 0; i < largeurs[6] - strlen(diff)+1;i++){printf(" ");}
                    printf("|");}
        
        else if(pilotes[i].temps == 0){char* diff = lap_time_format(pilotes[i-1].temps);
                    printf("%s",diff);
                   for(int i = 0; i < largeurs[6] - strlen(diff)+1;i++){printf(" ");}
                    printf("|");
                   }
        
        else{
            int diffTemps = pilotes[i-1].temps - pilotes[i].temps;
            char* diff = sector_time_format(-diffTemps);
            printf("%s",diff);
            for(int i = 0; i < largeurs[6] - strlen(diff)+1;i++){printf(" ");}
            printf("|");}
        
        printf("%d",pilotes[i].nbrTour);
        char str_nbrTour[20]; 
        sprintf(str_nbrTour, "%d", pilotes[i].nbrTour);
        for(int j = 0;j< largeurs[7] - strlen(str_nbrTour)+1; j++){printf(" ");}
        printf("|%s\n",RESET);
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