///Library
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
/**/
///Define
#define Xmax 16   ///len_x=14
#define Ymax 40  /// len_y=38

#define cover 219
#define MINE 15
#define FLAG 20
#define ques 63

#define v 179       //vertical
#define h 196       //horizontal
#define ur 192      //up right
#define ul 217      //up left
#define dr 218      //down right
#define dl 191      //down left
#define lru 193     //left right up
#define lrd 194     //left right down
#define udr 195     //up down right
#define udl 180     //up down left
#define udlr 197    //up down left right

#define tv 186       //vertical
#define th 205       //horizontal
#define tur 200      //up right
#define tul 188      //up left
#define tdr 201      //down right
#define tdl 187      //down left
#define tlru 202     //left right up
#define tlrd 203     //left right down
#define tudr 204     //up down right
#define tudl 185     //up down left
#define tudlr 206    //up down left right

#define vur 212      //up right
#define vul 190      //up left
#define vdr 213      //down right
#define vdl 184      //down left
#define vlru 207     //left right up
#define vlrd 209     //left right down
#define vudr 198     //up down right
#define vudl 181     //up down left
#define vudlr 216    //up down left right

#define hur 211      //up right
#define hul 189      //up left
#define hdr 214      //down right
#define hdl 183      //down left
#define hlru 208     //left right up
#define hlrd 210     //left right down
#define hudr 199     //up down right
#define hudl 182     //up down left
#define hudlr 215    //up down left right

/**/
///Global variable
char face=1,BGroundCol=15,DefCharCol=0;
/***
state is for the different phases of the game and how
the command_processor() give an output
(state=0 -> Main menu screen                )
(state=1 -> screen before mine allocation   )
(state=2 -> screen after mine allocation    )
(state=3 -> pause screen                    )
(state=4 -> difficulty screen               )
(state=5 -> custom difficulty               )
(state=6 -> score difficulty                )
(state=7 -> score card                      )
(state=13-> Exit the while loop             )
***/
int t_o,placed_flag,state;
int pos_x=0,pos_y=0,len_x,len_y,command=0,num_mine;
/***
t_o = the initial time by time(NULL) when the game starts
placed_flag = no of flags placed
pos_x & pos_y -> position of cursor on every possible screen
len_x & len_y -> length of the box
command = value gained from getch() on every possible screen
***/
unsigned char Name[11];
unsigned char element[Xmax][Ymax],flag[Xmax][Ymax],mine[Xmax][Ymax];
/*****************
element holds the character representation that is to be shown on the screen().
mine holds weather the tile holds a mine or how many mines surround the tile.
flag holds how the player has marked the tile (Mine marked(20) || Unmarked(219) || ?Marked(63) || opened(0)).
*****************/
/**/
///Structure
typedef struct last_board last_board;
struct last_board{
    int board_x,board_y,total_mine_number;
};

typedef struct saved_file saved_file;
struct saved_file{
    int game_state,board_flag_placed,time,board_x,board_y,total_mine_number;
    unsigned char board_element[Xmax][Ymax],board_mine[Xmax][Ymax],board_flag[Xmax][Ymax],player_name[11];
};
typedef struct profile pro;
struct profile{
    int Time;
    int serial;
    char player_name[11];
    char fin_datetime[25];
    struct profile *next;
};
/**/
///Function Declaration
int loading(int g);
int watch(int i);
int boxprint(void);
int game(void);     ///screen function
int command_processor(void);
int random_num(int min,int max);
int mine_allocator(void);
int pos(int x,int y);       ///for mine_allocator
int reveal(int r,int x,int y);
int flag_planter(int ch);
int checker(void);
int cprint(unsigned char ch);
int load_save(int ls,int type);
int DEF(void);
int pause(void);    ///screen function
int difficulty(void); ///screen function
int custom(void);       ///screen function
int score(void);
int card(char ch);
int timedate(char *dt); ///fill the dt string with time
pro* proload(pro* start, char o);
pro* proinsert(pro* start, pro* newE, char o);
void prosave(pro* start, char o);

///*///////////////COLORS///////////////////////////{
void SetColor(int ForgC);
void SetColorAndBackground(int ForgC, int BackC);
void ClearConsoleToColors(int ForgC, int BackC);
///catalog
///0>Black      15>white        D=15-L
///1>D Blue      9>L Blue       D=L-8
///2>D Green    10>L Green
///3>D Cyan     11>L Cyan
///4>D Red      12>L Red
///5>D Purple   13>L Purple
///6>D Yellow   14>L Yellow
///8>D Gray      7>L Gray

///*///////////////COLORS///////////////////////////}

/**/
///All function
int main(){
    state=0;
    ///reset***
    load_save(0,0);
    SetColorAndBackground(DefCharCol,BGroundCol);
    pos_x=0;
    ///***
    while(1){
        {///Main Menu print
        ///upper part
        system("CLS");
        int i,j;
        printf("%c%c%c%c%c%c%c",tdr,th,th,th,th,th,vdl);
        j=11-8;
        for(i=0;i<j;i++)
            printf(" ");
        printf("%c%c%c%c%c",hdr,h,h,h,hdl);
        for(i=0;i<j;i++)
            printf(" ");
        printf("%c%c%c%c%c%c%c\n",vdr,th,th,th,th,th,tdl);
        printf("%c%c%c%03d%c",tv,'t',175,0,vur);
        for(i=0;i<j;i++)
            printf("%c",th);
        printf("%c %c %c",tul,face,tur);
        for(i=0;i<j;i++)
            printf("%c",th);
        printf("%c%03d%c%c%c\n",vul,0,174,MINE,tv);
        printf("%c",tudr);
        for(i=0;i<6;i++)
            printf("%c",th);
        printf("MINESWEEPER");
        for(i=0;i<6;i++)
            printf("%c",th);
        printf("%c\n",tudl);
        printf("%c%c%c",tv,dr,h);
        for(i=0;i<10;i++)
            printf("%c%c",lrd,h);
        printf("%c%c\n",dl,tv);

        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,219,v,'5',v,219,v,219,v,219,v,15,v,219,v,'8',v,219,v,219,v,tv);
        ///condition

        if(pos_x==0)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tdr,h,tdl,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,udlr,h,udl,tv);

        if(pos_x==0)        printf("%c%c%c%c1%c NEW GAME      %c%c%c%c\n",tv,v,1,v,v,v,'6',v,tv);
        else                printf("%c%c%c%c1%c New Game      %c%c%c%c\n",tv,v,1,v,v,v,'6',v,tv);

        if(pos_x==0)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tur,h,tul,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else if(pos_x==1)   printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tdr,h,tdl,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);

        if(pos_x==1)        printf("%c%c%c%c2%c LOAD GAME     %c%c%c%c\n",tv,v,219,v,v,v,219,v,tv);
        else                printf("%c%c%c%c2%c Load Game     %c%c%c%c\n",tv,v,219,v,v,v,219,v,tv);

        if(pos_x==1)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tur,h,tul,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else if(pos_x==2)   printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tdr,h,tdl,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);

        if(pos_x==2)        printf("%c%c%c%c3%c HI-SCORE      %c%c%c%c\n",tv,v,20,v,v,v,219,v,tv);
        else                printf("%c%c%c%c3%c Hi-Score      %c%c%c%c\n",tv,v,20,v,v,v,219,v,tv);

        if(pos_x==2)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tur,h,tul,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else if(pos_x==3)   printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tdr,h,tdl,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);

        if(pos_x==3)        printf("%c%c%c%c4%c DIFFICULTY    %c%c%c%c\n",tv,v,219,v,v,v,'X',v,tv);
        else                printf("%c%c%c%c4%c Difficulty    %c%c%c%c\n",tv,v,219,v,v,v,'x',v,tv);

        if(pos_x==3)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tur,h,tul,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else if(pos_x==4)   printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tdr,h,tdl,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);

        if(pos_x==4)        printf("%c%c%c%c5%c EXIT          %c%c%c%c\n",tv,v,2,v,v,v,219,v,tv);
        else                printf("%c%c%c%c5%c Exit          %c%c%c%c\n",tv,v,2,v,v,v,219,v,tv);

        if(pos_x==4)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tur,h,tul,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,udlr,h,udl,tv);

        ///last layers
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,14,v,219,v,'7',v,219,v,219,v,219,v,20,v,219,v,3,v,219,v,tv);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,ur,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,ul,tv);
        printf("%c",tur);for(i=0;i<23;i++)printf("%c",th);printf("%c",tul);
        }
        fflush(stdin);
        command=getch();
        if(command==224)command=getch();
        command_processor();
        if(state==13){
            state=0;
            printf("\nThanks for playing.");
            SetColor(12);printf("%c%c%c\n\n\n",3,3,3);SetColor(0);
            getch();
            break;
        }
    }
}
///***********************************************************************************
int game(void){
    face=1;
    pos_x=0;pos_y=0;
    if(state==0){
        state=1;
        ///load last played game option
        load_save(0,0);
        if(len_x<5 || len_y<8 || len_x>Xmax-2 || len_y>Ymax-2 || num_mine<5) DEF();
        ///reset***
        pos_x=0;pos_y=0;
        face=1;
        ///
        int i,j;
        for(i=0;i<Xmax;i++)
            for(j=0;j<Ymax;j++){
                element[i][j]=cover;
                mine[i][j]=' ';
                flag[i][j]=cover;
            }
        placed_flag=0;
        t_o=0;
        ///reset finish***
    }
    fflush(stdin);
    while(1){
        boxprint();
        command=getch();
        if(command==224)command=getch();
        command_processor();
        if(state==13){
            state=0;
            break;
        }
        if(checker())
            break;
    }
}
///*************************************************************************************
int boxprint(void){
    int i,j;
    system("cls");
    ///time & mine table
    printf("%c%c%c%c%c%c%c",tdr,th,th,th,th,th,vdl);
    j=len_y-8;
    for(i=0;i<j;i++)
        printf(" ");
    printf("%c%c%c%c%c",hdr,h,h,h,hdl);
    for(i=0;i<j;i++)
        printf(" ");
    printf("%c%c%c%c%c%c%c\n",vdr,th,th,th,th,th,tdl);
    printf("%c%c%c%03d%c",tv,'t',175,watch(1),vur);
    for(i=0;i<j;i++)
        printf("%c",th);
    printf("%c %c %c",tul,face,tur);
    for(i=0;i<j;i++)
        printf("%c",th);
    printf("%c%03d%c%c%c\n",vul,(num_mine-placed_flag),174,MINE,tv);
    ///outer box top
    printf("%c",tudr);
    if(state==0 && face==3){
        for(j=0;j<len_y-3;j++)
            printf("%c",th);
        printf("VICTORY");
        for(j=0;j<len_y-3;j++)
            printf("%c",th);
    }
    else if(state==0 && face==2){
        for(j=0;j<len_y-4;j++)
            printf("%c",th);
        printf("GAME~OVER");
        for(j=0;j<len_y-4;j++)
            printf("%c",th);
    }
    else{
        for(j=0;j<2*len_y+1;j++)
        printf("%c",th);
    }
    printf("%c\n",tudl);
    ///box
    for(i=0;i<len_x;i++){
        ///top layer
        if(i==0){
            ///roof top
            printf("%c",tv);
            if(pos_x==0 && pos_y==0)
                printf("%c",tdr);
            else
                printf("%c",dr);
            for(j=0;j<len_y;j++){
                if(pos_x==i && pos_y==j)
                    printf("%c%c",h,tdl);              ///th or h
                else if(pos_x==i && pos_y==j+1)
                    printf("%c%c",h,tdr);
                else
                    printf("%c%c",h,lrd);
            }
            j--;
            if((pos_x==i ) && (pos_y==j ) )
                printf("%c\n",tv);
            else
                printf("\b%c%c\n",dl,tv);
            ///top wall
            printf("%c",tv);
            if(pos_x==0 && pos_y==0)
                printf("%c",v);                                    ///tv or v
            else
                printf("%c",v);
            for(j=0;j<len_y;j++){
                if(pos_x==i && (pos_y==j|| pos_y==j+1)){
                    cprint(element[i+1][j+1]);
                    printf("%c",v);                              ///tv or v
                }
                else{
                    cprint(element[i+1][j+1]);
                    printf("%c",v);
                }
            }
            printf("%c\n",tv);
            ///top layer floor
            printf("%c",tv);
            if(pos_x==0 && pos_y==0)
                printf("%c",tur);
            else if(pos_x==i+1 && pos_y==0)
                printf("%c",tdr);
            else
                printf("%c",udr);
            for(j=0;j<len_y;j++){
                if(pos_x==i && pos_y==j)
                    printf("%c%c",h,tul);                  ///th or h
                else if(pos_x==i && pos_y==j+1)
                    printf("%c%c",h,tur);
                else if(pos_x==i+1 && pos_y==j)
                    printf("%c%c",h,tdl);                 ///th or h
                else if(pos_x==i+1 && pos_y==j+1)
                    printf("%c%c",h,tdr);
                else
                    printf("%c%c",h,udlr);
            }
            j--;
            if((pos_x==i || pos_x==i+1) && pos_y==j)
                printf("%c\n",tv);
            else
                printf("\b%c%c\n",udl,tv);
        }
        ///ground layer
        else if(i==len_x-1){
            ///wall
            printf("%c",tv);
            if(pos_x==i && pos_y==0)
                printf("%c",v);                                    ///tv or v
            else
                printf("%c",v);
            for(j=0;j<len_y;j++){
                if(pos_x==i && (pos_y==j|| pos_y==j+1)){
                    cprint(element[i+1][j+1]);
                    printf("%c",v);                             ///tv o v
                  }
                else{
                    cprint(element[i+1][j+1]);
                    printf("%c",v);
                }
            }
            printf("%c\n",tv);
            ///floor
            printf("%c",tv);
            if(pos_x==len_x-1 && pos_y==0)
                printf("%c",tur);
            else
                printf("%c",ur);
            for(j=0;j<len_y;j++){
                if(pos_x==i && pos_y==j)
                    printf("%c%c",h,tul);                   ///th or h
                else if(pos_x==i && pos_y==j+1)
                    printf("%c%c",h,tur);
                else
                    printf("%c%c",h,lru);
            }
            j--;
            if((pos_x==i || pos_x==i+1) && pos_y==j )
                printf("%c\n",tv);
            else
                printf("\b%c%c\n",ul,tv);
        }
        ///common layer
        else{
            ///wall
            printf("%c",tv);
            if(pos_x==i && pos_y==0)
                printf("%c",v);                 ///tv or v
            else
                printf("%c",v);
            for(j=0;j<len_y;j++){
                if(pos_x==i && (pos_y==j|| pos_y==j+1)){
                    cprint(element[i+1][j+1]);
                    printf("%c",v);                             ///tv o v
                  }
                else{
                    cprint(element[i+1][j+1]);
                    printf("%c",v);
                }
            }
            printf("%c\n",tv);
            ///floor
            printf("%c",tv);
            if(pos_x==i && pos_y==0)
                printf("%c",tur);
            else if(pos_x==i+1 && pos_y==0)
                printf("%c",tdr);
            else
                printf("%c",udr);
            for(j=0;j<len_y;j++){
                if(pos_x==i && pos_y==j)
                    printf("%c%c",h,tul);               ///th or h
                else if(pos_x==i+1 && pos_y==j)
                    printf("%c%c",h,tdl);              ///th or h
                else if(pos_x==i && pos_y==j+1)
                    printf("%c%c",h,tur);
                else if(pos_x==i+1 && pos_y==j+1)
                    printf("%c%c",h,tdr);
                else
                    printf("%c%c",h,udlr);
            }
            j--;
            if((pos_x==i || pos_x==i+1) && pos_y==j)
                printf("%c\n",tv);
            else
                printf("\b%c%c\n",udl,tv);
        }
    }
    ///outer box bottom
    printf("%c",tur);
    for(j=0;j<2*len_y+1;j++)
        printf("%c",th);
    printf("%c\n",tul);
    ///
}
///*************************************************************************************
int command_processor(void){
    if(state==0){
        if(command==80 || command==50 || command==115 || command==83){
            pos_x++;
            if(pos_x==5)
                pos_x=0;
        }
        else if(command==72 || command==56 || command==119 || command==87){
            pos_x--;
            if(pos_x==-1)
                pos_x=4;
        }
        else if(command==13 || command==122 || command==90){
            if(pos_x==0){
                printf("\nPlease Enter Your Name:");
                scanf("%s",Name);
                loading(1);
                game();
            }
            else if(pos_x==1){
                printf("\nPlease Enter Your Name:");
                scanf("%s",Name);
                if(load_save(0,1))
                    return 0;
                load_save(1,0);
                loading(1);
                game();
            }
            else if(pos_x==2){
                score();
            }
            else if(pos_x==3){
                difficulty();
            }
            else if(pos_x==4)
                state=13;
        }
    }
    else if(state==1 || state==2){
        if(command==72 || command==56 || command==119 || command==87){
            pos_x--;
            if(pos_x==-1)
                pos_x=len_x-1;
        }
        else if(command==80 || command==50 || command==115 || command==83){
            pos_x++;
            if(pos_x==len_x)
                pos_x=0;
        }
        else if(command==77 || command==54 || command==100 || command==68){
            pos_y++;
            if(pos_y==len_y)
                pos_y=0;
        }
        else if(command==75 || command==52 || command==97 || command==65){
            pos_y--;
            if(pos_y==-1)
                pos_y=len_y-1;
        }
        else if(command==13 || command==122 || command==90){
            if(state==1){
                state=2;
                mine_allocator();
                reveal(0,pos_x,pos_y);
            }
            else if(state==2){
                reveal(0,pos_x,pos_y);
            }
        }
        else if(command==32 || command==120 || command==88){
            flag_planter(FLAG);
        }
        else if(command==47 || command==63 || command==99 || command==67){
            flag_planter(ques);
        }
        else if(command==27){
            pause();
        }
    }
    else if(state==3){
        if(command==80 || command==50 || command==115 || command==83){
            pos_x++;
            if(pos_x==3)
                pos_x=0;
        }
        else if(command==72 || command==56 || command==119 || command==87){
            pos_x--;
            if(pos_x==-1)
                pos_x=2;
        }
        else if(command==27){
            if(t_o==0)
                state=1;
            else{
                state=2;
                t_o=time(NULL)-t_o;
            }
        }
        else if(command==13 || command==122 || command==90){
            if(pos_x==0){
                if(t_o==0)
                    state=1;
                else{
                    state=2;
                    t_o=time(NULL)-t_o;
                }
            }
            else if(pos_x==1){
                load_save(1,1);
                loading(2);
                state=13;
            }
            else if(pos_x==2){
                state=13;
            }
        }
    }
    else if(state==4){
        if(command==80 || command==50 || command==115 || command==83){
            pos_x++;
            if(pos_x==5)
                pos_x=0;
        }
        else if(command==72 || command==56 || command==119 || command==87){
            pos_x--;
            if(pos_x==-1)
                pos_x=4;
        }
        else if(command==27 || command==120 || command==88){
            state=0;
        }
        else if(command==13 || command==122 || command==90){
            if(pos_x==0){
                len_x=9;len_y=9;num_mine=10;
                load_save(1,0);
                loading(2);
                state=0;
            }
            else if(pos_x==1){
                len_x=14;len_y=14;num_mine=30;
                load_save(1,0);
                loading(2);
                state=0;
            }
            else if(pos_x==2){
                len_x=14;len_y=30;num_mine=60;
                load_save(1,0);
                loading(2);
                state=0;
            }
            else if(pos_x==3){
                custom();
                //state=0;
            }
            else if(pos_x==4){
                state=0;
            }
        }
    }
    else if(state==6){
        if(command==80 || command==50 || command==115 || command==83){
            pos_x++;
            if(pos_x==4)
                pos_x=0;
        }
        else if(command==72 || command==56 || command==119 || command==87){
            pos_x--;
            if(pos_x==-1)
                pos_x=3;
        }
        else if(command==27 || command==120 || command==88){
            state=0;
        }
        else if(command==13 || command==122 || command==90){
            if(pos_x==0){
                state=7;
                card('e');
            }
            else if(pos_x==1){
                state=7;
                card('m');
            }
            else if(pos_x==2){
                state=7;
                card('h');
            }
            else if(pos_x==3){
                state=0;
            }
        }
    }
    ///
}
///*************************************************************************************
int random_num(int min,int max){
    static unsigned p=0;
    unsigned ret;
    srand(time(NULL)+p);
    ret=(rand()%(max-min+1))+min;
    p++;
    if(p%2==0)p++;
    else p+=8;
    //printf("%d ",p);
    if(p<0)p=0;
    //getch();
    return ret;
}
///*************************************************************************************
int mine_allocator(void){
    state=2;
    int f[Xmax*Ymax]={0};
    int i,j,m,p;
    int a=len_x*len_y-1;
    ///9 block marking around the cursor
    for(i=pos_x-1;i<=pos_x+1;i++){
        for(j=pos_y-1;j<=pos_y+1;j++)
            f[pos(i,j)]=2;
    }
    ///mine allocation for f[]
    printf("Please Wait");
    for(m=0;m!=num_mine;){
        p=random_num(0,a);
        if(f[p]==2)
            continue;
        else if(f[p]==0){
            f[p]=1;
            m++;
            printf(".");
        }
        else if(f[p]==1){
            f[p]=0;
            m--;
            printf("\b");
        }
    }
    ///mine and value allocation for mine[][]
    for(i=0;i<len_x;i++){
        for(j=0;j<len_y;j++){
            if(f[pos(i,j)]==1){
                mine[i+1][j+1]=MINE;
                int a,b;
                for(a=i;a<=i+2;a++){
                    for(b=j;b<=j+2;b++){
                        if(a==i+1 && b==j+1 || mine[a][b]==MINE)
                            continue;
                        else if(mine[a][b]>48 && mine[a][b]<57)
                            mine[a][b]++;
                        else
                            mine[a][b]=49;
                    }
                }
            }
        }
    }
    watch(0);
}
///************************************************************************************
int reveal(int r,int x,int y){           /// int r is here for specifying weather reveal
    int i,j;                             /// is called for the first time(0) or recursively(1)
    static char f[Xmax][Ymax];           /// or called to reveal the mines for victory(3) or defeat(2)
    ///
    if(r==2){
        for(i=0;i<len_x;i++){
            for(j=0;j<len_y;j++){
                if(element[i+1][j+1]==MINE || element[i+1][j+1]==FLAG && mine[i+1][j+1]!=MINE)
                    element[i+1][j+1]='X';
                else if(mine[i+1][j+1]==MINE && element[i+1][j+1]!=FLAG)
                    element[i+1][j+1]=mine[i+1][j+1];
            }
        }
        return 0;
    }
    else if(r==3){
        for(i=0;i<len_x;i++){
            for(j=0;j<len_y;j++){
                if(flag[i+1][j+1]!=0)
                    element[i+1][j+1]=FLAG;
            }
        }
        return 0;
    }
    else if(r==0){
        for(i=0;i<Xmax;i++){
            for(j=0;j<Ymax;j++)
                f[i][j]=0;
        }
    }
    ///recursion stopper condition
    if(f[x+1][y+1]==1 || x>len_x || x<0 || y>len_y || y<0 || flag[x+1][y+1]==FLAG)
        return 0;
    ///revealing for regular call
    element[x+1][y+1]=mine[x+1][y+1];
    flag[x+1][y+1]=0;
    f[x+1][y+1]=1;
    if(mine[x+1][y+1]==' '){
        reveal(1,x+1,y+1);
        reveal(1,x-1,y-1);
        reveal(1,x+1,y-1);
        reveal(1,x-1,y+1);
        reveal(1,x,y+1);
        reveal(1,x+1,y);
        reveal(1,x-1,y);
        reveal(1,x,y-1);
    }
    else if(mine[x+1][y+1]!=' '){
        //printf("fuck\n");
        int c=0;                    ///adjacent marked mine counter
        for(i=x;i<=x+2;i++){
            for(j=y;j<=y+2;j++){
                if(i==x+1 && j==y+1)
                    continue;
                if(flag[i][j]==FLAG)
                    c++;
            }
        }
        if(c==mine[x+1][y+1]-48 && r==0){
            c=getch();
            if(c==13 || c==122 || c==90){
                reveal(1,x+1,y+1);
                reveal(1,x-1,y-1);
                reveal(1,x+1,y-1);
                reveal(1,x-1,y+1);
                reveal(1,x,y+1);
                reveal(1,x+1,y);
                reveal(1,x-1,y);
                reveal(1,x,y-1);
            }
            else
                return 0;
        }
    }
    else
        return 0;
}
///************************************************************************************
int loading(int g){
    ///system("cls");
    int t_O=0,t_D=0,i;
    char ch[20];
    t_O=time(NULL);
    t_D=time(NULL)-t_O;
    if(g==1)     printf("\nLOADING ");
    else if(g==2)printf("\nSAVING ");
    for(i=0;i<20;i++){
        ch[i]=95;
        printf("%c",ch[i]);
    }
    while(t_D<7){                   ///7 sec please
        fflush(stdin);
        ///
        for(i=0;i<20;i++)
            printf("\b");
        if(t_D==0){
            for(i=0;i<20;i++)
                ch[i]=95;
        }
        else if(t_D==1){
            for(i=0;i<2;i++)
                ch[i]=220;
        }
        else if(t_D==2){
            for(i=0;i<2;i++)
                ch[i]=219;
            for(;i<7;i++)
                ch[i]=220;
        }
        else if(t_D==3){
            for(i=0;i<7;i++)
                ch[i]=219;
            for(;i<=11;i++)
                ch[i]=220;
        }
        else if(t_D==4){
            for(i=0;i<11;i++)
                ch[i]=219;
            for(;i<=16;i++)
                ch[i]=220;
        }
        else if(t_D==5){
            for(i=0;i<16;i++)
                ch[i]=219;
            for(;i<20;i++)
                ch[i]=220;
        }
        else if(t_D==6){
            for(i=0;i<20;i++)
                ch[i]=219;
        }
        for(i=0;i<20;i++)
            printf("%c",ch[i]);
        ///
        while(1){
            fflush(stdin);
            int t_1=t_D;
            int t_2=time(NULL)-t_O;
            if(t_2==t_1+1)
                break;
        }
        t_D=time(NULL)-t_O;
    }
    if(g==1)     printf("\nREADY!!!\nPress any key to continue.\n");
    else if(g==2)printf("\nDONE!!!\nPress any key to continue.\n");
    getch();

}
///*************************************************************************************
int watch(int i){
    ///mine allocation done and time starts
    if(i==0)
        t_o=time(NULL);
    ///time display for box
    else if(i==1){
        int t;
        if(t_o==0)
            return 0;
        else
            t=time(NULL)-t_o;
        if(t>=1000)
            return 999;
        return t;
    }
}
///************************************************************************************
int checker(void){
    int f=0,i,j;
    ///mine uncover check
    for(i=0;i<len_x;i++){
        for(j=0;j<len_y;j++){
            if(element[i+1][j+1]==MINE){
                reveal(2,pos_x,pos_y);
                state=0;
                face=2;
                boxprint();
                pos_x=0;pos_y=0;
                getch();
                loading(2);
                return 1;
            }
        }
    }
    ///counting no of uncovered tile
    for(i=0;i<len_x;i++){
        for(j=0;j<len_y;j++){
            if(flag[i+1][j+1]!=0)
                f++;
        }
    }
    ///win check
    if(f==num_mine){
        printf("\a\a\a");
        reveal(3,pos_x,pos_y);
        state=0;
        pos_x=0;pos_y=0;
        placed_flag=num_mine;
        face=3;
        boxprint();
        load_save(1,2);
        getch();
        loading(2);
        return 1;
    }
    else
        return 0;
}
///**************************************************************************************
int flag_planter(int ch){
    if(flag[pos_x+1][pos_y+1]==0)
        return 0;
    if(ch==FLAG){
        if(flag[pos_x+1][pos_y+1]==FLAG){
            flag[pos_x+1][pos_y+1]=cover;
            element[pos_x+1][pos_y+1]=flag[pos_x+1][pos_y+1];
            placed_flag--;
        }
        else if(flag[pos_x+1][pos_y+1]!=FLAG){
            flag[pos_x+1][pos_y+1]=FLAG;
            element[pos_x+1][pos_y+1]=flag[pos_x+1][pos_y+1];
            placed_flag++;
        }
    }
    else if(ch==ques){
        if(flag[pos_x+1][pos_y+1]==ques){
            flag[pos_x+1][pos_y+1]=cover;
            element[pos_x+1][pos_y+1]=flag[pos_x+1][pos_y+1];
        }
        else if(flag[pos_x+1][pos_y+1]!=ques){
            if(flag[pos_x+1][pos_y+1]==FLAG)
                placed_flag--;
            flag[pos_x+1][pos_y+1]=ques;
            element[pos_x+1][pos_y+1]=flag[pos_x+1][pos_y+1];
        }
    }
}
///*************************************************************************************
int cprint(unsigned char ch){
    if(ch>48 && ch<58 || ch==FLAG || ch==MINE || ch=='X'){
        ///fixing char color
        if(ch==FLAG && state!=0)        SetColorAndBackground(12,7);
        else if(ch==FLAG && state==0)   SetColorAndBackground(2,7);
        else if(ch==MINE)   SetColor(4);
        else if(ch=='X')    SetColor(12);
        else if(ch=='1')    SetColor(9);
        else if(ch=='2')    SetColor(2);
        else if(ch=='3')    SetColor(4);
        else if(ch=='4')    SetColor(6);
        else if(ch=='5')    SetColor(3);
        else if(ch=='6')    SetColor(5);
        else if(ch=='7')    SetColor(1);
        else if(ch=='8')    SetColor(13);
        ///printing character
        printf("%c",ch);
        ///returning to default
        SetColorAndBackground(DefCharCol,BGroundCol);
    }
    else
        printf("%c",ch);
}
///*************************************************************************************
int load_save(int ls,int type){
    /**************************
    (ls==0) -> load {
        (type==0) -> load board options.
        (type==1) -> load game.
    }
    (ls==1) -> save{
        (type==0) -> save board options.
        (type==1) -> save game.
        (type==2) -> save score.
    }
    **************************/
    FILE *fp;
    int i,j;
    if(ls==0){
        if(type==0){
            if((fp=fopen("Board.txt","rb"))==NULL){
                //printf("Error!!!\nBoard.txt not found");
                //getch();
                //difficulty();
                DEF();
                return 0;
            }
            last_board a;
            if(fread(&a,sizeof a,1,fp)!=1){
                printf("Error");
                exit(1);
            }
            fclose(fp);
            len_x=a.board_x;len_y=a.board_y;num_mine=a.total_mine_number;
            return 0;
        }
        else if(type==1){
             if((fp=fopen("Saved.txt","rb"))==NULL){
                printf("Error!!\nSaved File not found.");
                getch();
                return 1;
            }
            saved_file b;
            if(fread(&b,sizeof b,1,fp)!=1){
                printf("Error");
                exit(1);
            }
            fclose(fp);
            if(strcmp(b.player_name,Name)){
                printf("Player Name does not match !!!");
                getch();
                return 1;
            }
            state=b.game_state;
            if(state==1) t_o=0;
            else t_o=time(NULL)-b.time;
            num_mine=b.total_mine_number;
            placed_flag=b.board_flag_placed;
            len_x=b.board_x;len_y=b.board_y;
            for(i=0;i<Xmax;i++){
                for(j=0;j<Ymax;j++){
                    element[i][j]=b.board_element[i][j];
                    mine[i][j]=b.board_mine[i][j];
                    flag[i][j]=b.board_flag[i][j];
                }
            }
            b.game_state=0;
            if((fp=fopen("Saved.txt","wb"))==NULL){
                printf("Error");
                exit(1);
            }
            if(fwrite(&b,sizeof b,1,fp)!=1){
                printf("Error");
                exit(1);
            }
            fclose(fp);
            return 0;
        }
        //else if(){}
    }
    else if(ls==1){
        if(type==0){
            if((fp=fopen("Board.txt","wb"))==NULL){
                printf("Error");
                exit(1);
            }
            last_board a;
            a.board_x=len_x;a.board_y=len_y;a.total_mine_number=num_mine;
            if(fwrite(&a,sizeof a,1,fp)!=1){
                printf("Error");
                exit(1);
            }
            fclose(fp);
        }
        else if(type==1){
            if((fp=fopen("Saved.txt","wb"))==NULL){
                printf("Error");
                exit(1);
            }
            saved_file b;
            b.time=t_o;
            if(t_o==0) b.game_state=1;
            else b.game_state=2;
            b.total_mine_number=num_mine;
            b.board_x=len_x;
            b.board_y=len_y;
            b.board_flag_placed=placed_flag;
            strcpy(b.player_name,Name);
            for(i=0;i<Xmax;i++){
                for(j=0;j<Ymax;j++){
                    b.board_element[i][j]=element[i][j];
                    b.board_flag[i][j]=flag[i][j];
                    b.board_mine[i][j]=mine[i][j];
                }
            }
            if(fwrite(&b,sizeof b,1,fp)!=1){
                printf("Error");
                exit(1);
            }
            fclose(fp);
        }
        else if(type==2){
            if(!(len_x==9 && len_y==9 && num_mine==10 || len_x==14 && len_y==14 && num_mine==30 || len_x==14 && len_y==30 && num_mine==60)){
                return;
            }
            ///data
            char o;
            pro *newE;
            newE=(pro*)malloc(sizeof(pro));
            strcpy(newE->player_name,Name);
            newE->Time=time(NULL)-t_o;
            timedate(newE->fin_datetime);
            newE->serial=0;
            if(len_x==9 && len_y==9 && num_mine==10){
                if((fp=fopen("Easy.txt","ab"))==NULL){
                    printf("Error");
                    exit(1);
                }
                fclose(fp);
                o='e';
            }
            else if(len_x==14 && len_y==14 && num_mine==30){
                if((fp=fopen("Medium.txt","ab"))==NULL){
                    printf("Error");
                    exit(1);
                }
                fclose(fp);
                o='m';
            }
            else if(len_x==14 && len_y==30 && num_mine==60){
                if((fp=fopen("Hard.txt","ab"))==NULL){
                    printf("Error");
                    exit(1);
                }
                fclose(fp);
                o='h';
            }
            pro *start=NULL;
            start=proload(start,o);
            start=proinsert(start,newE,o);
            prosave(start,o);
        }


    }
}
///************************************************************************************
int DEF(void){
    len_x=14;len_y=14;num_mine=30;
}
///************************************************************************************
int pause(void){
    state=3;
    if(t_o!=0)
        t_o=time(NULL)-t_o;
    pos_x=0;
    while(1){
        {///pause menu print
            int i,j;
            {///top part
                system("cls");
                ///time & mine table
                printf("%c%c%c%c%c%c%c",tdr,th,th,th,th,th,vdl);
                j=len_y-8;
                for(i=0;i<j;i++) printf(" ");
                printf("%c%c%c%c%c",hdr,h,h,h,hdl);
                for(i=0;i<j;i++) printf(" ");
                printf("%c%c%c%c%c%c%c\n",vdr,th,th,th,th,th,tdl);
                printf("%c%c%c%03d%c",tv,'t',175,t_o,vur);
                for(i=0;i<j;i++) printf("%c",th);
                printf("%c %c %c",tul,face,tur);
                for(i=0;i<j;i++) printf("%c",th);
                printf("%c%03d%c%c%c\n",vul,(num_mine-placed_flag),174,MINE,tv);
                ///outer box top
                printf("%c",tudr);
                for(j=0;j<len_y-2;j++) printf("%c",th); printf("PAUSE");for(j=0;j<len_y-2;j++) printf("%c",th);
                printf("%c\n",tudl);
                printf("%c%c",tv,dr);for(i=0;i<len_y;i++)printf("%c%c",h,h);printf("\b%c%c\n",dl,tv);
            }///top part done
            for(i=0;i<2*len_x-1;i++){
                if(i==2 && pos_x==0)        {printf("%c%c ->1.CONTINUE",tv,v);for(j=0;j<2*len_y-13;j++) printf(" ");printf("\b%c%c\n",v,tv);}
                else if(i==2)               {printf("%c%c   1.Continue",tv,v);for(j=0;j<2*len_y-13;j++) printf(" ");printf("\b%c%c\n",v,tv);}
                else if(i==4 && pos_x==1)   {printf("%c%c ->2.SAVE",tv,v);for(j=0;j<2*len_y-9;j++) printf(" ");printf("\b%c%c\n",v,tv);}
                else if(i==4)               {printf("%c%c   2.Save",tv,v);for(j=0;j<2*len_y-9;j++) printf(" ");printf("\b%c%c\n",v,tv);}
                else if(i==6 && pos_x==2)   {printf("%c%c ->3.QUIT",tv,v);for(j=0;j<2*len_y-9;j++) printf(" ");printf("\b%c%c\n",v,tv);}
                else if(i==6)               {printf("%c%c   3.Quit",tv,v);for(j=0;j<2*len_y-9;j++) printf(" ");printf("\b%c%c\n",v,tv);}
                else                        {printf("%c%c",tv,v);for(j=0;j<2*len_y;j++)printf(" ");printf("\b%c%c\n",v,tv);}
            }
            printf("%c%c",tv,ur);for(i=0;i<len_y;i++)printf("%c%c",h,h);printf("\b%c%c\n",ul,tv);
            printf("%c",tur);for(i=0;i<2*len_y+2;i++)printf("%c",th);printf("\b%c\n",tul);
        }
        command=getch();
        if(command==224)command=getch();
        command_processor();
        if(state!=3){
            pos_x=0;
            break;
        }
    }
}
///************************************************************************************
int difficulty(void){
    state=4;
    pos_x=0;
    while(1){
        system("cls");
        {///box print
            int i,j;
            {///top part
                printf("%c%c%c%c%c%c%c",tdr,th,th,th,th,th,vdl);for(i=0;i<13;i++)printf(" ");printf("%c%c%c%c%c",hdr,h,h,h,hdl);for(i=0;i<13;i++)printf(" ");printf("%c%c%c%c%c%c%c\n",vdr,th,th,th,th,th,tdl);
                printf("%c%c%c%03d%c",tv,'t',175,0,vur);for(i=0;i<13;i++) printf("%c",th);printf("%c %c %c",tul,face,tur);for(i=0;i<13;i++) printf("%c",th);printf("%c%03d%c%c%c\n",vul,(num_mine),174,MINE,tv);
                printf("%c",tudr);for(i=0;i<6;i++)printf("%c",th);printf("DIFFICULTY");for(i=0;i<10;i++)printf("%c",th);printf("DESCRIPTION");for(i=0;i<6;i++)printf("%c",th);printf("%c\n",tudl);
                printf("%c%c%c",tv,dr,h);for(i=0;i<20;i++)printf("%c%c",lrd,h);printf("%c%c\n",dl,tv);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,20,v,'3',v,219,v,219,v,219,v,'X',v,219,v,'8',v,219,v,219,v,219,v,219,v,219,v,'?',v,'1',v,'?',v,'1',v,219,v,219,v,219,v,tv);
            }
            if(pos_x==0)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tdr,h,tdl  ,h);for(i=0;i<7;i++)printf("%c%c",lru,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",lru ,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<7;i++)printf("%c%c",lru,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}

            if(pos_x==0)        {printf("%c%c%c%c%c%c BEGINNER      %c  9x9  grid,Mine=10%c%c%c%c\n",tv,v,219,v,'1',v,v,v,1,v,tv);}
            else                {printf("%c%c%c%c%c%c Beginner      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,'1',v,v,15,v,219,v,219,v,219,v,'2',v,'1',v,' ',v,'1',v,'2',v,219,v,1,v,tv);}
            if(pos_x==1)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tdr,h,tdl  ,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",lru ,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else if(pos_x==0)   {printf("%c%c%c%c%c%c%c",tv,udr,h,tur,h,tul  ,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",lrd ,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}

            if(pos_x==1)        {printf("%c%c%c%c%c%c INTERMEDIATE  %c 14x14 grid,Mine=30%c%c%c%c\n",tv,v,20,v,'2',v,v,v,2,v,tv);}
            else                {printf("%c%c%c%c%c%c Intermediate  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,20,v,'2',v,v,'x',v,50,v,49,v,20,v,'1',v,' ',v,' ',v,' ',v,'2',v,219,v,2,v,tv);}
            if(pos_x==2)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tdr,h,tdl  ,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",lru ,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else if(pos_x==1)   {printf("%c%c%c%c%c%c%c",tv,udr,h,tur,h,tul  ,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",lrd ,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}

            if(pos_x==2)        {printf("%c%c%c%c%c%c ADVANCED      %c 14x30 grid,Mine=60%c%c%c%c\n",tv,v,'?',v,'3',v,v,v,15,v,tv);}
            else                {printf("%c%c%c%c%c%c Advanced      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,'?',v,'3',v,v,49,v,49,v,49,v,49,v,'1',v,' ',v,'1',v,'1',v,'1',v,219,v,15,v,tv);}
            if(pos_x==3)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tdr,h,tdl  ,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr ,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else if(pos_x==2)   {printf("%c%c%c%c%c%c%c",tv,udr,h,tur,h,tul  ,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",lrd ,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}

            if(pos_x==3)        {printf("%c%c%c%c%c%c CUSTOM        %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,'4',v,v,' ',v,' ',v,' ',v,' ',v,' ',v,' ',v,'1',v,15,v,219,v,219,v,20,v,tv);}
            else                {printf("%c%c%c%c%c%c Custom        %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,'4',v,v,' ',v,' ',v,' ',v,' ',v,' ',v,' ',v,'1',v,15,v,219,v,219,v,20,v,tv);}
            if(pos_x==4)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tdr,h,tdl  ,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else if(pos_x==3)   {printf("%c%c%c%c%c%c%c",tv,udr,h,tur,h,tul  ,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr ,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<7;i++)printf("%c%c",h,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}

            if(pos_x==4)        {printf("%c%c%c%c%c%c BACK          %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,27,v,'5',v,v,' ',v,49,v,49,v,49,v,'1',v,'1',v,'2',v,219,v,219,v,219,v,3,v,tv);}
            else                {printf("%c%c%c%c%c%c Back          %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,27,v,'5',v,v,' ',v,49,v,49,v,49,v,'1',v,'1',v,'2',v,219,v,219,v,219,v,3,v,tv);}
            if(pos_x==4)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tur ,h,tul ,h);for(i=0;i<7;i++)printf("%c%c",lrd,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<7;i++)printf("%c%c",lrd,h);printf("%c%c",udlr,h);for(i=0;i<9;i++)printf("%c%c",udlr,h);printf("%c%c%c%c\n",udlr,h,udl,tv);}
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,14,v,219,v,'1',v,15,v,219,v,219,v,20,v,219,v,3,v,' ',v,49,v,20,v,219,v,219,v,219,v,219,v,219,v,219,v,219,v,219,v,tv);
            printf("%c%c%c",tv,ur,h);for(i=0;i<20;i++)printf("%c%c",lru,h);printf("%c%c\n",ul,tv);
            printf("%c",tur);for(i=0;i<43;i++)printf("%c",th);printf("%c",tul);
        }
        command=getch();
        if(command==224)command=getch();
        command_processor();
        if(state!=4){
            pos_x=0;
            break;
        }
    }
}
///************************************************************************************
int custom(void){
    int x=len_x,y=len_y,m=num_mine,mm;
    pos_x=0;
    while(1){
        system("cls");
        ///
        if(y<8) y=8; if(y>Ymax-2) y=Ymax-2;
        if(x<5) x=5; if(x>Xmax-2) x=Xmax-2;
        mm=0.7*x*y;
        if(m<5) m=5; if(m>mm) m=mm;
        ///
        {///box print
            int i,j;
            {///top part
                printf("%c%c%c%c%c%c%c",tdr,th,th,th,th,th,vdl);for(i=0;i<4;i++)printf(" ");printf("%c%c%c%c%c",hdr,h,h,h,hdl);for(i=0;i<4;i++)printf(" ");printf("%c%c%c%c%c%c%c\n",vdr,th,th,th,th,th,tdl);
                printf("%c%c%c%03d%c",tv,'t',175,0,vur);for(i=0;i<4;i++) printf("%c",th);printf("%c %c %c",tul,face,tur);for(i=0;i<4;i++) printf("%c",th);printf("%c%03d%c%c%c\n",vul,(num_mine),174,MINE,tv);
                printf("%c",tudr);for(i=0;i<6;i++)printf("%c",th);printf("CUSTOM-BOARD");for(i=0;i<7;i++)printf("%c",th);printf("%c\n",tudl);
                printf("%c%c%c",tv,dr,h);for(i=0;i<11;i++)printf("%c%c",lrd,h);printf("%c%c\n",dl,tv);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,20,v,'2',v,20,v,219,v,49,v,15,v,219,v,'3',v,219,v,219,v,219,v,tv);
            }
            if(pos_x==0)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tdr,h,tdl  ,h);for(i=0;i<4;i++)printf("%c%c",lru,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,lru,h,udlr,h,udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<4;i++)printf("%c%c",lru,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,lru,h,udlr,h,udlr,h,udl,tv);}

            if(pos_x==0){
                printf("%c%c%c%c%c%c LENGTH  ",tv,v,219,v,49,v);
                if(y==8)        printf("%c%c%c %02d%c%c%c%c%c%c\n",v,219,v,y,v,16,v,th,v,tv);
                else if(y==Ymax-2) printf("%c%c%c %02d%c%c%c%c%c%c\n",v,17,v,y,v,219,v,th,v,tv);
                else            printf("%c%c%c %02d%c%c%c%c%c%c\n",v,17,v,y,v,16,v,th,v,tv);
            }
            else{
                printf("%c%c%c%c%c%c Length  %c%c%c %02d%c%c%c%c%c%c\n",tv,v,219,v,49,v,v,219,v,y,v,219,v,th,v,tv);
            }
            if(pos_x==0)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tur,h,tul  ,h);for(i=0;i<4;i++)printf("%c%c",h,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,h,h,udlr,h,udlr,h,udl,tv);}
            else if(pos_x==1)   {printf("%c%c%c%c%c%c%c",tv,udr,h,tdr,h,tdl  ,h);for(i=0;i<4;i++)printf("%c%c",h,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,h,h,udlr,h,udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<4;i++)printf("%c%c",h,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,h,h,udlr,h,udlr,h,udl,tv);}

            if(pos_x==1){
                printf("%c%c%c%c%c%c HEIGHT  ",tv,v,219,v,50,v);
                if(x==5)        printf("%c%c%c %02d%c%c%c%c%c%c\n",v,219,v,x,v,16,v,tv,v,tv);
                else if(x==Xmax-2) printf("%c%c%c %02d%c%c%c%c%c%c\n",v,17,v,x,v,219,v,tv,v,tv);
                else            printf("%c%c%c %02d%c%c%c%c%c%c\n",v,17,v,x,v,16,v,tv,v,tv);
            }
            else{
                printf("%c%c%c%c%c%c Height  %c%c%c %02d%c%c%c%c%c%c\n",tv,v,219,v,50,v,v,219,v,x,v,219,v,tv,v,tv);
            }
            if(pos_x==1)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tur,h,tul  ,h);for(i=0;i<4;i++)printf("%c%c",h,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,h,h,udlr,h,udlr,h,udl,tv);}
            else if(pos_x==2)   {printf("%c%c%c%c%c%c%c",tv,udr,h,tdr,h,tdl  ,h);for(i=0;i<4;i++)printf("%c%c",h,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,h,h,udlr,h,udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<4;i++)printf("%c%c",h,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,h,h,udlr,h,udlr,h,udl,tv);}

            if(pos_x==2){
                printf("%c%c%c%c%c%c MINE    ",tv,v,20,v,51,v);
                if(m==5)          printf("%c%c%c%03d%c%c%c%c%c%c\n",v,219,v,m,v,16,v,15,v,tv);
                else if(m==mm) printf("%c%c%c%03d%c%c%c%c%c%c\n",v,17,v,m,v,219,v,15,v,tv);
                else              printf("%c%c%c%03d%c%c%c%c%c%c\n",v,17,v,m,v,16,v,15,v,tv);
            }
            else{
                printf("%c%c%c%c%c%c Mine    %c%c%c%03d%c%c%c%c%c%c\n",tv,v,20,v,51,v,v,219,v,m,v,219,v,15,v,tv);
            }
            if(pos_x==2)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tur,h,tul  ,h);for(i=0;i<4;i++)printf("%c%c",h,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,lrd,h,udlr,h,udlr,h,udl,tv);}
            else if(pos_x==3)   {printf("%c%c%c%c%c%c%c",tv,udr,h,tdr,h,tdl  ,h);for(i=0;i<4;i++)printf("%c%c",h,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,lrd,h,udlr,h,udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<4;i++)printf("%c%c",h,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,lrd,h,udlr,h,udlr,h,udl,tv);}

            if(pos_x==3){printf("%c%c%c%c%c%c DONE    %c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,52,v,v,'2',v,15,v,219,v,219,v,'?',v,tv);}
            else        {printf("%c%c%c%c%c%c Done    %c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,52,v,v,'2',v,15,v,219,v,219,v,'?',v,tv);}
            if(pos_x==3)        {printf("%c%c%c%c%c%c%c",tv,udr,h,tur,h,tul  ,h);for(i=0;i<4;i++)printf("%c%c",lrd,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,udlr,h,udlr,h,udlr,h,udl,tv);}
            else                {printf("%c%c%c%c%c%c%c",tv,udr,h,udlr,h,udlr,h);for(i=0;i<4;i++)printf("%c%c",lrd,h);printf("%c%c%c%c%c%c%c%c%c%c%c%c\n",udlr,h,udlr,h,udlr,h,udlr,h,udlr,h,udl,tv);}

            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,'?',v,219,v,'1',v,15,v,219,v,219,v,20,v,219,v,20,v,' ',v,'3',v,tv);
            printf("%c%c",tv,ur);for(i=0;i<11;i++)printf("%c%c",h,lru);printf("%c%c%c\n",h,ul,tv);
            printf("%c",tur);for(i=0;i<25;i++)printf("%c",th);printf("%c\n",tul);
        }
        command=getch();
        if(command==224)command=getch();
        ///
        if(command==80 || command==50 || command==115 || command==83){
            pos_x++;
            if(pos_x==4)
                pos_x=0;
        }
        else if(command==72 || command==56 || command==119 || command==87){
            pos_x--;
            if(pos_x==-1)
                pos_x=3;
        }
        else if(command==77 || command==54 || command==100 || command==68){
            if     (pos_x==0) y++;
            else if(pos_x==1) x++;
            else if(pos_x==2) m++;
        }
        else if(command==75 || command==52 || command==97 || command==65){
            if     (pos_x==0) y--;
            else if(pos_x==1) x--;
            else if(pos_x==2) m--;
        }
        else if((command==13 || command==122 || command==90) && pos_x==3)
            break;
        else if(command==27 || command==120 || command==88)
            return 0;
        ///
    }
    len_x=x;len_y=y;num_mine=m;
    load_save(1,0);
    loading(2);
    return 0;
}
///************************************************************************************
///**********DOWNLOADED******************Character Color*********WARNING***************
void SetColor(int ForgC){
     WORD wColor;
     //We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
void ClearConsoleToColors(int ForgC, int BackC){
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     //Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     //This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     //A return value... indicating how many chars were written
     //   not used but we need to capture this since it will be
     //   written anyway (passing NULL causes an access violation).
     DWORD count;

     //This is a structure containing all of the console info
     // it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          //This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}
void SetColorAndBackground(int ForgC, int BackC){
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
///*******************************WARNING*********************************************
///***********************************************************************************
int pos(int x,int y){
/************************************************************************************
/****************************************************************
    int a;                                                      *
    a=x*len_y;                                          *********
    if(x%2!=0)                                          *
        a+=(len_y-1-y);                                 *********
    else                                                        *
        a+=y;                                           *********
    return a;                                           *
***                                                     *********/
///************************************spiral**********************************************
    if(x<0 || x>=len_x || y<0 || y>=len_y)
        return ;
    int a=len_x,b=len_y,i,j,c=0;
    ///
    int s=0,A=0,B=0,g;
    i=0;
    for(j=0;j<b;j++){
        if(x==i && y==j) return c;
        c++;
    }j--;c--;
    while(1){
        if(a==A || b==A) break;
        if(s==0){
            for(g=0;g<a-A;i++,g++){
                if(x==i && y==j) return c;
                c++;
            }i--;c--;s++;A++;
        }
        else if(s==1){
            for(g=0;g<b-B;j--,g++){
                if(x==i && y==j) return c;
                c++;
            }j++;c--;s++;B++;
        }
        else if(s==2 ){
           for(g=0;g<a-A;i--,g++){
                if(x==i && y==j) return c;
                c++;
           }i++;c--;s++;A++;
        }
        else if(s==3 ){
            for(g=0;g<b-B;j++,g++){
                if(x==i && y==j) return c;
                c++;
            }j--;c--;s=0;B++;
        }
    }



}
///************************************************************************************
int timedate(char *dt){
    time_t t ;
    struct tm *tmp ;
    time( &t );
    tmp = localtime( &t );
    char MY_TIME[30];
    int i;
    for(i=0;i<25;i++) dt[i]=0;
    strftime(MY_TIME, sizeof(MY_TIME), "%c", tmp);
    for(i=0;i<10;i++) dt[i]=MY_TIME[i+9];
    dt[i]='\0';
    strftime(MY_TIME, sizeof(MY_TIME), "%I", tmp);
    for(i=0;i<2;i++) dt[i]=MY_TIME[i];
    strftime(MY_TIME, sizeof(MY_TIME), " %p ", tmp);
    strcat(dt,MY_TIME);
    strftime(MY_TIME, sizeof(MY_TIME), "%d/%m/", tmp);
    strcat(dt,MY_TIME);
    strftime(MY_TIME, sizeof(MY_TIME), "%x", tmp);
    dt[18]=MY_TIME[6];dt[19]=MY_TIME[7];dt[20]='\0';
    strftime(MY_TIME, sizeof(MY_TIME), " %a", tmp);
    strcat(dt,MY_TIME);
}
///**************************************************************************************
pro* proload(pro* start,char o){
    FILE *fp;
    if(o=='e'){
        if((fp=fopen("Easy.txt","rb"))==NULL){
            printf("Error");
            exit(1);
        }
    }
    else if(o=='m'){
        if((fp=fopen("Medium.txt","rb"))==NULL){
            printf("Error");
            exit(1);
        }
    }
    else if(o=='h'){
        if((fp=fopen("Hard.txt","rb"))==NULL){
            printf("Error");
            exit(1);
        }
    }
        while(1){
        pro *newE,*curr;
        newE=(pro*)malloc(sizeof(pro));
        if(fread(newE,sizeof(pro),1,fp)!=1){
            //printf("ERROR");
            return start;
            //exit(1);
        }
        newE->next=NULL;
        if(start==NULL)
            start=newE;
        else{
            curr=start;
            while(curr->next!=NULL){
                curr=curr->next;
            }
            curr->next=newE;
        }
    }
    fclose(fp);
    //getch();
    return start;
}
///********************************************************************************
pro* proinsert(pro* start, pro* newE, char o){
    pro *curr, *prev;
    if(start==NULL){
        start=newE;
    }
    else{
        curr=start;
        prev=NULL;
        while(1){
            if(newE->Time<curr->Time&& prev==NULL){
                start=newE;
                newE->next=curr;
                break;
            }
            else if(newE->Time<curr->Time && prev!=NULL){
                prev->next=newE;
                newE->next=curr;
                break;
            }
            else if(newE->Time>curr->Time && curr->next==NULL){
                curr->next=newE;
                break;
            }
            else{
                prev=curr;
                curr=curr->next;
            }
        }
    }
    return start;
}
///**********************************************************************************
void prosave(pro* start, char o){
    FILE *fp;
    if(o=='e'){
        if((fp=fopen("Easy.txt","wb"))==NULL){
            printf("Error");
            exit(1);
        }
    }
    else if(o=='m'){
        if((fp=fopen("Medium.txt","wb"))==NULL){
            printf("Error");
            exit(1);
        }
    }
    else if(o=='h'){
        if((fp=fopen("Hard.txt","wb"))==NULL){
            printf("Error");
            exit(1);
        }
    }
    pro *curr=start;
    int i=1;
    while(curr!=NULL){
        curr->serial=i;i++;
        fwrite(curr,sizeof(pro),1,fp);
        curr=curr->next;
    }
    fclose(fp);
}
///************************************************************************************
int score(void){
    state=6;
    pos_x=0;
    while(1){
        system("cls");
        {///box print
            int i,j;
            {///top part
                printf("%c%c%c%c%c%c%c",tdr,th,th,th,th,th,vdl);for(i=0;i<3;i++)printf(" ");printf("%c%c%c%c%c",hdr,h,h,h,hdl);for(i=0;i<3;i++)printf(" ");printf("%c%c%c%c%c%c%c\n",vdr,th,th,th,th,th,tdl);
                printf("%c%c%c%03d%c",tv,'t',175,0,vur);for(i=0;i<3;i++) printf("%c",th);printf("%c %c %c",tul,face,tur);for(i=0;i<3;i++) printf("%c",th);printf("%c%03d%c%c%c\n",vul,(num_mine),174,MINE,tv);
                printf("%c",tudr);for(i=0;i<7;i++)printf("%c",th);printf("DIFFICULTY");for(i=0;i<6;i++)printf("%c",th);printf("%c\n",tudl);
                printf("%c%c%c",tv,dr,h);for(i=0;i<10;i++)printf("%c%c",lrd,h);printf("%c%c\n",dl,tv);
                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,20,v,'3',v,219,v,219,v,219,v,'X',v,219,v,'8',v,219,v,219,v,tv);
            }
        ///condition

        if(pos_x==0)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tdr,h,tdl,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,udlr,h,udl,tv);

        if(pos_x==0)        printf("%c%c%c%c1%c BEGINNER      %c%c%c%c\n",tv,v,1,v,v,v,'6',v,tv);
        else                printf("%c%c%c%c1%c Beginner      %c%c%c%c\n",tv,v,1,v,v,v,'6',v,tv);

        if(pos_x==0)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tur,h,tul,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else if(pos_x==1)   printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tdr,h,tdl,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);

        if(pos_x==1)        printf("%c%c%c%c2%c INTERMEDIATE  %c%c%c%c\n",tv,v,219,v,v,v,219,v,tv);
        else                printf("%c%c%c%c2%c Intermediate  %c%c%c%c\n",tv,v,219,v,v,v,219,v,tv);

        if(pos_x==1)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tur,h,tul,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else if(pos_x==2)   printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tdr,h,tdl,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);

        if(pos_x==2)        printf("%c%c%c%c3%c ADVANCED      %c%c%c%c\n",tv,v,20,v,v,v,219,v,tv);
        else                printf("%c%c%c%c3%c Advanced      %c%c%c%c\n",tv,v,20,v,v,v,219,v,tv);

        if(pos_x==2)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tur,h,tul,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else if(pos_x==3)   printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tdr,h,tdl,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,h,h,h,h,h,h,h,h,h,h,h,h,h,h,udlr,h,udl,tv);

        if(pos_x==3)        printf("%c%c%c%c4%c BACK          %c%c%c%c\n",tv,v,219,v,v,v,'X',v,tv);
        else                printf("%c%c%c%c4%c Back          %c%c%c%c\n",tv,v,219,v,v,v,'x',v,tv);

        if(pos_x==3)        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,tur,h,tul,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,udlr,h,udl,tv);
        else                printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,udr,h,udlr,h,udlr,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,lrd,h,udlr,h,udl,tv);

        ///last layers
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,14,v,219,v,'7',v,219,v,219,v,219,v,20,v,219,v,3,v,219,v,tv);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,ur,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,lru,h,ul,tv);
        printf("%c",tur);for(i=0;i<23;i++)printf("%c",th);printf("%c",tul);
        }
        fflush(stdin);
        command=getch();
        if(command==224)command=getch();
        command_processor();
        if(state!=6){
            pos_x=0;
            break;
        }
    }
}
///***************************************************************************************************************************************************************************************
int card(char ch){
    FILE *fp;
    int i;
    while(1){
        if(ch=='e'){
            if((fp=fopen("Easy.txt","ab"))==NULL){
                printf("Error");
                exit(1);
            }
            if((fp=fopen("Easy.txt","rb"))==NULL){
                printf("Error");
                exit(1);
            }
        }
        else if(ch=='m'){
            if((fp=fopen("Medium.txt","ab"))==NULL){
                printf("Error");
                exit(1);
            }
            if((fp=fopen("Medium.txt","rb"))==NULL){
                printf("Error");
                exit(1);
            }
        }
        else if(ch=='h'){
            if((fp=fopen("Hard.txt","ab"))==NULL){
                printf("Error");
                exit(1);
            }
            if((fp=fopen("Hard.txt","rb"))==NULL){
                printf("Error*");
                exit(1);
            }
        }
        pro a;
//    if(fread(&a,sizeof(pro),1,fp)!=1){
//        printf("Error");
//        exit(1);
//    }
        system("cls");
        ///
        int i,j;
        {///top part
            printf("%c%c%c%c%c%c%c",tdr,th,th,th,th,th,vdl);for(i=0;i<23;i++)printf(" ");printf("%c%c%c%c%c",hdr,h,h,h,hdl);for(i=0;i<23;i++)printf(" ");printf("%c%c%c%c%c%c%c\n",vdr,th,th,th,th,th,tdl);
            printf("%c%c%c%03d%c",tv,'t',175,0,vur);for(i=0;i<23;i++) printf("%c",th);printf("%c %c %c",tul,face,tur);for(i=0;i<23;i++) printf("%c",th);printf("%c%03d%c%c%c\n",vul,(num_mine),174,MINE,tv);
            printf("%c",tudr);for(i=0;i<27;i++)printf("%c",th);printf("HIGHSCORE");for(i=0;i<27;i++)printf("%c",th);printf("%c\n",tudl);
            printf("%c%c%c",tv,dr,h);for(i=0;i<30;i++)printf("%c%c",lrd,h);printf("%c%c\n",dl,tv);
            //printf("%c%c%c",tv,v,219);for(i=0;i<30;i++)printf("%c%c",v,219);printf("%c%c\n",v,tv);
            printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",tv,v,219,v,219,v,219,v,219,v,219,v,219,v,'N',v,'A',v,'M',v,'E',v,219,v,219,v,'T',v,'I',v,'M',v,'E',v,219,v,219,v,219,v,219,v,219,v,'D',v,'A',v,'T',v,'E',v,219,v,219,v,219,v,219,v,219,v,219,v,tv);
        }
        printf("%c%c",tv,udr);for(i=0;i<3;i++)printf("%c%c",h,udlr);for(i=0;i<6;i++)printf("%c%c",h,lru);for(i=0;i<3;i++)printf("%c%c",h,udlr);for(i=0;i<3;i++)printf("%c%c",h,lru);printf("%c%c%c%c",h,udlr,h,udlr);for(i=0;i<12;i++)printf("%c%c",h,lru);printf("%c%c%c%c%c\n",h,udlr,h,udl,tv);
        ///
        if(fread(&a,sizeof(pro),1,fp)!=1){
            state=0;
            printf("%c%cNo data found                                                %c%c\n%c%c",tv,v,v,tv,tv,ur);for(i=0;i<61;i++)printf("%c",h);printf("%c%c\n%c",ul,tv,tur);for(i=0;i<63;i++)printf("%c",th);printf("%c",tul);
            getch();
            return;
            printf("fError");
        }
        for(j=0;j<10 && strlen(a.fin_datetime); j++){
            if(strlen(a.fin_datetime)){
            printf("%c%c%c%c%c%c%c%c%13s%c%c%c%c%c%5d%c%c%c%c%c%c%s%c%c%c%c\n",tv,v,219,v,j+48,v,219,v,a.player_name,v,219,v,219,v,a.Time,' ','S',v,219,v,' ',a.fin_datetime,v,219,v,tv);
            }
            if(fread(&a,sizeof(pro),1,fp)!=1){
                printf("Error");
            }
            if(strlen(a.fin_datetime)){
                printf("%c%c",tv,udr);for(i=0;i<3;i++)printf("%c%c",h,udlr);for(i=0;i<13;i++)printf("%c",h);printf("%c%c%c%c%c",udlr,h,udlr,h,udlr);for(i=0;i<7;i++)printf("%c",h);printf("%c%c%c",udlr,h,udlr);for(i=0;i<25;i++)printf("%c",h);printf("%c%c%c%c\n",udlr,h,udl,tv);
            }
            else{
                printf("%c%c",tv,udr);for(i=0;i<3;i++)printf("%c%c",h,udlr);for(i=0;i<6;i++)printf("%c%c",h,lrd);for(i=0;i<3;i++)printf("%c%c",h,udlr);for(i=0;i<3;i++)printf("%c%c",h,lrd);printf("%c%c%c%c",h,udlr,h,udlr);for(i=0;i<12;i++)printf("%c%c",h,lrd);printf("%c%c%c%c%c\n",h,udlr,h,udl,tv);
                printf("%c%c%c",tv,v,219);for(i=0;i<30;i++)printf("%c%c",v,219);printf("%c%c\n",v,tv);
                printf("%c%c%c",tv,ur,h);for(i=0;i<30;i++)printf("%c%c",lru,h);printf("%c%c\n",ul,tv);
                printf("%c",tur);for(i=0;i<63;i++)printf("%c",th);printf("%c\n",tul);
            }
        }
        fflush(stdin);
        command=getch();
        if(command=='x' || command=='X' || command==32|| command==27){
            pos_x=0;
            state=0;
            break;
        }
    }
}
