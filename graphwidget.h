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
#include <cmath>
#include <queue>
#include <fstream>
#include <sstream>

typedef std::map<char,std::map<char, int>> Graph;

struct Compare{
    bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2){
        return p1.second < p2.second;
    }
};

struct Vertex{
    int id;
    int x;
    int y;
};

class Node;
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    ~GraphWidget();

    void showGraph(QList<std::pair<Vertex, QList<std::pair<int, int>>>> graphList);

    void itemMoved();

    QList<std::pair<Vertex, QList<std::pair<int, int>>>> getGraphList() const;

    std::vector<Node*> getNodes() const;

    void refresh();

    void setEdge(int s, int t, QColor _color, int w);

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

    void scaleView(qreal scaleFactor);

private:
    int timerId;
    QGraphicsScene *scene;
    std::vector<Node*> nodes;
    QList<std::pair<Vertex, QList<std::pair<int, int>>>> graphList;
};
#endif // GRAPHWIDGET_H
