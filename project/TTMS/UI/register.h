#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include "dboper.h"

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
signals:
    void Return();

private:
    Ui::Register *ui;
    Dboper db;
};

#endif // REGISTER_H
