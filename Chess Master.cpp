#include <iostream>
#include <ctype.h>
#include <graphics.h>
using namespace std;

struct node
{
    int turn;
    int x;
    int y;
    int x1;
    int y1;
    int p1;
    int p2;
    struct node *next;
};

int board[8][8],turn=0,count1=0,count2=0;
struct node *head=NULL;

int pawn(int x,int y,int x1,int y1);
int horse(int x,int y,int x1,int y1);
int rook(int x,int y,int x1,int y1);
int bishop(int x,int y,int x1,int y1);
int queen(int x,int y,int x1,int y1);
int king(int x,int y,int x1,int y1);
void draw_board();
void initialize_players();
void initialize_graphics();
void wrongStart();
int gameover();
void play();
void check();
void first_window();

void initialize_graphics()
{
    int gdriver = DETECT;
	int gmode;
	initgraph(&gdriver,&gmode,"e:\\borlandc\\bgi");
	initwindow(1050,650);
}

int horse(int x,int y,int x1,int y1)
{
	int a=0;
	if((y1==y+2 && x1==x+1)||(y1==y+2 && x1==x-1)||(y1==y+1 &&
x1==x+2)||(y1==y+1 && x1==x-2)||(y1==y-1 && x1==x+2)||(y1==y-1 &&
x1==x-2)||(y1==y-2 && x1==x+1)||(y1==y-2 && x1==x-1)){
		a = 1;
		}
	return a;
}

int king(int x,int y,int x1,int y1)
{
    int a = 0;
    if((y1==y+1 && x1==x)||(y1==y-1 && x1==x)||(y1==y+1 &&
        x1==x+1)||(y1==y+1 && x1==x-1)||(y1==y-1 && x1==x+1)||(y1==y-1 &&
        x1==x-1)||(y1==y && x1==x+1)||(y1==y && x1==x-1))
    {
        a = 1;
    }

    return a;
}

int bishop(int x,int y,int x1,int y1)
{
		int a=1,i;
		if(abs(x1-x)!=abs(y1-y))
		{
			a=0;
		}

		if((x<x1)&&(y<y1))
		{
			for(i=1;(i+x)<x1;i++)
			{
				 if(board[y+i][x+i]!=0)
				 a=0;
			}
		}

       else if((x>x1)&&(y>y1)){
	for(i=1;(x-i)>x1;i++){
	 if(board[y-i][x-i]!=0)
	    a=0;
	 }
	}
	else if((x>x1)&&(y<y1)){
	 for(i=1;(x-i)>x1;i++){
	  if(board[y+i][x-i]!=0)
	    a=0;
	 }
	}
	else if((x<x1)&&(y>y1)){
	for(i=1;(y-i)>y1;i++){
	 if(board[y-i][x+i]!=0)
	    a=0;
	 }
	}
	return a;
	}

int queen(int x,int y,int x1,int y1){
   if(x==x1||y==y1){
  //if queen moves in + direction
	 return rook(x,y,x1,y1);
   }
   else if(abs(x1-x)==abs(y-y1)){
  //if queen moves in diagnol
//direction
	 return bishop(x,y,x1,y1);
   }
   else
	 return 0;
}

int rook(int x,int y,int x1,int y1){
	int a=1;
	if(y1==y)
	{
		for(int i=x+1;i<x1;i++)
		{
			if(board[y1][i]!=0)
			{
				a = 0;
				break;
			}
		}
		for(int i=x-1;i>x1;i--)
		{
			if(board[y1][i]!=0)
			{
				a = 0;
				break;
			}
		}
	}
	else if(x1==x)
	{
		for(int i=y+1;i<y1;i++)
		{
			if(board[i][x1]!=0)
			{
				a = 0;
				break;
			}
		}
		for(int i=y-1;i>y1;i--)
		{
			if(board[i][x1]!=0)
			{
				a = 0;
				break;
			}
		}
	}
	else
	{
		a=0;
	}
	return a;
	}


int pawn(int x,int y,int x1,int y1){
	int a=0;
	if(turn==0){
		if(y==1){
		  if(y1==(y+2) && x1==x){
		if(board[y1][x1]==0&&board[y+1][x]==0){
				a = 1;
			   }
			}
			}
		 if(y1==y+1 && x1==x){
			if(board[y1][x1]==0){
				a = 1;
				}
			 }
	   else if(y1==(y+1) && (x1==(x+1)||x1==(x-1))){
		   if(board[y1][x1]<0){
			 a = 1;
			 }
		  }
		}
	  else if(turn==1){
		if(y==6){
		   if( y1==(y-2) && x1==x){
			if(board[y1][x1]==0&&board[y-1][x]==0){
				a = 1;
			   }
			}
		      }
		  if( y1==(y-1) && x1==x){
			if(board[y1][x1]==0){
				a = 1;
				}
			 }
	   else if(y1==(y-1) && (x1==(x-1)||x1==(x+1))){
		   if(board[y1][x1]>0){
			 a = 1;
			 }
		  }
	 }
   if(a==1)
   {
     if(turn==0)
     {
	 if(y1==7)
	 return 2;
     }
     else
     {
	if(y1==0)
	return 2;
     }
    }
 return a;
}


void initialize_players()
{
    for(int i=2;i<=5;i++)
		for(int j=0;j<=7;j++)
		 board[i][j] = 0;

		for(int j=0;j<=7;j++)
		{
		 board[0][j] = j+1;
		 board[1][j] = j+9;      //Pawns for player 1
		 board[7][j] = 0-(j+1);
		 board[6][j] = 0-(j+9);  //Pawns for player 2
		 }
}

void wrongStart()
{
	cout<<"\nWrong Input\n...";
	settextstyle(1,HORIZ_DIR,1);
	outtextxy(520,290,"Wrong Input, Try Again");
}


int gameover(){
	int i,j,a=0,b=0;

	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
		       if(board[i][j]==5)
		       b=1;
		       if(board[i][j]==-5)
		       a=1;
		}
	}
	if(b==0)
	{
	       setcolor(YELLOW);
	       outtextxy(70,520,"Game Over");
           setcolor(WHITE);
	       outtextxy(70,540,"Player 1 Loses");
	       getch();
	       return 1;
	}
	else if(a==0)
	{
		setcolor(GREEN);
		outtextxy(70,520,"Game Over");
		setcolor(WHITE);
		outtextxy(70,540,"Player 2 Loses");
		getch();
		return 1;
	}
return 0;
}


void play()
{
    struct node *temp=new node;
    temp->turn=turn;
    char ch;
    int x=-1,y=-1,x1=-1,y1=-1;
    for(;;)
    {
        draw_board();
        //cleartext();
        setcolor(YELLOW);
        settextstyle(1,HORIZ_DIR,3);
        outtextxy(520,400,">Player");
        if(turn!=0)
        {
            check();
            setcolor(GREEN);
            settextstyle(1,HORIZ_DIR,3);
            outtextxy(520,400,">Player 2");
            outtextxy(780,100, "Player 2:");
        }
        else
        {
            check();
            setcolor(YELLOW);
            settextstyle(1,HORIZ_DIR,3);
            outtextxy(520,400,">Player 1");
            outtextxy(520,100, "Player 1:");
        }
        ch=getch();
        if(gameover())
        {
        return;;
        }
        if(ch!='U')
        {
            if(x==-1)
            {
                ch=toupper(ch);
                if(ch>=65 && ch<=72)
                {

                    cout<<ch;
                    setcolor(WHITE);
                    settextstyle(1,HORIZ_DIR,1);
                    if(turn==0)
                    {
                    switch(ch)
                    {
                        case 65: outtextxy(600,140,"A");
                                    break;
                        case 66: outtextxy(600,140,"B");
                                break;
                        case 67: outtextxy(600,140,"C");
                                break;
                        case 68: outtextxy(600,140,"D");
                                break;
                        case 69: outtextxy(600,140,"E");
                                break;
                        case 70: outtextxy(600,140,"F");
                                break;
                        case 71: outtextxy(600,140,"G");
                                break;
                        case 72: outtextxy(600,140,"H");
                                break;
                    }//switch
                    }
                    else
                    {
                    switch(ch)
                    {
                        case 65: outtextxy(860,140,"A");
                                    break;
                        case 66: outtextxy(860,140,"B");
                                break;
                        case 67: outtextxy(860,140,"C");
                                break;
                        case 68: outtextxy(860,140,"D");
                                break;
                        case 69: outtextxy(860,140,"E");
                                break;
                        case 70: outtextxy(860,140,"F");
                                break;
                        case 71: outtextxy(860,140,"G");
                                break;
                        case 72: outtextxy(860,140,"H");
                                break;
                    }//switch
                    }
                    x=ch-65;
                    temp->x=x;
                }
            }//if(x==-1)

            else if(y==-1)
            {
                if(ch>='1' && ch<='8')
                {
                    cout<<ch;
                    settextstyle(1,HORIZ_DIR,1);
                    if(turn==0)
                    {
                    switch(ch)
                    {
                        case '1': outtextxy(625,140,"1");
                                break;
                        case '2': outtextxy(625,140,"2");
                                break;
                        case '3': outtextxy(625,140,"3");
                                break;
                        case '4': outtextxy(625,140,"4");
                                break;
                        case '5': outtextxy(625,140,"5");
                                break;
                        case '6': outtextxy(625,140,"6");
                                break;
                        case '7': outtextxy(625,140,"7");
                                break;
                        case '8': outtextxy(625,140,"8");
                                break;
                    }//switch
                    }
                    else
                    {
                    switch(ch)
                    {
                        case '1': outtextxy(885,140,"1");
                                break;
                        case '2': outtextxy(885,140,"2");
                                break;
                        case '3': outtextxy(885,140,"3");
                                break;
                        case '4': outtextxy(885,140,"4");
                                break;
                        case '5': outtextxy(885,140,"5");
                                break;
                        case '6': outtextxy(885,140,"6");
                                break;
                        case '7': outtextxy(885,140,"7");
                                break;
                        case '8': outtextxy(885,140,"8");
                                break;
                    }//switch
                    }
                    y=ch-'1';
                    temp->y=y;
                    if(board[y][x]==0){
                        wrongStart();
                        x=-1;
                        y=-1;
                        temp->x=x;
                        temp->y=y;
                    }
                    else
                    {
                        if(turn==0)
                        {
                            if(board[y][x]<0)//if Player 1 has selected a piece of Player 2
                            {
                                wrongStart();
                                x=-1;
                                y=-1;
                                temp->x=x;
                                temp->y=y;
                            }
                        }
                        else if(turn!=0)
                        {
                            if(board[y][x]>0)
                            {
                                wrongStart();
                                x=-1;
                                y=-1;
                                temp->x=x;
                                temp->x=y;
                            }
                        }
                    }
                }//if(ch>='1' && ch<='8');
            }//if(y==-1)

            else if(x1==-1)
            {
                ch=toupper(ch);
                if(ch>=65 && ch<=72)
                {
                    cout<<ch;
                    setcolor(WHITE);
                    settextstyle(1,HORIZ_DIR,1);
                    if(turn==0)
                    {
                    switch(ch)
                    {
                        case 65: outtextxy(700,140,"A");
                                break;
                        case 66: outtextxy(700,140,"B");
                                break;
                        case 67: outtextxy(700,140,"C");
                                break;
                        case 68: outtextxy(700,140,"D");
                                break;
                        case 69: outtextxy(700,140,"E");
                                break;
                        case 70: outtextxy(700,140,"F");
                                break;
                        case 71: outtextxy(700,140,"G");
                                break;
                        case 72: outtextxy(700,140,"H");
                                break;
                    }//switch
                    }
                    else
                    {
                    switch(ch)
                    {
                        case 65: outtextxy(955,140,"A");
                                break;
                        case 66: outtextxy(955,140,"B");
                                break;
                        case 67: outtextxy(955,140,"C");
                                break;
                        case 68: outtextxy(955,140,"D");
                                break;
                        case 69: outtextxy(955,140,"E");
                                break;
                        case 70: outtextxy(955,140,"F");
                                break;
                        case 71: outtextxy(955,140,"G");
                                break;
                        case 72: outtextxy(955,140,"H");
                                break;
                    }//switch
                    }
                    x1=ch-65;
                    temp->x1=x1;
				}
            }//if(x1==-1)
		else if(y1==-1)
		{
			if(ch>='1' && ch<='8')
			{
				cout<<ch;
				settextstyle(1,HORIZ_DIR,1);
                if(turn==0)
                {
                switch(ch)
                {
                    case '1': outtextxy(725,140,"1");
                                break;
                    case '2': outtextxy(725,140,"2");
                                break;
                    case '3': outtextxy(725,140,"3");
                                break;
                    case '4': outtextxy(725,140,"4");
                                break;
                    case '5': outtextxy(725,140,"5");
                                break;
                    case '6': outtextxy(725,140,"6");
                                break;
                    case '7': outtextxy(725,140,"7");
                                break;
                    case '8': outtextxy(725,140,"8");
                                break;
                }//switch
                }
                else
                {
                switch(ch)
                {
                    case '1': outtextxy(980,140,"1");
                                break;
                    case '2': outtextxy(980,140,"2");
                                break;
                    case '3': outtextxy(980,140,"3");
                                break;
                    case '4': outtextxy(980,140,"4");
                                break;
                    case '5': outtextxy(980,140,"5");
                                break;
                    case '6': outtextxy(980,140,"6");
                                break;
                    case '7': outtextxy(980,140,"7");
                                break;
                    case '8': outtextxy(980,140,"8");
                                break;
                }//switch
                }
				y1=ch-'1';
				temp->y1=y1;
			}
            int b=0,killed=0;
            setfillstyle(SOLID_FILL, BLACK);
            bar(520,290,840,365);

            temp->p1=board[y][x];
            temp->p2=board[y1][x1];
            //pawn
            if(abs(board[y][x])>=9 && abs(board[y][x])<=16){
                //if piece selscted has value greater than 8 and less than 17
				b = pawn(x,y,x1,y1);
            }//end pawn

            //horse
            else if(abs(board[y][x])==2 || abs(board[y][x])==7){
                //if piece selscted has value 2 and 7
				b = horse(x,y,x1,y1);
            }//end horse

            //queen
            else if(abs(board[y][x])==4){
                ////if piece selscted has value 4
				b = queen(x,y,x1,y1);
            }//end queen

            //king
            else if(abs(board[y][x])==5){
                //if piece selscted has value 5
				b = king(x,y,x1,y1);
            }//end king

            //rook
            else if(abs(board[y][x])==1 || abs(board[y][x])==8){
                //if piece selscted has value 1 and 8
				b = rook(x,y,x1,y1);
            }//end rook

            //bishop
            else if(abs(board[y][x])==3 || abs(board[y][x])==6){
                //if piece selscted has value 3 and 6
				b = bishop(x,y,x1,y1);
            }//end bishop

            if(b==2)
            {
                if(abs(board[y][x])>=9 && abs(board[y][x])<=16)
                {
                    char pp;
                    cout<<"\n\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\
                    \bwhich piece Q,R,H,B";
                    setcolor(WHITE);
                    settextstyle(1,HORIZ_DIR,1);
                    outtextxy(520,330,"which piece Q,R,H,B?");
                    pp=getch();
                    pp=tolower(pp);
                    if(turn==0)
                    {
                        if(pp=='r')
                        {
                            board[y1][x1]=1;
                            outtextxy(520,350,"R");
                        }
                        else if(pp=='h')
                            {
                                board[y1][x1]=2;
                                outtextxy(520,350,"H");
                            }
                            else if(pp=='b')
                                {
                                    board[y1][x1]=3;
                                    outtextxy(520,350,"B");
                                }
                                else if(pp=='q')
                                    {
                                        board[y1][x1]=4;
                                        outtextxy(520,350,"Q");
                                    }
                    }
                    else
                    {
                    if(pp=='r')
                        {
                            board[y1][x1]=-1;
                            outtextxy(520,350,"R");
                        }
                        else if(pp=='h')
                            {
                                board[y1][x1]=-2;
                                outtextxy(520,350,"H");
                            }
                            else if(pp=='b')
                                {
                                    board[y1][x1]=-3;
                                    outtextxy(520,350,"b");
                                }
                                else if(pp=='q')
                                    {
                                        board[y1][x1]=-4;
                                        outtextxy(520,350,"Q");
                                    }
                    }

                    board[y][x]=0;
                    killed =1;
                }

			      draw_board();
            }
            else if(b==1)
			{
				if(turn==0)
				{
					if(board[y1][x1]<0)
					{
						board[y1][x1]=board[y][x];
						board[y][x] = 0;
						killed=1;
					}
				}
				if(turn!=0)
				{
					if(board[y1][x1]>0)
					{
						board[y1][x1]=board[y][x];
						board[y][x] = 0;
						killed=1;
					}
				}
				if(board[y1][x1]==0)
				{
					int temp=board[y][x];
					board[y][x]=board[y1][x1];
					board[y1][x1]=temp;
					killed=1;
				}
				draw_board();
			}

			if(killed==1)
			{
			    if(head==NULL)
                {
                    temp->next=NULL;
                    head=temp;
                }
                else
                {
                    temp->next=head;
                    head=temp;
                }
                temp=NULL;
			}
			x=-1;
			y=-1;
			x1=-1;
			y1=-1;
			temp=NULL;
            if(killed==0){
                wrongStart();
                continue;
                }
			//cleartext();
			setcolor(YELLOW);
            settextstyle(1,HORIZ_DIR,3);
            outtextxy(520,400,">Player");
			if(turn==0)
            {
				check();
				turn=1;
				setcolor(GREEN);
                settextstyle(1,HORIZ_DIR,3);
                outtextxy(520,400,">Player 2");
                outtextxy(780,100, "Player 2:");
            }
			else
			{
				check();
				turn=0;
				setcolor(YELLOW);
                settextstyle(1,HORIZ_DIR,3);
                outtextxy(520,400,">Player 1");
                outtextxy(520,100, "Player 1:");
            }
        }//if(y1==-1)

        }//if(ch!=u)

        else if(ch=='U' || ch=='u')
        {
            if(head==NULL)
            {
                //outtextxy(,,"No Moves to undo");
            }
            else
            {
                board[head->y][head->x]=head->p1;
                board[head->y1][head->x1]=head->p2;
                head=head->next;
            }
        }

    }
}

void first_window()
{
    setfillstyle(SOLID_FILL, WHITE);
    bar(0,50,0,50);
    bar(50,50,100,100);
    bar(0,100,50,150);
    bar(100,0,150,50);
    bar(100,100,150,150);
    bar(1000,0,1050,50);
    setfillstyle(SOLID_FILL, GREEN);
    bar(200,100,800,300);
    settextstyle(1,HORIZ_DIR,5);
    setcolor(YELLOW);
    outtextxy(250,150, "Chess Using C++");
    setcolor(YELLOW);
    settextstyle(1,HORIZ_DIR,2);
    outtextxy(200,350,"Engineers:");
    settextstyle(1,HORIZ_DIR,1);
    setcolor(GREEN);
    outtextxy(200,380,"Abhimanyu Vashisht");
    outtextxy(200,410,"Rahul Sharma");
    outtextxy(200,440,"Sharad Dhadhich");
    outtextxy(200,470,"Vasu Arora");
    setcolor(YELLOW);
    outtextxy(200,500,"Jaypee Institute of Information Technology");
    setcolor(2);
    outtextxy(500,380,"15103001");
    outtextxy(500,410,"15103001");
    outtextxy(500,440,"15103001");
    outtextxy(500,470,"15103029");
    setfillstyle(SOLID_FILL, BLACK);
    setcolor(WHITE);
    for(int i=0; ;i=(i+1)%1000)
    {
        if(i<=500)
        {
            outtextxy(200,600,"_");
        }
        else
        {
            bar(200,600,220,620);
        }
        outtextxy(220,600,"Press Any Key To Continue");
        if(getch())
        {
            bar(0,0,1000,650);
            break;
        }
    }

}

void draw_board()
{
    int x_init=70;
    int y_init=100;
    setfillstyle(SOLID_FILL, WHITE);
    for(int i=x_init;i<=x_init+(50*8)-100;i+=100)
    {
        for(int j=y_init;j<=y_init+(50*8)-100;j+=100)
        {
            bar(i,j,i+50,j+50);
            bar(i+50,j+50,i+100,j+100);
        }
    }
    setfillstyle(SOLID_FILL, BLACK);
    for(int i=x_init;i<=x_init+(50*8)-100;i+=100)
    {
        for(int j=y_init;j<=y_init+(50*8)-100;j+=100)
        {
            bar(i+50,j,i+100,j+50);
            bar(i,j+50,i+50,j+100);
        }
    }

    setcolor(WHITE);
    settextstyle(1,HORIZ_DIR,3);
    outtextxy(520,100, "Player 1:");
    outtextxy(780,100, "Player 2:");

    setcolor(5);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(520,140, "From: ");
    outtextxy(650,140, "To:");
    outtextxy(780,140, "From: ");
    outtextxy(910,140, "To:");

    setcolor(WHITE);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(520,200,"Enter the initial and final positions");
    outtextxy(520,220,"of the active player");
    setcolor(5);
    outtextxy(520,260,"Or, Press U to undo");

    //Printing the keys
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {

            if(board[i][j]<0)
                setcolor(GREEN);
            else if(board[i][j]>0)
                setcolor(YELLOW);

            if(abs(board[i][j])>=9 && abs(board[i][j])<=16){
            outtextxy(x_init+20+(j*50),y_init+15+(i*50),"P");}

            else if(abs(board[i][j])==1 || abs(board[i][j])==8){
            outtextxy(x_init+20+(j*50),y_init+15+(i*50),"R");}

            else if(abs(board[i][j])==2 || abs(board[i][j])==7){
            outtextxy(x_init+20+(j*50),y_init+15+(i*50),"H");}

            else if(abs(board[i][j])==3 || abs(board[i][j])==6){
            outtextxy(x_init+20+(j*50),y_init+15+(i*50),"B");}

            else if(abs(board[i][j])==4){
            outtextxy(x_init+20+(j*50),y_init+15+(i*50),"Q");}

            else if(abs(board[i][j])==5){
            outtextxy(x_init+20+(j*50),y_init+15+(i*50),"K");}
        }//inner loop
    }//outer loop

     setcolor(5);

	  outtextxy(x_init+10,y_init-30,"A");
	  outtextxy(x_init+60,y_init-30,"B");
	  outtextxy(x_init+110,y_init-30,"C");
	  outtextxy(x_init+160,y_init-30,"D");
	  outtextxy(x_init+210,y_init-30,"E");
	  outtextxy(x_init+260,y_init-30,"F");
	  outtextxy(x_init+310,y_init-30,"G");
	  outtextxy(x_init+360,y_init-30,"H");

	  outtextxy(x_init-30,105,"1");
	  outtextxy(x_init-30,155,"2");
	  outtextxy(x_init-30,205,"3");
	  outtextxy(x_init-30,255,"4");
	  outtextxy(x_init-30,305,"5");
	  outtextxy(x_init-30,355,"6");
	  outtextxy(x_init-30,405,"7");
	  outtextxy(x_init-30,455,"8");
}

void check()
{
	  int t=0,i,j,x1,y1;
	   if(turn==0){
	     for(i=0;i<=7;i++)
	     {
		 for(j=0;j<=7;j++)
		 {
			if(board[i][j]==-5)
			{
				 y1=i; x1=j;
				  break;
			}
		  }
	     }
       for(j=0;j<=7;j++){
	for(i=0;i<=7;i++){
	 if (t==1){
	    setcolor(9);
	    settextstyle(1,HORIZ_DIR,3);
	    outtextxy(520,430, "CHECK!");
	    break;
	   }

	 if(board[j][i]>=9 && board[j][i]<=16)
		t = pawn(i,j,x1,y1);
	 else if(board[j][i]==2 || board[j][i]==7)
		t = horse(i,j,x1,y1);
	 else if(board[j][i]==4)
		t = queen(i,j,x1,y1);
	 else if(board[j][i]==1 || board[j][i]==8)
		t = rook(i,j,x1,y1);
	 else if(board[j][i]==3 || board[j][i]==6)
		t = bishop(i,j,x1,y1);

	}// for
       }//  for
     }//endif turn
    else {
     for(i=0;i<=7;i++){
      for(j=0;j<=7;j++){
       if(board[i][j]==5){
	 y1=i; x1=j;
	  break;
	      }
	  }
       }
       for(j=0;j<=7;j++){
	for(i=0;i<=7;i++){
	 if (t==1){
	    setcolor(9);
	    settextstyle(1,HORIZ_DIR,3);
	    outtextxy(520,430, "CHECK!");
	    break;
	   }

	 if(board[j][i]>=(-9) && board[j][i]<=(-16))
		t = pawn(i,j,x1,y1);
	 else if(board[j][i]==(-2) || board[j][i]==(-7))
		t = horse(i,j,x1,y1);
	 else if(board[j][i]==(-4))
		t = queen(i,j,x1,y1);
	 else if(board[j][i]==(-1) || board[j][i]==(-8))
		t = rook(i,j,x1,y1);
	 else if(board[j][i]==(-3) || board[j][i]==(-6))
		t = bishop(i,j,x1,y1);

	}// for
       }//  for
 }// end else
}

int main()
{
    initialize_graphics();

    first_window();

    initialize_players();

	draw_board();

	play();

	getch();
}

