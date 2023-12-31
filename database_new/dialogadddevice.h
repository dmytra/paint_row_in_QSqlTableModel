#ifndef DIALOGADDDEVICE_H
#define DIALOGADDDEVICE_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QDataWidgetMapper>
#include <QMessageBox>

#include <database.h>

namespace Ui {
class DialogAddDevice;
}

class DialogAddDevice : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddDevice(int row = -1, int column = -1, QWidget *parent = 0);
    ~DialogAddDevice();

signals:
    void signalReady();

private slots:
    void on_buttonBox_accepted();
    void updateButtons(int row);

private:
    Ui::DialogAddDevice *ui;
    QSqlQueryModel      *model;
    QDataWidgetMapper   *mapper;

private:
    void setupModel();
    void createUI();
    void accept();
};

#endif // DIALOGADDDEVICE_H
