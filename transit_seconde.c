#include <stdlib.h>
#include <stdio.h>


void lap_time_format(int lap_time){
    int min = lap_time/ (60 * 1000);
    int s = (lap_time % (60 * 1000))/1000;
    int ms = lap_time % 1000;

    printf("%d:%02d.%03d", min, s, ms);
}
void sector_time_format(int sector_time){
    int s = (sector_time % (601000)) / 1000;
    int ms = sector_time % 1000;

    printf("%02d.%03d", s, ms);
}

