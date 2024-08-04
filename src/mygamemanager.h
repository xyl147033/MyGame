#ifndef MYGAMEMANAGER_H
#define MYGAMEMANAGER_H

#include <QObject>
#include <QList>

class MyGameManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<int> levelItems READ levelItems WRITE setlevelItems NOTIFY levelItemsChanged FINAL)

public:
    explicit MyGameManager(QObject *parent = nullptr);


    // property
    QList<int> levelItems() const {
        return item_levels_;
    }
    void setlevelItems(const QList<int>& items){
        item_levels_ = items;
        emit levelItemsChanged();
    }

    Q_INVOKABLE void dragEvent(int index);
    Q_INVOKABLE void clickEvent(int index);
    // 在matrix_index_中寻找当前index所在行列，其中入口参数是方块的原生index，当期拖动或者下落后index保持不变，但其行列号改变了
    Q_INVOKABLE QList<int> indexToMatrixLocate(int indexNum);

signals:
    void levelItemsChanged();

    // 下落动画信号
    void downRectAnimation(QList<int>& needToMove,int x,int y);  // 需要移动的块，被移走的块坐标

private:



    // 维护当前每个格子中的等级
    QList<QList<int>> matrix_;

    // 维护每个格子中在原有数组中的序号
    QList<QList<int>> matrix_index_;

    // 维护格子对应level
    QList<int> item_levels_;

};

#endif // MYGAMEMANAGER_H
