// Proyek UAS Pemrograman Lanjut - Sistem Keuangan dan Struktural Hotel
// Kelompok 05
// Anggota: 
// 1. Adi Nugroho (2306208546)
// 2. Jesaya David Gamalael N P (2306161965)
// 14 Mei 2024
// Versi 0.6 - Penambahan dan Pengurangan Jenis Kamar

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
    char gender;
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

void menu(void);
void menustatistik(int floor, int room, int totalguests, int longestrent, long long int totalprofit, int totaltypes);
void menustruktur(int floor, int room, int availablerooms, int longestrent);
int menuubahlantai(int *floor);
int menuubahkamar(int *room);
void menutamu(int totalguests, int guestgender[2], int gueststatus[4]);
void menukeuangan(int dailyprofit, int totalprofit, int maxdays, struct roomtype *headtype, int totaltypes);
void menurestructure(struct roomtype *headtype, int room, int totaltypes, struct floor *head);
void adminmenu(struct floor *head);
void statreader(struct floor *head, int *totalguests, int *longestrent, int *availablerooms, long long int *totalprofit, long int *dailyprofit, int *totaltypes, struct roomtype *headtype, int guestgender[2], int gueststatus[4]);
void initfloor(struct floor **head, int floor, int room);
void initroom(struct floor *head, int floor, int room, struct roomtype *headtype);
void initallfloors(struct floor **head, int floor, int room, struct roomtype *headtype);
void initguest(int floor, int room, struct floor *head, struct room *headroom, struct roomtype *headtype);
void menuhelp(void);
void helpstatistik(void);
void helpstruktur(void);
void helpkeuangan(void);
void helptamu(void);
void emptyhotel(struct floor *head);
void print_hotel(int floors, int rooms);
void increasefloorsize(struct floor **head, int floor, int *room, struct roomtype *headtype, int newroom);
void increasehotelsize(struct floor **head, int *floor, int *room, int newfloor, struct roomtype *headtype);
void decreasesize(struct floor **head, int *floor, int *room, struct roomtype *headtype, int newroom, int newfloor);
void roomchanger(struct floor *head, struct roomtype *headtype);
void menunewtype(struct roomtype *headtype);
void newroomtype(struct roomtype **head, char type[20], int price, int maxguests);
void menuremovetype(struct roomtype *head);
void removeroomtype(struct roomtype **head, char type[20]);
void registration(struct floor *head, int roomnumber);
void searchguest(struct floor *head, struct roomtype *headtype);
void statupdater(int *floors, int *rooms);
void guestviewer(struct floor *head);

int main(void)
{
    int opsiA, opsiB, opsiC;

    int floor, room;
    int totalguests = 0, longestrent = 0, availablerooms = 0, totaltypes = 0;
    long long int totalprofit = 0;
    long int dailyprofit = 0;
    int guestgender[2], gueststatus[4];
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
    fclose(file2);
    struct floor *head = NULL;
    // Initialize the floors and rooms
    initallfloors(&head, floor, room, headtype);
    // Initialize the guests
    initguest(floor, room, head, head->headroom, headtype);
    struct floor *temp = head;
    int i;

    do 
    {
        statupdater(&floor, &room);
        statreader(head, &totalguests, &longestrent, &availablerooms, &totalprofit, &dailyprofit, &totaltypes, headtype, guestgender, gueststatus);
        menu(); //memanggil fungsi menu
        do 
        {
            scanf("%d", &opsiA);
            if(opsiA < 1 || opsiA > 6) 
            {
                printf(" Opsi tidak valid!\n| ");
            } 
        } while(opsiA < 1 || opsiA > 6); //error handling

        switch(opsiA) 
        {
            case 1:
            {
                system("cls");
                menustatistik(floor, room, totalguests, longestrent, totalprofit, totaltypes);
                scanf("%d", &opsiB);
                do 
                {
                    scanf("%d", &opsiB);
                    if(opsiB < 1 || opsiB > 2) 
                    {
                        printf(" Opsi tidak valid!\n| "); 
                    } 
                } while(opsiB < 1 || opsiB > 2); //error handling

                switch(opsiB)
                {
                    case 1:
                        system("cls");
                        print_hotel(floor, room);
                        system("pause");
                        system("cls");
                        break;

                    case 2:
                        system("cls");
                        break;
                }
                break;
            }

            case 2:
            {
                system("cls");
                menustruktur(floor, room, availablerooms, longestrent);
                scanf("%d", &opsiB);
                do 
                {
                    scanf("%d", &opsiB);
                    if(opsiB < 1 || opsiB > 3) 
                    {
                        printf(" Opsi tidak valid!\n| ");
                    } 
                } while(opsiB < 1 || opsiB > 3); //error handling
                switch(opsiB)
                {
                    case 1:
                        system("cls");
                        int newfloor = menuubahlantai(&floor);
                        if(newfloor != 0 && newfloor > floor)
                        {
                            increasehotelsize(&head, &floor, &room, newfloor, headtype);
                        }
                        else if(newfloor != 0 && newfloor < floor)
                        {
                            decreasesize(&head, &floor, &room, headtype, room, newfloor);
                        }
                        system("pause");
                        system("cls");
                        break;

                    case 2:
                        system("cls");
                        int newroom = menuubahkamar(&room);
                        if(newroom != 0 && newroom > room)
                        {
                            increasefloorsize(&head, floor, &room, headtype, newroom);
                        }
                        else if(newroom != 0 && newroom < room)
                        {
                            decreasesize(&head, &floor, &room, headtype, newroom, floor);
                        }
                        system("pause");
                        system("cls");
                        break;

                    case 3:
                    {
                        system("cls");
                        break;
                    }
                }
                break;
            }

            case 3:
            {
                system("cls");
                menukeuangan(dailyprofit, totalprofit, longestrent, headtype, totaltypes);
                scanf("%d", &opsiB);
                do 
                {
                    scanf("%d", &opsiB);
                    if(opsiB < 1 || opsiB > 4) 
                    {
                        printf(" Opsi tidak valid!\n"); 
                    } 
                } while(opsiB < 1 || opsiB > 4); //error handling
                switch(opsiB)
                {
                    case 1:
                        system("cls");
                        menurestructure(headtype, room, totaltypes, head);
                        system("pause");
                        system("cls");
                        break;

                    case 2:
                        system("cls");
                        menunewtype(headtype);
                        system("pause");
                        system("cls");
                        break;

                    case 3:
                    {
                        system("cls");
                        menuremovetype(headtype);
                        system("pause");
                        system("cls");
                        break;
                    }

                    case 4:
                        system("cls");
                        break;
                }
                break;
            }

            case 4:
            {
                system("cls");
                menutamu(totalguests, guestgender, gueststatus);
                scanf("%d", &opsiB);
                do 
                {
                    scanf("%d", &opsiB);
                    if(opsiB < 1 || opsiB > 4) 
                    {
                        printf(" Opsi tidak valid!\n"); 
                    } 
                } while(opsiB < 1 || opsiB > 4); //error handling
                switch(opsiB)
                {
                    case 1:
                        system("cls");
                        searchguest(head, headtype);
                        system("pause");
                        system("cls");
                        break;

                    case 2:
                        system("cls");
                        guestviewer(head);
                        system("pause");
                        system("cls");
                        break;

                    case 3:
                    {
                        system("cls");
                        adminmenu(head);
                        system("pause");
                        system("cls");
                        break;
                    }

                    case 4:
                        system("cls");
                        break;
                }
                break;
            }

            case 5:
                system("cls");
                menuhelp();
                scanf("%d", &opsiB);
                do 
                {
                    scanf("%d", &opsiB);
                    if(opsiB < 1 || opsiB > 5) 
                    {
                        printf(" Opsi tidak valid!\n"); 
                    } 
                } while(opsiB < 1 || opsiB > 5); //error handling
                switch(opsiB)
                {
                    case 1:
                        helpstatistik();
                        system("pause");
                        system("cls");
                        break;

                    case 2:
                        helpstruktur();
                        system("pause");
                        system("cls");
                        break;

                    case 3:
                    {
                        helpkeuangan();
                        system("pause");
                        system("cls");
                        break;
                    }

                    case 4:
                        helptamu();
                        system("pause");
                        system("cls");
                        break;

                    case 5:
                        break;
                }
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
    printf("| 4 | Manajemen Tamu                                        |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 5 | Help                                                  |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 6 | Exit                                                  |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("|___________________________________________________________|\n");
    printf("| Masukkan Pilihan Anda: ");   
}

void menustatistik(int floor, int room, int totalguests, int longestrent, long long int totalprofit, int totaltypes)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                       STATISTIK HOTEL                     |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Statistik General - = - = - = - = - = - = - = - = - = - = |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Lantai Hotel: %-36d |\n", floor);
    printf("| Jumlah Kamar per Lantai: %-32d |\n", room);
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Tamu Total: %-38d |\n", totalguests);
    printf("| Penginapan Terlama: %-37d |\n", longestrent);
    printf("+-----------------------------------------------------------+\n");
    printf("| Profit Total Hotel: Rp.%-34lld |\n", totalprofit);
    printf("| Jumlah Tipe Kamar: %-38d |\n", totaltypes);
    printf("+___+_______________________________________________________+\n");
    printf("| 1 | Diagram Hotel                                         |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Kembali                                               |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| Masukkan Pilihan Anda: ");
}

void menustruktur(int floor, int room, int availablerooms, int longestrent)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                       STRUKTUR HOTEL                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Statistik Hotel - = - = - = - = - = - = - = - = - = - = - |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Lantai Hotel: %-36d |\n", floor);
    printf("| Jumlah Kamar per Lantai: %-32d |\n", room);
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Kamar Total: %-37d |\n", floor * room);
    printf("| Jumlah Kamar Tersedia: %-34d |\n" , availablerooms);
    printf("+-----------------------------------------------------------+\n");
    printf("| Hotel Akan Kosong Dalam: %3d Hari                         |\n", longestrent);
    printf("+___+_______________________________________________________+\n");
    printf("| 1 | Ubah Jumlah Lantai Hotel                              |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Ubah Jumlah Kamar per Lantai                          |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Kembali                                               |\n"); 
    printf("+---+-------------------------------------------------------+\n");
    printf("| Masukkan Pilihan Anda: ");
}

int menuubahlantai(int *floor)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                       STRUKTUR HOTEL                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Ubah Jumlah Lantai - = - = - = - = - = - = - = - = - = -  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Lantai Hotel: %-36d |\n", *floor);
    printf("+-----------------------------------------------------------+\n");
    printf("| Masukkan Jumlah Lantai Baru: ");
    int floorinput;
    do
    {
        scanf("%d", &floorinput);
        if(floorinput < 1)
        {
            printf(" Jumlah lantai tidak valid!\n| ");
            printf("| Masukkan Jumlah Lantai Baru: ");
        }
    } while(floorinput < 1);

    if(floorinput == *floor)
    {
        return 0;
    }
    else if(floorinput > *floor)
    {
        printf("| Lantai baru dibuat!                                       |\n");
        printf("+-----------------------------------------------------------+\n");
        return floorinput;
    }
    else if(floorinput < *floor)
    {
        printf("| Pengecilan struktur butuh pengosongan hotel! Lanjut?      |\n");
        int opsi;
        printf("| 1. Ya                                                     |\n");
        printf("| 2. Tidak                                                  |\n");
        printf("+-----------------------------------------------------------+\n");
        printf("| Masukkan Pilihan Anda: ");
        do
        {
            scanf("%d", &opsi);
            if(opsi < 1 || opsi > 2)
            {
                printf("Pilihan tidak valid!\n| ");
                printf("| Masukkan Pilihan Anda: ");
            }
        } while(opsi < 1 || opsi > 2);

        if(opsi == 1)
        {
            printf("| Hotel diperkecil!                                         |\n");
            printf("+-----------------------------------------------------------+\n");
            return floorinput;
        }

        else if(opsi == 2)
        {
            printf("| Pembatalan berhasil!                                      |\n");
            printf("+-----------------------------------------------------------+\n");
            return 0;
        }
    }
}

int menuubahkamar(int *room)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                       STRUKTUR HOTEL                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Ubah Jumlah Kamar - = - = - = - = - = - = - = - = - = - = |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Kamar Hotel: %-37d |\n", *room);
    printf("+-----------------------------------------------------------+\n");
    printf("| Masukkan Jumlah Kamar Baru: ");
    int roominput;
    do
    {
        scanf("%d", &roominput);
        if(roominput < 1)
        {
            printf(" Jumlah kamar tidak valid!\n| ");
            printf("| Masukkan Jumlah Kamar Baru: ");
        }
    } while(roominput < 1);

    if(roominput == *room)
    {
        return 0;
    }
    else if(roominput > *room)
    {
        printf("| Lantai baru dibuat!                                       |\n");
        printf("+-----------------------------------------------------------+\n");
        return roominput;
    }
    else if(roominput < *room)
    {
        printf("| Pengecilan struktur butuh pengosongan hotel! Lanjut?      |\n");
        int opsi;
        printf("| 1. Ya                                                     |\n");
        printf("| 2. Tidak                                                  |\n");
        printf("+-----------------------------------------------------------+\n");
        printf("| Masukkan Pilihan Anda: ");
        do
        {
            scanf("%d", &opsi);
            if(opsi < 1 || opsi > 2)
            {
                printf("Pilihan tidak valid!\n| ");
                printf("| Masukkan Pilihan Anda: ");
            }
        } while(opsi < 1 || opsi > 2);

        if(opsi == 1)
        {
            printf("| Hotel diperkecil!                                         |\n");
            printf("+-----------------------------------------------------------+\n");
            return roominput;
        }

        else if(opsi == 2)
        {
            printf("| Pembatalan berhasil!                                      |\n");
            printf("+-----------------------------------------------------------+\n");
            return 0;
        }
    }
}

void menutamu(int totalguests, int guestgender[2], int gueststatus[4])
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                          DATA TAMU                        |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Statistik Tamu  - = - = - = - = - = - = - = - = - = - = - |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Tamu Hotel: %-38d |\n", totalguests);
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Tamu Dewasa: %-37d |\n", gueststatus[2]);
    printf("| Jumlah Tamu Remaja: %-37d |\n", gueststatus[1]);
    printf("| Jumlah Tamu Anak: %-39d |\n", gueststatus[0]);
    printf("| Jumlah Tamu Lansia: %-37d |\n" , gueststatus[3]);
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Tamu Laki-Laki: %-34d |\n", guestgender[0]);
    printf("| Jumlah Tamu Wanita: %-37d |\n", guestgender[1]);
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

void menukeuangan(int dailyprofit, int totalprofit, int maxdays, struct roomtype *headtype, int totaltypes)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                        DATA KEUANGAN                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Statistik Ekonomi - = - = - = - = - = - = - = - = - = - = |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Penghasilan Harian Hotel: Rp.%-28d |\n", dailyprofit);
    printf("| Penghasilan Total Hotel: Rp.%-29d |\n", totalprofit);
    printf("+-----------------------------------------------------------+\n");
    printf("| Tipe-Tipe Kamar: %-40d |\n", totaltypes);
    printf("+-----------------------------------------------------------+\n");
    printf("|    Nama Kelas    |   Harga / Malam   | Jumlah | Max Guest |\n");
    printf("+-----------------------------------------------------------+\n");
    struct roomtype *temp = headtype;
    while(temp != NULL)
    {
        printf("| %-16s | Rp.%-14d | %-6d | %-9d |\n", temp->type, temp->price, temp->amount, temp->maxguests);
        temp = temp->next;
    }
    printf("+___+_______________________________________________________+\n");
    printf("| 1 | Ubah Struktur Kamar                                   |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Tambah Kelas Kamar                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Hapus Kelas Kamar                                     |\n"); 
    printf("+---+-------------------------------------------------------+\n");
    printf("| 4 | Kembali                                               |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| Masukkan Pilihan Anda: ");
}

void menurestructure(struct roomtype *headtype, int room, int totaltypes, struct floor *head)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                         RESTRUCTURE                       |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Pengubahan Struktur - = - = - = - = - = - = - = - = - = - |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|    Nama Kelas    |   Harga / Malam   | Jumlah | Max Guest |\n");
    struct roomtype *temp = headtype;
    int i;
    while(temp != NULL)
    {
        printf("| %-16s | Rp.%-14d | %-6d | %-9d |\n", temp->type, temp->price, temp->amount, temp->maxguests);
        temp = temp->next;
    }
    printf("+-----------------------------------------------------------+\n");
    printf("| Jumlah Kamar per Lantai: %-32d |\n", room);
    printf("| Masukkan Struktur Kamar Baru                              |\n");
    printf("+-----------------------------------------------------------+\n");
    int totalroom;
    do
    {    
        totalroom = 0;
        temp = headtype;
        for(i = 0; i < totaltypes; i++)
        {
            printf("| Jumlah Kamar Kelas %s: ", temp->type);
            do
            {
                scanf("%d", &temp->amount);
                if(temp->amount < 0 || temp->amount > room || temp->amount + totalroom > room)
                {
                    printf("| Jumlah kamar tidak valid!\n| ");
                    printf("Jumlah Kamar Kelas %s: ", temp->type);
                }
            } while(temp->amount < 0 || temp->amount > room || temp->amount + totalroom > room);
            totalroom += temp->amount;
            temp = temp->next;
        }

        if(totalroom != room)
        {
            printf("| Jumlah kamar tidak sesuai dengan jumlah kamar per lantai! |\n");
            printf("+-----------------------------------------------------------+\n");
        }
    } while(totalroom != room);
    printf("+-----------------------------------------------------------+\n");
    printf("| Restrukturisasi Berhasil!                                 |\n");
    printf("+-----------------------------------------------------------+\n");
    
    //Now, with the new room structure, we need to change roomtype.txt
    FILE *file = fopen("roomtype.txt", "w");
    if(file == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    temp = headtype;
    while(temp != NULL)
    {
        fprintf(file, "%s,%d,%d,%d\n", temp->type, temp->price, temp->maxguests, temp->amount);
        temp = temp->next;
    }
    fclose(file);
    //call the restructuring function
    roomchanger(head, headtype);
}

void adminmenu(struct floor *head)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                     ADMINISTRASI TAMU                     |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Ruang Tersedia - = - = - = - = - = - = - = - = - = - = -  |\n");
    printf("+-----------------------------------------------------------+\n");
    int hotelfull = 1;
    //traverse the hotel and print the available rooms
    struct floor *temp = head;
    while(temp != NULL)
    {
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            if(strcmp(temp2->status, "Kosong") == 0)
            {
                printf("| Ruang No - %-6d | Kelas %-19s | Lantai %-2d |\n", temp2->number, temp2->type, temp->number);
                printf("| Harga / Malam: Rp.%-16d | Kapasitas Kamar: %-3d |\n", temp2->price, temp2->maxguests);
                printf("+-----------------------------------------------------------+\n");
                hotelfull = 0;
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    if(hotelfull == 1)
    {
        printf("| Hotel Penuh!                                              |\n");
        printf("+-----------------------------------------------------------+\n");
        return;
    }

    printf("| Masukkan Nomor Kamar: ");
    int roomnumber;
    do
    {
        scanf("%d", &roomnumber);
        if(roomnumber < 1)
        {
            printf(" Nomor kamar tidak valid!\n| Masukkan Nomor Kamar: ");
        }
    } while(roomnumber < 1);

    //First, check if the roomnumber is valid
    temp = head;
    int roomfound = 0;
    while(temp != NULL)
    {
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            if(temp2->number == roomnumber)
            {
                roomfound = 1;
                break;
            }
            temp2 = temp2->next;
        }
        if(roomfound == 1)
        {
            registration(head, roomnumber);
            break;
        }
        temp = temp->next;
    }
}

void statreader(struct floor *head, int *totalguests, int *longestrent, int *availablerooms, long long int *totalprofit, long int *dailyprofit, int *totaltypes, struct roomtype *headtype, int guestgender[2], int gueststatus[4])
{
    //This function's purpose is to read through the hotel and get the amount of guests currently residing in the hotel
    //The function will also get the longest renting period of the guests and the amount of available rooms
    struct floor *temp = head;
    *totalprofit = 0;
    *totaltypes = 0;
    *availablerooms = 0;
    *longestrent = 0;
    *totalguests = 0;
    *dailyprofit = 0;

    for(int i = 0; i < 2; i++)
    {
        guestgender[i] = 0;
    }
    for(int i = 0; i < 4; i++)
    {
        gueststatus[i] = 0;
    }

    //First, get the total amount of room types
    struct roomtype *temptype = headtype;
    while(temptype != NULL)
    {
        *totaltypes += 1;
        temptype = temptype->next;
    }

    while(temp != NULL)
    {
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            if(strcmp(temp2->status, "Terisi") == 0)
            {
                //If the room is occupied, add the price of the room multiplied by the staying period to the total profit
                *totalprofit += (temp2->price) * (temp2->days);
                *dailyprofit += temp2->price;
                //If the room is occupied, then add the amount of guests to the totalguests (don't count empty guests)
                int i;
                for(i = 0; i < temp2->maxguests; i++)
                {
                    if(strcmp(temp2->guests[i].name, "EMPTY") != 0)
                    {
                        *totalguests += 1;
                        if(strcasecmp(temp2->guests[i].status, "Anak") == 0)
                        {
                            gueststatus[0] += 1;
                        }
                        else if(strcasecmp(temp2->guests[i].status, "Remaja") == 0)
                        {
                            gueststatus[1] += 1;
                        }
                        else if(strcasecmp(temp2->guests[i].status, "Dewasa") == 0)
                        {
                            gueststatus[2] += 1;
                        }
                        else if(strcasecmp(temp2->guests[i].status, "Lansia") == 0)
                        {
                            gueststatus[3] += 1;
                        }

                        if(temp2->guests[i].gender == 'L')
                        {
                            guestgender[0] += 1;
                        }
                        else if(temp2->guests[i].gender == 'W')
                        {
                            guestgender[1] += 1;
                        }
                    }
                }
                if(temp2->days > *longestrent)
                {
                    *longestrent = temp2->days;
                }
            }
            else if(strcmp(temp2->status, "Kosong") == 0)
            {
                *availablerooms += 1;
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
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

    int typecounter = 0, i, j;
    struct roomtype *temptype;
    temptype = headtype;
    while(temptype != NULL)
    {
        typecounter++;
        temptype = temptype->next;
    }

    //Then, update the room types in the rooms linked list for each floor (empty the hotel first)
    emptyhotel(head);

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
}

void menunewtype(struct roomtype *headtype)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                   PENAMBAHAN JENIS KAMAR                  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Penambahan Jenis Kamar - = - = - = - = - = - = - = - = -  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Masukkan Name Jenis Kamar Baru: ");
    char type[40];
    scanf(" %[^\n]", type);
    printf("| Masukkan Harga Sewa Kamar / Malam: Rp");
    int price;
    scanf("%d", &price);
    printf("| Masukkan Kapasitas Maksimum Tamu: ");
    int maxguests;
    scanf("%d", &maxguests);
    printf("+-----------------------------------------------------------+\n");
    printf("| Jenis Kamar Berhasil Ditambahkan!                         |\n");
    printf("+-----------------------------------------------------------+\n");
    newroomtype(&headtype, type, price, maxguests);
}

void newroomtype(struct roomtype **head, char type[20], int price, int maxguests)
{
    //This function will add a new room type to the room type linked list and update the roomtype.txt file accordingly
    struct roomtype *newtype = (struct roomtype *)malloc(sizeof(struct roomtype));
    strcpy(newtype->type, type);
    newtype->price = price;
    newtype->maxguests = maxguests;
    newtype->amount = 0;
    newtype->next = NULL;
    if(*head == NULL)
    {
        *head = newtype;
    }
    else
    {
        struct roomtype *temp = *head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newtype;
    }

    FILE *file = fopen("roomtype.txt", "a");
    if(file == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }
    fprintf(file, "%s,%d,%d,0\n", type, price, maxguests);
    fclose(file);
}

void menuremovetype(struct roomtype *head)
{
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                   PENGHAPUSAN JENIS KAMAR                 |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| List Jenis Kamar - = - = - = - = - = - = - = - = - = - =  |\n");
    printf("+-----------------------------------------------------------+\n");
    //List all room types
    struct roomtype *temp = head;
    while(temp != NULL)
    {
        printf("| %-16s | Rp.%-14d | %-6d | %-9d |\n", temp->type, temp->price, temp->amount, temp->maxguests);
        temp = temp->next;
    }

    printf("+-----------------------------------------------------------+\n");
    printf("| Masukkan Jenis Kamar yang Ingin Dihapus: ");
    char type[20];
    int typeflag = 0;
    do
    {
        scanf(" %[^\n]", type);
        //Check if the room type exists
        temp = head;
        while(temp != NULL)
        {
            if(strcasecmp(temp->type, type) == 0)
            {
                typeflag = 1;
                break;
            }
            temp = temp->next;
        }
        if(typeflag == 0)
        {
            printf("| Jenis Kamar tidak ditemukan! Masukkan kembali: ");
        }

    } while (typeflag == 0);
    
    removeroomtype(&head, type);
}

void removeroomtype(struct roomtype **head, char type[20])
{
    struct roomtype *temptype = *head;
    struct roomtype *prev = NULL;

    // Traverse the linked list to find the room type to remove
    while (temptype != NULL)
    {
        if (strcasecmp(temptype->type, type) == 0)
        {
            if (temptype->amount > 0)
            {
                printf("+-----------------------------------------------------------+\n");
                printf("| Tolong kosongkan jenis ruangan ini sebelum menghapus!     |\n");
                printf("+-----------------------------------------------------------+\n");
                return;
            }
            else
            {
                if (prev == NULL)  // This means we're at the head
                {
                    *head = temptype->next;
                }
                else
                {
                    prev->next = temptype->next;
                }
                free(temptype);
                printf("+-----------------------------------------------------------+\n");
                printf("| Jenis ruang telah berhasil dihapus!                       |\n");
                printf("+-----------------------------------------------------------+\n");
                break;
            }
        }
        prev = temptype;
        temptype = temptype->next;
    }

    if (temptype == NULL)
    {
        printf("Room type %s not found!\n", type);
        return;
    }

    // Update the roomtype.txt file with the new room types
    FILE *file = fopen("roomtype.txt", "w");
    if (file == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }
    temptype = *head;
    while (temptype != NULL)
    {
        fprintf(file, "%s,%d,%d\n", temptype->type, temptype->price, temptype->maxguests);
        temptype = temptype->next;
    }
    fclose(file);
}

void registration(struct floor *head, int roomnumber)
{
    //If the room number is valid and empty, the user will be brought here
    //The user will then be asked to input the guest's data
    //Traverse to the room
    struct floor *tempfloor = head;
    struct room *room = NULL;
    while(tempfloor != NULL)
    {
        struct room *temproom = tempfloor->headroom;
        while(temproom != NULL)
        {
            if(temproom->number == roomnumber)
            {
                room = temproom;
                break;
            }
            temproom = temproom->next;
        }
        if(room != NULL)
        {
            break;
        }
        tempfloor = tempfloor->next;
    }

        //If the user wants to rent the room, then the user will be asked to input the guest's data
        int i;
        char name[50];
        //Make an array of guests
        struct guest *guests = (struct guest *)malloc(room->maxguests * sizeof(struct guest));
        for(i = 0; i < room->maxguests; i++)
        {
            printf("+-----------------------------------------------------------+\n");
            printf("| Data Tamu %-3d                                             |\n", i + 1);
            printf("+-----------------------------------------------------------+\n");
            printf("| Nama Tamu (00 untuk mengosongkan): ");
            scanf(" %[^\n]", name);
            if(strcmp(name, "00") == 0)
            {
                strcpy(guests[i].name, "EMPTY");
                guests[i].gender = 'X';
                guests[i].age = 0;
                strcpy(guests[i].status, "Kosong");
                printf("| Tamu %d dikosongkan!\n", i + 1);
            }
            else
            {
                strcpy(guests[i].name, name);
                printf("| Gender (L/W): ");
                do
                {
                    scanf(" %c", &guests[i].gender);

                    if(guests[i].gender != 'L' && guests[i].gender != 'W' && guests[i].gender != 'l' && guests[i].gender != 'w')
                    {
                        printf("| Mohon masukkan L atau W!\n| Gender (L/W): ");
                    }
                } while (guests[i].gender != 'L' && guests[i].gender != 'W' && guests[i].gender != 'l' && guests[i].gender != 'w');
                
                printf("| Age: ");
                do
                {
                    scanf("%d", &guests[i].age);

                    if(guests[i].age < 0 || guests[i].age > 100)
                    {
                        printf("| Mohon masukkan angka dalam rentang 0-100!: ");
                    }
                } while (guests[i].age < 0 || guests[i].age > 100); 

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
        }

        room->guests = guests;
        strcpy(room->status, "Terisi");
        printf("| Durasi Sewa (Hari): ");
        scanf("%d", &room->days);
        printf("+-----------------------------------------------------------+\n");
        printf("| Ruang Berhasil Disewa!                                    |\n");
        printf("+-----------------------------------------------------------+\n");
        //Update the roomdata.txt file with the new guest data

        FILE *file = fopen("roomdata.txt", "w");
        if(file == NULL)
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
                fprintf(file, "%d,%d\n", temproom->maxguests, temproom->days);
                if(temproom->guests != NULL)
                {
                    for(i = 0; i < temproom->maxguests; i++)
                    {
                        fprintf(file, "%s,%c,%d\n", temproom->guests[i].name, temproom->guests[i].gender, temproom->guests[i].age);
                    }
                }
                else
                {
                    for(i = 0; i < temproom->maxguests; i++)
                    {
                        fprintf(file, "EMPTY,X,0\n");
                    }
                }
                temproom = temproom->next;
            }
            tempfloor = tempfloor->next;
        }
    fclose(file);
}

void searchguest(struct floor *head, struct roomtype *headtype)
{
    // This function will search for a guest in the hotel, based on the flag that the user inputs
    // The user can search for a guest based on the room number, guest name, or guest status
    int flag;
    char nama[50];
    int found = 0;
    struct floor *temp = head;
    struct roomtype *temptype = headtype;
    struct room *temproom;
    
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                       PENCARIAN TAMU                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Kategori - = - = - = - = - = - = - = - = - = - = - = - =  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| 1 | Nama Tamu                                             |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 2 | Jenis Kelamin Tamu                                    |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 3 | Umur Tamu                                             |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| 4 | Status Umur Tamu                                      |\n");
    printf("+---+-------------------------------------------------------+\n");
    printf("| Masukkan kategori pencarian: ");
    do
    {
        scanf("%d", &flag);

        if(flag < 1 || flag > 4)
        {
            printf(" Kategori tidak valid!\n| Masukkan kategori pencarian: ");
        }
    } while (flag < 1 || flag > 4);

    if(flag == 1)
    {
        printf("+-----------------------------------------------------------+\n");
        printf("| Masukkan Nama Tamu:                                       |\n");
        printf("+-----------------------------------------------------------+\n| ");
        scanf(" %[^\n]", nama);
        
        while(temp != NULL)
        {
            temproom = temp->headroom;
            while(temproom != NULL)
            {
                if(strcmp(temproom->status, "Terisi") == 0)
                {
                    for(int i = 0; i < temproom->maxguests; i++)
                    {
                        char tempname[50], tempnama[50];
                        strcpy(tempname, temproom->guests[i].name);
                        strcpy(tempnama, nama);
                        strlwr(tempname);
                        strlwr(tempnama);
                        if(strstr(tempname, tempnama) != NULL)
                        {
                            if(found == 0)
                            {
                                printf("+-----------------------------------------------------------+\n");
                                printf("| Tamu ditemukan!                                           |\n");
                                printf("+-----------------------------------------------------------+\n");
                            }
                            printf("| Nama Tamu: %-25s | Ruang Tamu: %-6d |\n", temproom->guests[i].name, temproom->number);
                            found = 1;
                        }
                    }
                }
                temproom = temproom->next;
            }
            temp = temp->next;
            printf("+-----------------------------------------------------------+\n");
        }
        if(found == 0)
        {
            printf("| Tamu tidak ditemukan!                                     |\n");
            printf("+-----------------------------------------------------------+\n");
        }
        system("pause");
        system("cls");
    }

    else if(flag == 2 || flag == 3 || flag == 4)
    {
        switch(flag)
        {
            case 2:
            {
                printf("+-----------------------------------------------------------+\n");
                printf("| Masukkan Gender Tamu (L/W)                                |\n");
                printf("+-----------------------------------------------------------+\n| ");
                char searchgender;
                do
                {
                    scanf(" %c", &searchgender);

                    if(searchgender != 'L' && searchgender != 'W' && searchgender != 'l' && searchgender != 'w')
                    {
                        printf(" Kategori tidak valid!\n| Masukkan kategori pencarian: ");
                    }
                } while (searchgender != 'L' && searchgender != 'W' && searchgender != 'l' && searchgender != 'w');
                
                temp = head;
                while(temp != NULL)
                {
                    temproom = temp->headroom;
                    while(temproom != NULL)
                    {
                        if(strcmp(temproom->status, "Terisi") == 0)
                        {
                            for(int i = 0; i < temproom->maxguests; i++)
                            {
                                if(tolower(temproom->guests[i].gender) == tolower(searchgender))
                                {
                                    if(found == 0)
                                    {
                                        printf("+-----------------------------------------------------------+\n");
                                        printf("| Tamu ditemukan!                                           |\n");
                                        printf("+-----------------------------------------------------------+\n");
                                    }
                                    printf("| Nama Tamu: %-25s | Ruang Tamu: %-6d |\n", temproom->guests[i].name, temproom->number);
                                    found = 1;
                                }
                            }
                        }
                        temproom = temproom->next;
                    }
                    temp = temp->next;
                    printf("+-----------------------------------------------------------+\n");
                }
                if(found == 0)
                {
                    printf("| Tamu tidak ditemukan!                                     |\n");
                    printf("+-----------------------------------------------------------+\n");
                }
                system("pause");
                system("cls");
                break;
            }

            case 3:
            {
                printf("+-----------------------------------------------------------+\n");
                printf("| Masukkan Umur Tamu (1-100)                                |\n");
                printf("+-----------------------------------------------------------+\n| ");
                int searchage;
                do
                {
                    scanf("%d", &searchage);

                    if(searchage < 0 || searchage > 100)
                    {
                        printf(" Kategori tidak valid!\n| Masukkan kategori pencarian: ");
                    }
                } while (searchage < 0 || searchage > 100);
                temp = head;
                while(temp != NULL)
                {
                    temproom = temp->headroom;
                    while(temproom != NULL)
                    {
                        if(strcmp(temproom->status, "Terisi") == 0)
                        {
                            for(int i = 0; i < temproom->maxguests; i++)
                            {
                                if(temproom->guests[i].age == searchage)
                                {
                                    if(found == 0)
                                    {
                                        printf("+-----------------------------------------------------------+\n");
                                        printf("| Tamu ditemukan!                                           |\n");
                                        printf("+-----------------------------------------------------------+\n");
                                    }
                                    printf("| Nama Tamu: %-25s | Ruang Tamu: %-6d |\n", temproom->guests[i].name, temproom->number);
                                    found = 1;
                                }
                            }
                        }
                        temproom = temproom->next;
                    }
                    temp = temp->next;
                    printf("+-----------------------------------------------------------+\n");
                }
                if(found == 0)
                {
                    printf("| Tamu tidak ditemukan!                                     |\n");
                    printf("+-----------------------------------------------------------+\n");
                }
                system("pause");
                system("cls");
                break;
            }

            case 4:
            {
                printf("+-----------------------------------------------------------+\n");
                printf("| Masukkan Status Tamu (Anak / Remaja / Dewasa / Lansia)    |\n");
                printf("+-----------------------------------------------------------+\n| ");
                char searchstatus[20];
                do
                {
                    scanf(" %[^\n]", searchstatus);

                    if(strcasecmp(searchstatus, "Anak") != 0 && strcasecmp(searchstatus, "Remaja") != 0 && strcasecmp(searchstatus, "Dewasa") != 0 && strcasecmp(searchstatus, "Lansia") != 0)
                    {
                        printf(" Kategori tidak valid!\n| Masukkan kategori pencarian: ");
                    }
                } while (strcasecmp(searchstatus, "Anak") != 0 && strcasecmp(searchstatus, "Remaja") != 0 && strcasecmp(searchstatus, "Dewasa") != 0 && strcasecmp(searchstatus, "Lansia") != 0);
                
                temp = head;
                while(temp != NULL)
                {
                    temproom = temp->headroom;
                    while(temproom != NULL)
                    {
                        if(strcmp(temproom->status, "Terisi") == 0)
                        {
                            for(int i = 0; i < temproom->maxguests; i++)
                            {
                                if(strcasecmp(temproom->guests[i].status, searchstatus) == 0)
                                {
                                    if(found == 0)
                                    {
                                        printf("+-----------------------------------------------------------+\n");
                                        printf("| Tamu ditemukan!                                           |\n");
                                        printf("+-----------------------------------------------------------+\n");
                                    }
                                    printf("| Nama Tamu: %-25s | Ruang Tamu: %-6d |\n", temproom->guests[i].name, temproom->number);
                                    found = 1;
                                }
                            }
                        }
                        temproom = temproom->next;
                    }
                    temp = temp->next;
                    printf("+-----------------------------------------------------------+\n");
                }
                if(found == 0)
                {
                    printf("| Tamu tidak ditemukan!                                     |\n");
                    printf("+-----------------------------------------------------------+\n");
                    
                }
                system("pause");
                system("cls");
                break;
            }
        }
    }        
}

void statupdater(int *floors, int *rooms)
{
    //This function's purpose is to read structure.txt file and update the floors and rooms variables
    FILE *file = fopen("structure.txt", "r");
    if(file == NULL)
    {
        printf("File tidak ditemukan!\n");
        return;
    }
    fscanf(file, "%d,%d", floors, rooms);
    fclose(file);
}

void guestviewer(struct floor *head)
{
    //This function's purpose is to print the guests in a specific room
    //The user will be asked to input the room number
    printf("||_________________________________________________________||\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|                   Proyek UAS Kelompok 05                  |\n");
    printf("|                       PENCARIAN TAMU                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Pencarian Tamu - = - = - = - = - = - = - = - = - = - = -  |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Masukkan Nomor Ruangan: ");
    int roomnumber;
    scanf("%d", &roomnumber);

    //Travel each floor to find the room
    struct floor *temp = head;
    while(temp != NULL)
    {
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            if(temp2->number == roomnumber)
            {
                //Check if the room is empty
                if(strcmp(temp2->status, "Kosong") == 0)
                {
                    printf("+-----------------------------------------------------------+\n");
                    printf("| Ruangan Kosong!                                           |\n");
                    printf("+-----------------------------------------------------------+\n");
                    system("pause");
                    system("cls");
                    return;
                }
                else
                {
                    //Print the guests in the room
                    printf("+-----------------------------------------------------------+\n");
                    printf("| Data Ruangan %-44d |\n", roomnumber);
                    printf("+-----------------------------------------------------------+\n");
                    for(int i = 0; i < temp2->maxguests; i++)
                    {
                        if(strcmp(temp2->guests[i].name, "EMPTY") != 0)
                        {
                            printf("| Nama Tamu %-2d: %-43s |\n", i + 1, temp2->guests[i].name);
                            printf("| Jenis Kelamin: %-42c |\n", temp2->guests[i].gender);
                            printf("| Umur - Status: %-3d - %-36s |\n", temp2->guests[i].age, temp2->guests[i].status);
                            printf("+-----------------------------------------------------------+\n");
                        }
                    }
                    system("pause");
                    system("cls");
                    return;
                }
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    printf("+-----------------------------------------------------------+\n");
    printf("| Ruangan tidak ditemukan!                                  |\n");
    printf("+-----------------------------------------------------------+\n");
    system("pause");
    system("cls");
}