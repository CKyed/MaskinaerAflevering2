#include <stdio.h>
//#include <vss.h>
#include <stdbool.h>
#include <string.h>
void printCardDeck();
void testCardDeck();


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
   struct Node *nextPointer;
   //En pointer der peger hen på kortet før
   struct Node *previousPointer;

}node;

//Et array af 7 pointers til HEAD i hver af de 7 linklister
struct node *headArray[7];
//Et array med alle vores 52 cord som der er i bunken ved start
struct card cardArray[52];

void printCardDeck();

int main() {
    printf("Hello, World!\n");
    testCardDeck();
    printCardDeck();


}
    void testCardDeck(){
        char tempChar="H";
        for (int i = 0; i < 4; ++i) {
            if(i==1){
                tempChar="D";
            }if(i==2){
                tempChar="C";
            }if(i==3){
                tempChar="S";
            }

            for (int i = 1; i < 14; ++i) {
                struct card tempCard;
                tempCard.rank=i;
                tempCard.suit=tempChar;
                tempCard.isFaceUp=true;
                //TODO Spørg en TA om hvorfor den ikke vil printe vores suit som char. Kan Måske være noget med pointers.
                printf("rank: %d suit: %c isFaceUp:%d \n",tempCard.rank,tempCard.suit,tempCard.isFaceUp);
                cardArray[i]=tempCard;

            }
        }

        for (int i = 0; i < 7; ++i) {
            //TODO Spørgsmål til TA: Når jeg laver en node "lokalt" i en metode, vil den så forblive når metoden ikke bliver brugt længere?
            struct node tempNode;
            tempNode.nodeCard=&cardArray[i];
            tempNode.nextPointer=NULL;
            tempNode.previousPointer=NULL;
            headArray[i]=&tempNode;
        }
        for (int i = 0; i < 7; ++i) {
            struct node tempNode;
            tempNode.nodeCard[i+7];
        }

}


    void printCardDeck(){

        bool nextPointer=true;
        char printCards[2][7];
        struct node tempCurrentNode[7];

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

