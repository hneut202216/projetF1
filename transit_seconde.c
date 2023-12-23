
#include <stdio.h>
#include <string.h>


/*void lap_time_format(int lap_time){
    int min = lap_time/ (60 * 1000);
    int s = (lap_time % (60 * 1000))/1000;
    int ms = lap_time % 1000;

    printf("%d:%02d.%03d", min, s, ms);
}*/
char* lap_time_format(int lap_time){
    static char formatted_time[12]; // Déclare une chaîne de caractères statique pour stocker le temps formaté

    int min = lap_time / (60 * 1000);
    int s = (lap_time % (60 * 1000)) / 1000;
    int ms = lap_time % 1000;

    // Formatage du temps dans la chaîne de caractères statique
    sprintf(formatted_time, "%d:%02d.%03d", min, s, ms);

    return formatted_time;
}
/*void sector_time_format(int sector_time){
    int s = (sector_time % (601000)) / 1000;
    int ms = sector_time % 1000;

    printf("%02d.%03d", s, ms);
}*/
char* sector_time_format(int sector_time){
    static char formatted_time[8]; // Déclare une chaîne de caractères statique pour stocker le temps formaté

    int s = (sector_time % (60 * 1000)) / 1000;
    int ms = sector_time % 1000;

    // Formatage du temps dans la chaîne de caractères statique
    sprintf(formatted_time, "%02d.%03d", s, ms);

    return formatted_time;
}