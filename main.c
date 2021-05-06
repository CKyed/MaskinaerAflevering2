#include <stdio.h>
//#include <vss.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

void printCardDeck();
void testCardDeck();
void createHeadNodes();
void createShowCardDeck();
void createNewCardGame();

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
struct node headArray[7];
//Et array med alle vores 52 cord som der er i bunken ved start
struct card cardArray[52];

void printCardDeck();

int main() {
    testCardDeck();
    createHeadNodes();
    //createShowCardDeck();

    insertAfter(&headArray[1].previousPointer,cardArray[1]);
    insertAfter(&headArray[1].previousPointer,cardArray[2]);
    insertAfter(&headArray[1].previousPointer,cardArray[3]);
    insertAfter(&headArray[1].previousPointer,cardArray[4]);
    insertAfter(&headArray[1].previousPointer,cardArray[5]);
    printCardDeck();


}

    void createHeadNodes(){
    //Laver de 7 fiktive head noder
        for (int i = 0; i < 7; ++i) {
            headArray[i].nextPointer=&headArray[i];
            headArray[i].previousPointer=&headArray[i];
        }
}

    void createShowCardDeck(){
        for (int i = 0; i < 52; ++i) {
            int x = i%7;

            insertAfter(&headArray[x].previousPointer,cardArray[i]);

            struct card testTempCard = cardArray[i];


        }
}



    void insertAfter(struct node *prevNode,struct card* newCardPointer){
       if(prevNode==NULL){
            printf("Tidligere node er NULL");
            return;
        }

       //Opretter en ny node og allokere plads i memory til den
        struct node* newNode=(struct node*)malloc(sizeof (struct node));

       newNode->nodeCard=newCardPointer;


       newNode->nextPointer=prevNode->nextPointer;

        //nextPointer i noden før, peger nu hen til den nye nuværende node
        prevNode->nextPointer=newNode;

        //I den nye, nuværende node, peger prevNode nu hen til noden før
        newNode->previousPointer=prevNode;

        if(newNode->nextPointer!=NULL){
            newNode->nextPointer->previousPointer=newNode;
        }

        //TODO Skal fjernes. Vi tester her at alle noderne rent faktisk får et kort tildelt
        printf("Rank:%d ,Suit: %d, isFaceUp:%d \n",newNode->nodeCard->rank,newNode->nodeCard->suit,newNode->nodeCard->isFaceUp);

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
}


    void printCardDeck(){
        //PrintCardDeck er rigtig meget work in progress. Derfor kan der sagtens være fejl hvis man bruger den

        bool nextPointer=true;
        //Er måske overflødig
        //char printCards[2][7];
        struct node tempCurrentNode[7];

        for (int i = 0; i < 7; ++i) {
            //Vi arbejder med fiktive head nodes. Derfor vil vi gerne have at den første node er den første reele node med et kort.
            if(headArray[i].nextPointer!=NULL){

                //TODO Hvorfor fejler det her?! Hvorfor er nodeCard=NULL i tempTestNode, når vi debugger. Det tyder jo på at vi får fat i vores fiktive HEAD nodes og ikke det rigtige første element
                struct node tempTestNode=*headArray[i].nextPointer;
                struct card tempTestCard=*tempTestNode.nodeCard;
                printf("Rank: %d,\n",tempTestCard.rank);
                tempCurrentNode[i]=*headArray[i].nextPointer;
            }else{
                printf("Nextpointer var NULL, i=%d\n",i);
            }
        }

        printf("C1\tC2\tC3\tC4\tC5\tC6\tC7");
        printf("\n");

        int j =1;
         while(j==1){
             for (int i = 0; i < 7; ++i) {
                 if(tempCurrentNode[i].nodeCard != NULL){

                    struct card tempCard = *tempCurrentNode[i].nodeCard;

                     char tempCardSuit = tempCard.suit;
                     int tempCardRank = tempCard.rank;


                      printf("tempCard isFaceUp: %d",tempCard.isFaceUp);
                      if(tempCard.isFaceUp){
                          //Hvis kortet ikke er skjult
                          if(card.rank==1){
                              //char tempChar[2] = "A";
                              //printf(strcat(tempChar, tempCardSuit));

                          }else if(card.rank==10){

                          }else if(card.rank==11){

                          }else if(card.rank==12){

                          }else if(card.rank==13){

                          }else{

                          }

                      }else{
                          //Hvis kortet er skjult
                          //char tempChar= "[]";
                          //printCards[2][i]=tempChar;
                      }

            }
        }
             j=2;
        //printf("");
        //nextPointer=false;
    }



}

