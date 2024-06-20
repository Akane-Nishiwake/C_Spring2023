#ifndef ASSIGNMENTCOMILATION_H_INCLUDED
#define ASSIGNMENTCOMILATION_H_INCLUDED


#include <ctype.h>
#include <time.h>

#include "Money.h"

#define VOTERS 1000
#define CARDS 52
#define PLAYERS 3
#define HAND 5


//These are in no particular order
//Assignment 1
 int isPrime (int input, int _isPrime)
{
    if(_isPrime == 1) //if prime is 1 then it is prime
        return 1;
    if(input%_isPrime == 0) //if prime is not 1 it is not prime
        return 0;
    return isPrime(input, _isPrime - 1); //recursive statement
}
 void inputCheck()
{
    int userInput;
    if(scanf("%d", &userInput)> 0) //grab user input and validate if it is an int
    {
        if(userInput>= 2 && userInput <= INT_MAX)//check to see if it is with in the parameters
        {
            if(isPrime(userInput, userInput/2)) //check to see if prime through recursion
                printf("%d is prime", userInput);
            else
                printf("%d is not prime", userInput);
        }
        else //if input is not with in the parameters
        {
            printf("That is not a number between 2 and %d \n", INT_MAX);
            fflush(stdin);
        return inputCheck(); //recursive statement
        }
    }
    else //if input is not an int
    {
        printf("That is not a valid input.\n");
        fflush(stdin); //clears input buffer
        return inputCheck();
    }
}
void Assignment01()
{
    printf("Please input a number between 2 and %d \n", INT_MAX); //Ask user for input
    inputCheck();
}

//Assignment 2
 typedef struct NAME
{
    char firstName[51]; //one more than needed to take in account of the null terminator (\0)
    char middleInitial;
    char lastName[71];
}NAME;
 typedef struct VOTER
{
    NAME name;
    char gender;
    int favNum;
    float weight;
    char* weightStatement;
    int won;
}VOTER;
 void MainMenu()
{
    printf("\t\t\t\tMain Menu\n");
    printf("1.Create Voter\n");
    printf("2. Write to File\n");
    printf("3. Print All Voters\n");
    printf("4. Play Lottery\n");
    printf("5. Exit\n");
    printf("Enter Choice: ");
}
 float Validate(float min, float max)
{
    float num;
    do {
        printf("Please enter a number between %.2f and %.2f: ", min, max);
        scanf("%f", &num);
        if (num < min || num > max) {
            printf("Invalid input. Please try again.\n");
        }
    } while (num < min || num > max);
    return num;
}
 void ChangeCase(char* chara)
{
    if(chara[0] != '\0');//if it is not the null terminator
    {
        chara[0]=toupper(chara[0]);
        for(int i = 1; chara[i] != '\0'; i++)//while the character is not null terminator
        {
            chara[i] = tolower(chara[i]);
        }
    }
}
 char FixGender(char gender)
{
    gender = toupper(gender);
    switch(gender)//if the gender is M/F/O return it
    {
    case 'M':
    case 'F':
    case 'O':
        return gender;
    default://if it is not one of the ones above return U
        return 'U';
    }
}
 void printAllVoters(VOTER vote[VOTERS],int size)
{
    for(int i = 0; i <size; i++)
    {
        printf("Voter #%d\n",i+1);
        printf("First Name : %s\tMiddle Initial: %c\tLast Name: %s\tGender: %c\nFavorite Number: %d\tLotteries Won: %d\tWeight: %.2f\tWeight Category: %s\n", vote[i].name.firstName,vote[i].name.middleInitial,vote[i].name.lastName,vote[i].gender,vote[i].favNum,vote[i].won,vote[i].weight,vote[i].weightStatement);
    }
}
 void PrintLotto(VOTER vote[VOTERS], int size)
{
    printf("\nLottery Results\n");
    for(int i = 0; i < 500; i++)
    {
        int winner = rand() % 1000;
        printf("Drawing %d: %d\n", i+1, winner);
        for(int j = 0; j <size; j++)
        {
            if(vote[j].favNum == winner)
                vote[j].won++;
        }
    }
}
 void WeightCategory (VOTER vote[VOTERS])
{
    for(int i = 0; i < 1; i++)
    {
        if(vote[i].weight < 125)
        {
            if(vote[i].gender == 'M')
                vote[i].weightStatement = "SKINNY";
            else if(vote[i].weight == 'F')
                vote[i].weightStatement = "SKINNY";
            else
                vote[i].weightStatement = "SKINNY";
        }
        else if(vote[i].weight >= 125 && vote[i].weight <= 200)
        {
            if(vote[i].gender == 'M')
                vote[i].weightStatement = "FIT";
            else if(vote[i].weight == 'F')
                vote[i].weightStatement = "FIT";
            else
                vote[i].weightStatement = "FIT";
        }
        else
        {
            if(vote[i].gender == 'M')
                vote[i].weightStatement = "FAT";
            else if(vote[i].weight == 'F')
                vote[i].weightStatement = "FAT";
            else
                vote[i].weightStatement = "FAT";
        }
    }
}
void ClearConsole()
{
    system("pause");
    system("cl");
}
int Assignment02()
{
    srand(time(NULL));
    int choice = 0;
    FILE* file = fopen("input.bin", "r"); //read the file from the source folder
    if(file == NULL)
    {
        perror("Could not open file.");//if the file is not found let the user know
        return 1;
    }
    int size;
    fread(&size, sizeof(int),1,file);
    VOTER vote[VOTERS];//create the voter container
    int numVoters = 0;
    fclose(file);
    while(choice != 5)
    {
        MainMenu();
        scanf("%d", &choice);
        switch(choice)
        {
        case 1: //create voter
            printf("Pleaser enter the voter information:\n");
            VOTER voter;
            printf("Name (First): ");
            scanf("%51s", voter.name.firstName);
            ChangeCase(voter.name.firstName);
            printf("Middle Initial: ");
            scanf(" %c", &voter.name.middleInitial);
            voter.name.middleInitial = toupper(voter.name.middleInitial);
            printf("Name (Last): ");
            scanf("%71s", voter.name.lastName);
            ChangeCase(voter.name.lastName);
            printf("Gender (M/F/O): ");
            scanf(" %c",&voter.gender);
            voter.gender = FixGender(voter.gender);
            printf("Favorite Number: ");
            voter.favNum = (int)Validate(1.0f,999.0f);
            printf("Weight: ");
            voter.weight = Validate(10.0f, 999.0f);
            voter.won = 0;
            vote[numVoters++] = voter;
            size = numVoters;
            WeightCategory (vote);
            ClearConsole();
            break;
        case 2://write to binary
            file = fopen("input.bin","wb");
            if(file == NULL)
            {
                printf("File could not be opened.");
                return 1;
            }
            for(int i = 0; i <numVoters; i++)
            {

                fprintf(file, "First Name : %s\tMiddle Initial: %c\tLast Name: %s\tGender: %c\nFavorite Number: %d\tLotteries Won: %d\tWeight: %.2f\tWeight Category: %s\n", vote[i].name.firstName,vote[i].name.middleInitial,vote[i].name.lastName,vote[i].gender,vote[i].favNum,vote[i].won,vote[i].weight,vote[i].weightStatement);
            }
            fclose(file);
            ClearConsole();
            break;
        case 3:
            printAllVoters( vote,size);
            ClearConsole();
            break;
        case 4:
            PrintLotto(vote,size);
            ClearConsole();
            break;
        case 5:
            printf("You have ended the program.");
            break;
        default:
            printf("Invalid input.");
            ClearConsole();
            break;
        }
    }
    return 0;
}

//Assignment 3
 typedef struct{
 int month;
 int day;
 int year;
} DATE; //individual components of the date
 typedef struct{
char name[20];
DATE birthday;
char gender;
float annualIncome;
}PERSON; //individual components of a person
int isGenderValid(char inputGender)
{
    if(inputGender == 'M' || inputGender == 'F' || inputGender == 'O'
       || inputGender == 'm' || inputGender == 'f' || inputGender == 'o')
        return 1;
    else
        return 0;
}
 int isIncomeValid(float inputIncome)
{
    if(inputIncome > 0.0f && inputIncome < 1000001.0f)
        return 1;
    else
        return 0;
}
int isDateValid (int inputDay, int inputMonth, int inputYear)
{
    if(inputYear > 0) //if the input year exists
    {
        if(inputMonth > 0 && inputMonth < 13)//if the month is between 1 and 12
        {
            if(inputMonth == 2)//if it is february
            {
                if(inputYear % 4 == 0)//for every 4th year
                {
                    if (inputDay < 30)//if it is one of the 29 days of the month
                        return 1; //return true
                    else
                        return 0;
                }
                if(inputDay < 29) //if it is one of the 28 days of the month
                    return 1;
                else
                    return 0;
            }
            else //if it is not february
            {
                if(inputDay < 32)
                {
                        //if the month is one of the ones with 31 days in it
                    if (inputMonth == 1 || inputMonth == 3 || inputMonth == 5 || inputMonth == 7
                        || inputMonth == 8 || inputMonth == 10 || inputMonth == 12)
                    {
                        if(inputDay < 32)
                            return 1;
                        else
                            return 0;
                    }
                    else
                    {
                        if(inputDay < 31)
                            return 1;
                        else
                            return 0;
                    }
                }
                else //if it is greater than 31 days
                    return 0;
            }
        }
        else //if the month is not valid
            return 0;
    } //if the year is not valid
    else
        return 0;
}
 static void populateEmployees(PERSON employee[])
{
    for (int i = 0; i < 3; i++)
    {
        //name input
        printf("Please enter details for a person below.\n");
        printf("Name: ");
        scanf(" %s", employee[i].name);
        //birthday input and validation
        do{
            printf("\nPlease enter a birth date:");
            printf("\nPlease enter a day in dd format: ");
            scanf("%d", &employee[i].birthday.day);
            printf("\nPlease enter a month in mm format: ");
            scanf("%d", &employee[i].birthday.month);
            printf("\nPlease enter a year in yy format: ");
            scanf("%d", &employee[i].birthday.year);
            fflush(stdin);
            if(isDateValid(employee[i].birthday.day,employee[i].birthday.month,employee[i].birthday.year) == 0)
                printf("\nPlease enter a valid date of birth.");
        }while(isDateValid(employee[i].birthday.day, employee[i].birthday.month, employee[i].birthday.year) == 0);
        //gender input and validation m,f,o upper and lower case accepted
        do{
            printf("\nPlease enter a gender (M, F, or O): ");
            scanf(" %c", &employee[i].gender); //extra space is to take in account of the input buffer
            if(isGenderValid(employee[i].gender)== 0)
            {
                printf("\nPlease enter a valid input.");
            }
        }while(isGenderValid(employee[i].gender) == 0);
        //income input and validation 0 - 1 mil
        do{
            printf("\nPlease enter your annual income between 0 and 1 million: ");
            scanf("%f", &employee[i].annualIncome);
            if(isIncomeValid(employee[i].annualIncome) == 0)
                printf("\nPlease enter a valid input.\n");
        }while(isIncomeValid(employee[i].annualIncome) == 0);
    }
}
 static void displayEmployee(PERSON employee[])
{
    printf("\nThe people entered and their details are:\n");
    for(int i = 0; i < 3; i++)
    {
        printf("\nPerson %d", i+1);
        printf("\nName: %s", employee[i].name);
        printf("\nDate of Birth: %d/%d/%d", employee[i].birthday.day, employee[i].birthday.month, employee[i].birthday.year);
        printf("\nGender: %c", toupper(employee[i].gender));
        printf("\nAnnual Income: %.2f\n", employee[i].annualIncome);
    }
}
void Assignment03()
{
    PERSON employee[3];
    populateEmployees(employee);
    displayEmployee(employee);
}

//Assignment 4
void Assignment04()
{
    //arrays of letters
char unCoded[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char coded[] = {'H','I','V','J','K','W','L','A','M','Y','N','B','X','O','Z','C','T','P','U','D','Q','S','R','E','G','F'};
int index,i,j;

//grab user input
char userInput[30];
char encoded[30];
printf("Enter your input: ");
scanf("%s", userInput);
i =0;
//create encoding
while(userInput[i]!= '\0')
{
    for(j = 0; j < 26; j++)//loop through all the letters
    {
        if(unCoded[j] == toupper(userInput[i]))//if found index is equal to j to correspind with the coded array
        {
            index = j;
            break;
        }
    }
    //encoding the output with codded array
    encoded[i] = coded[index];
    i++;
}

encoded[i] = '\0';
printf("Word inputted: %s", userInput);
printf("Encoded word: %s",encoded);
}

//Assignment 5
 typedef struct
{
    int year; //starting year is 1990
    int miles; //assigned at random under a limit of 30000
    char emission; //arbitrary grade does not reflect actual emission testing
}CAR;
void Assignment05()
{
    srand(time(NULL));
const int MAXSIZE = 1000;
//array on the stack
CAR cars_stack[MAXSIZE];
int num = 10;
for(int i = 0; i < num; i++)
{
    cars_stack[i].year = 1990 + i;
    cars_stack[i].miles = rand()%30000;
    if(cars_stack[i].miles >= 25000)
        cars_stack[i].emission = 'A';
    else if(cars_stack[i].miles >= 20000)
        cars_stack[i].emission = 'B';
    else if(cars_stack[i].miles >= 15000)
        cars_stack[i].emission = 'C';
    else if(cars_stack[i].miles >= 10000)
        cars_stack[i].emission = 'D';
    else if(cars_stack[i].miles >= 5000)
        cars_stack[i].emission = 'E';
    else
        cars_stack[i].emission = 'D';
}
//array on the heap
CAR *cars_heap = (CAR*)malloc(num*sizeof(CAR));
if(cars_heap == NULL)
{
    printf("\nMemory not allocated.");
    return 0;
}
//copying the tack values to the heap values
for(int i = 0; i < num; i++)
{
    cars_heap[i].year = cars_stack[i].year;
    cars_heap[i].miles = cars_stack[i].miles;
    cars_heap[i].emission = cars_stack[i].emission;
}
//print both the stack and heap elements
for(int i = 0; i < num; i++)
{
    printf("\nStack : ");
    printf("\nID: %d\tScore: %d\tGrade: %c", cars_stack[i].year, cars_stack[i].miles, cars_stack[i].emission);
    printf("\nHeap : ");
    printf("\nID: %d\tScore: %d\tGrade: %c", cars_heap[i].year, cars_heap[i].miles, cars_heap[i].emission);
}
//writing contents to binary file
FILE *fileptr = fopen("cars.bin","w");
if(fileptr == NULL)
{
    printf("File could not be opened.");
    return 0;
}
for(int i = 0; i < num; i++)
{
    if(i != num-1)
    {
        fprintf(fileptr,"%d %d %c\n",cars_heap[i].year,cars_heap[i].miles,cars_heap[i].emission);
    }
    else
    {
        fprintf(fileptr,"%d %d %c",cars_heap[i].year,cars_heap[i].miles,cars_heap[i].emission);
    }
}
fclose(fileptr);

}

//Assignment 6
void Assignment06()
{
    char keywords [200][20]; //create a space for the key words
    int count = 0;
    FILE * keys = fopen("Keys.txt", "r"); //open the keys file for the key words
    if (keys == NULL) //validation if the file can be opened or not
    {
        printf("Error! Could not open file\n");
        exit(-1);
    }
    while(fscanf(keys, "%s", keywords[count]) != EOF) //scan the file until you reach the end
    {
        count++;
    }
    fclose(keys); //close the file

    char resume[200][20];//create a space for the resume
    int index = 0;
    FILE * resumeFile = fopen("Resume.txt", "r"); //open the file
    if (resumeFile == NULL) //file validation
    {
        printf("Error! Could not open file\n");
        exit(-1);
    }
    while(fscanf(resumeFile, "%s", resume[index]) != EOF)//do this until end of file
    {
        index++;
    }
    fclose(resumeFile); //close the file

    int total = 0;
    for(int i = 0; i < index; i++)//each word in resume
    {
        for(int j = 0; j < count; j++)//each word is key words
        {
            if(strcmp(keywords[j],resume[i]) == 0)//if the words match
                total++; //add to total amount
        }
    }
    printf("Keywords found: %d", total);
}

//Assignment 7
 void forwardDisplay(char uString[])
{
    for(int i=0; i < strlen(uString); i++) //displays string
    {
        printf("%c", uString[i]);
    }
}
 void backwardDisplay(char uString[])
{
    for(int i=(strlen(uString)-1); i >= 0; i--) //displays reverse string
    {
        printf("%c", uString[i]);
    }
}
 void verticalDisplay(char uString[])
{
    for(int i=0; i < strlen(uString); i++)//displays string with new lines between characters
    {
        printf("%c\n", uString[i]);
    }
}
 void triangleDisplay(char uString[])
{
    for(int i = 0; i < strlen(uString); i++)//row of that the iter is currently on
    {
        for(int j = 0; j <= i; j++)// column that the iter is currently on
        {
            printf("%c", uString[j]);
        }
        printf("\n");
    }
}
void Assignment07()
{
    char userString[100];
    int userChoice;
    //int count;
    do
    {
        //user inputs up to 100 chars in a string
        printf("Please input a word or string of letters. ");
        //user inputs up to 100 chars in a string
        scanf("%s", userString);
        //displays string forward, backward, vertical, triangle
        printf("\nForward: ");
        forwardDisplay(userString);
        printf("\nBackward: ");
        backwardDisplay(userString);
        printf("\nVertical:\n");
        verticalDisplay(userString);
        printf("\Triangle:\n");
        triangleDisplay(userString);
        //display number of letters in the string
        printf("\nString length: %d", strlen(userString));
        //prompt user if they want to do it again
        printf("\nPress 1 to enter another string.\nPress 0 to quit. ");
        scanf("%d", &userChoice);
    }while (userChoice != 0);
}

//Assignment 8
 void bubbleSort(int myArray[], size_t mySize)
{
    int tempArray;
    for(int i = 0; i < mySize - 1; i++)
    {
       for(int j = 0; j < mySize - i - 1; j++)
       {
           if(myArray[j] < myArray[j +1])
           {
               tempArray = myArray[j];
               myArray[j] = myArray[j+1];
               myArray[j+1] = tempArray;
           }
       }

    }
}
void Assignment08()
{
    size_t arraySize = 10;
    int inputArray[10] = {NULL};
    int inputChoice;
    int deposite;
    int totalBalance = 0;
    int avgBalance = 0;
    do{
        printf("\n***********Main Menu***********\n");
        printf("Press 1 to input a new deposit. A max of 10 deposits are allowed.\n");
        printf("Press 2 to show the sum of all deposits.\n");
        printf("Press 3 to show deposits highest to lowest.\n");
        printf("Press 4 to show the average of all deposits.\n");
        printf("Press 5 to show the lowest deposit amount.\n");
        printf("Press 0 to quit.\n");

        scanf("%d", &inputChoice);

        switch(inputChoice)
        {
        case 1:
            printf("Enter 10 amounts to deposit: \n");
            for(int j = 0; j < arraySize; j++)
            {
                scanf("%d", &deposite);
                if(inputArray[j] == NULL)
                {
                inputArray[j] = deposite;
                //break;
                }
                if(j == 9 && inputArray[j] != NULL)
                {
                    printf("Thank you for depositing. \n");
                    break;
                }
            }
            break;
        case 2:
           for(int i = 0; i < arraySize; i++)
            {
                totalBalance += inputArray[i];
            }
            printf("Your total balance is: %d", totalBalance);
            break;
        case 3:
            bubbleSort(inputArray, arraySize);
            printf("Your deposits from highest to lowest are: \n");
            for(int k = 0; k < arraySize; k++)
            {
                printf("%d\n", inputArray[k]);
            }
            break;
        case 4:
              for(int i = 0; i < arraySize; i++)
            {
                avgBalance += inputArray[i];
            }
            avgBalance = avgBalance/arraySize;
            printf("Your average balance is: %d", avgBalance);
            break;
        case 5:
            bubbleSort(inputArray, arraySize);
            printf("Your lowest deposit was: %d", inputArray[arraySize-1]);
            break;
        }
    } while (inputChoice != 0);
}

//Assignment 9
 typedef struct node
{
    char name[100];
    int age;
    float weight;
    struct node *next;
}node;
 void menu()
{
        printf("\n MENU \n");
        printf("\n 1.Insert into Linked list \n");
        printf("\n 2.Display Linked list \n");
        printf("\n 3.Exit \n");
        printf("Enter your choice:\t");
}
 int IValidate(int min, int max)
{//validates all numerical inputs
    int num;
    do {
        printf("\nPlease enter a number between %d and %d: ", min, max);
        scanf("%d", &num);
        if (num < min || num > max) {
            printf("\nInvalid input. Please try again.");
        }
    } while (num < min || num > max);
    return num;
}
 void displayList(node *start)
{

    if(start==NULL)// if list is empty
    {
        printf("\nList is empty:\n");
    }
    else
    {
        printf("\nThe List elements are:\n");
        while(start!=NULL)// travel linked list
        {
            //print all data on console
            printf("Name: %s\t",start->name );
            printf("Age: %d\t",start->age );
            printf("Weight: %.2f\t",start->weight );
            printf("\n");
            start=start->next ;//go to next node
        }
    }
}
  node* insertRecord(node *start)
{
    struct node *temp,*ptr;
    // allocate memory using malloc
    temp=(struct node *)malloc(sizeof(struct node));
    if(temp==NULL)// if list is empty
    {
        printf("\nOut of heap Space:\n");
    }
    // add record to node
    printf("\nEnter the Name of the student:\t");
    scanf("%s",temp->name);
    printf("\nEnter the age of the student:\t");
    temp->age = IValidate(1,18);
    printf("\nEnter the weight of the student:\t");
    temp->weight = Validate(65.00,300.00);
    temp->next =NULL;
    ptr = start;
    if(start==NULL) // if it is 1st node
    {
        ptr = temp;
    }
    else // add to next node
    {
        while(ptr->next !=NULL)
        {
            ptr = ptr->next ;
        }
        ptr->next = temp;
    }
    return ptr;
}
void Assignment09()
{
    struct node *start=NULL;
    int choice;
    do
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        {
        case 1: // add record to linked list
            start = insertRecord(start);
            ClearConsole();
            break;
        case 2: //display all record from list
            displayList(start);
            ClearConsole();
            break;
        case 3: // exit condition
            exit(0);
            break;
        default:
            printf("\n Invalid Option:\n");
            ClearConsole();
            break;
        }//end of switch()
    }while(choice != 3);
}

//Assignment 10
 void inputScores(int results[][2], int records)
{
    printf("Please enter your score : \n");
    scanf("%d",&results[records][0]);
    printf("Enter opponent score : \n");
    scanf("%d",&results[records][1]);
}
 void printScores(int results[][2], int records)
{
    int win =0;
    int loss =0;
    int tie =0;
     for(int i=0;i<records;i++)
    {
        //if you > opponent
        if(results[i][0] > results[i][1])
            win++;
        //if you < opponent
        else if (results[i][0] < results[i][1])
            loss++;
        //if tie
        else
            tie++;
    }
    //print results
    printf("\nWins = %d  Loss = %d  Ties = %d\n",win,loss,tie);

}
 void wonScores(int results[][2], int records)
{
    for(int i=0;i<records;i++)
        {
            //if your > opponent
            if(results[i][0] > results[i][1])
            {
                printf("\nYour score : %d, Opponent's score : %d\n",results[i][0],results[i][1]);
            }
        }
}
 void BubbleSort(int results[][2], int records)
{
    int tempArray;
    int k =1;
    for(int i = 0; i < records; i++)
    {
       for(int j = i+1; j < records; j++)
       {
           if(results[i][k] > results[j][k])
           {
               tempArray = results[i][0];
               results[i][0] = results[j][0];
               results[j][0] = tempArray;
               tempArray = results[i][1];
               results[i][1] = results[j][1];
               results[j][1] = tempArray;
           }
       }

    }
}
 void opponentScores(int results[][2], int records)
{
    BubbleSort(results,records);
    for (int i = 0; i < records; i++)
    {
        printf("\nYour score: %d   Opponent's score: %d\n", results[i][0], results[i][1]);
    }
}
void Assignment10()
{
    int gameScores[30][2];
    int inputChoice;
    int record =0;
    do{
        printf("Press 1 to enter game scores.\n");
        printf("Press 2 to display game scores.\n");
        printf("Press 3 to display WON game scores.\n");
        printf("Press 4 to display game scores ordered by Opponent's scores.\n");
        printf("Press 0 to exit.\n");
        scanf("%d", &inputChoice);
        switch(inputChoice)
        {
        case 1:
            inputScores(gameScores,record);
            record++;
            break;
        case 2:
            printScores(gameScores,record);
            break;
        case 3:
            printf("Results of the games won: \n");
            wonScores(gameScores,record);
            break;
        case 4:
            printf("Results of games from ordered by Opponent's scores Low to High: \n");
            opponentScores(gameScores,record);
            break;
        }
    }while(inputChoice != 0);
}

//Assignment 11
void Assignment11()
{
    //declare array for amounts
    int amounts[] = { 2, 5, 10, 15, 50, 20, 10, 5, 3 };
    //declare the odd win percentages
    int odds[] = { 40, 10, 8, 6, 1, 4, 8, 10, 13 };
    //call the method with two arrays
    start_game(amounts, odds);
    track_dogs();
}

//Assignment 12
 void ShuffleCards(int deck[CARDS])
{
    for(int i = 0; i < CARDS; i++)
    {
        int rnd = rand() % CARDS;
        int temp = deck[i];
        deck[i] = deck[rnd];
        deck[rnd] = temp;
    }
}
 int DealCards(int deck[CARDS], int playerHand[PLAYERS][HAND],int dealt[CARDS], int numDealt, bool check[CARDS])
{
    for(int i = 0; i < HAND; i++)
    {
        for(int j = 0; j < PLAYERS; j++)
        {
            //deal card that has not been dealt
            int index = rand() % (CARDS - numDealt);
            int card = -1;
            for(int k = 0; k < CARDS; k++) //for every card
            {
                //check to see if it has been dealt before
                if(deck[k] != -1 && check[k] != true) //if the space is not negative 1 which means it is empty
                {
                        if(index == 0) //when the index reaches the random space that is not "empty"
                        {
                            card = deck[k]; //card is equal to the value of deck[k]
                            dealt[k] = card; //dealt takes the value of the card
                            deck[k] = -1; //empty the card from deck
                            check[k] = true;
                            numDealt++; //add to the number dealt
                            break;
                        }
                        else
                            index--;
                }
            }
            playerHand[j][i] = card; //place the card into the player hand
        }
    }
    return numDealt;
}
 void PrintHand(int playerHand[PLAYERS][HAND])
{
    for (int i = 0; i < PLAYERS; i++) //for all players
    {
        printf("Player %d's hand: ", i+1);
        for(int j = 0; j < HAND; j++) //for all cards in hand
        {
            printf("\t%d ", playerHand[i][j]);
        }
        printf("\n");
    }
}
 void PrintDeck(int deck[CARDS])
{
    printf("\nCards in Deck:");
    for(int i = 0; i < CARDS; i++)
    {
        if(deck[i] != -1)//if the card is not empty
        {
            printf("\n%d", deck[i]);//all the cards currently in the deck
        }
    }
}
 void PrintDealt(int dealt[CARDS])
{
    printf("\nCards Dealt:");
    for(int i = 0; i < CARDS; i++)
    {
         if(dealt[i] != -1)//if the card is not empty
        {
            printf("\n%d", dealt[i]);//all the cards that the players were dealt
        }
    }
}
void Assignment12()
{
    srand(time(NULL)); //allows for random number generation
    int choice = 0;
    //creating deck of cards array
    int deck[CARDS];
    //creating player hand
    int playerHand [PLAYERS][HAND];
    //creating array to hold already dealt cards
    int dealt[CARDS];
    int numDealt = 0;

    bool check[CARDS];
    //populating deck
    for(int i = 0; i < CARDS; i++)
    {
        deck[i] = i + 1;
        dealt[i] = -1;
        check[i] = false;
    }
    do
    {
        printf("\t\t\t\tMain Menu\t\t\t\t\n");
        printf("1. Print Deck\n");
        printf("2. Shuffle Deck\n");
        printf("3. Deal Cards\n");
        printf("4. Show Dealt Cards\n");
        printf("5. Restart game\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            PrintDeck(deck);
            ClearConsole();
            break;
        case 2:
            ShuffleCards(deck);
            ClearConsole();
            break;
        case 3:
            if(numDealt <= 34)
            {
                numDealt = DealCards(deck, playerHand,dealt, numDealt,check);
                PrintHand(playerHand);
            }
            else
                printf("There is not enough cards in the deck to continue.");
            ClearConsole();
            break;
        case 4:
             PrintDealt( dealt);
             ClearConsole();
            break;
        case 5:
            for(int i = 0; i < CARDS; i++)
            {
                deck[i] = i + 1;
                dealt[i] = -1;
                check[i] = false;
            }
            break;
        case 6:
            printf("Thank you for playing.");
            break;
        default:
            printf("Invalid Input please enter an option.\n");
            break;
        }
    }while(choice != 6);
}




#endif // ASSIGNMENTCOMILATION_H_INCLUDED
