#include "birditem.h"
#include <QTimer>

BirdItem::BirdItem(QPixmap pixmap) :
    wingPosition(WingPosition::Up),
    wingDirection(0)
{
    setPixmap(pixmap);

    QTimer *birdWingsTimer = new QTimer(this);
    connect(birdWingsTimer, &QTimer::timeout, [=](){
            updatePixmap();
            });

    birdWingsTimer->start(80);


    groundPosition = scenePos().y() + 290;

    yAnimation = new QPropertyAnimation(this, "y", this);
    yAnimation->setStartValue(scenePos().y());

    yAnimation->setEndValue(groundPosition);
    yAnimation->setEasingCurve(QEasingCurve::InQuad);
    yAnimation->setDuration(1000);

   // yAnimation->start();


    rotationAnimation = new QPropertyAnimation(this, "rotation", this);
    //rotateTo(90, 1200, QEasingCurve::InQuad);

}

void BirdItem::updatePixmap()
{
    if(wingPosition == WingPosition::Middle){
        if(wingDirection){
            //UP
            setPixmap(QPixmap(":/bird_blue_up.png"));
            wingPosition = WingPosition::Up;
            wingDirection = 0;
        }else{
            //DOWN
            setPixmap(QPixmap(":/bird_blue_down.png"));
            wingPosition = WingPosition::Down;
            wingDirection = 1;
        }

    }   else{
        setPixmap(QPixmap(":/bird_blue_middle.png"));
        wingPosition = WingPosition::Middle;
    }
}

qreal BirdItem::rotation() const
{
    return m_rotation;
}

void BirdItem::setRotation(qreal rotation)
{
    m_rotation = rotation;


    QPointF c = boundingRect().center();
    QTransform t;
    t.translate(c.x(), c.y());
    t.rotate(rotation);
    t.translate(-c.x(), -c.y());
    setTransform(t);
}

qreal BirdItem::y() const
{
    return m_y;
}

void BirdItem::setY(qreal y)
{
    moveBy(0, y-m_y);
    m_y = y;
}

void BirdItem::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);

    rotationAnimation->start();
}

void BirdItem::shootUp()
{
    yAnimation->stop();
    rotationAnimation->stop();

    qreal curPosy = y();
    yAnimation->setStartValue(curPosy);
    yAnimation->setEndValue(curPosy - scene()->sceneRect().height()/8);
    yAnimation->setEasingCurve(QEasingCurve::OutQuad);

    connect(yAnimation, &QPropertyAnimation::finished, [=](){
            fallToGroundIfNecessary();
            });

    yAnimation->start();

    rotateTo(-20, 200, QEasingCurve::OutCubic);

}

void BirdItem::fallToGroundIfNecessary()
{
    if(y() < groundPosition){
        rotationAnimation->stop();
        //yAnimation->stop();

        yAnimation->setStartValue(y());
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setEndValue(groundPosition);
        yAnimation->setDuration(1200);
        yAnimation->start();

        rotateTo(90, 1100, QEasingCurve::InCubic);
    }
}

void BirdItem::startFlying()
{
    yAnimation->start();
    rotateTo(90, 1200, QEasingCurve::InQuad);
}

void BirdItem::freezeInPlace()
{
    yAnimation->stop();
    rotationAnimation->stop();
}
