#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core/bus.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    assm = std::make_shared<Assembler>();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pcEdit_editingFinished()
{

}


void MainWindow::on_toolRun_triggered()
{
    QString text = ui->textEdit->toPlainText();
    if(text != "")
        assm->parse(text.toStdString());
}

void MainWindow::on_actionReset_triggered()
{
    assm.reset();
}
