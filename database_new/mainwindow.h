#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
/* Подключаем заголовочный файл для работы с информацией, которая помещена в базу данных */
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

private:
    Ui::MainWindow  *ui;
    /* В проекте используются объекты для взаимодействия с информацией в базе данных
     * и моделью представления таблицы базы данных
     * */
    DataBase    *db;
    TableModel  *model;

private:
    /* Также присутствуют два метода, которые формируют модель
     * и внешний вид TableView
     * */
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};

#endif // MAINWINDOW_H
