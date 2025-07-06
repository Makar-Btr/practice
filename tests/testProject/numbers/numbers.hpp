#ifndef NUMBERS_H
#define NUMBERS_H

#include <QTextStream>
#include <QString>
#include <cmath>

class Numbers
{
    int a;

public:

    Numbers() : a(0) {}

    Numbers(int A) : a(A) {}

    Numbers(const Numbers& X) : a(X.a) {}

    Numbers& operator=(const Numbers& X) {
        if (this != &X) {
            a = X.a;
        }
        return *this;
    }

    Numbers& operator=(const int& X) {
        this->a = X;
        return *this;
    }

    friend bool operator== (const Numbers& X, const Numbers& Y)
    {
        return X.a == Y.a;
    }

    friend bool operator== (const Numbers& X, const int& Y)
    {
        return X.a == Y;
    }

    int NOD(const Numbers& X)
    {
        int a1 = a, b1 = X.a;
        while (a1 != 0 && b1 != 0) {
            if (a1 > b1) {
                a1 %= b1;
            }
            else {
                b1 %= a1;
            }
        }

        return (a1+b1);
    }

    int NOK(const Numbers& X)
    {
        return abs(a*X.a)/this->NOD(X);
    }

    bool IsSimple()
    {
        int a1 = a;
        if(a1 == 1 || a1 == 0)
        {
            return false;
        }
        if (a1 == 2) {
            return true;
        }
        if (a1 % 2 == 0) {
            return false;
        }
        for (int i = 3; i <= sqrt(a1); i += 2) {
            if (a1 % i == 0) {
                return false;
            }
        }
        return true;
    }

    unsigned int count_numb() {
        unsigned int x = abs(a);
        unsigned int res = 0;
        if (x == 0)
        {
            res = 1;
            return res;
        }
        while (x != 0)
        {
            x /= 10;
            res++;
        }
        return res;
    }

    bool is_Armstrong() {
        unsigned int sum = 0, y = abs(a), z = y, k = 1;
        k = count_numb();
        unsigned int ost;
        bool res = false;
        while (y != 0)
        {
            ost = y % 10;
            ost = pow(ost, k);
            sum += ost;
            y /= 10;
        }

        if (sum == z)
            res = true;
        return res;
    }

    friend QTextStream& operator>> (QTextStream& in, Numbers& X)
    {
        in >> X.a;
        return in;
    }

    friend QTextStream& operator<< (QTextStream& out, const Numbers& X)
    {
        out << X.a;
        return out;
    }


};

#endif // NUMBERS_H
