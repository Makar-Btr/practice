#include <QtTest>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include "../Numbers/mainwindow.h"
#include "../Numbers/ui_mainwindow.h"

// add necessary includes here

class testVamsUI : public QObject
{
    Q_OBJECT

public:
    testVamsUI();
    ~testVamsUI();

private slots:
    void init();

    void testUiDynamics();

    void testCalculations_data();
    void testCalculations();

private:
    MainWindow mainwindow;
};

testVamsUI::testVamsUI() {}

testVamsUI::~testVamsUI() {}

void testVamsUI::init()
{
    mainwindow.ui->first->clear();
    mainwindow.ui->second->clear();
    mainwindow.ui->res->clear();
    mainwindow.ui->comboBox->setCurrentIndex(0);
    mainwindow.ui->second->show();
}

void testVamsUI::testUiDynamics()
{
    QVERIFY(mainwindow.ui->second->isVisible());
    mainwindow.ui->comboBox->setCurrentIndex(2);

    QVERIFY(!mainwindow.ui->second->isVisible());

    mainwindow.ui->comboBox->setCurrentIndex(0);

    QVERIFY(mainwindow.ui->second->isVisible());
}

void testVamsUI::testCalculations_data()
{
    QTest::addColumn<int>("optionIndex");
    QTest::addColumn<QString>("num1");
    QTest::addColumn<QString>("num2");
    QTest::addColumn<QString>("expected");

    QTest::newRow("NOD_normal")       << 0 << "54" << "24" << "6";

    QTest::newRow("NOK_normal")       << 1 << "21" << "6" << "42";

    QTest::newRow("IsPrime_true")     << 2 << "13" << "" << "True";
    QTest::newRow("IsPrime_false")    << 2 << "12" << "" << "False";
    QTest::newRow("IsPrime_one")      << 2 << "1"  << "" << "False";

    QTest::newRow("IsArmstrong_true") << 3 << "153" << "" << "True";
    QTest::newRow("IsArmstrong_false")<< 3 << "154" << "" << "False";
    QTest::newRow("IsArmstrong_zero") << 3 << "0"   << "" << "True";
}

void testVamsUI::testCalculations()
{
    QFETCH(int, optionIndex);
    QFETCH(QString, num1);
    QFETCH(QString, num2);
    QFETCH(QString, expected);

    mainwindow.ui->comboBox->setCurrentIndex(optionIndex);
    QTest::keyClicks(mainwindow.ui->first, num1);
    QTest::keyClicks(mainwindow.ui->second, num2);

    QTest::mouseClick(mainwindow.ui->pushButton, Qt::LeftButton);

    QCOMPARE(mainwindow.ui->res->text(), expected);
}


QTEST_MAIN(testVamsUI)

//#include "tst_testvamsui.moc"
