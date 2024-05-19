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
    printf("Debug Finish\n");
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
    decreasesize(&head, &floor, &room, headtype, 4, 1);
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