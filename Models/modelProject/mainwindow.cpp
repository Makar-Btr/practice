#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , MM1(new objModel())
    , MM2(new objModel())
    , MM3(new objModel())
    , MK1(new objModel2())
    , MK2(new objModel2())
    , MK3(new objModel2())
{
    ui->setupUi(this);

    M1 = new COMP<Comp>;
    M2 = new COMP<Comp>;
    M3 = new COMP<Comp>;

    K1 = new COMP<Bag>;
    K2 = new COMP<Bag>;
    K3 = new COMP<Bag>;
}

MainWindow::~MainWindow()
{
    delete ui;

    delete M1;
    delete M2;
    delete M3;

    delete K1;
    delete K2;
    delete K3;
}

void MainWindow::fillTableFromCOMP1(QTableWidget* table, const COMP<Comp>& Comp)
{
    table->clearContents();
    table->setRowCount(Comp.GetCount());
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << "имя" << "секция" << "цена");

    for (int i = 0; i < Comp.GetCount(); ++i)
    {
        QTableWidgetItem* nameItem = new QTableWidgetItem(Comp[i].Name);
        QTableWidgetItem* sectionItem = new QTableWidgetItem(Comp[i].Section);
        QTableWidgetItem* priceItem = new QTableWidgetItem(QString::number(Comp[i].Price));

        table->setItem(i, 0, nameItem);
        table->setItem(i, 1, sectionItem);
        table->setItem(i, 2, priceItem);
    }
}

void MainWindow::fillTableFromCOMP2(QTableWidget* table, const COMP<Bag>& Bag)
{
    table->clearContents();
    table->setRowCount(Bag.GetCount());
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << "имя" << "количество" << "секция");

    for (int i = 0; i < Bag.GetCount(); ++i)
    {
        QTableWidgetItem* nameItem = new QTableWidgetItem(Bag[i].Name);
        QTableWidgetItem* countItem = new QTableWidgetItem(QString::number(Bag[i].Count));
        QTableWidgetItem* sectionItem = new QTableWidgetItem(Bag[i].Section);

        table->setItem(i, 0, nameItem);
        table->setItem(i, 1, countItem);
        table->setItem(i, 2, sectionItem);
    }
}

void MainWindow::on_M123_clicked()
{
    QFile filename1("in1.txt");
    if (!filename1.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in1(&filename1);

    QFile filename2("in2.txt");
    if (!filename2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        filename1.close();
        return;
    }
    QTextStream in2(&filename2);

    QFile filename3("out1.txt");
    if (!filename3.open(QIODevice::WriteOnly | QIODevice::Text)) {
        filename1.close();
        filename2.close();
        return;
    }
    QTextStream out1(&filename3);

    in1 >> *M1;
    in2 >> *M2;

    MM1->setModel(M1);
    MM2->setModel(M2);

    ui->tableView_1->setModel(MM1);
    ui->tableView_1->resizeColumnsToContents();
    ui->tableView_2->setModel(MM2);
    ui->tableView_2->resizeColumnsToContents();

    *M3 = *M1 + *M2;

    MM3->setModel(M3);
    ui->tableView_3->setModel(MM3);
    ui->tableView_3->resizeColumnsToContents();

    out1 << *M3;

    filename1.close();
    filename2.close();
    filename3.close();
}

void MainWindow::on_K123_clicked()
{
    QFile filename1("in3.txt");
    if (!filename1.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in3(&filename1);

    QFile filename2("in4.txt");
    if (!filename2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        filename1.close();
        return;
    }
    QTextStream in4(&filename2);

    QFile filename3("out2.txt");
    if (!filename3.open(QIODevice::WriteOnly | QIODevice::Text)) {
        filename1.close();
        filename2.close();
        return;
    }
    QTextStream out2(&filename3);

    in3 >> *K1;
    in4 >> *K2;

    MK1->setModel(K1);
    MK2->setModel(K2);
    ui->tableView_4->setModel(MK1);
    ui->tableView_4->resizeColumnsToContents();
    ui->tableView_5->setModel(MK2);
    ui->tableView_5->resizeColumnsToContents();

    *K3 = *K1 + *K2;
    out2 << *K3;

    MK3->setModel(K3);
    ui->tableView_6->setModel(MK3);
    ui->tableView_6->resizeColumnsToContents();

    filename1.close();
    filename2.close();
    filename3.close();
}

void MainWindow::on_RsortM_clicked()
{
    M1->Rsort();
    MM1->setModel(M1);
    ui->tableView_1->setModel(MM1);
    ui->tableView_1->resizeColumnsToContents();
}

void MainWindow::on_RsortK_clicked()
{
    K1->Rsort();
    MK1->setModel(K1);
    ui->tableView_4->setModel(MK1);
    ui->tableView_4->resizeColumnsToContents();
}



