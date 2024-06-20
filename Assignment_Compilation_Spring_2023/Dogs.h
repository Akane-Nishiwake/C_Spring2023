#ifndef DOGS_H_INCLUDED
#define DOGS_H_INCLUDED
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define NUMBER_DOGS 9


typedef struct dog
{
    char name[100];
    int amount;
    int odd;
}dog;

dog dlist[NUMBER_DOGS];

//use bubble sort method to sort dogs by name
void sortDog()
{
    for(int i =0; i < NUMBER_DOGS -1; i++)
    {
        for(int j = i + 1; j < NUMBER_DOGS; j++)
        {
            if(strcmp(dlist[i].name,dlist[j].name) > 0)
            {
                dog temp = dlist[i];
                dlist[i] = dlist[j];
                dlist[j] = temp;
            }
        }
    }
}

//search for a specific dog name
int searchDogName(char name[])
{
    sortDog();
    int index;
    int high = NUMBER_DOGS - 1;
    int low = 0;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        if(strcmp(dlist[mid].name, name) == 0)
        {
            index = mid;
            break;
        }
        else if (strcmp(dlist[mid].name,name) > 0)
            high = mid -1;
        else if (strcmp(dlist[mid].name,name) < 0)
            low = mid -1;
    }
    return index;
}

//shuffle dogs by using rand()
void shuffle()
{
    srand(time(NULL));
    for(int i = 0; i < NUMBER_DOGS -1; i++)
    {
        int j = rand() % (i+1);
        dog temp = dlist[i];
        dlist[i] = dlist[j];
        dlist[j] = temp;
    }
}

//display all stats of dog
void displayDog()
{
    printf("\n\n%-20s | %-20s | %-20s", "Dog Name", "Payout", "Odds of Winning");
    for(int i = 0; i < NUMBER_DOGS; i++)
    {
        char payout[10];
        char odds[10];
        sprintf(payout, "%d TO 1", dlist[i].amount);
        sprintf(odds, "%d %%", dlist[i].odd);
        printf("\n%-20s | ", dlist[i].name);
        printf("%-20s | ", payout);
        printf("%-20s", odds);
    }
}
#endif // DOGS_H_INCLUDED
