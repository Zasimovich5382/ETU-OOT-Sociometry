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
    ui->textForm->setReadOnly(!isAdmin);
}

void ConclusionForm::setText(const QString &text)
{
    ui->textForm->setPlainText(text);
}

ConclusionForm::~ConclusionForm()
{
    delete ui;
}

void ConclusionForm::on_updateDataBox_accepted()
{
    emit conclusionText(ui->textForm->toPlainText());
    close();
}

void ConclusionForm::on_updateDataBox_rejected()
{
    close();
}
