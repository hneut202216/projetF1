 
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

#include "structure.h"
#include "afiichage.c"


int compare(const void *a, const void *b) {
    struct Pilote *piloteA = (struct Pilote *)a;
    struct Pilote *piloteB = (struct Pilote *)b;
    if(piloteA->temps == 0){return 0;}
    if(piloteB->temps == 0){return 0;}

    return (piloteA->temps - piloteB->temps);
}

int main(int argc, char **argv) {
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
    // struct Pilote *listePilotes = (struct Pilote*) calloc(tailleListePilote,sizeof(struct Pilote));
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
    // printf("shmid = %d",shmid);
    // struct Pilote listeAffichage[20];
    for (int i = 0; i < indicePilote; i++)
    {
        int totalF = 0;
        int a = 0;
        usleep(1000000);
        srand(time(NULL));
        p_id = fork();
        if (p_id == 0)
        {
            while (a < 3)
        {

            int random = rand() % 20001;
            int finaleR = 25000 + random;
            totalF += finaleR;
            listePilotes[i].tempsTour[a] = finaleR;
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
        srand(time(NULL));

        while(p_id == waitpid(-1,NULL,0)){
                if(errno == ECHILD){
                        break;
                }
        }
        qsort(listePilotes, indicePilote+1, sizeof(struct Pilote), compare);
        afficherDonnees(listePilotes, 20);

        }

    shmdt(listePilotes);
}