// #include <stdio.h>: Includes the standard I/O library for input/output functions.
// #include <stdlib.h>: Includes the standard library for functions like rand() and srand().
// #include <time.h>: Provides the time() function to seed the random number generator.
// STARTING_BALANCE: Defines the initial amount of money the player starts with.
// REEL_SYMBOLS: Represents the number of symbols on the reels.
// symbols[]: Stores the symbols ('A', 'B', 'C', 'D', 'E') that appear on the reels.
// balance: Tracks the player's current money balance.

// rand() % REEL_SYMBOLS: Generates a random number between 0 and REEL_SYMBOLS-1.
// Uses pointers (*reel1, *reel2, *reel3) to set the values of the reel symbols.

// Winning Conditions:
// Three Matching Symbols: Multiplies the bet by a factor based on the symbol (e.g., 'A' gives 5x payout).
// Two Matching Symbols: Returns the bet amount as a small payout.
// No Matches: Returns 0.
// Switch Statement: Determines the payout multiplier for three matching symbols.

/*By passing the addresses of the variables (&reel1, &reel2, &reel3)
and using pointers (char* reel1, char* reel2, char* reel3), the spinReels()
function can directly modify the values stored at those memory locations. 
This ensures that changes made in spinReels() are reflected in the playSlotMachine() function.*/

/*Without srand():

The random sequence from rand() starts from the same fixed seed (often 1).
You'll get the same numbers every time you run the program.
With srand():

srand() initializes the random number generator.
Using different seeds (e.g., srand(time(0))) ensures different sequences.*/




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>//for sleep() function

#define STARTING_BALANCE 100
#define REEL_SYMBOLS 5

const char symbols[REEL_SYMBOLS] = {'A', 'B', 'C', 'D', 'E'};
int balance = STARTING_BALANCE;

//function declaration
void displayBalance();
void spinReels(char* reel1, char* reel2, char* reel3);
int calculatePayout(char reel1, char reel2, char reel3, int bet);
void playSlotMachine();
void displayRules();

int main() {
    srand(time(0)); // Initialize random number generator
    printf("\n Welcome to the Interactive Slot Machine Game! \n");
    printf("Let's test your luck! You start with $%d.\n", STARTING_BALANCE);
    displayRules();

    while (1) {
        if (balance <= 0) {
            printf(" You are out of money! Game Over. Better luck next time!\n");
            break;
        }

        printf("\nWhat would you like to do?\n");
        printf("[1] Play a round\n");
        printf("[2] View current balance\n");
        printf("[3] View the game rules\n");
        printf("[q] Quit the game\n");
        printf("Your choice: ");

        char choice;
        scanf(" %c", &choice); // Read single character inputṇṇṇ
        getchar(); // Consume newline character left by scanf

        if (choice == 'q') {
            printf("\n Thank you for playing! Your final balance is $%d. See you next time! \n", balance);
            break;
        }

        switch (choice) {
            case '1':
                playSlotMachine();
                break;
            case '2':
                displayBalance();
                break;
            case '3':
                displayRules();
                break;
            default:
                printf(" Invalid choice. Please enter 1, 2, 3, or 'q'.\n");
        }
    }

    return 0;
}

void displayBalance() {
    printf("\n Current Balance: $%d\n", balance);
}

void spinReels(char* reel1, char* reel2, char* reel3) {
    *reel1 = symbols[rand() % REEL_SYMBOLS];
    *reel2 = symbols[rand() % REEL_SYMBOLS];
    *reel3 = symbols[rand() % REEL_SYMBOLS];
}

int calculatePayout(char reel1, char reel2, char reel3, int bet) {
    if (reel1 == reel2 && reel2 == reel3) {
        switch (reel1) {
            case 'A': return bet * 5;
            case 'B': return bet * 4;
            case 'C': return bet * 3;
            case 'D': return bet * 2;
            case 'E': return bet * 1;
        }
    } else if (reel1 == reel2 || reel2 == reel3 || reel1 == reel3) {
        return bet * 1; // Small payout for two matches
    }
    return 0; // No payout
}

void playSlotMachine() {
    int bet;
    printf("\n Place your bet! (1 - $%d): ", balance);
    scanf("%d", &bet);
    getchar(); // Consume newline character left by scanf

    if (bet < 1 || bet > balance) {
        printf(" Invalid bet. Please bet between $1 and your current balance of $%d.\n", balance);
        return;
    }

    char reel1, reel2, reel3;
   

    printf("\n Spinning the reels...\n");
   
    Sleep(2000);//implemeenting the spinning function after 2 seconds delay

    spinReels(&reel1, &reel2, &reel3);
    printf("| %c | %c | %c |\n", reel1, reel2, reel3);

  
    int payout = calculatePayout(reel1, reel2, reel3, bet);
 if (payout > 0) {
        printf(" Congratulations! You won $%d!\n", payout);
        balance += payout;
    } else {
        printf(" Better luck next time. You lost $%d.\n", bet);
        balance -= bet;
    }

    displayBalance();
}

void displayRules() {
    printf("\n Game Rules:\n");
    printf("1. You start with $%d as your balance.\n", STARTING_BALANCE);
    printf("2. Each round, you place a bet within your available balance.\n");
    printf("3. The reels spin and show random symbols: A, B, C, D, or E.\n");
    printf("4. Payouts are as follows:\n");
    printf(" ***Three matching symbols:\n --A pays 5x,\n --B pays 4x,\n --C pays 3x,\n --D pays 2x,\n --E pays 1x your bet.\n");
    printf(" **Two matching symbols:\n --Pays back 1x your bet.\n");
    printf("5. If you run out of money, the game ends.\n");
    printf("6. You can quit anytime by choosing the 'q' option.\n");
    printf("\nGood luck and have fun! \n");
}
