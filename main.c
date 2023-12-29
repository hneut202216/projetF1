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
    
    // Comparaison par le nombre de tours
    if (piloteA->nbrTour != piloteB->nbrTour) {
        return piloteA->nbrTour - piloteB->nbrTour;
    } else {
        // En cas d'égalité du nombre de tours, comparer par le temps
        if (piloteA->temps == 0 || piloteB->temps == 0) {
            return 0; // Gérer le cas où le temps est nul
        }
        return piloteA->temps - piloteB->temps;
    }
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
    
        listeFinale[indice].nbrTours = atoi(strtok(NULL, ";"));
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
    int choix;
    int jqualif =0;
    int bessaie = 0;
    printf("choisissez un chiffre entre :\n1 : pour commencer l'essaie 1\n2 : pour commencer l'essaie 2\n3 : pour commencer l'essaie 3\n4 : pour commencer avec la quallification 1\n5 : pour commencer avec la quallification 2\n6 : pour commencer avec la quallification 3\n7 : pour commencer la course\n Mettez un autre chiffre si vous voulez Quitter.\nVotre choix : ");
    scanf("%d",&choix);
    switch(choix){
        case 1:
            nombreQ = 0;
            tempsEnMoins =0;
            jqualif =0;
            bessaie = 0;
            break;
        case 2:
            nombreQ = 0;
            tempsEnMoins =0;
            jqualif =0;
            bessaie= 1;
            break;
        case 3:
            nombreQ = 0;
            tempsEnMoins =0;
            jqualif =0;
            bessaie = 2;
            break;
        case 4:
            nombreQ = 0;
            tempsEnMoins =0;
            jqualif =0;
            bessaie = 3;
            break;
        case 5:
            nombreQ = 5;
            tempsEnMoins =2;
            jqualif =1;
            bessaie = 3;
            break;
        case 6:
            nombreQ = 10;
            tempsEnMoins =4;
            jqualif =2;
            bessaie = 3;
            break;
        case 7 :
            jqualif = 3;
            bessaie = 3;
            break;
        default:
            return -1;
    }
       //int accessQ = 0;
    for(int b = bessaie; b<3;b++){
        //accessQ = 0;
            for(int k = 0; k < 20 ; k++){
                        listePilotes[k].temps = 0;
                        listePilotes[k].tempsTour[0] = 0;
                        listePilotes[k].tempsTour[1] = 0;
                        listePilotes[k].tempsTour[2] = 0;

            }
        
        for (int o = 0; o < 10 - tempsEnMoins; o++)
        {
            for (int i = 0; i < 20 ; i++){
            // sleep(10);
            int totalF = 0;
            int a = 0;
            usleep(200000);
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
        qsort(listePilotes, 20, sizeof(struct Pilote), compare);
        afficherDonnees(listePilotes, 20,b);
        
        }
        //printf("Qualif : %d",j+1);
        }
        if(nombreQ < 10){nombreQ+=5;}
        tempsEnMoins +=2;
        afficheMeilleurTemps(listePilotes,2);
        /*while(accessQ != 1){
            
            printf("écrivez 1 si vous voulez terminer la qualification %d :",j+1);
            scanf("%d",&accessQ);

            }*/
            
            listePilotes[21].temps = 0;
            listePilotes[21].tempsTour[0] = 0;
            listePilotes[21].tempsTour[1] = 0;
            listePilotes[21].tempsTour[2] = 0;
            sleep(4);
            if(b>2){
                nombreQ = 0;
                tempsEnMoins =0;
                jqualif =0;
                afficherDonnees(listePilotes,20,b);
                printf("êtes vous prét pour les qualification?(appuyer sur Enter , ctrl + c pour quitter)");
                scanf("%lc",&choix);
                }
    }
    
    for(int j = jqualif; j<3;j++){
        //accessQ = 0;
            for(int k = 0; k < 15-nombreQ ; k++){
                        listePilotes[k].temps = 0;
                        listePilotes[k].tempsTour[0] = 0;
                        listePilotes[k].tempsTour[1] = 0;
                        listePilotes[k].tempsTour[2] = 0;

            }
        
        for (int o = 0; o < 18 - tempsEnMoins; o++)
        {
            for (int i = 0; i < indicePilote - nombreQ; i++){
            // sleep(10);
            int totalF = 0;
            int a = 0;
            usleep(200000);
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
        afficherDonnees(listePilotes, 20-nombreQ,j+3);
        
        }
        //printf("Qualif : %d",j+1);
        }
        if(nombreQ < 10){nombreQ+=5;}
        tempsEnMoins +=2;
        afficheMeilleurTemps(listePilotes,2);
        /*while(accessQ != 1){
            
            printf("écrivez 1 si vous voulez terminer la qualification %d :",j+1);
            scanf("%d",&accessQ);

            }*/
            
            listePilotes[21].temps = 0;
            listePilotes[21].tempsTour[0] = 0;
            listePilotes[21].tempsTour[1] = 0;
            listePilotes[21].tempsTour[2] = 0;
            sleep(4);
    }
   afficherDonnees(listePilotes,20,6);
   printf("Qualif terminé\n");
   /*printf("écrivez 1 si vous voulez terminer la qualification la course:");
            scanf("%d",&accessQ);

            
            accessQ = 0;*/

    
        for (int i = 0; i < 20; i++){
            for (int i = 0; i < indicePilote; i++){
                // sleep(10);
                int totalF = 0;
                int a = 0;
                usleep(200000);
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
                    if(listePilotes[i].meilleurTemps > totalF || listePilotes[i].meilleurTemps== 0){listePilotes[i].meilleurTemps = totalF;}
                    listePilotes[i].temps += totalF;
                    listePilotes[i].nbrTour += 1;
                    sem_post(&semaphore);
                    return 0;
                }

                else if (p_id < 0)
                {
                    printf("pas bon erreur");
                    return -1;
                }
                    sem_wait(&semaphore);

                    sem_post(&semaphore);
                    
            while(p_id == waitpid(-1,NULL,0)){
                if(errno == ECHILD){
                    break;
                }
            }
            afficherDonnees(listePilotes, 20,6);
            
            afficheMeilleurTemps(listePilotes, 2);
            }
            qsort(listePilotes, 20, sizeof(struct Pilote), compare);
            afficherDonnees(listePilotes, 20,6);
            
            afficheMeilleurTemps(listePilotes, 2);
            affichePoint(listePilotes,20);
            
        }
        
        for(int i = 0 ; i<20 ;i++){

            
            printf("coucou");
            if(i = 0){listePilotes[i].point += 25;}
            if(i = 1){listePilotes[i].point += 18;}
            if(i = 2){listePilotes[i].point += 15;}
            if(i = 3){listePilotes[i].point += 12;}
            if(i = 4){listePilotes[i].point += 10;}
            if(i = 5){listePilotes[i].point += 8;}
            if(i = 6){listePilotes[i].point += 6;}
            if(i = 7){listePilotes[i].point += 4;}
            if(i = 8){listePilotes[i].point += 2;}
            if(i = 9){listePilotes[i].point += 1;}
            //if((i <= 9 )&& (listePilotes[21].temps = listePilotes[i].temps)){listePilotes[i].point += 1;}
            if((i>9)){listePilotes[i].point += 0;}
        }
        affichePoint(listePilotes,20);

   sem_destroy(&semaphore);
   shmdt(listePilotes);

   
}