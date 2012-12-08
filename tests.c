/*
 * tests.c
 *
 *  Created on: Dec 7, 2012
 *      Author: ehud
 */
#include "tests.h"
int test_move(Board *board,int sx,int sy,int dx,int dy)
{

	int result;
	result = one_move(board,sx,sy,dx,dy);
	return result;


}
void test_rook()
{
	Board board;
	init_board(&board);
	draw_board(&board);
	board.board[3][3] = board.board[0][0];
	board.board[0][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,3,2) == 1);
	init_board(&board);
	board.board[3][3] = board.board[0][0];
	board.board[0][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,3,4) == 1);
	init_board(&board);
	board.board[3][3] = board.board[0][0];
	board.board[0][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,0,3) == 1);
	init_board(&board);
	board.board[3][3] = board.board[0][0];
	board.board[0][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,3,6) == 1);
	init_board(&board);
	board.board[3][3] = board.board[0][0];
	board.board[0][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,2,3) == 1);
	init_board(&board);
	board.board[3][3] = board.board[0][0];
	board.board[0][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,7,3) == 1);
	init_board(&board);
	board.board[3][3] = board.board[0][0];
	board.board[0][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,3,0) == 0);
	assert(test_move(&board,3,3,2,2) == 0);
	assert(test_move(&board,3,3,1,5) == 0);
	assert(test_move(&board,3,3,5,1) == 0);

}
void test_bishop()
{
	Board board;
	init_board(&board);
	draw_board(&board);
	board.board[4][3] = board.board[5][0];
	board.board[5][0] = (Piece){"empty",EMPTY,"_",1};
	assert(test_move(&board,4,3,0,5) == 0);
	assert(test_move(&board,4,3,1,4) == 0);
	assert(test_move(&board,4,3,6,5) == 1);
	init_board(&board);
	board.board[3][2] = board.board[5][0];
	board.board[5][0] = (Piece){"empty",EMPTY,"_",1};
	assert(test_move(&board,3,2,7,7) == 0);
	init_board(&board);
	board.board[4][3] = board.board[5][0];
	board.board[5][0] = (Piece){"empty",EMPTY,"_",1};
	assert(test_move(&board,4,3,7,6) == 1);
	draw_board(&board);
	//@todo test that the soldier you eat is from your enamy


}
void test_knight()
{
	Board board;
	init_board(&board);
	draw_board(&board);

	board.board[4][3] = board.board[1][0];
	board.board[1][0] = (Piece){"empty",EMPTY,"_",1};
	assert(test_move(&board,4,3,3,5) == 1);
	board.board[4][3] = board.board[3][5];
	assert(test_move(&board,4,3,5,6) == 0);

	//board.board[4][3] = board.board[1][0];
	assert(test_move(&board,4,3,3,1) == 1);

	board.board[4][3] = board.board[3][1];
	assert(test_move(&board,4,3,5,1) == 1);

	board.board[4][3] = board.board[5][1];
	assert(test_move(&board,4,3,6,2) == 1);

	board.board[4][3] = board.board[6][2];
	assert(test_move(&board,4,3,8,2) == 0);

	//board.board[4][3] = board.board[1][0];
	assert(test_move(&board,4,3,4,8) == 0);

	//board.board[4][3] = board.board[1][0];
	assert(test_move(&board,4,3,5,0) == 0);

	//board.board[4][3] = board.board[1][0];
	assert(test_move(&board,4,3,0,5) == 0);

	//board.board[4][3] = board.board[1][0];
	assert(test_move(&board,4,3,2,4) == 1);


	pf("\n");

}
void test_pawn()
{
	//@todo to check when pawn eats
	Board board;
	init_board(&board);
	draw_board(&board);
	assert(not_empty((Piece){.t = EMPTY})  == 0);
	assert(not_empty((Piece){.t = PAWN}) == 1);
	//pawn;
	assert(test_move(&board,0,1,0,3) == 1);
	init_board(&board);
	assert(test_move(&board,0,1,0,2) == 1);
	init_board(&board);
	assert(test_move(&board,0,6,0,4) == 1);
	init_board(&board);
	assert(test_move(&board,0,6,0,5) == 1);
	init_board(&board);
	assert(test_move(&board,0,6,0,3) == 0);
	init_board(&board);
	assert(test_move(&board,0,1,0,5) == 0);
	init_board(&board);
	assert(test_move(&board,0,1,1,1) == 0);
	init_board(&board);
	assert(test_move(&board,0,1,1,2) == 0);
	init_board(&board);
	assert(test_move(&board,0,6,1,6) == 0);
	init_board(&board);
	assert(test_move(&board,0,6,1,5) == 0);

}
void test_queen()
{
	Board board;
	init_board(&board);
	draw_board(&board);
	board.board[3][3] = board.board[3][0];
	board.board[3][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,3,6) == 1);
	init_board(&board);
	board.board[3][3] = board.board[3][0];
	board.board[3][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,0,6) == 1);
	init_board(&board);
	board.board[3][3] = board.board[3][0];
	board.board[3][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,7,3) == 1);
	init_board(&board);
	board.board[3][3] = board.board[3][0];
	board.board[3][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,6,6) == 1);
	init_board(&board);
	board.board[3][3] = board.board[3][0];
	board.board[3][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,3,2) == 1);
	init_board(&board);
	board.board[3][3] = board.board[3][0];
	board.board[3][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,2,4) == 1);
	init_board(&board);
	board.board[3][3] = board.board[3][0];
	board.board[3][0] = (Piece){"empty",EMPTY,"_",1};

	assert(test_move(&board,3,3,2,6) == 0);
	assert(test_move(&board,3,3,3,7) == 0);
	assert(test_move(&board,3,3,2,5) == 0);
	assert(test_move(&board,3,3,4,5) == 0);
	assert(test_move(&board,3,3,7,7) == 0);
}
void test_king()
{
	Board board;
	init_board(&board);
	//draw_board(&board);
		board.board[3][3] = board.board[4][0];
		board.board[4][0] = (Piece){"empty",EMPTY,"_",1};
		draw_board(&board);
		assert(test_move(&board,3,3,3,2) == 1);
		init_board(&board);
		board.board[3][3] = board.board[4][0];
		board.board[4][0] = (Piece){"empty",EMPTY,"_",1};

		assert(test_move(&board,3,3,2,3) == 1);
		init_board(&board);
		board.board[3][3] = board.board[4][0];
		board.board[4][0] = (Piece){"empty",EMPTY,"_",1};
		assert(test_move(&board,3,3,7,5) == 0);
		assert(test_move(&board,3,3,4,4) == 1);
		init_board(&board);
		board.board[3][3] = board.board[4][0];
		board.board[4][0] = (Piece){"empty",EMPTY,"_",1};

		assert(test_move(&board,3,3,2,2) == 1);
		init_board(&board);
		board.board[3][3] = board.board[4][0];
		board.board[4][0] = (Piece){"empty",EMPTY,"_",1};

		assert(test_move(&board,3,3,4,4) == 1);
		init_board(&board);
		board.board[3][3] = board.board[4][0];
		board.board[4][0] = (Piece){"empty",EMPTY,"_",1};

		assert(test_move(&board,3,3,4,3) == 1);
		init_board(&board);
		board.board[3][3] = board.board[4][0];
		board.board[4][0] = (Piece){"empty",EMPTY,"_",1};

		assert(test_move(&board,3,3,3,5) == 0);
		assert(test_move(&board,3,3,2,5) == 0);
		assert(test_move(&board,3,3,5,2) == 0);
		assert(test_move(&board,3,3,1,3) == 0);
		assert(test_move(&board,3,3,5,3) == 0);
		assert(test_move(&board,3,3,1,1) == 0);
		assert(test_move(&board,3,3,2,1) == 0);

}
void test_game_start()
{
	Board board;
	init_board(&board);
	assert(one_move(&board,4,1,4,3) ==1);
	assert(one_move(&board,4,6,4,4) ==1);
	assert(one_move(&board,5,0,2,3) ==1);
	assert(one_move(&board,5,7,2,4) ==1);
	assert(one_move(&board,1,0,2,2) ==1);
	assert(one_move(&board,1,7,2,5) ==1);
	assert(one_move(&board,3,0,4,1) ==1);
	assert(one_move(&board,3,7,4,6) ==1);
	assert(one_move(&board,6,0,7,2) ==1);
	assert(one_move(&board,6,7,5,5) ==1);
	assert(one_move(&board,5,5,5,4) ==0);
	draw_board(&board);

}
void test_is_threat()
{
	Board board;
	init_board(&board);
	switch_piece(&board.board[3][6],&board.board[3][3]);
	draw_board(&board);
	assert(is_threat(&board,3,3,"b") == 0);
	draw_board(&board);
	switch_piece(&board.board[3][3],&board.board[3][6]);
	switch_piece(&board.board[3][1],&board.board[3][6]);
	assert(is_threat(&board,3,3,"w") == 0);
}


