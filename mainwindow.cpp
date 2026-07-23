#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino = new QSerialPort;

    setWindowTitle("Smart backpack");
    resize(1280, 800);
    this->setStyleSheet("QMainWindow { background-color: #070D19; }");
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    sidebarWidget = new QWidget(centralWidget);
    sidebarWidget->setFixedWidth(260);

    sidebarWidget->setStyleSheet(
        "QWidget { background-color: #0B1224; }"
        "QPushButton { color: white; border: none; text-align: left; padding-left: 10px; background: transparent; height: 45px; font-size: 14px; }"
        "QPushButton:checked { background-color: blue; border-radius: 5px; font-weight: bold; }"
        );

    dashboardWidget = new QWidget(centralWidget);
    dashboardWidget->setStyleSheet("background-color: #070D19;");

    mainLayout->addWidget(sidebarWidget);
    mainLayout->addWidget(dashboardWidget);

    barMenu = new QVBoxLayout(sidebarWidget);
    barMenu->setContentsMargins(20, 30, 20, 20);
    barMenu->setSpacing(15);

    titleLabel = new QLabel(sidebarWidget);
    titleLabel->setText("<b style='color:#4EA2E4; font-size:16px;'>SMART</b><br>"
                        "<b style='color:#2D63C8; font-size:20px;'>BACKPACK</b>");
    barMenu->addWidget(titleLabel);
    barMenu->addSpacing(20);

    btnAuth = new QPushButton("Authentification", sidebarWidget);
    btnAuth->setCheckable(true);
    barMenu->addWidget(btnAuth);

    btnDashboard = new QPushButton("Tableau de bord", sidebarWidget);
    btnDashboard->setCheckable(true);
    barMenu->addWidget(btnDashboard);

    btnHistory = new QPushButton("Historique", sidebarWidget);
    btnHistory->setCheckable(true);
    barMenu->addWidget(btnHistory);

    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    barMenu->addItem(spacer);

    statusWidget = new QWidget(sidebarWidget);
    statusWidget->setFixedHeight(80);
    statusWidget->setStyleSheet("background-color: red; border-radius: 8px;");

    statusLayout = new QVBoxLayout(statusWidget);
    statusLayout->setContentsMargins(10, 10, 10, 10);

    btnConnection = new QPushButton("Non connecte", statusWidget);
    btnConnection->setCheckable(true);
    btnConnection->setFixedHeight(45);
    btnConnection->setStyleSheet("background-color: transparent; border: none; color: white; font-weight: bold;");
    statusLayout->addWidget(btnConnection);

    barMenu->addWidget(statusWidget);

    connect(btnAuth, &QPushButton::clicked, this, [=]() {
        btnAuth->setChecked(true);
        btnDashboard->setChecked(false);
        btnHistory->setChecked(false);
    });

    connect(btnDashboard, &QPushButton::clicked, this, [=]() {
        btnAuth->setChecked(false);
        btnDashboard->setChecked(true);
        btnHistory->setChecked(false);
        tableauDebord();
    });

    connect(btnHistory, &QPushButton::clicked, this, [=]() {
        btnAuth->setChecked(false);
        btnDashboard->setChecked(false);
        btnHistory->setChecked(true);
    });

    connect(btnConnection, &QPushButton::clicked, this, [=](){ verifyConnection(); });
}

void MainWindow::verifyConnection(){
    if(arduino->isOpen()){
        arduino->close();
        statusWidget->setStyleSheet("background-color: red; border-radius: 8px;");
        btnConnection->setStyleSheet("background-color: transparent; border: none; color: white; font-weight: bold;");
        btnConnection->setText("Non connecte");
        return;
    }

    bool arduinoFound = false;
    QString targetedPortName = "";

    const auto ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &portInfo : ports){
        if(portInfo.hasVendorIdentifier() && (portInfo.vendorIdentifier() == 0x2341 || portInfo.vendorIdentifier() == 0x1a86)){
            arduinoFound = true;
            targetedPortName = portInfo.systemLocation();
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
        statusWidget->setStyleSheet("background-color: red; border-radius: 8px;");
        btnConnection->setStyleSheet("background-color: transparent; border: none; color: white; font-weight: bold;");
        btnConnection->setText("Non connecte");
        qDebug() << "Aucun périphérique Arduino détecté";
    }

    if(arduino->open(QIODevice::ReadWrite)){
        statusWidget->setStyleSheet("background-color: green; border-radius: 8px;");
        btnConnection->setStyleSheet("background-color: transparent; border: none; color: white; font-weight: bold;");
        btnConnection->setText("Connecte");
    }
    else{
        statusWidget->setStyleSheet("background-color: red; border-radius: 8px;");
        btnConnection->setStyleSheet("background-color: transparent; border: none; color: white; font-weight: bold;");
        btnConnection->setText("Non connecte");
        qDebug() << "Arduino trouvé sur" << targetedPortName << "mais échec de l'ouverture :" << arduino->errorString();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tableauDebord()
{
    QVBoxLayout *dashlayout = new QVBoxLayout(dashboardWidget);
    dashlayout->setContentsMargins(30,30,30,30);
    dashlayout->setSpacing(20);
    QLabel *dashTitle = new QLabel("<b style='color: white; font-size: 22px;'>Tableau de bord</b><br>"
                                   "<span style='color: #718096; font-size: 13px;'>Aperçu en temps réel de votre sac intelligent</span>", dashboardWidget);
    dashlayout->addWidget(dashTitle);
    QGridLayout *cardsGrid = new QGridLayout();
    cardsGrid->setSpacing(20);
    QString cardStyle = "QWidget { background-color: #0B1224; border: 1px solid #1E293B; border-radius: 12px; }";

    /*QWidget *cardEtat =  new QWidget(dashboardWidget);
    cardEtat->setStyleSheet(cardStyle);
    QVBoxLayout *layoutEtat = new QVBoxLayout(cardEtat);
    layoutEtat->setContentsMargins(20,20,20,20);
    QLabel *labelTitre = new QLabel("Etat du sac",cardEtat);
    QLabel *labelEtat = new QLabel("Fermé & Sécurisé",cardEtat);

    layoutEtat->addWidget(labelTitre);
    layoutEtat->addWidget(labelEtat);

    dashlayout->addWidget(cardEtat);

    QWidget *cardHumidite= new QWidget(dashboar
*/
    QWidget *cardStatus = new QWidget(dashboardWidget);
    cardStatus->setStyleSheet(cardStyle);
    QVBoxLayout *layoutStatus = new QVBoxLayout(cardStatus);
    layoutStatus->setContentsMargins(20, 20, 20, 20);

    QLabel *lblStatusTitle = new QLabel("<span style='color: #A0AEC0; font-size: 13px; font-weight: bold;'>ÉTAT DU SAC</span>", cardStatus);
    QLabel *lblStatusVal = new QLabel("<span style='color: #10B981; font-size: 20px; font-weight: bold;'>Fermé & Sécurisé</span>", cardStatus);
    layoutStatus->addWidget(lblStatusTitle);
    layoutStatus->addWidget(lblStatusVal);
    layoutStatus->addStretch();

    //CARTE 2 : Authentification ---
    QWidget *cardAuth = new QWidget(dashboardWidget);
    cardAuth->setStyleSheet(cardStyle);
    QVBoxLayout *layoutAuth = new QVBoxLayout(cardAuth);
    layoutAuth->setContentsMargins(20, 20, 20, 20);

    QLabel *lblAuthTitle = new QLabel("<span style='color: #A0AEC0; font-size: 13px; font-weight: bold;'>AUTHENTIFICATION</span>", cardAuth);
    QLabel *lblAuthVal = new QLabel("<span style='color: #4EA2E4; font-size: 20px; font-weight: bold;'>Verrouillé</span>", cardAuth);
    layoutAuth->addWidget(lblAuthTitle);
    layoutAuth->addWidget(lblAuthVal);
    layoutAuth->addStretch();

    // CARTE 3 : Humidité ---
    QWidget *cardHum = new QWidget(dashboardWidget);
    cardHum->setStyleSheet(cardStyle);
    QVBoxLayout *layoutHum = new QVBoxLayout(cardHum);
    layoutHum->setContentsMargins(20, 20, 20, 20);

    QLabel *lblHumTitle = new QLabel("<span style='color: #A0AEC0; font-size: 13px; font-weight: bold;'>HUMIDITÉ INTERNE</span>", cardHum);
    QLabel *lblHumVal = new QLabel("<span style='color: white; font-size: 28px; font-weight: bold;'>42 %</span>", cardHum);
    QLabel *lblHumSub = new QLabel("<span style='color: #10B981; font-size: 12px;'>Niveau optimal</span>", cardHum);
    layoutHum->addWidget(lblHumTitle);
    layoutHum->addWidget(lblHumVal);
    layoutHum->addWidget(lblHumSub);
    layoutHum->addStretch();

    // CARTE 4 : Batterie ---
    QWidget *cardBat = new QWidget(dashboardWidget);
    cardBat->setStyleSheet(cardStyle);
    QVBoxLayout *layoutBat = new QVBoxLayout(cardBat);
    layoutBat->setContentsMargins(20, 20, 20, 20);

    QLabel *lblBatTitle = new QLabel("<span style='color: #A0AEC0; font-size: 13px; font-weight: bold;'>BATTERIE</span>", cardBat);
    QLabel *lblBatVal = new QLabel("<span style='color: white; font-size: 28px; font-weight: bold;'>85 %</span>", cardBat);
    QLabel *lblBatSub = new QLabel("<span style='color: #10B981; font-size: 12px;'>En fonctionnement</span>", cardBat);
    layoutBat->addWidget(lblBatTitle);
    layoutBat->addWidget(lblBatVal);
    layoutBat->addWidget(lblBatSub);
    layoutBat->addStretch();

    cardsGrid->addWidget(cardStatus, 0, 0);
    cardsGrid->addWidget(cardAuth, 0, 1);
    cardsGrid->addWidget(cardHum, 1, 0);
    cardsGrid->addWidget(cardBat, 1, 1);

    dashlayout->addLayout(cardsGrid);
    dashlayout->addStretch();
    QSpacerItem *space = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    dashlayout->addItem(space);

}
