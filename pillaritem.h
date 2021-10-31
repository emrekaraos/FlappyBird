#ifndef PILLARITEM_H
#define PILLARITEM_H

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>



class PillarItem :public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit PillarItem();
    ~PillarItem();

    qreal x() const;;
    void setX(qreal x);

signals:


public slots:

private:
    QGraphicsPixmapItem *topPillar;
    QGraphicsPixmapItem *bottomPillar;
    QPropertyAnimation *xAnimation;

    int yPos;

    qreal m_x;
};

#endif // PILLARITEM_H
