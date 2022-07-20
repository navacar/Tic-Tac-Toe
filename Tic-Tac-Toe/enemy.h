#ifndef ENEMY_H
#define ENEMY_H

#include <QVector>
#include "board.h"


class Enemy
{
private:
    void ChoseRect(QVector<QVector<Board::GameConditions>>* data);
    bool CheckWinCondition(QVector<QVector<Board::GameConditions>>* data, Board::GameConditions firstSymbol,
                                                                                 Board::GameConditions secondSymbol);

public:
    Enemy(bool isGoesFirst, Board *board);
    void MakeMove();

private:
    QVector<QVector<int>> rectsWorth;

    Board *boardPtr;

    Board::GameConditions enemySymbol;
    Board::GameConditions friendlySymbol;

};

#endif // ENEMY_H
