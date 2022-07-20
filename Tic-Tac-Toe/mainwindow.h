#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QVector>

#include "board.h"
#include "enemy.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum GameMode
    {
        Undefined = 0,
        PlayerVsPlayer = 1,
        PlayerVsComputer = 2,
        ComputerVsComputer = 3
    };

    void WinCheck();
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    void ChoseGameModeMessage();
    void ChoseBoardSizeMessage();
    void GameOverFunction(Board::GameConditions whoWin);

    void DeleteEnemies();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
   void Update();

   void on_actionSmall_triggered();
   void on_actionMedium_triggered();
   void on_actionLarge_triggered();

   void on_playerVSPlayer_triggered();
   void on_playerFirst_triggered();
   void on_playerSecond_triggered();
   void on_PcVsPC_triggered();

private:
   Board* newBoard;
   Enemy* firstEnemy;
   Enemy* secondEnemy;

   QVector<QVector<QRect>> boardRects;

   int boardSize;
   int clickCounter;

    GameMode currentGameMode;

    bool isComputerMove;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
