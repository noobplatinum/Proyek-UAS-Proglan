// Proyek UAS Pemrograman Lanjut - Sistem Keuangan dan Struktural Hotel
// Kelompok 05
// Anggota:
// 1. Adi Nugroho (2306208546)
// 2. Jesaya David Gamalael N P (2306161965)
// 14 Mei 2024
// Versi 0.2 - Base Frame & Menus

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

    //make a head node for room types
    struct roomtype *headtype = NULL;
    //read roomtype.txt and store the data in the linked list with format "type,price,maxguests"
    FILE *file2 = fopen("roomtype.txt", "r");
    if(file2 == NULL)
    {
        printf("File tidak ditemukan!\n");
        return 1;
    }

    char type[20];
    int price, maxguests, amount;
    while(fscanf(file2, "%[^,],%d,%d,%d\n", type, &price, &maxguests, &amount) != EOF)
    {
        struct roomtype *newtype = (struct roomtype *)malloc(sizeof(struct roomtype));
        strcpy(newtype->type, type);
        newtype->price = price;
        newtype->maxguests = maxguests;
        newtype->amount = amount;
        newtype->next = NULL;

        if(headtype == NULL)
        {
            headtype = newtype;
        }
        else
        {
            struct roomtype *temp = headtype;
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newtype;
        }
    }

    struct floor *head = NULL;

    int totalrooms, totalguests, totaltypes, maxdays;

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
                    scanf("%d", &opsiB);
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
    printf("| 1 | Statistik Hotel                                       |\n"); //1 tentative
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Manajemen Struktur                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Manajemen Keuangan                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 4 | Manajemen Tamu                                        |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 5 | Help                                                  |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 6 | Exit                                                  |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("|___________________________________________________________|\n");
    printf("| Masukkan Pilihan Anda: ");   
}

void menustruktur(int floor, int room, int maxdays, int emptyrooms)
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
    printf("| Hotel Akan Kosong Dalam X Hari                            |\n");
    printf("+___+_______________________________________________________+\n");
    printf("| 1 | Ubah Jumlah Lantai Hotel                              |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Ubah Jumlah Kamar per Lantai                          |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Kembali                                               |\n"); 
    printf("+---+-------------------------------------------------------+\n");
    printf("| Masukkan Pilihan Anda: ");
}

void menutamu(int *totalguests, int *totalrooms)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                          DATA TAMU                        |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Statistik Tamu  - = - = - = - = - = - = - = - = - = - = - |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Tamu Hotel:                                        |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Tamu Dewasa:                                       |\n");
    printf("| Jumlah Tamu Remaja:                                       |\n");
    printf("| Jumlah Tamu Anak:                                         |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Tamu Pria:                                         |\n");
    printf("| Jumlah Tamu Wanita:                                       |\n");
    printf("+___+_______________________________________________________+\n");
    printf("| 1 | Cari Tamu                                             |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Lihat Tamu Kamar                                      |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Administrasi Tamu                                     |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 4 | Kembali                                               |\n"); 
    printf("+---+-------------------------------------------------------+\n");
    printf("| Masukkan Pilihan Anda: ");
}

void menukeuangan(int dailyprofit, int totalprofit, int maxdays, struct roomtype *types)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                        DATA KEUANGAN                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Statistik Ekonomi - = - = - = - = - = - = - = - = - = - = |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Penghasilan Harian Hotel:                                 |\n");
    printf("| Penghasilan Total Hotel:                                  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Tipe-Tipe Kamar                                           |\n");
    //for loop to print each listed type, read from roomtype.txt")
    for(int i = 0; i < 100; i++)
    {
        printf("| %d. %s - Rp.%d |\n", i+1, types[i].type, types[i].price);
    }
    printf("+___+_______________________________________________________+\n");
    printf("| 1 | Ubah Kelas Kamar                                      |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Tambah Kelas Kamar                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Hapus Kelas Kamar                                     |\n"); 
    printf("+---+-------------------------------------------------------+\n");
    printf("| 4 | Kembali                                               |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| Masukkan Pilihan Anda: ");
}

void statreader(int *totalguests, int *maxdays, int floors, int rooms, int *dailyprofit, int *totalprofit)
{
    //each floor node (which is a linked list) will have their own linked list of rooms
    //each room will have a linked list of customers
    //this function will get the total number of rooms, total number of guests, and the maximum number of days a guest can stay
    //this function will also traverse each room and calculate the hotel's daily profit and total profit
}

void initfloor(struct floor **head, int floor, int room)
{
    struct floor *newfloor = (struct floor *)malloc(sizeof(struct floor));
    //for the floor number, use a counter to increment the floor number
    int counter;
    if(*head == NULL)
    {
        counter = 1;
    }
    else
    {
        struct floor *temp = *head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        counter = temp->number + 1;
    }
    newfloor->number = counter;
    newfloor->rooms = room;
    newfloor->next = NULL;
    newfloor->headroom = NULL;

    if(*head == NULL)
    {
        *head = newfloor;
    }
    else
    {
        struct floor *temp = *head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newfloor;
    }
}

void initroom(struct floor *head, int floor, int room, struct roomtype *headtype)
{
    int i;
    struct floor *temp = head;
    int typecounter = 0;
    struct roomtype *temptype = headtype;
    while(temptype != NULL)
    {
        typecounter++;
        temptype = temptype->next;
    }

    while(temp != NULL)
    {
        int roomnumber = 1, j;
        for(i = 0; i < typecounter; i++)
        {
            temptype = headtype;
            for(j = 0; j < i; j++)
            {
                temptype = temptype->next;
            }
            for(j = 0; j < temptype->amount; j++)
            {
                struct room *newroom = (struct room *)malloc(sizeof(struct room));
                newroom->number = roomnumber;
                strcpy(newroom->type, temptype->type);
                strcpy(newroom->status, "Kosong");
                newroom->days = 0;
                newroom->maxguests = temptype->maxguests;
                newroom->price = temptype->price;
                newroom->next = NULL;

                if(temp->headroom == NULL)
                {
                    temp->headroom = newroom;
                }
                else
                {
                    struct room *temp2 = temp->headroom;
                    while(temp2->next != NULL)
                    {
                        temp2 = temp2->next;
                    }
                    temp2->next = newroom;
                }
                roomnumber++;
            }
        }
        temp = temp->next;
    }
}

void initallfloors(struct floor **head, int floor, int room, struct roomtype *headtype)
{
    int i;
    for(i = 1; i <= floor; i++)
    {
        initfloor(head, i, room);
        struct floor *temp = *head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        initroom(temp, i, room, headtype);
    }
}

void menuhelp(void)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                           BANTUAN                         |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Bantuan - = - = - = - = - = - = - = - = - = - = - = - = - |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| 1 | Statistik Hotel                                       |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Manajemen Struktur                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Manajemen Keuangan                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 4 | Manajemen Tamu                                        |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 5 | Kembali                                               |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("|___________________________________________________________|\n");
    printf("| Masukkan Pilihan Anda: ");
}

void helpstatistik(void)
{
    printf("+-----------------------------------------------------------+\n");
    printf("| Statistik Hotel - = - = - = - = - = - = - = - = - = - = - |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Statistik Hotel menampilkan informasi general hotel,      |\n");
    printf("| seperti jumlah lantai, jumlah kamar per lantai, jumlah    |\n");
    printf("| tamu hotel, nama hotel, dan penghasilan hotel tiap hari   |\n");
    printf("+-----------------------------------------------------------+\n");
}

void helpstruktur(void)
{
    printf("+-----------------------------------------------------------+\n");
    printf("| Manajemen Struktur - = - = - = - = - = - = - = - = - = -  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Manajemen Struktur memungkinkan pengguna untuk mengubah   |\n");
    printf("| informasi terkait bangunan hotel, seperti jumlah lantai,  |\n");
    printf("| jumlah kamar per lantai, dan struktur kamar lantai hotel  |\n");
    printf("| Menu ini juga menampilkan informasi terkait struktur hotel|\n");
    printf("+-----------------------------------------------------------+\n");
}

void helpkeuangan(void)
{
    printf("+-----------------------------------------------------------+\n");
    printf("| Manajemen Keuangan - = - = - = - = - = - = - = - = - = -  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Manajemen Keuangan memungkinkan pengguna untuk melihat    |\n");
    printf("| informasi terkait keuangan hotel, seperti penghasilan     |\n");
    printf("| harian, penghasilan total, dan informasi terkait tipe     |\n");
    printf("| kamar yang ada di hotel. Pengguna dapat memakai menu ini  |\n");
    printf("| untuk mengubah informasi terkait tipe kamar hotel         |\n");  
    printf("+-----------------------------------------------------------+\n");
}

void helptamu(void)
{
    printf("+-----------------------------------------------------------+\n");
    printf("| Manajemen Tamu - = - = - = - = - = - = - = - = - = - = -  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Manajemen Tamu memungkinkan pengguna untuk melihat        |\n");
    printf("| informasi terkait tamu hotel, seperti jumlah tamu hotel,  |\n");
    printf("| jumlah tamu dewasa, remaja, dan anak, serta jumlah tamu   |\n");
    printf("| pria dan wanita. Pengguna juga dapat mencari tamu hotel   |\n");
    printf("| dan melihat informasi terkait tamu yang menginap di hotel |\n");
    printf("+-----------------------------------------------------------+\n");
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
