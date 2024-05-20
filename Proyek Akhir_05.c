// Proyek UAS Pemrograman Lanjut - Sistem Keuangan dan Struktural Hotel
// Kelompok 05
// Anggota:
// 1. Adi Nugroho (2306208546)
// 2. Jesaya David Gamalael N P (2306161965)
// 14 Mei 2024
// Versi 0.4 - Ubah Ukuran Hotel (Increase / Decrease)

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
    struct guest *guests;   
    struct room *next;
};

struct floor
{
    int number;
    int rooms;
    struct room *headroom;
    struct floor *next;
};

struct guest
{
    char name[50];
    char gender[10];
    char status[20];
    int age;
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


void emptyhotel(struct floor *head)
{
    FILE *guestfile = fopen("roomdata.txt", "w");
    if(guestfile == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    struct floor *temp = head;
    int i;
    while(temp != NULL)
    {
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            if(temp2->guests == NULL)
            {
                fprintf(guestfile, "%d,0\n", temp2->maxguests);
                for(i = 0; i < temp2->maxguests; i++)
                {
                    fprintf(guestfile, "EMPTY,X,0\n");
                }
            }
            else if(temp2->guests != NULL)
            {
                fprintf(guestfile, "%d,0\n", temp2->maxguests);
                //traverse the guests array and free the memory
                for(i = 0; i < temp2->maxguests; i++)
                {
                    memset(temp2->guests[i].name, 0, sizeof(temp2->guests[i].name));
                    fprintf(guestfile, "EMPTY,X,0\n");
                }
                free(temp2->guests);
                temp2->guests = NULL;
                strcpy(temp2->status, "Kosong");
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    fclose(guestfile);
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

void initguest(int floor, int room, struct floor *head, struct room *headroom, struct roomtype *headtype)
{
    FILE *guestfile = fopen("roomdata.txt", "r");
    if(guestfile == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    struct floor *tempfloor = head;
    int guestcnt, i;
    while(tempfloor != NULL)
    {
        struct room *temproom = tempfloor->headroom;
        while(temproom != NULL)
        {
            struct guest *guests = (struct guest *)malloc(temproom->maxguests * sizeof(struct guest));
            fscanf(guestfile, "%d,%d\n", &guestcnt, &temproom->days); 
            if(guestcnt > 0 && temproom->days > 0) // Check if there are guests and the room is occupied for more than 0 days
            {
                for(i = 0; i < guestcnt; i++)
                {
                    fscanf(guestfile, "%[^,],%c,%d\n", guests[i].name, &guests[i].gender, &guests[i].age);
                    switch(guests[i].age)
                    {
                        case 1 ... 12:
                            strcpy(guests[i].status, "Anak");
                            break;
                        case 13 ... 20:
                            strcpy(guests[i].status, "Remaja");
                            break;
                        case 21 ... 50:
                            strcpy(guests[i].status, "Dewasa");
                            break;
                        case 51 ... 100:
                            strcpy(guests[i].status, "Lansia");
                            break;
                    }
                }
                temproom->guests = guests;
                strcpy(temproom->status, "Terisi");
            }
            else
            {
                temproom->guests = NULL;
                strcpy(temproom->status, "Kosong");
                for(i = 0; i < guestcnt; i++)
                {
                    fscanf(guestfile, "%*[^,],%*c,%*d\n");
                }
            }
            temproom = temproom->next; // Moved this line outside of the if-else statement
        }
        tempfloor = tempfloor->next;
    }
    fclose(guestfile);
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

void emptyhotel(struct floor *head)
{
    FILE *guestfile = fopen("roomdata.txt", "w");
    if(guestfile == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    struct floor *temp = head;
    int i;
    while(temp != NULL)
    {
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            if(temp2->guests == NULL)
            {
                fprintf(guestfile, "%d,0\n", temp2->maxguests);
                for(i = 0; i < temp2->maxguests; i++)
                {
                    fprintf(guestfile, "EMPTY,X,0\n");
                }
            }
            else if(temp2->guests != NULL)
            {
                fprintf(guestfile, "%d,0\n", temp2->maxguests);
                //traverse the guests array and free the memory
                for(i = 0; i < temp2->maxguests; i++)
                {
                    memset(temp2->guests[i].name, 0, sizeof(temp2->guests[i].name));
                    fprintf(guestfile, "EMPTY,X,0\n");
                }
                free(temp2->guests);
                temp2->guests = NULL;
                strcpy(temp2->status, "Kosong");
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    fclose(guestfile);
}

void increasefloorsize(struct floor **head, int floor, int *room, struct roomtype *headtype, int newroom)
{
    FILE *file = fopen("roomdata.txt", "w");
    if(file == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    struct floor *tempfloor = *head;
    struct roomtype *temptype = headtype;
    int typecounter = 0;

    // Calculate the number of room types
    while(temptype != NULL)
    {
        typecounter++;
        temptype = temptype->next;
    }

    // Iterate over each floor
    while(tempfloor != NULL)
    {
        int oldroomcounter = tempfloor->rooms;
        tempfloor->rooms = newroom;
        int extrarooms = newroom - oldroomcounter;
        struct room *temproom = tempfloor->headroom, *lastroom = NULL;

        // Iterate over existing rooms
        while(temproom != NULL)
        {
            fprintf(file, "%d,%d\n", temproom->maxguests, temproom->days);
            if(temproom->guests != NULL)
            {
                for(int i = 0; i < temproom->maxguests; i++)
                {
                    fprintf(file, "%s,%c,%d\n", temproom->guests[i].name, temproom->guests[i].gender, temproom->guests[i].age);
                }
            }
            else
            {
                for(int i = 0; i < temproom->maxguests; i++)
                {
                    fprintf(file, "EMPTY,X,0\n");
                }
            }
            lastroom = temproom;
            temproom = temproom->next;
        }

        // Add new rooms
        for(int i = 0; i < extrarooms; i++)
        {
            struct room *newroom = (struct room *)malloc(sizeof(struct room));
            if(newroom == NULL)
            {
                printf("Memory allocation failed!\n");
                fclose(file);
                return;
            }
            newroom->number = tempfloor->number * 1000 + oldroomcounter + i + 1;
            strcpy(newroom->type, lastroom->type);
            strcpy(newroom->status, "Kosong");
            newroom->days = 0;
            newroom->maxguests = lastroom->maxguests;
            newroom->price = lastroom->price;
            newroom->guests = NULL;
            newroom->next = NULL;

            if (lastroom == NULL)
            {
                tempfloor->headroom = newroom;
            }
            else
            {
                lastroom->next = newroom;
            }
            lastroom = newroom;

            fprintf(file, "%d,%d\n", newroom->maxguests, newroom->days);
            for(int j = 0; j < newroom->maxguests; j++)
            {
                fprintf(file, "EMPTY,X,0\n");
            }
        }

        tempfloor->rooms = newroom; // Update room count in the floor
        tempfloor = tempfloor->next;
    }

    fclose(file);

    // Write the updated structure to structure.txt
    FILE *file2 = fopen("structure.txt", "w");
    if(file2 == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }
    fprintf(file2, "%d,%d", floor, newroom);
    fclose(file2);

    // Write the updated room types to roomtype.txt
    FILE *file3 = fopen("roomtype.txt", "w");
    if(file3 == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }
    temptype = headtype;
    for(int i = 0; i < typecounter - 1; i++)
    {
        fprintf(file3, "%s,%d,%d,%d\n", temptype->type, temptype->price, temptype->maxguests, temptype->amount);
        temptype = temptype->next;
    }
    int difference = newroom - *room;
    if (temptype != NULL) 
    {
        fprintf(file3, "%s,%d,%d,%d\n", temptype->type, temptype->price, temptype->maxguests, temptype->amount + difference);
    }
    //in the temptype array, update the amount of rooms for the last room type
    temptype = headtype;
    for(int i = 0; i < typecounter - 1; i++)
    {
        temptype = temptype->next;
    }
    temptype->amount += difference;
    
    fclose(file3);

    // Update the total room count
    *room = newroom;
}

void increasehotelsize(struct floor **head, int *floor, int *room, int newfloor, struct roomtype *headtype)
{
    FILE *file = fopen("roomdata.txt", "a");
    if (file == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    struct floor *tempfloor = *head;
    struct roomtype *temptype = headtype;
    int typecounter = 0;

    // Calculate the number of room types
    while (temptype != NULL)
    {
        typecounter++;
        temptype = temptype->next;
    }

    // Move to the last floor in the linked list
    while (tempfloor->next != NULL)
    {
        tempfloor = tempfloor->next;
    }

    int extrafloors = newfloor - *floor;
    for (int i = 0; i < extrafloors; i++)
    {
        struct floor *newfloor = (struct floor *)malloc(sizeof(struct floor));
        if (newfloor == NULL)
        {
            printf("Memory allocation failed!\n");
            fclose(file);
            return;
        }

        newfloor->number = tempfloor->number + 1;
        newfloor->rooms = *room; // Use the updated room count
        newfloor->next = NULL;
        newfloor->headroom = NULL;
        tempfloor->next = newfloor;

        struct room *lastroom = NULL;
        temptype = headtype;

        int roomnumber = 1;
        // Create rooms for the new floor
        for (int j = 0; j < typecounter; j++)
        {
            int roomcounter = temptype->amount;
            for (int k = 0; k < roomcounter; k++)
            {
                struct room *newroom = (struct room *)malloc(sizeof(struct room));
                if (newroom == NULL)
                {
                    printf("Memory allocation failed!\n");
                    fclose(file);
                    return;
                }

                newroom->number = newfloor->number * 1000 + roomnumber;
                roomnumber++;
                strcpy(newroom->type, temptype->type);
                strcpy(newroom->status, "Kosong");
                newroom->days = 0;
                newroom->maxguests = temptype->maxguests;
                newroom->price = temptype->price;
                newroom->guests = NULL;
                newroom->next = NULL;

                if (newfloor->headroom == NULL)
                {
                    newfloor->headroom = newroom;
                }
                else
                {
                    lastroom->next = newroom;
                }
                lastroom = newroom;

                // Write the new room's data to roomdata.txt
                fprintf(file, "%d,%d\n", newroom->maxguests, newroom->days);
                for (int x = 0; x < newroom->maxguests; x++)
                {
                    fprintf(file, "EMPTY,X,0\n");
                }
            }
            temptype = temptype->next;
        }

        tempfloor = newfloor;
    }

    fclose(file);

    // Rewrite the structure.txt file with the new floor and room amount
    FILE *file2 = fopen("structure.txt", "w");
    if (file2 == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }
    fprintf(file2, "%d,%d", newfloor, *room);
    fclose(file2);

    *floor = newfloor;
}

void decreasesize(struct floor **head, int *floor, int *room, struct roomtype *headtype, int newroom, int newfloor)
{
    // Decrease the size of the hotel and empty the rooms
    emptyhotel(*head);
    
    // Update structure.txt with the new floor and room amount
    FILE *file = fopen("structure.txt", "w");
    if(file == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }
    fprintf(file, "%d,%d", newfloor, newroom);
    fclose(file);
    *room = newroom;
    *floor = newfloor;

    // Update roomtype.txt with the new room amount
    // Set the first room type to the new amount, and all other room types to 0
    FILE *file2 = fopen("roomtype.txt", "w");
    if(file2 == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }
    struct roomtype *temptype = headtype;
    fprintf(file2, "%s,%d,%d,%d\n", temptype->type, temptype->price, temptype->maxguests, newroom);
    while(temptype->next != NULL)
    {
        temptype = temptype->next;
        fprintf(file2, "%s,%d,%d,%d\n", temptype->type, temptype->price, temptype->maxguests, 0);
    }
    fclose(file2);

    // Free the excess floors. If the floor count exceeds newfloor, free it and the next floors
    struct floor *current = *head;
    struct floor *previous = NULL;
    int currentFloor = 0;

    while(current != NULL && currentFloor < newfloor)
    {
        previous = current;
        current = current->next;
        currentFloor++;
    }

    // If current is not NULL, it means we have more floors than newfloor
    if(current != NULL)
    {
        // Free all remaining floors starting from the current floor
        while(current != NULL)
        {
            struct floor *temp = current;
            current = current->next;
            free(temp);
        }
        // Set the end of the new list
        if(previous != NULL)
        {
            previous->next = NULL;
        }
        else
        {
            // If previous is NULL, it means we are freeing all the floors
            *head = NULL;
        }
    }

    // After freeing the floors, free the rooms. If the room count exceeds newroom, free it and the next rooms
    current = *head;
    while(current != NULL)
    {
        struct room *currentRoom = current->headroom;
        struct room *previousRoom = NULL;
        int currentRoomNumber = 0;

        while(currentRoom != NULL && currentRoomNumber < newroom)
        {
            previousRoom = currentRoom;
            currentRoom = currentRoom->next;
            currentRoomNumber++;
        }

        // If currentRoom is not NULL, it means we have more rooms than newroom
        if(currentRoom != NULL)
        {
            // Free all remaining rooms starting from the current room
            while(currentRoom != NULL)
            {
                struct room *temp = currentRoom;
                currentRoom = currentRoom->next;
                free(temp);
            }
            // Set the end of the new list
            if(previousRoom != NULL)
            {
                previousRoom->next = NULL;
            }
            else
            {
                // If previousRoom is NULL, it means we are freeing all the rooms
                current->headroom = NULL;
            }
        }
        current = current->next;
    }

    // Traverse all the rooms and set all of them to the first room type
    current = *head;
    while(current != NULL)
    {
        struct room *currentRoom = current->headroom;
        while(currentRoom != NULL)
        {
            struct roomtype *temptype = headtype;
            strcpy(currentRoom->type, temptype->type);
            currentRoom->maxguests = temptype->maxguests;
            currentRoom->price = temptype->price;
            currentRoom = currentRoom->next;
        }
        current = current->next;
    }

    // Update the room type amounts
    temptype = headtype;
    temptype->amount = newroom;
    temptype = temptype->next;
    while(temptype != NULL)
    {
        temptype->amount = 0;
        temptype = temptype->next;
    }

    // Lastly, rewrite roomdata.txt with the emptied guest data
    FILE *file3 = fopen("roomdata.txt", "w");
    if(file3 == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    int i;

    current = *head;
    while(current != NULL)
    {
        struct room *currentRoom = current->headroom;
        while(currentRoom != NULL)
        {
            fprintf(file3, "%d,0\n", currentRoom->maxguests);
            for(i = 0; i < currentRoom->maxguests; i++)
            {
                fprintf(file3, "EMPTY,X,0\n");
            }
            currentRoom = currentRoom->next;
        }
        current = current->next;
    }

    fclose(file3);
}

void roomchanger(struct floor *head, struct roomtype *headtype)
{
    // This function's purpose is to change the structure of the rooms in the hotel

    //First, update the roomtype linked list using roomtype.txt data
    //This function updates the roomtype linked list in case a new room type is added or an existing room type is removed
    FILE *file = fopen("roomtype.txt", "r");
    if(file == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    //empty the roomtype linked list and read the roomtype.txt file to update the linked list
    struct roomtype *temp = headtype;
    while(temp != NULL)
    {
        struct roomtype *temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    headtype = NULL;

    char type[20];
    int price, maxguests, amount;
    while(fscanf(file, "%[^,],%d,%d,%d\n", type, &price, &maxguests, &amount) != EOF)
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
    printf("Room types have been updated!\n");

    int typecounter = 0, i, j;
    struct roomtype *temptype;
    temptype = headtype;
    while(temptype != NULL)
    {
        typecounter++;
        printf("Type: %s, Price: %d, Max guests: %d, Amount: %d\n", temptype->type, temptype->price, temptype->maxguests, temptype->amount);
        temptype = temptype->next;
    }

    //Then, update the room types in the rooms linked list for each floor (empty the hotel first)
    emptyhotel(head);
    printf("Hotel has been emptied!\n");

    //Then, update the room types in the rooms linked list for each floor
    struct floor *tempfloor = head;
    while(tempfloor != NULL)
    {
        struct room *temproom = tempfloor->headroom;
        temptype = headtype;
        //the roomtype list will have the amount of each room type in a floor
        for(i = 0; i < typecounter; i++)
        {
            for(j = 0; j < temptype->amount; j++)
            {
                strcpy(temproom->type, temptype->type);
                temproom->maxguests = temptype->maxguests;
                temproom->price = temptype->price;
                temproom->days = 0;
                temproom->guests = NULL;
                strcpy(temproom->status, "Kosong");
                temproom = temproom->next;
            }
            temptype = temptype->next;
        }
        tempfloor = tempfloor->next;
    }
    printf("Room types have been updated!\n");

    //Lastly, update the roomdata.txt file with the new room types
    FILE *file2 = fopen("roomdata.txt", "w");
    if(file2 == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    tempfloor = head;
    while(tempfloor != NULL)
    {
        struct room *temproom = tempfloor->headroom;
        while(temproom != NULL)
        {
            fprintf(file2, "%d,0\n", temproom->maxguests, temproom->days);
            if(temproom->guests != NULL) // Check if guests is not NULL
            {
                for(int i = 0; i < temproom->maxguests; i++)
                {
                    fprintf(file2, "%s,%c,%d\n", temproom->guests[i].name, temproom->guests[i].gender, temproom->guests[i].age);
                }
            }
            else
            {
                for(int i = 0; i < temproom->maxguests; i++)
                {
                    fprintf(file2, "EMPTY,X,0\n");
                }
            }
            temproom = temproom->next;
        }
        tempfloor = tempfloor->next;
    }
    fclose(file2);
    printf("Room types have been updated!\n\n\n");
}