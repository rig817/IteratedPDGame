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
	if (player1GameStepNum == 1)
		*currentPlayer1Strategy = COOPERATION;
	else {
		if (previousPlayer1Strategy == COOPERATION && previousPlayer2Strategy == COOPERATION ||
				previousPlayer1Strategy == DECEPTION && previousPlayer2Strategy == COOPERATION) {
			*currentPlayer1Strategy = previousPlayer1Strategy;
		}	else {
			if (previousPlayer1Strategy == DECEPTION) {
				*currentPlayer1Strategy = COOPERATION;
			} else {
				*currentPlayer1Strategy = DECEPTION;
			}
		}
	}
	player1GameStepNum++;
}
