#include <bits/stdc++.h>
using namespace std;
#define MS(X,Y) memset(X,Y,sizeof(X))
#define VALID(X,Y,R,C) X>=0 && X<R && Y>=0 && Y<C

bool graph[15][15][15][15];
char printChar[15][15];
map <int,int> hashValue;


void setHash()
{
    for(int i=0; i<= 100; i++)
    {
        hashValue[i] = 2*i - 2;
    }
}


int main()
{
    setHash();
    int row1, col1, row2, col2;
    int boardSize;
    string player1, player2;
    string turn;
    int count1 = 0, count2 = 0;
    int blockedCell = 0;
    bool isBlocked;

    printf("Enter 1st Player Name: ");
    cin>>player1;
    printf("Enter 2nd Player Name: ");
    cin>>player2;

    printf("Enter the board size. Example(4, meaning 4*4 grid)\n");
    scanf("%d",&boardSize);
    turn = player1;
    while(1)
    {

        cout<<player1<<" : "<<count1<<endl;
        cout<<player2<<" : "<<count2<<endl;



        for(int i=1; i<=boardSize; i++)
        {
            printf("  %d",i);
        }
        printf("\n");


        //Printing Grid
        int no=0;
        for(int r=0; r<=(2*boardSize - 2); r++)
        {
            if(r%2 ==0) printf("%d ",++no);
            else printf("  ");

            for(int c=0; c<=(2*boardSize -2); c++)
            {

                if(c == 2*boardSize-2 && r%2 == 0) printf(".");

                else if(r%2 == 0)
                {
                    if(c%2 == 0)
                    {
                        printf(".");
                    }

                    else
                    {
                        if(graph[r][c-1][r][c+1] == true) printf("--");
                        else printf("  ");
                    }
                }

                else
                {
                    if(c%2 == 0){
                        if(printChar[r][c] == '|') printf("|");
                        else printf(" ");
                    }
                    else
                    {
                        if(printChar[r][c] == player1[0] || printChar[r][c] == player2[0]) printf(" %c",printChar[r][c]);
                        else printf("  ");
                    }
                }
            }
            printf("\n");
        }



        //Game Ending Condition
        if(blockedCell == (boardSize-1)*(boardSize-1))
        {
            cout<<player1<<"'s Score: "<<count1<<"\n";
            cout<<player2<<"'s Score: "<<count2<<"\n";

            if(count1 > count2) cout<<player1<<" won the game.\n";
            else if(count2 > count1) cout<<player2<<" won the game.\n";
            else cout<<"Match tied.\n";
            break;
        }


        //Taking Move as input
        while(1)
        {
            printf("Enter four integer denoting two dots coordinate\n");
            printf("dot1(row1,col1) and dot2(row2,col2).\n");
            cout<<turn<<"'s turn: ";
            scanf("%d%d%d%d",&row1, &col1, &row2, &col2);

            if(row1 == row2 && col1 != col2  && graph[row1][col1][row2][col2] == false)
            {
                if(col1 > col2) swap(col1,col2);
                break;
            }

            else if(col1 == col2 && row1 != row2 && graph[row1][col1][row2][col2] == false)
            {
                if(row1 > row2) swap(row1,row2);
                break;
            }

            else
            {
                printf("Invalid Input\n");
            }

        }

        isBlocked = false;
        row1 =hashValue[row1];
        row2 =hashValue[row2];
        col1 =hashValue[col1];
        col2 =hashValue[col2];

        graph[row1][col1][row2][col2] = true;
        graph[row2][col2][row1][col1] = true;


        if(row1 == row2)
        {
            if(row1 > 0 && graph[row1][col1][row1-2][col1] == true && graph[row2][col2][row2-2][col2] == true && graph[row1-2][col1][row2-2][col2] == true)
            {
                printChar[row1-1][col1+1] = turn[0];
                if(turn == player1) count1++;
                else count2++;
                blockedCell++;
                isBlocked = true;
            }

            if(row1 < 2*boardSize-2 && graph[row1][col1][row1+2][col1] == true && graph[row2][col2][row2+2][col2] == true && graph[row1+2][col1][row2+2][col2] == true)
            {
                printChar[row1+1][col1+1] = turn[0];
                if(turn == player1) count1++;
                else count2++;
                blockedCell++;
                isBlocked = true;
            }

        }

        else if(col1 == col2)
        {
            printChar[row2-1][col2] = '|';

            if(col1 > 0 && graph[row1][col1][row1][col1-2] == true && graph[row2][col2][row2][col2-2] == true && graph[row1][col1-2][row2][col2-2] == true)
            {
                printChar[row1+1][col1-1] = turn[0];
                if(turn == player1) count1++;
                else count2++;
                blockedCell++;
                isBlocked = true;
            }

            if(col1 < 2*boardSize-2 && graph[row1][col1][row1][col1+2] == true && graph[row2][col2][row2][col2+2] == true && graph[row1][col1+2][row2][col2+2] == true)
            {
                printChar[row1+1][col1+1] = turn[0];
                if(turn == player1) count1++;
                else count2++;
                blockedCell++;
                isBlocked = true;
            }
        }

        if(turn == player1 && isBlocked == false) turn = player2;
        else if(isBlocked == false) turn = player1;

        system("cls");
    }

    return 0;
}
