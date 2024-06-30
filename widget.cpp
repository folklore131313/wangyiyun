#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QSlider>
#include <QPainter>
#include <QtDebug>
#include <QFileDialog>
#include <QDir>
#include <QDesktopServices>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->big_widget->close();
    ui->music_widget->close();
    ui->listT1->setCurrentRow(0);
    QString curPash = QDir::currentPath();
    QString dlgTitle = "选择音频文件";
    QString filter = "音频文件(*.mp3 *.wav *.wma);;mp3文件(*.mp3);;wav文件(*.wav);;wma文件(*.wma);;所有文件(*.*)";
    QStringList fileList = QFileDialog::getOpenFileNames(this, dlgTitle, curPash, filter);
    for (int i = 0; i < fileList.count(); i++)
    {
        QString aFile = fileList.at(i);
        musicFiles.append(aFile);
        QFileInfo fileInfo(aFile);
        ui->love_list->addItem(fileInfo.fileName());  // 用于显示
    }

    if (!musicFiles.isEmpty())
    {
        player->setSource(QUrl::fromLocalFile(musicFiles.at(0)));
    }

    QDir dir = QString(":/new/prefix1/music");
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(0);  // 音量
    ui->num_label->setText("歌曲数:" + QString::number(fileList.count()));
    if (fileList.count() > 0)
        ui->love_list->setCurrentRow(0);

    connect(player, &QMediaPlayer::positionChanged, this, &Widget::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &Widget::updateDuration);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(QColor(171, 32, 32));
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(QPoint(0, 72), QPoint(1400, 72));
    pen.setColor(QColor(59, 59, 59));
    painter.setPen(pen);
    painter.drawLine(QPoint(251, 73), QPoint(251, 750));
}

void Widget::on_toolButton_2_clicked()
{
    // ui->toolButton_2->setIcon(QPixmap(":/new/prefix1/wyy res/red_previous.png"));
}

void Widget::on_toolButton_4_clicked()
{
    // ui->toolButton_4->setIcon(QPixmap(":/new/prefix1/wyy res/red_next.png"));
}

void Widget::on_toolButton_2_pressed()
{
    ui->toolButton_2->setIcon(QPixmap(":/new/prefix1/wyy res/red_previous.png"));
}

void Widget::on_toolButton_2_released()
{
    ui->toolButton_2->setIcon(QPixmap(":/new/prefix1/wyy res/shang.png"));
    int row = musicFiles.count();  // 获取歌曲数量
    int current = musicFiles.indexOf(player->source().toString());  // 获取当前位置
    ui->love_list->item(current)->setForeground(QColor(186, 186, 186));
    if (--current < 0)
    {
        current = row - 1;
    }
    else
    {
        ui->love_list->item(current)->setForeground(QColor(221, 65, 65));
    }
    player->setSource(QUrl::fromLocalFile(musicFiles.at(current)));  // 设置当前音乐
    list_row = current;
    chose_jpg(list_row);
    if (Start_flag == 0)
        player->play();
}

void Widget::on_toolButton_4_released()
{
    ui->toolButton_4->setIcon(QPixmap(":/new/prefix1/wyy res/next.png"));
    int row = musicFiles.count();  // 获取歌曲数量
    int current = musicFiles.indexOf(player->source().toString());  // 获取当前位置
    ui->love_list->item(current)->setForeground(QColor(186, 186, 186));
    if (++current >= row)
    {
        current = 0;
        ui->love_list->item(0)->setForeground(QColor(221, 65, 65));
    }
    else
    {
        ui->love_list->item(current)->setForeground(QColor(221, 65, 65));
    }
    player->setSource(QUrl::fromLocalFile(musicFiles.at(current)));  // 设置当前音乐
    list_row = current;
    chose_jpg(list_row);
    if (Start_flag == 0)
        player->play();
}

void Widget::on_toolButton_4_pressed()
{
    ui->toolButton_4->setIcon(QPixmap(":/new/prefix1/wyy res/red_next.png"));
}

// 关闭按键--槽
void Widget::on_exit_bnt_clicked()
{
    QWidget::close();
}

// 最小化按键
void Widget::on_minBtn_clicked()
{
    QWidget::showMinimized();
}

// 开始&暂停键按钮
void Widget::on_StartButton_clicked()
{
    if (Start_flag == 1)
    {
        ui->StartButton->setIcon(QPixmap(":/new/prefix1/wyy res/stop.png"));
        player->play();
        Start_flag--;
    }
    else
    {
        ui->StartButton->setIcon(QPixmap(":/new/prefix1/wyy res/play.png"));
        player->pause();
        Start_flag++;
    }
}

// 循环&顺序播放按键
void Widget::on_toolButton_5_clicked()
{
    if (Xun_flag == 1)
    {
        ui->toolButton_5->setIcon(QPixmap(":/new/prefix1/wyy res/xun1.png"));
        Xun_flag--;
    }
    else
    {
        ui->toolButton_5->setIcon(QPixmap(":/new/prefix1/wyy res/shunx2.png"));
        Xun_flag++;
    }
}

// 桌面歌词按键
void Widget::on_toolButton_6_clicked()
{
    if (Ci_flag == 1)
    {
        ui->toolButton_6->setIcon(QPixmap(":/new/prefix1/wyy res/ci1.png"));
        Ci_flag--;
    }
    else
    {
        ui->toolButton_6->setIcon(QPixmap(":/new/prefix1/wyy res/ci2.png"));
        Ci_flag++;
    }
}

void Widget::updateDuration(qint64 duration)  // 更新播放歌曲的时间
{
    ui->horizontalSlider_music->setMaximum(duration);  // 设置进度条最大值 也就是歌曲时长 ms
    int secs = duration / 1000;  // 全部秒数
    int mins = secs / 60;  // 分
    secs = secs % 60;  // 秒
    durationTime = QString::asprintf("%d:%d", mins, secs);
    ui->time1->setText(positionTime);
    ui->time2->setText(durationTime);
}

void Widget::updatePosition(qint64 position)  // 接收歌曲位置改变，那么滑块的位置也要变
{
    if (ui->horizontalSlider_music->isSliderDown())
        return;  // 如果手动调整进度条，则不处理
    ui->horizontalSlider_music->setSliderPosition(position);
    qInfo() << position;
    int secs = position / 1000;
    int mins = secs / 60;
    secs = secs % 60;
    positionTime = QString::asprintf("%d:%d", mins, secs);
    ui->time1->setText(positionTime);
    ui->time2->setText(durationTime);
    ui->music_widget->showcontent(position);
}

void Widget::on_horizontalSlider_music_sliderReleased()
{
    player->setPosition(ui->horizontalSlider_music->value());
}

void Widget::on_love_list_doubleClicked(const QModelIndex &index)
{
    int current = index.row();
    ui->love_list->item(list_row)->setForeground(QColor(186, 186, 186));
    ui->love_list->item(current)->setForeground(QColor(221, 65, 65));
    player->setSource(QUrl::fromLocalFile(musicFiles.at(current)));  // 设置当前音乐
    list_row = current;
    chose_jpg(list_row);
    if (Start_flag == 0)
        player->play();
}

void Widget::on_listT1_doubleClicked(const QModelIndex &index)
{
    switch (index.row())
    {
    case 0: { ui->love_wid->show(); break; }
    case 1: { ui->big_widget->show(); break; }
    case 2: { QString URL = "https://music.163.com/"; QDesktopServices::openUrl(QUrl(URL.toLatin1())); break; }
    case 3: { break; }
    case 4: {
        if (nosic_flag == 0)
        {
            ui->love_wid->close();
            ui->music_widget->show();
            nosic_flag = 1;
        }
        break;
    }
    }
}

void Widget::chose_jpg(int row)
{
    switch (row)
    {
    case 0: { ui->now_music_btn->setIcon(QPixmap(":/new/prefix2/music/Jpg/01.png")); now_jpg = 0; break; }
    case 1: { ui->now_music_btn->setIcon(QPixmap(":/new/prefix2/music/Jpg/11.png")); now_jpg = 1; break; }
    case 2: { ui->now_music_btn->setIcon(QPixmap(":/new/prefix2/music/Jpg/21.png")); now_jpg = 2; break; }
    case 3: { ui->now_music_btn->setIcon(QPixmap(":/new/prefix2/music/Jpg/31.png")); now_jpg = 3; break; }
    case 4: { ui->now_music_btn->setIcon(QPixmap(":/new/prefix2/music/Jpg/41.png")); now_jpg = 4; break; }
    case 5: { ui->now_music_btn->setIcon(QPixmap(":/new/prefix2/music/Jpg/51.png")); now_jpg = 5; break; }
    default: { ui->now_music_btn->setIcon(QPixmap(":/new/prefix2/music/Jpg/01.png")); now_jpg = 0; break; }
    }
    ui->music_widget->setjpg(row);
}

void Widget::on_now_music_btn_clicked()
{
    if (nosic_flag == 0)
    {
        ui->love_wid->close();
        ui->music_widget->show();
        nosic_flag = 1;
    }
    else
    {
        ui->music_widget->close();
        ui->love_wid->show();
        nosic_flag = 0;
    }
}

void Widget::on_horizontalSlider_sliderReleased()
{
    QAudioOutput *audioOutput = player->audioOutput();
    if (audioOutput)
    {
        audioOutput->setVolume(ui->horizontalSlider->value() / 100.0);
    }
}

void Widget::on_toolButton_set_clicked()
{
    if (ui_color == 1)
    {
        ui->groupBox->setStyleSheet("background-color: rgb(34, 34, 37)");
        ui->groupBox_2->setStyleSheet("background-color: rgb(34, 34, 37)");
    }
}

void Widget::on_findres_btn_clicked()
{

}

void Widget::on_toolButton_11_clicked()
{
    QAudioOutput *audioOutput = player->audioOutput();
    if (audioOutput)
    {
        audioOutput->setVolume(0);
    }
}
