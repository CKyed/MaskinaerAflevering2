#include <stdio.h>
//#include <vss.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

void printCardDeck();
void testCardDeck();
void setupGame();
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
   struct card *nodeCard;
   //En pointer der peger hen på det næste kort
   struct node *nextPointer;
   //En pointer der peger hen på kortet før
   struct node *previousPointer;

}node;

//Et array af 7 pointers til HEAD i hver af de 7 linklister
struct node *headArray[7];
//Et array med alle vores 52 cord som der er i bunken ved start
struct card cardArray[52];

void printCardDeck();

int main() {
    testCardDeck();
    insertAfter(headArray[0],cardArray[0]);
    //printCardDeck();


}

    void setupGame(){
        /*//Vi opretter 7 fiktive HEAD-nodes.


    */
}

    void insertAfter(struct node *prevNode,struct card *newCardPointer){
       if(prevNode==NULL){
            printf("Tidligere node er NULL");
            return;
        }

       //Opretter en ny node og allokere plads i memory til den
        struct node *newNode=(struct node*)malloc(sizeof (struct node));

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

    void testCardDeck(){
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

        //Det her skal være i en metode for sig

        for (int i = 0; i < 7; ++i) {
            //Her oprette 7 fitkive HEAD noder. Index 0 svare til C1 og index 6 svare til C7
            struct node tempNode;
            tempNode.nodeCard=NULL;
            tempNode.nextPointer=NULL;
            tempNode.previousPointer=NULL;
            headArray[i]=&tempNode;
        }


        for (int i = 0; i < 52; ++i) {
            //Her skal linked listen bygges op ved hjælp af de fiktive HEAD noder.
            struct node tempNode;
            tempNode.nodeCard=&cardArray[i];
            int x = i%7;
            bool isNextPointer = true;

            struct node tempCheckNode =*headArray[x];


            while(isNextPointer){
                struct node *tempNodeNextPointer= tempCheckNode.nextPointer;
                if(tempNodeNextPointer==NULL){
                    //Stop while loopet
                    isNextPointer=false;

                }else{
                    //Vi opdatere vores tempCheckNode til at være den næste i rækken.
                    tempCheckNode=*tempNodeNextPointer;
                }

            }
            /*
            //Vi sætter den tidligere pointer til at pege hen på den nu nyeste node
            tempCheckNode.nextPointer=&tempNode;
            //Den nyeste node peger nu hen på den tidligere node
            tempNode.previousPointer=&tempCheckNode;
             */


        }

}


    void printCardDeck(){

        bool nextPointer=true;
        char printCards[2][7];
        struct node tempCurrentNode[7];

        for (int i = 0; i < 52; ++i) {
            struct card tempCard=cardArray[i];
            printf("i: %d Suit: %c Rank: %d isFaceUp: %d \n",i,tempCard.suit,tempCard.rank,tempCard.isFaceUp);

        }
        for (int i = 0; i < 7; ++i) {
            //TODO Skal tjekke om den rent faktisk giver pointeren
            //Her sørger vi for at den første pointer vi starter med peger på HEAD noden
            tempCurrentNode[i]=*headArray[i];
        }

        printf("C1\tC2\tC3\tC4\tC5\tC6\tC7");
        printf("\n");


         while(nextPointer){


             for (int i = 0; i < 7; ++i) {
                 if(tempCurrentNode[i].nextPointer != NULL){
                    //TODO Tjek om der er styr på pointers
                    struct card tempCard = *tempCurrentNode[i].nodeCard;
                    char tempCardSuit = tempCard.suit;
                    int tempCardRank = tempCard.rank;
                    bool tempCardIsFaceUp = tempCard.isFaceUp;

                    if(tempCardIsFaceUp){
                        //Hvis kortet ikke er skjult
                        if(card.rank==1){
                            char tempChar[2] = "A";
                            strcat(tempChar, tempCardSuit);

                        }else if(card.rank==10){

                        }else if(card.rank==11){

                        }else if(card.rank==12){

                        }else if(card.rank==13){

                        }else{

                        }

                    }else{
                        //Hvis kortet er skjult
                        char tempChar= "[]";
                        printCards[2][i]=tempChar;
                    }
            }


        }
        printf("");
        nextPointer=false;
    }




}

