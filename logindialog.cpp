#include "logindialog.h"
#include "ui_logindialog.h"
#include "QMessageBox"
#include "mainwindow.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    if(!MainWindow::authenticated){
        ui->stackedWidget->setCurrentWidget(ui->page);
    }
    else{
        ui->stackedWidget->setCurrentWidget(ui->page_2);
    }
    ui->userEditLine->setFocus();
    ui->passwordEditLine->setEchoMode(QLineEdit::Password);
    connect(ui->loginButton,&QPushButton::clicked,[=](){onLoginButtonClicked();});
    connect(ui->disconnectButton,&QPushButton::clicked,[=](){onDisconnectButtonClicked();});
    connect(ui->cancelButton,&QPushButton::clicked,this,&QDialog::reject);
    connect(ui->cancelButton_2,&QPushButton::clicked,this,&QDialog::reject);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::onLoginButtonClicked(){
    if(ui->userEditLine->text()=="Fiaro Iarilanja" && ui->passwordEditLine->text()=="umbrella"){
        accept();
        QMessageBox::information(this,"Login","You are logged in.");
    }
    else{
        QMessageBox::critical(this,"Login Error","Invalid password or username");
        ui->userEditLine->setFocus();
    }
}

void LoginDialog::onDisconnectButtonClicked(){
    accept();
    QMessageBox::information(this, "Login", "Disconnected.");
}
