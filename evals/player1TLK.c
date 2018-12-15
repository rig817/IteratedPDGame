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
int player1CCount = 0;
double player1Probability;

void Player1(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
	if (player1GameStepNum <= 10) {
		*currentPlayer1Strategy = 1;
		if (previousPlayer2Strategy == 1)
			player1CCount++;
	}
	if (player1GameStepNum == 11) {
		if (previousPlayer2Strategy == 1)
			player1CCount++;
		player1Probability = (player1CCount - 1.0) * 0.1;
		if (player1Probability < 0) player1Probability = 0.0;
	}
	if (player1GameStepNum >= 11) {
		if ((double)rand()/RAND_MAX < player1Probability) {
			*currentPlayer1Strategy = 1;
		} else {
			*currentPlayer1Strategy = 0;
		}
	}

	player1GameStepNum++;
}
