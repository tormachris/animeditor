#include "matrixview.h"

#include <QDebug>
#include <QKeyEvent>
#include <math.h>
#include "mainwindow.h"
#include "matrixscene.h"

MatrixView::MatrixView(QWidget *parent) :
    QGraphicsView (parent)
{
    setDragMode(ScrollHandDrag);
}

void MatrixView::zoomIn()
{
    scale(1.2, 1.2);
}

void MatrixView::zoomOut()
{
    scale(1/1.2, 1/1.2);
}

void MatrixView::toggleSpacing()
{
    auto matrixScene = static_cast<MatrixScene*>(scene());
    matrixScene->toggleSpacing();
}

void MatrixView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}


void MatrixView::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2.0, event->delta() / 240.0));
}

void MatrixView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    qDebug() << "Mouse factor: " << factor;
    if (factor < 0.17 || factor > 3.3)
        return;

    scale(scaleFactor, scaleFactor);
}
