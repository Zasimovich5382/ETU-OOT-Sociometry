#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    loginForm = new LoginForm();
    loginForm->show();
    ui->setupUi(this);
    ui->updateParticipantsBtn->setHidden(true);

    connect(loginForm, SIGNAL(on_setRole(ROLE)), this, SLOT(on_setRole(ROLE)));

}

MainWindow::~MainWindow()
{
    delete participantsForm;
    delete loginForm;
    delete ui;
}

void MainWindow::on_setRole(enum ROLE role)
{
    if (role == ADMIN){
        ui->updateParticipantsBtn->setHidden(false);
    }
    this->show();
}

void MainWindow::on_updateParticipantsBtn_clicked()
{
    participantsForm = new Participants();
    participantsForm->show();
}
