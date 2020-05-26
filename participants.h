#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <QWidget>
#include <QListWidgetItem>

#include "participantitem.h"
#include "ercontainer.h"

namespace Ui {
class Participants;
}

class Participants : public QWidget
{
    Q_OBJECT

public:
    explicit Participants(QWidget *parent = 0);

    void setGraph(ERContainer<std::string> *graph);
    void initParticipantsList();
    ~Participants();

private slots:
    void on_addParticipantBtn_clicked();

    void on_saveChoicesBtn_clicked();

    void on_chooseParticipantBox_currentIndexChanged(const QString &name);

signals:
    void updateGraph();


private:
    Ui::Participants *ui;
    ERContainer<std::string> *graph;
    QString current_participant;

    void participantFormAddParticipant(SocialEntity<std::string>& e);
    void participantFormSetRelations();

};

#endif // PARTICIPANTS_H
