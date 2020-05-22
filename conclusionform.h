#ifndef CONCLUSIONFORM_H
#define CONCLUSIONFORM_H

#include <QWidget>
#include <QAbstractButton>

namespace Ui {
class ConclusionForm;
}

class ConclusionForm : public QWidget
{
    Q_OBJECT

public:
    explicit ConclusionForm(QWidget *parent = 0);
    void loadTextInAdminMode(bool isAdmin);
    ~ConclusionForm();

private slots:

    void on_updateDataBox_clicked(QAbstractButton *button);

private:
    Ui::ConclusionForm *ui;
};

#endif // CONCLUSIONFORM_H
