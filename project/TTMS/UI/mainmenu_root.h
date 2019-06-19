#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "dboper.h"
namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

    void on_add_user_2_clicked();

    void on_select_user_clicked();

    void on_select_cancel_clicked();

    void on_delete_user_clicked();

    void on_modify_user_clicked();

    void on_delete_cancel_clicked();

    void on_modify_cancel_clicked();

    void on_add_cancel_clicked();

    void on_add_room_clicked();

    void on_add_roomcancel_clicked();

    void on_delete_room_clicked();

    void on_delete_roomcancel_clicked();

    void on_update_room_clicked();

    void on_update_roomcancel_clicked();

    void on_select_room_clicked();

    void on_select_roomcancel_clicked();

private:
    Ui::MainMenu *ui;
    Dboper db;
};

#endif // MAINMENU_H
