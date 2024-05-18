#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct room
{
    int number;
    char type[20];
    char status[10];
    int days;
    int maxguests;
    int price;
    struct room *next;
};

struct floor
{
    int number;
    int rooms;
    struct room *headroom;
    struct floor *next;
};

struct customer
{
    char name[50];
    char status[20];
    int age;
    struct customer *left;
    struct customer *right;
}; 

struct roomtype
{
    char type[20];
    int price;
    int maxguests;
    int amount;
    struct roomtype *next;
};


int main() 
{
    return 0;
}