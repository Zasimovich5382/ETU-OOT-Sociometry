#include "participants.h"
#include "ui_participants.h"

Participants::Participants(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Participants)
{
    ui->setupUi(this);
    //iterate through conteiner entities and whow them in chooseParticipantBox
    //ui->chooseParticipantBox->addItems(participants);
    for (QString name : testlist){
        ui->chooseParticipantBox->addItem(name);
        this->participants.append(new ParticipantItem(name));
    }
    initParticipantsList();//to show all names

}

Participants::~Participants()
{
    delete ui;
}

void Participants::closeEvent (QCloseEvent *event)
{
    // on close update the graph
}

void Participants::on_addParticipantBtn_clicked()
{
    //create new entity and add to container
    if(ui->femaleRB->isChecked()){
        //female
    }
    else {
        //male
    }

    QString name = ui->nameLine->text();

    // send signal to update graph
}

void Participants::on_saveChoicesBtn_clicked()
{
    //iterate through list of QScrollArea which are entities and foreach add new relation or update the previous

}

void Participants::initParticipantsList()
{
    ui->participantsListWidget->clear();
    for (ParticipantItem* item: this->participants) {
        QListWidgetItem *participant = new QListWidgetItem();

        participant->setSizeHint(item->minimumSizeHint());
        item->setParent(this);
        ui->participantsListWidget->addItem(participant);
        ui->participantsListWidget->setItemWidget(participant, item);
    }
}


void Participants::on_chooseParticipantBox_currentIndexChanged(const QString &name)
{
    for (int i = 0; i < ui->participantsListWidget->count(); i++){
        QListWidgetItem* item = ui->participantsListWidget->item(i);
        ParticipantItem* widget = (ParticipantItem* )ui->participantsListWidget->itemWidget(item);
        item->setHidden(false);
        if(widget->getParticipantInfo() == name){
            item->setHidden(true);
        }
    }
}
