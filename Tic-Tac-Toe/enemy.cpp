#include "enemy.h"

Enemy::Enemy(bool isGoesFirst, Board *board)
      : boardPtr(board)
{
    if (isGoesFirst)
    {
        friendlySymbol = Board::FirstWin;
        enemySymbol = Board::SecondWin;
    }
    else
    {
        friendlySymbol = Board::SecondWin;
        enemySymbol = Board::FirstWin;
    }
}


void Enemy::MakeMove()
{
    QVector<QVector<Board::GameConditions>>* boardDataCopy = boardPtr->GetBoardDataPointer();

    if (!CheckWinCondition(boardDataCopy, friendlySymbol, enemySymbol))
    {
        if (!CheckWinCondition(boardDataCopy, enemySymbol, friendlySymbol))
        {
            ChoseRect(boardDataCopy);
        }
    }
}


void Enemy::ChoseRect(QVector<QVector<Board::GameConditions> > *data)
{
    int boardSize = data->size();
    int worthArr[boardSize][boardSize];

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            worthArr[i][j] = 0;
        }
    }

    int counter[4] = {0, 0, 0, 0};
    bool zeroInRow[4] = {false, false, false, false};

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if ((*data)[i][j] == enemySymbol)
            {
                zeroInRow[0] = true;
            }
            else
            {
                counter[0]++;
            }

            if ((*data)[j][i] == enemySymbol)
            {
                zeroInRow[1] = true;
            }
            else
            {
                counter[1]++;
            }
        }

        if ((*data)[i][i] == enemySymbol)
        {

            zeroInRow[2] = true;
        }
        else
        {
            counter[2]++;
        }

        if ((*data)[boardSize - i - 1][i] == enemySymbol)
        {
            zeroInRow[3] = true;
        }
        else
        {
            counter[3]++;
        }

        for (int k = 0; k < 4; k ++)
        {
            if (zeroInRow[k])
            {
                zeroInRow[k] = false;
                counter[k] = 0;
            }
            else if (counter[k] == boardSize)
            {
                for (int j = 0; j < boardSize; j++)
                {
                    if (k == 0)
                    {
                        worthArr[i][j]++;
                    }
                    else if (k == 1)
                    {
                        worthArr[j][i]++;
                    }
                    else if (k == 2)
                    {
                        worthArr[j][j]++;
                    }
                    else
                    {
                        worthArr[boardSize - j - 1][j]++;
                    }
                }
                counter[k] = 0;
            }
        }
    }

    int max = -1;
    QPoint rectSaver;

    for (int i = 0; i < boardSize; i++)
    {
       for (int j = 0; j < boardSize; j++)
       {
           if ((*data)[i][j] == friendlySymbol)
           {
               worthArr[i][j] = -1;
           }

           if (max <= worthArr[i][j] && (*data)[i][j] == Board::SteelInProcces)
           {
               max = worthArr[i][j];
               rectSaver = boardPtr->GetRectCenter(i, j);
           }
       }
    }

    boardPtr->GetClick(rectSaver);
}


bool Enemy::CheckWinCondition(QVector<QVector<Board::GameConditions> > *data, Board::GameConditions firstSymbol, Board::GameConditions secondSymbol)
{
    bool moveWasMade = false;
    int boardSize = data->size();
    int counter = 0;
    bool secondSymbolInRow = false;
    int emptyRectIndex;

    for (int i = 0; i < boardSize; i++)
    {
        for (int j = 0; j < boardSize; j++)
        {
            if ((*data)[i][j] == firstSymbol)
            {
                counter++;
            }
            else if ((*data)[i][j] == secondSymbol)
            {
                secondSymbolInRow = true;
                break;
            }
            else if (!secondSymbolInRow)
            {
                emptyRectIndex = j;
            }
        }

        if (counter == boardSize - 1 && !secondSymbolInRow)
        {
            moveWasMade = boardPtr->GetClick(boardPtr->GetRectCenter(i, emptyRectIndex));
            break;
        }

        secondSymbolInRow = false;
        counter = 0;

        for (int j = 0; j < boardSize; j++)
        {
            if ((*data)[j][i] == firstSymbol)
            {
                counter++;
            }
            else if ((*data)[j][i] == secondSymbol)
            {
                secondSymbolInRow = true;
                break;
            }
            else if (!secondSymbolInRow)
            {
                emptyRectIndex = j;
            }
        }

        if (counter == boardSize - 1 && !secondSymbolInRow)
        {
            moveWasMade = boardPtr->GetClick(boardPtr->GetRectCenter(emptyRectIndex, i));
            break;
        }

        secondSymbolInRow = false;
        counter = 0;
    }

    if (!moveWasMade)
    {
        for (int i = 0; i < boardSize; i++)
        {
            if ((*data)[i][i] == firstSymbol)
            {
                counter++;
            }
            else if ((*data)[i][i] == secondSymbol)
            {
                secondSymbolInRow = true;
                break;
            }
            else if (!secondSymbolInRow)
            {
                emptyRectIndex = i;
            }
        }

        if (counter == boardSize - 1 && !secondSymbolInRow)
        {
            moveWasMade = boardPtr->GetClick(boardPtr->GetRectCenter(emptyRectIndex, emptyRectIndex));
        }
        else
        {
            secondSymbolInRow = false;
            counter = 0;
        }
    }

    if (!moveWasMade)
    {
        for (int i = 0; i < boardSize; i++)
        {
            if ((*data)[boardSize - i - 1][i] == firstSymbol)
            {
                counter++;
            }
            else if ((*data)[boardSize - i - 1][i] == secondSymbol)
            {
                secondSymbolInRow = true;
                break;
            }
            else if (!secondSymbolInRow)
            {
                emptyRectIndex = i;
            }
        }

        if (counter == boardSize - 1 && !secondSymbolInRow)
        {
            moveWasMade = boardPtr->GetClick(boardPtr->GetRectCenter(boardSize - 1 - emptyRectIndex, emptyRectIndex));
        }
    }

    return moveWasMade;
}


