#ifndef VOLUME_H
#define VOLUME_H
#include <QWidget>

namespace Ui {
class volume;
}

class volume : public QWidget
{
    Q_OBJECT

public:
    explicit volume(QWidget *parent = nullptr);
    ~volume();

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::volume *ui;
};

#endif // VOLUME_H
