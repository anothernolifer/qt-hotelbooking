#include "mainwindow.h"
#include "newindow1.h"
#include "./ui_newindow1.h"
#include "./ui_mainwindow.h"
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QPixmap>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // Setup animations
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->label, "geometry");
    animation2->setDuration(3000);
    animation2->setStartValue(QRect(400, 560, 0, 0));
    animation2->setEndValue(QRect(400, 170, 561, 61));
    animation2->setEasingCurve(QEasingCurve::InOutQuad);
    animation2->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *animation3 = new QPropertyAnimation(ui->label_2, "geometry");
    animation3->setDuration(3000);
    animation3->setStartValue(QRect(510, 560, 0, 0));
    animation3->setEndValue(QRect(510, 210, 341, 71));
    animation3->setEasingCurve(QEasingCurve::InOutQuad);
    animation3->start(QAbstractAnimation::DeleteWhenStopped);

    // Connect button to slot
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::showNewWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showNewWindow()
{
    Newindow1 *newWindow = new Newindow1;
    newWindow->show();
    this->close();
}
