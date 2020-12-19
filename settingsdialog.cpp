#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->NoWallsButton->setChecked(true);
    ui->SinglePlayerButton->setChecked(true);
    game = new GameBoard();
    connect(ui->NoWallsButton, &QRadioButton::clicked, game, QOverload<>::of(&GameBoard::noWalls));
    connect(ui->SurroundingWallsButton, &QRadioButton::clicked, game, QOverload<>::of(&GameBoard::surroundingWalls));
    connect(ui->SinglePlayerButton, &QRadioButton::clicked, game, QOverload<>::of(&GameBoard::singlePlayer));
    connect(ui->DoublePlayersButton, &QRadioButton::clicked, game, QOverload<>::of(&GameBoard::doublePlayers));
    connect(ui->TriplePlayersButton, &QRadioButton::clicked, game, QOverload<>::of(&GameBoard::triplePlayers));
    connect(ui->OnlyAIButton, &QRadioButton::clicked, game, QOverload<>::of(&GameBoard::onlyAI));
    connect(ui->PlayerAndAIButton, &QRadioButton::clicked, game, QOverload<>::of(&GameBoard::playerAndAI));
}
void SettingsDialog::accept() {
    game->init();
    game->show();
    this->hide();
}
SettingsDialog::~SettingsDialog()
{
    delete game;
    delete ui;
}
