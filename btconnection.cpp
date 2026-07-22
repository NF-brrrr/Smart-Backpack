#include "btconnection.h"
#include <QDebug>

BtConnection::BtConnection(QObject *parent) : QObject(parent), controller(nullptr), service(nullptr){
    discoveryAgent= new QBluetoothDeviceDiscoveryAgent(this);
    discoveryAgent->setLowEnergyDiscoveryTimeout(5000);

    connect(discoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,this,&BtConnection::deviceDiscovered);
    connect(discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,this,&BtConnection::scanFinished);

}

void BtConnection::startScan(){
    qDebug() << "Starting scan...";
    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void BtConnection::deviceDiscovered(const QBluetoothDeviceInfo &device){
    if (device.name() == "ESP32S3_BLE_Demo") {
        qDebug() << "Found ESP32-S3! Stopping scan...";
        discoveryAgent->stop();

        // Initialize BLE Controller
        if (controller) {
            controller->disconnectFromDevice();
            delete controller;
        }

        controller = QLowEnergyController::createCentral(device, this);

        connect(controller, &QLowEnergyController::connected, this, &BtConnection::controllerConnected);
        connect(controller, &QLowEnergyController::disconnected, this, &BtConnection::controllerDisconnected);
        connect(controller, &QLowEnergyController::serviceDiscovered, this, &BtConnection::serviceDiscovered);
        connect(controller, &QLowEnergyController::discoveryFinished, this, &BtConnection::discoveryFinished);

        qDebug() << "Connecting to peripheral...";
        controller->connectToDevice();
    }
}

void BtConnection::scanFinished(){
    qDebug() << "Scan complete.";
}

void BtConnection::controllerConnected(){
    qDebug() << "Discovering Service...";
    controller->discoverServices();
}

void BtConnection::controllerDisconnected(){
    qDebug() << "Disconnected";
    service=nullptr;
}

void BtConnection::discoveryFinished(){
    qDebug() << "Service discovery finished. Handling services...";
    service = controller->createServiceObject(NUS_SERVICE_UUID,this);

    if (!service){
        qDebug() << "Could not map service object.";
        return;
    }

    connect(service,&QLowEnergyService::stateChanged,this,&BtConnection::serviceStateChanged);
    connect(service,&QLowEnergyService::characteristicChanged,this,&BtConnection::characteristicChanged);

    service->discoverDetails();























}