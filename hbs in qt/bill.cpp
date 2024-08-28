#include "bill.h"
#include "./ui_bill.h"
#include "newwindow3.h"
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMessageBox>
#include "newwindow2.h"
#include "newindow1.h"
#include "./ui_newwindow2.h"
#include "adminportal.h"
#include "adminmenu.h"
#include "./ui_adminmenu.h"
#include <QtWidgets/QTextEdit>

Bill::Bill(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Bill)
{
    ui->setupUi(this);
    QString fname,lname,hotel, checkin, checkout,seatType,bookdate, seatNo, bill;

    QFile fp("TicketID.txt");
    if (!fp.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for reading:";

    }

    QTextStream init(&fp);
    QString id = init.readLine();

    fp.close();

    FindTicket tick;
    bool search = tick.find(id);
    QStringList Data= tick.getTicketData();
    if (search)
    {
        fname = Data.at(0);
        lname = Data.at(1);
        hotel = Data.at(4);
        checkin = Data.at(5);
        checkout = Data.at(6);
        seatType = Data.at(8);
        seatNo = Data.at(9);
        bookdate = Data.at(10);
        bill = Data.at(15);
    }
    else
    {
        qDebug() << "ID not found";
    }



    QPropertyAnimation *animation = new QPropertyAnimation(ui->label_12, "geometry");
    animation->setDuration(2000);
    animation->setStartValue(QRect(360, 430, 0, 0));
    animation->setEndValue(QRect(360, 430, 111, 101));
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);



    QFont ai("MV Boli ", 22, QFont::Bold);
    QFont font("Segoe UI ", 9, QFont::Bold);

    QString fullName = fname + " " + lname;
    ui->label_3->setFont(font);
    ui->label_3->setText(fullName);
    ui->label_4->setFont(font);
    ui->label_4->setText(id);
    ui->label_5->setFont(font);
    ui->label_5->setText(hotel);
    ui->label_6->setFont(font);
    ui->label_6->setText(seatType);
    ui->label_7->setFont(font);
    ui->label_7->setText(seatNo);
    ui->label_8->setFont(font);
    ui->label_8->setText(bookdate);
    QFont my("Segoe UI ", 13, QFont::Bold);
    ui->label_9->setFont(my);
    ui->label_9->setText(bill);

}

Bill::~Bill()
{
    delete ui;
}

void Bill::on_pushButton_clicked()
{
    QFile file("checkinFlagValue.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for reading:";

    }

    QTextStream in(&file);
    QString flag = in.readLine();
    file.close();
    if(flag=="false")
    {
        adminportal ob1;
        ob1.showAdminMenu();
        this->close();
    }

    else{
        Newindow1 obj;
        obj.showNewWindow();
        this->close();

    }
}


void Bill::on_pushButton_2_clicked()
{
    if(ui->radioButton->isChecked())
    {
        if (ui->textEdit->toPlainText().isEmpty()) {
            ui->label_27->setText("Kindly provide pickup location");

        } else {
            ui->label_27->setText("Pathao Driver is on its way!");
        }
    }

    else{
        ui->label_27->setText(" ");
    }
}

