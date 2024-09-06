
#include "newwindow3.h"
#include "ui_newwindow3.h"
#include <QMessageBox>
#include <QComboBox>
#include <QString>
#include <QDate>
#include <QDateEdit>
#include "newwindow2.h"
#include "newindow1.h"
#include "./ui_newwindow2.h"
#include "bill.h"
#include "./ui_bill.h"
#include "updateticket.h"
#include "./ui_updateticket.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QPainter>
#include <QPoint>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMovie>
#include <QTimer>
#include "adminportal.h"
#include "adminmenu.h"
#include "./ui_adminmenu.h"


QString check_indate = "";
QString check_outdate = "";

NewWindow3::NewWindow3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewWindow3)
{
    ui->setupUi(this);

    connect(ui->comboBox_3, &QComboBox::currentTextChanged, this, &NewWindow3::updateLineEdit);
    connect(ui->comboBox_2, &QComboBox::currentTextChanged, this, &NewWindow3::updateLineEdit);
    connect(ui->lineEdit_6, &QLineEdit::textChanged, this, &NewWindow3::updateLineEdit);



    QFile file("CurrentFlagValue.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for reading:";

    }

    QTextStream in(&file);
    QString flag = in.readLine();
    file.close();
    if(flag=="false"){
        QFile file1("CurrentTicketUpdate.txt");
        if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Failed to open file for reading:";

        }

        QTextStream ini(&file1);
        QString flag1 = ini.readLine();
        file1.close();
        FindTicket fp;
        bool search;
        search= fp.find(flag1);
        QStringList Data= fp.getTicketData();
        if (search)
        {
            QString fname1 = Data.at(0);
            QString lname1 = Data.at(1);
            QString   address1 = Data.at(2);
            QString   a1 = Data.at(3);

            QString   hotel1 = Data.at(4);
            QString   checkindate1 = Data.at(5);
            QString   checkoutdate1 = Data.at(6);
            QString   meal1 = Data.at(7);
            QString   seat1 = Data.at(8);
            QString   c1 = Data.at(9);

            QString  bookdate1 = Data.at(10);
            QString   card_type1 = Data.at(11);
            QString  b1 = Data.at(12);

            QString   d1 = Data.at(13);

            QString  carddate1 = Data.at(14);
            QString bill = Data.at(15);
            ui->lineEdit->setText(fname1);
            ui->lineEdit_2->setText(lname1);
            ui->lineEdit_3->setText(a1);
            ui->lineEdit_4->setText(address1);
            ui->lineEdit_5->setText(b1);
            ui->lineEdit_6->setText(c1);
            ui->lineEdit_7->setText(d1);
            ui->comboBox->setCurrentText(hotel1);
            ui->comboBox_2->setCurrentText(checkoutdate1);
            ui->comboBox_3->setCurrentText(checkindate1);
            QDateTime dateTime = QDateTime::fromString(bookdate1 + " 00:00:00", "yyyy-MM-dd hh:mm:ss");
            QDate date = dateTime.date();
            ui->dateEdit_2->setDate(date);
            QDateTime dateTime2 = QDateTime::fromString(carddate1 + " 00:00:00", "yyyy-MM-dd hh:mm:ss");
            QDate date1 = dateTime2.date();
            ui->dateEdit->setDate(date1);
            if(meal1=="Veg")
            {
                ui->checkBox->setChecked(true);
            }
            else if(meal1=="Non-Veg")
            {
                ui->checkBox_2->setChecked(true);
            }
            if(seat1=="Business")
            {
                ui->checkBox_3->setChecked(true);
            }
            else if(seat1=="Economy")
            {
                ui->checkBox_4->setChecked(true);
            }
            if(card_type1=="VisaCard")
            {
                ui->radioButton->setChecked(true);
            }
            else if(card_type1=="MasterCard")
            {
                ui->radioButton_2->setChecked(true);
            }
            else if(card_type1=="CreditCard")
            {
                ui->radioButton_3->setChecked(true);
            }
        }

        QFile inputFile("TicketInfo.txt");
        inputFile.open(QIODevice::ReadOnly | QIODevice::Text);

        QFile tempFile("temp.txt");
        tempFile.open(QIODevice::WriteOnly | QIODevice::Text);

        QTextStream init(&inputFile);
        QTextStream out(&tempFile);

        while (!init.atEnd()) {
            QString line = init.readLine();
            if (line.startsWith(flag1)) {
                for (int i = 0; i < 16; i++) {
                    init.readLine();
                }
            } else {
                out << line << "\n";
            }
        }

        // Step 5: Close both files
        inputFile.close();
        tempFile.close();

        QFile::remove("TicketInfo.txt");
        QFile::rename("temp.txt", "TicketInfo.txt");
        QMessageBox::warning(this,"Admin View","You are in admin view");
    }
    else{
        QDate currentDate = QDate::currentDate();
        ui->dateEdit->setDate(currentDate);
        ui->dateEdit_2->setDate(currentDate);
    }
}

NewWindow3::~NewWindow3()
{
    delete ui;
}

void NewWindow3::updateLineEdit()
{
    QString comboBox1Text = ui->comboBox_3->currentText();
    QString comboBox2Text = ui->comboBox_2->currentText();
    QString c1 = ui->lineEdit_6->text();
    int n = c1.toInt();

    Ticket t;
    int value = t.l_payment(comboBox1Text, comboBox2Text);
    int bus_value = value;






}

void NewWindow3::showbillwindow()
{
    Bill *newWindow = new Bill();
    newWindow->show();
    this->close();
}

void NewWindow3::on_pushButton_clicked()
{
    QFile file("CurrentFlagValue.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for reading:";

    }

    QTextStream in(&file);
    QString flag = in.readLine();
    file.close();
    QDate selectedDate = ui->dateEdit->date();
    QDate selectedDate_2 = ui->dateEdit_2->date();
    QDate currentDate = QDate::currentDate();

    if((!(ui->checkBox->isChecked()) && !(ui->checkBox_2->isChecked())) || (!(ui->checkBox_3->isChecked()) && !(ui->checkBox_4->isChecked())) || !(selectedDate.isValid()) || (!(selectedDate_2.isValid())||!(ui->radioButton->isChecked()) && !(ui->radioButton_2->isChecked()) && !(ui->radioButton_3->isChecked())) || (ui->lineEdit->text().isEmpty()) || (ui->lineEdit_2->text().isEmpty()) || (ui->lineEdit_3->text().isEmpty()) || (ui->lineEdit_4->text().isEmpty()) || (ui->lineEdit_5->text().isEmpty()) || (ui->lineEdit_6->text().isEmpty()) || (ui->lineEdit_7->text().isEmpty()) )
    {
        QMessageBox::warning(this,"Error","Please Fill every detail");
    }

    else if(((ui->checkBox->isChecked()) && (ui->checkBox_2->isChecked())) || ((ui->checkBox_3->isChecked()) && (ui->checkBox_4->isChecked())))
    {
        QMessageBox::warning(this,"Error","Please Choose 1 option b/w Meal or Seat Type");
    }

    else if((ui->comboBox_3->currentText()=="-") || (ui->comboBox_2->currentText()== "-"))
    {
        QMessageBox::warning(this,"Error","Please Choose checkout date");
    }

    else{
        if(flag=="true"){
            if(currentDate > selectedDate)
            {
                QMessageBox::warning(this,"Error","Please Choose correct Card Expiration date");
            }

            if(currentDate > selectedDate_2)
            {
                QMessageBox::warning(this,"Error","Please Choose correct booking date");
            }
        }
        if(flag=="false" || (flag=="true" && (selectedDate>=currentDate && selectedDate_2>=currentDate))){

            QString fname = ui->lineEdit->text();
            QString lname = ui->lineEdit_2->text();
            QString a = ui->lineEdit_3->text();
            qint64 phone= a.toLongLong();
            QString address = ui->lineEdit_4->text();
            QString b = ui->lineEdit_5->text();
            qint64 cardno = b.toLongLong();
            QString c = ui->lineEdit_6->text();
            int noseats = c.toInt();
            QString d = ui->lineEdit_7->text();
            int cvv = d.toInt();
            QString origin = ui->comboBox_3->currentText();
            QString destination = ui->comboBox_2->currentText();
            QString hotel = ui->comboBox->currentText();
            QString meal, seat, card;
            QString depDate= selectedDate_2.toString(Qt::ISODate);
            QString carddate = selectedDate.toString(Qt::ISODate);
            if(ui->checkBox->isChecked())
                meal= "Veg";
            else if(ui->checkBox_2->isChecked())
                meal= "Non-Veg";
            if(ui->checkBox_3->isChecked())
                seat= "Business";
            else if(ui->checkBox_4->isChecked())
                seat= "Economy";
            if(ui->radioButton->isChecked())
                card= "VisaCard";
            else if(ui->radioButton_2->isChecked())
                card = "MasterCard";
            else if(ui->radioButton_3->isChecked())
                card = "CreditCard";

            Passenger p1(fname,lname,address,origin,destination,meal,seat,hotel,card,phone,depDate,cardno,cvv,carddate);
            TicketType* ticketType;
            if (seat=="Economy") {
                ticketType = new Economy(&p1);
            } else if(seat =="Business"){
                ticketType = new Business(&p1);
            }
            Ticket t1;
            t1= Ticket(noseats,p1, ticketType);
            if(t1.checkCard())
            {
                if(t1.checkCheckoutdate())
                {

                    if(t1.seat())
                    {
                        if(flag=="false"){
                            QFile file1("CurrentTicketUpdate.txt");
                            if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
                            {
                                qDebug() << "Failed to open file for reading:";

                            }

                            QTextStream ini(&file1);
                            QString flag2 = ini.readLine();
                            t1.setTicketID(flag2);
                            file1.close();
                        }
                        t1.registration();
                        t1.saveTicketID();
                        showbillwindow();
                    }
                    else
                    {
                        if(seat=="Economy")
                            QMessageBox::warning(this,"Seats Unavaialable!","Sorry, the quantity of Economy Class seats are not available!");
                        else if(seat=="Business")
                            QMessageBox::warning(this,"Seats Unavaialable!","Sorry, the quantity of Business Class seats are not available!");
                    }
                }

                else{
                    QMessageBox::warning(this,"check in and checkout date Same!","Book for at least 1 day! ");
                }
            }
            else{
                QMessageBox::warning(this,"Card InValid","Enter Valid Card Details!");}

        }

    }

}


void NewWindow3::resetdates(QString date) {
    if (date != date && date != check_outdate) {
        if (date == date) {
            date = "";
            ui->comboBox_3->setCurrentText("-");
        }
        if (check_outdate == date) {
            check_outdate = "";
            ui->comboBox_2->setCurrentText("-");
        }
        if (date != "" && check_outdate != "") {
            date = date;
            check_outdate = "";
            ui->comboBox_2->setCurrentText("-");
            ui->comboBox_3->setCurrentText(date);
        }
    }
}


void NewWindow3::dateFunction(QString date1) {
    resetdates(date1);
    if (check_indate == date1) {
        check_indate = "";
        ui->comboBox_3->setCurrentText("-");
    } else if (check_outdate == date1) {
        check_outdate = "";
        ui->comboBox_2->setCurrentText("-");
    } else if (check_indate == "" && check_outdate != date1) {
        check_indate = date1;
        ui->comboBox_3->setCurrentText(date1);
    } else if (check_outdate == "" && check_indate != date1) {
        check_outdate = date1;
        ui->comboBox_2->setCurrentText(date1);
    }
}

void NewWindow3::on_pushButton_2_clicked()
{

    QFile file("CurrentFlagValue.txt");
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

