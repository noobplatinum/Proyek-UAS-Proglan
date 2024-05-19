
void changeRoom() {
    FILE *roomType = fopen("roomtype.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    char editType[20];
    char newType[20];
    int newPrice;
    int newCapacity;
    int newRoomNumber;
    char buffer[50];
    char originalLine[50];
    printf("Masukkan Tipe Kamar yang Ingin Diubah : ");
    scanf("%s", editType);

    printf("Masukkan Tipe Kamar Baru : ");
    scanf("%s", newType);
    printf("Masukkan Harga Baru : ");
    scanf("%d", &newPrice);
    printf("Masukkan Kapasitas Baru : ");
    scanf("%d", &newCapacity);
    printf("Masukkan Jumlah Kamar per lantai Baru : ");
    scanf("%d", &newRoomNumber);

    int isFirstLine = 1;
    while (fgets(buffer, 50, roomType) != NULL)
    {
        strcpy(originalLine, buffer);  // Store the original line
        char *token = strtok(buffer, ",");
        if (strcmp(editType, token) != 0) {
            if (isFirstLine) {
                fprintf(temp, "%s", originalLine);  // Write the original line
                isFirstLine = 0;
            } else {
                fprintf(temp, "%s", originalLine);  // Write the original line
            }
        }   
    }
    fprintf(temp, "%s,%d,%d,%d", newType, newPrice, newCapacity, newRoomNumber);
    
    fclose(roomType);
    fclose(temp);
    
    roomType = fopen("roomtype.txt", "w");
    temp = fopen("temp.txt", "r");
    
    while (fgets(buffer, 50, temp) != NULL) {
        fprintf(roomType, "%s", buffer);
    }

    fclose(roomType);
    fclose(temp);
} 



// menambah tipe kamar  ===================================================
void addroomtype()
{
    FILE *roomType = fopen("roomtype.txt", "a");
    char type[20];
    int price;
    int capacity;
    int roomNumber;
    printf("Masukkan Tipe Baru : ");
    scanf("%s", type);
    printf("Masukkan Harga : ");
    scanf("%d", &price);
    printf("Masukkan Kapasitas : ");
    scanf("%d", &capacity);
    printf("Masukkan Jumlah Kamar per lantai : ");
    scanf("%d", &roomNumber);
    
    fprintf(roomType, "\n%s,%d,%d,%d", type, price, capacity, roomNumber);
    fclose(roomType);
}



// hapus tipe kamar ======================================================
void deleteroomtype()
{
    FILE *roomType = fopen("roomtype.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char tempType[50];
    char originalLine[50];
    char deleteType[20];
    printf("Masukkan Tipe Kamar yang Ingin Dihapus : ");
    scanf("%s", deleteType);

    int isFirstLine = 1;
    while (fgets(tempType, 50, roomType) != NULL)
    {
        strcpy(originalLine, tempType);  // Store the original line
        char *token = strtok(tempType, ",");
        if (strcmp(deleteType, token) != 0) {
            if (isFirstLine) {
                fprintf(temp, "%s", originalLine);  // Write the original line
                isFirstLine = 0;
            } else {
                fprintf(temp, "%s", originalLine);  // Write the original line
            }
        }   
    }
    fclose(roomType);
    fclose(temp);
    
    roomType = fopen("roomtype.txt", "w");
    temp = fopen("temp.txt", "r");
    
    while (fgets(tempType, 50, temp) != NULL) {
        fprintf(roomType, "%s", tempType);
    }
    
    fclose(roomType);
    fclose(temp);
}
