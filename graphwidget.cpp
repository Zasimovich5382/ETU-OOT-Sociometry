#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

#include <QKeyEvent>
#include <QDebug>
#include <QThread>


GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-500, -500, 1000, 1000);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(1.2), qreal(1.2));
    setMinimumSize(400, 400);
}

GraphWidget::~GraphWidget(){
    scene->clear();
    if(nodes.size() > 0){
        foreach (QGraphicsItem *item, scene->items()) {
            delete item;
        }
    }
    nodes.clear();
}

void GraphWidget::showGraph(ERContainer<std::string>* graph){
    scene->clear();
    id_map.clear();

    if(nodes.size() > 0){
        foreach (QGraphicsItem *item, scene->items()) {
            delete item;
        }
        nodes.clear();
    }
    int nodes_len = graph->size();
    int radius = 150;
    int angle = 0;

    float angle_step = (2*M_PI)/nodes_len;
    for(auto& e : *graph){
        nodes.push_back(new Node(e.getId(), e.getGender(), this));
        scene->addItem(nodes[nodes.size() - 1]);

        id_map.insert(e.getId(), nodes[nodes.size() - 1]);

        nodes[nodes.size()-1]->setPos(radius*cosf(angle), radius*sinf(angle));
        nodes[nodes.size()-1]->setGravity(false);

        angle += angle_step;
    }

    for(auto& e : *graph){
        for(auto& r: e.getRelations()){
            int first_id = r.getFirstEntity()->getId();
            int second_id = r.getSecondEntity()->getId();
            scene->addItem(new Edge(id_map[first_id], id_map[second_id], r.getType()));
        }
    }
}

std::vector<Node*> GraphWidget::getNodes() const{
    return nodes;
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::clear()
{
    scene->clear();
    id_map.clear();

    if(nodes.size() > 0){
        foreach (QGraphicsItem *item, scene->items()) {
            delete item;
        }
        nodes.clear();
    }
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Plus:
            zoomIn();
            break;
        case Qt::Key_Minus:
            zoomOut();
            break;
        case Qt::Key_Space:
            break;
        default:
            QGraphicsView::keyPressEvent(event);
            break;
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void GraphWidget::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    this->centerOn(0, 0);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2f));
}

void GraphWidget::changeGravity(){
    for(auto& node : nodes){
        node->setGravity(node->forces ? false : true);
    }
}

void GraphWidget::delay(int msec)
{
    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(msec);
    loop.exec();
}
