#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serial.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      ledStatus('0'){
    ui->setupUi(this);
    try{
        device = std::make_unique<Serial>("/dev/ttyACM0", 9600);
    }catch(const char* error){
        ui->errorView->setText(error);
        ui->redButton->hide();
        ui->greenButton->hide();
        ui->blueButton->hide();
    }
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_redButton_clicked(){
    ledStatus ^= 1;
    device->sendChar(ledStatus);
}


void MainWindow::on_greenButton_clicked(){
    ledStatus ^= 2;
    device->sendChar(ledStatus);
}


void MainWindow::on_blueButton_clicked(){
    ledStatus ^= 4;
    device->sendChar(ledStatus);
}

