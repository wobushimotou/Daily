#ifndef MAINMENU_MANAGER_H
#define MAINMENU_MANAGER_H

#include <QMainWindow>
#include "dboper.h"

namespace Ui {
class mainmenu_manager;
}

class mainmenu_manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainmenu_manager(QWidget *parent = nullptr);
    ~mainmenu_manager();

private slots:
    void on_select_movie_clicked();

    void on_add_movie_clicked();

    void on_delete_movie_clicked();

    void on_update_movie_clicked();

    void on_add_sche_clicked();

    void on_delete_sche_clicked();

    void on_update_sche_clicked();

    void on_select_sche_clicked();

private:
    Ui::mainmenu_manager *ui;
    Dboper db;
};

#endif // MAINMENU_MANAGER_H
