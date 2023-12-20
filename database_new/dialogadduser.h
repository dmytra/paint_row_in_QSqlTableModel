#ifndef DIALOGADDUSER_H
#define DIALOGADDUSER_H

#include <QDialog>

#include <database.h>

namespace Ui {
class DialogAddUser;
}

class DialogAddUser : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddUser(QWidget *parent = 0);
    ~DialogAddUser();

private:
    Ui::DialogAddUser *ui;
};

#endif // DIALOGADDUSER_H
