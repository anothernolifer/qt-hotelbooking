#ifndef PAKTOUR_H
#define PAKTOUR_H

#include <QMainWindow>
#include "newwindow2.h"
#include "newindow1.h"
#include "./ui_newwindow2.h"
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QPushButton>
#include <QMouseEvent>

namespace Ui {
class Info;
}

class Info : public QMainWindow
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr);
    ~Info();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::Info *ui;
};

#endif // PAKTOUR_H
