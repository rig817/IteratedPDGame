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

#ifndef PLAYER2_TTT
#define PLAYER2_TTT 1
#endif

#ifndef PLAYER2_PAV
#define PLAYER2_PAV 2
#endif



int player2GameStepNum = 1;
int player2CCount = 0;
int player2DCount = 0;
int player2ErrorCount = 0;
int player2DeceptionFlg = 0; // 最初の10回のうちに自分が裏切ったときのフラグ
int player2StrategyType;    // TTTかPAVかを格納するフラグ
int player2ChooseStrategy;  // player2が選択した戦略
int player2Resistance = 0;  // 相手の手応えがあるかないか

/*
 * 堪忍袋戦略(Tit-For-Two-Tat)
 */
void player2TTT(int previousPlayer1Strategy, int *currentPlayer2Strategy)
{
	*currentPlayer2Strategy = COOPERATION;
	if (previousPlayer1Strategy == COOPERATION) {
		player2DCount = 0;
	} else {
		if (player2DCount++ >= 1) {
			*currentPlayer2Strategy = DECEPTION;
		}
	}
}

/*
 * パブロフ戦略
 */
void player2PAV(int previousPlayer1Strategy, int previousPlayer2Strategy,
									int *currentPlayer2Strategy)
{
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

void Player2(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer2Strategy)
{
	/* 最初の10回の対戦での行動*/
	if (player2GameStepNum <= 10) {
		*currentPlayer2Strategy = COOPERATION;

		/* エラーが発生したあとに相手が報復してくるか*/
	if (player2ChooseStrategy != previousPlayer2Strategy) {
		if (player2DeceptionFlg == 0 && previousPlayer1Strategy == DECEPTION) {
				player2Resistance = 1;
				player2DeceptionFlg = 1;
			}
		}

		/* もしエラーが発生していなければ9回目で裏切る*/
		if (player2DeceptionFlg != 1 && player2GameStepNum == 9) {
			*currentPlayer2Strategy = DECEPTION;
			player2DeceptionFlg = 1;
		}
	}

	/* 手応えの有無を判断、戦略を決定*/
	if (player2GameStepNum == 11) {

		/*前回エラーだったらフラグ立てる*/
		if (player2ChooseStrategy != previousPlayer2Strategy) {
			player2DeceptionFlg = 1;
		}
		/*9回目で裏切ったときに報復してきたらフラグ立てる*/
		if (player2DeceptionFlg == 1 && previousPlayer1Strategy == DECEPTION) {
			player2Resistance = 1;
		}
		if (player2Resistance == 1) {
			player2StrategyType = PLAYER2_TTT;
		} else {
			player2StrategyType = PLAYER2_PAV;
		}
	}

	/* 11回目以降の行動*/
	if (player2GameStepNum >= 11) {
		switch (player2StrategyType) {
			case PLAYER2_TTT:
				player2TTT(previousPlayer1Strategy, currentPlayer2Strategy);
				break;
			case PLAYER2_PAV:
				player2PAV(previousPlayer1Strategy, previousPlayer2Strategy, currentPlayer2Strategy);
				break;
		}
	}

	/*今回選んだ戦略を保存する*/
	player2ChooseStrategy = *currentPlayer2Strategy;
	/* 対戦回数のカウントを増やす*/
	player2GameStepNum++;
}
