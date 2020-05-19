#include "participantitem.h"

ParticipantItem::ParticipantItem(QString &participantInfo, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    this->like = new QCheckBox("+");
    this->dislike = new QCheckBox("-");
    this->participantInfo = new QLabel(participantInfo);
    horizontalLayout->addWidget(this->participantInfo);
    horizontalLayout->addWidget(this->like);
    horizontalLayout->addWidget(this->dislike);
    setLayout(horizontalLayout);
}

QString ParticipantItem::getParticipantInfo()
{
    return this->participantInfo->text();
}

ParticipantItem::~ParticipantItem(){
    delete like;
    delete dislike;
    delete participantInfo;
}
