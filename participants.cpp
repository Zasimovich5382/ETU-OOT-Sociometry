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

void Participants::closeEvent (QCloseEvent *event)
{
    // on close update the graph
}

void Participants::setGraph(ERContainer<std::string> *graph)
{
    this->graph = graph;
}

void Participants::on_addParticipantBtn_clicked()
{
    QString name = ui->nameLine->text();

    if(ui->femaleRB->isChecked()){
        graph->addEntity(name.toStdString(), FEMALE);
    }
    else {
        graph->addEntity(name.toStdString(), MALE);
    }

     participantFormAddNew(name);

    // send signal to update graph
}

void Participants::on_saveChoicesBtn_clicked()
{
    //iterate through list of QScrollArea which are entities and foreach add new relation or update the previous

}

void Participants::initParticipantsList()
{
    ui->chooseParticipantBox->clear();
    ui->participantsListWidget->clear();

    for(auto entity = graph->begin(); entity != graph->end(); entity++){
        QString name = QString::fromStdString(entity->getName());
        participantFormAddNew(name);
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

void Participants::participantFormAddNew(QString &name)
{
    ui->chooseParticipantBox->addItem(name);

    //Participant's list
    QListWidgetItem *participant = new QListWidgetItem();
    ParticipantItem *participantItem = new ParticipantItem(name);
    participant->setSizeHint(participantItem->minimumSizeHint());
    participantItem->setParent(this);
    ui->participantsListWidget->addItem(participant);
    ui->participantsListWidget->setItemWidget(participant, participantItem);
}
