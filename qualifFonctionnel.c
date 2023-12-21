#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>
struct Course
{
    int num;
    char ville[100];
    char pays[100];
    char circuit[200];
    char taille[10];
    char gp[200];
    char date[100];
};

struct Pilote
{
    int num;
    char prenom[50];
    char nom[50];
    char team[50];
    char bday[50];
    char nation[50];
    int temps;
    int tempsTour[3];
};

int compare(const void *a, const void *b)
{
    struct Pilote *piloteA = (struct Pilote *)a;
    struct Pilote *piloteB = (struct Pilote *)b;
    
    if (piloteA->temps == 0){return 0;}
    if (piloteB->temps == 0){return 0;}

    return (piloteA->temps - piloteB->temps);
}
void afficherDonnees(struct Pilote pilotes[], int lignes) {
	system("clear");

    int colonnes = 6; // Nombre de colonnes
    int largeurs[colonnes];
	char* titres[] = {"Classement", "Nom du Pilote", "Temps 1", "Temps 2", "Temps 3", "Temps 4"};
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
        printf("|");
        printf("%-*d |", largeurs[0], i+1 );
        printf("%-*s |", largeurs[1], pilotes[i].nom);
        for (int j = 0; j < 3; ++j) {
            printf("%-*d |", largeurs[j + 2], pilotes[i].tempsTour[j]);
        }
        printf("%-*d |", largeurs[4], pilotes[i].temps);
        printf("\n");

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

void afficheCourse(struct Course course)
{
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

void affichePilote(struct Pilote pilote)
{
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

void afficheTemps(struct Pilote pilote)
{
    int temps = pilote.temps;
    int num = pilote.num;
    // printf("temps du pilote:%d",temps);
    printf("Le temps du pilote num %d est de : %d \n", num, temps);
    printf("Le temps du tour 1 : %d\n",pilote.tempsTour[0]);
    printf("Le temps du tour 2 : %d\n",pilote.tempsTour[1]);
    printf("Le temps du tour 3 : %d\n",pilote.tempsTour[2]);
}

int main(int argc, char **argv)
{
    FILE *file;
    //srand(time(NULL));
    struct stat fileStats;
    char *fileContent;
    char *listeCourses;
    // struct Course course;

    file = fopen("Listes_circuits_de_F1_2023.csv", "r");
    if (file == NULL)
    {
        printf("pas lu");
        return 0;
    }
    // pour retrouver le file descriptor
    int f = fileno(file);
    int indice = 0;
    fstat(f, &fileStats);
    off_t taille = fileStats.st_size;
    char *listeTemp = (char *)malloc(sizeof(char) * taille);
    struct Course *listeFinale = (struct Course *)calloc(taille, sizeof(struct Course));

    fgets(listeTemp, taille, file);

    while (fgets(listeTemp, taille, file) != NULL)
    {
        listeFinale[indice].num = atoi(strtok(listeTemp, ";"));
        strcpy(listeFinale[indice].ville, strtok(NULL, ";"));
        strtok(NULL, ";");
        strcpy(listeFinale[indice].pays, strtok(NULL, ";"));
        strcpy(listeFinale[indice].circuit, strtok(NULL, ";"));
        strcpy(listeFinale[indice].taille, strtok(NULL, ";"));
        strcpy(listeFinale[indice].gp, strtok(NULL, ";"));
        strtok(NULL, ";");
        strcpy(listeFinale[indice].date, strtok(NULL, ";"));
        afficheCourse(listeFinale[indice]);
        indice++;

        if (feof(file))
        {
            break;
        }
    }

    FILE *filePilote;
    struct stat fileStatsPilote;
    char *filePiloteContent;
    filePilote = fopen("Liste_des_pilotes.csv", "r");
    int numFilePilote = fileno(filePilote);
    fstat(numFilePilote, &fileStatsPilote);
    off_t tailleListePilote = fileStats.st_size;
    char *listeTempPilote = (char *)malloc(sizeof(char) * tailleListePilote);
    //struct Pilote *listePilotes = (struct Pilote*) calloc(tailleListePilote,sizeof(struct Pilote));
    int shmid = shmget(77, 21 * sizeof(struct Pilote), IPC_CREAT | 0666);
    struct Pilote *listePilotes = shmat(shmid, 0, 0);

    fgets(listeTempPilote, tailleListePilote, filePilote);
    int indicePilote = 0;
    int trash;
    while (fgets(listeTempPilote, tailleListePilote, filePilote) != NULL)
    {
        trash = atoi(strtok(listeTempPilote, ";"));

        // listePilotes[indice].num = atoi(strtok(listeTempPilote,";"));
        listePilotes[indicePilote].num = atoi(strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].prenom, strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].nom, strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].team, strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].bday, strtok(NULL, ";"));
        strcpy(listePilotes[indicePilote].nation, strtok(NULL, ";"));
        affichePilote(listePilotes[indicePilote]);
        indicePilote++;
    }
    // printf(" test : %c",listePilotes[0].nom); pq pas bon ?
    int p_id;
	for(int i = 0; i < indicePilote ; i++){
                listePilotes[i].temps = 0;
                listePilotes[i].tempsTour[0] = 0;
                listePilotes[i].tempsTour[1] = 0;
                listePilotes[i].tempsTour[2] = 0;
    }
    
    int nombreQ = 0;
    int tempsEnMoins = 0;
   for(int i = 0; i<3;i++){
    for (int i = 0; i < 10 - tempsEnMoins; i++)
    {
        for (int i = 0; i < indicePilote - nombreQ; i++){
        // sleep(10);
        int totalF = 0;
        int a = 0;
        srand(time(NULL));
        usleep(900000);
        p_id = fork();
        if (p_id == 0){
            while (a < 3){ 
            int random = rand() % 20001;
            int finaleR = 25000 + random;
            totalF += finaleR;
            listePilotes[i].tempsTour[a] = finaleR;
            //printf("%d ms        ",finaleR);
            a++;
            
        }
            listePilotes[i].temps = totalF;
            return 0;
        }

        else if (p_id < 0)
        {
            printf("pas bon erreur");
            return -1;
        }
        else
        {
            
            char result[3000];
        }
	while(p_id == waitpid(-1,NULL,0)){
		if(errno == ECHILD){
			break;
		}
	}
	qsort(listePilotes, indicePilote+1, sizeof(struct Pilote), compare);
	afficherDonnees(listePilotes, 20-nombreQ);
    
    }
    printf("Qualif : %d",i);
    }
    if(nombreQ < 10){nombreQ+=5;}
    tempsEnMoins +=2;
   }
   printf("Qualif terminé");
   shmdt(listePilotes);

   
}
