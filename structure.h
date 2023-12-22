#ifndef STRUCTURES_H
#define STRUCTURES_H

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
    int nbrTour;
};

#endif