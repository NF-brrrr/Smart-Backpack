#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Smart backpack");
    resize(1280,800);
    this->setStyleSheet("QMainWindow {background-color : 070D19; }");
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    sidebarWidget = new QWidget(this);
    sidebarWidget->setStyleSheet("background-color: #0B1224;");
    sidebarWidget->setFixedWidth(260);

    dashboardWidget = new QWidget(this);
    dashboardWidget->setStyleSheet("background-color: #070D19;");

    mainLayout->addWidget(sidebarWidget);
    mainLayout->addWidget(dashboardWidget);

    barMenu = new QVBoxLayout(sidebarWidget);
    barMenu->setContentsMargins(20,30,20,20);
    barMenu->setSpacing(15);

    titleLabel =  new QLabel(sidebarWidget);
    titleLabel->setText("<span style='color: #4EA2E4; font-weight: bold; font-size: 16px;'>SMART</span><br>"
                        "<span style='color: #2D63C8; font-weight: bold; font-size: 20px;'>BACKPACK</span>");
    barMenu->addWidget(titleLabel);
    barMenu->addSpacing(20);

    btnAuth = new QPushButton("Authentification",sidebarWidget);
    btnAuth->setCheckable(true);
    btnAuth->setChecked(true);
    btnAuth->setFixedHeight(45);
    btnAuth->setStyleSheet("color: #A0AEC0; background-color: transparent; border: none; text-align: left; padding-left: 10px;");
    barMenu->addWidget(btnAuth);

    btnDashboard = new QPushButton(" Tableau de bord ",sidebarWidget);
    btnDashboard->setFixedHeight(45);
    btnDashboard->setStyleSheet("background-color: #1E3A8A; color: #4EA2E4; border-radius: 5px; text-align: left; padding-left: 10px;");
    barMenu->addWidget(btnDashboard);


    btnHistory = new QPushButton("Historique",sidebarWidget);
    btnHistory->setFixedHeight(45);
    btnHistory->setStyleSheet("background-color: #1E3A8A; color: #4EA2E4; border-radius: 5px; text-align: left; padding-left: 10px;");
    barMenu->addWidget(btnHistory);

    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    barMenu->addItem(spacer);

    statusWidget = new QWidget(sidebarWidget);
    statusWidget->setFixedHeight(80);
    statusWidget->setStyleSheet("background-color: #050A14; border: 1px solid #10B981; border-radius: 8px;");

    statusLayout = new QVBoxLayout(statusWidget);
    statusLayout->setContentsMargins(15, 10, 15, 10);
    QLabel *statusTitle = new QLabel("<span style='color: #10B981; font-weight: bold;'>Système actif</span>", statusWidget);
    QLabel *statusDesc = new QLabel("<span style='color: #718096; font-size: 11px;'>Tout fonctionne normalement</span>", statusWidget);

    statusLayout->addWidget(statusTitle);
    statusLayout->addWidget(statusDesc);

    barMenu->addWidget(statusWidget);

}

MainWindow::~MainWindow()
{
    delete ui;

}
