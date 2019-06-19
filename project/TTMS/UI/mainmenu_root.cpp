#include "mainmenu_root.h"
#include "ui_mainmenu.h"

#include <QTabWidget>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QMessageBox>
MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);


}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_clicked()
{

}

void MainMenu::on_pushButton_9_clicked()
{

}

void MainMenu::on_add_user_2_clicked()
{
   //添加用户
   int type;
   if(ui->add_root->isChecked())
       type = 1;
   else if(ui->add_boos->isChecked())
       type = 2;
   else {
       type = 3;
   }

   if(db.AddUser(ui->add_userName->text(),ui->add_userPasswd->text(),ui->add_userMail->text(),type))
       QMessageBox::information(nullptr, "成功", "添加成功", QMessageBox::Ok, QMessageBox::Ok);
   else {
       QMessageBox::information(nullptr, "失败", "添加失败", QMessageBox::Ok, QMessageBox::Ok);
   }
}


void MainMenu::on_select_user_clicked()
{
    //查询用户信息
   ui->select_text->setText(db.SelectUser(ui->select_userName->text()).to_string());

}


void MainMenu::on_select_cancel_clicked()
{
    ui->select_userName->setText("");
}

void MainMenu::on_delete_user_clicked()
{

    if(db.DeleteUser(ui->delete_userName->text()))
        QMessageBox::information(nullptr, "成功", "删除成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(nullptr, "失败", "删除失败", QMessageBox::Ok, QMessageBox::Ok);
}

void MainMenu::on_modify_user_clicked()
{
    if(db.UpdateUser(ui->modify_userName->text(),ui->modify_userPasswd->text(),ui->modify_userMail->text()))
        QMessageBox::information(nullptr, "成功", "更新成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(nullptr, "失败", "更新失败", QMessageBox::Ok, QMessageBox::Ok);
}

void MainMenu::on_delete_cancel_clicked()
{
    ui->delete_userName->setText("");
}

void MainMenu::on_modify_cancel_clicked()
{
    ui->modify_userName->setText("");
    ui->modify_userPasswd->setText("");
    ui->modify_userMail->setText("");
}

void MainMenu::on_add_cancel_clicked()
{
    ui->add_userName->setText("");
    ui->add_userPasswd->setText("");
    ui->add_userMail->setText("");
    ui->add_root->setChecked(false);
    ui->add_boos->setChecked(false);
    ui->add_user->setChecked(true);
}



void MainMenu::on_add_room_clicked()
{
    if(db.AddRoom(ui->add_roomName->text(),ui->add_roomRow->text().toInt(),ui->add_roomCol->text().toInt()))
        QMessageBox::information(nullptr, "成功", "添加成功", QMessageBox::Ok, QMessageBox::Ok);
    else {
        QMessageBox::information(nullptr, "失败", "添加失败", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainMenu::on_add_roomcancel_clicked()
{
    ui->add_roomName->setText("");
    ui->add_roomRow->setText("");
    ui->add_roomCol->setText("");
}

void MainMenu::on_delete_room_clicked()
{
    if(db.DeleteRoom(ui->delete_roomName->text()))
        QMessageBox::information(nullptr, "成功", "删除成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(nullptr, "失败", "删除失败", QMessageBox::Ok, QMessageBox::Ok);
}


void MainMenu::on_delete_roomcancel_clicked()
{
    ui->delete_roomName->setText("");
}

void MainMenu::on_update_room_clicked()
{
    if(db.UpdateRoom(ui->update_roomName->text(),ui->update_roomRow->text().toInt(),ui->update_roomCol->text().toInt()))
        QMessageBox::information(nullptr, "成功", "更新成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(nullptr, "失败", "更新失败", QMessageBox::Ok, QMessageBox::Ok);
}


void MainMenu::on_update_roomcancel_clicked()
{
    ui->update_roomName->setText("");
    ui->update_roomRow->setText("");
    ui->update_roomCol->setText("");
}

void MainMenu::on_select_room_clicked()
{
    ui->select_roomText->setText(db.SelectRoom(ui->select_roomName->text()).to_string());
}


void MainMenu::on_select_roomcancel_clicked()
{
    ui->select_roomName->setText("");
}
