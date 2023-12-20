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

    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
     * и инициализировать подключение к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Метод для инициализации модеи представления данных
 * */
void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
     * и инициализировать подключение к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();

    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    model = new TableModel(this);
    model->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
    ui->tableView->setModel(model);     // Устанавливаем модель на TableView
    ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    //ui->tableView->resizeColumnsToContents();
    ui->tableView->sortByColumn(0,Qt::AscendingOrder); //https://stackoverflow.com/questions/45356682/qtableview-format-individual-row-and-columns
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,120);
        ui->tableView->setColumnWidth(2,150);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    model->select(); // Делаем выборку данных из таблицы
}

void MainWindow::on_pushButton_add_4_line_in_DB_clicked()
{

    /* После чего производим наполнение таблицы базы данных
     * контентом, который будет отображаться в TableView
     * */
    for(int i = 0; i < 4; i++){
        QVariantList data;
        quint32 v = QRandomGenerator::global()->bounded(256);

        int random = v; //qrand(); // Получаем случайные целые числа для вставки а базу данных
        data.append(QDate::currentDate()); // Получаем текущую дату для вставки в БД
        data.append(QTime::currentTime()); // Получаем текущее время для вставки в БД
        // Подготавливаем полученное случайное число для вставки в БД
        data.append(random);
        // Подготавливаем сообщение для вставки в базу данных
        data.append("Получено сообщение от " + QString::number(random));
        // Вставляем данные в БД
        db->inserIntoTable(data);
    }
    on_pushButton_view_DB_clicked();
}

void MainWindow::on_pushButton_delete_DB_clicked()
{


    /* В данном случае используется формирование сырого SQL-запроса
     * с последующим его выполнением.
     * */
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



    /* Инициализируем модель для представления данных
     * с заданием названий колонок
     * */
    this->setupModel(TABLE,
                     QStringList() << trUtf8("id")
                                   << trUtf8("Дата")
                                   << trUtf8("Время")
                                   << trUtf8("Рандомное число")
                                   << trUtf8("Сообщение")
               );
    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();
}

void MainWindow::on_pushButton_Open_DB_clicked()
{
    QString tmpCurrentPath = QDir().currentPath();
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir().currentPath(), "All Files (*.*)");
    if (!fileName.isEmpty()) {
        // do something with the selected file

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
            //https://stackoverflow.com/questions/23160959/qfile-to-qbytearray-save-file-name

        on_pushButton_view_DB_clicked();
    }
}

void MainWindow::on_pushButton_Save_DB_clicked()
{
    QString tmpCurrentPath = QDir().currentPath();

    //QCoreApplication::applicationDirPath()
    qDebug() << QDir().currentPath()+"/"+DATABASE_NAME;
        QDir().currentPath();
        QString fileName = QFileDialog::getSaveFileName(this, "Save File", QDir().currentPath()+"/"+DATABASE_NAME, "All Files (*.*)");
        if (!fileName.isEmpty()) {
            // save contents to the selected file
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

