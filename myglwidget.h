#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QObject>
#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class myGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    myGLWidget(QWidget *parent = 0);
    virtual ~myGLWidget();


signals:
    // signaling rotation from mouse movement
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);


public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:

    int xRot, yRot, zRot;
    void renderText(double x, double y, double z, const QString &str);

};




#endif // MYGLWIDGET_H
