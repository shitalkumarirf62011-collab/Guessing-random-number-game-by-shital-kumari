/* Number Guessing Game
   Compile: gcc guess.c -o guess
   The best score (fewest attempts) is saved in the file best.txt */

#include <stdio.h>
#include <stdlib.h>     /* rand() and srand() */
#include <time.h>       /* time() - used to get a different random number every run */

#define MAX_TRIES 7

int best = 0;       /* best score so far (fewest attempts), 0 means no best score yet */

/* reads the best score from the file (0 means no best score yet) */
int readBest() {
    int best = 0;
    FILE *fp = fopen("best.txt", "r");
    if (fp != NULL) {
        if (fscanf(fp, "%d", &best) != 1)
            best = 0;
        fclose(fp);
    }
    return best;
}

/* writes a new best score to the file */
void saveBest(int tries) {
    FILE *fp = fopen("best.txt", "w");
    if (fp == NULL) {
        printf("(Could not save to a file, so the best score is kept only until the program closes.)\n");
        return;
    }
    fprintf(fp, "%d", tries);
    fclose(fp);
}

void play() {
    int secret = rand() % 100 + 1;      /* random number from 1 to 100 */
    int guess, tries = 0, result, c;

    printf("\nI have picked a number between 1 and 100.\n");
    printf("You have %d attempts.\n", MAX_TRIES);

    while (tries < MAX_TRIES) {
        printf("\nAttempt %d of %d - enter your guess: ", tries + 1, MAX_TRIES);
        result = scanf("%d", &guess);
        if (result == EOF)
            return;
        if (result != 1) {              /* the user typed a letter */
            printf("Please enter a number.\n");
            while ((c = getchar()) != '\n' && c != EOF)
                ;                       /* throw away the wrong input */
            continue;
        }
        if (guess < 1 || guess > 100) {
            printf("Enter a number between 1 and 100.\n");
            continue;
        }

        tries++;
        if (guess == secret) {
            printf("Correct! You guessed it in %d attempt(s).\n", tries);
            if (best == 0 || tries < best) {
                best = tries;
                saveBest(tries);
                printf("New best score!\n");
            }
            return;
        }
        if (guess < secret)
            printf("Too low. Try a bigger number.\n");
        else
            printf("Too high. Try a smaller number.\n");
    }
    printf("\nGame over! The number was %d.\n", secret);
}

int main() {
    int choice;

    srand(time(NULL));                  /* start the random number generator */
    best = readBest();                  /* load the saved best score (if the file exists) */
    do {
        printf("\n===== NUMBER GUESSING GAME =====\n");
        printf("1. Play\n2. Best score\n0. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
            choice = 0;                 /* if a letter is typed, exit */

        if (choice == 1) {
            play();
        } else if (choice == 2) {
            if (best == 0)
                printf("No best score yet. Play a game first!\n");
            else
                printf("Best score: %d attempt(s).\n", best);
        } else if (choice != 0) {
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    printf("Goodbye!\n");
    return 0;
}
