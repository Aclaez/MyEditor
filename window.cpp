#include "window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    setLayout(mainLayout);
    setWindowTitle(tr("Graphic Editor"));
    setFixedSize(1300, 700);

    QIcon winIcon(":ico/editor_ico.ico");
    setWindowIcon(winIcon);

    squareButton = new QPushButton(tr("Square"));
    circleButton = new QPushButton(tr("Circle"));
    penButton = new QPushButton(tr("Pen"));
    penButton->setEnabled(false);
    QPushButton* clearButton = new QPushButton(tr("Clear all"));
    QPushButton* changeColorButton = new QPushButton(tr("Change color"));
    QPushButton* openImageButton = new QPushButton(tr("Open"));
    QPushButton* saveImageButton = new QPushButton(tr("Save"));
    QPushButton* closeButton = new QPushButton(tr("Exit"));
    QPushButton* newFileButton = new QPushButton(tr("New"));

    QLabel *labelBPattern = new QLabel(tr("Brush pattern:"));
    QLabel *labelFile = new QLabel(tr("File:"));
    QLabel *labelForm = new QLabel(tr("Form:"));

    QComboBox *patterns = new QComboBox();
    patterns->addItem(tr("SolidPattern"));
    patterns->addItem(tr("Dense1Pattern"));
    patterns->addItem(tr("Dense2Pattern"));
    patterns->addItem(tr("Dense3Pattern"));
    patterns->addItem(tr("Dense4Pattern"));
    patterns->addItem(tr("Dense5Pattern"));
    patterns->addItem(tr("Dense6Pattern"));
    patterns->addItem(tr("Dense7Pattern"));
    patterns->addItem(tr("NoBrush"));
    patterns->addItem(tr("HorPattern"));
    patterns->addItem(tr("VerPattern"));
    patterns->addItem(tr("CrossPattern"));
    patterns->addItem(tr("BDiagPattern"));
    patterns->addItem(tr("FDiagPattern"));
    patterns->addItem(tr("DiagCrossPattern"));

    QLabel *labelWeight = new QLabel(tr("Pen weight:"));

    QSpinBox *penWeight = new QSpinBox;
    penWeight->setMinimum(1);

    QHBoxLayout *layWeight = new QHBoxLayout;
    layWeight->addWidget(labelWeight);
    layWeight->addWidget(penWeight);

    QVBoxLayout *toolbar = new QVBoxLayout;
    toolbar->addWidget(labelFile);
    toolbar->addWidget(newFileButton);
    toolbar->addWidget(openImageButton);
    toolbar->addWidget(saveImageButton);
    toolbar->addWidget(labelForm);
    toolbar->addWidget(squareButton);
    toolbar->addWidget(circleButton);
    toolbar->addWidget(penButton);
    toolbar->addWidget(changeColorButton);
    toolbar->addWidget(labelBPattern);
    toolbar->addWidget(patterns);
    toolbar->addLayout(layWeight);
    toolbar->addWidget(clearButton);

    poligon = new Poligon();
    scene = new QGraphicsView;
    scene->setScene(poligon);

    mainLayout->addLayout(toolbar, 0, 0);
    mainLayout->addWidget(closeButton, 14, 0);
    mainLayout->addWidget(scene, 0, 1, 15, 15);

    poligon->setSceneRect(0,0, scene->width(), scene->height());
    scene->fitInView(poligon->sceneRect(), Qt::KeepAspectRatio);

    //poligon->setSceneRect(0,0, scene->width()+516, scene->height()+195);

    connect(openImageButton, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(saveImageButton, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(squareButton, SIGNAL(clicked()), this, SLOT(figureClicked()));
    connect(circleButton, SIGNAL(clicked()), this, SLOT(figureClicked()));
    connect(penButton, SIGNAL(clicked()), this, SLOT(figureClicked()));
    connect(changeColorButton, SIGNAL(clicked()), this, SLOT(changeColor()));
    connect(patterns, SIGNAL(currentIndexChanged(QString)), poligon, SLOT(setBrushPattern(QString)));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(penWeight, SIGNAL(textChanged(QString)), poligon, SLOT(setWeight(QString)));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(newFileButton, SIGNAL(clicked()), poligon, SLOT(setWhiteBackground()));
}

void Window::figureClicked()
{
    QPushButton *buttonClicked = qobject_cast<QPushButton *>(sender());
    QString buttonName = buttonClicked->text();
    if(buttonName == "Pen")
    {
        squareButton->setEnabled(true);
        circleButton->setEnabled(true);
        penButton->setEnabled(false);
    }
    else if(buttonName == "Circle")
    {
        squareButton->setEnabled(true);
        circleButton->setEnabled(false);
        penButton->setEnabled(true);
    }
    else
    {
        squareButton->setEnabled(false);
        circleButton->setEnabled(true);
        penButton->setEnabled(true);
    }
    poligon->setMode(buttonName);
}

void Window::changeColor()
{
    QColor newColor = QColorDialog::getColor(poligon->getPenColor());
    if (newColor.isValid())
        poligon->setPenColor(newColor);
}

void Window::clearAll()
{
    poligon->clear();
}
void Window::openFile()
{
    poligon->clear();
    poligon->setSceneRect(5, 10, scene->width() - 10, scene->height() - 20);
    scene->fitInView(poligon->sceneRect(), Qt::KeepAspectRatio);

    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), QDir::currentPath());
    poligon->openImage(fileName);
}

void Window::saveFile()
{
    QString initialPath = QDir::currentPath() + "/untitled.png";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath);

    QPixmap pixMap = scene->grab();
    pixMap.save(fileName);
}
