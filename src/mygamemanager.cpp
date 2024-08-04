#include "mygamemanager.h"
#include <QDebug>

MyGameManager::MyGameManager(QObject *parent)
    : QObject{parent}
{
    const QList<int> items = {1, 2, 4, 5, 2,
                              3, 3, 1, 3, 1,
                              1, 1, 2, 2, 3,
                              2, 3, 1, 4, 3,
                              1, 2, 1, 2, 2};
    setlevelItems(items);

    for(int i=0;i<5;i++){
        QList<int> row;
        QList<int> row2;
        for(int j=0;j<5;j++){
            row.push_back(items[i*5+j]);
            row2.push_back(i*5+j);
        }
        matrix_.push_back(row);
        matrix_index_.push_back(row2);
    }
}

void MyGameManager::dragEvent(int index){
    // 获取当前移动格子在矩阵中的位置
    auto locate = indexToMatrixLocate(index);
    if(locate.contains(-1)){
        return;
    }

    // 计算需要下坠的方块
    int x = locate[0],y = locate[1];
    QList<int> needToMove;
    // 获取需要下落方块的index
    for(int i=x-1;i>=0;i--){
        needToMove.push_back(matrix_index_[i][y]);
    }
    // 重新调整对应关系
    for(int i=x;i>=1;i--){
        matrix_index_[i][y] = matrix_index_[i-1][y];
    }
    matrix_index_[0][y] = index;
    // 下落动画

}

void MyGameManager::clickEvent(int  index){

}

QList<int> MyGameManager::indexToMatrixLocate(int indexNum){

    for(int i =0;i<matrix_index_.size();i++){
        auto it = std::find_if(matrix_index_[i].begin(),matrix_index_[i].end(),[indexNum](int arg){return arg == indexNum;});
        if(it!=matrix_index_[i].end()){
            int j = std::distance(matrix_index_[i].begin(),it);
            return QList<int>{i,j};
        }
    }
    return QList<int>{-1,-1};


}
