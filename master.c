/*
 * Master Program for Iterative Prisoner's Dilemma Game (for Solaris)
 * version 1.0
 *
 * Authour: Ei-Ichi Osawa
 * Date: November 1, 2002
 * Copyright (c) 2002, Ei-Ichi Osawa, FUN
 *
 */

#define VERSION_1_0 1

/*
 * Load libralies (stdio.h, stdlib.h, time.h)
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

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

#ifndef COOPERATION
#define COOPERATION 1
#endif

#ifndef DECEPTION
#define DECEPTION 0
#endif

/* $B%2!<%`2s?t(B($B%G%#%U%)%k%HCM(B) */

#ifndef NUM_OF_GAME
#define NUM_OF_GAME 200
#endif

/* $B%(%i!<$r7hDj$9$kogCM$N@_Dj(B */

#ifndef ERROR
#define ERROR 5 
#endif

/*
 * $B3F%W%l%$%d$NMxF@7W;;(B
 * $BJV$jCM(B: $B$J$7(B
 */

void payoff(int strtgy1, int strtgy2, int *payoff1, int *payoff2) {

  if (strtgy1 == COOPERATION)  {
    if (strtgy2 == COOPERATION) {
      *payoff1 = 3;
      *payoff2 = 3;
    } else if (strtgy2 == DECEPTION) {
      *payoff1 = 0;
      *payoff2 = 5;
    } else {
      *payoff1 = 5;
      *payoff2 = 0;
    }
  } else if (strtgy1 == DECEPTION) {
    if (strtgy2 == COOPERATION) {
      *payoff1 = 5;
      *payoff2 = 0;
    } else if (strtgy2 == DECEPTION) {
      *payoff1 = 1;
      *payoff2 = 1;
    } else {
      *payoff1 = 5;
      *payoff2 = 0;
    }
  } else {
    if ((strtgy2 == COOPERATION) ||
	(strtgy2 == DECEPTION)) {
      *payoff1 = 0;
      *payoff2 = 5;
    } else {
      *payoff1 = 0;
      *payoff2 = 0;
    }
  }
  return;
}

/*
 * Game Master $B$N(B main $B4X?t(B
 * $BJV$jCM(B: $B@5>o$J$i(B 0, $B0J>e$J$i(B -1
 */

int main(int argc, char *argv[]) {
  int i, random, error_count1 = 0, error_count2 = 0;
  time_t t;
  int score1 = 0, score2 = 0;  /*$B3F%W%l%$%d$NAmF@E@(B */
  int payoff1, payoff2;   /*$B3F%W%l%$%d$N3F2s$N%2!<%`$NF@E@(B */
  int gameStepNum;  /* $B%2!<%`$N8=:_$N2s?t(B */
  int prevStrtgy1 = -1,  prevStrtgy2 = -1; /*$B3F%W%l%$%d$NA02s$N@oN,(B */
  int currentStrtgy1, currentStrtgy2; /*$B3F%W%l%$%d$N:#2s$N@oN,(B */

  /* $B0J2<$O%*%W%7%g%s;XDj$K$h$jJQ99$5$l$k2DG=@-$N$"$kJQ?t(B */
  int gameStepNum_Max = NUM_OF_GAME; /* $B%2!<%`$N:GBg%9%F%C%W?t(B */

  /*$BI8=`F~NO$+$i$N%Q%i%a!<%?=hM}(B */
  for (i=1; i < argc; i++) {
    /* "-s" $BBP@o2s?t%*%W%7%g%s$N=hM}(B */
    if(strcmp(argv[i], "-s")==0) {
      if (i+1 < argc) {
	gameStepNum_Max = atoi(argv[i+1]);
	if ((gameStepNum_Max > 0) &&  (gameStepNum_Max <= 10000)) {
	  i++;
	} else {
	  printf("Invalid input value!! Specify one positive number no more than 10000.\n");
	  /* $BCM$,BEEv$G$J$$>l9g(B*/
	  return(1);
	}
      } else {
	/* $B%*%W%7%g%s$N<!$KF~NO%Q%i%a!<%?$,$J$$>l9g(B */
	printf("Option error!! You must specify number of games.\n");
	return (1);
      }
    } else {
      printf("Invalid option:  available option is:\n");
      printf("-s: Specify number of games. ex: \"-s 200\"\n");
      return (1);
    }
  }

  /* $B;~4V$K0MB8$7$?Mp?t$N%7!<%I$N@_Dj(B */
  srand((unsigned) time(&t));

   /* $B%2!<%`%9%?!<%H(B */

   for (gameStepNum=1; gameStepNum <= gameStepNum_Max; gameStepNum++) {

     currentStrtgy1 = -1;
     currentStrtgy2 = -1;     

     /* $B3F%W%l%$%d$N@oN,7hDj(B*/
     Player1(prevStrtgy1, prevStrtgy2,  &currentStrtgy1);
     Player2(prevStrtgy1, prevStrtgy2,  &currentStrtgy2);

     /*$BMp?t$NH/@8(B*/
     random = rand()%100;

     /* $B%W%l%$%d(B1$B$K%(%i!<$,5/$-$?>l9g$O@oN,$r5U$K$9$k(B */

     if (random < ERROR) {
       error_count1++;

#ifdef DEBUG
       printf("ERROR on p1. step = %d, random = %d\n", gameStepNum, random);
#endif

       if (currentStrtgy1 == 0) {
	 currentStrtgy1 = 1;
       } else if (currentStrtgy1 == 1) {
	 currentStrtgy1 = 0;
       }
     }

     /*$BMp?t$NH/@8(B*/
     random = rand()%100;

     /* $B%W%l%$%d(B2$B$K%(%i!<$,5/$-$?>l9g$O@oN,$r5U$K$9$k(B */

     if (random < ERROR) {

       error_count2++;

#ifdef DEBUG
       printf("ERROR on p2. step = %d, random = %d\n", gameStepNum, random);
#endif

       if (currentStrtgy2 == 0) {
	 currentStrtgy2 = 1;
       } else if (currentStrtgy2 == 1) {
	 currentStrtgy2 = 0;
       }
     }

#ifdef DEBUG
     printf("p1: %d, p2: %d\n", currentStrtgy1, currentStrtgy2);
#endif

     prevStrtgy1 = currentStrtgy1;
     prevStrtgy2 = currentStrtgy2;

     /*$BN>%W%l%$%d$N:#2s$N@oN,$NMxF@$HAmF@E@$N7W;;(B */
     payoff(currentStrtgy1, currentStrtgy2,  &payoff1, &payoff2);

     score1 = score1 + payoff1; 
     score2 = score2 + payoff2; 

   }

   /* $B%2!<%`$N=*N;;~$NAmF@E@$NI=<((B */
   printf("Game Over!! Player1 score: %d, Player2 score: %d\n", score1, score2);

//#ifdef DEBUG

   printf("p1 error: %d, ratio: %f\n", error_count1, ((float) error_count1)/((float) gameStepNum_Max));
   printf("p2 error: %d, ratio: %f\n", error_count2, ((float) error_count2)/((float) gameStepNum_Max));

//#endif
   return(0);
}
