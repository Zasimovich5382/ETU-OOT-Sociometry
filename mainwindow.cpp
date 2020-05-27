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

    resize(1000, 640);
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
    QString filename = QFileDialog::getOpenFileName(nullptr, "Load graph from json", "", "Json (*.json)");
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
}

void MainWindow::saveToJson(const QString& filename)
{
    QFile file(filename);
    if(!file.open(QFile::WriteOnly)) return;
    QJsonObject graphRepr;
    QJsonArray entitiesRepr;
    QJsonArray relationsRepr;
    for(auto& entity: *graph){
        QJsonObject entityRepr;
        //QVariant has constuctor that use const char*, which is given by data() method
        entityRepr.insert("id", QJsonValue::fromVariant(entity.getId()));
        entityRepr.insert("name", QJsonValue::fromVariant(entity.getName().data()));
        entityRepr.insert("age", QJsonValue::fromVariant(entity.getAge()));
        entityRepr.insert("gender", QJsonValue::fromVariant(entity.getGender()));
        entitiesRepr.push_back(entityRepr);
        for(auto& relation: entity.getRelations()){
            QJsonObject relationRepr;
            relationRepr.insert("from", QJsonValue::fromVariant(relation.getFirstEntity()->getName().data()));
            relationRepr.insert("to", QJsonValue::fromVariant(relation.getSecondEntity()->getName().data()));
            relationRepr.insert("type", QJsonValue::fromVariant(relation.getType()));
            relationRepr.insert("description", QJsonValue::fromVariant(relation.getDescription().data()));
            relationsRepr.push_back(relationRepr);
        }
    }
    graphRepr.insert("conclusion", QJsonValue::fromVariant(conclusion));
    graphRepr.insert("entities", entitiesRepr);
    graphRepr.insert("relations", relationsRepr);
    QJsonDocument document(graphRepr);
    file.write(document.toJson());
    file.close();
}

void MainWindow::loadFromJson(const QString& filename)
{
    graph->clear();

    QFile file(filename);
    if(!file.open(QFile::ReadOnly))
        throw FileNotOpenedException(filename);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    QJsonObject graphRepr = document.object();

    conclusion = graphRepr["conclusion"].toString();
    QJsonArray entitiesRepr = graphRepr["entities"].toArray();
    QJsonArray relationsRepr = graphRepr["relations"].toArray();

    for(auto value: entitiesRepr){
        QJsonObject entityRepr = value.toObject();
        QString name = entityRepr["name"].toString();
        int age = entityRepr["age"].toInt();
        int gender = entityRepr["gender"].toInt();
        int id = entityRepr["id"].toInt();

        SocialEntity<std::string> entity(name.toStdString(), (Gender)gender);
        entity.setAge(age);
        entity.setId(id);
        if(!graph->addEntity(entity))
            throw WrongFileDataException(filename);

    }

    for(auto value: relationsRepr){
        QJsonObject relationRepr = value.toObject();
        QString from = relationRepr["from"].toString();
        QString to = relationRepr["to"].toString();
        QString descr = relationRepr["description"].toString();
        int type = relationRepr["type"].toInt();

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
