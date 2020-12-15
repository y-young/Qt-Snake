#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settingsDialog = new SettingsDialog();
    connect(ui->StartButton, &QPushButton::released, this, QOverload<>::of(&MainWindow::newGame));
    connect(ui->QuitButton, &QPushButton::released, this, QOverload<>::of(&MainWindow::quit));
    connect(settingsDialog, &QDialog::rejected, this, QOverload<>::of(&MainWindow::show));
}
void MainWindow::keyPressEvent(QKeyEvent*)
{
//    if (event->key() == Qt::Key_Escape)
//    {
//        QApplication::exit(0);
//    }
//    QWidget::keyPressEvent(event);
}
void MainWindow::newGame() {
    this->hide();
    settingsDialog->show();
}
void MainWindow::quit() {
    QApplication::exit(0);
}
MainWindow::~MainWindow()
{
    delete ui;
}

