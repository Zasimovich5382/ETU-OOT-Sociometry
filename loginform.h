#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

namespace Ui {
class LoginForm;
}

enum ROLE {
    USER,
    ADMIN
};

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

signals:
    void on_setRole(enum ROLE);


private slots:
    void on_signIn_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
