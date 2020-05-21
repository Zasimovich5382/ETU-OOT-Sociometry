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

int ParticipantItem::getRelationType()
{
    if((this->like->isChecked() && this->dislike->isChecked()) ||
       (!this->like->isChecked() && !this->dislike->isChecked())) {
        return -1;
    }
    else {
        return this->like->isChecked();
    }
}

ParticipantItem::~ParticipantItem(){
    delete like;
    delete dislike;
    delete participantInfo;
}
