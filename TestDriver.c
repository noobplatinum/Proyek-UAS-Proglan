#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_hotel(int floors, int rooms) 
{
    // Print base floor
    if(rooms % 2 != 0) 
    {
        rooms++;
    }
    
    printf("|");
    for (int i = 0; i < rooms* 3 - 1; i++) 
    {
        printf(" ");
    }
    printf("|\n");

    printf("|");
    for (int i = 0; i < rooms* 3 - 1; i++) 
    {
        printf("=");
    }
    printf("|\n");


    printf("+");
    for (int i = 0; i < rooms* 3 - 1; i++) 
    {
        printf("-");
    }
    printf("+\n");

    // Print each floor
    for (int i = 0; i < floors; i++) {
        // Print windows
        for (int j = 0; j < rooms / 2; j++) {
            printf("| --- ");
        }
        printf("|\n");

        for (int j = 0; j < rooms / 2; j++) {
            printf("| | | ");
        }
        printf("|\n");

        for (int j = 0; j < rooms / 2; j++) {
            printf("| --- ");
        }
        printf("|\n");

        // Print floor separator
        printf("+");
        for (int j = 0; j < rooms* 3 - 1; j++) {
            printf("-");
        }
        printf("+\n");
    }

    // Print base floor with windows
    for (int j = 0; j < rooms / 2; j++) {
        printf("|  _  ");
    }
    printf("|\n");

    for (int j = 0; j < rooms / 2; j++) {
        printf("| | | ");
    }
    printf("|\n");

    for (int j = 0; j < rooms / 2; j++) {
        printf("| |_| ");
    }
    printf("|\n");

    // Print floor separator
    printf("+");
    for (int j = 0; j < rooms * 3 - 1; j++) {
        printf("-");
    }
    printf("+\n");
}

int main() {
    print_hotel(5, 7);
    return 0;
}