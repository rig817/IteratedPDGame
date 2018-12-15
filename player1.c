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

#ifndef PLAYER1_TTT
#define PLAYER1_TTT 1
#endif

#ifndef PLAYER1_PAV
#define PLAYER1_PAV 2
#endif



int player1GameStepNum = 1;
int player1CCount = 0;
int player1DCount = 0;
int player1ErrorCount = 0;
int player1DeceptionFlg = 0; // 最初の10回のうちに自分が裏切ったときのフラグ
int player1StrategyType;    // TTTかPAVかを格納するフラグ
int player1ChooseStrategy;  // player1が選択した戦略
int player1Resistance = 0;  // 相手の手応えがあるかないか

/*
 * 堪忍袋戦略(Tit-For-Two-Tat)
 */
void player1TTT(int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
	*currentPlayer1Strategy = COOPERATION;
	if (previousPlayer2Strategy == COOPERATION) {
		player1DCount = 0;
	} else {
		if (player1DCount++ >= 1) {
			*currentPlayer1Strategy = DECEPTION;
		}
	}
}

/*
 * パブロフ戦略
 */
void player1PAV(int previousPlayer1Strategy, int previousPlayer2Strategy,
									int *currentPlayer1Strategy)
{
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

void Player1(int previousPlayer1Strategy, int previousPlayer2Strategy, int *currentPlayer1Strategy)
{
	/* 最初の10回の対戦での行動*/
	if (player1GameStepNum <= 10) {
		*currentPlayer1Strategy = COOPERATION;

		/* エラーが発生したあとに相手が報復してくるか*/
	if (player1ChooseStrategy != previousPlayer1Strategy) {
		if (player1DeceptionFlg == 0 && previousPlayer2Strategy == DECEPTION) {
				player1Resistance = 1;
				player1DeceptionFlg = 1;
			}
		}

		/* もしエラーが発生していなければ9回目で裏切る*/
		if (player1DeceptionFlg != 1 && player1GameStepNum == 9) {
			*currentPlayer1Strategy = DECEPTION;
			player1DeceptionFlg = 1;
		}
	}

	/* 手応えの有無を判断、戦略を決定*/
	if (player1GameStepNum == 11) {

		/*前回エラーだったらフラグ立てる*/
		if (player1ChooseStrategy != previousPlayer1Strategy) {
			player1DeceptionFlg = 1;
		}
		/*9回目で裏切ったときに報復してきたらフラグ立てる*/
		if (player1DeceptionFlg == 1 && previousPlayer2Strategy == DECEPTION) {
			player1Resistance = 1;
		}
		if (player1Resistance == 1) {
			player1StrategyType = PLAYER1_TTT;
		} else {
			player1StrategyType = PLAYER1_PAV;
		}
	}

	/* 11回目以降の行動*/
	if (player1GameStepNum >= 11) {
		switch (player1StrategyType) {
			case PLAYER1_TTT:
				player1TTT(previousPlayer2Strategy, currentPlayer1Strategy);
				break;
			case PLAYER1_PAV:
				player1PAV(previousPlayer1Strategy, previousPlayer2Strategy, currentPlayer1Strategy);
				break;
		}
	}

	/*今回選んだ戦略を保存する*/
	player1ChooseStrategy = *currentPlayer1Strategy;
	/* 対戦回数のカウントを増やす*/
	player1GameStepNum++;
}
