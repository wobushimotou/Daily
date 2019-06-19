#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QWidget>
#include "dboper.h"
#include "mainmenu_root.h"
#include "mainmenu_manager.h"
#include "mainmenu_user.h"
#include "register.h"
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void reshow();
signals:
    void Return();

private:
    Ui::Login *ui;
    MainMenu menu_ui;
    mainmenu_manager menu_rootui;
    mainmenu_user   *menu_userui;
    Register register_ui;
    Dboper db;
};

#endif // LOGIN_H
