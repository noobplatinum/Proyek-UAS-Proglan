// Proyek UAS Pemrograman Lanjut - Sistem Keuangan dan Struktural Hotel
// Kelompok 05
// Anggota:
// 1. Adi Nugroho (2306208546)
// 2. Jesaya David Gamalael N P (2306161965)
// 14 Mei 2024
// Versi 1.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
#include <strings.h>
#include <time.h>
#include <ctype.h>

struct room
{
    int number;
    int guestcount;
    char type[20];
    char status[10];
    int price;
    int days;
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

int main(void)
{
    int opsiA, opsiB, opsiC;

    int floor, room;
    FILE *file = fopen("structure.txt", "r");
    if(file == NULL)
    {
        printf("File tidak ditemukan!\n");
        return 1;
    }
    fscanf(file, "%d,%d", &floor, &room);
    fclose(file);

    struct floor *head = NULL;
    struct room *headroom = NULL;

    int counter = 0;

    do 
    {
        menu(); //memanggil fungsi menu
        do 
        {
            scanf("%d", &opsiA);
            if(opsiA < 1 || opsiA > 6) 
            {
                printf(" Opsi tidak valid!\n"); 
            } 
        } while(opsiA < 1 || opsiA > 6); //error handling

        switch(opsiA) 
        {
            case 1:
                if(counter <= 0)  //handling jika tidak ada node
                    {
                        printf(" Mohon isi nilai terlebih dahulu!\n");
                        system("pause");
                        system("cls");
                        break;
                    }
                    system("cls");
                    //menu
                    system("pause");
                    system("cls");
                    break;

            case 2:
                if(counter <= 0)  //handling jika tidak ada node
                {
                    printf(" Mohon isi nilai terlebih dahulu!\n");
                    system("pause");
                    system("cls");
                    break;
                }
                system("cls");
                //menu
                system("pause");
                system("cls");
                break;

            case 3:
            {
                if(counter <= 0)  //handling jika tidak ada node
                {
                    printf(" Mohon isi nilai terlebih dahulu!\n");
                    system("pause");
                    system("cls");
                    break;
                }
                system("cls");
                //menu
                system("pause");
                system("cls");
                break;
            }

            case 4:
                if(counter <= 0)  //handling jika tidak ada node
                {
                    printf(" Mohon isi nilai terlebih dahulu!\n");
                    system("pause");
                    system("cls");
                    break;
                }
                system("cls");
                //menu
                system("pause");
                system("cls");
                break;
        }
    } while(opsiA != 6); //keluar dari program
}

void menu(void)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                      HOTEL MANAGEMENT                     |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Daftar Opsi - = - = - = - = - = - = - = - = - = - = - = - |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 1 | Statistik Hotel                                       |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Manajemen Struktur                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Manajemen Keuangan                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 4 | Manajemen Customer                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 5 | Help                                                  |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 6 | Exit                                                  |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("|___________________________________________________________|\n");
    printf("| Masukkan Pilihan Anda: ");   
}

void menustruktur(int floor, int room)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                       STRUKTUR HOTEL                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Statistik Hotel - = - = - = - = - = - = - = - = - = - = - |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Lantai Hotel:                                      |\n");
    printf("| Jumlah Kamar per Lantai:                                  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Kamar Total:                                       |\n");
    printf("| Jumlah Kamar Tersedia:                                    |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Total Tamu:                                               |\n");
    printf("| Hotel Akan Kosong Dalam X Hari                            |\n");
    printf("+___+_______________________________________________________+\n");
    printf("| 1 | Ubah Jumlah Lantai Hotel                              |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Ubah Jumlah Kamar per Lantai                          |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Kembali                                               |\n"); 
    printf("+---+-------------------------------------------------------+\n");
    printf("| 4 | Reset Struktur Hotel                                  |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| Masukkan Pilihan Anda: ");
}

void statreader()
{

}

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
    for (int i = 0; i < floors; i++) 
    {
        // Print windows
        for (int j = 0; j < rooms / 2; j++) 
        {
            printf("| --- ");
        }
        printf("|\n");

        for (int j = 0; j < rooms / 2; j++) 
        {
            printf("| | | ");
        }
        printf("|\n");

        for (int j = 0; j < rooms / 2; j++) 
        {
            printf("| --- ");
        }
        printf("|\n");

        // Print floor separator
        printf("+");
        for (int j = 0; j < rooms* 3 - 1; j++) 
        {
            printf("-");
        }
        printf("+\n");
    }

    // Print base floor with windows
    for (int j = 0; j < rooms / 2; j++) 
    {
        printf("|  _  ");
    }
    printf("|\n");

    for (int j = 0; j < rooms / 2; j++) 
    {
        printf("| | | ");
    }
    printf("|\n");

    for (int j = 0; j < rooms / 2; j++) 
    {
        printf("| |_| ");
    }
    printf("|\n");

    // Print floor separator
    printf("+");
    for (int j = 0; j < rooms * 3 - 1; j++) 
    {
        printf("-");
    }
    printf("+\n");
}
