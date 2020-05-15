#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    loginForm = new LoginForm();
    loginForm->show();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
