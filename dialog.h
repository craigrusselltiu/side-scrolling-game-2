#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QKeyEvent>
#include "config.h"
#include "player.h"
#include "worldmanager.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
Q_OBJECT

public:

    // Constructor + Destructor
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:

    // Process events
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *e);

private:

    // Members
    Ui::Dialog* ui;
    QTimer* timer;
    Config* config;
    Player* player;
    WorldManager* worldManager;

public slots:

    // Process next frame
    void nextFrame();

};

#endif // DIALOG_H
