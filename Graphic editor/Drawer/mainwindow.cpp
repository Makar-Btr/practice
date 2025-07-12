#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog> // Include for QColorDialog
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new paintScene();       // Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);                // Устанавливаем сглаживание

    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void MainWindow::on_actionRed_triggered()
{
    scene->setPenColor(Qt::red);
    scene->setDrawMode(paintScene::ModeDraw);
}

void MainWindow::on_actionGreen_triggered()
{
    scene->setPenColor(Qt::green);
    scene->setDrawMode(paintScene::ModeDraw);
}

void MainWindow::on_actionBlue_triggered()
{
    scene->setPenColor(Qt::blue);
    scene->setDrawMode(paintScene::ModeDraw);
}

void MainWindow::on_actionClear_triggered()
{
    scene->clear();
}

void MainWindow::on_actionCustomColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid()) {
        scene->setPenColor(color);
        scene->setDrawMode(paintScene::ModeDraw);
    }
}

void MainWindow::on_actionSquare_triggered()
{
    scene->setTypeFigure(paintScene::SquareType);
    scene->setDrawMode(paintScene::ModeFigure);
}

void MainWindow::on_actionRomb_triggered()
{
    scene->setTypeFigure(paintScene::RombType);
    scene->setDrawMode(paintScene::ModeFigure);
}

void MainWindow::on_actionTriangle_triggered()
{
    scene->setTypeFigure(paintScene::TriangleType);
    scene->setDrawMode(paintScene::ModeFigure);
}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Figures", "", "Text Files (*.txt)");
    if (!filename.isEmpty()) {
        QFileInfo fileInfo(filename);
        // Добавить расширение .txt, если пользователь не указал расширение
        if (fileInfo.suffix().isEmpty()) {
            filename += ".txt";
        }
        if (fileInfo.exists()) {
            auto reply = QMessageBox::question(this, "Overwrite File",
                                               "File already exists. Overwrite?",
                                               QMessageBox::Yes | QMessageBox::No);
            if (reply != QMessageBox::Yes) {
                return;
            }
        }
        if (!scene->saveFigures(filename)) {
            QMessageBox::warning(this, "Error", "Failed to save figures!");
        }
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load Figures", "", "Text Files (*.txt)");
    if (!filename.isEmpty()) {
        if (!scene->loadFigures(filename)) {
            QMessageBox::warning(this, "Error", "Failed to load figures!");
        }
    }
}


