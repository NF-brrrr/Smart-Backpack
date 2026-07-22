#include "logindialog.h"
#include "ui_logindialog.h"
#include "QMessageBox"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->userEditLine->setFocus();
    ui->passwordEditLine->setEchoMode(QLineEdit::Password);
    connect(ui->loginButton,&QPushButton::clicked,[=](){onLoginButtonClicked();});
    connect(ui->cancelButton,&QPushButton::clicked,this,&QDialog::reject);
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
