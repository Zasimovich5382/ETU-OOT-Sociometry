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
    scene = new QGraphicsScene(parent);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-300, -300, 600, 600);
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
    graphList.clear();
    if(nodes.size() > 0){
        foreach (QGraphicsItem *item, scene->items()) {
            delete item;
        }
    }
    nodes.clear();
}

void GraphWidget::showGraph(QList<std::pair<Vertex, QList<std::pair<int, int>>>> _graphList){
    scene->clear();
    scene->addItem(new Node(1, 0, this));
//    graphList.clear();
//    if(nodes.size() > 0){
//        foreach (QGraphicsItem *item, scene->items()) {
//            delete item;
//        }
//        nodes.clear();
//    }
//    graphList = _graphList;
//    int nodes_len = graphList.size();
//    int d = 150;
//    int angle = 0;
//    for(int i = 0; i < nodes_len; i++){
//        nodes.push_back(new Node(i+1, this));
//        scene->addItem(nodes[nodes.size() - 1]);
//        nodes[nodes.size() - 1]->setPos(graphList[i].first.x, graphList[i].first.y);
//        nodes[nodes.size()-1]->setGravity(false);
//    }
//    for(int i = 0; i < nodes_len; i++){
//        for(int j = 0; j < graphList[i].second.length(); j++){
//            if(graphList[i].second[0].first != -1)
//                scene->addItem(new Edge(nodes[graphList[i].first.id], nodes[graphList[i].second[j].first],
//                                        graphList[i].second[j].second, true));
//        }
//    }
}

void GraphWidget::refresh(){
    for(auto& el : nodes){
        el->setColor(Qt::lightGray);
    }
}

QList<std::pair<Vertex, QList<std::pair<int, int>>>> GraphWidget::getGraphList() const{
    return graphList;
}

std::vector<Node*> GraphWidget::getNodes() const{
    return nodes;
}


void GraphWidget::setEdge(int s, int t, QColor _color, int w){
//    QList<Edge*> edges;
//    foreach (QGraphicsItem *item, scene->items()) {
//        if (Edge *edge = qgraphicsitem_cast<Edge*>(item))
//            edges << edge;
//    }
//    for(auto& edge: edges){
//        if((edge->source->data-1 == s) && (edge->dest->data-1 == t)){
//            edge->color = _color;
//            edge->weight = w;
//            edge->update();
//            break;
//        }
//    }
}


void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
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
    scaleView(1 / qreal(1.2));
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
