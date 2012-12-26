//pass for home work linked-list
/*
 * main.c
 *  Created on: Oct 30, 2012
 *      Author: ehud
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "src.h"
#include "tests.h"

#define _DEBUG 1
//#define _TESTS 1
//#define _RELEASE 1
int main ()
{
	printf("start\n");
	//print_int(10,15);
	//test_is_threat();
	//test_game_start();
	//@todo switch king and rook
	//@todo take the code of the switch and wrap it with a function is_ok
	//@todo color the soldiers
	play_game();
	//test_pawn();
	//test_knight();
	//test_bishop();
	//test_rook();
	//test_queen();
	//test_game_start();
	//test_king();
	//char *b = "hello";
	//int result;
	//assert(strcmp(b,"hello") == 0);
	//result = strcmp(b,"bello");
	//printf("%d,",result);
	//assert((b == "h") == 1);
	printf("end game");

}
