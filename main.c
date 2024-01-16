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
#include "afiichage.h"

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
        return piloteB->nbrTour - piloteA->nbrTour;
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
        listeFinale[indice].tour = atoi(strtok(NULL, ";"));
        //afficheCourse(listeFinale[indice]);
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
    remiseAZero(listePilotes,22);
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
        //affichePilote(listePilotes[indicePilote]);
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
for(int z = 0;z <indice;z++){
/*-------------------------------------------choix de la course-----------------------------------------*/

    printf("choissisez le numéro du grand Prix de formule 1 \n");
    for(int i = 0 ;i < indice ; i++){
        printf("%d   %s\n",i+1,listeFinale[i].circuit);
    }
    int choixCourse;
    printf("Si vous ne voulez pas faire de course choisisez le chifffre 23\nVotre choix:");
    scanf("%d",&choixCourse);

/*----------------------------------------------choix du démarage du GP----------------------------------------------*/
    int nombreQ = 0;
    int tempsEnMoins = 0;
    int choix;
    int jqualif =0;
    int bessaie = 0;
    printf("choisissez un chiffre entre :\n1 : pour commencer avec l'essaie 1\n2 : pour commencer avec l'essaie 2\n3 : pour commencer avec l'essaie 3\n4 : pour commencer avec la quallification 1\n5 : pour commencer avec la quallification 2\n6 : pour commencer avec la quallification 3\n7 : pour commencer la course\n Mettez un autre chiffre si vous voulez Quitter.\nVotre choix : ");
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
            bessaie = 1;
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

/*-------------------------------------------Essaie---------------------------------------------------------*/

int choixE;
for(int b = bessaie; b<3;b++){
        
        for (int o = 0; o < 6 ; o++)
        {
            usleep(500000);
            
            for (int i = 0; i < indicePilote; i++){
            // sleep(10);
            int totalF = 0;
            int a = 0;
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
                if(listePilotes[i].bestTemps > totalF || listePilotes[i].bestTemps == 0){listePilotes[i].bestTemps = totalF;}
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
        qsort(listePilotes, 20, sizeof(struct Pilote), compare);
        afficherDonnees(listePilotes, 20,b);
        
        
        }
        //printf("Qualif : %d",j+1);
        }
        
        afficheMeilleurTemps(listePilotes,3);
        while(choixE != 1){
            
            printf("écrivez 1 si vous voulez terminer l'essaie' %d :",b+1);
            scanf("%d",&choixE);

            }
        for(int k = 0; k < 21 ; k++){
                        listePilotes[k].temps = 0;
                        listePilotes[k].tempsTour[0] = 0;
                        listePilotes[k].tempsTour[1] = 0;
                        listePilotes[k].tempsTour[2] = 0;
                        listePilotes[k].bestTemps = 0;
           

            }
        
        listePilotes[21].temps = 0;
        listePilotes[21].tempsTour[0] = 0;
        listePilotes[21].tempsTour[1] = 0;
        listePilotes[21].tempsTour[2] = 0;
        choixE = 0;

       /* while (choixYes != "oui" || b < 2)
        {
            printf("Voulez vous faire l'essaie %d. Répondez par oui/non!!",b+2);
            scanf("%c",choixYes);
            if(choixYes == "non"){
                b +=1;
            }
        }*/
        

    }

/*------------------------------------------------Qualification ----------------------------------------------------*/
    int choixQ;
    for(int j = jqualif; j<3;j++){
        
            
        
        for (int o = 0; o < 6 - tempsEnMoins; o++)
        {
            usleep(500000);
            for (int i = 0; i < indicePilote - nombreQ; i++){
            // sleep(10);
            int totalF = 0;
            int a = 0;
            
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
                if(listePilotes[i].bestTemps > totalF || listePilotes[i].bestTemps == 0){listePilotes[i].bestTemps = totalF;}  
                listePilotes[i].nbrTour +=1;
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
        afficheMeilleurTemps(listePilotes,3);
        
        }
        //printf("Qualif : %d",j+1);
        }
        if(nombreQ < 10){nombreQ+=5;}
        tempsEnMoins +=2;

        while(choixQ != 1){
            
            printf("écrivez 1 si vous voulez terminer la qualification %d :",j+1);
            scanf("%d",&choixQ);

            }
            for(int k = 0; k < 15-nombreQ ; k++){
                        listePilotes[k].temps = 0;
                        listePilotes[k].tempsTour[0] = 0;
                        listePilotes[k].tempsTour[1] = 0;
                        listePilotes[k].tempsTour[2] = 0;
                        listePilotes[k].bestTemps = 0;
                        listePilotes[k].nbrTour = 0;

            }
            listePilotes[21].temps = 0;
            listePilotes[21].tempsTour[0] = 0;
            listePilotes[21].tempsTour[1] = 0;
            listePilotes[21].tempsTour[2] = 0;
            choixQ = 0;

    }
   afficherDonnees(listePilotes,20,6);
   afficheMeilleurTemps(listePilotes,3);
   
        while(choixQ != 1){
            printf("Fin de la qualification!\nécrivez 1 si vous voulez terminer la qualification de la course:");
            scanf("%d",&choixQ);
        }
            

/*------------------------------------------------Course---------------------------------------------------*/

    
        for (int j = 0; j < listeFinale[choixCourse-1].tour; j++){
            for (int i = 0; i < indicePilote; i++){
                // sleep(10);
                int totalF = 0;
                int a = 0;
                //usleep(500000);
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
                    if(listePilotes[i].bestTemps > totalF || listePilotes[21].bestTemps == 0){listePilotes[i].bestTemps = totalF;}
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
            
            
            }
            usleep(500000);
            qsort(listePilotes, 20, sizeof(struct Pilote), compare);
            afficherDonnees(listePilotes, 20,6);
            afficheMeilleurTemps(listePilotes, 3);
        }
    listePilotes[0].pointPilote += 25;
    listePilotes[1].pointPilote += 18;
    listePilotes[2].pointPilote += 15;
    listePilotes[3].pointPilote += 12;
    listePilotes[4].pointPilote += 10;
    listePilotes[5].pointPilote += 8;
    listePilotes[6].pointPilote += 6;
    listePilotes[7].pointPilote += 4;
    listePilotes[8].pointPilote += 2;
    listePilotes[9].pointPilote += 1;

    for(int i = 0;i<10;i++){

        if(listePilotes[i].bestTemps == listePilotes[21].temps){listePilotes[i].pointPilote += 1;}
    }
    affichePoint(listePilotes, 20);
}
   sem_destroy(&semaphore);
   shmdt(listePilotes);

   
}