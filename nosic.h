#ifndef NOSIC_H
#define NOSIC_H

#include <QWidget>
#include <QMap>
#include <QVector>
#include <algorithm>

class LyricLine
{
public:
    qint64 time;
    QString text;
    LyricLine(qint64 time, QString text) : time(time), text(text) {}
};

bool operator <(const LyricLine& A, const LyricLine& B);

namespace Ui {
class nosic;
}

class nosic : public QWidget
{
    Q_OBJECT

public:
    explicit nosic(QWidget *parent = nullptr);
    ~nosic();
    int flag;
    int getflag() {
        return flag;
    }

    QVector<LyricLine> lines;
    void setjpg(int row);

    // Process lyrics file content into a structure
    bool process(QString filePath);
    // Find lyrics index based on current playback time
    int getIndex(qint64 position);
    // Display lyrics based on current playback progress
    void showcontent(qint64 position);
    // Get lyrics text by index
    QString getLyricText(int index);
    // Clear the lyrics display
    void clear();

private slots:
    void on_toolButton_clicked();
    void on_pushButton_clicked();
    void on_radioButton_clicked(bool checked);
    void on_radioButton_2_clicked(bool checked);

private:
    Ui::nosic *ui;
};

#endif // NOSIC_H
