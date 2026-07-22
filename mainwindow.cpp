#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Smart backpack");
    resize(1280, 800);
    this->setStyleSheet("QMainWindow {background-color : #070D19; }");

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ERREUR 1 CORRIGÉE : On met centralWidget comme parent (et pas 'this') pour débloquer les clics !
    sidebarWidget = new QWidget(centralWidget);
    sidebarWidget->setStyleSheet("background-color: #0B1224;");
    sidebarWidget->setFixedWidth(260);

    dashboardWidget = new QWidget(centralWidget);
    dashboardWidget->setStyleSheet("background-color: #070D19;");

    mainLayout->addWidget(sidebarWidget);
    mainLayout->addWidget(dashboardWidget);

    barMenu = new QVBoxLayout(sidebarWidget);
    barMenu->setContentsMargins(20, 30, 20, 20);
    barMenu->setSpacing(15);

    titleLabel = new QLabel(sidebarWidget);
    titleLabel->setText("<span style='color: #4EA2E4; font-weight: bold; font-size: 16px;'>SMART</span><br>"
                        "<span style='color: #2D63C8; font-weight: bold; font-size: 20px;'>BACKPACK</span>");
    barMenu->addWidget(titleLabel);
    barMenu->addSpacing(20);

    // Bouton Authentification (Inactif au démarrage)
    btnAuth = new QPushButton("Authentification", sidebarWidget);
    btnAuth->setCheckable(true);
    btnAuth->setFixedHeight(45);
    btnAuth->setStyleSheet("color: #A0AEC0; background-color: transparent; border: none; text-align: left; padding-left: 10px;");
    barMenu->addWidget(btnAuth);

    // Bouton Tableau de bord (Actif au démarrage)
    btnDashboard = new QPushButton(" Tableau de bord ", sidebarWidget);
    btnDashboard->setCheckable(true); // ERREUR 2 CORRIGÉE : Ajout de setCheckable
    btnDashboard->setChecked(true);   // Sélectionné par défaut
    btnDashboard->setFixedHeight(45);
    btnDashboard->setStyleSheet("background-color: #1E3A8A; color: #4EA2E4; border-radius: 5px; text-align: left; padding-left: 10px;");
    barMenu->addWidget(btnDashboard);

    // Bouton Historique (Inactif au démarrage)
    btnHistory = new QPushButton("Historique", sidebarWidget);
    btnHistory->setCheckable(true);
    btnHistory->setFixedHeight(45);
    // ERREUR 2 CORRIGÉE : Fond transparent au démarrage (car il n'est pas encore sélectionné)
    btnHistory->setStyleSheet("color: #A0AEC0; background-color: transparent; border: none; text-align: left; padding-left: 10px;");
    barMenu->addWidget(btnHistory);

    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    barMenu->addItem(spacer);

    statusWidget = new QWidget(sidebarWidget);
    statusWidget->setFixedHeight(80);
    statusWidget->setStyleSheet("background-color: #050A14; border: 1px solid #10B981; border-radius: 8px;");

    statusLayout = new QVBoxLayout(statusWidget);
    statusLayout->setContentsMargins(15, 10, 15, 10);
    btnConnection = new QPushButton("Non connecte", statusWidget);
    //btnConnection
    btnConnection->setFixedHeight(45);
    statusLayout->addWidget(btnConnection);

    barMenu->addWidget(statusWidget);

    // ERREUR 3 CORRIGÉE : On met à jour la couleur bleue au clic
    connect(btnHistory, &QPushButton::clicked, this, [this]() {
        btnDashboard->setChecked(false);
        btnAuth->setChecked(false);
        btnHistory->setChecked(true);
        QString styleInactif = "color: #A0AEC0; background-color: transparent; border: none; text-align: left; padding-left: 10px;";
        btnDashboard->setStyleSheet(styleInactif);
        btnAuth->setStyleSheet(styleInactif);
        btnHistory->setStyleSheet("background-color: #1E3A8A; color: #4EA2E4; border-radius: 5px; text-align: left; padding-left: 10px;");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
