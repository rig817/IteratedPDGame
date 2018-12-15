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

int player2GameStepNum = 1;

void Player2(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer2Strategy)
{
	if (player2GameStepNum == 1)
		*currentPlayer2Strategy = COOPERATION;
	else {
		if (previousPlayer2Strategy == COOPERATION && previousPlayer1Strategy == COOPERATION ||
				previousPlayer2Strategy == DECEPTION && previousPlayer1Strategy == COOPERATION) {
			*currentPlayer2Strategy = previousPlayer2Strategy;
		}	else {
			if (previousPlayer2Strategy == DECEPTION) {
				*currentPlayer2Strategy = COOPERATION;
			} else {
				*currentPlayer2Strategy = DECEPTION;
			}
		}
	}
	player2GameStepNum++;
}
