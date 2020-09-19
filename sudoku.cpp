#include<bits/stdc++.h>
using namespace std;
int sudoku_board[9][9]= {0};
int zero_board[9][9]={0};
int solved_array[9][9]={0};
int counter;
int numberlist[]={1,2,3,4,5,6,7,8,9};
int randomfunc()
{
    return rand()%9;
}

bool isvalid(int num,int a,int b,int board[][9])
{
    for(int i=0;i<9;i++)
    {
        if(board[a][i]==num)
        return false;
    }
    for(int i=0;i<9;i++)
    {
        if(board[i][b]==num)
        return false;
    }
    int x1=(a/3)*3;
    int y1=(b/3)*3;
    for(int i=x1;i<x1+3;i++)
    {
        for(int j=y1;j<y1+3;j++)
        {
             if(board[i][j]==num)
             return false;
        }
    }
    return true;
}
void print_board(int board[][9])
{
    cout<<endl;

    for(int i=0;i<9;i++)
    {
        if(i%3==0)
            cout<<" ---------------------------"<<endl;
        for(int j=0;j<9;j++)
        {
            if(j%3==0)
            cout<<" | ";
            cout<<board[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<" ---------------------------"<<endl;

}
bool checkfull(int board[][9])
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(board[i][j]==0)
            return false;
        }
    }
    return true;
}


bool complete_sudoku()
{
    int l,i,j;
    for(l=0;l<81;l++)
    {
        i=l/9;
        j=l%9;
            if(zero_board[i][j]==0)
            {
                shuffle(numberlist,numberlist+9,default_random_engine(randomfunc()));
                for(int k=0;k<9;k++)
                {
                    if(isvalid(numberlist[k],i,j,zero_board))
                    {
                        zero_board[i][j]=numberlist[k];
                        if(checkfull(zero_board))
                        return true;
                        else{
                        if(complete_sudoku())
                        return true;
                        }
                    }

                }
                break;
            }
    }

    zero_board[i][j]=0;
    return false;
}
bool solve(int board[][9])
{
    int l,i,j;
    for(l=0;l<81;l++)
    {
        i=l/9;
        j=l%9;
            if(board[i][j]==0)
            {
                for(int k=1;k<=9;k++)
                {
                    if(isvalid(k,i,j,board))
                    {
                        board[i][j]=k;
                        if(checkfull(board)){
                              for(int i=0;i<81;i++)
                                 {
                                   solved_array[i/9][i%9]=board[i/9][i%9];
                                 }
                         counter+=1;
                           break;
                        }
                        else
                        {
                        if(solve(board))
                        return true;
                        }
                    }
                }
                break;
            }
    }
    board[i][j]=0;
    return false;
}
void erase_values()
{
   int attempts=5;
   while(attempts)
   {
       int row=rand()%9;
       int column=rand()%9;
       while(zero_board[row][column]==0)
       {
            row=rand()%9;
            column=rand()%9;
       }
      int store=zero_board[row][column];
      zero_board[row][column]=0;

      int store_array[9][9]={0};
      for(int i=0;i<81;i++)
      {
        store_array[i/9][i%9]=zero_board[i/9][i%9];
      }
      counter=0;
      solve(store_array);
      if(counter!=1){
      zero_board[row][column]=store;
      attempts--;
      }
   }
}
set<pair<int,int>> s;
void after_gen_board()
{
    for(int i=0;i<81;i++)
    {
        int r=i/9;
        int c=i%9;
        if(zero_board[r][c]!=0)
            s.insert(make_pair(r,c));
    }

}

bool check_same(int a[][9],int b[][9])
{

    for(int i=0;i<81;i++)
    {
        if(a[i/9][i%9]!=b[i/9][i%9])
            return false;
    }

    return true;
}

void value_insert_for_play(int r,int c,int k)
{
    if(r>8 or c>8 or r<0 or c<0)
    {
      cout<<"\nWrong Position";
      return;
    }

    if(s.find(make_pair(r,c))==s.end())
    zero_board[r][c]=k;
    else
    cout<<"\nThis position cannot be filled";

    if(checkfull(zero_board))
    {
          if(check_same(zero_board,solved_array))
          cout<<"CONGRATULATIONS... YOU WON !!";
          else
          cout<<"THE SUDOKU IS NOT SOLVED CORRECTLY ";
    }
}


int main()
{
    srand(unsigned(time(0)));
    int n;
    cout<<"*************** WELCOME TO SUDOKU ***************\n\n";
    do
    {
        //USER CAN PRESS 1 TO START A NEW GAME
        cout<<"\nEnter 1 to start a new game"<<endl;

        //USER CAN PRESS TO 2 GET HIS/HER SUDOKU SOLVED
        cout<<"Enter 2 to get your sudoku solved"<<endl;

        //USER CAN ENTER 3 TO QUIT
        cout<<"Enter 3 to quit"<<endl;
        cout<<"\nEnter choice: ";
        cin>>n;

        if(n==1)
        {
            memset(zero_board,0,sizeof(zero_board));
            complete_sudoku();
            erase_values();
            after_gen_board();
            solve(zero_board);
            cout<<"\nThe sudoku board has generated now you can start playing...!!!";
            print_board(zero_board);

            while(1)
            {
              cout<<"\nEnter values b/w 0-9 and space separated row and column number to insert, -1 to return to main menu, -2 to see solution"<<endl;
              int val,r,c;
              cin>>val;
              if(val==-1)
                break;
              if(val==-2)
              {
                  print_board(solved_array);
                  break;
              }
              cin>>r>>c;
              if(val<=9 and val>=0)
              {
                value_insert_for_play(r-1,c-1,val);
              }
              else
              {
                  cout<<"Oops. You have entered a wrong value... Try again ";
              }
              print_board(zero_board);
            }
        }
        else if(n==2)
        {

           memset(sudoku_board,0,sizeof(sudoku_board));
           cout<<"Enter 1-9 for valid positions and enter 0 for empty positions.";
           cout<<"Enter -1 to return to main menu...!!!\n";
           cout<<"Enter -2 to see the solution";

            int flag=0,flag2=0;
            for(int l=0;l<81;l++)
            {
                int i,j;
                i=l/9;
                j=l%9;
                while(1)
                {   int val;
                    cout<<"\nEnter value at "<<i+1<<","<<j+1<<" : ";
                    cin>>val;
                    if(val==-1)
                    {   flag=1;
                        break;
                    }
                    if(val==-2)
                    {   flag2=1;
                        break;
                    }
                    if(isvalid(val,i,j,sudoku_board))
                    {
                        if(val>=0 and val<=9)
                        {
                          sudoku_board[i][j]=val;
                          break;
                        }
                        else
                        {
                          cout<<"Oops. You have entered a wrong value... Try again";
                        }

                    }
                    else
                    {
                         cout<<"Hey, your sudoku is not valid...!! Try again";
                    }
                }
                if(flag==1 or flag2==1)
                break;
            }

            if(flag!=1)
            {
            cout<<"\nHere's the solution to your sudoku board\n";
            solve(sudoku_board);
            print_board(solved_array);
            }

        }
        else if(n!=3)
        {
            cout<<"Wrong choice... Please enter a valid choice...!!!";
        }

    }
    while(n!=3);
    cout<<"\nThank you for playing with us :) ";
    return 0;
}
