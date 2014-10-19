#include "stdafx.h"
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Header.h"
#include <Windows.h>
#pragma warning(disable: 4703)
typedef enum{redd,blackk}colour;
#define BOARD_HEIGHT 21
#define BOARD_WIDTH 30
 
void play();
void menu_selection(char option);
void menu();
void generate_board(char board[BOARD_HEIGHT][BOARD_WIDTH]);
void draw_board();
void change_icon(int x, int y,char q);

using namespace std;
char playboard[BOARD_HEIGHT][BOARD_WIDTH];
bool gameplay = true;	


class Checker {
private:
	
	char icon;
	int posx,posy;
	bool kingvar;//whether or not king
	bool spex;//whether or not has special
	Checker* next;
	
	int dirx;
	int diry;
	
public:
	void printz(){printf("\nx=%d\ny=%d\nk?%d\ns?%d",posx,posy,kingvar,spex);}
	Checker()
	{
	
	};
	Checker(int x,int y)
	{
		posx = x;
		posy = y;
		kingvar = false;
		spex = true;
	};
	~Checker()
	{
		delete [] next;
	}
	void seticon(char x)//indicates color and kingship
	{
		icon = x;
	};
	char geticon()
	{
		return icon;
	}
	
	
	void kingme()
	{
		//kings this piece
		//seticontouppercase this might need to be moved to the specific color, 
		kingvar=true;
		
	};
	virtual void destroy()
	{
		//go through linked list til this checker is the next
		//set temp to point to this checker
		//set next as next->next
		//delete this checker
	}
	
	
		void setposx(int i)	{posx = i;}
	
	void setposy(int i)	{posy = i;}
	
	int getposx(){return posx;}
	
	int getposy(){return posy;}
	Checker* getnext(){return next;}
	void setnext(Checker* a){next = a;}
	void setdirx(int i)	{dirx = i;}
	
	void setdiry(int i)	{diry = i;}
	
	int getdirx(){return dirx;}
	
	int getdiry(){return diry;}
	int hasspex(){return spex;}
	void usedspex(){spex =0;}
	bool isking(){return kingvar;}
	
};
Checker* blackhead;
Checker* redhead;

Checker* contains(int x,int y,colour type)//black is 1, red is 2
{
	Checker* node;
	
	//deciding which head to point to
	if (type==blackk)
	{
		node = blackhead; 
	}
	if (type==redd)
	{
		node = redhead;
	}
	while (node!=NULL)
	{
		if (x==node->getposx() && y==node->getposy())
		{
			return node;}
		else
		{
			node=node->getnext();
		}
		
	}
	
	return NULL;
	
}
bool move(Checker* piece,int tomovex,int tomovey,colour me, colour other)//if return 0, failed move, if 1, then successful
	{
		


		bool flag=false;
		bool kingvar = piece->isking();
		int posx = piece->getposx();
		int posy = piece->getposy();
		int dirx = piece->getdirx();
		int diry = piece->getdiry();
		
		//set up a way to input the location tobemoved
		int dx = tomovex-posx;
		int dy = tomovey-posy;
		
		if (kingvar == false)//not kinged
		{

			if (contains(tomovex,tomovey,me)==NULL&&contains(tomovex,tomovey,other)==NULL )	 //check if there is a checker in next location()
			{
				if((dx==1||dx==-1)&&(dy==diry))				//check if moved diagonally once//this takes advantage that the direction is only up down, i'd change it if we needed to do more than 2 colors
					{
						flag=true;
						printf("true");
					}
				else if((dx==2||dx==-2)&&(dy==2*diry))				//check if jump
				{
				
					if (contains(posx+((dx)/2),posy+((dy)/2),me)==NULL&&contains(posx+((dx)/2),posy+((dy)/2),other)!=NULL)//if positioncheck((posx-dx),(posy-y))
							{
								flag=true;
								contains(posx+(dx/2),posy+(dy/2),other)->destroy();
							}
				}
			}
		}
		else 
		{
			if (contains(tomovex,tomovey,me)==NULL&&contains(tomovex,tomovey,other)==NULL )	 //check if there is a checker in next location()
			{
				if((dx==1||dx==-1)&&(dy==1||dy==-1))				//check if moved diagonally once//this takes advantage that the direction is only up down, i'd change it if we needed to do more than 2 colors
					{
						flag=true;
						printf("true");
					}
				else if(	((dx==2||dx==-2) &&(dy==2||dy==-2))		//check if jump diagonally
						||	((dx==0) && (dy==2||dy==-2))			//check if vertical jump
						||	((dx==2)||(dx==-2 && dy==0)))				
				{
				
					if (contains(posx+((dx)/2),posy+((dy)/2),me)==NULL&&contains(posx+((dx)/2),posy+((dy)/2),other)!=NULL)//if positioncheck((posx-dx),(posy-y))
							{
								flag=true;
								contains(posx+(dx/2),posy+(dy/2),other)->destroy();
							}
				}
			}
		
		

		}
		if(flag==true)//if move succesful, make current pos blank and tomove pos has new icon
		{
			if (piece->getdiry()==1)
				{
					if(tomovey==8)
						{
							piece->kingme();
							piece->seticon('B');
						}
				}
			if (piece->getdiry()==-1)
				{
					if(tomovey==0)
						{
							piece->kingme();
							piece->seticon('R');
						}
				}
		
			change_icon(posx,posy,' ');
			change_icon(tomovex,tomovey,piece->geticon());
			piece->setposx(tomovex);
			piece->setposy(tomovey);

			return true;
			//set icon at posx,posy to blank
			//set icon at tomovex,y to icon
			
		}
		//if move was bad
		cout << "\nInvalid move.";
		return false;
	};
class Black:public Checker{
private:
	Black* next;
public:
	Black(int x, int y):Checker(x,y){seticon('b');setdirx(0);setdiry(1);};
	~Black(){ delete next;};

	void special(){};
void deleteBlackList(Black **head)
{
	Black *deleteBlack = *head;
	while(deleteBlack)
	{
		Black *next = deleteBlack->next;
		delete deleteBlack;

		deleteBlack = next;
	}

	*head = NULL;
}
void destroy()
{

	//
	////check for win!!
	//
	//put tie after bomb destroy


	Checker* temp;
	temp = blackhead;
	
	srand((unsigned)time(0));
	int ww = 1 + (rand() %100);
	if (ww >= 0 && ww <= 50)
	{
		cout<<"The black piece blew up!!";
			
			if (contains(getposx()+1,getposy()+1,redd)!=NULL)
			{
				contains(getposx()+1,getposy()+1,redd)->destroy();
			}			
						
			if(contains(getposx()+1,getposy()-1,redd)!=NULL)
			{
				contains(getposx()+1,getposy()-1,redd)->destroy();
			}
			if(contains(getposx()-1,getposy()-1,redd)!=NULL)
			{
				contains(getposx()-1,getposy()-1,redd)->destroy();
			}
			if(contains(getposx()-1,getposy()+1,redd)!=NULL)
			{
				contains(getposx()-1,getposy()+1,redd)->destroy();
			}
			//make sure to account for a tie!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}	
	
		
	//deleting this node from the list
	
	if(temp->getposx() == getposx() && temp->getposy() ==getposy())
		{
			if (getnext() !=NULL)
				blackhead=getnext();
			else
				blackhead=NULL;
		}
	else
		{
			while (temp->getnext()->getposx() != getposx() && temp->getnext()->getposy() != getposy())
			{temp = temp->getnext();}//point to object before this
			temp->setnext(getnext());
		}
	
	
	change_icon(getposx(),getposy(),' ');

	if (blackhead==NULL)
	{
		if (redhead==NULL)
		{
			printf("THE GAME RESULTED IN A TIE.");
			gameplay = false;
		}

	}

}
	
};
void populateb()
{
	blackhead = new Black(1,0);
	Checker* temp;
	temp = blackhead;
	for(int i = 3;i<8;i+=2)
		{
			Checker* b;
			temp->setnext(b = new Black(i,0));
			temp = temp->getnext();
			
		}
	
	for(int i = 2;i<=7;i+=2)
	{
		temp->setnext(new Black(i,1));
		temp = temp->getnext();
	}
	temp->setnext(NULL);
}
class Red:public Checker{
private:
	Red* next;
public:
	Red(int x, int y):Checker(x,y){seticon('r');setdirx(0);setdiry(-1);};
	~Red(){ delete next;};
void deleteRedList(Red **head)
{
	Red *deleteRed = *head;
	while(deleteRed)
	{
		Red *next = deleteRed->next;
		delete deleteRed;

		deleteRed = next;
	}

	*head = NULL;
}
void destroy()
{
	
	Checker* temp;
	temp = redhead;
	if (this->hasspex())
	{
		printf("The red piece used its shield, press enter.");//not shown on the screen because of the screen clear
		this->usedspex();
		return;
	}
	
	//deleting this node from the list
	if(temp->getposx() == getposx() && temp->getposy() ==getposy())
	{redhead=getnext();}
	else
	{
		while (temp->getnext()->getposx() != getposx() && temp->getnext()->getposy() != getposy())
			{temp = temp->getnext();}//point to object before this
		temp->setnext(this->getnext());
	}
	change_icon(getposx(),getposy(),' ');
}
	
};
void populater()
{
	redhead = new Red(1,8);
	Checker* temp;
	temp = redhead;
	for(int i = 3;i<8;i+=2)
		{
			Checker* b;
			temp->setnext(b = new Red(i,8));
			temp = temp->getnext();
			
		}
	
	for(int i = 2;i<=6;i+=2)
	{
		temp->setnext(new Red(i,7));
		temp = temp->getnext();
	}
	temp->setnext(NULL);
}

	
void turn(colour type)
{
	bool flag;
	int x;
	int y;
	int tomx;
	int tomy;
	colour other;
	Checker* piece;
	if (type==blackk)
	{
		cout <<"Black Turn";
		other = redd;
	}
	if (type==redd)
	{
		cout <<"Red Turn";
		other = blackk;
	}
	//getting the piece
	do
	{
	cout <<"\nX position of piece to move?: ";
	cin >> x;
		while(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input for X position of piece to move.\n";
			cout<< "Enter an X position of piece to move: ";
			cin >> x;
		}
		
	fflush(stdin);
	
	cout <<"Y position of piece to move?: ";
	cin >> y;
		while(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input for Y position of piece to move.\n";
			cout<< "Enter an Y position of piece to move: ";
			cin >> y;
		}
	fflush(stdin);
	
	//check its own list
	piece = contains(x,y,type);
	
	if(piece==NULL)
	{
		cout << "No piece exists there, please pick another location.";
	}
	} while (piece==NULL);
	do{
	cout << "Where would you like to move?\n";
	cout << "X position to move?: ";
	cin >> tomx;
	while(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input for X position.\n";
			cout<< "Enter an X position: ";
			cin >> tomx;
		}
	fflush(stdin);
	
	cout << "Y position to move?: ";
	cin >> tomy;
	while(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input for Y position.";
			cout<< "Enter a Y position of piece to move: ";
			cin >> tomy;
		}
	fflush(stdin);
	
	
	//check its own list and other list
	
	flag = move(piece,tomx,tomy,type,other);
	
	if (flag==false)//if the move was not allowable
	{
		int choice1;
		
		cout << "\nEnter 1 for a new piece, anything else for a new position to move: ";
		cin >> choice1;
		fflush(stdin);
		if (choice1==1)
		{do//choosing another piece
			{
				cout << "X position of piece to move?: ";
				cin >> x;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Invalid input for X position of piece to move.";
					cout<< "Enter an X position of piece to move: ";
					cin >> x;
				}
				fflush(stdin);
	
				cout << "Y position of piece to move?: ";
				cin >> y;
				while(cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Invalid input for Y position of piece to move.";
					cout<< "Enter an Y position of piece to move: ";
					cin >> y;
				}
				fflush(stdin);
	
		//check its own list
		piece = contains(x,y,type);
	
		if(piece==NULL)
		{
			cout << "no piece exists there, please pick another location";
			fflush(stdin);
		}
			} while (piece==NULL);
		}


	}
			
	}while (flag==false);//flag means turn complete
	
	fflush(stdin);
	system("cls");
	draw_board();

	if (redhead == NULL)
	{
		if (blackhead == NULL)
		{
			printf("TIE");
			
		}

		else
			{printf("BLACK WINS");}
		gameplay = false;
	}	
		else if (blackhead==NULL)
			{
				printf("RED WINS");
			}
	
}
void main() //main, menu, creates visual display of board
{
	
	
		
		
		cout << "\n\nWelcome to MAZE\n";
	
		char input_buffer;
	//menu and input loop
		do
		{
			menu();
	
			input_buffer = tolower(getchar()); 
			dump_key_buffer();
			menu_selection(input_buffer);
		} 
		while (input_buffer != 'q');
}
	
    void menu()
	{
		cout <<"\nMenu Options\n";
	cout<<"------------------------------------------------------\n";
	cout <<"p: Play Checkers!\n";
	cout <<"q: Quit\n";
	cout << "\n\nPlease enter a choice ---> ";
	}
	void menu_selection(char option)
	{
		switch(option)
		{
		case 'p':
			play();
			
			break;
		case 'q':
			// main loop will take care of this.
			break;
		default:
			cout << "\nError: Invalid Input.  Please try again..."; 
			break;
		}
	}
void generate_board()
{
	int x, y;
	char cboard[BOARD_HEIGHT][BOARD_WIDTH] = 	 
	{{'_','_', '_', '0', '_', '_', '1', '_', '_', '2', '_', '_', '3', '_', '_', '4', '_', '_', '5', '_', '_', '6', '_', '_', '7', '_', '_', '8', '_'},
	{'_','_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'}, 
	{'0','|', '|', ' ', '|', '|', 'b', '|', '|', ' ', '|','|', 'b', '|', '|', ' ', '|', '|', 'b','|', '|', ' ', '|', '|', 'b', '|', '|', ' ', '|'}, 
	{'|','|', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '|'},
	{'1','|', '|', ' ', '|', '|', ' ', '|', '|', 'b', '|','|', ' ', '|', '|', 'b', '|', '|', ' ','|', '|', 'b', '|', '|', ' ', '|', '|', ' ', '|'},
	{'|','|', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '|'},
	{'2','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|','|', ' ', '|', '|', ' ', '|', '|', ' ','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|'},
	{'|','|', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '|'},
	{'3','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|','|', ' ', '|', '|', ' ', '|', '|', ' ','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|'},
	{'|','|', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '|'},
	{'4','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|','|', ' ', '|', '|', ' ', '|', '|', ' ','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|'},
	{'|','|', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '|'},
	{'5','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|','|', ' ', '|', '|', ' ', '|', '|', ' ','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|'},
	{'|','|', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '|'},
	{'6','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|','|', ' ', '|', '|', ' ', '|', '|', ' ','|', '|', ' ', '|', '|', ' ', '|', '|', ' ', '|'},
	{'|','|', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '|'},
	{'7','|', '|', ' ', '|', '|', ' ', '|', '|', 'r', '|','|', ' ', '|', '|', 'r', '|', '|', ' ','|', '|', 'r', '|', '|', ' ', '|', '|', ' ', '|'},
	{'|','|', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', '|'},
	{'8','|', '|', ' ', '|', '|', 'r', '|', '|', ' ', '|','|', 'r', '|', '|', ' ', '|', '|', 'r','|', '|', ' ', '|', '|', 'r', '|', '|', ' ', '|'},
	{'|','|', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '|'}};
	
	for(y = 0; y < BOARD_HEIGHT; y++) 
		for (x = 0; x < BOARD_WIDTH; x++)
			playboard[y][x] = cboard[y][x];
}
void draw_board()
{
	int y, x;
	for (y = 0; y < BOARD_HEIGHT; y++) 
		for (x = 0; x < BOARD_WIDTH; x++)
			print_char(x, y, playboard[y][x]);
}
void play()
{
	gameplay = true;
	populateb();//populate the pieces
	populater();
	

	generate_board();
	console_activate();
	system("cls");//clears the screen
	draw_board();
	
	srand((unsigned)time(0));
	int ww = 1 + (rand() %100);
	if (ww >= 0 && ww <= 50)
	{
		turn(blackk);
	}
		
	do{
	turn(redd);
	if (gameplay==true)
		turn(blackk);
	} while(gameplay==true);
	
	
}

void change_icon(int x, int y, char q)
{
	playboard[2*y+2][3*x+3] = q;
	draw_board();
}
