/*
 * src.c
 *
 *  Created on: Dec 7, 2012
 *      Author: ehud
 */
#include <ctype.h>
#include "src.h"


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

Piece make_piece(char *color,int p , char output)
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
	char output;
	for(x=0;x<8;x++)
		 for(y=1;y<6;y++)
		 {
			 if (y == 1){
					board->board[x][y] = make_piece("w",PAWN,(char)'P');
					board->board[x][7-y] = make_piece("b",PAWN,(char)'P');
			 }
			 else{
				 board->board[x][y] = (Piece){"empty",EMPTY,'_',1};
			 }
		 }
	for (x=0;x<5;x++) //x < 5
	{
				switch (x)
				//set up all other pieces
				{
					case 0:
						//ROOK
						output = 'R';
						break;
					case 1:
						//KNIGHT
						output = 'H';
						break;
					case 2:
						//BISHOP
						output = 'B';
						break;
					case 3:
						//QUEEN
						output = 'Q';
						break;
					case 4:
						//KING
						output = 'K';
					break;
					default:
						break;
				}
				board->board[x][0] =  make_piece("w",x,(char)output);
				board->board[x][7] =  make_piece("b",x,(char)output);
				if (x != KING && x != QUEEN)
				{
					board->board[7-x][0] =  make_piece("w",x,(char)output);
					board->board[7-x][7] =  make_piece("b",x,(char)output);
				}
		}

}

void switch_piece(Piece *piece_src,Piece *piece_dest)
{
	Piece temp = (Piece){"empty",EMPTY,'_',1};
	memcpy(piece_dest,piece_src,sizeof(Piece));
	memcpy(piece_src,&temp,sizeof(Piece));

}

void draw_board (Board  *board)
{
	int x,y;
	char output;
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
				output = board->board[x][y].output;
				//printf("'%d','%d','%s',\n",x,y,board->board[x][y].color);
				if (strcmp(board->board[x][y].color, "w") == 0){

				}
				else if (strcmp(board->board[x][y].color, "b") == 0){
					output = tolower(output);
				//	printf(",,%c,,",c);
				}
				else{
					//textcolor(BLACK);
				}
				printf("%s",&output);
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
	int result_x,result_y;//,flag = 0;
	//int x,y,i;
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
	if ((strcmp(temp.color , "w") == 0) && sy == 1 && dy == 3 && (sx == dx)){
		#ifdef _DEBUG
			printf("%d",__LINE__);
		#endif
		if(not_empty(board->board[dx][2]) || not_empty(board->board[dx][3])){
			return 0;
		}
		flag = 1;
	}
	else  if((strcmp(temp.color,"b") == 0) && sy == 6 && dy == 4 && (sx == dx)){
		#ifdef _DEBUG
			printf("%d",__LINE__);
		#endif
		if(not_empty(board->board[dx][5]) || not_empty(board->board[dx][4])){
			return 0;
		}
		flag = 1;
	}
	else if ((strcmp(temp.color,"w") == 0) && sx == dx && ( dy - sy  == 1) ){
		#ifdef _DEBUG
			printf("%d",__LINE__);
		#endif
		flag = 1 ;
	}
	else if ((strcmp(temp.color , "b") == 0) && sx == dx && (sy - dy == 1)){
		#ifdef _DEBUG
			printf("%d",__LINE__);
		#endif
		flag = 1;
	}
	else if ((strcmp(temp.color , "w") == 0) && (dx == sx +1 || dx == sx -1) && (dy - sy == 1) && not_empty(board->board[dx][dy])){
		#ifdef _DEBUG
			printf("%d",__LINE__);
		#endif
		flag = 1;
	}
	else if ((strcmp(temp.color , "b") == 0) && (dx == sx +1 || dx == sx -1) && (sy - dy == 1) && not_empty(board->board[dx][dy])){
		#ifdef _DEBUG
			printf("%d",__LINE__);
		#endif
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
	if(is_threat(board,dx,dy,board->board[sx][sy].color) ){
		pf("chess\n");
		return 0;
	}
	//switch_piece(&board->board[sx][sy],&board->board[dx][dy]);
	return 1;

}

int is_threat (Board *board,int dx,int dy,char *color)
{
	int i ,j,result ;
	for (i =0;i<8;i++){
		for(j=0;j<8;j++){
			if((strcmp(board->board[i][j].color,color) != 0) && (strcmp(board->board[i][j].color ,"empty") != 0)){
				//printf("%s != %s\n",board->board[i][j].color,color);
				//printf("check piece %s ->%s [%d][%d]\n",board->board[i][j].output,board->board[i][j].color,i,j);
				result = move_inner(board,i,j,dx,dy);
				if (result == 1){
					return result;
				}
			}
		}
	}
	return 0;
}

int move_inner(Board  *board,int sx,int sy,int dx,int dy)
{
	if(!not_empty(board->board[sx][sy])){
			return 0;
	}
	if((dx < 0 && dx > 7) || (dy < 0 && dy > 7)){
		return 0;
	}
	if(sx == dx && dy == sy){
		return 0;
	}
	#ifdef _DEBUG
		printf("[%d],[%d]->[%d],[%d] - ",sx,sy,dx,dy);
		printf("pawn type:%c;pawn color:%s\n",board->board[sx][sy].output,board->board[sx][sy].color);
	#endif
	switch(board->board[sx][sy].t)
	{
		//ROOK,KNIGHT,BISHOP,QUEEN,KING,PAWN
		case PAWN:
			return play_pawn(board,sx,sy,dx,dy);
		case ROOK:
			return play_rook(board,sx,sy,dx,dy);
		case KNIGHT:
			return play_knight(board,sx,sy,dx,dy);
		case BISHOP:
			return play_bishop(board,sx,sy,dx,dy);
		case QUEEN:
			return play_queen(board,sx,sy,dx,dy);
		case KING:
			return play_king(board,sx,sy,dx,dy);
		default:
			return 0;
	}
}

int one_move(Board  *board,int sx,int sy,int dx,int dy)
{
	int result;
	result = move_inner(board,sx,sy,dx,dy);
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
	board.white = (char *)malloc(64);
	board.black = (char *)malloc(64);
	char *move = (char *)malloc(sizeof(64));
	int source_x,source_y,dest_x,dest_y,result,turn;
#ifdef _RELEASE
	pf("Hello White Please Enter Your Name:");
	scanf("%s",board.white);
	pf("Hello Black Please Enter Your Name:");
	scanf("%s",board.black);
#else
	board.white = "Ohad_White";
	board.black = "Ohad_Black";
#endif
	init_board(&board);
	draw_board(&board);
	turn = 0;
do
	{
		printf("%s, ",(turn == 0 ? board.white : board.black));
		pf("Please insert your move:\n"); //@todo (maybe count the turns;)
		scanf("%s",move);
		//fgets(move,6,stdin);
		printf("%s\n",move);
		if(move[0] != 69){
			source_x = parse_string_move(move[0]);
			source_y = atoi(&move[1]);
			dest_x = parse_string_move(move[3]);
			dest_y = atoi(&move[4]);
			result = one_move(&board,source_x -1,source_y - 1,dest_x -1,dest_y - 1);
			turn = turn == 0 ? 1 : 0;
			draw_board(&board);
		}
	}while(move[0] != 69 && result != -1 && 0);
	free(move);
	return 0;
}


