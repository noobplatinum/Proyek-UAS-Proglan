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
                        case 0:
                            strcpy(guests[i].status, "Kosong");
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
                newroom->number = temp->number * 1000 + roomnumber;
                strcpy(newroom->type, temptype->type);
                strcpy(newroom->status, "Kosong");
                newroom->days = 0;
                newroom->maxguests = temptype->maxguests;
                newroom->price = temptype->price;
                newroom->guests = NULL;
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
                printf("Room type %s has rooms in the hotel. Please empty the rooms first before removing the room type.\n", type);
                return;
            }
            else
            {
                printf("Room found!\n");
                if (prev == NULL)  // This means we're at the head
                {
                    *head = temptype->next;
                }
                else
                {
                    prev->next = temptype->next;
                }
                free(temptype);
                printf("Room freed!\n");
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

void registration(struct floor *head, int roomnumber, char type[20])
{
    //If the room number is valid and empty, the user will be brought here
    //The user will then be asked to input the guest's data
    printf("Room is available!\n");
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
    //Print the room's type data first
    printf(" Room Number: %d\n Type: %s\n Price: %d\n Max guests: %d\n", room->number, room->type, room->price, room->maxguests);
    printf("Do you want to rent this room? (Y/N): ");
    char answer;
    scanf(" %c", &answer);  
    if(answer == 'Y' || answer == 'y')
    {
        //If the user wants to rent the room, then the user will be asked to input the guest's data
        int i;
        char name[50];
        //Make an array of guests
        struct guest *guests = (struct guest *)malloc(room->maxguests * sizeof(struct guest));
        for(i = 0; i < room->maxguests; i++)
        {
            printf("Guest %d\n", i + 1);
            printf("Name (Type 00 for none): ");
            scanf(" %[^\n]", name);
            if(strcmp(name, "00") == 0)
            {
                strcpy(guests[i].name, "EMPTY");
                guests[i].gender = 'X';
                guests[i].age = 0;
                strcpy(guests[i].status, "Kosong");
                printf("Guest %d is empty!\n", i + 1);
            }
            else
            {
                strcpy(guests[i].name, name);
                printf("Gender (L/W): ");
                scanf(" %c", &guests[i].gender);
                printf("Age: ");
                do
                {
                    scanf("%d", &guests[i].age);

                    if(guests[i].age < 0 || guests[i].age > 100)
                    {
                        printf("Invalid age! Please enter a valid age: ");
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
        printf("Renting period: ");
        scanf("%d", &room->days);
        printf("Room rented!\n");
        //Update the roomdata.txt file with the new guest data

        FILE *file = fopen("roomdata.txt", "w");
        if(file == NULL)
        {
            printf("File tidak ditemukan!\n");
            return;
        }

        struct floor *tempfloor = head;
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
        printf("Debug Finish!\n");
    }
    else
    {
        printf("Administration Cancelled!\n");
        return;
    }
}

void administration(struct floor *head)
{
    //This function's purpose is to print the number of rooms in the hotel for the user to pick
    //After picking, the user will then be brought to the administration menu

    //For each floor, print all the rooms
    struct floor *temp = head;
    while(temp != NULL)
    {
        printf("Floor number: %d\n", temp->number);
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            printf("Room number: %d, Type: %s, Status: %s, Max guests: %d, Price: %d\n", temp2->number, temp2->type, temp2->status, temp2->maxguests, temp2->price);
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    printf("Please enter the room number you want to rent: ");
    int roomnumber;
    scanf("%d", &roomnumber);
    //First, check if the room number is valid
    //Also, check if the room is empty
    temp = head;
    struct room *room = NULL;
    while(temp != NULL)
    {
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            if(temp2->number == roomnumber)
            {
                room = temp2;
                break;
            }
            temp2 = temp2->next;
        }
        if(room != NULL)
        {
            break;
        }
        temp = temp->next;
    }
    if(room == NULL)
    {
        printf("Room number not found!\n");
        return;
    }
    if(strcmp(room->status, "Kosong") != 0)
    {
        printf("Room is not empty!\n");
        return;
    }
    //If the room is empty, then the user can rent the room
    registration(head, roomnumber, room->type);
}

int main() 
{
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
    fclose(file2);
    struct floor *head = NULL;
    // Initialize the floors and rooms
    initallfloors(&head, floor, room, headtype);
    // Initialize the guests
    initguest(floor, room, head, head->headroom, headtype);
    // Print out the data
    struct floor *temp = head;
    int i;
    while(temp != NULL)
    {
        printf("Floor number: %d\n", temp->number);
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            printf("Room number: %d, Type: %s, Status: %s, Max guests: %d, Price: %d\n", temp2->number, temp2->type, temp2->status, temp2->maxguests, temp2->price);
            if(strcmp(temp2->status, "Kosong") != 0)
            {
                for(i = 0; i < temp2->maxguests; i++)
                {
                    if(temp2->guests[i].gender != 'X');
                    {
                        printf("Guest %d: %s, %c, %s, %d\n", i + 1, temp2->guests[i].name, temp2->guests[i].gender, temp2->guests[i].status, temp2->guests[i].age);
                    }
                }
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    printf("+===============================================================================================+\n");
    printf("+====================================TESTING THE FUNCTIONS======================================+\n");
    printf("+===============================================================================================+\n");
    //Test the roomchanger function
    //Change the roomtype from 5 standard rooms and 1 deluxe room to 3 standard rooms and 3 deluxe rooms

    newroomtype(&headtype, "Super Suite", 5000000, 15);
    printf("Room type added!\n");
    removeroomtype(&headtype, "Standar");
    printf("Room type removed!\n");

    while(headtype != NULL)
    {
        printf("Type: %s, Price: %d, Max guests: %d, Amount: %d\n", headtype->type, headtype->price, headtype->maxguests, headtype->amount);
        headtype = headtype->next;
    }

    FILE *file3 = fopen("roomtype.txt", "w");
    if(file3 == NULL)
    {
        printf("File tidak ditemukan!\n");
        return 1;
    }   
    fprintf(file3, "Standard,1000000,3,3\n");
    fprintf(file3, "Deluxe,2000000,5,3\n");
    fclose(file3);

    roomchanger(head, headtype);
    //Print out the data again
    temp = head;
    while(temp != NULL)
    {
        printf("Floor number: %d\n", temp->number);
        struct room *temp2 = temp->headroom;
        while(temp2 != NULL)
        {
            printf("Room number: %d, Type: %s, Status: %s, Max guests: %d, Price: %d\n", temp2->number, temp2->type, temp2->status, temp2->maxguests, temp2->price);
            if(strcmp(temp2->status, "Kosong") != 0)
            {
                for(i = 0; i < temp2->maxguests; i++)
                {
                    if(temp2->guests[i].gender != 'X');
                    {
                        printf("Guest %d: %s, %c, %s, %d\n", i + 1, temp2->guests[i].name, temp2->guests[i].gender, temp2->guests[i].status, temp2->guests[i].age);
                    }
                }
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    printf("Debug Finish\n");
    return 0;
}