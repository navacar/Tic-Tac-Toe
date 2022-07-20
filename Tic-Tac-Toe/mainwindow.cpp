#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QRect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , firstEnemy(nullptr)
    , secondEnemy(nullptr)
    , boardSize(0)
    , currentGameMode(Undefined)
    , isComputerMove(false)
    , ui(new Ui::MainWindow)
{
    QWidget::setFixedSize(QWidget::size());

    newBoard = new Board();

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start(400);
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    if (newBoard)
    {
        delete newBoard;
        newBoard = nullptr;
    }

    DeleteEnemies();

    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (boardSize >= 3 && !isComputerMove && currentGameMode != ComputerVsComputer)
        {
            if (currentGameMode == Undefined)
            {
                ChoseGameModeMessage();
            }
            else if(newBoard->GetClick(event->pos()))
            {
                isComputerMove = currentGameMode == PlayerVsPlayer ? false : true;
                WinCheck();
            }
        }
    }

    repaint();
}


void MainWindow::WinCheck()
{
    Board::GameConditions a = newBoard->Win();
    if (a != Board::SteelInProcces)
    {
        GameOverFunction(a);
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    newBoard->Draw(&painter);
}


void MainWindow::Update()
{
    if (firstEnemy && isComputerMove && currentGameMode == PlayerVsComputer)
    {
        isComputerMove = false;
        firstEnemy->MakeMove();
        WinCheck();
        repaint();
    }
    else if (currentGameMode == ComputerVsComputer && firstEnemy && secondEnemy)
    {
        if (isComputerMove)
        {
            firstEnemy->MakeMove();
            WinCheck();
            repaint();
        }
        else
        {
            secondEnemy->MakeMove();
            WinCheck();
            repaint();
        }

        isComputerMove = !isComputerMove;
    }
    else if (isComputerMove)
    {
        isComputerMove = false;
    }
}


void MainWindow::ChoseGameModeMessage()
{
    QMessageBox::information(this, "Game Mode", "Выберите режим игры");
}


void MainWindow::ChoseBoardSizeMessage()
{
    QMessageBox::information(this, "Window Size", "Сначала выберите размер доски");
}


void MainWindow::GameOverFunction(Board::GameConditions whoWin)
{
    QString winLine;

    if (whoWin == Board::FirstWin)
    {
        winLine = "Победил первый игрок!";
    }
    else if (whoWin == Board::SecondWin)
    {
        winLine = "Победил второй игрок!";
    }
    else
    {
        winLine = "Ничья";
    }

    currentGameMode = Undefined;
    DeleteEnemies();

    QMessageBox::information(this, "Result", winLine);
    newBoard->SetBoardSize(boardSize);
}


void MainWindow::DeleteEnemies()
{
    if (firstEnemy)
    {
        delete firstEnemy;
        firstEnemy = nullptr;
    }

    if (secondEnemy)
    {
        delete secondEnemy;
        secondEnemy = nullptr;
    }
    isComputerMove = false;
}


void MainWindow::on_actionSmall_triggered()
{
    currentGameMode = Undefined;
    DeleteEnemies();
    newBoard->SetBoardSize(3);
    boardSize = 3;
    repaint();
}


void MainWindow::on_actionMedium_triggered()
{
    currentGameMode = Undefined;
    DeleteEnemies();
    newBoard->SetBoardSize(4);
    boardSize = 4;
    repaint();
}


void MainWindow::on_actionLarge_triggered()
{
    currentGameMode = Undefined;
    DeleteEnemies();
    newBoard->SetBoardSize(5);
    boardSize = 5;
    repaint();
}


void MainWindow::on_playerVSPlayer_triggered()
{
    if (boardSize >= 3)
    {
        currentGameMode = PlayerVsPlayer;
        DeleteEnemies();

        newBoard->SetBoardSize(boardSize);
        repaint();
    }
    else
    {
        ChoseBoardSizeMessage();
    }
}


void MainWindow::on_playerFirst_triggered()
{
    if (boardSize >= 3)
    {
        DeleteEnemies();
        currentGameMode = PlayerVsComputer;
        firstEnemy = new Enemy(false, newBoard);
        newBoard->SetBoardSize(boardSize);
        isComputerMove = false;
        repaint();
    }
    else
    {
        ChoseBoardSizeMessage();
    }
}


void MainWindow::on_playerSecond_triggered()
{
    if (boardSize >= 3)
    {
        DeleteEnemies();
        currentGameMode = PlayerVsComputer;
        firstEnemy = new Enemy(true, newBoard);
        newBoard->SetBoardSize(boardSize);
        isComputerMove = true;
        repaint();
    }
    else
    {
        ChoseBoardSizeMessage();
    }
}


void MainWindow::on_PcVsPC_triggered()
{
    if (boardSize >= 3)
    {
        DeleteEnemies();
        currentGameMode = ComputerVsComputer;
        firstEnemy = new Enemy(true, newBoard);
        secondEnemy = new Enemy(false, newBoard);
        isComputerMove = true;
        newBoard->SetBoardSize(boardSize);
        repaint();
    }
    else
    {
        ChoseBoardSizeMessage();
    }
}

