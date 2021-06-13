#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <gl/glaux.h>
#include <bits/stdc++.h>
#include "BmpLoader.h"
#include "hat.cpp"
using namespace std;
extern unsigned int textures[7];
extern bool head_tex;
inline float mov=-7.5f;
inline bool mov_pos_flag=true;
extern const double PI;
extern float dimMat[];
void drawSphere(double r, int lats, int longs);
//inline float robotmat[]={1.0f,1.0f,1.0f,1.0f};
inline float robotmat[]={0.824f,0.706f,0.549f,1.0f};
inline float blackMat[]={0.0f,0.0f,0.0f,1.0f};
inline float whiteMat[]={1.0f,1.0f,1.0f,1.0f};
inline void DrawheadCube(float xPos, float yPos, float zPos)
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,robotmat);
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D,textures[0]);
    glTranslatef(xPos, yPos, zPos);
    //glClear(GL_COLOR_BUFFER_BIT);

    //glBegin(GL_POLYGON);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(0.0f, 0.0f, 0.0f); // top face
    glVertex3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glTexCoord2f(0.0,1.0);glVertex3f(0.0f, 0.0f, 0.0f); // front face
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0,0.0);glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0,0.0);glVertex3f(0.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); // right face
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0f,0.0f,0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f); // left face
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0f,-1.0f,0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f); // bottom face
    glVertex3f(0.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(0.0f, 0.0f, -1.0f); // back face
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    glEnd();
    glPopMatrix();
}

inline void DrawCube(float xPos, float yPos, float zPos)
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,robotmat);
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D,textures[0]);
    glTranslatef(xPos, yPos, zPos);
    //glClear(GL_COLOR_BUFFER_BIT);

    //glBegin(GL_POLYGON);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glTexCoord2f(0.0,0.0);glVertex3f(0.0f, 0.0f, 0.0f); // top face
    glTexCoord2f(1.0,0.0);glVertex3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0,1.0);glVertex3f(-1.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glTexCoord2f(0.0,0.0);glVertex3f(0.0f, 0.0f, 0.0f); // front face
    glTexCoord2f(1.0,0.0);glVertex3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0,1.0);glVertex3f(0.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0f,0.0f,0.0f);
    glTexCoord2f(0.0,0.0);glVertex3f(0.0f, 0.0f, 0.0f); // right face
    glTexCoord2f(1.0,0.0);glVertex3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(1.0,1.0);glVertex3f(0.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0,1.0);glVertex3f(0.0f, 0.0f, -1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0f,0.0f,0.0f);
    glTexCoord2f(0.0,0.0);glVertex3f(-1.0f, 0.0f, 0.0f); // left face
    glTexCoord2f(1.0,0.0);glVertex3f(-1.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0,1.0);glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0f,-1.0f,0.0f);
    glTexCoord2f(0.0,0.0);glVertex3f(0.0f, -1.0f, 0.0f); // bottom face
    glTexCoord2f(1.0,0.0);glVertex3f(0.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0,1.0);glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glTexCoord2f(0.0,0.0);glVertex3f(0.0f, 0.0f, -1.0f); // back face
    glTexCoord2f(1.0,0.0);glVertex3f(-1.0f, 0.0f, -1.0f);
    glTexCoord2f(1.0,1.0);glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0,1.0);glVertex3f(0.0f, -1.0f, -1.0f);
    glEnd();
    glPopMatrix();
}
inline float robotHair[]={0.0f,0.0f,0.0f,1.0f};
inline void DrawHair(float xPos, float yPos, float zPos)
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,robotHair);
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D,textures[0]);
    glTranslatef(xPos, yPos, zPos);
    //glClear(GL_COLOR_BUFFER_BIT);

    //glBegin(GL_POLYGON);
    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(0.0f, 0.0f, 0.0f); // top face
    glVertex3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(0.0f, 0.0f, 0.0f); // front face
    glVertex3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(-1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f); // right face
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, -1.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(1.0f,0.0f,0.0f);
    glVertex3f(-1.0f, 0.0f, 0.0f); // left face
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0f,-1.0f,0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f); // bottom face
    glVertex3f(0.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(0.0f, 0.0f, -1.0f); // back face
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    glEnd();
    glPopMatrix();
}

inline float robotHelmet[]={0.184, 0.310, 0.310,1.0f};
class robot{
public:

hat h;
float point1_x=0;
float point1_y=0;
float point1_z=0;

bool alive=true;

float angle1 = 0.0f; // current angle of the camera
bool leg1 = true; // robot’s leg states
bool leg2 = false; // true = forward, false = back
bool arm1 = true;
bool arm2 = false;

float legAngle[2] = { 0.0f, 0.0f }; // each leg’s current angle
float armAngle[2] = { 0.0f, 0.0f }; // each arm’s current angle


void circle(float radius){
    double x=0.0f;
    double y=0.0f;
    double height=0.0f;
    int ntheta = 20;
    //double angle_stepsize=0.0f;
    const float dtheta = 2*PI / ntheta;
    glBegin(GL_POLYGON);

    //glColor3f(0.0f,1.0f,0.0f);
    glNormal3f(0.0f,0.0f,1.0f);
    float angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            //angle = angle + angle_stepsize;
            angle = angle + dtheta;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}

void half_circle(float radius){
    double x=0.0f;
    double y=0.0f;
    double height=0.0f;
    int ntheta = 20;
    //double angle_stepsize=0.0f;
    const float dtheta = 2*PI / ntheta;
    glBegin(GL_POLYGON);
    //glColor3f(0.0f,1.0f,0.0f);
    glNormal3f(0.0f,0.0f,1.0f);
    float angle = 0.0;
        while( angle < PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            //angle = angle + angle_stepsize;
            angle = angle + dtheta;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}



void DrawArm(float xPos, float yPos, float zPos)
{
    glPushMatrix();
    //glColor3f(1.0f, 0.0f, 0.0f); // red
    glTranslatef(xPos, yPos, zPos);
    glScalef(1.0f, 4.0f, 1.0f); // arm is a 1x4x1 cube
    DrawCube(0.0f, 0.0f, 0.0f);
    glPopMatrix();
}
void helmetMat(){
    glMaterialfv(GL_FRONT,GL_AMBIENT,robotHelmet);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,robotHelmet);
}
void blackProperty(){
    glMaterialfv(GL_FRONT,GL_AMBIENT,blackMat);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,dimMat);
}
void whiteProperty(){
    glMaterialfv(GL_FRONT,GL_AMBIENT,whiteMat);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,dimMat);
}
void DrawHead(float xPos, float yPos, float zPos)
{


    glPushMatrix();
    point1_x=point1_x+xPos;
    point1_y=point1_y+yPos;
    point1_z=point1_z+zPos;

    glTranslatef(xPos, yPos, zPos);
    glScalef(2.0f, 2.0f, 2.0f); // head is a 2x2x2 cube

    DrawheadCube(0.0f, 0.0f, 0.0f);
    helmetMat();
    h.draw();

    ///eye
    /*glPushMatrix();
    glTranslatef(-0.25,-0.25,0.05);
    //glRotatef(180,1,0,0);
    blackProperty();
    circle(0.1);
    glTranslatef(0.0,0.0,0.01);
    whiteProperty();
    circle(0.03);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.75,-0.25,0.05);
    //glRotatef(180,1,0,0);
    blackProperty();
    circle(0.1);
    glTranslatef(0.0,0.0,0.01);
    whiteProperty();
    circle(0.03);
    glPopMatrix();*/
    ///eye with solid sphere
    /*glTranslatef(-0.25,-0.25,0.0);
    drawSphere(0.05,20,20);
    glTranslatef(-0.5,0.0,0.0);
    drawSphere(0.05,20,20);*/
    ///mouth
    //glPushMatrix();
    //glTranslatef(-0.25,-0.25,0.1);
    //glRotatef(180,1,0,0);
    //blackProperty();
    //half_circle(2.0);

    //glPopMatrix();

    //strips
    helmetMat();
    glTranslatef(-0.25,-0.25,0.0);
    glTranslatef(-0.5,0.0,0.0);
    glRotatef(5,0,0,1);
    glTranslatef(-0.35f,0.15f,-0.2f);

    glBegin(GL_QUADS);
    glVertex3f(0.0f,0.1f,0.0f);
    glVertex3f(0.0f,-0.9f,0.0f);
    glVertex3f(0.0f,-0.9f,0.1f);
    glVertex3f(0.0f,0.1f,0.1f);
    glEnd();

    //
    glRotatef(10,0,0,-1);
    glTranslatef(1.2f,0.15f,0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0.0f,0.1f,0.0f);
    glVertex3f(0.0f,-0.9f,0.0f);
    glVertex3f(0.0f,-0.9f,0.1f);
    glVertex3f(0.0f,0.1f,0.1f);
    glEnd();

    glPopMatrix();

    //hair
    glPushMatrix();
    //glColor3f(1.0f,0.0f,0.0f);
    //glColor3f(0.0f,0.0f,0.0f);
    glScalef(2.0f,0.1f,2.0f);
    //glTranslatef(xPos, yPos, zPos);
    glTranslatef(0.5f, 21.1f, 0.0f);
    DrawHair(0.0f,0.0f,0.0f);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0f,0.0f,0.0f);
    //glColor3f(0.0f,0.0f,0.0f);
    //glTranslatef(15.0f, 24.1f, 0.0f);
    glTranslatef(-1.1f, 2.2f, 0.1f);
    glRotatef(90,0,0,1);
    glScalef(1.0f,0.1f,2.2f);
    //glTranslatef(xPos, yPos, zPos);

    DrawHair(0.0f,0.0f,0.0f);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0f,0.0f,0.0f);
    //glColor3f(0.0f,0.0f,0.0f);
    //glTranslatef(15.0f, 24.1f, 0.0f);
    glTranslatef(1.0f, 2.2f, 0.1f);
    glRotatef(90,0,0,1);
    glScalef(1.0f,0.1f,2.2f);
    //glTranslatef(xPos, yPos, zPos);

    DrawHair(0.0f,0.0f,0.0f);
    glPopMatrix();

    glPushMatrix();
    //glColor3f(1.0f,0.0f,0.0f);
    //glColor3f(0.0f,0.0f,0.0f);
    //glTranslatef(15.0f, 24.1f, 0.0f);
    glTranslatef(1.0f, 0.1f, -2.0f);
    glRotatef(90,1,0,0);
    glScalef(2.0f,0.2f,1.9f);
    //glTranslatef(xPos, yPos, zPos);

    DrawHair(0.0f,0.0f,0.0f);
    glPopMatrix();

    //eye

    //mouth
}

void DrawTorso(float xPos, float yPos, float zPos)
{
    glPushMatrix();
    //glBindTexture(GL_TEXTURE_2D,textures[0]);
    //glColor3f(0.0f, 0.0f, 1.0f); // blue
    glTranslatef(xPos, yPos, zPos);
    glScalef(3.0f, 5.0f, 2.0f); // torso is a 3x5x2 cube
    DrawCube(0.0f, 0.0f, 0.0f);
    glPopMatrix();
}

void DrawLeg(float xPos, float yPos, float zPos)
{
    glPushMatrix();
    //glColor3f(1.0f, 1.0f, 0.0f); // yellow
    glTranslatef(xPos, yPos, zPos);
    glScalef(1.0f, 6.0f, 1.0f); // leg is a 1x5x1 cube
    DrawCube(0.0f, 0.0f, 0.0f);
    glPopMatrix();
}

void DrawRobot(float xPos, float yPos, float zPos)
{
    glPushMatrix();
    //glRotatef(180,0,1,0);
    glTranslatef(0,0,mov);
    glTranslatef(xPos, yPos, zPos); // draw robot at desired coordinates
    point1_x=xPos;
    point1_y=yPos;
    point1_z=zPos+mov;
// draw components
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[6]);
    head_tex=true;
    //glDisable(GL_TEXTURE_2D);
    DrawHead(1.0f, 2.0f, 0.0f);
    //head_tex=false;
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[0]);

                                              //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //glDisable(GL_TEXTURE_2D);
    blackProperty();
    DrawTorso(1.5f, 0.0f, 0.0f);

    //arm0
    glPushMatrix();


    glTranslatef(0.0f, -0.5f, 0.0f);
    //glPushMatrix();
    glRotatef(armAngle[0], 1.0f, 0.0f, 0.0f);
    //glPushMatrix();
    DrawArm(2.5f, 0.0f, -0.5f);
    glPopMatrix();

    //arm1
    glPushMatrix();

    glTranslatef(0.0f, -0.5f, 0.0f);
    glRotatef(armAngle[1], 1.0f, 0.0f, 0.0f);
    DrawArm(-1.5f, 0.0f, -0.5f);
    glPopMatrix();

    //leg0
    glPushMatrix();

    glTranslatef(0.0f, -0.5f, 0.0f);
    glRotatef(legAngle[0], 1.0f, 0.0f, 0.0f);
    //(-0.5f, -5.0f, -0.5f)
    DrawLeg(-0.5f, -4.5f, -0.5f);
    glPopMatrix();

    //leg1
    glPushMatrix();

    glTranslatef(0.0f, -0.5f, 0.0f);
    glRotatef(legAngle[1], 1.0f, 0.0f, 0.0f);
    //(1.5,-0.5,0.5) chilo
    DrawLeg(1.5f, -4.5f, -0.5f);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void animateRobot(){
    if(alive==true){
        if (arm1)
        armAngle[0] = armAngle[0] + 1.0f;
    else
        armAngle[0] = armAngle[0] - 1.0f;

    if (armAngle[0] >= 15.0f)
        arm1 = false;
    if (armAngle[0] <= -15.0f)
        arm1 = true;

    //walking effect
    if (arm2)
        armAngle[1] = armAngle[1] + 1.0f;
    else
        armAngle[1] = armAngle[1] - 1.0f;

    //arm2<15 then it will rotate forward
    if (armAngle[1] >= 15.0f)
        arm2 = false;
    if (armAngle[1] <= -15.0f)
        arm2 = true;


    if (leg1)
        legAngle[0] = legAngle[0] + 1.0f;
    else
        legAngle[0] = legAngle[0] - 1.0f;

    if (legAngle[0] >= 15.0f)
        leg1 = false;
    if (legAngle[0] <= -15.0f)
        leg1 = true;

    if (leg2)
        legAngle[1] = legAngle[1] + 1.0f;
    else
        legAngle[1] = legAngle[1] - 1.0f;
    if (legAngle[1] >= 15.0f)
        leg2 = false;
    if (legAngle[1] <= -15.0f)
        leg2 = true;

    if(mov_pos_flag){
        mov+=0.05;
        if(mov>10)
            mov_pos_flag=false;
            //glRotatef(180,0,1,0);
    }
    else{
        mov-=0.05;
        //cout<<"2"<<endl;
        //cout<<mov<<endl;
        if(mov<=-7.5)
            mov_pos_flag=true;
    }

    }
}
};
