#include "participants.h"
#include "ui_participants.h"

#include <QDebug>

Participants::Participants(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Participants)
{
    ui->setupUi(this);
    current_participant = "";
}

Participants::~Participants()
{
    delete ui;
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
    auto * e = graph->find(name.toStdString());
    participantFormAddParticipant(*e);

    emit updateGraph();
}

void Participants::on_saveChoicesBtn_clicked()
{
    std::string name = ui->chooseParticipantBox->currentText().toStdString();
    auto *entity = graph->find(name);
    //iterate through list of QScrollArea which are entities and foreach add new relation or update the previous
    for (int i = 0; i < ui->participantsListWidget->count(); i++){
        QListWidgetItem* item = ui->participantsListWidget->item(i);
        ParticipantItem* widget = (ParticipantItem* )ui->participantsListWidget->itemWidget(item);
        int relType = widget->getRelationType();
        std::string relatedName = widget->getParticipantInfo().toStdString();
        if(relType < 0 && !entity->isRelatedTo(relatedName)){ // if there were no relations and nothing is changed
            continue;
        }
        else if(entity->isRelatedTo(relatedName)){ //change or remove relation
            auto *relation = entity->getRelationWith(relatedName);
            switch (relType) {
            case -1:
                entity->removeRelation(relatedName);
                break;
            case 0:
                relation->setType(NEGATIVE);
                break;
            case 1:
                relation->setType(POSITIVE);
                break;
            default:
                break;
            }
        }
        else {
            graph->addRelation(name, relatedName, (Type)relType);
        }
    }
    emit updateGraph();

}

void Participants::initParticipantsList()
{
    ui->chooseParticipantBox->clear();
    ui->participantsListWidget->clear();
    for(auto& entity : *graph){
        participantFormAddParticipant(entity);
    }
}




void Participants::on_chooseParticipantBox_currentIndexChanged(const QString &name)
{
    current_participant = name;
    for (int i = 0; i < ui->participantsListWidget->count(); i++){
        QListWidgetItem* item = ui->participantsListWidget->item(i);
        ParticipantItem* widget = (ParticipantItem* )ui->participantsListWidget->itemWidget(item);
        item->setHidden(false);
        if(widget->getParticipantInfo() == name){
            item->setHidden(true);
        }
    }
    participantFormSetRelations();
}

void Participants::participantFormAddParticipant(SocialEntity<std::string>& e)
{
    ui->chooseParticipantBox->addItem(QString::fromStdString(e.getName()));
    QListWidgetItem *participant = new QListWidgetItem();
    QString gender = e.getGender() == MALE ? "male" : "female";
    ParticipantItem *participantItem = new ParticipantItem(QString::fromStdString(e.getName()), gender, e.getId());
    participant->setSizeHint(participantItem->minimumSizeHint());
    participantItem->setParent(this);
    ui->participantsListWidget->addItem(participant);
    ui->participantsListWidget->setItemWidget(participant, participantItem);
}

void Participants::participantFormSetRelations()
{
    auto* entity = graph->find(current_participant.toStdString());
    if (!entity) return;

    for (int i = 0; i < ui->participantsListWidget->count(); i++){
        QListWidgetItem* item = ui->participantsListWidget->item(i);
        ParticipantItem* widget = (ParticipantItem* )ui->participantsListWidget->itemWidget(item);
        widget->clearButtons();
        for(auto relation : entity->getRelations()){
            QString match = QString::fromStdString(relation.getSecondEntity()->getName());
            if(widget->getParticipantInfo() == match){
                widget->setRelationType(relation.getType() == POSITIVE);
                break;
            }
        }
    }
}
