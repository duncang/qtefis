
#include "myglwidget.h"

#include <QOpenGLWidget>

#include <math.h>

#define PI 3.1415926
#define RAD2DEG (180.0 / PI)
#define DEG2RAD (PI / 180)


myGLWidget::myGLWidget(QWidget *parent) : QOpenGLWidget (parent)
{

    xRot = 0;
    yRot = 0;
    zRot = 0;
}

myGLWidget::~myGLWidget()
{


}

void myGLWidget::setXRotation(int angle)
{

    xRot = angle;
    emit xRotationChanged(angle);
    update();

}

void myGLWidget::setYRotation(int angle)
{

    yRot = angle;
    emit yRotationChanged(angle);
    update();

}
void myGLWidget::setZRotation(int angle)
{

    zRot = angle;
    emit zRotationChanged(angle);
    update();
}


void myGLWidget::initializeGL()
{
    initializeOpenGLFunctions();


    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_BLEND);
    //glBlendFunc( GL_SRC_ALPHA_SATURATE, GL_ONE ) ;

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void myGLWidget::paintGL()
{

    float fPitchScale = 0.3;
    int iCount = 0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // render ownship icon
    glColor3f(1.0,1.0,0.0);
    glLineWidth(1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.2, -0.1, 0.0);
        glVertex3f(0.0,-0.05,0.0);
        glVertex3f(-0.2, -0.1, 0.0);
    glEnd();

    glColor3f(1.0,1.0,0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex3f(-0.5,0.0,0.0);
        glVertex3f(-0.3,0.0,0.0);

        glVertex3f(0.5,0.0,0.0);
        glVertex3f(0.3,0.0,0.0);
    glEnd();


    // draw top marker
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.8, 0.0);
        glVertex3f(0.05, 0.75, 0.0);
        glVertex3f(-0.05,0.75,0.0);
    glEnd();


    glPushMatrix();

    glLoadIdentity();

    // roll
    glRotatef((float)zRot,0.0,0.0,1.0);

    glColor3f(1.0,1.0,1.0);
    glLineWidth(2.0);

    // draw roll scale arc
    float fRadius = 0.8;
    float fStartAngle = 150.0 * DEG2RAD;
    float fEndAngle = 30.0 * DEG2RAD;
    int iNumSegments = 100;
    float x1,x2,y1,y2;
    glBegin(GL_LINES);
        for(iCount=0;iCount<iNumSegments;iCount++)
        {
            float fResolution = (fEndAngle - fStartAngle) / (float)iNumSegments;

            x1 = fRadius * cos(fStartAngle + fResolution*iCount);
            y1 = fRadius * sin(fStartAngle + fResolution*iCount);

            x2 = fRadius * cos(fStartAngle + fResolution*(iCount+1));
            y2 = fRadius * sin(fStartAngle + fResolution*(iCount+1));


            glVertex3f(x1,y1,0.0);
            glVertex3f(x2,y2,0.0);
        }
    glEnd();

    // draw roll scale tick marks
    glBegin(GL_LINES);
        // -60
        x1 = fRadius * cos(150. * DEG2RAD);
        y1 = fRadius * sin(150. * DEG2RAD);
        x2 = (fRadius+0.1) * cos(150. * DEG2RAD);
        y2 = (fRadius+0.1) * sin(150. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);

        // -45
        x1 = fRadius * cos(135. * DEG2RAD);
        y1 = fRadius * sin(135. * DEG2RAD);
        x2 = (fRadius+0.05) * cos(135. * DEG2RAD);
        y2 = (fRadius+0.05) * sin(135. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);


        // -30
        x1 = fRadius * cos(120. * DEG2RAD);
        y1 = fRadius * sin(120. * DEG2RAD);
        x2 = (fRadius+0.1) * cos(120. * DEG2RAD);
        y2 = (fRadius+0.1) * sin(120. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);

        // -20
        x1 = fRadius * cos(110. * DEG2RAD);
        y1 = fRadius * sin(110. * DEG2RAD);
        x2 = (fRadius+0.05) * cos(110. * DEG2RAD);
        y2 = (fRadius+0.05) * sin(110. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);

        // -10
        x1 = fRadius * cos(100. * DEG2RAD);
        y1 = fRadius * sin(100. * DEG2RAD);
        x2 = (fRadius+0.05) * cos(100. * DEG2RAD);
        y2 = (fRadius+0.05) * sin(100. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);

        // 60
        x1 = fRadius * cos(30. * DEG2RAD);
        y1 = fRadius * sin(30. * DEG2RAD);
        x2 = (fRadius+0.1) * cos(30. * DEG2RAD);
        y2 = (fRadius+0.1) * sin(30. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);

        // 45
        x1 = fRadius * cos(45. * DEG2RAD);
        y1 = fRadius * sin(45. * DEG2RAD);
        x2 = (fRadius+0.05) * cos(45. * DEG2RAD);
        y2 = (fRadius+0.05) * sin(45. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);

        // 30
        x1 = fRadius * cos(60. * DEG2RAD);
        y1 = fRadius * sin(60. * DEG2RAD);
        x2 = (fRadius+0.1) * cos(60. * DEG2RAD);
        y2 = (fRadius+0.1) * sin(60. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);

        // 20
        x1 = fRadius * cos(70. * DEG2RAD);
        y1 = fRadius * sin(70. * DEG2RAD);
        x2 = (fRadius+0.05) * cos(70. * DEG2RAD);
        y2 = (fRadius+0.05) * sin(70. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);

        // 10
        x1 = fRadius * cos(80. * DEG2RAD);
        y1 = fRadius * sin(80. * DEG2RAD);
        x2 = (fRadius+0.05) * cos(80. * DEG2RAD);
        y2 = (fRadius+0.05) * sin(80. * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);

    glEnd();

    // draw top marker
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.8, 0.0);
        glVertex3f(0.05, 0.85, 0.0);
        glVertex3f(-0.05,0.85,0.0);
    glEnd();




    glPushMatrix();

    // pitch
    glTranslatef(0.0,10.0*fPitchScale*(float)yRot/90.0,0.0);


    // pitch marks
    glColor3f(1.0,1.0,1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);

    for (iCount = 0;iCount<10;iCount++)
    {
        float fPitchLineOffset = iCount*1.0*fPitchScale;

        // major line
        glVertex3f(-0.3,fPitchLineOffset,0.0);
        glVertex3f(0.3,fPitchLineOffset,0.0);

        // major line
        glVertex3f(-0.3,-fPitchLineOffset,0.0);
        glVertex3f(0.3,-fPitchLineOffset,0.0);


        // minor line
        glVertex3f(-0.15,fPitchLineOffset + 0.5 * fPitchScale,0.0);
        glVertex3f(0.15,fPitchLineOffset + 0.5 * fPitchScale,0.0);

        glVertex3f(-0.15,-fPitchLineOffset - 0.5 * fPitchScale,0.0);
        glVertex3f(0.15,-fPitchLineOffset - 0.5 * fPitchScale,0.0);

    }
    glEnd();

    // sky
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
     glVertex3f(-10.0, 0.0, 0.0);
     glVertex3f(10.0, 0.0, 0.0);
     glVertex3f(10.0, 10.0, 0.0);
     glVertex3f(-10.0, 10.0, 0.0);
    glEnd();

    // ground
    glColor3f(0.5,0.3,0.3);
    glBegin(GL_POLYGON);
     glVertex3f(-10.0, 0.0, 0.0);
     glVertex3f(10.0, 0.0, 0.0);
     glVertex3f(10.0, -10.0, 0.0);
     glVertex3f(-10.0, -10.0, 0.0);
    glEnd();

    glPopMatrix();
    glPopMatrix();


}

void myGLWidget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45, (float)width/height, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0,0,5,0,0,0,0,1,0);

}




