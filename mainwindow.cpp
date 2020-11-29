#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setFocusPolicy(Qt::StrongFocus);
    Map *map = new Map(this);
    setCentralWidget(map);
}
void MainWindow::keyPressEvent(QKeyEvent* event)
{
//    if (event->key() == Qt::Key_Escape)
//    {
//        QApplication::exit(0);
//    }
//    QWidget::keyPressEvent(event);
}
MainWindow::~MainWindow()
{
    delete ui;
}
