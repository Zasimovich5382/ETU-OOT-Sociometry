#include "participantitem.h"

ParticipantItem::ParticipantItem(QString &participantInfo, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    this->like = new QRadioButton("+");
    this->dislike = new QRadioButton("-");
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
//    if((this->like->isChecked() && this->dislike->isChecked()) ||
//       (!this->like->isChecked() && !this->dislike->isChecked())) {
//        return -1;
//    }
      if (this->like->isChecked() && this->dislike->isChecked())
          return -1;
//    else {
        return this->like->isChecked();
        //    }
}

void ParticipantItem::setRelationType(bool positive)
{
    if(positive){
        this->like->setChecked(true);
    } else {
        this->dislike->setChecked(true);
    }
}

void ParticipantItem::clearButtons()
{
    this->like->setAutoExclusive(false);
    this->dislike->setAutoExclusive(false);
    this->like->setChecked(false);
    this->dislike->setChecked(false);
    this->like->setAutoExclusive(true);
    this->dislike->setAutoExclusive(true);
}





ParticipantItem::~ParticipantItem(){
    delete like;
    delete dislike;
    delete participantInfo;
}
