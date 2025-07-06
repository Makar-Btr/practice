#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    x = new int;

    A = new Numbers;
    B = new Numbers;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_activated(int index)
{
    if(index == 0)
    {
        ui->second->setEnabled(true);
        *x = 0;
    }
    if(index == 1)
    {
        ui->second->setEnabled(true);
        *x = 1;
    }
    if(index == 2)
    {
        ui->second->setEnabled(false);
        *x = 2;
    }
    if(index == 3)
    {
        ui->second->setEnabled(false);
        *x = 3;
    }
}


void MainWindow::on_pushButton_clicked()
{
    ui->res->clear();
    QString f = ui->first->text(), s = ui->second->text();
    *A = f.toInt(); *B = s.toInt();

    if(*x == 0)
    {
        ui->res->setText(QString::number(A->NOD(*B)));
    }
    if(*x == 1)
    {
        ui->res->setText(QString::number(A->NOK(*B)));
    }
    if(*x == 2)
    {

        if (A->IsSimple())
        {
            ui->res->setText(f + " - простое число");
        }
        else
        {
            ui->res->setText(f + " - не простое число");
        }
    }
    if(*x == 3)
    {
        if (A->is_Armstrong())
        {
            ui->res->setText(f + " - число Армстронга");
        }
        else
        {
            ui->res->setText(f + " - не число Армстронга");
        }
    }
}

