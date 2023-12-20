#include "dialogadddevice.h"
#include "ui_dialogadddevice.h"

DialogAddDevice::DialogAddDevice(int row, int column, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddDevice)
{
    ui->setupUi(this);

    setupModel();

    if(row == -1 && column == -1){
        model->insertRow(model->rowCount(QModelIndex()));
        mapper->toLast();
    } else {
        mapper->setCurrentModelIndex(model->index(row,column));
    }

    createUI();
}

DialogAddDevice::~DialogAddDevice()
{
    delete ui;
}

void DialogAddDevice::setupModel(const QString &tableName)
{
    model = new QSqlRelationalTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    mapper = new QDataWidgetMapper();
    mapper->setModel(model);
    mapper->addMapping(ui->lineEditHostname, 1);
    mapper->addMapping(ui->lineEditIP, 2);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    connect(ui->previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
    connect(ui->nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
    connect(mapper, SIGNAL(currentIndexChanged(int)), this, SLOT(updateButtons(int)));
}

void DialogAddDevice::createUI()
{
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    ui->lineEditIP->setValidator(ipValidator);
}

void DialogAddDevice::on_buttonBox_accepted()
{
    QSqlQuery query;
    QString str = QString("SELECT EXISTS (SELECT " DEVICE_HOSTNAME " FROM " DEVICE
                          " WHERE ( " DEVICE_HOSTNAME " = '%1' "
                          " OR " DEVICE_IP " = '%2' )"
                          " AND id NOT LIKE '%3' )")
            .arg(ui->lineEditHostname->text(),
                 ui->lineEditIP->text(),
                 model->data(model->index(mapper->currentIndex(),0), Qt::DisplayRole).toString());

    query.prepare(str);
    query.exec();
    query.next();

    if(query.value(0) != 0){
        QMessageBox::information(this, trUtf8("Ошибка хоста"),
                                 trUtf8("Хост с таким именем или IP-адресом уже существует"));
    } else {
        mapper->submit();
        model->submit();
        emit signalReady();
        this->close();
    }
}

void DialogAddDevice::accept()
{

}

void DialogAddDevice::updateButtons(int row)
{
    ui->previousButton->setEnabled(row > 0);
    ui->nextButton->setEnabled(row < model->rowCount() - 1);
}
