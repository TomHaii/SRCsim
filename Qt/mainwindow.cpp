#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Run_clicked(){
    QString text = ui->textEdit->toPlainText();
    std::cout << "Running\n" << text.toStdString() << std::endl;
}

