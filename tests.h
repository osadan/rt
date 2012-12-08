/*
 * tests.h
 *
 *  Created on: Dec 6, 2012
 *      Author: ehud
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "src.h"


#ifndef TESTS_H_
#define TESTS_H_
int test_move();
void test_rook();
void test_bishop();
void test_knight();
void test_pawn();
void test_queen();
void test_king();
void test_game_start();
void test_is_threat();


#endif /* TESTS_H_ */
