#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1500,1000);
    this->setFixedSize(1500,1000);

    scene = new QGraphicsScene();

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(-250,-250,500,500);
    scene->addEllipse(-240, -240, 480, 480, QPen(Qt::black), QBrush(Qt::NoBrush));
    scene->addEllipse(-140, -140, 280, 280, QPen(Qt::black), QBrush(Qt::NoBrush));
    scene->addEllipse(-440, -440, 880, 880, QPen(Qt::black), QBrush(Qt::NoBrush));

    loginForm = new LoginForm();
    loginForm->show();

    ui->updateParticipantsBtn->setHidden(true);
    ui->writeConclusionBtn->setHidden(true);
    participantsForm = new Participants();

    connect(loginForm, SIGNAL(on_setRole(ROLE)), this, SLOT(on_setRole(ROLE)));

    graph = new ERContainer<std::string>();

    graph->addEntity("Lesha", MALE);
    graph->addEntity("Olya", FEMALE);
    graph->addEntity("Masha", FEMALE);
    graph->addRelation("Masha", "Olya", POSITIVE);
    graph->addRelation("Olya", "Masha", POSITIVE);
    graph->addRelation("Masha","Lesha" ,NEGATIVE);
}

MainWindow::~MainWindow()
{
    delete participantsForm;
    delete loginForm;
    delete ui;
}

void MainWindow::on_setRole(enum ROLE role)
{
    if (role == ADMIN){
        ui->updateParticipantsBtn->setHidden(false);
        ui->writeConclusionBtn->setHidden(false);
    }
    this->show();
}

void MainWindow::on_updateParticipantsBtn_clicked()
{
    participantsForm->show();
    participantsForm->setGraph(graph);
    participantsForm->initParticipantsList();
}

void MainWindow::on_loadPreviousStateBtn_clicked()
{
    // load the previous conteiner state and show it
}

void MainWindow::on_saveCurrentStateBtn_clicked()
{

}

void MainWindow::on_showResearchResultBtn_clicked()
{

//    for ( auto i = graph->begin(); i != graph->end(); ++i ){
//        for ( auto j = i; j != graph->end(); ++j )
//            if (i->getRating() < j->getRating()) {
//                std::cout<<i->getRating()<<j->getRating()<<std::endl;
//                std::iter_swap(i, j);

//            }
//    }


    // show the conclusion written by admin
    QList <DrawingEntity*> drawingList;
    auto iter = graph->begin();
    QPoint c = QPoint(0,0);



    while(iter!=graph->end())
    {

        SocialEntity<std::string> own_entity = *iter;
        DrawingEntity * own_drawing_entity = new DrawingEntity(&own_entity);

        own_drawing_entity->setCentre(c);
        scene->addItem(own_drawing_entity);
        own_drawing_entity->setPos(0,0);
        ++iter;
        c = c + QPoint(100,100);
        drawingList.push_back(own_drawing_entity);

    }


    iter = graph->begin();
    while(iter!=graph->end())
    {

        SocialEntity<std::string> own_entity = *iter;
        for(Relation<std::string> r : own_entity.getRelations()){
            int idFirst = r.getFirstEntity()->getID();
            int idSecond = r.getSecondEntity()->getID();

            std::cout<<idFirst<<idSecond<<std::endl;
            DrawingEntity* firstEntity;
            DrawingEntity* secondEntity;

            for(DrawingEntity* e : drawingList){
                if(idFirst == e->getID()){
                    firstEntity = e;
                } else if(idSecond == e->getID()){
                    secondEntity = e;
                }
            }

            DrawingRelation * own_drawing_relation = new DrawingRelation(r.getType(), firstEntity, secondEntity);
            scene->addItem(own_drawing_relation);
            own_drawing_relation->setPos(0,0);



        }

        ++iter;
    }






}

void MainWindow::on_writeConclusionBtn_clicked()
{
    // open text window and show written by admin conclusion for this graph
}
