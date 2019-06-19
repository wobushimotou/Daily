#ifndef MAINMENU_USER_H
#define MAINMENU_USER_H

#include <QMainWindow>
#include <QString>
#include "dboper.h"
#include "../DBOP/Client.h"
#include "ticket.h"
namespace Ui {
class mainmenu_user;
}

class mainmenu_user : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainmenu_user(QString Id,QWidget *parent = nullptr);
    ~mainmenu_user();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_3_clicked();
    void reshow();
signals:
    void Return();

private:
    Ui::mainmenu_user *ui;
    ticket *ticket_ui;
    Dboper db;
    QString UserName;
};

#endif // MAINMENU_USER_H
