#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Team{
    char name[100];
    char code[40];
    int NoOfWins;
    int NoOfDraws;
    int NoOfLoses;
    int GoalDifference;
    int points;

};

struct TeamList{
    struct Team team;
    struct TeamList* Next;
    struct PlayerList* playerL;
    struct QueueRecord* playersQueue;

};
struct TeamList* l1;

struct Player{
    char name[100];
    char TeamCode[40];

};
struct PlayerList{
    struct Player player;
    struct PlayerList* Next;
};

typedef struct QueueRecord *Queue;
#define MinQueueSize 5
struct QueueRecord{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    struct Player *Array;

};



struct TeamList* Nodes[10];



struct TeamList* MakeEmpty(struct TeamList* L);
void DeleteList(struct TeamList* L);
struct TeamList* Find(struct Team x , struct TeamList* L);
struct TeamList* FindPrevious(struct Team team , struct TeamList* L);
void addLast(struct TeamList* L , struct Team team);
void Insert(struct Team team, struct TeamList* P , struct TeamList* L);
int IsEmpty(struct TeamList* L);
int IsLast(struct TeamList* P , struct TeamList* L);
int FindPointOfTeam(struct Team team);
void printTeamList(struct TeamList* L);
struct TeamList* RadixSort(struct TeamList *array );
void readNodes(struct TeamList *array ,struct TeamList* Nodes[]);
int findMaxNumber(struct TeamList* L);
int findMaxDigitInList(struct TeamList* array);
int sizeOfLinkedList(struct TeamList* L);
void DeleteTeam( struct Team team , struct TeamList* L);
struct Team FindTeamByCode(char teamCode[40] , struct TeamList* L );
void CreateMatch(char firstTeamCode[40] , char secondTeamCode[40]);
void ChangeElementarySparePlayers(struct TeamList* L ,struct PlayerList* player );
void GivePlayerRedCard(struct TeamList* L , struct PlayerList* player);
void DisposeTeamList(struct TeamList* L);

void DeletePlayerList(struct PlayerList* L);
struct PlayerList* MakeEmptyPlayerList(struct PlayerList* L);
void addLastPlayerList(struct PlayerList* L , struct Player player);
void printPLayerList(struct PlayerList* L);
struct PlayerList* FindPreviousPlayer(struct Player  x , struct PlayerList* L);
void DeletePlayer(struct Player x , struct PlayerList* L);
struct TeamList *insertionsort(struct TeamList* L);

Queue CreatQueue(int MaxElements);
void MakeEmptyQueue(Queue q);
void DisposeQueue(Queue q);
int isEmptyQueue(Queue q);
int isFull(Queue q);
int Succ(int  x , Queue q);
void Enqueue(struct Player x , Queue q);
void Dequeue(Queue q);
struct  Player Front(Queue q);
struct Player FrontAndDequeue(Queue q);
void printQueue(Queue q);
int main()
{


    // read file teams.txt:
    FILE *teamsFile = fopen("teams.txt" , "r");
    char all[6000];

     l1 = MakeEmpty(l1);

    // read teams Informations from file(teams.txt):

    while(fgets(all , 6000 , teamsFile) != NULL){
         struct Team team;
        strcpy(team.name , strtok(all , ","));
        strcpy(team.code , strtok('\0', ","));
        team.NoOfWins = atoi(strtok('\0', ","));
        team.NoOfDraws = atoi(strtok('\0', ","));
        team.NoOfLoses = atoi(strtok('\0', ","));
        team.GoalDifference = atoi(strtok('\0', ","));
        team.points = FindPointOfTeam(team);




        // add the certain team to the last of linked list using funtion(addLast())
        addLast(l1, team);



    }

    //sort the team list using radix sort depend on points and goal difference:


    // get input from the user:

    int input;


    while(1){
            l1 = insertionsort(l1);
            l1 = RadixSort(l1);


        //print options for user:
        printf("1:add a team\n2:delete a team\n3:modify in a team\n4:Create Game\n5:print teams Information\n6:Save teams information in  file (teamInfo.txt)\n7:Exit\n");
        scanf("%d" , &input);

        //option to add new team:
        if(input == 1){
            // get teams informations from the user keyboard:

            char teamName[100];
            char teamCode[40];
            int teamNoOfWins;
            int teamNoOfDraws;
            int teamNoOfLoses;
            int teamPoints;
            int teamGoalDifference;
            printf("Enter Team name:\n");
            scanf("%s" , &teamName);
            printf("Enter team code:\n");
            scanf("%s" , &teamCode);
            printf("Enter team number of wins:\n");
            scanf("%d" , &teamNoOfWins);
            printf("Enter team number of draws:\n");
            scanf("%d" , &teamNoOfDraws);
            printf("Enter team number of loses:\n");
            scanf("%d" , &teamNoOfLoses);
            printf("Enter team goal difference:\n");
            scanf("%d" , &teamGoalDifference);
            struct Team team;
            strcpy(team.name , teamName);
            strcpy(team.code , teamCode);
            team.NoOfWins = teamNoOfWins;
            team.NoOfDraws = teamNoOfDraws;
            team.NoOfLoses = teamNoOfLoses;
            team.GoalDifference = teamGoalDifference;
            team.points = teamPoints = FindPointOfTeam(team);
            addLast(l1 ,team );

        }
        // option to delete team from the list by getting team code from the user:

        else if(input == 2){
            char teamCode[40];
            printf("Enter team code\n");
            scanf("%s" , &teamCode);
            struct Team team;
            //find team by code(input from user):
            team = FindTeamByCode(teamCode , l1);

            // check if team exist in the list
            if(strcmp(team.code , "") == 0){
                printf("This team is not in the list\n");
                printf("try again:\n");
            }
            else{
                // call delete team,to delete the selected team from the team list:

                DeleteTeam(team , l1);
            }




        }
        // modify team by get code from the user:

        else if(input == 3){
            int modificationInput;
            char teamCode[40];
            printf("Enter code of the team you want to modify\n");
            scanf("%s" ,&teamCode);
            struct Team team = FindTeamByCode(teamCode , l1);

            // check if team exist in the list:
            if(strcmp(team.code , "") ==0 ){
                printf("this team is not exist in the list\n");
                printf("try again:\n");

            }
            else{
                // print the modification inputs:

                printf("1:Modify number of wins\n2:Modify number of draws\n3:Modify number of loses\n4:Modify goal difference\n ");
                scanf("%d" , &modificationInput);

                if(modificationInput == 1){
                    // modify number of wins:

                    int NoOfWins = 0;
                    printf("Enter number of wins of team %s\n" , team.name);
                    scanf("%d" , &NoOfWins);
                    struct TeamList* P = l1->Next;
                    //find the team in team list:

                    while(P!= NULL){
                        if(strcmp(P->team.code , team.code) ==0){
                            P->team.NoOfWins = NoOfWins;
                            P->team.points = FindPointOfTeam(P->team);
                        }
                        P = P->Next;
                    }

                }
               else if(modificationInput == 2){
                    // modify number of draws:
                    int NoOfDraws = 0;
                    printf("Enter number of draws of team %s\n" , team.name);
                    scanf("%d" , &NoOfDraws);
                    struct TeamList* P = l1->Next;
                    //find team using team code:

                    while(P!= NULL){
                        if(strcmp(P->team.code , team.code) ==0){
                            P->team.NoOfDraws= NoOfDraws;
                            P->team.points = FindPointOfTeam(P->team);
                        }
                         P = P->Next;
                    }


                }
                else if(modificationInput == 3){
                    // modify number of loses:
                    int NoOfLoses = 0;
                    printf("Enter number of loses of team %s\n" , team.name);
                    scanf("%d" , &NoOfLoses);
                    struct TeamList* P = l1->Next;
                    // find team by team code:

                    while(P!= NULL){
                        if(strcmp(P->team.code , team.code) ==0){
                            P->team.NoOfLoses = NoOfLoses;

                        }
                        P = P->Next;
                    }


                }
                else if(modificationInput == 4){
                    // modify goal difference
                    int goalDifference = 0;
                    printf("Enter goal difference of the team %s\n" , team.name);
                    scanf("%d" , &goalDifference);
                    struct TeamList* P = l1->Next;
                    //find team using team code:

                    while(P!= NULL){
                        if(strcmp(P->team.code , team.code) ==0){
                            P->team.GoalDifference = goalDifference;
                        }
                         P = P->Next;
                    }


                }
                else{
                    // print error message if the modification input not in list:

                    printf("Wrong entry:\n");
                    printf("try again\n");
                }

            }



        }
        else if(input == 4){
            //create team:

            //take code of first and second team codes:

            char firstTeamCode[40];
            char secondTeamCode[40];
            printf("Enter code of the first team\n");
            scanf("%s" , &firstTeamCode);
            printf("Enter code of the second team\n");
            scanf("%s" , &secondTeamCode);
            // call function CreateGame():
            CreateMatch(firstTeamCode , secondTeamCode);
        }
        else if(input == 5){
            // call function printTeamList() to print teams informations on screen:

            printTeamList(l1);
        }
        else if(input == 6){
            // save teams informations in file(teamsInfo.txt):

            //create the output file:
            FILE *outputFile;
            outputFile = fopen("teamsInfo.txt" , "w");

            struct TeamList* list;
            list = l1->Next;
            // print team informations in the file:

            fprintf( outputFile, "teamName,teamCode,NoOfWins,NoOfDraws,NoOfLoses,GoalDifference,Points\n");
            //iterate the list to print the informations:

            while(list != NULL){

                fprintf(outputFile , "%s,%s,%d,%d,%d,%d,%d\n" , list->team.name, list->team.code, list->team.NoOfWins, list->team.NoOfDraws,list->team.NoOfLoses,list->team.GoalDifference,list->team.points);
                list = list->Next;
            }
            fclose(outputFile);

        }

        else if (input == 7){
            // exit the options:

            break;

        }
        else{
            // print error message  if user enter wrong input from list:

            printf("Wrong entry: try again\n\n");
        }
    }


    // close file teams.txt:

    fclose(teamsFile);

    return 0;
}

// function MakeEmpty() to create the team linked list:

struct TeamList* MakeEmpty(struct TeamList* L){
    if(L != NULL){
        // call function DeleteList() to delete list if exist:
        DeleteList(L);
    }
    // create the head of linked list:
    L= (struct TeamList*) malloc(sizeof(struct TeamList));
    L ->Next = NULL;

    if(L == NULL){
        printf("wrong in memory storage\n");
    }

    return L;
}
//function DeleteList to delete all items in the list.But keep the head of the list:

void DeleteList(struct TeamList* L){

    struct TeamList* P;
    struct TeamList* temp;
    P= L->Next;

    L->Next =NULL;

    // iterate the items of team linked list to delete them:

    while(P != NULL){
        temp = P->Next;
        free(P);
        P = temp;

    }
}
//function DeletePlayerList to delete player list:

void DeletePlayerList(struct PlayerList* L){

    struct PlayerList* P;
    struct PlayerList* temp;
    P= L->Next;

    L->Next =NULL;

    // iterate the list of players to delete it:
    while(P != NULL){
        temp = P->Next;
        free(P);
        P = temp;

    }
}
// function Find() to find team in team linked list using teamcode:
struct TeamList* Find(struct Team x , struct TeamList* L){
    struct TeamList* P;
    P = L->Next;
    // iterate the linked list and find team using team code
    while(P != NULL && strcpy(P->team.code ,  x.code)!=0){
        P = P->Next;
    }
    //return pointer to team if is found:

    return P;
}

// function FindPrevoius() to find team in team linked list and return pointer to the prevoius node of it:

struct TeamList* FindPrevious(struct Team team , struct TeamList* L){
    struct TeamList* P;
    P = L;

    while(P->Next != NULL && strcmp(P ->Next->team.code , team.code) != 0){
        P = P->Next;
    }
    if(P!= NULL){
        return P;
    }
    else{
        return NULL;
    }

}


//function addLast: add the team to  end of the list:

void addLast(struct TeamList* L , struct Team team){
    // create the node of team list:

    struct TeamList* P = (struct TeamList*)malloc(sizeof(struct TeamList));
    struct TeamList *temp;
    strcpy(P->team.name , team.name);
    strcpy(P->team.code , team.code);
    P->team.NoOfWins = team.NoOfWins;
    P->team.NoOfDraws = team.NoOfDraws;
    P->team.NoOfLoses = team.NoOfLoses;
    P->team.GoalDifference = team.GoalDifference;
    P->team.points = team.points;

    if(IsEmpty(L)){
        P->Next = NULL;
        L->Next= P;
    }
    else{
        temp = L;
        // iterate loop to reach the end of the list:

        while(temp->Next != NULL){
            temp = temp->Next;
        }
        temp->Next = P;
        P->Next = NULL;
    }

}

// function Insert(): insert the team after node(P) given
void Insert(struct Team team, struct TeamList* P , struct TeamList* L){
    struct TeamList* temp;
    //create the node
    temp = (struct TeamList*) malloc(sizeof(struct TeamList));
    temp->team = team;
    temp->Next =  P->Next;
    P->Next = temp;

}
//function isEmpty():check if team list is empty (head points to null):

int IsEmpty(struct TeamList* L){
    return L ->Next == NULL;
}
//function isLast():check if given node if the last in team list:

int IsLast(struct TeamList* P , struct TeamList* L){
    return P ->Next == NULL;
}
//function to find Points of specific team by 1- number of wins 2- number of draws:

int FindPointOfTeam(struct Team team){
    return (3 * team.NoOfWins) + (1 * team.NoOfDraws);
}

// function printTeamList(): print the informations of team list:

void printTeamList(struct TeamList* L){
    struct TeamList* P;
    P = L->Next;

    if(IsEmpty(L)){
        printf("The list is empty\n");

    }
    else{
        // iterate the team linked list to print informations:
        printf("name//code//NoOfWins//NoOfDraws//NoOfLoses//GoalDifference//Points \n");
       while(P!=NULL){
            printf("%s// %s // %d// %d // %d // %d // %d \n" ,P->team.name, P->team.code , P->team.NoOfWins , P->team.NoOfDraws, P->team.NoOfLoses , P->team.GoalDifference , P->team.points );
            P=P->Next;
        }
    }

    printf("\n");
}

//function RadixSort(): sort team linked list by points.However , if teams have same points will sort them based on goal difference:
// The function sort teams using array of linked lists called Nodes[] , and size of 10.
// Time of radix sort is O(kN) , where k: is number of digits of maximum number ,  N:number of elements in linked list.
struct TeamList* RadixSort(struct TeamList *array ){
    // create all nodes of the array of linked list called Nodes[] by call function MakeEmpty():

    for(int i=0;i<10 ; i++){
        Nodes[i] = MakeEmpty(Nodes[i]);

    }
    // find maximum number of digits of points of team linked list:

    int max = findMaxDigitInList(array );

    // initialize the mode variable to check the number of iteration:
    int mode =1;

    struct TeamList* P ;
    // first loop to iterate based on number of digits of maximum number in list:

    for(int i=0;i<max ; i++){

        // empty the Nodes to fill them again:

        for(int i=0;i<10 ; i++){
            Nodes[i] = MakeEmpty(Nodes[i]);
        }
        // second loop iterate the
        P = array->Next;
        while(P!= NULL){
            // check if points reminder
            if(((P->team.points/mode)%10) == 0){
              /* int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference

                if(IsEmpty(Nodes[0])){
                    addLast(Nodes[0] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[0]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[0])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[0]);
                                isInserted = 1;
                                break;
                            }
                            else{

                                //struct TeamList* temp2 = FindPrevious(P->team,Nodes[0]);
                                Insert(P->team , Nodes[0] , Nodes[0]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[0]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                                //struct TeamList* temp3 = FindPrevious(P->team , Nodes[0]);
                                Insert(P->team , Nodes[0], Nodes[0]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[0] , P->team);
                }
                printf("Nodes[0]\n");
                printTeamList(Nodes[0]);*/
                addLast(Nodes[0] , P->team);

            }
             // check if points reminder
            else if(((P->team.points/mode)%10)  == 1){
                /*
               int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference
                if(IsEmpty(Nodes[1])){
                    addLast(Nodes[1] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[1]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[1])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[1]);
                                isInserted = 1;
                                break;
                            }
                            else{

                                //struct TeamList* temp2 = FindPrevious(P->team,Nodes[1]);
                                Insert(P->team , Nodes[1] , Nodes[1]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[1]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                                //struct TeamList* temp3 = FindPrevious(P->team , Nodes[1]);
                                Insert(P->team , Nodes[1] , Nodes[1]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[1] , P->team);
                }
                */
                 addLast(Nodes[1] , P->team);
            }
            // check if points reminder
            else if(((P->team.points/mode)%10) == 2){
                /*
                int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference
                if(IsEmpty(Nodes[2])){
                    addLast(Nodes[2] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[2]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[2])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[2]);
                                isInserted = 1;
                                break;
                            }
                            else{

                               // struct TeamList* temp2 = FindPrevious(P->team,Nodes[2]);
                                Insert(P->team , Nodes[2] , Nodes[2]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[2]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                               // struct TeamList* temp3 = FindPrevious(P->team , Nodes[2]);
                                Insert(P->team , Nodes[2] , Nodes[2]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[2] , P->team);
                }
                */
                 addLast(Nodes[2] , P->team);
            }
            // check if points reminder
            else if(((P->team.points/mode)%10) == 3){
                /*
                int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference
                if(IsEmpty(Nodes[3])){
                    addLast(Nodes[3] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[3]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[3])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[3]);
                                isInserted = 1;
                                break;
                            }
                            else{

                                //struct TeamList* temp2 = FindPrevious(P->team,Nodes[3]);
                                Insert(P->team , Nodes[3] , Nodes[3]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[3]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                                //struct TeamList* temp3 = FindPrevious(P->team , Nodes[3]);
                                Insert(P->team , Nodes[3] , Nodes[3]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[3] , P->team);
                }
                */
                 addLast(Nodes[3] , P->team);
            }
            // check if points reminder
            else if(((P->team.points/mode)%10) == 4){
                /*
                int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference
                if(IsEmpty(Nodes[4])){
                    addLast(Nodes[4] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[4]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[4])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[4]);
                                isInserted = 1;
                                break;
                            }
                            else{
                               // struct TeamList* temp2 = FindPrevious(P->team,Nodes[4]);
                                Insert(P->team , Nodes[4] , Nodes[4]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[4]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                                //struct TeamList* temp3 = FindPrevious(P->team , Nodes[4]);
                                Insert(P->team , Nodes[4] , Nodes[4]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[4] , P->team);
                }

            }
            */
            addLast(Nodes[4] , P->team);
            }
             // check if points reminder
            else if(((P->team.points/mode)%10) == 5){
               /* int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference
                if(IsEmpty(Nodes[5])){
                    addLast(Nodes[5] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[5]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[5])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[5]);
                                isInserted = 1;
                                break;
                            }
                            else{

                               // struct TeamList* temp2 = FindPrevious(P->team,Nodes[5]);
                                Insert(P->team , Nodes[5] , Nodes[5]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[5]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                                //struct TeamList* temp3 = FindPrevious(P->team , Nodes[5]);
                                Insert(P->team , Nodes[5], Nodes[5]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[5] , P->team);
                }*/

                 addLast(Nodes[5] , P->team);
            }
             // check if points reminder
            else if(((P->team.points/mode)%10) == 6){
                /*
                int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference
                if(IsEmpty(Nodes[6])){
                    addLast(Nodes[6] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[6]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[6])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[6]);
                                isInserted = 1;
                                break;
                            }
                            else{

                                //struct TeamList* temp2 = FindPrevious(P->team,Nodes[6]);
                                Insert(P->team , Nodes[6] , Nodes[6]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[6]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                               // struct TeamList* temp3 = FindPrevious(P->team , Nodes[6]);
                                Insert(P->team , Nodes[6] , Nodes[6]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[6] , P->team);
                }
                */
                 addLast(Nodes[6] , P->team);

            }
            // check if points reminder
            else if(((P->team.points/mode)%10) == 7){
                /*
                int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference
                if(IsEmpty(Nodes[7])){
                    addLast(Nodes[7] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[7]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[7])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[7]);
                                isInserted = 1;
                                break;
                            }
                            else{
                                //struct TeamList* temp2 = FindPrevious(P->team,Nodes[7]);
                                Insert(P->team , Nodes[7] , Nodes[7]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[7]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                               // struct TeamList* temp3 = FindPrevious(P->team , Nodes[7]);
                                Insert(P->team , Nodes[7] , Nodes[7]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[7] , P->team);
                }
                */
                 addLast(Nodes[7] , P->team);

            }
            // check if points reminder
            else if(((P->team.points/mode)%10) == 8){
                /*
                int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference
                if(IsEmpty(Nodes[8])){
                    addLast(Nodes[8] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[8]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[8])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[8]);
                                isInserted = 1;
                                break;
                            }
                            else{

                               // struct TeamList* temp2 = FindPrevious(P->team,Nodes[8]);
                                Insert(P->team , Nodes[8] , Nodes[8]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[8]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                                //struct TeamList* temp3 = FindPrevious(P->team , Nodes[8]);
                                Insert(P->team , Nodes[8], Nodes[8]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[8] , P->team);
                }
                */
                 addLast(Nodes[8] , P->team);
            }
            // check if points reminder
            else if(((P->team.points/mode)%10) == 9){
                /*
                int isInserted = 0;
                //The rest is to insert team that has same points based on goal difference

                if(IsEmpty(Nodes[9])){
                    addLast(Nodes[9] , P->team);
                    isInserted = 1;

                }
                else{
                    struct TeamList* temp1 = Nodes[9]->Next;
                    while(temp1!=NULL){
                        if(IsLast(temp1 , Nodes[9])){
                            if(P->team.GoalDifference > temp1->team.GoalDifference){

                                Insert(P->team , temp1 , Nodes[9]);
                                isInserted = 1;
                                break;
                            }
                            else{

                                //struct TeamList* temp2 = FindPrevious(P->team,Nodes[9]);
                                Insert(P->team , Nodes[9] , Nodes[9]);
                                isInserted = 1;
                                break;
                            }

                        }
                        else{
                            struct TeamList* temp2 = temp1->Next;
                            if(P->team.GoalDifference >= temp1->team.GoalDifference && P->team.GoalDifference <= temp2->team.GoalDifference){
                                Insert(P->team , temp1 , Nodes[9]);
                                isInserted = 1;
                                break;
                            }
                            else if(P->team.GoalDifference < temp1->team.GoalDifference){
                               // struct TeamList* temp3 = FindPrevious(P->team , Nodes[9]);
                                Insert(P->team , Nodes[9] , Nodes[9]);
                                isInserted = 1;
                                break;
                            }
                        }
                        temp1 = temp1->Next;

                    }
                }
                if(isInserted == 0){
                    addLast(Nodes[9] , P->team);
                }
                */
                 addLast(Nodes[9] , P->team);
            }



         P = P->Next;
        }
        array = MakeEmpty(array);
        readNodes(array , Nodes);



        mode*=10;
    }



    return array;

}
// function readNodes():is part of implementation of radix sort.Read the nodes to insert items of nodes in the team linked list:

void readNodes(struct TeamList *array ,struct TeamList* Nodes[]){
    int count =0;
    int size;

    // iterate the array of linked list:

    for(int i=0;i<10 ;i++){
        if(!IsEmpty(Nodes[i])){
            // check the size of linked list by call function sizeOfLinkedList() that return size of nodes:

             size = sizeOfLinkedList(Nodes[i]);


        // if size is greater than 0
        if(size >= 0){


        struct TeamList*P = Nodes[i]->Next;
        struct TeamList* temp;

        // insert the items of nodes from first index to last index at end of team linked list:

        while(P != NULL){

            addLast(array , P->team) ;
            P = P->Next;

        }



        }
    }

    }
    // make the nodes empty to fill it again:
    for(int i=0;i<10 ; i++){
            Nodes[i] = MakeEmpty(Nodes[i]);
    }


}
// function findMaxNumber(): find maximum number of points in linked list
int findMaxNumber(struct TeamList* L){
    int max = L->Next->team.points;
    struct TeamList* P = L->Next->Next;
    // iterate team linked list to find team of maximum number of points:
    while(P!=NULL){
        if(max < P->team.points){
            max = P->team.points;
        }
        P = P->Next;
    }

    return max;
}
//function findMaxDigitInList(): find maximum number of digits of points in linked list:
int findMaxDigitInList(struct TeamList* array){
    // first find maximum points in linked list by call the function findMaxNumber():
    int max = findMaxNumber(array);
    int maxDigit = 0;

    // iterate digits of maximum points to find number of digits of the maximum number:
    while(max > 0){
        max /= 10;
        maxDigit+=1;
    }
    return maxDigit;
}

// function to return size of team linked list:

int sizeOfLinkedList(struct TeamList* L){
    struct TeamList* P;
    int count =0;
    P = L;
    // iterate team linked list to find size of it:

    while(!IsLast(P, L)){
        count+=1;
        P=P->Next;

    }

    return count;


}



//function DeleteTeam(): delete selected team in team linked list:

void DeleteTeam( struct Team team , struct TeamList* L){
    struct TeamList* P;
    struct TeamList *temp;
    // find node before selected team:
    P= FindPrevious(team , L);
    // if node exist, delete node and make the prevoius points to next node of deleted node:
    if(P->Next != NULL){
        temp = P->Next;
        P->Next = temp->Next;
        free(temp);
    }

}
// function FindTeamByCode(): find team by team code in team linked list:
struct Team FindTeamByCode(char teamCode[40] , struct TeamList* L ){
    struct TeamList* tempList = L->Next;
    while(tempList != NULL){

        if(strcmp(teamCode , tempList->team.code) == 0){
            // if team found return Team struct:
            return tempList->team;
        }
        tempList = tempList->Next;
    }
    // if team not exist make default team:
    struct Team team;
    strcpy(team.code ,  "");
    strcpy(team.name ,"");
    team.GoalDifference =0;
    team.NoOfWins =0;
    team.NoOfDraws = 0;
    team.NoOfLoses = 0;
    team.points = 0;

    return team;
}

//function CreateMatch(): is the second phase of project
// it take code of two teams and print options to user to select
void CreateMatch(char firstTeamCode[40] , char secondTeamCode[40]){
    // check if teams exist in team linked list:
    struct Team firstTeam = FindTeamByCode(firstTeamCode , l1);
    struct Team secondTeam = FindTeamByCode(secondTeamCode , l1);

    if(strcmp(firstTeam.code , "") == 0 && strcmp(secondTeam.code , "")==0 ){
        printf("Both teams that with codes: %s and %s are not exist in the list\n" , firstTeamCode , secondTeamCode);
    }
    else if(strcmp(firstTeam.code , "") == 0){
        printf("The team that has code %s is not exist in the list\n" , firstTeamCode);
        printf("try again\n");
    }
    else if(strcmp(secondTeam.code , "")==0){
        printf("The team that has code %s is not exist in the list\n" , secondTeamCode);
        printf("try again\n");
    }
    else{
        // if both teams exist in the team linked list:

        struct TeamList* list = l1->Next;

        // iterate team linked list:
        //1- create teams elementary players linked list
        //2-create teams spare players linked list
        while(list != NULL){

            list->playerL = MakeEmptyPlayerList(list->playerL);
            list->playersQueue = CreatQueue(20);

            list = list->Next;
        }

        // create file (players.txt) to read from:
        FILE *playersFile;
        playersFile = fopen("players.txt" , "r");
        char all[1000];


        // iterate file players.txt line by line:
        while(fgets(all , 1000 , playersFile) != NULL){
            char teamCode[40];
            char playerName[200];
            struct TeamList* teamL;
            int count = 1;


            if(all[0] == '*'){
                // read new team players if line start with (*):

                strcpy(teamCode , strtok( all, "*\n ") );
                count =1;

                 teamL = l1->Next;
                 //find pointer of the team in linked list using team code:
                 while(teamL != NULL){

                    if(strcmp(teamL->team.code , teamCode) == 0){

                        break;
                    }
                    teamL = teamL->Next;

                 }





            }
            else{
                //read player information in specific team:

                struct Player player;
                int order = atoi(strtok(all , "-"));
                strcpy(playerName, strtok('\0' , "-\n"));


                strcpy(player.name , playerName);
                strcpy(player.TeamCode , teamCode);
                count++;
                if(order <= 11){
                    // to insert first 11 players into elementary players linked list in specific team:
                    addLastPlayerList(teamL->playerL , player);


                }
                else{
                    // Enqueue players after 11 until the last player to the queue of spare players in specific team:
                    Enqueue(player , teamL->playersQueue);
                }

            }
        }

        // close the read file players.txt
        fclose(playersFile);

        int input;
        struct TeamList* team1 = l1->Next;
        struct TeamList* team2 = l1->Next;

        // iterate team linked list to find pointer of team1 based on its code:
        while(team1 !=NULL){
            if(strcmp(team1->team.code,firstTeamCode) == 0){
                break;
            }
            team1 = team1->Next;
        }
        // iterate team linked list to find pointer of team2 based on its code:
        while(team2!=NULL){
            if(strcmp(team2->team.code , secondTeamCode) == 0){
                break;
            }
            team2 = team2->Next;
        }


        while(1){
            // print options of CreateMatch function:
            printf("1:change player from elementary and spare\n2:give red card to player from one of playing teams\n3:print players information\n4:save players information in file(playersInfo.txt)\n5:exit game\n");
            scanf("%d", &input);
            if(input == 1){
                // change player of elementary linked list by its name:
                int whichTeam;
                struct TeamList* team;
                while(1){
                    // make user choose between the two teams to make changes in:
                     printf("Enter which team to make changes in 1:%s 2:%s\n" , team1->team.code , team2->team.code);
                    scanf("%d" , &whichTeam);

                    if(whichTeam == 1){
                        team = team1;
                        break;
                    }
                    else if(whichTeam ==2){
                        team = team2;
                        break;
                    }
                    else{
                        // print error message if user enter wrong entry:
                        printf("wrong entry: try agian\n");
                    }
                }
                // read player name from the user:
                char playerName[100];
                printf("Enter name of player in team %s\n" , team->team.name);
                scanf("%s" , &playerName);
                struct PlayerList * player = team->playerL->Next;

                while(player!= NULL){
                    if(strcmp(player->player.name , playerName)==0){
                        break;
                    }
                    player = player->Next;
                }
                while(player == NULL){
                    // if player not exist print error message and try again:
                    printf("player %s is not exist\n" , playerName);
                    printf("Enter name of player in team %s\n" , team->team.name);
                    scanf("%s" , &playerName);
                    player = team->playerL->Next;
                    while(player!= NULL){
                        if(strcmp(player->player.name , playerName)==0){
                            break;
                        }
                        player = player->Next;
                    }

                }
                /* call function ChangeElementarySparePlayers(): to change the selected player from elementary players linked list to

                    spare players queue.Also put the front player in queue in elementary players linked list:

                */

                ChangeElementarySparePlayers(team , player);



            }
            else if(input == 2){
                //give red card to a player:


                int whichTeam;

                struct TeamList* team;
                while(1){
                    // ask user to choose between the two teams
                    printf("Enter which team to make changes in 1:%s 2:%s\n" , team1->team.code , team2->team.code);
                    scanf("%d" , &whichTeam);
                    if(whichTeam == 1){
                        team = team1;
                        break;
                    }
                    else if(whichTeam ==2){
                        team = team2;
                        break;
                    }
                    else{
                        // print error message to user if enter wrong entry and try again:
                        printf("wrong entry: try agian\n");
                    }
                }

                //read player name from the user:
                char playerName[100];
                printf("Enter name of player in team %s\n" , team->team.name);
                scanf("%s" , &playerName);
                struct PlayerList * player = team->playerL->Next;
                while(player!= NULL){
                    if(strcmp(player->player.name , playerName)==0){
                        break;
                    }
                    player = player->Next;
                }
                while(player == NULL){
                    // if player not exist print error message and try again:
                    printf("player %s is not exist\n" , playerName);
                    printf("Enter name of player in team %s\n" , team->team.name);
                    scanf("%s" , &playerName);
                    player = team->playerL->Next;
                    while(player!= NULL){
                        if(strcmp(player->player.name , playerName)==0){
                            break;
                        }
                        player = player->Next;
                    }

                }

                // call function GivePlayerRedCard(): to remove the choosen player from the elementary linked list, and remove it to spare players queue:
                GivePlayerRedCard(team , player);

            }
            else if(input == 3){
                //print information of a team on a screen:

                int whichTeam;

                struct TeamList* team;
                while(1){
                    // ask user to choose between the two teams to print its information:
                    printf("Enter which team to make changes in 1:%s 2:%s\n" , team1->team.code , team2->team.code);
                    scanf("%d" , &whichTeam);
                    if(whichTeam == 1){
                        team = team1;
                        break;
                    }
                    else if(whichTeam ==2){
                        team = team2;
                        break;
                    }
                    else{
                        //print error message if not exist and try again:
                        printf("wrong entry: try agian\n");
                    }
                }

                printf("Elementary player\n\n");
                // call function printPlayerList() that print information of elementary players
                printPLayerList(team->playerL);
                printf("Spare players\n\n");
                //call function printQueue() that print information of spare players
                printQueue(team->playersQueue);



            }
            else if(input == 4){
                //print team information in file (playersInfo.txt)
                int whichTeam;

                struct TeamList* team;
                while(1){
                    // ask user to choose between the two teams:
                    printf("Enter which team to make changes in 1:%s 2:%s\n" , team1->team.code , team2->team.code);
                    scanf("%d" , &whichTeam);
                    if(whichTeam == 1){
                        team = team1;
                        break;
                    }
                    else if(whichTeam ==2){
                        team = team2;
                        break;
                    }
                    else{
                        // print error message if user put wrong entry and try again:
                        printf("wrong entry: try agian\n");
                    }
                }

                // create file (playersInfo.txt) to write team players information in:
                FILE* playersFile;
                playersFile = fopen("playersInfo.txt" , "w");

                fprintf(playersFile , "team Name:%s\n" , team->team.name);
                fprintf(playersFile , "elementary players:\n");
                int count =1;
                struct PlayerList* elemtaryPlayers= team->playerL->Next;
                // iterate elementary player linked list and print players information in the file:
                while(elemtaryPlayers!=NULL){
                    fprintf(playersFile , "%d-%s\n" , count , elemtaryPlayers->player.name);
                    elemtaryPlayers = elemtaryPlayers->Next;
                    count++;
                }
                 Queue tempQ = CreatQueue(20);
                struct Player player = team->playersQueue->Array[team->playersQueue->Front];
                count =1;
                fprintf( playersFile, "spare players:\n");

                // iterate the spare players queue and print players informations in the file:
                while(!isEmptyQueue(team->playersQueue)){
                    player = FrontAndDequeue(team->playersQueue);
                    fprintf(playersFile , "%d-%s\n"  , count , player.name );
                    count++;
                    Enqueue( player, tempQ  );

                }
                // refill the queue after delete it to print every player informations in it:
                while(!isEmptyQueue(tempQ)){
                    player = FrontAndDequeue(tempQ);
                    Enqueue(player , team->playersQueue);
                }

                // close write file:
                fclose(playersFile);

            }
            else if(input == 5){
                // exit function CreateMatch
                break;
            }
            else{
                //print error message if user enter wrong entry:
                printf("Wrong entry\n");
                printf("try again\n\n");
            }

        }
    }

}

//function ChangeElementarySparePlayers(): remove player from the elementary linked list to the queue of spare linked list.Also remove the front of queue of spare players to elementary players linked list:
void ChangeElementarySparePlayers(struct TeamList* L ,struct PlayerList* player ){
    struct PlayerList* tempPlayer;
    tempPlayer = player;
    // call function DeletePlayer to remove the chosen player from elementary players linked list:
    DeletePlayer(player->player , L->playerL );
    struct Player temp2Player;
    // get the front of spare players queue and Dequeue it by call function FrontAndDequeue():
    temp2Player = FrontAndDequeue(L->playersQueue);
    //Enqueue the deleted player from elementary linked list to spare players queue
    Enqueue(tempPlayer->player , L->playersQueue);
    //add the spare player from queue to linked list:
    addLastPlayerList(L->playerL , temp2Player);
    //print message to confirm change:
    printf("change player %s with player %s\n" , tempPlayer->player.name , temp2Player.name);
}
//function GivePlayerRedCard():remove chosen player from elementary players linked list to spare players queue
void GivePlayerRedCard(struct TeamList* L , struct PlayerList* player){
    struct PlayerList* tempPlayer;
    tempPlayer = player;
    // call function DeletePlayer() to delete the chosen player from elementary players linked list
    DeletePlayer(player->player , L->playerL);
    // add the deleted player from elementary players linked list to spare players queue
    Enqueue(tempPlayer->player , L->playersQueue);
    //print message to user to confirm giving red card to the chosen player
    printf("Give player %s a red card\n" ,tempPlayer->player.name );

}

//function DisposeTeam(): to delete team linked list items and delete the head of the linked list
void DisposeTeamList(struct TeamList* L){
    L = MakeEmpty(L);
    free(L);
}
//function MakeEmptyPlayerList(): create player linked list if linked list not exist and delete all items if its exist and keep the head of the linked list:
struct PlayerList* MakeEmptyPlayerList(struct PlayerList* L){
    if(L != NULL){
        // call function DeletePlayerList(): to delete every player in it.
        DeletePlayerList(L);
    }
    // create the head of players linked list.
    L= (struct PlayerList*) malloc(sizeof(struct PlayerList));
    L ->Next = NULL;

    if(L == NULL){
        printf("wrong in memory storage\n");
    }

    return L;
}

//function addLastPlayerList():add new player to player linked list at the end of it
void addLastPlayerList(struct PlayerList* L , struct Player player){


    //create of new linked list:
    struct PlayerList* P = (struct PlayerList*)malloc(sizeof(struct PlayerList));
    struct PlayerList *temp;
    strcpy(P->player.name , player.name);
    strcpy(P->player.TeamCode , player.TeamCode);



    if(L->Next == NULL){
        P->Next = NULL;
        L->Next= P;
    }
    else{
        temp = L;
        //iterate players linked list to reach the end of it:
        while(temp->Next != NULL){
            temp = temp->Next;
        }
        temp->Next = P;
        P->Next = NULL;
    }

}

//function printPlayerList(): print informations of players in linked list:
void printPLayerList(struct PlayerList* L){
    struct PlayerList* P;
    P = L->Next;

    if(IsEmpty(L)){
        printf("The list is empty\n");

    }
    else{
        printf("code of team:%s\n",P->player.TeamCode );
        printf("players name:\n\n");
        //iterate the players linked list to print every player informations:
       while(P!=NULL){
            printf("%s\t" ,P->player.name);
            P=P->Next;
        }
    }

    printf("\n\n");
}
//function FindPreviousPlayer(): find the previous node of the selected team using player code
struct PlayerList* FindPreviousPlayer(struct Player  x , struct PlayerList* L){
    struct PlayerList* P;
    P = L ->Next;
    //iterate players linked list and find chosen player by his name
    while(P->Next != NULL && strcmp(P->Next->player.name ,  x.name) != 0) {
        P = P->Next;
    }
    return P;
}
//function DeletePlayer(): delete player from players linked list
void DeletePlayer(struct Player x , struct PlayerList* L){
    struct PlayerList* P;
    struct PlayerList *temp;
    // return prevoius  node of chosen player by call the function FindPreviousPlayer()
    P= FindPreviousPlayer(x , L);


    if(P->Next != NULL){
        temp = P->Next;
        P->Next = temp->Next;

        free(temp);
    }

}


//function CreateQueue():create new queue and return pointer of RecordQueue
Queue CreatQueue(int MaxElements){
    Queue q;
    if(MaxElements < MinQueueSize){
        printf("Queue size is too small\n");
    }
    q = (Queue)malloc(sizeof(struct QueueRecord));

    if(q== NULL){
        printf("out of space\n");
    }
    // create pointer to the array of Players
    q->Array = (struct Player*) malloc(sizeof(struct Player) * MaxElements);

    if(q->Array == NULL){
        printf("Out of space\n");
    }
    q->Capacity = MaxElements;
    MakeEmptyQueue(q);
    return q;

}
//function MakeEmptyQueue(): initialize the content of the array:
void MakeEmptyQueue(Queue q){
    q->Size = 0;
    q->Front = 1;
    q->Rear = 0;

}
//function DisposeQueue(): delete all content of the queue with the head:
void DisposeQueue(Queue q){
    if(q  == NULL){
        free(q->Array);
        free(q);
    }

}
// function isEmptyQueue():check if queue empty
int isEmptyQueue(Queue q){
    return q->Size == 0;

}
//function isFull():check if queue full
int isFull(Queue q){
    return q->Size == q->Capacity;

}
//function Succ():part of Enqueue implementation to change queue variables and return the rear index
int Succ(int  x , Queue q){
    if(++x == q->Capacity){
        return 0;
    }
    return x;
}
//function Enqueue():insert the player in queue
void Enqueue(struct Player x , Queue q){
    //call function isFull() to check if queue full:
    if(isFull(q)){
        printf("Full Queue\n");
    }
    else{
        q->Size++;
        q->Rear = Succ(q->Rear , q);
        q->Array[q->Rear] = x;

    }
}
//function Dequeue():delete the front item from the queue
void Dequeue(Queue q){
    //call function isEmptyQueue to check if queue empty
    if(isEmptyQueue(q)){
        printf("Queue is Empty\n");
    }
    else{
        q->Size --;
        q->Front = Succ(q->Front , q);
    }
}
//function Front(): return the front player of queue:
struct  Player Front(Queue q){
    if(!isEmptyQueue(q)){
        return q->Array[q->Front];

    }
    printf("Queue is Empty\n");
    struct Player player;
    strcpy(player.name ,"");

    strcpy(player.TeamCode, "");
    return player;
}
//function FrontAndDequeue():return Front player in queue and Dequeue the front(remove it from the queue) after that
struct Player FrontAndDequeue(Queue q){
    struct Player x;
    if(!isEmptyQueue(q)){
        x= q->Array[q->Front];
        q->Size--;
        q->Front = Succ(q->Front , q);
        return x;
    }
    printf("Queue is Empty\n");
    struct Player player;
    strcpy(player.name ,"");

    strcpy(player.TeamCode, "");
    return player;

}
//function printQueue():print all items in the queue
void printQueue(Queue q){
    Queue tempQ = CreatQueue(20);
    struct Player player = q->Array[q->Front];
    printf("teamCode:%s\n\n" , player.TeamCode);
    printf("player names:\n");
    // iterate queue and print and dequeue its items and enqueue them in temprorary queue
    while(!isEmptyQueue(q)){
        player = FrontAndDequeue(q);
        printf("%s\t" , player.name );
        Enqueue( player, tempQ  );

    }
    // dequeue the items from the temprorary queue and enqueue them in the players queue
    while(!isEmptyQueue(tempQ)){
        player = FrontAndDequeue(tempQ);
        Enqueue(player , q);
    }
    printf("\n\n");
}
/*void sortList() {
        //Node current will point to head
        struct node *current = head, *index = NULL;
        int temp;

        if(head == NULL) {
            return;
        }
        else {
            while(current != NULL) {
                //Node index will point to node next to current
                index = current->next;

                while(index != NULL) {
                    //If current node's data is greater than index's node data, swap the data between them
                    if(current->data > index->data) {
                        temp = current->data;
                        current->data = index->data;
                        index->data = temp;
                    }
                    index = index->next;
                }
                current = current->next;
            }
        }
}*/
void sortTeamList(struct TeamList* L){
    struct TeamList* current = L->Next;
    struct TeamList* index = NULL;
    struct Team temp;

    if(L == NULL){
        return NULL;
    }
    else{
        while(current !=NULL){
            index = current->Next;

            while(index !=NULL){
                if(current->team.points == index->team.points){
                    if(current->team.GoalDifference > index->team.GoalDifference){
                        temp = current->team;
                        current->team = index->team;
                        index->team = temp;
                    }
                }

                index = index->Next;
            }
            current = current->Next;
        }

    }

}


struct TeamList* sorted = NULL;
void sortedInsert(struct TeamList* newnode)
{

    // Special case for the head end
    if (sorted == NULL || sorted->team.GoalDifference >= newnode->team.GoalDifference   ) {
        newnode->Next = sorted;
        sorted = newnode;
    }
    else {
        struct TeamList* current = sorted;
        // Locate the node before the point of insertion




        while (current->Next != NULL && current->Next->team.GoalDifference <= newnode->team.GoalDifference ) {

            current = current->Next;

        }
        newnode->Next = current->Next;
        current->Next = newnode;

    }

}

struct TeamList *insertionsort(struct TeamList* L)
{

    struct TeamList* current = L->Next;


    while (current != NULL) {

        struct TeamList* next = current->Next;


        sortedInsert(current);


        current = next;
    }

    return sorted;
}
