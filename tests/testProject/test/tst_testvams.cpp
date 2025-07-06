#include <QtTest>

#include "../Numbers/numbers.hpp"

// add necessary includes here

class testVams : public QObject
{
    Q_OBJECT

public:
    //testVams();
    //~testVams();

private slots:
    void testNOD_data();
    void testNOD();

    void testNOK_data();
    void testNOK();

    void testSimple_data();
    void testSimple();

    void testArmstrong_data();
    void testArmstrong();

private:
    Numbers A, B;
};

//testVams::testVams() {}

//testVams::~testVams() {}


void testVams::testNOD_data()
{
    QTest::addColumn<int>("a");
    QTest::addColumn<int>("b");
    QTest::addColumn<int>("result");

    QTest::newRow("1") << 1 << 1 << 1;
    QTest::newRow("2") << 2000000000 << 2 << 2;
    QTest::newRow("3") << 2 << 11 << 1;
}
void testVams::testNOD()
{
    QFETCH(int, a);
    QFETCH(int, b);
    QFETCH(int, result);
    A = a; B = b;
    QCOMPARE(A.NOD(B), result);
    QCOMPARE(B.NOD(A), result);
}

void testVams::testNOK_data()
{
    QTest::addColumn<int>("a");
    QTest::addColumn<int>("b");
    QTest::addColumn<int>("result");

    QTest::newRow("1") << 7 << 5 << 35;
    QTest::newRow("2") << 2 << 10 << 10;
}
void testVams::testNOK()
{
    QFETCH(int, a);
    QFETCH(int, b);
    QFETCH(int, result);
    A = a; B = b;
    QCOMPARE(A.NOK(B), result);
    QCOMPARE(B.NOK(A), result);
}

void testVams::testSimple_data()
{
    QTest::addColumn<int>("a");

    QTest::newRow("1") << 2;
    QTest::newRow("2") << 17;
    QTest::newRow("3") << 23;
    QTest::newRow("failed test 1") << 1;
    QTest::newRow("failed test 2") << 0;
}
void testVams::testSimple()
{
    QFETCH(int, a);
    A = a;
    if(A.IsSimple() == false)
    {
        QVERIFY(!A.IsSimple());
    }
    QVERIFY(A.IsSimple());
}

void testVams::testArmstrong_data()
{
    QTest::addColumn<int>("a");

    QTest::newRow("1") << 153;
    QTest::newRow("2") << 370;
    QTest::newRow("3") << 371;
    QTest::newRow("4") << 9474;
    QTest::newRow("5") << 0;
    QTest::newRow("failed test") << 10;
}
void testVams::testArmstrong()
{
    QFETCH(int, a);
    A = a;
    if(!A.is_Armstrong())
    {
        QVERIFY(!A.is_Armstrong());
    }
    QVERIFY(A.is_Armstrong());
}

QTEST_APPLESS_MAIN(testVams)

#include "tst_testvams.moc"
