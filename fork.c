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

struct Course{
        int num;
        char ville[100];
        char pays[100];
        char circuit[200];
        char taille[10]; 
        char gp[200];
        char date[100];
};


struct Pilote{
    int num;
    char prenom[50];
    char nom[50];
    char team[50];
    char bday[50];
    char nation[50];
    int tempsFinal;
    int tempsTour[3];
};

int compare(const void *a, const void *b){
	struct Pilote *piloteA = (struct Pilote *)a;
	struct Pilote *piloteB = (struct Pilote  *)b;

	return (piloteA->tempsFinal - piloteB->tempsFinal);
}


void afficheCourse(struct Course course){
    int num=course.num;
    char ville[100];
    strcpy(ville,course.ville);
    char pays[100];
    strcpy(pays,course.pays);
    char ci[200];
    strcpy(ci,course.circuit);
    char taille[10];
    strcpy(taille,course.taille);
    char gp[200];
    strcpy(gp,course.gp);
    char date[100];
    strcpy(date,course.date);
    printf("numéro course: %d\n",num);
    printf("ville course: %s\n",ville);
    printf("pays: %s\n",pays);
    printf("circuit: %s\n",ci);
    printf("taille circuit: %s\n",taille);
    printf("Grand prix: %s\n",gp);
    printf("Date: %s\n",date);
}

void affichePilote(struct Pilote pilote){
    int num = pilote.num;
    printf("Num du Pilote: %d\n",num);
    char prenom[50];
    strcpy(prenom,pilote.prenom);
    printf("Prénom du pilote: %s\n",prenom);
    char nom[50];
    strcpy(nom,pilote.nom);
    printf("Nom du pilote: %s\n",nom);
    char team[50];
    strcpy(team,pilote.team);
    printf("Equipe du coureur: %s \n",team);
    char bday[50];
    strcpy(bday,pilote.bday);
    printf("Date de naissance du Pilote: %s\n",bday);
    
}

void afficheTemps(struct Pilote pilote){
    int temps = pilote.tempsFinal;
    int num=pilote.num;
    //printf("temps du pilote:%d",temps);
    printf("Le temps final du pilote num %d est de : %d \n",num,temps);
    printf("Le temps du tour 1 : %d\n",pilote.tempsTour[0]);
    printf("Le temps du tour 2 : %d\n",pilote.tempsTour[1]);
    printf("Le temps du tour 3 : %d\n",pilote.tempsTour[2]);


}

int main(int argc,char **argv){
    FILE *file;
    //srand(time(NULL));
    struct stat fileStats;
    char *fileContent;
    char *listeCourses;
    //struct Course course;
    
    file=fopen("Listes_circuits_de_F1_2023.csv","r");
    if (file==NULL)
    {
        printf("pas lu");
        return 0;
    }
    // pour retrouver le file descriptor
    int f=fileno(file);
    int indice=0;
    fstat(f,&fileStats);
    off_t taille=fileStats.st_size;
    char *listeTemp= (char *)malloc(sizeof(char)*taille);
    struct Course *listeFinale = (struct Course*) calloc(taille,sizeof(struct Course));
    
    fgets(listeTemp,taille,file);

    while(fgets(listeTemp,taille,file)!= NULL){
        listeFinale[indice].num=atoi(strtok(listeTemp,";"));
        strcpy(listeFinale[indice].ville,strtok(NULL,";"));
        strtok(NULL,";");
        strcpy(listeFinale[indice].pays,strtok(NULL,";"));
        strcpy(listeFinale[indice].circuit,strtok(NULL,";"));
        strcpy(listeFinale[indice].taille,strtok(NULL,";"));
        strcpy(listeFinale[indice].gp,strtok(NULL,";"));
        strtok(NULL,";");
        strcpy(listeFinale[indice].date,strtok(NULL,";"));
        afficheCourse(listeFinale[indice]);
        indice++;
        
        if(feof(file)){
            break;
        }
    }
    
    FILE *filePilote;
    struct stat fileStatsPilote;
    char *filePiloteContent;
    filePilote = fopen("Liste_des_pilotes.csv","r");
    int numFilePilote = fileno(filePilote);
    fstat(numFilePilote,&fileStatsPilote);
    off_t tailleListePilote=fileStats.st_size;
    char *listeTempPilote= (char *)malloc(sizeof(char)*tailleListePilote);
    //struct Pilote *listePilotes = (struct Pilote*) calloc(tailleListePilote,sizeof(struct Pilote));
    int shmid = shmget(77,21*sizeof(struct Pilote),IPC_CREAT | 0666);
    struct Pilote *listePilotes = shmat(shmid,0,0);

    fgets(listeTempPilote,tailleListePilote,filePilote);
    
    int indicePilote = 0;
    int trash;
    
    while(fgets(listeTempPilote,tailleListePilote,filePilote) != NULL){
        printf("listeTempPilote : %s",listeTempPilote);
        trash=atoi(strtok(listeTempPilote,";"));
        printf("trash=%d",trash);
        //listePilotes[indice].num = atoi(strtok(listeTempPilote,";"));
        char * toto = strtok(NULL,";");
        printf("toto=%s\n",toto);
        printf("Appuyer sur une touche ici\n");
        listePilotes[indicePilote].num = atoi(toto);
        
        printf("toto=%s",toto);
        printf("Appuyer sur une touche ici\n");
            getchar();
            getchar();

        strcpy(listePilotes[indicePilote].prenom,toto);
        strcpy(listePilotes[indicePilote].nom,strtok(NULL,";"));
        strcpy(listePilotes[indicePilote].team,strtok(NULL,";"));
        
        strcpy(listePilotes[indicePilote].bday,strtok(NULL,";"));
        strcpy(listePilotes[indicePilote].nation,strtok(NULL,";"));
        
        affichePilote(listePilotes[indicePilote]);
        indicePilote++;
    }
    //printf(" test : %c",listePilotes[0].nom); pq pas bon ?
        int p_id;
        //printf("shmid = %d",shmid);
    //struct Pilote listeAffichage[20];

    for (int i=0;i<indicePilote;i++){
        
        
        sleep(2);
        int totalF = 0;
        int a = 0;
            
        
        p_id=fork();
        if (p_id == 0)
        {
            while(a < 3){
            srand(time(NULL));
			int random = rand() % 20001;
			int finaleR = 25000 + random;
            //printf("Appuyer sur une touche ici\n");
            //getchar();
            //getchar();
            listePilotes[i].tempsTour[a] = finaleR; 
			totalF += finaleR;
			//printf("%d ms        ",finaleR);
			a++;
            //sleep(10);
            
			}
            sleep(2);
		//listePilotes[i].id = i+1 ;
		listePilotes[i].tempsFinal = totalF;
        //usleep(1000000);
        
        
        return 0;
		//printf("%d\n",totalF);
        //dup2(fd[1],1);
        //afficheTemps(listePilotes[i]);
        //sleep();

        
        }

        else if(p_id < 0){printf("pas bon erreur");return -1;}
        else{
          //close(fd[1]);
          //wait(NULL);
          printf("Je suis le padré\n");
          char result[3000];
          //close(fd[1]);
          //read(fd[0],result,sizeof(result));
          //printf("%s",result);
          //affichePilote(listePilotes[i]);
          afficheTemps(listePilotes[i]);
          //sleep(2);
          
        }
        //affichePilote(listePilotes[i]);
        //afficheTemps(listePilotes[i]);
        
        
    }
    shmdt(listePilotes);
    
}