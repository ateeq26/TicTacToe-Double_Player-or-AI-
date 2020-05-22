#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

char bo[10];
char dbo[10];
int no[]={0,1,2,3,4,5,6,7,8,9};
int random(int low,int up)
{
    int num=(rand()%(up-low+1))+low;
    return num;
}

void drawPBoard()
{
    printf("\n\n\t | |\n");
    printf("\t%d|%d|%d\n",no[7],no[8],no[9]);
    printf("\t | |\n");
    printf("   ----------------\n");
    printf("\t | |\n");
    printf("\t%d|%d|%d\n",no[4],no[5],no[6]);
    printf("\t | |\n");
    printf("   ---------------\n");
    printf("\t | |\n");
    printf("\t%d|%d|%d\n",no[1],no[2],no[3]);
    printf("\t | |\n");
}
void drawBoard()
{
    printf("\n\n\t | |\n");
    printf("\t%c|%c|%c\n",bo[7],bo[8],bo[9]);
    printf("\t | |\n");
    printf("   ----------------\n");
    printf("\t | |\n");
    printf("\t%c|%c|%c\n",bo[4],bo[5],bo[6]);
    printf("\t | |\n");
    printf("   ---------------\n");
    printf("\t | |\n");
    printf("\t%c|%c|%c\n",bo[1],bo[2],bo[3]);
    printf("\t | |\n");
}

char selectLetter()
{
    char let=' ';
    while(let!='X' || let!='O')
    {
        printf("Select your character:X or O\n");
        scanf("%c",&let);
        if(let=='X' || let=='O')
            break;
    }
    return let;
}

void makeMove(int mo,int le)
{
    bo[mo]=le;
}
void copyMove(int mo,int le)
{
    dbo[mo]=le;
}
bool isWinner(char ar[],char le)
{
    if((ar[7]==le && ar[8]==le && ar[9]==le)||
       (ar[4]==le && ar[5]==le && ar[6]==le)||
       (ar[1]==le && ar[2]==le && ar[3]==le)||
       (ar[7]==le && ar[4]==le && ar[1]==le)||
       (ar[8]==le && ar[5]==le && ar[2]==le)||
       (ar[9]==le && ar[6]==le && ar[3]==le)||
       (ar[7]==le && ar[5]==le && ar[3]==le)||
       (ar[9]==le && ar[5]==le && ar[1]==le))
        return true;
    else
        return false;

}

bool isFree(char ar[],int pos)
{
    if(ar[pos]==' ')
        return true;
    else
        return false;
}
void copyBoard()
{
    int i;
    for(i=1;i<10;i++)
        dbo[i]=bo[i];

}

int playerMove()
{
    int f3=0;
    int mo=0;
    do
    {
        printf("What is your next move?(1-9)\n");
        scanf("%d",&mo);
        f3=0;
        if(mo<1 && mo>9)
        {
            f3=1;
            printf("Invalid position\n");
        }
        if(!isFree(bo,mo))
        {
            printf("Space not available\n");
            f3=1;
        }
    }while(f3==1);
    return mo;
}
int chooseMove(char bo[],int ar[])
{
    int i;
    for(i=0;i<4;i++)
    {
            if(isFree(bo,ar[i]))
            {
                return ar[i];
                break;
            }
    }
    return 0;
}

void compMove(char let)
{
    char le,ple;int i;
    if(let=='X')
    {
        le='X';
        ple='O';
    }
    else
    {
        le='O';
        ple='X';
    }
    int f2=0;
    copyBoard();
    for(i=1;i<10;i++)
    {
        copyBoard();
        if(isFree(dbo,i))
        {
            copyMove(i,le);
            if(isWinner(dbo,le))
            {
                makeMove(i,le);
                f2=1;
                break;
            }
        }
    }
    for(i=1;i<10;i++)
    {
        copyBoard();
        if(isFree(dbo,i))
        {
            copyMove(i,ple);
            if(isWinner(dbo,ple) && f2==0)
            {
                makeMove(i,le);
                f2=1;
                break;
            }
        }
    }
    int cor[]={1,9,7,3};
    int m=chooseMove(bo,cor);
    if(m!=0 && f2==0)
    {
        makeMove(m,le);
        f2=1;
    }

    if(isFree(bo,5) && f2==0)
    {
        makeMove(5,le);
        f2=1;
    }
    int side[]={2,4,6,8};
    int m2=chooseMove(bo,side);
    if(m2!=0 && f2==0)
    {
            makeMove(m2,le);
            f2=1;
    }
}
bool isBoardFull()
{
    int i,c=0;
    for(i=1;i<10;i++)
    {
        if(!isFree(bo,i))
            c++;
    }
    if(c==9)
        return true;
    else
        return false;

}

void twoplayer()
{
    char le1,le2;int cPl=1,mo;
    printf("Player 1:");
    le1=selectLetter();
    if(le1=='X')
        le2='O';
    else
        le2='X';
    drawPBoard();
    while(isBoardFull()==false)
    {
        if(cPl==1)
        {
        printf("Player %d's turn:",cPl);
        mo=playerMove();
        makeMove(mo,le1);
        if(isWinner(bo,le1))
        {
            printf("%d has won\n",cPl);
            drawBoard();
            break;
        }
        cPl=2;
        }
        drawBoard();
        if(isBoardFull())
        {
            printf("It was a tie\n");
            break;
        }
        if(cPl==2)
        {
        printf("Player %d's turn:",cPl);
        mo=playerMove();
        makeMove(mo,le2);
        if(isWinner(bo,le2))
        {
        printf("%d has won\n",cPl);
        drawBoard();
        break;
        }
        cPl=1;
        }
        drawBoard();
        if(isBoardFull())
        {
            printf("It was a tie\n");
            break;
        }
    }
}
void aicomp()
{
    char le,le1,lec;int mo;
    int cPl=random(1,2);
    if(cPl==1){
        printf("You are Player 1 and Computer is player 2\n");
    }
    else
    {
        printf("You are Player 2 and Computer is player 1\n");
    }
    le=selectLetter();
    if(le=='X')
    {
        le1='X';
        lec='O';
    }
    else
    {
        le1='O';
        lec='X';
    }
    drawPBoard();
    while(isBoardFull()==false)
    {
        if(cPl==1)
        {
        printf("Player %d's turn:",cPl);
        mo=playerMove();
        makeMove(mo,le1);
        if(isWinner(bo,le1))
        {
            printf("%d has won\n",cPl);
            drawBoard();
            break;
        }
        cPl=2;
        }
        if(cPl==2)
        {
            compMove(lec);
            if(isWinner(bo,lec))
            {
            printf("%d has won\n",cPl);
            drawBoard();
            break;
            }
            cPl=1;
        }drawBoard();
        if(isBoardFull())
        {
            printf("It was a tie\n");
            break;
        }
    }

}

int main()
{
int f1=0,mode;char ch;int i;
for(i=1;i<10;i++)
     bo[i]=' ';
while(f1==0)
{
    f1=1;
    printf("\nTIC-TAC-TOE\n");
    printf("\nSelect mode:\n");
    printf("\n1.Double Player.");
    printf("\n2.With AI Computer.");
    printf("Your mode?\n");
    scanf("%d",&mode);
    if(mode==1)
        twoplayer();
    else if(mode==2)
        aicomp();
    else
    {
        f1=0;
        printf("Enter a valid mode");
    }
if(f1==1)
{
printf("Do you want to play more?y\n");
 scanf(" %c",&ch);
if(ch=='y' || ch=='Y')
{
for(i=1;i<10;i++)
     bo[i]=' ';
f1=0;
}
else
printf("Invalid choice");
}
}
return  0;
}


