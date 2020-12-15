#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "qdebug.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->NoWallsButton->setChecked(true);
    ui->SinglePlayerButton->setChecked(true);
    map = new Map();
    connect(ui->NoWallsButton, &QRadioButton::clicked, map, QOverload<>::of(&Map::noWalls));
    connect(ui->SurroundingWallsButton, &QRadioButton::clicked, map, QOverload<>::of(&Map::surroundingWalls));
    connect(ui->SinglePlayerButton, &QRadioButton::clicked, map, QOverload<>::of(&Map::singlePlayer));
    connect(ui->DoublePlayersButton, &QRadioButton::clicked, map, QOverload<>::of(&Map::doublePlayers));
    connect(ui->TriplePlayersButton, &QRadioButton::clicked, map, QOverload<>::of(&Map::triplePlayers));
}
void SettingsDialog::accept() {
    map->init();
    map->show();
    this->hide();
}
SettingsDialog::~SettingsDialog()
{
    delete map;
    delete ui;
}
