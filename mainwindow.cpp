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
    ui->writeConclusionBtn->setHidden(true);

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
        ui->writeConclusionBtn->setHidden(false);
    }
    this->show();
}

void MainWindow::on_updateParticipantsBtn_clicked()
{
    participantsForm = new Participants();
    participantsForm->show();
}

void MainWindow::on_loadPreviousStateBtn_clicked()
{
    // load the previous conteiner state and show it
}

void MainWindow::on_saveCurrentStateBtn_clicked()
{
    // save the current contaioner state
}

void MainWindow::on_showResearchResultBtn_clicked()
{
    // show the conclusion written by admin
}

void MainWindow::on_writeConclusionBtn_clicked()
{
    // open text window and show written by admin conclusion for this graph
}
