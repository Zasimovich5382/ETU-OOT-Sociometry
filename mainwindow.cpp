#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    loginForm = new LoginForm();
    loginForm->show();
    ui->setupUi(this);
    ui->updateParticipantsBtn->setHidden(true);
    ui->writeConclusionBtn->setHidden(true);
    participantsForm = new Participants();
    conclusionForm = new ConclusionForm();
    graphWidget = new GraphWidget(this);
    ui->horizontalLayout->addWidget(graphWidget);
    graph = new ERContainer<std::string>();

    connect(loginForm, SIGNAL(on_setRole(ROLE)), this, SLOT(on_setRole(ROLE)));

    connect(conclusionForm, &ConclusionForm::conclusionText, [=](const QString &text) {
        this->conclusion = text; }) ;

    connect(participantsForm, &Participants::updateGraph, [=]() {
        graphWidget->showGraph(graph); }) ;
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
        ui->showResearchResultBtn->setHidden(true);
    }
    else{
        ui->updateParticipantsBtn->setHidden(true);
        ui->writeConclusionBtn->setHidden(true);
        ui->showResearchResultBtn->setHidden(false);
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
    QString filename = QFileDialog::getOpenFileName(nullptr, "Load graph from json", "", "Json (*.json)");
    qDebug() << filename;
    if (filename.isEmpty()) return;
    loadFromJson(filename);
    graphWidget->showGraph(graph);
}

void MainWindow::on_saveCurrentStateBtn_clicked()
{
    QString filename = QFileDialog::getSaveFileName(nullptr, "Save graph to json", "", "Json (*.json)");
    if (filename.isEmpty()) return;
    saveToJson(filename);
}

void MainWindow::on_showResearchResultBtn_clicked()
{
    conclusionForm->loadTextInAdminMode(false);
    conclusionForm->setText(conclusion);
    conclusionForm->show();
}

void MainWindow::on_writeConclusionBtn_clicked()
{
    // open text window and show written by admin conclusion for this graph
    conclusionForm->loadTextInAdminMode(true);
    conclusionForm->setText(conclusion);
    conclusionForm->show();
}

void MainWindow::on_actionLog_out_triggered()
{
    this->close();
    graphWidget->clear();
    graph->clear();
    conclusion = "";
    loginForm->show();
    //connect(loginForm, SIGNAL(on_setRole(ROLE)), this, SLOT(on_setRole(ROLE)));
}

void MainWindow::saveToJson(const QString& filename)
{
    QFile file(filename);
    if(!file.open(QFile::WriteOnly)) return;
    QJsonObject graph_repr;
    QJsonArray entities_repr;
    QJsonArray relations_repr;
    for(auto& entity: *graph){
        QJsonObject entity_repr;
        //QVariant has constuctor that use const char*, which is given by data() method
        entity_repr.insert("id", QJsonValue::fromVariant(entity.getId()));
        entity_repr.insert("name", QJsonValue::fromVariant(entity.getName().data()));
        entity_repr.insert("age", QJsonValue::fromVariant(entity.getAge()));
        entity_repr.insert("gender", QJsonValue::fromVariant(entity.getGender()));
        entities_repr.push_back(entity_repr);
        for(auto& relation: entity.getRelations()){
            QJsonObject relation_repr;
            relation_repr.insert("from", QJsonValue::fromVariant(relation.getFirstEntity()->getName().data()));
            relation_repr.insert("to", QJsonValue::fromVariant(relation.getSecondEntity()->getName().data()));
            relation_repr.insert("type", QJsonValue::fromVariant(relation.getType()));
            relation_repr.insert("description", QJsonValue::fromVariant(relation.getDescription().data()));
            relations_repr.push_back(relation_repr);
        }
    }
    graph_repr.insert("conclusion", QJsonValue::fromVariant(conclusion));
    graph_repr.insert("entities", entities_repr);
    graph_repr.insert("relations", relations_repr);
    QJsonDocument document(graph_repr);
    file.write(document.toJson());
    file.close();
}

void MainWindow::loadFromJson(const QString& filename)
{
    graph->clear();
    //clear graphics widget

    QFile file(filename);
    if(!file.open(QFile::ReadOnly))
        throw FileNotOpenedException(filename);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    QJsonObject graph_repr = document.object();

    conclusion = graph_repr["conclusion"].toString();
    QJsonArray entities_repr = graph_repr["entities"].toArray();
    QJsonArray relations_repr = graph_repr["relations"].toArray();

    for(auto value: entities_repr){
        QJsonObject entity_repr = value.toObject();
        QString name = entity_repr["name"].toString();
        int age = entity_repr["age"].toInt();
        int gender = entity_repr["gender"].toInt();
        int id = entity_repr["id"].toInt();

        SocialEntity<std::string> entity(name.toStdString(), (Gender)gender);
        entity.setAge(age);
        entity.setId(id);
        if(!graph->addEntity(entity))
            throw WrongFileDataException(filename);

    }

    for(auto value: relations_repr){
        QJsonObject relation_repr = value.toObject();
        QString from = relation_repr["from"].toString();
        QString to = relation_repr["to"].toString();
        QString descr = relation_repr["description"].toString();
        int type = relation_repr["type"].toInt();

        if(!graph->addRelation(from.toStdString(), to.toStdString(), (Type)type))
            throw WrongFileDataException(filename);

        Relation<std::string>* r;
        SocialEntity<std::string>* e = graph->find(from.toStdString());
        if (e && (r = e->getRelationWith(to.toStdString()))) {
            r->setDescription(descr.toStdString());
        }
    }
    file.close();
}
