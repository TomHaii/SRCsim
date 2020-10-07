#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <iostream>
#include <assembler\assembler.h>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_pcEdit_editingFinished();


    void on_toolRun_triggered();

    void on_actionReset_triggered();

    void print_registers();
    void on_write_memory_button_clicked();

    void on_read_memory_button_clicked();

    void on_actionCredits_triggered();

private:
    Ui::MainWindow *ui;
    Assembler * assm;
};
#endif // MAINWINDOW_H
