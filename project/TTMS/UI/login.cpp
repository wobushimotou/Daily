#include "login.h"
#include "ui_login.h"
#include "mainmenu_root.h"
#include "ui_mainmenu.h"
#include "register.h"
#include "ui_register.h"
#include "dboper.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    connect(&register_ui,&Register::Return,this,&Login::reshow);
}

void Login::reshow() {
    this->show();
}
Login::~Login()
{
    delete ui;
    delete menu_userui;
}

void Login::on_pushButton_clicked()
{
    QString Name = ui->lineEdit->text();
    QString Passwd = ui->lineEdit_2->text();

    //登录成功
    int n = db.UserLogin(Name,Passwd);
    if(n == 1) {    //管理员
        this->close();
        menu_ui.show();
    }
    else if(n == 2) {//经理
        this->close();
        menu_rootui.show();
    }
    else if(n == 3)  {//普通用户
        this->close();
        menu_userui = new mainmenu_user(Name);
        menu_userui->show();
    }
    else {
        QMessageBox::information(NULL, "失败", "登录失败", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void Login::on_pushButton_2_clicked()
{
    //注册
    this->hide();
    register_ui.show();
}
