#include "ticket.h"
#include "ui_ticket.h"
#include "dboper.h"
ticket::ticket(QString Name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ticket)
{
    ui->setupUi(this);

    //得到演出厅座位情况
    RoomData data = db.SelectRoom(Name);
    //根据座位情况初始化tableWidget
    ui->tableWidget->setColumnCount(data.cols);
    ui->tableWidget->setColumnCount(data.rows);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);

    QTableWidgetItem *item = new QTableWidgetItem();
        item->setBackground(QBrush(QColor(Qt::lightGray)));

    for(int i = 0;i < data.cols;++i)
        for(int j = 0;j < data.rows;++j)
            if(data.distrbute.at(i*data.cols+j) == '1') {
                QTableWidgetItem *item = new QTableWidgetItem("有");

                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
                ui->tableWidget->setItem(i,j,item);
            }
            else {
                QTableWidgetItem *item = new QTableWidgetItem("无");

                item->setFlags(item->flags() & (~Qt::ItemIsEditable));
                ui->tableWidget->setItem(i,j,item);
            }

    ui->tableWidget->setVisible(true);
}

ticket::~ticket()
{
    delete ui;
}
