#ifndef NEWWINDOW3_H
#define NEWWINDOW3_H
#include "newwindow2.h"
#include "newindow1.h"
#include "./ui_newwindow2.h"
#include <QMainWindow>
#include <iostream>
#include <QRandomGenerator>
#include <bits/stdc++.h>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include <cmath>
#include <QDateTime>
#include <QCoreApplication>
#include <QLabel>
#include <QComboBox>
#include <QPainter>
#include <QPoint>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMouseEvent>
#include "adminmenu.h"
#include "./ui_adminmenu.h"

namespace Ui {
class NewWindow3;
}

class NewWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewWindow3(QWidget *parent = nullptr);
    ~NewWindow3();

public slots:
    void showbillwindow();
    void resetdates(QString date);
    void dateFunction(QString date1);
    void updateLineEdit();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::NewWindow3 *ui;
};


class Passenger{

protected:
    QString first_name, last_name, address,check_indate, check_outdate, meal_type, seat_type, hotel_name, card_type , card_expiry_date , date_book;
    qint64 phone,card_no;
    int card_cvv;
    const int eco_seats, bus_seats;

public:
    int eco, bus;
    Passenger(QString a, QString b, QString c, QString d, QString e, QString f, QString g, QString h, QString i, qint64 v, QString w, qint64 x, int y, QString z): eco_seats(150),bus_seats(50)
    {
        first_name= a;
        last_name = b;
        address = c;
        check_indate = d;
        check_outdate = e;
        meal_type= f;
        seat_type= g;
        hotel_name = h;
        card_type = i;
        phone = v;
        date_book= w;
        card_no = x;
        card_cvv = y;
        card_expiry_date= z;
        eco= eco_seats;
        bus= bus_seats;
    }

    QString getFirstName()
    {
        return first_name ;
    }

    QString getLastName()
    {
        return last_name ;
    }

    QString getAddress()
    {
        return address ;
    }

    QString getCheckindate()
    {
        return check_indate ;
    }

    QString getcheckoutdate()
    {
        return check_outdate ;
    }

    QString getMeal()
    {
        return meal_type ;
    }

    QString getSeat()
    {
        return seat_type ;
    }

    QString getHotel()
    {
        return hotel_name ;
    }

    QString getCardType()
    {
        return card_type ;
    }

    qint64 getPhone()
    {
        return phone;
    }

    QString getbookdate()
    {
        return date_book;
    }

    qint64 getCardNo()
    {
        return card_no;
    }

    int getCardCVV()
    {
        return card_cvv;
    }

    QString getCardExp()
    {
        return card_expiry_date;
    }

    int getEco()
    {
        return eco;
    }

    int getBus()
    {
        return bus;
    }
};

class TicketType{
public:
    int no_seats;
    int bill;

public:
    TicketType()
    {

    }

    void Bill(int a)
    {
        bill = a;
    }
    void NoSeats(int b)
    {
        no_seats = b;
    }
    virtual bool seat() = 0;
};

class Economy: public TicketType{
private:
    Passenger *p;

public:

    Economy(Passenger *passenger) : p(passenger){}
    bool seat() override
    {

        TicketType::bill= TicketType::bill*TicketType::no_seats;
        return true;

    }

    ~Economy(){}

};

class Business: public TicketType{

private:
    Passenger *p1;
public:

    Business(Passenger *passenger): p1(passenger){}
    bool seat() override
    {

        TicketType::bill= (TicketType::bill*TicketType::no_seats)+(1000*TicketType::no_seats);
        return true;

    }

    ~Business(){}
};

class Ticket{
protected:
    QString ticket_id;
    Passenger *passenger;
    TicketType *ticketType;
    int bill1,noseat1;

public:
    Ticket():ticketType(){}
    Ticket(int a, Passenger p, TicketType *t):ticketType(t)
    {
        noseat1= a;
        passenger = &p;
        qint64 seed = QDateTime::currentMSecsSinceEpoch() ^ qint64(QCoreApplication::applicationPid());

        // Create a random number generator with the unique seed value
        QRandomGenerator generator(seed);
        int randomValue = generator.bounded(10000);
        ticket_id = "HF" + QString::number(randomValue);
    }

    bool checkCheckoutdate()
    {
        if(passenger->getCheckindate()== passenger->getcheckoutdate())
        {
            return false;
        }
        else
        {
            bill1= l_payment(passenger->getCheckindate(),passenger->getcheckoutdate());
            ticketType->Bill(bill1);
            ticketType->NoSeats(noseat1);
            return true;
        }
    }
    bool checkCard()
    {
        if((floor(log10(passenger->getCardNo())) + 1 == 16) && (floor(std::log10(passenger->getCardCVV())) + 1 == 3))
            return true;
        else
            return false;
    }

    void registration()
    {
        QFile *f;
        QString path = "TicketInfo.txt";
        f = new QFile(path);
        if(!f->open(QIODevice::Append | QIODevice::Text))
            qDebug() << "Could not open file for read/write";
        QTextStream out(f);
        out.seek(f->size());
        out << ticket_id << "\n" << passenger->getFirstName() << "\n" << passenger->getLastName() << "\n" << passenger->getAddress() << "\n" << passenger->getPhone() << "\n" << passenger->getHotel() << "\n" << passenger->getCheckindate() << "\n" << passenger->getcheckoutdate() << "\n" << passenger->getMeal() << "\n" << passenger->getSeat() << "\n" << ticketType->no_seats << "\n" << passenger->getbookdate() << "\n" << passenger->getCardType() << "\n" << passenger->getCardNo() << "\n" << passenger->getCardCVV() << "\n" << passenger->getCardExp() << "\n" << ticketType->bill<< "\n\n";
        f->close();
    }

    void saveTicketID()
    {
        QFile *fp;
        QString path = "TicketID.txt";
        fp = new QFile(path);
        if(!fp->open(QIODevice::WriteOnly | QIODevice::Text))
            qDebug() << "Could not open file for read/write";
        QTextStream out(fp);
        out.seek(fp->size());
        out << ticket_id<< "\n";
        fp->close();
    }

    bool seat(){
        if(ticketType->seat())
            return true;
        else
            return false;
    }

    void setTicketID(QString a)
    {
        ticket_id= a;
    }

    int l_payment(QString orig, QString dest)
    {
        if((orig=="10" && dest=="11") ||(orig=="11" && dest=="12"))
            return 1500;
        else if((orig=="10" && dest=="12") || (orig=="11" && dest== "13"))
            return 3000;
        else if((orig=="10" && dest=="13") || (orig=="11" && dest== "14"))
            return 4500;
        else if((orig=="12" && dest=="13") || (orig=="13" && dest== "14"))
            return 1500;
        else if((orig=="12" && dest=="14") || (orig=="13" && dest== "15"))
            return 3000;
        else if((orig=="12" && dest=="15") || (orig=="13" && dest== "16"))
            return 4500;
        else if((orig=="14" && dest=="15") || (orig=="15" && dest== "16"))
            return 1500;
        else if((orig=="14" && dest=="16") || (orig=="15" && dest== "17"))
            return 3000;
        else if((orig=="14" && dest=="17") || (orig=="15" && dest== "18"))
            return 4500;
        else if((orig=="16" && dest=="17") || (orig=="17" && dest== "18"))
            return 1500;
        else if((orig=="16" && dest=="18") || (orig=="17" && dest== "19"))
            return 3000;

        else{
            return 0;
        }
    }
};


#endif // NEWWINDOW3_H
