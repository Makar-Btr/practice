#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->labelLeft->setScaledContents(true);
    ui->labelRight->setScaledContents(true);
    ui->labelResult->setScaledContents(true);

    ui->labelResult->setVisible(false);
    ui->labelRight->setVisible(false);
    ui->labelLeft->setVisible(false);
}

void MainWindow::on_pushButtonAnimate_clicked()
{
    ui->labelResult->setVisible(false);
    ui->labelLeft->setVisible(true);
    ui->labelRight->setVisible(true);

    QRect leftStart = ui->labelLeft->geometry();
    QRect leftEnd = leftStart;
    leftEnd.moveTopLeft(ui->labelResult->geometry().topLeft());

    QRect rightStart = ui->labelRight->geometry();
    QRect rightEnd = rightStart;
    rightEnd.moveTopLeft(ui->labelResult->geometry().topLeft());

    QPropertyAnimation *animLeft = new QPropertyAnimation(ui->labelLeft, "geometry", this);
    animLeft->setDuration(1000);
    animLeft->setStartValue(leftStart);
    animLeft->setEndValue(leftEnd);

    QPropertyAnimation *animRight = new QPropertyAnimation(ui->labelRight, "geometry", this);
    animRight->setDuration(1000);
    animRight->setStartValue(rightStart);
    animRight->setEndValue(rightEnd);

    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->addAnimation(animLeft);
    group->addAnimation(animRight);

    connect(group, &QParallelAnimationGroup::finished, this, &MainWindow::showResultLabel);

    group->start();
}


void MainWindow::showResultLabel()
{
    ui->labelLeft->setVisible(false);
    ui->labelRight->setVisible(false);
    ui->labelResult->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

