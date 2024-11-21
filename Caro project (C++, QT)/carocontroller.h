#ifndef CAROCONTROLLER_H
#define CAROCONTROLLER_H
#include<bot.h>
#include <QObject>
#include<QVector>
#include<QVector2D>
class CaroController : public QObject
{
    Q_OBJECT
   // Q_PROPERTY(QVariantList matrix READ matrix CONSTANT)
public:
    explicit CaroController(QObject *parent = nullptr);

    QVector<QVector<int> > getCaro() const;
    void setCaro(const QVector<QVector<int> > &newCaro);

    void setDefaultCaro();

   // Q_INVOKABLE QVariantList matrix() const;
    QVector<int> getMatrix() const;
    void setMatrix(const QVector<int> &newMatrix);

    void setMatrix();
    Q_INVOKABLE  void move(int index);

    Q_INVOKABLE int checkWin();
    Q_INVOKABLE int getShowWinScreen() const;
    void setShowWinScreen(int newShowWinScreen);

    Q_INVOKABLE void playWithBot(int index);
    void makeBotMove();
    Q_INVOKABLE void replayLastMatch();
    void replayNextMove();
signals:
    void caroChanged();

    void matrixChanged();

    void showWinScreenChanged();

private:
    QVector< QVector<int> > caro;
    Q_PROPERTY(QVector<QVector<int> > caro READ getCaro WRITE setCaro NOTIFY caroChanged FINAL)

    QVector<int> matrix;
    int numberOfX = 0, numberOfO = 0;
    int showWinScreen=0;

    QVector<Cell> replay;
    int     replayIndex;
    Bot bot;
    Q_PROPERTY(QVector<int> matrix READ getMatrix WRITE setMatrix NOTIFY matrixChanged FINAL)
    Q_PROPERTY(int showWinScreen READ getShowWinScreen WRITE setShowWinScreen NOTIFY showWinScreenChanged FINAL)
};

#endif // CAROCONTROLLER_H
