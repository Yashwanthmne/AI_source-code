#include <bits/stdc++.h>
using namespace std;

#define ll long long

int SIZE = 8;


class ChessBoard
{

        private:
                string board;
                int cost;

        public:
                ChessBoard(string board, int cost)
                {
                        this->cost = cost;
                        this->board = board;
                }

                int getCost()
                {
                        return this->cost;
                }
                string getBoard()
                {
                        return this->board;
                }

                void setCost(int cost)
                {
                        this->cost = cost;
                }
                void setBoard(string board)
                {
                        this->board = board;
                }
};
class Compare
{
        public:
                bool operator() (ChessBoard c1, ChessBoard c2)
                {
                        if (c1.getCost() > c2.getCost())
                                return 1;
                        else if (c1.getCost() < c2.getCost())
                                return -1;
                        return 0;
                }
};

class EightQueens
{
        public:
                string arr;
                ChessBoard initialise()
                {
                        for(int i=0;i<SIZE;i++)
                                for(int j=0;j<SIZE;j++)
                                        arr+="0";
                        return ChessBoard(arr,0);
                }
                int find(string arr){
                        int i;
                        for(i=0;i<SIZE;i++)
                        {
                                int flag = 0;
                                for(int j=0;j<SIZE;j++)
                                {
                                        if(arr[SIZE*i+j] == '1')
                                        {
                                                flag = 1;
                                                break;
                                        }
                                }
                                if(flag == 0)
                                        return i;
                        }
                        return i;
                }

                bool isValid(string arr)
                {
                        for(int i=0;i<SIZE;i++)
                        {
                                int sum_row = 0;
                                int sum_col = 0;
                                for(int j=0;j<SIZE;j++)
                                {
                                        sum_row+=(int)arr[SIZE*i+j]-48;
                                        sum_col+=(int)arr[SIZE*j+i]-48;
                                }
                                if(sum_row > 1 || sum_col > 1)
                                        return false;
                        }
                        for(int i=0;i<SIZE;i++)
                        {
                                int sum_left = 0;
                                int sum_right = 0;
                                for(int j=0;j+i<SIZE;j++)
                                {
                                        sum_left+=(int)arr[SIZE*j+j+i]-48;
                                        sum_right+=(int)arr[SIZE*(j+i)+j]-48;
                                }
                                if(sum_left > 1 || sum_right > 1)
                                        return false;
                        }
                        for(int i=0;i<2*SIZE-1;i++)
                        {
                                int sum_left = 0;
                                int sum_right = 0;
                                if(i<SIZE)
                                {
                                        for(int j=0;i-j>=0;j++)
                                        {
                                                sum_left+=(int)arr[SIZE*j+i-j]-48;
                                        }
                                }
                                else
                                {
                                        for(int j=i-SIZE+1;j<SIZE;j++)
                                        {
                                                sum_right+=(int)arr[SIZE*j+i-j]-48;
                                        }
                                }
                                if(sum_left > 1 || sum_right > 1)
                                        return false;
                        }
                        return true;
                }

                void display(string arr)
                {
                        for(int i=0;i<SIZE;i++)
                        {
                                for(int j=0;j<SIZE;j++)
                                {
                                        if(arr[SIZE*i+j]=='1')cout<<"Q ";
                                        else cout<<"_ ";
                                }
                                cout<<'\n';
                        }
                }
};

int main(){
        EightQueens obj;
        ChessBoard sol = obj.initialise();
        priority_queue<ChessBoard, vector<ChessBoard>, Compare> ucs;
        int count = 1;
        ucs.push(sol);

        while(!(ucs.empty()))
        {

                ChessBoard chs = ucs.top();
                ucs.pop();
                string ans = chs.getBoard();


                if(!(obj.isValid(ans)))continue;


                int i = obj.find(ans);


                if(i==sizeof(obj))
                {
                        cout<<"Solution no:  "<<count<<"\n";
                        obj.display(ans);
                        cout<<"-----------------------\n";
                        count++;
                }
                else
                {
                        for(int j=0;j<SIZE;j++)
                        { 
                                ans = ans.substr(0, SIZE*i+j)+"1"+ans.substr(SIZE*i+j+1);
                                ucs.push(ChessBoard(ans, chs.getCost()+1));
                                ans = chs.getBoard();
                        }
                }

        }
        return 0;
}
