#include <stdio.h>
#include <vss.h>
#include <stdbool.h>
#include <string.h>


struct card{
    char suit;
    int rank;
    bool isFaceUp;
} card;

struct node{
   struct card nodeCard;
   struct Node* next;
}node;

//Et array af 11 pointers til HEAD i hver af de 11 linklister
struct node *headArray[7];
//Et array med alle vores 52 cord som der er i bunken ved start
struct card cardArray[52];

int main() {
    printf("Hello, World!\n");
    return 0;

}

void test(){

}

_Noreturn void print(){
    bool nextPointer=true;
    char printCards[2][7];
    struct node *tempNextPointer[7];
    for (int i = 0; i < 7; ++i) {
        //TODO Skal tjekke om den rent faktisk giver pointeren
        //Her sørger vi for at den første pointer vi starter med peger på HEAD
        tempNextPointer[i]=headArray[i];
    }


    printf("C1\tC2\tC3\tC4\tC5\tC6\tC7");
    printf("\n");
    while(nextPointer){
        for (int i = 0; i < 7; ++i) {

            if(tempNextPointer[i]!=NULL){
                //TODO Tjek om der er styr på pointers
                struct card tempCard = tempNextPointer[i]->nodeCard;
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
    }



}

