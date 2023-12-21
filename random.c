#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*void tricroissant( int a[1000][1000], int b )
{
    int x=0;
    int i=0;
    int j=0;
    for(i=0;i<b;i++)
    {
        	for(j=1;j<b;j++)
        	{
            		if(a[i][1]<a[j][1])
            		{
                		x=a[i][0];
                		a[i][0]=a[j][0];
                		a[j][0]=x;
                		//j--;
                	}

        	}

	}

    x=a[0][0];
    for(i=0;i<b;i++){
	//printf("a[i][0] = %d    a[i +1][0]= %d\n",a[i][0],a[i+1][0]);
    	a[i][0]=a[i+1][0];
    	a[b-1][0]=x;
	}

}*/

typedef struct{
	int temps;
	int id;
}personne;

int compare(const void *a, const void *b){
	personne *personneA = (personne *)a;
	personne *personneB = (personne *)b;

	return (personneA->temps - personneB->temps);
}
int main(){


//	int total[1000][1000] ;
	personne list[20];
	srand(time(NULL));
	printf("secteur1	secteur2	secteur3	total\n");
	for(int i = 0;i < 20;i++)
		{
		int totalF = 0;
		int a = 0;
		while(a < 3){
			int random = rand() % 20001;
			int finaleR = 25000 + random;
			totalF += finaleR;
			printf("%d ms        ",finaleR);
			a++;
			}
		list[i].id = i ;
		list[i].temps = totalF;
		printf("%d\n",totalF);
		}
//	tricroissant(total,20);

	qsort(list,20,sizeof(personne),compare);
	for(int o = 0; o<20 ;o++){
	printf("la place numero %d a fait un temps de %d\n",list[o].id,list[o].temps);

	}
	return 0;
}