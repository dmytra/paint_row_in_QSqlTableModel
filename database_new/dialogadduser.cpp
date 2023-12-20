#include "dialogadduser.h"
#include "ui_dialogadduser.h"

DialogAddUser::DialogAddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddUser)
{
    ui->setupUi(this);
}

DialogAddUser::~DialogAddUser()
{
    delete ui;
}
