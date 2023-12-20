#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "database.h"
#include "tablemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_add_4_line_in_DB_clicked();

    void on_pushButton_delete_DB_clicked();

    void on_pushButton_view_DB_clicked();

    void on_pushButton_Open_DB_clicked();

    void on_pushButton_Save_DB_clicked();

    void on_pushButton_add_UP1_UP1_line_in_DB_clicked();

private:
    Ui::MainWindow  *ui;
    DataBase    *db;
    TableModel  *model;

private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW_H
