#include <stdio.h>
//#include <vss.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

//Hjælpe funktioner
void printCardDeck();
void createCardDeck();
void createHeadNodes();
void createShowCardDeck();
void createGameCardDeck();
void createNewCardGame();
void randomShuffel();

//User interface
void userInterface();

//Endelige funktioner
int sw();

//Vi skal nok ikke bruge push til noget
void push();
void insertAfter();
void append();



struct card{
    char suit;
    int rank;
    bool isFaceUp;
} card;

struct node{
    //Hver node indeholder 3 pointers
    //En pointer der peger hen på et specifikt kort
   struct card* nodeCard;
   //En pointer der peger hen på det næste kort
   struct node* nextPointer;
   //En pointer der peger hen på kortet før
   struct node* previousPointer;

}node;

//Et array af 7 pointers til HEAD i hver af de 7 linklister
struct node headArray[7];
//Et array med alle vores 52 cord som der er i bunken ved start
struct card cardArray[52];

void printCardDeck();

int main() {
    //Sørger for at randomShuffel funktionen har et nyt random seed hver gang
    time_t t;
    srand((unsigned) time(&t));
    createHeadNodes();

    userInterface();


    //Exit bruger vi til opgave 6.
    exit(0);
}

    //User interfaceet
    void userInterface(){
        //Test int
        int j =0;

        char *lastCommand,*message;
        char str[2];
        lastCommand="No last command";
        message="no message";
        while (j<2){

            printf("LAST Command: %s\n",lastCommand);
            printf("Message: %s\n",message);
            printf( "Input: ");
            gets(str);

            if(0== strcmp(str,"SW")){
                lastCommand="SW";
                if(sw()==0){
                    message="No cards in deck";
                }else{
                    message="OK";
                }

            }


                j=j+1;
        }

    }

    //Funktioner

    //2 SW
    int sw(){
    if(cardArray[0].rank==0){
        return 0;
    }else{
        createShowCardDeck();
        printCardDeck();
        return 1;
    }


}

    //Hjælpe funktioner
    void createHeadNodes(){
    //Laver de 7 fiktive head noder
        for (int i = 0; i < 7; ++i) {
            //printf("Adresse for i=%d %d \n",i,&headArray[i]);
            headArray[i].nextPointer=&headArray[i];
            headArray[i].previousPointer=&headArray[i];
        }
}

    void createShowCardDeck(){
        for (int i = 0; i < 52; ++i) {
            int x = i%7;
            insertAfter(headArray[x].previousPointer,&cardArray[i]);
        }
}

    void createGameCardDeck(){
    //Laver linked listen der skal bruges til spillet;
    //Det første element tiløjes
    insertAfter(headArray[0].previousPointer,&cardArray[0]);
        int tempI;

        //Hvis der tages udgangspunkt i et ublandet kortdæk(Den vidst i opgave beskrivelsen) tilføjes kortene op til QH.
        //De kort der skal være faceDown bliver sat til det
        for (int i = 1; i < 7; ++i) {
            tempI=i;
            for (int j = 0; j < 6; ++j) {
                //Hvis kortet ikke er faceUp bliver den sat til false
                if(j<i){
                    cardArray[tempI].isFaceUp=false;
                }
                //Tilføjer kortene til vores linked list
                insertAfter(headArray[i].previousPointer,&cardArray[tempI]);
                tempI=tempI+6;
            }
        }
        //Prøvede at lave et loop for det her, men det viser sig ikke at være lige til. Derfor er det nemmere og bare at indtaste det manuelt.
        //I sidste ende er det alligevel det sammen og gør ingen forskel
        insertAfter(headArray[2].previousPointer,&cardArray[37]);

        insertAfter(headArray[3].previousPointer,&cardArray[42]);
        insertAfter(headArray[3].previousPointer,&cardArray[38]);

        insertAfter(headArray[4].previousPointer,&cardArray[39]);
        insertAfter(headArray[4].previousPointer,&cardArray[43]);
        insertAfter(headArray[4].previousPointer,&cardArray[46]);

        insertAfter(headArray[5].previousPointer,&cardArray[40]);
        insertAfter(headArray[5].previousPointer,&cardArray[44]);
        insertAfter(headArray[5].previousPointer,&cardArray[47]);
        insertAfter(headArray[5].previousPointer,&cardArray[49]);

        insertAfter(headArray[6].previousPointer,&cardArray[41]);
        insertAfter(headArray[6].previousPointer,&cardArray[45]);
        insertAfter(headArray[6].previousPointer,&cardArray[48]);
        insertAfter(headArray[6].previousPointer,&cardArray[50]);
        insertAfter(headArray[6].previousPointer,&cardArray[51]);

}

    void insertAfter(struct node *prevNode,struct card* newCardPointer){
       if(prevNode==NULL){
            printf("Tidligere node er NULL");
            return;
        }

       //Opretter en ny node og allokere plads i memory til den
       struct node* newNode=(struct node*)malloc(sizeof (struct node));
       //struct node newNode;

       newNode->nodeCard=newCardPointer;

       newNode->nextPointer=prevNode->nextPointer;

        //nextPointer i noden før, peger nu hen til den nye nuværende node
        prevNode->nextPointer=newNode;

        //I den nye, nuværende node, peger prevNode nu hen til noden før
        newNode->previousPointer=prevNode;

        if(newNode->nextPointer!=NULL){
            newNode->nextPointer->previousPointer=newNode;
        }
}

    void createCardDeck(){
    //Test card skal kun oprette 52 kort og putte det ind i vores cardArray.
        char tempChar='H';
        int tempInt=0;
        for (int i = 0; i < 4; ++i) {
            if(i==1){
                tempChar='D';
            }if(i==2){
                tempChar='C';
            }if(i==3){
                tempChar='S';
            }

            for (int i = 1; i < 14; ++i){
                struct card tempCard;
                tempCard.rank=i;
                tempCard.suit=tempChar;
                tempCard.isFaceUp=true;
                //printf("rank: %d suit: %c isFaceUp:%d \n",tempCard.rank,tempCard.suit,tempCard.isFaceUp);
                cardArray[i+tempInt-1]=tempCard;
            }
            tempInt=tempInt+13;
        }
}

    void printCardDeck(){
        //Printer linked listerne som de ser ud.
        int numberOfNULLNodeCards = 0;
        int counter = 0;
        bool nextPointer=true;
        struct node tempCurrentNode[7];

        for (int i = 0; i < 7; ++i) {
            //Vi arbejder med fiktive head nodes. Derfor vil vi gerne have at den første node er den første reele node med et kort.
            if(headArray[i].nextPointer!=NULL){
                tempCurrentNode[i]=*headArray[i].nextPointer;
            }
        }
        printf("C1\tC2\tC3\tC4\tC5\tC6\tC7");
        printf("\n\n");


        while(nextPointer==true){
             for (int i = 0; i < 7; ++i) {
                 if(tempCurrentNode[i].nodeCard != NULL){

                    struct card tempCard = *tempCurrentNode[i].nodeCard;

                      if(tempCard.isFaceUp){
                          //Hvis kortet ikke er skjult
                          if(tempCard.rank==1){
                              printf("A%c",tempCard.suit);
                          }else if(tempCard.rank==10){
                              printf("T%c",tempCard.suit);
                          }else if(tempCard.rank==11){
                            printf("J%c",tempCard.suit);
                          }else if(tempCard.rank==12){
                              printf("D%c",tempCard.suit);
                          }else if(tempCard.rank==13){
                              printf("K%c",tempCard.suit);
                          }else{
                                printf("%d%c",tempCard.rank,tempCard.suit);
                          }
                      }else{
                          //Hvis kortet er skjult
                          printf("[]");
                      }
                      tempCurrentNode[i]=*tempCurrentNode[i].nextPointer;
            }else{
                     //Vi tæller hvor mange gange vi har et NULL card. Hvis alle 7 har NULL card betyder det at vi har været hele listen igennem da vi dermed har ramt head node igen
                    numberOfNULLNodeCards=numberOfNULLNodeCards+1;
                    if(numberOfNULLNodeCards==7){
                        nextPointer=false;
                    }
                 }
                 printf("\t");
        }
             if(counter==0||counter==2||counter==4||counter==6){
                 int fValue=(counter/2)+1;
                 printf("\t\t[]\tF%d",fValue);
             }
             //Vi nulstiller antallet af NULL card hver gang
             numberOfNULLNodeCards=0;
             printf("\n");
             counter=counter+1;
    }
}

    void randomShuffel(){
        //Opgave 4
        //Laver et midlertidigt kort array
        struct card tempCardArray[52];
        //Putter data ind i det midlertidige kort array
        for (int i = 0; i < 52; ++i) {
            tempCardArray[i].rank=0;
            tempCardArray[i].suit= 'f';
            tempCardArray[i].isFaceUp=false;
        }

        //Undersøger om næste element i bunken er tomt. Hvis det er putter den kortet her, hvis ikke undersøge den det næste igen, indtil den finder et tom plads.
        //Stopper når den har fundet en tom plads at ligge kortet på.
        for (int i = 0; i < 52; ++i) {
            int randomNumber = (rand()%51);
            //Hvis der ikke allerede ligger et kort på den position
            if(!(tempCardArray[randomNumber].rank>0)){
                tempCardArray[randomNumber].rank=cardArray[i].rank;
                tempCardArray[randomNumber].suit=cardArray[i].suit;
                tempCardArray[randomNumber].isFaceUp=cardArray[i].isFaceUp;
            }else{
                //Hvis der ligger et kort på den oprindelige possition
                int tempNumber=randomNumber;
                for (int j = 0; j < 52; ++j) {
                    //Hvis det index nummeret er det sidste i bunken, starter den fra 0 istedet
                    if(tempNumber == 51){
                        tempNumber=0;
                    }else{
                        //Hvis det ikke er det sidste element i bunken undersøger den næste element
                        tempNumber=tempNumber+1;
                    }

                    //Hvis det element der undersøges er tomt, gemmes kortet her.
                    if(!(tempCardArray[tempNumber].rank > 0)){
                        tempCardArray[tempNumber].rank=cardArray[i].rank;
                        tempCardArray[tempNumber].suit=cardArray[i].suit;
                        tempCardArray[tempNumber].isFaceUp=cardArray[i].isFaceUp;
                        //Sørger for at for loopet stopper
                        j=52;
                    }
                }
            }
        }

        //Gemmer kortet i vores oprindelige kort array
        for (int i = 0; i <52; ++i) {
            cardArray[i].rank=tempCardArray[i].rank;
            cardArray[i].suit=tempCardArray[i].suit;
            cardArray[i].isFaceUp=tempCardArray[i].isFaceUp;
        }
}



