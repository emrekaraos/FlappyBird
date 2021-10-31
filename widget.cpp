#include "widget.h"
#include "./ui_widget.h"
#include <QGraphicsPixmapItem>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new Scene(this);
    scene->setSceneRect(-250,-300,500,600);

    QGraphicsPixmapItem * pixItem = new QGraphicsPixmapItem(QPixmap(":/sky.png"));

    scene->addItem(pixItem);

    ui->graphicsView->setScene(scene);
}

Widget::~Widget()
{
    delete ui;
}

