#ifndef BOT_H
#define BOT_H
#include <QObject>
#include<QVector>

struct Cell{
    int x,y;
    Cell(){};
    Cell(int x, int y): x(x), y(y){}
};

class Bot : public QObject
{
    Q_OBJECT
public:
    explicit Bot(QObject *parent = nullptr);

private:
    QString level;
public:
   // Bot();
    Bot(QString level): level(level){};

    QString getLevel() const;
    void setLevel(const QString &newLevel);
    Cell readGame(QVector<Cell> &replay);

signals:
};

#endif // BOT_H
