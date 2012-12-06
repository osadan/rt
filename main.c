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
//#include <conio.h>
#include <./funcs.h>
#include <./funcs.c>
#define pf(x) {printf(x);}
#define pp(x,y){printf(x,y);}
#define pl(x){printf("%d\n",x);
//#include <stdint.h>
//#include <./definitions.h>
//#include <funcs.c>


enum Pawns {ROOK,KNIGHT,BISHOP,QUEEN,KING,PAWN,EMPTY};

typedef struct point{
	int i;
	int j;
} Point;

typedef struct piece
{
	char *color;
	enum Pawns t;
	char *output;
	short int status;
	//Point point;
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
Piece make_piece(char *color,int p, char *output);
int one_move(Board  *board,int sx,int sy,int dx,int dy);
int parse_string_move(char c);
int play_king(Board  *board,int sx,int sy,int dx,int dy);
int play_pawn(Board  *board,int sx,int sy,int dx,int dy);
int play_queen(Board  *board,int sx,int sy,int dx,int dy);
int play_rook(Board  *board,int sx,int sy,int dx,int dy);
int play_bishop(Board  *board,int sx,int sy,int dx,int dy);
int play_knight(Board  *board,int sx,int sy,int dx,int dy);
Board init_game ()
{
	Board board;
	board.status = 1;
	board.white = (char * )malloc(sizeof(char) * 64);
	board.black = (char * )malloc(sizeof(char) * 64);
	printf("Please insert the White player Name:");
	scanf("%s",board.white);
	printf("Please insert the Black player Name:");
	scanf("%s",board.black);
	return board;
}
void switch_piece(Piece *piece_src,Piece *piece_dest);
Piece make_piece(char *color,int p , char *output)
{
	Piece piece ;
	piece.color = color;
	piece.t = p;
	piece.output = output;
	piece.status = 1;
	return piece;
}

void init_board (Board *board)
{
	int y,x;
	char *output;
	for(x=0;x<8;x++)
		 for(y=1;y<6;y++)
		 {
			 if (y == 1){
					board->board[x][y] = make_piece("w",PAWN,"P");
					board->board[x][7-y] = make_piece("b",PAWN,"P");
			 }
			 else{
				 board->board[x][y] = (Piece){"empty",EMPTY,"_",1};
			 }
		 }
	for (x=0;x<5;x++) //x < 5
	{
				switch (x)
				//set up all other pieces
				{
					case 0:
						//ROOK
						output = "R";
						break;
					case 1:
						//KNIGHT
						output = "H";
						break;
					case 2:
						//BISHOP
						output = "B";
						break;
					case 3:
						//QUEEN
						output = "Q";
						break;
					case 4:
						//KING
						output = "K";
					break;
					default:
						break;
				}
				board->board[x][0] =  make_piece("w",x,output);
				board->board[x][7] =  make_piece("b",x,output);
				if (x != KING && x != QUEEN)
				{
					board->board[7-x][0] =  make_piece("w",x,output);
					board->board[7-x][7] =  make_piece("b",x,output);
				}
		}

}
void switch_piece(Piece *piece_src,Piece *piece_dest)
{
	Piece temp = (Piece){"empty",EMPTY,"_",1};
	memcpy(piece_dest,piece_src,sizeof(Piece));
	memcpy(piece_src,&temp,sizeof(Piece));

}
void draw_board (Board  *board)
{
	int x,y;
	pf("\n ");
	for (x = 0 ;x<8;x++)
	{
		printf("%d",x);
	}
	pf("\n");
	for(y = 0 ;y< 8;y++)
	{
		printf("%d",y);
		for (x = 0 ;x<8;x++)
		{
			if(board->board[x][y].status == 1){
				if (board->board[x][y].color == 'w'){
					//textcolor(GREEN);
				}
				else if (board->board[x][y].color == 'b'){
					//textcolor(BLUE);
				}
				else{
					//textcolor(BLACK);
				}
				printf("%s",board->board[x][y].output);
			}


		}
		printf("%d",y);
		printf("\n");

	}
	pf(" ");
	for (x = 0 ;x<8;x++)
	{
		printf("%d",x);
	}
	pf("\n");

}
int play_queen(Board  *board,int sx,int sy,int dx,int dy)
{
	int result_rook ,result_bishop;
	result_rook = play_rook(board,sx,sy,dx,dy);
	printf("r=%d,",result_rook);
	if (result_rook == 0){
		result_bishop = play_bishop(board,sx,sy,dx,dy);
		printf("b=%d",result_bishop);
		if(result_bishop == 1){
			return 1;
		}
		else{
			return 0;
		}
	}else{
		return 1;
	}
	//printf("r=%d,b=%d\n",result_rook,result_bishop);
	/*if (play_rook(board,sx,sy,dx,dy) == 1  ||
		play_bishop(board,sx,sy,dx,dy) == 1){
		return 1;
	}*/
	return 0;
}

int play_bishop(Board *board,int sx,int sy,int dx,int dy)
{
	//Piece temp = board->board[sx][sy];
	int result_x,result_y,x,y,i;//,flag = 0;
	result_x = (sx > dx) ? sx - dx : dx -sx;
	result_y = (sy > dy) ? sy -dy : dy -sy;
	printf("%d - %d = %d, %d - %d = %d",sx,dx,sx -dx,sy,dy,sy - dy);
	if (result_x == result_y){
		x = sx;
		y = sy;
		for(i = 0;i<(result_x - 1);i++ )
		{
			if(sx > dx){
				x--;
			}
			else
			{
				x++;
			}
			if(sy > dy){
				y--;
			}
			else{
				y++;
			}
			if(not_empty(board->board[x][y])){
				return 0;
			}
		}
		//board->board[dx][dy] = board->board[sx][sy];
		//board->board[sx][sy] = (Piece){"empty",EMPTY,"_",1};
		//switch_piece(&board->board[sx][sy],&board->board[dx][dy]);
		return 1;
	}
	return 0;
}
int play_knight(Board *board,int sx,int sy,int dx,int dy)
{
	//Piece temp = board->board[sx][sy];
	int result_x,result_y,i;//,flag = 0;
	int x,y;
	result_x = (sx > dx) ? sx - dx : dx -sx;
	result_y = (sy > dy) ? sy -dy : dy -sy;
	if ((result_x == 1 && result_y == 2) || (result_x == 2 && result_y == 1)){


		printf("%d - %d = %d, %d - %d = %d",sx,dx,sx -dx,sy,dy,sy - dy);
		//board->board[dx][dy] = board->board[sx][sy];
		//board->board[sx][sy] = (Piece){"empty",EMPTY,"_",1};
		//pf("\n");
		//switch_piece(&board->board[sx][sy],&board->board[dx][dy]);
		return 1;
	}
	return 0;
}
int play_pawn(Board  *board,int sx,int sy,int dx,int dy)
{
	//@todo whan pawn get to the end of the board switch to something
	Piece temp = board->board[sx][sy];
	int flag = 0;
	if (temp.color == "w" && sy == 1 && dy == 3){
		printf("%d",__LINE__);
		if(not_empty(board->board[dx][2])){
			return 0;
		}
		flag = 1;
	}
	else  if(temp.color == "b" && sy == 6 && dy == 4){
		printf("%d",__LINE__);
		if(not_empty(board->board[dx][5])){
			return 0;
		}
		flag = 1;
	}
	else if (temp.color == "w" && sx == dx && ( dy - sy  == 1) ){
		printf("%d",__LINE__);
		flag = 1 ;
	}
	else if (temp.color == "b" && sx == dx && (sy - dy == 1)){
		printf("%d",__LINE__);
		flag = 1;
	}
	else if (temp.color == "w" && (dx == sx +1 || dx == sx -1) && (dy - sy == 1) && not_empty(board->board[dx][dy])){
		printf("%d",__LINE__);
		flag = 1;
	}
	else if (temp.color == "b" && (dx == sx +1 || dx == sx -1) && (sy - dy == 1) && not_empty(board->board[dx][dy])){
		printf("%d",__LINE__);
		flag = 1;
	}

	if(flag == 1){
		//@todo write function to move player get two pointers and switch;
		//board->board[dx][dy] = board->board[sx][sy];
		//board->board[sx][sy] = (Piece){"empty",EMPTY,"_",1};
		return 1;
	}

	return 0;
}
int play_rook (Board  *board,int sx,int sy,int dx,int dy)
{
	int i,max,x,y;
	if((dx == sx) || (dy == sy) ){
		if (dx == sx){
			y = sy ;
			max = abs(sy - dy);
			for(i = 0 ;i < max - 1 ;i++)
			{
				if (sy > dy){
					y--;
				}else{
					y++;
				}
				if (not_empty(board->board[dx][y])){
					return 0;
				}
			}
		}
		else if (dy == sy){
			x = sx ;
			max = abs(sy - dy);
			for(i = 0 ;i < max - 1 ;i++)
			{
				if (sx > dx){
					x--;
				}else{
					x++;
				}
				if (not_empty(board->board[x][dy])){
					return 0;
				}
			}
		}
		//board->board[dx][dy] = board->board[sx][sy];
		//board->board[sx][sy] = (Piece){"empty",EMPTY,"_",1};
		//switch_piece(&board->board[sx][sy],&board->board[dx][dy]);
		return 1;
	}
	return 0;


}
int play_king(Board  *board,int sx,int sy,int dx,int dy)
{
	if (sx == dx){
		if(abs(sy -dy) != 1){
			pf("358");
			return 0;
		}
	}
	else if(sy == dy){
		if(abs(sx-dx) != 1){
			pf("364");
			return 0;
		}
	}
	else if	(abs(sx-dx) != 1 || abs(dy-sy) != 1){
		printf("%d != 1 || %d != 1,== %d;",abs(sx-dx),abs(dy-sy),(abs(sx-dx) != 1 || abs(dy-sy) != 1));
		pf(",368");
		return 0;
	}
	/*if(is_thret(board,dx,dy) ){

	}*/
	//switch_piece(&board->board[sx][sy],&board->board[dx][dy]);
	return 1;

}
int is_threat (Board *board,int dx,int dy,char *color)
{
	int i ,j,result ;
	for (i =0;i<8;i++){
		for(j=0;j<8;j++){
			if(board->board[i][j].color != color && board->board[i][j].color != "empty"){
				result = one_move(board,i,j,dx,dy);
				if (result == 1){
					return 1;
				}
			}
		}
	}
	return 0;
}
int one_move(Board  *board,int sx,int sy,int dx,int dy)
{
	int result;
	if(!not_empty(board->board[sx][sy])){
		return 0;
	}
	if((dx < 0 && dx > 7) || (dy < 0 && dy > 7)){
		return 0;
	}
	if(sx == dx && dy == sy){
		return 0;
	}
	printf("\n[%d,%d],[%d,%d] - ",sx,sy,dx,dy);
	printf("pawn type:%s;pawn color:%s\n",board->board[sx][sy].output,board->board[sx][sy].color);

	switch(board->board[sx][sy].t)
	{
		//ROOK,KNIGHT,BISHOP,QUEEN,KING,PAWN
		case PAWN:
			result = play_pawn(board,sx,sy,dx,dy);
			break;
		case ROOK:
			result = play_rook(board,sx,sy,dx,dy);
			break;
		case KNIGHT:
			result = play_knight(board,sx,sy,dx,dy);
			break;
		case BISHOP:
			result =  play_bishop(board,sx,sy,dx,dy);
			break;
		case QUEEN:
			result = 	play_queen(board,sx,sy,dx,dy);
			break;
		case KING:
			result =  play_king(board,sx,sy,dx,dy);
			break;
		default:
			break;
	}
	if(result == 1){
		switch_piece(&board->board[sx][sy],&board->board[dx][dy]);
		return 1;
	}else{
		return 0;
	}
}
int not_empty(Piece p)
{
	return p.t != EMPTY;
}
int parse_string_move(char c)
{
	if ( c > 96 && c < 123 ){
		return c - 96;
	}
	if(c > 64 && c < 91){
		return c -  64;
	}
	return 0;

}
int play_game()
{
	Board board ;
	init_board(&board);
	draw_board(&board);
	char *move = (char *)malloc(sizeof(64));
	int source_x,source_y,dest_x,dest_y,result;
	draw_board(&board);

do
	{
		pf("Please insert your move:\n") //@todo add the name of the player (maybe count the turns;)
		scanf("%s",move);
		//fgets(move,6,stdin);
		printf("%s\n",move);
		if(move[0] != 69){
			source_x = parse_string_move(move[0]);
			source_y = atoi(&move[1]);
			dest_x = parse_string_move(move[3]);
			dest_y = atoi(&move[4]);

			result = one_move(&board,source_x -1,source_y - 1,dest_x -1,dest_y - 1);
			//draw_board(&board);
		}
	}while(move[0] != 69 && result != -1);
	free(move);
	return 0;
}
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
	draw_board(&board);
	assert(is_threat(&board,3,3,"b") == 0);
	assert(is_threat(&board,3,3,"w") == 0);
}
int main ()
{
	pf("start\n");
	//test_is_threat();
	//test_game_start();
	//@todo switch king and rook
	//@todo take the code of the switch and wrap it with a function is_ok
	//@todo color the soldiers
	//play_game();
	//test_pawn();
	//test_knight();
	//test_bishop();
	//test_rook();
	//test_queen();
	test_game_start();
	//test_king();
	//char *b = "hello";
	//int result;
	//assert(strcmp(b,"hello") == 0);
	//result = strcmp(b,"bello");
	//printf("%d,",result);
	//assert((b == "h") == 1);
	pf("end game");

}
