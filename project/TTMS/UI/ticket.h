#ifndef TICKET_H
#define TICKET_H

#include <QWidget>
#include "dboper.h"
namespace Ui {
class ticket;
}

class ticket : public QWidget
{
    Q_OBJECT

public:
    explicit ticket(QString Name,QWidget *parent = nullptr);
    ~ticket();
signals:
    void Return();
private:
    Ui::ticket *ui;
    Dboper db;
    int RoomId;
};

#endif // TICKET_H
