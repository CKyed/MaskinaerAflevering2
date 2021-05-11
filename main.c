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
void deleteNode();
void moveNode();
void extractInput();
void emptyLinkedList();
void insertAfter();

//User interface
void userInterface();

//Endelige funktioner
int sw();
void sr();
void sd();
void ld();
void si();

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

struct card headCard;

void printCardDeck();

int main(){
    //Test fil placering
    //char tempChar[] = "E:\\Studie\\MaskinaerAflevering2v2\\.idea.\\file.txt";

    //Sørger for at sr funktionen har et nyt random seed hver gang
    time_t t;
    srand((unsigned) time(&t));
    //Vores fiktive headnodes der altid skal være der
    createHeadNodes();
    //Userinterface som køre hele programmet
    userInterface();
}

    //User interfaceet
    void userInterface(){
        int running =1;
        int startUp=1;
        int playing=0;

        char *lastCommand,*message;
        char str[30];
        lastCommand="No last command";
        message="no message";
        while (running==1){

            //Startup fasen
            while (startUp==1){
                printf("LAST Command: %s\n",lastCommand);
                printf("Message: %s\n",message);
                printf( "Input: ");
                gets(str);

                //1 LD
                if(0==strncmp(str,"LD",2)){
                    printf("Default kortdaek, indtast 1. Load kortdaek fra fil, indtast 2 \n");
                    gets(str);
                    if(strcmp(str,"1")==0){
                        ld();
                        lastCommand="LD";
                        message="OK";
                    }else if(strcmp(str,"2")==0){
                        //TODO Note: Programmet vil crashe hvis filnavnet er forkert
                        //TODO NOTE Der skal også være 52 kort i kortdækket
                        //Testet på CKyeds computer med: E:\\Studie\\MaskinaerAflevering2v2\\.idea.\\file.txt
                        printf("Indtast filsti og filnavn:");
                        gets(str);
                        ld(str);
                        lastCommand="LD";
                        message="OK";
                    }
                }
                //2 SW
                else if(0==strncmp(str,"SW",2)){
                    lastCommand="SW";
                    if(sw()==0){
                        message="No cards in deck";
                    }else{
                        message="OK";
                    }
                }
                //3 SI
                else if(0== strncmp(str,"SI",2)){
                    lastCommand="SI";
                    if(cardArray[0].rank>0){
                        si();
                        message="OK";
                    }else{
                        message="Kortdaekket er tomt";
                    }
                }
                //4 SR
                else if(0==strncmp(str,"SR",2)){
                    lastCommand="SR";
                    if(cardArray[0].rank>0){
                        message="OK";
                        sr();
                    }else{
                        message="Kortdaekket er tomt";
                    }
                }
                //5 SD
                else if(0== strncmp(str,"SD",2)){
                    //TODO implementer SD med input
                    if(cardArray[0].rank>0){
                        sd();
                        message="OK";
                    }else{
                        message="Kortdaekket er tomt";
                    }
                }
                //6 QQ
                else if(0==strncmp(str,"QQ",2)){
                    //Lukker programmet
                    printf("Programmet lukkes");
                    running=0;
                    startUp=0;
                    playing=0;
                }
                //7 P
                else if(0== strncmp(str,"P",1)){
                    //Programmet går nu fra startup fasen til spille fasen
                    message="Du er nu i spille fasen. Indtast Q for at gaa tilbage til start fasen";
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
                //8 Q
                if(0== strncmp(str,"Q",1)){
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
    void ld(char fileName[]){
    if(strlen(fileName)>1){
        loadFile(fileName);
    }else{
        createCardDeck();
    }
}

    //2 SW
    int sw(){
    if(cardArray[0].rank>0){
        //Hvis der er kort i bunken
        createShowCardDeck();
        printCardDeck();
        return 1;
    }else{
        //Hvis der ikke er nogle kort i bunken
        return 0;
    }
}

    //3 SI
    void si(int split){
        //Laver 3 head nodes til de 3 bunker af kort vi kommer til at have
        struct node splitHeadArray[3];
        //Bruges til at holde styr på om der flere kort i en af min en af bunkerne
        int moreCards=1;

        int splitNumber;
        //Med den datastruktur vi har er vi nød til at arbejde med et andet midlertidigt kort bunke
        struct card tempCardArray[52];

        //Tjekker om spit vi får indtastet er et rigtigt tal. Hvis split ikke er et tal vi kan bruge(dermed ikke indtastet) bliver splitNumber sat til et tilfældigt tal
        if(split<53){
            if(split!=0){
                splitNumber=split-1;
            }else{
                splitNumber=split;
            }
        }else{
            splitNumber=(rand()%52);
        }

        //Vi kopiere kortbunken over
        for (int i = 0; i < 52; ++i) {
            tempCardArray[i].rank=cardArray[i].rank;
            tempCardArray[i].suit=cardArray[i].suit;
            tempCardArray[i].isFaceUp=cardArray[i].isFaceUp;
        }

        //Initialiserer linked listen på de 3 head nodes
        for (int i = 0; i < 3; ++i) {
            //printf("Adresse for i=%d %d \n",i,&headArray[i]);
            splitHeadArray[i].nextPointer=&splitHeadArray[i];
            splitHeadArray[i].previousPointer=&splitHeadArray[i];
            //Head noderne har et fiktivt kort en med rank=-1 for at kunne holde styr på hvornår vi rammer head
            struct card tempCard;
            tempCard.rank=-1;
            splitHeadArray[i].nodeCard=&tempCard;
        }

        //Ligger første halvdel af kortene over i en linked liste
        for(int i = 0; i < splitNumber; i++){
            insertAfter(splitHeadArray[0].previousPointer,&tempCardArray[i]);
        }
        //Ligger anden halvdel af kortene over i en linked liste
        for(int i = splitNumber; i < 52; i++){
            insertAfter(splitHeadArray[1].previousPointer,&tempCardArray[i]);
        }
        //Tager det sidste kort fra hver stack hen i den sidste stack, indtil der ik er flere kort.
        while (moreCards==1){
            //Tjekker om begge lister er tomme
            if(splitHeadArray[0].previousPointer->nodeCard->rank<0 && splitHeadArray[1].previousPointer->nodeCard->rank<0){
                //Stopper while loopet
                moreCards=0;
            }else{
                //Tjekker liste 0 er tom
                if(splitHeadArray[0].previousPointer->nodeCard->rank>0){
                    //Hvis liste ikke er tom tilføjes øverste element til liste 2
                    moveNode(splitHeadArray[0].previousPointer,splitHeadArray[2].previousPointer);
                } //Tjekker om liste 1 er tom
                if(splitHeadArray[1].previousPointer->nodeCard->rank>0){
                    //Hvis liste 1 ikke er tøm tilføjes øverste element til liste 2
                    moveNode(splitHeadArray[1].previousPointer,splitHeadArray[2].previousPointer);
                }
            }
        }

        //Kopiere liste 2 over i vores kort array
        for (int i = 0; i < 52; ++i) {
            //Kopiere dataen over
            cardArray[i].rank=splitHeadArray[2].previousPointer->nodeCard->rank;
            cardArray[i].suit=splitHeadArray[2].previousPointer->nodeCard->suit;
            cardArray[i].isFaceUp=splitHeadArray[2].previousPointer->nodeCard->isFaceUp;
            //Sletter noden. Vi benytter malloc
            deleteNode(splitHeadArray[2].previousPointer);
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
        for (int i = 0; i < 52; ++i) {
            int randomNumber = (rand()%52);
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
        saveFile("cards.txt");
    }


}

    //Hjælpe funktioner

    void createHeadNodes(){
        headCard.rank=-1;
        headCard.suit='f';
        headCard.isFaceUp=false;
        //Laver de 7 fiktive head noder
        for (int i = 0; i < 7; ++i) {
            //printf("Adresse for i=%d %d \n",i,&headArray[i]);
            headArray[i].nextPointer=&headArray[i];
            headArray[i].previousPointer=&headArray[i];

            //Alle head node kommer til at indeholde et fiktivt kort med rank -1
            headArray[i].nodeCard=&headCard;
        }
}

    void createShowCardDeck(){
        //Sørger for at linkedlisterne er tomme
        emptyLinkedList();
        for (int i = 0; i < 52; ++i) {
            int x = i%7;
            cardArray[i].isFaceUp=true;
            insertAfter(headArray[x].previousPointer,&cardArray[i]);
        }
}

    void createGameCardDeck(){
    //Tømmer linked listerne:
    emptyLinkedList();

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
                 if(tempCurrentNode[i].nodeCard->rank!=-1){
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
                              printf("Q%c",tempCard.suit);
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
        printf("\n");
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

    void moveNode(struct node* currentNode, struct node* previousNode){
        //Flytter en node
        currentNode->previousPointer->nextPointer=currentNode->nextPointer;
        currentNode->nextPointer->previousPointer=currentNode->previousPointer;

        currentNode->previousPointer=previousNode;
        currentNode->nextPointer=previousNode->nextPointer;

        previousNode->nextPointer=currentNode;

        currentNode->nextPointer->previousPointer=currentNode;
}

    void deleteNode(struct node* deleteNode){
        //Sletter en node og samtidig sørger
        //Sørger for at den næste node får ny korrekt previous pointer
        deleteNode->nextPointer->previousPointer=deleteNode->previousPointer;
        //Sørger for at den tidligere node får ny korrekt next pointer
        deleteNode->previousPointer->nextPointer=deleteNode->nextPointer;
        //Frigiver noden fra hukommelsen (malloc)
        free(deleteNode);
    }

    void emptyLinkedList(){
    int counter =0;
        while (counter!=7){
            counter=0;
            for (int i = 0; i < 7; ++i) {
                if(headArray[i].previousPointer->nodeCard->rank!=-1){
                    deleteNode(headArray[i].previousPointer);
                }else{
                    counter=counter+1;
                }
            }
        }
}