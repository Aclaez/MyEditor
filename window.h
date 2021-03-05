#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QIcon>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QComboBox>
#include <QGraphicsView>
#include <QSpinBox>
#include <QLabel>
#include <QColorDialog>
#include <QMenuBar>
#include <QList>
#include <QFileDialog>

#include "poligon.h"

class Window : public QWidget
{

    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

private slots:
    void figureClicked();
    void changeColor();
    void clearAll();
    void openFile();
    void saveFile();

private:



    Poligon *poligon;
    QGraphicsView *scene;
    QPushButton* squareButton;
    QPushButton* circleButton;
    QPushButton* penButton;
};

#endif // WINDOW_H
