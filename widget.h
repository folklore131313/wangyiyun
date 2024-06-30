#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include "nosic.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

    static int Start_flag = 1;
static int Xun_flag = 1;
static int Ci_flag;
static int nosic_flag = 0;
static int list_row = 0;
static int now_jpg = 0;
static int ui_color = 0;

class Widget : public QWidget
{
    Q_OBJECT

public:
    QMediaPlayer *player = new QMediaPlayer(this); // Ensure player is parented to widget for proper cleanup
    QStringList musicFiles; // Manages music files instead of QMediaPlaylist
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void updateList();
    void chose_jpg(int row);
    static QString Time(qint64 time) // Time conversion utility
    {
        qint64 seconds = time / 1000;
        const qint64 minutes = seconds / 60;
        seconds -= minutes * 60;
        return QStringLiteral("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
    }
    QString durationTime;
    QString positionTime;

private slots:
    void on_toolButton_2_pressed();
    void on_toolButton_2_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_2_released();
    void on_toolButton_4_released();
    void on_toolButton_4_pressed();
    void on_exit_bnt_clicked();
    void on_StartButton_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();
    void on_minBtn_clicked();
    void on_findres_btn_clicked();
    void on_horizontalSlider_music_sliderReleased();
    void on_love_list_doubleClicked(const QModelIndex &index);
    void on_toolButton_11_clicked();
    void on_listT1_doubleClicked(const QModelIndex &index);
    void on_now_music_btn_clicked();
    void on_horizontalSlider_sliderReleased();
    void on_toolButton_set_clicked();

private:
    Ui::Widget *ui;
    QSqlDatabase db;
};
#endif // WIDGET_H
