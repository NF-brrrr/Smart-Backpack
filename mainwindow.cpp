#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "logindialog.h"
#include <QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduino=new QSerialPort(this);
    authenticated=false;
    ui->authenticateButton->setStyleSheet("background-color: purple; color: white");
    verifyConnection();
    connect(ui->connectionStatus,&QPushButton::clicked,[=](){verifyConnection();});
    connect(ui->authenticateButton,&QPushButton::clicked,[=](){onAuthenticateButtonClicked();});
    //connect(ui->switchOn,&QPushButton::clicked,[=](){switchLight('1');});
    //connect(ui->switchOff,&QPushButton::clicked,[=](){switchLight('0');});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::verifyConnection(){
    if(arduino->isOpen()){
        arduino->close();
        return;
    }

    bool arduinoFound=false;
    QString targetedPortName="";

    const auto ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &portInfo : ports){
        if(portInfo.hasVendorIdentifier() && (portInfo.vendorIdentifier() == 0x2341 || portInfo.vendorIdentifier() == 0x1a86)){
            arduinoFound=true;
            targetedPortName=portInfo.systemLocation();
            break;
        }
        else if(portInfo.description().contains("Arduino", Qt::CaseInsensitive)
                   || portInfo.manufacturer().contains("Arduino", Qt::CaseInsensitive)){
            arduinoFound = true;
            targetedPortName = portInfo.systemLocation();
            break;
        }
    }


    if(arduinoFound){
        arduino->setPortName(targetedPortName);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }
    else{
        ui->connectionStatus->setStyleSheet("background-color: red; color: black");
        ui->connectionStatus->setText("Not Connected");
        qDebug() << "No arduino device detected";
    }

    if(arduino->open(QIODevice::ReadWrite)){
        ui->connectionStatus->setStyleSheet("background-color: green; color: white");
        ui->connectionStatus->setText("Connected");
        return;
    }
    else{
        qDebug() << "Arduino found at: " << targetedPortName << "but failed to open. Error: " << arduino->errorString();
    }
}

void MainWindow::switchLight(char signal){
    if(arduino->isWritable()){
        arduino->write(&signal,1);
    }
    else{
        qDebug()<< "Not Writable";
    }
}

void MainWindow::onAuthenticateButtonClicked(){
    if(!authenticated){
        LoginDialog login;
        if(login.exec() == QDialog::Accepted){
            authenticated=true;
            ui->authenticateButton->setText("Fiaro-Iarilanja");
            return;
        }
    }
}