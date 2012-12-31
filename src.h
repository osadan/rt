
/*
 * funcs1.h
 *
 *  Created on: Nov 30, 2012
 *      Author: ehud
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef SRC_H_
#define SRC_H_

//#define _DEBUG
#define _RELEASE
//#define _ZEROBASED

#define pf(x) {printf(x);}
#define pp(x,y){printf(x,y);}
#define pl(x){printf("%d\n",x);
enum Pawns {ROOK,KNIGHT,BISHOP,QUEEN,KING,PAWN,EMPTY};
enum Turn {WHITE,BLACK};

typedef struct piece
{
	char *color;
	enum Pawns t;
	char output;
	short int status;
	char first_move;
} Piece;

typedef struct board
{
	 Piece board [8][8];
	 Piece old_board [8][8];
	 char *white;
	 char *black;
	 int status;

}Board;

void init_board(Board *board);
Board init_game();
void draw_board(Board  *board);
int play_game();
Piece make_piece(char *color,int p, char output);
int one_move(Board  *board,int sx,int sy,int dx,int dy);
int parse_string_move(char c);
int play_king(Board  *board,int sx,int sy,int dx,int dy);
int play_pawn(Board  *board,int sx,int sy,int dx,int dy);
int play_queen(Board  *board,int sx,int sy,int dx,int dy);
int play_rook(Board  *board,int sx,int sy,int dx,int dy);
int play_bishop(Board  *board,int sx,int sy,int dx,int dy);
int play_knight(Board  *board,int sx,int sy,int dx,int dy);
int move_inner(Board  *board,int sx,int sy,int dx,int dy);
void switch_piece(Piece *piece_src,Piece *piece_dest);
int is_chess (Board *board,int dx,int dy,char *color);
int is_threat (Board *board,int dx,int dy,char *color);
int not_empty(Piece p);
char to_board_letters(int i);
#endif




