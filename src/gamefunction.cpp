#include "gamefunction.h"
#include <QStack>

GameFunction::GameFunction()
{

}

int GameFunction::searchX[4] = {1,-1,0,0};
int GameFunction::searchY[4] = {0,0,1,-1};

QList<QList<int>> GameFunction::bfs(int x,int y,const QList<QList<int>>& board,QList<QList<bool>>& searched){
    // 首先判断入参是否有问题
    if(board.size()!= searched.size() || board.size()==0 || searched.size()==0 || board[0].size() != searched[0].size()){
        return {};
    }
    QList<QList<int>> res;
    QStack<QList<int>> temp;
    QList<int> init = {x,y};
    int val = board[x][y];
    while(temp.size()){
        auto l = temp.pop();
        res.push_back(l);
        int tempx = l[0];
        int tempy = l[1];
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                int new_x = tempx + searchX[i];
                int new_y = tempy + searchY[i];
                if(new_x>=0 && new_x < board.size() && new_y>=0 && new_y<board[0].size() &&searched[new_x][new_y]==false&& board[new_x][new_y] == val){
                    searched[new_x][new_y] = true;
                    QList<int> new_l = {new_x,new_y};
                    temp.push(new_l);
                }
            }
        }
    }
    return res;
}
