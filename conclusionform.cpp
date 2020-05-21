#include "conclusionform.h"
#include "ui_conclusionform.h"

ConclusionForm::ConclusionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConclusionForm)
{
    ui->setupUi(this);
}

void ConclusionForm::loadTextInAdminMode(bool isAdmin)
{
    ui->textForm->setEnabled(isAdmin);
    ui->updateDataBox->setHidden(!isAdmin);
}

ConclusionForm::~ConclusionForm()
{
    delete ui;
}

void ConclusionForm::on_updateDataBox_clicked(QAbstractButton *button)
{
    close();
}
