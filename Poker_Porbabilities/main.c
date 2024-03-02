/*
  This Code uses Monte-Carlo simulation to calculate
  the frequency of 7-card poker hands.

  Ramin Akbari Jul 2021
*/


typedef enum suits {hearts,diamonds,spades,clubs} suits;
typedef struct cards {unsigned short p; suits s;} cards;

// required lib
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// constants
#define NSIM 4000000
#define NDECK 52
#define NPIPS 13
#define NSUITS 4
#define NHAND 7



void set_counts(cards *deck,unsigned int *pips_count,unsigned int *suits_count) {

    /*
     This function increments the pips and suits
     that correspond to the hand. We will use this
     to detect the hand.
    */
    unsigned short i;
    for (i=0;i<NHAND;i++){
        ++pips_count[deck[i].p];
        ++suits_count[deck[i].s];
    }
}

unsigned short check_suits(const unsigned int *suits_count){

    /*
     This function checks for the flush.
     the output is as follows
     0-3 flush hand and the number is the corresponding suits
     4   not a flush hand
    */

    unsigned short i = 0;
    while (i < 4 && suits_count[i] < 5)
        i++;
    return i;
}


void check_pips(const unsigned int *pips_count,unsigned int *cnd){

    /*
     This function checks for pair, three , full house , four , straight.
     We look at the frequency of pips.
     For straight, we look for consecutive frequency that are greater than zero
    */

    unsigned int i,pairs = 0,straight = 0,three = 0, four = 0;
    for (i = 0;i<NPIPS;i++){

        if (pips_count[i] == 2)
            ++pairs; // increment pair counter
        else if(pips_count[i] == 3)
            ++three; // increment three counter we can have two threes
        else if(pips_count[i] == 4)
            four = 1; // set to one ( max possible is 1 )

        // check consecutive elements that are not zero
        if (pips_count[i]>0 && pips_count[(i+1)%NPIPS]>0)
            ++straight;
        else if (straight && straight <4)
            straight = 0; // reset straight counter
    }

    if (four) {
        cnd[0] = 5; // Four Of A Kind

    }else if (three) {
        if (three > 1 || pairs > 0) {
            cnd[0] = 4; // Full House
        }else {
            cnd[0] = 3; // Three of a kind
        }

    }else if (pairs > 1) {
        cnd[0] = 2; // Two Pairs

    }else if (pairs == 1) {
        cnd[0] = 1;

    }else {
        cnd[0] = 0;
    }

    // check for straight separately. Because we also use this to
    // check for straight flush
    if (straight>3)
        cnd[1] = 1; // Straight

    else
        cnd[1] = 0; // No Straight
}

unsigned short check_straight_flush(cards *deck,unsigned int *pips_count ,const unsigned int color){

    /*
     This function checks the possibility for straight flush or royal.
     Before calling this function first we check for straight and flush
     if they are true then we call this function. This is for improving
     the performance. Check for straight flush in general is more complex
     compared to checking for flush or straight.

     Note : we can have a hand which is flush and straight but is not a straight flush.
    */

    unsigned int i;

    // removing the suits that does not belong to the flush suits
    for (i = 0; i<NHAND; i++){
        if (deck[i].s != color)
            --pips_count[deck[i].p];
    }

    // check for royal straight flush
    if (pips_count[0] && pips_count[NPIPS-1]) {
        i = 0;
        // go back from the king to check for royal straight flush
        while (pips_count[NPIPS - 2 - i] && i<3)
            ++i;
        if (i==3)
            return 2; // royal straight flush
    }

    // check for straight flush that is checking
    // for consecutive elements that are not zero
    unsigned int j = 0;
    for (i = 0;i<NPIPS-1;i++){
        if (pips_count[i]>0 && pips_count[(i+1)]>0)
            ++j;
        else if (j && j <4)
            j = 0;
    }

    if (j>3)
        return 1; // straight flush

    return 0; // Nope! This is not a james bond movie !
}

unsigned int eval_hand(cards *deck){

    /*
      This function evaluates the hand. based on the outputs
      of the previous functions. It returns a values which shows
      the status of the hand.
      0 = Royal , 1 = St-Flush , 2 = Four
      3 = Full  , 4 = Flush , 5 = Straight
      6 = Three , 7 = Two pairs , 8 = pair
      9 = High card
    */

    unsigned int cnd[2],pips_count[NPIPS]={0},suits_count[NSUITS]={0},color,st_flush;
    // increment pips_count and suits_count
    set_counts(deck,pips_count,suits_count);

    // checking for pairs,three,straight based on pips
    check_pips(pips_count,cnd);

    // checking for flush based on suits.
    color = check_suits(suits_count);

    if (color<4 && cnd[1]) { // straight flush ( or royal ) is possible
        st_flush = check_straight_flush(deck, pips_count, color);

        if (st_flush == 2)
            return 0; // royal straight flush
        if (st_flush == 1)
            return 1; // straight flush

        return 4; // flush ( Note : if straight is true then four of a kind and full house did not occur )
    }

    if (cnd[0] == 5)
        return 2; // four of a kind
    if (cnd[0] == 4)
        return 3; // full house
    if (color<4)
        return 4; // flush
    if (cnd[1])
        return 5; // straight
    if (cnd[0] == 3)
        return 6; // three of a kind
    if (cnd[0] == 2)
        return 7; // two pairs
    if (cnd[0] == 1)
        return 8; // one pairs

    return 9;
}


void shuffle_deck(cards *deck){

    /*
     This function shuffles the deck
     At each iteration "i" it generates random number "j"
     which is greater than "i".
     For more on algorithms on shuffle use wikipedia:
     https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle

     Note : If you are using Windows replace
     random() with rand() for compatibility.
    */
    unsigned int i,j;
    cards tmp;

    for (i = 0; i < NDECK - 1; i++) {
        // generate random j such that i<=j
        j = i + random() % (NDECK-i);
        // swapping indexes
        tmp = deck[i];
        deck[i] = deck[j];
        deck[j] = tmp;
    }
}

/*
 I created this function for the purpose of debugging.
 To make it more readable I used symbols for suits.
 It prints the first 7 cards of the deck.
*/
void print_card(cards *deck) {
    static char* pips_name[NPIPS] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    static char* suits_name[NSUITS] = {"♥️","♦️","♠️","♣️"};
    for(int j=0;j<NHAND;j++)
        printf("%3s %3s ",pips_name[deck[j].p],suits_name[deck[j].s]);
    printf("\n\n");
}


int main(void)
{

    int i,cond[10]={0};
    unsigned int sec = time(NULL);
    char* hand_name[10] = {"Royal Straight Flush","Straight Flush","Four Of A Kind","Full House","Flush","Straight","Three of A Kind","Two Pairs","One Pair","High Card"};
    cards deck[NDECK];

    // creating the deck cards
    for (i=0;i<NDECK;i++) {
        deck[i].p = i % 13;
        deck[i].s = i / 13; // note this is an integer division and is always between (0-3)
    }

    srandom(sec); // reset random seed replace with srand() for rand()


     //comment this part if you just want the simulation
    printf("\nSome examples of the code output :\n\n") ;
    for(i=0;i<5;i++){
        shuffle_deck(deck);
        printf("%-22s",hand_name[eval_hand(deck)]);
        print_card(deck);
    }

    clock_t n_clck = clock();

    // simulation loop
    for(i=0;i<NSIM;i++){
        shuffle_deck(deck);
        ++cond[eval_hand(deck)];
    }

    double elp_tm = (double) (clock() - n_clck)/CLOCKS_PER_SEC;
    // output
    printf("\n\nResults of Monte-Carlo Simulation for %d sampling\n\n",NSIM);
    for(i=0;i<10;i++)
        printf("%-22s : %8.4lf %% \n",hand_name[i],(double) cond[i]/NSIM*100.0);
    printf("\n\n\n");
    printf("Elapsed time :  %6.5lf \n",elp_tm);
    return 0;

}

