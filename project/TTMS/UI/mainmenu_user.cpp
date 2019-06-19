#include "mainmenu_user.h"
#include "ui_mainmenu_user.h"
#include "dboper.h"
#include <QMessageBox>
#include <QAction>
#include <QDateTime>

mainmenu_user::mainmenu_user(QString Name,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainmenu_user)
{
    ui->setupUi(this);
    UserName = Name;
    ui->select_personPasswd->setEchoMode(QLineEdit::Password);
    ui->update_userPasswd->setEchoMode(QLineEdit::Password);
    ui->user_Info->setVisible(false);
    ui->update_Info->setVisible(false);
    ui->widget->setVisible(false);
    ui->select_ticketImage->setVisible(false);



}

void mainmenu_user::reshow() {
    this->show();
}
mainmenu_user::~mainmenu_user()
{
    delete ui;
}

void mainmenu_user::on_pushButton_clicked()
{
    //得到该电影的所有演出计划并显示在屏幕上
    ScheduleData data = db.SelectSche(ui->select_ticketMovie->text());
    if(data.scheduleId == 0)
        QMessageBox::information(nullptr, "失败", "近期无此片场次", QMessageBox::Ok, QMessageBox::Ok);
    else {
        qDebug() << data.beginTime;
        qDebug() << data.endTime;
        QDateTime start = QDateTime::fromString(data.beginTime,"yyyy-MM-dd hh:mm:ss");
        QDateTime end = QDateTime::fromString(data.endTime,"yyyy-MM-dd hh:mm:ss");

        ui->label_11->setText(db.SelectRoom(data.roomId).roomName);
        ui->label_13->setText(start.toString("MM-dd hh:mm:ss"));
        ui->label_14->setText(end.toString("MM-dd hh:mm:ss"));
        ui->label_15->setText(QString::number(data.price));

        ui->select_ticketImage->setPixmap(db.SelectMovie(data.movieId).poster);
        ui->select_ticketImage->setScaledContents(true);

        ui->widget->setVisible(true);
        ui->select_ticketImage->setVisible(true);
    }
}

void mainmenu_user::on_pushButton_5_clicked()
{
    //根据用户名获取密码并验证密码是否正确
    UserData data = db.SelectUser(this->UserName);
    if(data.userPasswd != ui->select_personPasswd->text())
        QMessageBox::information(nullptr, "失败", "密码错误", QMessageBox::Ok, QMessageBox::Ok);
    else {
        //获取用户信息
        UserData data = db.SelectUser(UserName);
        ui->user_Name->setText(data.userName);
        ui->user_Passwd->setText(data.userPasswd);
        ui->user_Type->setText(QString::number(data.userType));
        ui->user_Mail->setText(data.userMail);
        ui->user_Info->setVisible(true);
        QMessageBox::information(nullptr, "成功", "密码正确", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void mainmenu_user::on_pushButton_7_clicked()
{
    //根据用户名获取密码并验证密码是否正确
        UserData data = db.SelectUser(this->UserName);

        if(data.userPasswd != ui->update_userPasswd->text())
            QMessageBox::information(nullptr, "失败", "密码错误", QMessageBox::Ok, QMessageBox::Ok);
        else {
            ui->update_Info->setVisible(true);
            QMessageBox::information(nullptr, "成功", "密码正确", QMessageBox::Ok, QMessageBox::Ok);
        }
}

void mainmenu_user::on_pushButton_9_clicked()
{

    //设置用户信息
    UserData data;
    data.userName = ui->update_Name->text();
    data.userPasswd = ui->update_Passwd->text();

    data.userMail = ui->update_Mail->text();

    if(db.UpdateUser(data.userName,data.userPasswd,data.userMail))
        QMessageBox::information(nullptr, "成功", "修改成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(nullptr, "失败", "修改失败", QMessageBox::Ok, QMessageBox::Ok);
}

void mainmenu_user::on_pushButton_8_clicked()
{

}

void mainmenu_user::on_pushButton_3_clicked()
{
    //跳转到买票界面
    this->hide();
    QString Name = ui->label_11->text();
    ticket_ui = new ticket(Name);
    connect(ticket_ui,&ticket::Return,this,&mainmenu_user::reshow);
    ticket_ui->show();

}
