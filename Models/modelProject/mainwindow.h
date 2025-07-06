#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "model.h"
#include <QMainWindow>
#include <QTableWidget>
#include <vector>


#include "comp.h"
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
    void on_M123_clicked();

    void on_K123_clicked();

    void on_RsortM_clicked();

    void on_RsortK_clicked();


private:
    Ui::MainWindow *ui;

    COMP<Comp> *M1, *M2, *M3;
    COMP<Bag> *K1, *K2, *K3;
    objModel *MM1, *MM2, *MM3;
    objModel2 *MK1, *MK2, *MK3;
    void fillTableFromCOMP1(QTableWidget*, const COMP<Comp>&);
    void fillTableFromCOMP2(QTableWidget*, const COMP<Bag>&);
};
#endif // MAINWINDOW_H
