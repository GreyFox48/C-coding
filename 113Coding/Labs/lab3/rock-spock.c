/**                        
 * @file rock-spock.c
 * @author Matthew Olsen
 * @date September 23rd 2015
 * @brief Play Rock-paper-scissors-lizard-Spock against the machine 
 * @bugs none
 * @todo none
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>


#define COMPUTER 8088
#define PLAYER 1000

#define CHOICES 5

#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define LIZARD 3
#define SPOCK 4
#define TIE 6

#define INPUT_SIZE 25 /*to be used for user input string */

void move(int who, int move);
int winner(int computer, int player);
void print_winner(int winner, int comp_move, int player_move);
int nrand(int range);
void seed();


int main(void)
{
	int computer;
	int player = 0; 
        char input[INPUT_SIZE];    
        int rep;         

	/* set up the seed value for the random number generator */
	/* call only once */
	seed();

        while (1) {
	        printf("Enter a move:\n");
	        printf("0 for ROCK\n");
	        printf("1 for PAPER\n");
	        printf("2 for SCISSORS\n");
	        printf("3 for LIZARD\n");
	        printf("4 for SPOCK\n");
	        printf("5 to have SPOCK eat a ROCK while chasing a LIZARD and quit\n"); 
	        printf("Move: ");
	        fgets(input, INPUT_SIZE, stdin);

                /* ensure user input is digits */
                for(rep = 0; rep < INPUT_SIZE; rep++) {                        
                        if(input[rep] == '\n') {
                                break; /* ensures newline character will not cause false flag of invalid input */
                        }

                        if(!isdigit(input[rep])) {
                                printf("%c is not valid input.\n", input[rep]);
                                printf("Goodbye!\n");
                                return -1;
                        }
                }

                player = atoi(input);

                if (player == 5) {
                        printf("Goodbye!\n");
                        return 0;
                }

                if (player < 0 || player > 5) {
                        printf("%d is not valid input.\n", player);
                        printf("Goodbye!\n");
                        return -1;
                }  
	
                /* debug -- you don't need move() to play game  */
	        move(PLAYER, player);

                /* generate random number for computers play */
	        computer = nrand(CHOICES);

	        /*debug -- you don't need this to play the game */
	        move(COMPUTER, computer);        
        
                print_winner(winner(computer, player), computer, player);
        }

	return 0;
}


/** prints the player's or computer's  move to stdin 
 * used in debugging
 * @param who is it the computer or the player's move?
 * @param move what move did they make
 * @return void
 */
void move(int who, int move)
{
	if (who == COMPUTER) 
		printf("Computer's play is ");
	else 
		printf("Player's play is ");


	switch(move) {
	case ROCK:
		printf("ROCK\n");
		break;
	case PAPER:
		printf("PAPER\n");
		break;
	case SCISSORS:
		printf("SCISSORS\n");
		break;
	case SPOCK:
		printf("SPOCK\n");
		break;
	case LIZARD:
		printf("LIZARD\n");
		break;
    	}
}


/** 
 * determines the winner: either COMPUTER or PLAYER
 * @param computer the computer's move
 * @param player the player's move
 * @return the winner of the game
 */
int winner(int computer, int player)
{
	switch (player) {
        case ROCK:  /* if player chooses rock */
                switch (computer) {
                case ROCK: /* both tie */
                        return TIE;
                case SCISSORS:
                case LIZARD:
                        return PLAYER;
                default:
                        return COMPUTER;
                }
         case PAPER:  /* if player chooses paper */
                switch (computer) {
                case PAPER: /* both tie */
                        return TIE;
                case ROCK:
                case SPOCK:
                        return PLAYER;
                default:
                        return COMPUTER;
                }
         case SCISSORS:  /* if player chooses scissors */
                switch (computer) {
                case SCISSORS: /* both tie */
                        return TIE;
                case PAPER:
                case LIZARD:
                        return PLAYER;
                default:
                        return COMPUTER;
                }
         case LIZARD:  /* if player chooses lizard */
                switch (computer) {
                case LIZARD: /* both tie */
                        return TIE;
                case PAPER:
                case SPOCK:
                        return PLAYER;
                default:
                        return COMPUTER;
                }
         case SPOCK:  /* if player chooses spock */
                switch (computer) {
                case SPOCK: /* both tie */
                        return TIE;
                case ROCK:
                case SCISSORS:
                        return PLAYER;
                default:
                        return COMPUTER;
                }
        default:
                printf("ERROR: function winner defaulted.\n");
                return COMPUTER;
        }	
}

/** 
 * prints the winner of the game to stdin 
 * @param winner who won the computer or player
 * @param comp_move what move did the computer make
 * @param play_move what move did the player make
 * @return void
 */
void print_winner(int winner, int comp_move, int player_move)
{ 
        int winner_move = 0;
        int loser_move = 0;
	
        switch (winner) {
        case COMPUTER:
                printf("The computer wins!\n");
                winner_move = comp_move;
                loser_move = player_move;    
                
                switch (winner_move) { 
                case ROCK: /* rock wins against... */
                        switch (loser_move) {
                        case SCISSORS:
                                printf("Rock crushes scissors!\n");
                                break;
                        case LIZARD:
                                printf("Rock crushes lizard!\n");
                                break;                
                        }
                        break;

                case PAPER: /* paper wins against... */
                        switch (loser_move) {
                        case ROCK:
                                printf("Paper covers rock!\n");
                                break;
                        case SPOCK:
                                printf("Paper disproves Spock!\n");
                                break;                
                        }
                        break;

                case SCISSORS: /* scissors wins against... */  
                        switch (loser_move) {
                        case PAPER:
                                printf("Scissors cuts paper!\n");
                                break;
                        case LIZARD:
                                printf("Scissors decapitates lizard!\n");
                                break;
                        }
                        break;

                case LIZARD: /* lizard wins against... */  
                        switch (loser_move) {
                        case PAPER:
                                printf("Lizard eats paper!\n");
                                break;
                        case SPOCK:
                                printf("Lizard poisons Spock!\n");
                                break;               
                        }
                        break;

                case SPOCK: /* spock wins against... */  
                        switch (loser_move) {
                        case ROCK:
                                printf("Spock vaporizes rock!\n");
                                break;
                        case SCISSORS:
                                printf("Spock smashes scissors!\n");
                                break;                
                        }
                        break;
 
                }
                break; /* break for case COMPUTER */

        case PLAYER:
                printf("The player wins!\n");
                winner_move = player_move;
                loser_move = comp_move;    
                
                switch (winner_move) { 
                case ROCK: /* rock wins against... */
                        switch (loser_move) {
                        case SCISSORS:
                                printf("Rock crushes scissors!\n");
                                break;
                        case LIZARD:
                                printf("Rock crushes lizard!\n");
                                break;                
                        }
                        break;

                case PAPER: /* paper wins against... */
                        switch (loser_move) {
                        case ROCK:
                                printf("Paper covers rock!\n");
                                break;
                        case SPOCK:
                                printf("Paper disproves Spock!\n");
                                break;                
                        }
                        break;

                case SCISSORS: /* scissors wins against... */  
                        switch (loser_move) {
                        case PAPER:
                                printf("Scissors cuts paper!\n");
                                break;
                        case LIZARD:
                                printf("Scissors decapitates lizard!\n");
                                break;
                        }
                        break;

                case LIZARD: /* lizard wins against... */  
                        switch (loser_move) {
                        case PAPER:
                                printf("Lizard eats paper!\n");
                                break;
                        case SPOCK:
                                printf("Lizard poisons Spock!\n");
                                break;               
                        }
                        break;

                case SPOCK: /* spock wins against... */  
                        switch (loser_move) {
                        case ROCK:
                                printf("Spock vaporizes rock!\n");
                                break;
                        case SCISSORS:
                                printf("Spock smashes scissors!\n");
                                break;                
                        }
                        break; 
                }
                
                break; /* break for case PLAYER */
        case TIE: /* if player and computer chose some thing */
                printf("Tie!\n");
                switch (player_move) {
                case ROCK:
                        printf("The player and the computer both chose rock!\n");
                        break;                          
                case PAPER:
                        printf("The player and the computer both chose paper!\n");  
                        break;  
                case SCISSORS:
                        printf("The player and the computer both chose scissors!\n");   
                        break; 
                case LIZARD:
                        printf("The player and the computer both chose lizard!\n");  
                        break;  
                case SPOCK:
                        printf("The player and the computer both chose spock!\n");       
                        break;
                }

                break; /* break for case TIE */
        default:
                printf("ERROR: main switch in function print_winner fell through completely.\n");        
        }	
}

/**
 * returns a uniform random integer n, between 0 <= n < range
 * @param range defines the range of the random number [0,range)  
 * @return the generated random number
 */
int nrand(int range) 
{
	return rand() % range;
}

/**
 * call this to seed the random number generator rand()
 * uses a simple seed -- the number of seconds since the epoch 
 * call once before using nrand and similar functions that call rand()
 */
void seed(void) 
{
  	srand((unsigned int)time(NULL));
}
