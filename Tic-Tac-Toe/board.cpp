#include "board.h"

const int rectsSize = 85;

Board::Board()
      : boardSize(0)
      , isSizeSetted(false)
      , isPlayerOne(true)
      , moveCounter(0)
{
}


void Board::Draw(QPainter *painter)
{
    if (isSizeSetted)
    {
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                painter->drawRect(boardRects[i][j]);

                if (boardData[i][j] == SecondWin)
                {
                    painter->drawEllipse(boardRects[i][j].center(), 50 / 2, 50 / 2);
                }
                else if (boardData[i][j] == FirstWin)
                {
                    painter->drawLine(QLine(boardRects[i][j].x() + 10, boardRects[i][j].y() + 10,
                                            boardRects[i][j].x() + rectsSize - 10,  boardRects[i][j].y() + rectsSize - 10));
                    painter->drawLine(QLine(boardRects[i][j].x() + rectsSize - 10, boardRects[i][j].y() + 10,
                                            boardRects[i][j].x() + 10,  boardRects[i][j].y() + rectsSize - 10));
                }
            }
        }
    }
}


void Board::SetBoardSize(int size)
{
    boardSize = size;

    boardRects.clear();
    boardData.clear();
    moveCounter = 0;
    SetBoard();
    isSizeSetted = true;
}


void Board::SetBoard()
{
    int x = 0;
    int y = 0;
    int xSaver = 0;
    isPlayerOne = true;

    if (boardSize == 3)
    {
        xSaver = 190;
        y = 100;
    }
    else if (boardSize == 4)
    {
        xSaver = 150;
        y = 70;
    }
    else
    {
        xSaver = 105;
        y = 30;
    }

    x = xSaver;

    for (int i = 0; i < boardSize; i++)
    {
        QVector<QRect> boardVector;
        QVector<GameConditions> dataVector;

        for (int j = 0; j < boardSize; j++)
        {
            boardVector.append(QRect(x, y, rectsSize, rectsSize));
            dataVector.append(SteelInProcces);
            x += rectsSize;
        }

        boardRects.append(boardVector);
        boardData.append(dataVector);

        x = xSaver;
        y += rectsSize;
    }
}


bool Board::GetClick(QPoint pos)
{
    QRect mouseRect(pos.x(), pos.y(), 1, 1);
    bool flagToBreak = false;
    bool isClickValid = false;

    if (isSizeSetted)
    {
        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                if (boardRects[i][j].intersects(mouseRect))
                {
                    if (boardData[i][j] == SteelInProcces)
                    {
                        moveCounter++;
                        boardData[i][j] = isPlayerOne ? FirstWin : SecondWin;
                        isPlayerOne = isPlayerOne ? 0 : 1;
                        isClickValid = true;
                    }


                    flagToBreak = true;
                    break;
                }
            }

            if (flagToBreak)
            {
                break;
            }
        }
    }

    return isClickValid;
}


QVector<QVector<Board::GameConditions>>* Board::GetBoardDataPointer()
{
    return &boardData;
}


QPoint Board::GetRectCenter(int i, int j)
{
    return boardRects[i][j].center();
}


Board::GameConditions Board::Win()
{
    GameConditions result = SteelInProcces;

    if (moveCounter >= boardSize + boardSize - 1)
    {
        int counter[4] = {0, 0, 0, 0};

       for (int i = 0; i < boardSize; i++)
       {
           for (int j = 0; j < boardSize; j++)
           {
               if (boardData[i][0] == boardData[i][j] && boardData[i][j] != SteelInProcces)
               {
                   counter[0]++;
                   result = boardData[i][j];
               }
           }

           if (counter[0] == boardSize)
           {
                break;
           }
           else
           {
               result = SteelInProcces;
               counter[0] = 0;
           }

           for (int j = 0; j < boardSize; j++)
           {
               if (boardData[0][i] == boardData[j][i] && boardData[j][i] != SteelInProcces)
               {
                   counter[1]++;
                   result = boardData[j][i];
               }
           }

           if (counter[1] == boardSize)
           {
                break;
           }
           else
           {
               result = SteelInProcces;
               counter[1] = 0;
           }

           if (boardData[0][0] == boardData[i][i] && boardData[0][0] != SteelInProcces)
           {
               counter[2]++;
           }

           if (boardData[boardSize - 1][0] == boardData[boardSize - 1 - i][i] && boardData[boardSize - 1][0] != SteelInProcces)
           {
               counter[3]++;
           }
       }

       if (result == SteelInProcces)
       {
           if (counter[2] != boardSize)
           {
               counter[2] = 0;
           }
           else if (counter[2] == boardSize)
           {
               result = boardData[0][0];
           }

           if (counter[3] != boardSize)
           {
               counter[3] = 0;
           }
           else
           {
               result = boardData[boardSize - 1][0];
           }
       }

    }

    if (moveCounter == boardSize*boardSize && result == SteelInProcces)
    {
        result = NoWinner;
    }

    return result;
}

