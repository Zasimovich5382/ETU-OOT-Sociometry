#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H

#include <QWidget>

namespace Ui {
class Participants;
}

class Participants : public QWidget
{
    Q_OBJECT

public:
    explicit Participants(QWidget *parent = 0);
    ~Participants();

private:
    Ui::Participants *ui;
};

#endif // PARTICIPANTS_H
