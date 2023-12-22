 
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
#include <semaphore.h>

#include "structure.h"
#include "afiichage.c"

void remiseAZero(struct Pilote *pilotes, int taille) {
    for (int i = 0; i < taille; ++i) {
        memset(&pilotes[i], 0, sizeof(struct Pilote));
    }
}

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
    remiseAZero(listePilotes,21);
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
    sem_t semaphore;
    // printf("shmid = %d",shmid);
    // struct Pilote listeAffichage[20];
    if (sem_init(&semaphore, 1, 1) == -1)
    {
        perror("Initialisation du sémaphore échoué");
        exit(EXIT_FAILURE);
    }
    int nombreQ = 0;
    int tempsEnMoins = 0;
    int accessQ = 0;
    for(int j = 0; j<3;j++){
        while(accessQ != 1){
            printf("%d\n",20-nombreQ);
            
            printf("écrivez 1 si vous voulez commencer la qualification %d :",j+1);
            scanf("%d",&accessQ);

            }
            accessQ = 0;
        
            for(int k = 0; k < 15-nombreQ ; k++){
                        listePilotes[k].temps = 0;
                        listePilotes[k].tempsTour[0] = 0;
                        listePilotes[k].tempsTour[1] = 0;
                        listePilotes[k].tempsTour[2] = 0;

            }
            listePilotes[21].temps = 0;
            listePilotes[21].tempsTour[0] = 0;
            listePilotes[21].tempsTour[1] = 0;
            listePilotes[21].tempsTour[2] = 0;
        for (int i = 0; i < 18 - tempsEnMoins; i++)
        {
            for (int i = 0; i < indicePilote - nombreQ; i++){
            // sleep(10);
            int totalF = 0;
            int a = 0;
            //usleep(1000000);
            p_id = fork();
            if (p_id == 0){
                srand(time(NULL)*getpid());
                sem_wait(&semaphore);
                while (a < 3){ 
                int random = rand() % 20001;
                int finaleR = 25000 + random;
                totalF += finaleR;
                
                if (listePilotes[21].tempsTour[a] > finaleR || listePilotes[21].tempsTour[a] == 0){listePilotes[21].tempsTour[a] = finaleR;}
                if (listePilotes[i].tempsTour[a] > finaleR || listePilotes[i].tempsTour[a] == 0){listePilotes[i].tempsTour[a] = finaleR;}
                //printf("%d ms        ",finaleR);
                a++;

                
                
                }
                if(listePilotes[21].temps > totalF || listePilotes[21].temps == 0){listePilotes[21].temps = totalF;}
                if(listePilotes[i].temps > totalF || listePilotes[i].temps == 0){listePilotes[i].temps = totalF;}
                sem_post(&semaphore);
                return 0;
            }

            else if (p_id < 0)
            {
                printf("pas bon erreur");
                return -1;
            }
            else
            {
                 sem_wait(&semaphore);

                sem_post(&semaphore);
                
            }
        while(p_id == waitpid(-1,NULL,0)){
            if(errno == ECHILD){
                break;
            }
        }
        qsort(listePilotes, 20-nombreQ, sizeof(struct Pilote), compare);
        afficherDonnees(listePilotes, 20-nombreQ);
        
        }
        printf("Qualif : %d",j+1);
        }
        if(nombreQ < 10){nombreQ+=5;}
        tempsEnMoins +=2;
        afficheMeilleurTemps(listePilotes,2);
    }
   afficherDonnees(listePilotes,20);
   printf("Qualif terminé\n");
   sem_destroy(&semaphore);
   shmdt(listePilotes);

   
}