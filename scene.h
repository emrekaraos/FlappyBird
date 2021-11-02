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

    void incrementScore();

    int getScore() const;
    void setScore(int newScore);

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
    void showGameOverGraphics();
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    int score;
    int bestScore;

    QGraphicsPixmapItem *gameOverPix;
    QGraphicsTextItem *scoreTextItem;

};

#endif // SCENE_H
