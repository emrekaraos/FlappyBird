#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include "pillaritem.h"
#include <QTimer>
#include "birditem.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);

    void addBird();

    void startGame();

    bool getGameOn() const;
    void setGameOn(bool newGameOn);

signals:



private:
    void cleanPillars();
    void setUpPillerTimer();

    void freezeBirdAndPillarsInPlace();
    QTimer *pillarTimer;

    BirdItem *bird;

    bool gameOn;

    // QGraphicsScene interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SCENE_H
