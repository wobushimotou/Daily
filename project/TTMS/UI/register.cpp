#include "register.h"
#include "ui_register.h"
#include "dboper.h"
#include <QMessageBox>
Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    if(db.UserRegister(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text())) {
        QMessageBox::information(nullptr, "成功", "注册成功", QMessageBox::Ok, QMessageBox::Ok);
        //返回到登录页面

        emit Return();
        this->close();
    }
    else {
        QMessageBox::information(nullptr, "失败", "注册失败", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void Register::on_pushButton_2_clicked()
{
    //返回到登录页面
    emit Return();
    this->close();
    db.~Dboper();
}

