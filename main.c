#include <stdio.h>
//#include <vss.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Hjælpe funktioner
void printCardDeck();
void createCardDeck();
void createHeadNodes();
void createShowCardDeck();
void createGameCardDeck();
void createNewCardGame();
int loadFile();
void saveFile();
//void splitCardDeck(int split);
//void deleteNode();

//User interface
void userInterface();

//Endelige funktioner
int sw();
void sr();
void sd();
void ld();


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
    //Test fil placering
    //char tempChar[] = "E:\\Studie\\MaskinaerAflevering2v2\\.idea.\\file.txt";
    //ld(tempChar);
    createCardDeck();
    sd();
    printf("breakpoint");
    /*
    //Sørger for at sr funktionen har et nyt random seed hver gang
    time_t t;
    srand((unsigned) time(&t));
    //Vores fiktive headnodes der altid skal være der
    createHeadNodes();
    createCardDeck();
    createShowCardDeck();
    userInterface();
     */
}

    //User interfaceet
    void userInterface(){
        int running =1;
        int startUp=1;
        int playing=0;

        char *lastCommand,*message;
        char str[2];
        lastCommand="No last command";
        message="no message";
        while (running==1){



            //Startup fasen
            while (startUp==1){
                printf("LAST Command: %s\n",lastCommand);
                printf("Message: %s\n",message);
                printf( "Input: ");
                gets(str);

                if(0==strcmp(str,"SW")){
                    lastCommand="SW";
                    if(sw()==0){
                        message="No cards in deck";
                    }else{
                        message="OK";
                    }

                }

                else if(0==strcmp(str,"SR")){
                    //Tager ikke højde for om kort dækket er tomt, da det ikke står i opgaven. Vil være let er implementere, lige som i SW.
                    lastCommand="SR";
                    message="OK";
                    sr();
                }

                else if(0== strcmp(str,"QQ")){
                    //Lukker programmet
                    running=0;
                }

                else if(0== strcmp(str,"P")){
                    //Programmet går nu fra startup fasen til spille fasen
                    message="Du er nu i spille fasen";
                    lastCommand="P";
                    startUp=0;
                    playing=1;
                }else{
                    lastCommand="Ukendt kommando";
                    message="Ukendt kommando";
                }
            }

            //Spille fasen
            while(playing==1){
                printf("LAST Command: %s\n",lastCommand);
                printf("Message: %s\n",message);
                printf( "Input: ");
                gets(str);

                if(0== strcmp(str,"Q")){
                    //Vi går fra spille delen tilbage til startup fasen
                    //Da vores kortspil er gemt i et array som ikke bliver brugt til andet en at opbevare dens oprindelig stadie i behøver vi ikke at gøre yderligere
                    message="Du er nu i startup fasen";
                    lastCommand="Q";
                    playing=0;
                    startUp=1;
                }else{
                    lastCommand="Ukendt kommando";
                    message="Ukendt kommando";
                }
            }

        }
    }

    //Funktioner
    //1 LD<filename>
    void ld(char *fileName){
    if(fileName!=NULL){
        loadFile(fileName);
    }else{
        createCardDeck();
    }

}

    //2 SW
    int sw(){
    if(cardArray[0].rank==0){
        //Hvis der ikke er nogle kort i bunken
        return 0;
    }else{
        //Hvis der er kort i bunken
        createShowCardDeck();
        printCardDeck();
        return 1;
    }
}

    //4 SR
    void sr(){
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
        //TODO: skal det ik være rand()%52? Vælger den ik et random number fra 0 - 51 så?
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

    //5 SD
    void sd(char *fileName){
    if(fileName!=NULL){
        saveFile(fileName);
    }else{
        //TODO Hvad gør vi med denne mappestruktur når vi ikke kender brugerens mapper?
        saveFile("C:\\Users\\Public\\cards.txt");
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

    int loadFile(char *fileName) {
    //TODO Mangler check for om filen kan findes. Hvis den ikke findes skal den returnere 0. Kan godt undværes da vi tjekker for det i ld
    FILE  *fp;
    int c;
    //i bruges til at indsætte kortet i indexet i array
    int i=0;
    //counter bruges til at holde styr på hvilket element vi kigger på, på hver linje
    int counter=0;
    int returnNumber;
    fp = fopen(("%s",fileName),"r");

    while(1){

        c= fgetc(fp);
        printf("%c",c);
        if(feof(fp)){
            returnNumber=1;
            break;
        }
        if(counter==0){
            //Hvis der er et bogstav bliver det konverteret til den rigtige rank
            if(49<c && c<58){
                cardArray[i].rank=(c-48);
            }else if(c==65){
                cardArray[i].rank=1;
            }else if(c==84){
                cardArray[i].rank=10;
            }else if(c==74){
                cardArray[i].rank=11;
            }else if(c==81){
                cardArray[i].rank=12;
            }else if(c==75){
                cardArray[i].rank=13;
            }

            counter=counter+1;
        }else if(counter==1){
            cardArray[i].suit=c;
            counter=counter+1;
        }else if(counter==2){
            counter=0;
            i=i+1;
        }

    }
    fclose(fp);
    return returnNumber;
}

    void saveFile(char *fileName){
        FILE *fp;

        fp = fopen(("%s",fileName),"w+");

        for (int i = 0; i < 52; ++i) {
            char tempSuit = cardArray[i].suit;
            int tempInt=cardArray[i].rank;

            if(1<tempInt && tempInt<10){
                fprintf(fp,"%d%c\n",tempInt,tempSuit);
            }else if(tempInt==1){
                fprintf(fp,"A%c\n",tempSuit);
            }
            else if(tempInt==10){
                fprintf(fp,"T%c\n",tempSuit);
            }else if(tempInt==11){
                fprintf(fp,"J%c\n",tempSuit);
            }else if(tempInt==12){
                fprintf(fp,"Q%c\n",tempSuit);
            }else if(tempInt==13){
                fprintf(fp,"K%c\n",tempSuit);
            }
        }
        fclose(fp);
}
/*
void splitCardDeck(int split){
    //Laver 3 head nodes til de 3 bunker af kort vi kommer til at have
    struct node splitHeadArray[3];

    //Initialiserer linked listen på de 3 head nodes
    for (int i = 0; i < 3; ++i) {
        //printf("Adresse for i=%d %d \n",i,&headArray[i]);
        splitHeadArray[i].nextPointer=&headArray[i];
        splitHeadArray[i].previousPointer=&headArray[i];
    }
    //hvis parameter ikke bliver givet
    if(!split){
        //første halvdel af kortene bliver lagt i en stack
        for(int i = 0; i < 26; i++){
            insertAfter(splitHeadArray[0].previousPointer,&cardArray[i]);
        }
        //anden halvdel af kortene bliver lagt i en anden stack
        for(int i = 27; i < 52; i++){
            insertAfter(splitHeadArray[1].previousPointer,&cardArray[i]);
        }
        //vi ska ha det sidste kort fra hver stack hen i den sidste stack, indtil der ik er flere kort
        for(int i = 0; i < 52; i++){
            if(i % 2 == 0){
                for(int j = 0; j < 26; j++){
                    if(splitHeadArray[0].nextPointer->nodeCard == NULL){
                        insertAfter(splitHeadArray[2].previousPointer, (struct card *) &splitHeadArray[0].nodeCard);
                        deleteNode();
                    }

                }

            }
            else{

            }
        }
    }
        //hvis parameter bliver givet
    else{

    }

}
 */

/*
void deleteNode(struct node** headNode, struct node* del){
    //base case
    if(*headNode == NULL || del == NULL)
        return;
    //hvis noden der skal slettes er headnode
    if(*headNode == del)
        *headNode = del->nextPointer;
    //Ændrer nextpointer hvis noden der skal slettes ikke er den sidste node
    if(del->nextPointer != NULL)
        del->nextPointer->previousPointer = del->previousPointer;
    //Ændrer prevpointer hvis noden der skal slettes ikke er den første node
    if(del->previousPointer != NULL)
        del->previousPointer->nextPointer = del->nextPointer;
    //Frigør memory
    free(del);
    return;
}
 */


