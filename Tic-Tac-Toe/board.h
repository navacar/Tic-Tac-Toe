#ifndef BOARD_H
#define BOARD_H

#include <QImage>
#include <QPainter>
#include <QRect>

class Board
{
private:
    void SetBoard();


public:
    enum GameConditions
    {
        SteelInProcces = -1,
        SecondWin = 0,
        FirstWin = 1,
        NoWinner = 2
    };


    Board();
    void Draw(QPainter *painter);
    void SetBoardSize(int size);
    bool GetClick(QPoint pos);

    QVector<QVector<GameConditions>>* GetBoardDataPointer();
    QPoint GetRectCenter(int i, int j);

    GameConditions Win();

private:
    QVector<QVector<QRect>> boardRects;
    QVector<QVector<GameConditions>> boardData;

    int boardSize;
    bool isSizeSetted;
    bool isPlayerOne;
    int moveCounter;
};

#endif // BOARD_H
