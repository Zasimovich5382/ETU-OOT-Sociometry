#ifndef PARTICIPANTITEM_H
#define PARTICIPANTITEM_H

#include <QWidget>
#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>

class ParticipantItem : public QWidget
{
    Q_OBJECT
public:
    explicit ParticipantItem(QString &participantInfo, QWidget *parent = nullptr);
    QString getParticipantInfo();
    ~ParticipantItem();

private:
    QCheckBox *like;
    QCheckBox *dislike;
    QLabel *participantInfo;

signals:


public slots:
};

#endif // PARTICIPANTITEM_H
