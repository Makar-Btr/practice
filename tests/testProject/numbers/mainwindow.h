#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "numbers.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    int *x;

    Numbers *A, *B;


    friend class testVamsUI;
};
#endif // MAINWINDOW_H
