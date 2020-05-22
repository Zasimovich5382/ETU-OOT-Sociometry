#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QEventLoop>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <vector>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QGraphicsEllipseItem>
#include <QtMath>
#include <algorithm>

#include "ercontainer.h"

class Node;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    ~GraphWidget();

    void showGraph(ERContainer<std::string>* graph);

    void itemMoved();
    void clear();

    std::vector<Node*> getNodes() const;

public slots:
    //void shuffle();
    void zoomIn();
    void zoomOut();
    void changeGravity();
protected:
    void delay(int msec=1000);
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void scaleView(qreal scaleFactor);

private:
    int timerId;
    QGraphicsScene *scene;
    std::vector<Node*> nodes;
    QMap<int, Node*> id_map;
};
#endif // GRAPHWIDGET_H
