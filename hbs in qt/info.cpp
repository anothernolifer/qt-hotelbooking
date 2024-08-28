#include "paktour.h"
#include "ui_paktour.h"
#include "newwindow2.h"
#include "newindow1.h"
#include "./ui_newwindow2.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QSequentialAnimationGroup>


// global initialize current index to 0
int currentIndex = 0;


Info::Info(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);


    // update label with current image

    QPropertyAnimation *animation = new QPropertyAnimation(ui->label, "geometry", this);
    animation->setDuration(2500);
    animation->setStartValue(QRect(0, 0, 1080, 629));
    animation->setEndValue(QRect(-5, -5, 1110, 659));

    // Set the easing curve of the animation to make it smoother
    animation->setEasingCurve(QEasingCurve::InOutQuad);

    // Create a new animation group to loop the animation
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);
    group->addAnimation(animation);

    QPropertyAnimation *reverseAnimation = new QPropertyAnimation(ui->label, "geometry", this);
    reverseAnimation->setDuration(2500);
    reverseAnimation->setStartValue(QRect(-5,-5, 1110, 659));
    reverseAnimation->setEndValue(QRect(0, 0, 1080, 629));

    // Set the easing curve of the animation to make it smoother
    reverseAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // Add the reverse animation to the animation group
    group->addAnimation(reverseAnimation);

    // Set the loop count of the animation group to 0 to make it loop infinitely
    group->setLoopCount(-1);
    group->start();

    //connect next button
    connect(ui->pushButton, &QPushButton::clicked, [=]() {
        currentIndex++;

        if(currentIndex==1)
        {
            ui->label_2->setText(" Hotel:Trisara");
            ui->label_4->setText("Location: Pokhara");
            ui->label_3->setText("Phone no:963 ");



        }
        else if(currentIndex==0)
        {
            ui->label_2->setText("Hotel:Lakeside");
            ui->label_4->setText("Location: Pokhara");
            ui->label_3->setText("Phone no:369 ");



        }
        else if(currentIndex==2)
        {
            ui->label_2->setText("Hotel:Lumbini");
            ui->label_4->setText("Location: Pokhara");
            ui->label_3->setText("Phone no:258 ");



        }
        else if(currentIndex==3)
        {
            ui->label_2->setText("Hotel:XYZ");
            ui->label_4->setText("Location: Dharan");

            ui->label_3->setText("Phone no: 147");


        }
        else if(currentIndex==4)
        {
            ui->label_2->setText("Hotel:Seaview");
            ui->label_4->setText("Location: Dharan");
            ui->label_3->setText("Phone no:123 ");


        }
        else if(currentIndex==5)
        {
            ui->label_2->setText("Hotel:kanchanjunga");
            ui->label_4->setText("Location: Dharan");
            ui->label_3->setText("Phone no:456 ");



        }
        else if(currentIndex==6)
        {
            ui->label_2->setText("Hotel:Patan");
            ui->label_4->setText("Location: Kathmandu");
            ui->label_3->setText("Phone no:789 ");



        }
        else if(currentIndex==7)
        {
            ui->label_2->setText("Hotel:Everest");
            ui->label_4->setText("Location: Kathmandu");
            ui->label_3->setText("Phone no:987 ");



        }
        else if(currentIndex==8)
        {
            ui->label_2->setText("Hotel:Annapurna");
            ui->label_4->setText("Location: Kathmandu");

            ui->label_3->setText("Phone no:654 ");


        }
        else if(currentIndex==9)
        {
            ui->label_2->setText("Hotel:ABC");
            ui->label_4->setText("Location: Kathmandu");
            ui->label_3->setText("Phone no:321 ");



        }


        group->start();
    });

    // connect previous button
    connect(ui->pushButton_2, &QPushButton::clicked, [=]() {
        currentIndex--;

        if(currentIndex==1)
        {
            ui->label_2->setText(" Hotel:Trisara");
            ui->label_4->setText("Location: Pokhara");
             ui->label_3->setText("Phone no:963 ");


        }
        else if(currentIndex==0)
        {
            ui->label_2->setText("Hotel:Lakeside");
            ui->label_4->setText("Location: Pokhara");

            ui->label_3->setText("Phone no:369 ");


        }
        else if(currentIndex==2)
        {
            ui->label_2->setText("Hotel:Lumbini");
            ui->label_4->setText("Location: Pokhara");

            ui->label_3->setText("Phone no:258 ");


        }
        else if(currentIndex==3)
        {
            ui->label_2->setText("Hotel:XYZ");
            ui->label_4->setText("Location: Dharan");
            ui->label_3->setText("Phone no:147 ");



        }
        else if(currentIndex==4)
        {
            ui->label_2->setText("Hotel:Seaview");
            ui->label_4->setText("Location: Dharan");
            ui->label_3->setText("Phone no:123 ");


        }
        else if(currentIndex==5)
        {
            ui->label_2->setText("Hotel:kanchanjunga");
            ui->label_4->setText("Location: Dharan");
            ui->label_3->setText("Phone no:456 ");



        }
        else if(currentIndex==6)
        {
            ui->label_2->setText("Hotel:Patan");
            ui->label_4->setText("Location: Kathmandu");

            ui->label_3->setText("Phone no:789 ");


        }
        else if(currentIndex==7)
        {
            ui->label_2->setText("Hotel:Everest");
            ui->label_4->setText("Location: Kathmandu");
            ui->label_3->setText("Phone no:987 ");



        }
        else if(currentIndex==8)
        {
            ui->label_2->setText("Hotel:Annapurna");
            ui->label_4->setText("Location: Kathmandu");
            ui->label_3->setText("Phone no:654 ");

        }
        else if(currentIndex==9)
        {
            ui->label_2->setText("Hotel:ABC");
            ui->label_4->setText("Location: Kathmandu");
            ui->label_3->setText("Phone no:321 ");


        }

        group->start();
    });
}

Info::~Info()
{
    delete ui;
}

void Info::on_pushButton_3_clicked()
{
    Newindow1 obj;
    obj.showNewWindow();
    this->close();
}

