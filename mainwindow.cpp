#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    map = new Map();
    map->hide();
    map->pause();
    connect(ui->StartButton, &QPushButton::released, this, QOverload<>::of(&MainWindow::newGame));
    connect(ui->QuitButton, &QPushButton::released, this, QOverload<>::of(&MainWindow::quit));
}
void MainWindow::keyPressEvent(QKeyEvent* event)
{
//    if (event->key() == Qt::Key_Escape)
//    {
//        QApplication::exit(0);
//    }
//    QWidget::keyPressEvent(event);
}
void MainWindow::newGame() {
    this->hide();
    map->show();
    map->resume();
//    this->setFocusPolicy(Qt::StrongFocus);
}
void MainWindow::quit() {
    this->close();
}
MainWindow::~MainWindow()
{
    delete map;
    delete ui;
}

