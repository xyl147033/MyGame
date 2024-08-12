#ifndef GAMEFUNCTION_H
#define GAMEFUNCTION_H

#include <QList>
#include <QVector>

class GameFunction
{
public:
    GameFunction();
    // 用BFS算法搜索邻域中相同level的格子
    // x,y:要搜索的位置
    // board:当前局面状态
    // searched:已经搜索过的格子
    // 返回值:与x,y,相同level的格子数量，包括x,y
    static QList<QList<int>> bfs(int x,int y,const QList<QList<int>>& board,QList<QList<bool>>& searched);
private:
    static int searchX[4];
    static int searchY[4];
};

#endif // GAMEFUNCTION_H
