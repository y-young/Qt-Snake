#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "settingsdialog.h"
#include "map.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Map* map;
    SettingsDialog *settingsDialog;

protected:
    void keyPressEvent(QKeyEvent * event);

public slots:
    void newGame();
    void load();
    void quit();
};
#endif // MAINWINDOW_H
