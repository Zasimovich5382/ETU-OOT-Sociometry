#ifndef PARTICIPANTITEM_H
#define PARTICIPANTITEM_H

#include <QWidget>
#include <QCheckBox>
#include <QRadioButton>
#include <QLabel>
#include <QHBoxLayout>

class ParticipantItem : public QWidget
{
    Q_OBJECT
public:
    explicit ParticipantItem(const QString &participantInfo, const QString& genger, int id, QWidget *parent = nullptr);
    QString getParticipantInfo();
    int getRelationType();
    void setRelationType(bool positive);
    void clearButtons();

    ~ParticipantItem();

private:
    QRadioButton *like;
    QRadioButton *dislike;
    QLabel *participantInfo;

signals:


public slots:
};

#endif // PARTICIPANTITEM_H
