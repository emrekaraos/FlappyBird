#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    gameOn(false)
{
    setUpPillerTimer();

}

void Scene::addBird()
{
    bird = new BirdItem(QPixmap(":/bird_blue_up.png"));
    addItem(bird);
}

void Scene::startGame()
{
    bird->startFlying();
    if(!pillarTimer->isActive()){
        setGameOn(true);
        pillarTimer->start(1000);
    }
}

void Scene::setUpPillerTimer()
{
    pillarTimer = new QTimer(this);
    connect(pillarTimer, &QTimer::timeout, [=](){

        PillarItem *pillarItem = new PillarItem();

        connect(pillarItem, &PillarItem::collideFail, [=](){
            pillarTimer->stop();
            freezeBirdAndPillarsInPlace();
            setGameOn(false);
        });

        addItem(pillarItem);

    });

    //pillarTimer->start(1000);
}

void Scene::freezeBirdAndPillarsInPlace()
{
    bird->freezeInPlace();

    QList<QGraphicsItem *> sceneItems = items();
    foreach(QGraphicsItem * item, sceneItems){
        PillarItem * pillar = dynamic_cast<PillarItem *>(item);
        if(pillar){
            pillar->freezeInPlace();
        }
    }

}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Scene::cleanPillars()
{


}


void Scene::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        if(gameOn)
            bird->shootUp();
    }
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(gameOn)
            bird->shootUp();
    }
    QGraphicsScene::mousePressEvent(event);
}
