#include "mainmenu_manager.h"
#include "ui_mainmenu_manager.h"
#include <QMessageBox>
#include "dboper.h"
#include <QString>
mainmenu_manager::mainmenu_manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainmenu_manager)
{
    ui->setupUi(this);
     ui->add_scheStart->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
}

mainmenu_manager::~mainmenu_manager()
{
    delete ui;
}

void mainmenu_manager::on_select_movie_clicked()
{
    MovieData data = db.SelectMovie(ui->select_movieName->text());
    if(data.movieId == 0) {
        QMessageBox::information(nullptr, "失败", "查无此片", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    ui->label_35->setText(data.title);
    ui->label_34->setText(QString::number(data.rating));
    ui->select_movieActor->setText(data.directors);
    ui->select_movieMain->setText(data.actors);
    ui->select_movieTyep->setText(data.genres);
    ui->select_movieCountry->setText(data.country);
    ui->select_movieTime->setText(QString::number(data.runTime));
    ui->select_movieSimple->setText(data.plotSimple);
    ui->select_movieImage->setPixmap(QPixmap(data.poster));

}

void mainmenu_manager::on_add_movie_clicked()
{
    MovieData data;
    data.title = ui->add_movieName->text();
    data.rating = ui->add_movieRating->text().toDouble();
    data.directors = ui->add_movieDirectors->text();
    data.actors = ui->add_movieActors->text();
    data.genres = ui->add_movieType->text();
    data.country = ui->add_movieCountry->text();
    data.runTime = ui->add_movieTime->text().toInt();
    data.plotSimple = ui->add_movieSmple->text();
    data.poster = ui->add_movieImage->text();
    if(db.AddMovie(data))
        QMessageBox::information(nullptr, "成功", "添加成功", QMessageBox::Ok, QMessageBox::Ok);
    else
         QMessageBox::information(nullptr, "失败", "添加失败", QMessageBox::Ok, QMessageBox::Ok);
}

void mainmenu_manager::on_delete_movie_clicked()
{
    if(db.DeleteMovie(ui->delete_movieName->text()))
        QMessageBox::information(nullptr, "成功", "删除成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(nullptr, "失败", "删除失败", QMessageBox::Ok, QMessageBox::Ok);
}

void mainmenu_manager::on_update_movie_clicked()
{
    MovieData data;
    data.title = ui->update_movieName->text();
    data.rating = ui->update_movieRating->text().toDouble();
    data.directors = ui->update_movieDirectors->text();
    data.actors = ui->update_movieActors->text();
    data.genres = ui->update_movieType->text();
    data.country = ui->update_movieCountry->text();
    data.runTime = ui->update_movieTime->text().toInt();
    data.plotSimple = ui->update_movieSmple->text();
    data.poster = ui->update_movieImage->text();
    if(db.UpdateMovie(data))
        QMessageBox::information(nullptr, "成功", "更新成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(nullptr, "失败", "更新失败", QMessageBox::Ok, QMessageBox::Ok);
}


void mainmenu_manager::on_add_sche_clicked()
{
    //根据影片名和演出厅名得到对应的Id
    ScheduleData data;
    data.movieId = db.SelectMovie(ui->add_scheMovie->text()).movieId;
    data.roomId = db.SelectRoom(ui->add_scheRoom->text()).roomId;

    data.beginTime = ui->add_scheStart->dateTime().toString("yyyy-MM-dd hh:mm:ss");

    data.endTime = ui->add_scheStart->dateTime().addSecs(db.SelectMovie(ui->add_scheMovie->text()).runTime*60).toString("yyyy-MM-dd hh:mm:ss");
    data.price = ui->add_schePrice->text().toInt();


    if(db.AddSche(data))
        QMessageBox::information(nullptr, "成功", "插入成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(nullptr, "失败", "插入失败", QMessageBox::Ok, QMessageBox::Ok);
}

void mainmenu_manager::on_delete_sche_clicked()
{
    QString roomName = db.SelectRoom(ui->delete_scheRoom->text()).roomName;

    if(db.DeleteSche(roomName,ui->delete_shceStart->dateTime()) == true)
        QMessageBox::information(nullptr, "成功", "删除成功", QMessageBox::Ok, QMessageBox::Ok);
    else
        QMessageBox::information(nullptr, "失败", "删除失败", QMessageBox::Ok, QMessageBox::Ok);
}

void mainmenu_manager::on_update_sche_clicked()
{
    //根据影片名称和开始时间获取演出计划数据
    qDebug() << ui->label_48->text();
    if(ui->label_48->text() == "影片名称") {
        ScheduleData data;

        data.scheduleId = db.SelectSche(db.SelectRoom(ui->update_scheRoom->text()).roomName, \
                                    ui->update_scheStart->dateTime()).scheduleId;

        if(data.scheduleId != 0) {
            QMessageBox::information(nullptr, "成功", "获取演出计划信息成功", QMessageBox::Ok, QMessageBox::Ok);
            ui->label_48->setText("新影片名称");
            ui->label_49->setText("新演出厅名称");
            ui->label_30->setText("新售价");
            ui->label_50->setText("新开始时间");
            return;
        }
        else
            QMessageBox::information(nullptr, "失败", "获取演出计划信息失败", QMessageBox::Ok, QMessageBox::Ok);
    }
    else {//根据演出计划数据修改
        ScheduleData data;
        data.roomId = db.SelectRoom(ui->update_scheRoom->text()).roomId;
        data.movieId = db.SelectMovie(ui->update_scheMovie->text()).movieId;
        data.beginTime = ui->update_scheStart->dateTime().toString("yyyy-MM-dd hh:mm:ss");
        data.endTime = ui->update_scheStart->dateTime().addSecs(db.SelectMovie(ui->add_scheMovie->text()).runTime*60).toString("yyyy-MM-dd hh:mm:ss");
        data.scheduleId = db.SelectSche(db.SelectRoom(ui->update_scheRoom->text()).roomName, \
                                    ui->update_scheStart->dateTime()).scheduleId;
        data.price = ui->update_schePrice->text().toInt();

        if(db.UpdateSche(data) == true)
            QMessageBox::information(nullptr, "成功", "更新成功", QMessageBox::Ok, QMessageBox::Ok);
        else
            QMessageBox::information(nullptr, "失败", "更新失败", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void mainmenu_manager::on_select_sche_clicked()
{
    ScheduleData data = db.SelectSche(ui->select_scheName->text());
    if(data.scheduleId == 0)
        QMessageBox::information(nullptr, "失败", "查询失败", QMessageBox::Ok, QMessageBox::Ok);

    ui->select_scheMovie->setText(db.SelectMovie(data.movieId).title);
    ui->select_scheRoom->setText(db.SelectRoom(data.roomId).roomName);
    ui->select_scheStart->setDateTime(QDateTime::fromString(data.beginTime,"yyyy-MM-dd hh:mm:ss"));
    ui->select_scheEnd->setDateTime(QDateTime::fromString(data.endTime,"yyyy-MM-dd hh:mm:ss"));
    ui->select_schePrice->setText(QString::number(data.price));
}
