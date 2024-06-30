#include "nosic.h"
#include "ui_nosic.h"
#include <QFile>
#include <QRegularExpression>
nosic::nosic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nosic)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

nosic::~nosic()
{
    delete ui;
}

void nosic::setjpg(int row){
    switch(row){
    case 0:{ ui->jpg_label->setPixmap(QPixmap(":/new/prefix2/music/Jpg/00.png")); break;}
    case 1:{ ui->jpg_label->setPixmap(QPixmap(":/new/prefix2/music/Jpg/10.png")); process(":/new/prefix2/music/lrcs/Call of Silence.lrc"); break;}
    case 2:{ ui->jpg_label->setPixmap(QPixmap(":/new/prefix2/music/Jpg/20.png")); process(":/new/prefix2/music/lrcs/Operation Ashring.lrc"); break;}
    case 3:{ ui->jpg_label->setPixmap(QPixmap(":/new/prefix2/music/Jpg/30.png")); process(":/new/prefix2/music/lrcs/Operation Deepness.lrc"); break;}
    case 4:{ ui->jpg_label->setPixmap(QPixmap(":/new/prefix2/music/Jpg/40.png")); process(":/new/prefix2/music/lrcs/Renegade.lrc"); break;}
    case 5:{ ui->jpg_label->setPixmap(QPixmap(":/new/prefix2/music/Jpg/50.png")); process(":/new/prefix2/music/lrcs/Running In The Dark.lrc"); break;}
    default:{ ui->jpg_label->setPixmap(QPixmap(":/new/prefix2/music/Jpg/00.png")); break;}
    }
}

bool operator <(const LyricLine& A, const LyricLine& B)
{
    return A.time<B.time;
}

void nosic::clear()
{
    ui->label_1->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("");
    ui->label_4->setText("");
    ui->label_5->setText("");
    ui->label_6->setText("");
}
QString nosic::getLyricText(int index)//根据下标获得歌词内容
{
    if(index<0 || index>=lines.size()){
        return "";
    }else{
        //qDebug()<<"输出歌词："<<lines[index].text;
        return lines[index].text;
    }
}
void nosic::showcontent(qint64 position)//显示当前播放进度的歌词
{
    int index=getIndex(position);
    if(index==-1){
        ui->label_1->setText("");
        ui->label_2->setText("");
        ui->label_3->setText(u8"当前歌曲无歌词");
        ui->label_4->setText("");
        ui->label_5->setText("");
        ui->label_6->setText("");
    }else{
        ui->label_1->setText(getLyricText(index-2));
        ui->label_2->setText(getLyricText(index-1));
        ui->label_3->setText(getLyricText(index));
        ui->label_4->setText(getLyricText(index+1));
        ui->label_5->setText(getLyricText(index+2));
        ui->label_6->setText(getLyricText(index+3));
    }
}
int nosic::getIndex(qint64 position)//获取歌词位置
{
    if(!lines.size()){
        return -1;//如果没歌词
    }
    else{
        if(lines[0].time>=position){
            return 0;
        }
    }
    int i=1;
    for(i=1;i<lines.size();i++){
        if(lines[i-1].time<position && lines[i].time>=position){
            return i-1;
        }
    }
    return lines.size()-1;
}

bool nosic::process(QString filePath)
{
    QFile lyricFile(filePath);
    if (!lyricFile.open(QFile::ReadOnly))
        return false;

    QString content = QTextStream(&lyricFile).readAll();
    lyricFile.close();

    lines.clear();

    QRegularExpression regex(R"(\\[(\d+):(\d+(?:\.\d+)?)\\])"); // Updated regex pattern
    QRegularExpressionMatchIterator it = regex.globalMatch(content);

    QList<int> timeLabels;
    int lastPos = 0;
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        timeLabels << (match.captured(1).toInt() * 60 + match.captured(2).toDouble()) * 1000;
        int pos = match.capturedEnd();

        if (!it.hasNext()) {
            QString text = content.mid(lastPos).trimmed();
            for (const int& time : timeLabels) {
                lines.append(LyricLine(time, text));
            }
            break;
        }

        QString text = content.mid(lastPos, pos - lastPos).trimmed();
        if (!text.isEmpty()) {
            for (const int& time : timeLabels) {
                lines.append(LyricLine(time, text));
            }
            timeLabels.clear();
        }
        lastPos = pos;
    }

    return !lines.isEmpty();
}

void nosic::on_toolButton_clicked()
{
    // 添加按钮点击处理逻辑
}

void nosic::on_pushButton_clicked()
{
    // 添加按钮点击处理逻辑
}

void nosic::on_radioButton_clicked(bool checked)
{
    // 添加按钮点击处理逻辑
}

void nosic::on_radioButton_2_clicked(bool checked)
{
    // 添加按钮点击处理逻辑
}
