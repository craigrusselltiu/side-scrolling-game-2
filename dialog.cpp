#include <QDir>
#include <QDebug>
#include "dialog.h"
#include "ui_dialog.h"
#include "define.h"

// Constructor
Dialog::Dialog(QWidget *parent): QDialog(parent), ui(new Ui::Dialog){

    // Setup window, FPS, path, RNG
    ui->setupUi(this);
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    this->setWindowState(Qt::WindowFullScreen);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(FRAME_TIME);
    std::srand(std::time(nullptr));

    // Read config file
    config = new Config("resources/config.json");
    if(!config->isValid()){
        qCritical() << config->getErrorMsg().c_str();
        QMetaObject::invokeMethod(this, "close", Qt::QueuedConnection);
    }

    // Init world manager and player
    else{
        player = new Player(config);
        worldManager = new WorldManager(config);
    }
}

// Destructor
Dialog::~Dialog(){
    delete ui;
    delete timer;
    if(config->isValid()){
        delete player;
        delete worldManager;
    }
    delete config;
}

// Frame update
void Dialog::nextFrame(){
    update();
}

void Dialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    worldManager->update(painter);
    player->render(painter);
    if(config->getStage() >= 2) worldManager->checkCollision(player);
}

// Respond to Key Press
void Dialog::keyPressEvent(QKeyEvent *e){
    // Quit
    if(e->key() == Qt::Key_Escape)
        this->reject();
    if(!(config->getTestMode())){
        // Pause
        if(e->key() == Qt::Key_Tab)
            if(!(worldManager->isOver())){
                worldManager->togglePause();
                player->togglePause();
            }
        // Jump
        if(e->key() == Qt::Key_Space)
            if(config->getStage() >= 2 && !(worldManager->isOver())) player->jump();
        // Restart
        if(e->key() == Qt::Key_R)
            if(worldManager->isOver()){
                delete player;
                delete worldManager;
                player = new Player(config);
                worldManager = new WorldManager(config);
            }
    }
}
