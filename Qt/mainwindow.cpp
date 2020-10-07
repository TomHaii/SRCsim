#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "core/bus.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    assm = new Assembler();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete assm;
}


void MainWindow::on_pcEdit_editingFinished()
{

}


void MainWindow::on_toolRun_triggered()
{
    QString text = ui->textEdit->toPlainText();
    if(text != "")
        assm->parse(text.toStdString());
    print_registers();

}

void MainWindow::on_actionReset_triggered()
{
    assm->reset_program();
    print_registers();
}

void MainWindow::print_registers()
{
    ui->pcEdit->setText(QString::number(assm->p_pc()));
    ui->r0_edit->setText(QString::number(assm->p_register(0)));
    ui->r1_edit->setText(QString::number(assm->p_register(1)));
    ui->r2_edit->setText(QString::number(assm->p_register(2)));
    ui->r3_edit->setText(QString::number(assm->p_register(3)));
    ui->r4_edit->setText(QString::number(assm->p_register(4)));
    ui->r5_edit->setText(QString::number(assm->p_register(5)));
    ui->r6_edit->setText(QString::number(assm->p_register(6)));
    ui->r7_edit->setText(QString::number(assm->p_register(7)));
    ui->r8_edit->setText(QString::number(assm->p_register(8)));
    ui->r9_edit->setText(QString::number(assm->p_register(9)));
    ui->r10_edit->setText(QString::number(assm->p_register(10)));
    ui->r11_edit->setText(QString::number(assm->p_register(11)));
    ui->r12_edit->setText(QString::number(assm->p_register(12)));
    ui->r13_edit->setText(QString::number(assm->p_register(13)));
    ui->r14_edit->setText(QString::number(assm->p_register(14)));
    ui->r15_edit->setText(QString::number(assm->p_register(15)));
    ui->r16_edit->setText(QString::number(assm->p_register(16)));
    ui->r17_edit->setText(QString::number(assm->p_register(17)));
    ui->r18_edit->setText(QString::number(assm->p_register(18)));
    ui->r19_edit->setText(QString::number(assm->p_register(19)));
    ui->r20_edit->setText(QString::number(assm->p_register(20)));
    ui->r21_edit->setText(QString::number(assm->p_register(21)));
    ui->r22_edit->setText(QString::number(assm->p_register(22)));
    ui->r23_edit->setText(QString::number(assm->p_register(23)));
    ui->r24_edit->setText(QString::number(assm->p_register(24)));
    ui->r25_edit->setText(QString::number(assm->p_register(25)));
    ui->r26_edit->setText(QString::number(assm->p_register(26)));
    ui->r27_edit->setText(QString::number(assm->p_register(27)));
    ui->r28_edit->setText(QString::number(assm->p_register(28)));
    ui->r29_edit->setText(QString::number(assm->p_register(29)));
    ui->r30_edit->setText(QString::number(assm->p_register(30)));
    ui->r31_edit->setText(QString::number(assm->p_register(31)));
}

void MainWindow::on_write_memory_button_clicked()
{
    QString address = ui->address_edit->text();
    QString value = ui->mem_value_edit->text();
    bool isAddressNum = false;
    bool isValNum = false;
    uint32_t data_val = value.toUInt(&isValNum);
    uint32_t address_val = address.toUInt(&isAddressNum);
    if(isAddressNum && isValNum){
        assm->write_to_memory(address_val, data_val);
        ui->outputBox->append("Inserting the value " + value + " at address " + address);
    }
    else
        ui->outputBox->append("Please insert a valid address/value");
}

void MainWindow::on_read_memory_button_clicked()
{
    QString address = ui->address_edit->text();
    bool isNum = false;
    uint32_t address_val = address.toUInt(&isNum);
    if(isNum)
        ui->outputBox->append("Value at address " + address + " is " + QString::number(assm->print_memory(address_val)));
    else
        ui->outputBox->append("Please insert a valid address");

}

void MainWindow::on_actionCredits_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Made By Tom Levy");
    msgBox.addButton(QMessageBox::Close);
    msgBox.exec();

}
