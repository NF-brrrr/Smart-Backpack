#include "logindialog.h"
#include "ui_logindialog.h"
#include "QMessageBox"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
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
    }
    else{
        QMessageBox::critical(this,"Login Error","Invalid password or username");
        ui->userEditLine->setFocus();
    }
}
