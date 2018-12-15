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
int player2DeceptionFlg = 0;

void Player2(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer2Strategy)
{
	if (player2GameStepNum == 1) {
		*currentPlayer2Strategy = 1;
	} else {
		*currentPlayer2Strategy = 1;
		if (previousPlayer1Strategy == 0) {
			player2DeceptionFlg = 1;
		}
		if (player2DeceptionFlg != 0) {
			*currentPlayer2Strategy = 0;
		}
	}
	player2GameStepNum++;
}
