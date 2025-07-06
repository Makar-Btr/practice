#ifndef COMP_H
#define COMP_H

#include <QString>
#include <vector>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include <algorithm>

struct Comp
{
    QString Name;
    QString Section;
    int Price;

    Comp() : Name(""), Section(""), Price(0) {}
    Comp(const Comp& x) : Name(x.Name), Section(x.Section), Price(x.Price) {}

    Comp& operator= (const Comp& x)
    {
        if (this != &x)
        {
            Name = x.Name;
            Section = x.Section;
            Price = x.Price;
        }
        return *this;
    }

    friend QTextStream& operator>> (QTextStream& in, Comp& X)
    {
        QString line = in.readLine();
        QStringList parts = line.split(", ");
        if (parts.size() == 3) {
            X.Name = parts[0];
            X.Section = parts[1];
            X.Price = parts[2].toInt();
        }
        return in;
    }

    friend QTextStream& operator<< (QTextStream& out, const Comp& X)
    {
        out << X.Name << ", " << X.Section << ", " << X.Price << Qt::endl;
        return out;
    }

    friend bool operator== (const Comp& X, const Comp& Y)
    {
        return X.Name == Y.Name;
    }

    friend bool operator< (const Comp& X, const Comp& Y)
    {
        return X.Name < Y.Name;
    }

    friend bool operator> (const Comp& X, const Comp& Y)
    {
        return X.Name > Y.Name;
    }
};

struct Bag
{
    QString Name;
    int Count;
    QString Section;

    Bag() : Name(""), Count(0), Section("") {}
    Bag(const Bag& x) : Name(x.Name), Count(x.Count), Section(x.Section) {}

    friend QTextStream& operator>> (QTextStream& in, Bag& X)
    {
        QString line = in.readLine();
        QStringList parts = line.split(", ");
        if (parts.size() == 3) {
            X.Name = parts[0];
            X.Count = parts[1].toInt();
            X.Section = parts[2];
        }
        return in;
    }
    friend QTextStream& operator<< (QTextStream& out, const Bag& X)
    {
        out << X.Name << ", " << X.Count << ", " << X.Section << Qt::endl;
        return out;
    }

    Bag& operator= (const Bag& x)
    {
        if (this != &x)
        {
            Name = x.Name;
            Count = x.Count;
            Section = x.Section;
        }
        return *this;
    }

    friend bool operator== (const Bag& X, const Bag& Y)
    {
        return X.Name == Y.Name;
    }

    friend bool operator< (const Bag& X, const Bag& Y)
    {
        return X.Name < Y.Name;
    }

    friend bool operator> (const Bag& X, const Bag& Y)
    {
        return X.Name > Y.Name;
    }

    QString name()
    {
        return Name;
    }
};

template <class T>
class COMP
{
    QString Table_Title;
    int count;
    std::vector<T> M;

public:

    COMP() : count(0) {};

    COMP(const COMP& x) : count(x.count), M(x.M)
    {
    };

    COMP(COMP&& x) : count(x.count), M(std::move(x.M))
    {
        x.count = 0;
    };

    COMP<T>& operator= (const COMP<T>& x)
    {
        if (this != &x)
        {
            count = x.count;
            M = x.M;
        }
        return *this;
    }

    friend QTextStream& operator>> (QTextStream& in, COMP& X)
    {
        T temp;
        X.M.clear();
        while(!in.atEnd())
        {
            in >> temp;
            if (!temp.Name.isEmpty())
                X.M.push_back(temp);
        }
        std::sort(X.M.begin(), X.M.end(), [](const T& a, const T& b) { return a < b; });
        X.count = X.M.size();
        return in;
    }
    friend QTextStream& operator<< (QTextStream& out, const COMP& X)
    {
        for (int i = 0; i < X.count; i++)
        {
            out << X.M[i];
        }
        return out;
    }

    friend COMP<T> operator+ (const COMP<T>& x, const COMP<T>& y)
    {
        COMP<T> z;
        int i = 0, j = 0;
        while(i < x.count && j < y.count)
        {
            if(x.M[i] < y.M[j])
                z.M.push_back(x.M[i++]);
            else if(x.M[i] > y.M[j])
                z.M.push_back(y.M[j++]);
            else
            {
                z.M.push_back(y.M[j++]);
                i++;
            }
        }
        while(i < x.count)
        {
            z.M.push_back(x.M[i++]);
        }
        while(j < y.count)
        {
            z.M.push_back(y.M[j++]);
        }
        z.count = z.M.size();
        return z;
    }

    T& operator[](int i)
    {
        return M[i];
    }
    const T& operator[](int i) const
    {
        return M[i];
    }

    void Rsort()
    {
        std::sort(M.begin(), M.end(), [](const T& a, const T& b) { return a > b; });
    }

    int GetCount() const
    {
        return M.size();
    }
};

#endif // COMP_H
