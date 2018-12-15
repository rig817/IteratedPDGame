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
int player1DeceptionFlg = 0;

void Player1(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
	if (player1GameStepNum == 1) {
		*currentPlayer1Strategy = 1;
	} else {
		*currentPlayer1Strategy = 1;
		if (previousPlayer2Strategy == 0) {
			player1DeceptionFlg = 1;
		}
		if (player1DeceptionFlg != 0) {
			*currentPlayer1Strategy = 0;
		}
	}
	player1GameStepNum++;
}
