
#include "myglwidget.h"

#include <QOpenGLWidget>

#include <math.h>
#include <QPainter>

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

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void myGLWidget::paintGL()
{

    float fPitchScale = 0.3;
    int iCount = 0;
    int iNumSegments = 100;
    float x1,x2,y1,y2;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);










    glPushMatrix();

    glLoadIdentity();

    // roll
    glRotatef((float)zRot,0.0,0.0,1.0);


    glPushMatrix();

    // pitch
    glTranslatef(0.0,10.0*fPitchScale*(float)yRot/90.0,0.0);


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


    glEnable(GL_SCISSOR_TEST);

    int iWindowWidth = this->width();
    int iWindowHeight = this->height();

    int iClipX = iWindowWidth/2 - 0.3 * iWindowWidth;
    int iClipY = iWindowHeight/2 - 0.1 *  iWindowHeight;
    int iClipWidth = iWindowWidth * 0.6;
    int iClipHeight = iWindowHeight * 0.4;

    glScissor(iClipX, iClipY, iClipWidth,iClipHeight);

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

    glDisable(GL_SCISSOR_TEST);

    glPopMatrix();



    glColor3f(1.0,1.0,1.0);
    glLineWidth(2.0);

    // draw roll scale arc
    float fRadius = 0.8;
    float fStartAngle = 150.0 * DEG2RAD;
    float fEndAngle = 30.0 * DEG2RAD;

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
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.8, 0.0);
        glVertex3f(0.05, 0.85, 0.0);
        glVertex3f(-0.05,0.85,0.0);
    glEnd();


    glPopMatrix();

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
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.8, 0.0);
        glVertex3f(0.05, 0.75, 0.0);
        glVertex3f(-0.05,0.75,0.0);
    glEnd();


    glPushMatrix();
    glTranslatef(0.0,-0.8,0.0);

    glPushMatrix();
    // draw top marker
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(0.05, 0.55, 0.0);
        glVertex3f(-0.05,0.55,0.0);
    glEnd();
    glPopMatrix();

    // yaw
    glRotatef((float)xRot,0.0,0.0,1.0);

    // draw compass rose
    glColor3f(1.0,1.0,1.0);
    glLineWidth(1.0);
    glBegin(GL_LINES);

    // minor ticks
    for(iCount=0;iCount < 360;iCount = iCount + 5)
    {
        x1 = 0.5 * cos((float)iCount * DEG2RAD);
        y1 = 0.5 * sin((float)iCount * DEG2RAD);
        x2 = 0.475 * cos((float)iCount * DEG2RAD);
        y2 = 0.475 * sin((float)iCount * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);
    }

    // major ticks
    for(iCount=0;iCount < 360;iCount = iCount + 10)
    {
        x1 = 0.5 * cos((float)iCount * DEG2RAD);
        y1 = 0.5 * sin((float)iCount * DEG2RAD);
        x2 = 0.45 * cos((float)iCount * DEG2RAD);
        y2 = 0.45 * sin((float)iCount * DEG2RAD);
        glVertex3f(x1,y1,0.0);
        glVertex3f(x2,y2,0.0);
    }




    glEnd();


    glPopMatrix();

    glColor3f(1.0,1.0,1.0);
    renderText(0.5,0.8,0.0,"TEST TEST");

    renderText(0.0,0.0,0.0,"000");


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



void myGLWidget::renderText(double x, double y, double z, const QString &str)
{
    // map window coordinates to GL coordinates
    GLdouble textPosX = x * this->width()/2.0 + this->width()/2.0;
    GLdouble textPosY = (-y * this->height()/2.0 + this->height()/2.0);
    GLdouble textPosZ = z;

//    // Retrieve last OpenGL color to use as a font color
    GLdouble glColour[4];
    glGetDoublev(GL_CURRENT_COLOR, glColour);
    QColor fontColour = QColor(glColour[0]*255, glColour[1]*255, glColour[2]*255,glColour[3]*255);

    // Render text
    QPainter painter(this);
    painter.setPen(fontColour);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(textPosX, textPosY, str);
    painter.end();
}



