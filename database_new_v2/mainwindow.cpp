#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QRandomGenerator>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DataBase();
    db->connectToDataBase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    db = new DataBase();
    db->connectToDataBase();

    model = new TableModel(this);
    model->setTable(tableName);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //ui->tableView->resizeColumnsToContents();
    ui->tableView->sortByColumn(0,Qt::AscendingOrder); //https://stackoverflow.com/questions/45356682/qtableview-format-individual-row-and-columns
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,120);
        ui->tableView->setColumnWidth(2,150);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select();
}

void MainWindow::on_pushButton_add_4_line_in_DB_clicked()
{
    for(int i = 0; i < 4; i++){
        QVariantList data;
        quint32 v = QRandomGenerator::global()->bounded(256);
        int random = v;
        data.append(QDate::currentDate());
        data.append(QTime::currentTime());
        data.append(random);
        data.append("Получено сообщение от " + QString::number(random));
        db->inserIntoTable(data);
    }
    on_pushButton_view_DB_clicked();
}

void MainWindow::on_pushButton_delete_DB_clicked()
{
    QSqlQuery query;
    if(!query.exec( "DELETE FROM " TABLE " " )){
        qDebug() << "DataBase: error of delete " << TABLE;
        qDebug() << query.lastError().text();
    } else {
        qDebug() << "DataBase: delete " << TABLE;
    }
    on_pushButton_view_DB_clicked();
}

void MainWindow::on_pushButton_view_DB_clicked()
{

    this->setupModel(TABLE,
                     QStringList() <<  "id"
                                   << "Дата"
                                   << "Время"
                                   << "Рандом №"
                                   << "Сообщение"
               );
    this->createUI();
}

void MainWindow::on_pushButton_Open_DB_clicked()
{
    QString tmpCurrentPath = QDir().currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir().currentPath(), "All Files (*.*)");
    if (!fileName.isEmpty()) {

        QFile file(fileName);
        file.open(QIODevice::ReadOnly);

        qDebug() << "DB: " << " " << tmpCurrentPath+"/"+DATABASE_NAME << "\n" << fileName;

        QFile fileW(tmpCurrentPath+"/"+DATABASE_NAME);
        fileW.open(QIODevice::WriteOnly);

        QByteArray file_data;
        file_data = file.readAll();
        fileW.write(file_data);
        fileW.close();
        file.close();

        QDir().currentPath() = tmpCurrentPath;

        on_pushButton_view_DB_clicked();
    }
}

void MainWindow::on_pushButton_Save_DB_clicked()
{
    QString tmpCurrentPath = QDir().currentPath();

    qDebug() << QDir().currentPath()+"/"+DATABASE_NAME;
        QDir().currentPath();
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir().currentPath()+"/"+DATABASE_NAME, "All Files (*.*)");
        if (!fileName.isEmpty()) {
            qDebug() << QDir().currentPath()+"/"+DATABASE_NAME;

            QFile file(fileName);
            file.open(QIODevice::WriteOnly);

            qDebug() << "DB: " << " " << tmpCurrentPath+"/"+DATABASE_NAME << "\n" << fileName;

            QFile fileW(tmpCurrentPath+"/"+DATABASE_NAME);
            fileW.open(QIODevice::ReadOnly);

            QByteArray file_data;
            file_data = fileW.readAll();
            file.write(file_data);
            file.close();
            fileW.close();
        }

        QDir().currentPath() = tmpCurrentPath;

        on_pushButton_view_DB_clicked();
}


void MainWindow::on_pushButton_add_UP1_UP1_line_in_DB_clicked()
{
        QVariantList data;
        int random = QRandomGenerator::global()->bounded(256);
        data.append(QDate::currentDate());
        data.append(QTime::currentTime());

        data.append(random);
        data.append(ui->lineEdit_1->text() + " | " + ui->lineEdit_2->text());
        db->inserIntoTable(data);

    on_pushButton_view_DB_clicked();
}


