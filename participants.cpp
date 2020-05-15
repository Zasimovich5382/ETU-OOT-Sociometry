#include "participants.h"
#include "ui_participants.h"

Participants::Participants(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Participants)
{
    ui->setupUi(this);
}

Participants::~Participants()
{
    delete ui;
}
