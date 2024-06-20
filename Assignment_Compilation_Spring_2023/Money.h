#ifndef MONEY_H_INCLUDED
#define MONEY_H_INCLUDED
#pragma once
#include <stdbool.h>
#include "Dogs.h"

typedef struct betAmount
{
    int number;
    int wager;
    char bet[100];
}betAmount;

typedef struct race
{
    bool won;
    betAmount betA;
    dog first;
    struct race *next;
}race;

race* start = NULL;
int funds =0;
bool winner(betAmount* bets, race* races)
{
    dog firstPlace = races->first;
    if(strcmp(bets->bet, firstPlace.name)==0)
    {
        int index = searchDogName(bets->bet);
        dog newList = dlist[index];
        int wager = newList.amount * bets->wager;
        funds = funds + wager;
        printf("\n %s was in first place, You won %d.", bets->bet, wager);
        printf("Your new balance of funds is %d.", funds);
        return true;
    }
    else
    {
        int index = searchDogName(bets->bet);
        dog newList = dlist[index];
        int wager = newList.amount * bets->wager;
        funds = funds - wager;
        printf("\n %s was not in first place, You lost %d.", bets->bet, wager);
        printf("Your new balance of funds is %d.", funds);
        return false;
    }
}

void game(betAmount bets)
{
    shuffle();
    race* newDog = (race*)malloc(sizeof(race));
    newDog->first = dlist[0];
    newDog->betA = bets;
    newDog->next = NULL;
    newDog->won = winner(&bets, newDog);

    if(start == NULL)
        start = newDog;
    else
    {
        race* ptr = start;
        while(ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = newDog;
        free(ptr);
    }
}

void results ()
{
    printf("\n\nRACE RESULTS SO FAR");
    printf("\n----------------------------------------------");
    race* ptr = start;
    while (ptr->next != NULL)
    {
        betAmount bets = ptr->betA;
        dog dogs = ptr->first;
        printf("\nRace number %d", bets.number);
        printf("\nRace status %s", ptr->won ? "WON" : "LOST");
        printf("\nBet on %s", dogs.name);
        printf("\n-----------------------------------------");
        ptr = ptr->next;
    }
    betAmount bets = ptr->betA;
    dog dogs = ptr->first;
    printf("\nRace number %d", bets.number);
    printf("\nRace status %s", ptr->won ? "WON" : "LOST"); //if check to see if race status was won or lost
    printf("\nBet on %s", dogs.name);
}

//banking menu and transactions
void banking_transactions()
{
    bool flag = true;
    while (flag)
    {
        printf("\n\nBANKING MENU");
        printf("\n[W]ithdraw funds");
        printf("\n[D]eposit funds");
        printf("\n[E]xit bank");
        printf("\nPlease make a selection: ");

        char option;
        int amount;
        scanf(" %c", &option);
        switch (option)
        {
            case 'W':
            // withdraw funds
                printf("\nAmount: ");
                scanf(" %d", &amount);
                if (amount > funds)
                {
                    printf("\nInsufficient funds.");
                }
                else
                {
                    funds = funds - amount;
                    printf("\nUpdated funds: %d", funds);
                }
                break;
            case 'D':
            // deposit funds
                printf("\nAmount: ");
                scanf(" %d", &amount);
                funds = funds + amount;
                printf("\nUpdated funds: %d", funds);
                break;
            case 'E':
                flag = false;
                break;
            default:
                printf("\nUnrecognized selection %c", option);
                break;
        }
    }
}

void gamble(int count)
{
    int wagers = 0;
    char name[100];
    printf("\nEnter wager: ");
    scanf(" %d", &wagers);
    printf("\nDogs on race track: ");
    displayDog();
    printf("\nEnter a dog's name: ");
    scanf(" %[^\n]s", name);
    getchar();
    int index = searchDogName(name);
    if (index == -1) //check to see if dog is racing
    {
        printf("\n %s is not racing!", name);
    }
    else //bet then play game
    {
        betAmount* bets = (betAmount*)malloc(sizeof(betAmount));
        strcpy(bets->bet, name);
        bets->number = count;
        bets->wager = wagers;
        game(*bets);
        free(bets);
    }
}

//start the game/race
void start_game(int amounts[], int odds[])
{
    char namesofDog[9][32] = { "Billy","Renee","Lisa","Suzy","Joey",
    "Kyle","Spot","Maxine","Charlie" };
    for (int i = 0; i < NUMBER_DOGS; i++)
    {
        dlist[i].amount = amounts[i];
        dlist[i].odd = odds[i];
        strcpy(dlist[i].name, namesofDog[i]);
    }
}
//Implement method to display menu
void displayTrackMenu()
{
printf("\n\nDOG TRACK MENU");
printf("\n[G]amble");
printf("\n[B]anking");
printf("\n[R]esults of each race that Greg wagered");
printf("\n[L]eave the dog track");
printf("\n\nPlease make a selection: ");
}
//implement the method to track the dogs
void track_dogs()
{
    bool check = true;
    int count = 0;
    while (check)
    {
        printf("\n\nDOG TRACK MENU");
        printf("\n[G]amble");
        printf("\n[B]anking");
        printf("\n[R]esults of each race that Greg wagered");
        printf("\n[L]eave the dog track");
        printf("\n\nPlease make a selection: ");
        char option;
        scanf(" %c", &option);
        printf("\n\n");
        switch (option)
        {
            case 'G':
                gamble(++count);
                break;
            case 'B':
                banking_transactions();
                break;
            case 'R':
            // display race outcomes
                results();
                break;
            case 'L':
                printf("\nLeaving the dog track!");
                check = false;
                break;
            default:
                printf("\nUnrecognized selection %c", option);
                break;
        }
    }
}
#endif // MONEY_H_INCLUDED
