#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

//    connect(ui->signIn, SIGNAL(clicked()), this, SLOT(onClicked()));
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_signIn_clicked()
{
    QString login = ui->login->text();
    QString password = ui->password->text();
    if(login == "admin" && password == "admin"){
        emit on_setRole(ADMIN);
    }
    else {
        emit on_setRole(USER);
    }

    close();
}

//void LoginForm::onClicked()
//{

//}
