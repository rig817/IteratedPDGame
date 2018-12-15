/*
 * Author:       Ryota Narita
 * Student ID:   b1014056
 * Class:        L
 * Created:      December 1, 2018
 * Language:     C
 */

/*
 * Load libralies
 *
 */

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef COOPERATION
#define COOPERATION 1
#endif

#ifndef DECEPTION
#define DECEPTION 0
#endif

int player1GameStepNum = 1;

void Player1(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
	double probability = 0.1;

	if (player1GameStepNum == 1) {
		*currentPlayer1Strategy = 1;	
	} else {
		if ((double)rand()/RAND_MAX < probability) {
			*currentPlayer1Strategy = 0;
		} else {
			*currentPlayer1Strategy = 1;
		}
		if (previousPlayer2Strategy == 0) {
			*currentPlayer1Strategy = 0;
		}
	}
	player1GameStepNum++;
}
