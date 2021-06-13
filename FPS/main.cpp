#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
//texture
unsigned int textures[7];
#include "tree.cpp"
#include "bullet.cpp"
#include "robot.cpp"
#include "BmpLoader.h"
#include "helicopter.cpp"
bool head_tex=false;
//shooting
bool shoot=false;
// angle of rotation for the camera direction
float angle = 0.0, yAngle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, ly = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = -5.0f, z = 25.0f;
float roll = 0.0f;

//number of robots
robot r[6];
//bullet
bullet bb;
//tree
tree t[4];
///helicopter
helicopter hel;
float helicopter_rotate=0;
float helicopter_position_vertices[8][3]={
        {1.0,0.0,0.0},
        {-30.0,0.0,30.0},
        {30.0,0.0,-10.0},
        {65.0,0.0,25.0},
        {-10.0,0.0,-20.0},
        {70.0,0.0,-30.0},
        {-20.0,0.0,20.0},
        {10.0,0.0,-5.0}
    };
int select=0;
float helicopter_step_size=0.01;
float helicopter_vertices_angle=0.0;
float hel_x=helicopter_position_vertices[select][0];
float hel_z=helicopter_position_vertices[select][2];
float radius=100.0;
bool radi=true;
//for mouse movements
float halfWidth = (float)(WINDOW_WIDTH/2.0);
float halfHeight = (float)(WINDOW_HEIGHT/2.0);
float mouseX = 0.0f, mouseY = 0.0f;

float translate_x=40.0f;

using namespace std;

extern void DrawCube();

const double PI = 3.14159265389;
extern float blackMat[];


///lights
float dimMat[]={0.412, 0.412, 0.412,1.0f};
float matAmbient[]={0.8f,0.6f,0.3f,1.0f};
//float ambientLight[]={0.412f,0.412f,0.412f,1.0f};
float ambientLight[]={1.0f,1.0f,1.0f,1.0f};
float lightPosition[]={0.0f,20.5f,0.0f,1.0f};
float ambientLightModel[]={0.0f,0.0f,1.0f,1.0f};
float specularLight[]={1.0f,1.0f,1.0f,1.0f};
float specularMat[]={1.0f,1.0f,1.0f,1.0f};
float spotlightPosition[]={0.0f,0.0f,0.0f,1.0f};
float lightDirection[]={0.0f,-1.0f,0.0f};


void copter_movement(){
    ///works

    glPushMatrix();
    glScalef(0.25,0.25,0.25);
    //glPushMatrix();
    glTranslatef(100.0,100.0,0.0);
    glRotatef(helicopter_rotate,0,-1,0);

    glTranslatef(radius,0.0,0.0);

    hel.draw();
    //glLightfv(GL_LIGHT3,GL_POSITION,spotlightPosition);
    //glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,lightDirection);

    //glEnable(GL_LIGHT3);
    //glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glScalef(0.25,0.25,0.25);
    //glPushMatrix();
    glTranslatef(100.0,98.0,0.0);
    glRotatef(helicopter_rotate,0,-1,0);
    glTranslatef(radius,0.0,0.0);
    glLightfv(GL_LIGHT3,GL_POSITION,spotlightPosition);
    glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,lightDirection);
    glPopMatrix();


    ///working
    /*glPushMatrix();
    //glTranslatef(helicopter_position_vertices[select][0],0,helicopter_position_vertices[select][2]);


    glTranslatef(hel_x,0,hel_z);
    glRotatef(90+helicopter_vertices_angle,0,1,0);
    //glTranslatef(0,0,hel_z);;

    glScalef(0.5,0.5,0.5);
    hel.draw();
    glPopMatrix();*/
}



void mouse(int button, int state, int x, int y){
    if(state==GLUT_DOWN){
        if(button==GLUT_LEFT_BUTTON){
            shoot=true;
            //printf("true");
            cout<<shoot<<endl;
        }
        else if(button==GLUT_RIGHT_BUTTON){
            shoot=false;
        }
        //glutPostRedisplay();
    }
    //glutPostRedisplay();

    //else if(state==GLUT_UP){
      //  if(button==GLUT_LEFT_BUTTON){
        //    shoot=false;
          //  cout<<shoot<<endl;
        //}
}


void Grid()
{
    glPushMatrix();
    //glColor3f(1,1,1);

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(i, 0, -50);
        glVertex3f(i, 0, 50);
        glEnd();
    }

    for(int i=-50; i < 50; i++) {
        glBegin(GL_LINES);
        glVertex3f(-50, 0, i);
        glVertex3f(50, 0, i);
        glEnd();
    }

    glPopMatrix();
}
void wall(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[3]);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    //glDisable(GL_TEXTURE_2D);
    //glColor3f(0.7f, 0.7f, 0.7f);
	//floor
	glBegin(GL_QUADS);
	glNormal3f(0.0f,1.0f,0.0f);
	glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, 0.0f, -10.0f);
	glTexCoord2f(0.0f,4.0f);glVertex3f(-10.0f, 0.0f, 10.0f);
	glTexCoord2f(8.0f,4.0f);glVertex3f(10.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f,4.0f);glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();

    //wall
    //glColor3f(0.9294f, 0.9216f, 0.8353f);
    glBindTexture(GL_TEXTURE_2D,textures[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);glVertex3f(-10.0f, 0.0f, -10.0f);
	glTexCoord2f(0.0,4.0);glVertex3f(-10.0f, 7.0f, -10.0f);
	glTexCoord2f(8.0,4.0);glVertex3f(10.0f, 7.0f, -10.0f);
	glTexCoord2f(8.0,0.0);glVertex3f(10.0f, 0.0f, -10.0f);
	glEnd();

	//wall
    //glColor3f(1.0f, 0.851f, 0.702f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, 0.0f, -10.0f);
	glTexCoord2f(0.0f,4.0f);glVertex3f(-10.0f, 7.0f, -10.0f);
	glTexCoord2f(8.0f,4.0f);glVertex3f(-10.0f, 7.0f, 10.0f);
	glTexCoord2f(8.0f,0.0f);glVertex3f(-10.0f, 0.0f, 10.0f);
	glEnd();

	//wall with door
    //glColor3f(1.0f, 0.851f, 0.702f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f,4.0f);glVertex3f(-10.0f, 7.0f, 10.0f);
	glTexCoord2f(3.0f,4.0f);glVertex3f(-6.0f, 7.0f, 10.0f);
	glTexCoord2f(3.0f,0.0f);glVertex3f(-6.0f, 0.0f, 10.0f);
	glEnd();

	//glColor3f(1.0f, 0.851f, 0.702f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);glVertex3f(-3.0f, 0.0f, 10.0f);
	glTexCoord2f(0.0f,4.0f);glVertex3f(-3.0f, 7.0f, 10.0f);
	glTexCoord2f(8.0f,4.0f);glVertex3f(10.0f, 7.0f, 10.0f);
	glTexCoord2f(8.0f,0.0f);glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();

	//above door polygon
	//glColor3f(1.0f, 0.851f, 0.702f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);glVertex3f(-6.0f, 7.0f, 10.0f);
	glTexCoord2f(0.0f,1.0f);glVertex3f(-6.0f, 5.0f, 10.0f);
	glTexCoord2f(2.0f,1.0f);glVertex3f(-3.0f, 5.0f, 10.0f);
	glTexCoord2f(2.0f,0.0f);glVertex3f(-3.0f, 7.0f, 10.0f);
	glEnd();

	//glColor3f(0.4f, 0.2f, 0.0f);
	glLineWidth(30.0f);
	glBegin(GL_LINES);
    glVertex3f(-6.0f, 5.0f, 10.01f);
	glVertex3f(-3.0f, 5.0f, 10.01f);
	glEnd();

	glBegin(GL_LINES);
    glVertex3f(-6.0f, 5.0f, 10.01f);
	glVertex3f(-6.0f, 0.0f, 10.01f);
	glEnd();

	glBegin(GL_LINES);
    glVertex3f(-3.0f, 0.0f, 10.01f);
	glVertex3f(-3.0f, 5.0f, 10.01f);
	glEnd();


	//wall
    //glColor3f(1.0f, 0.851f, 0.702f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f,0.0f);glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(0.0f,4.0f);glVertex3f(10.0f, 7.0f, -10.0f);
	glTexCoord2f(8.0f,4.0f);glVertex3f(10.0f, 7.0f, 10.0f);
	glTexCoord2f(8.0f,0.0f);glVertex3f(10.0f, 0.0f, 10.0f);
	glEnd();

	//ceiling
	glBindTexture(GL_TEXTURE_2D,textures[2]);
	//glColor3f(0.95f, 0.95f, 0.95f);
	glBegin(GL_QUADS);
    glNormal3f(0,1,0);
	glTexCoord2f(0.0f,0.0f);glVertex3f(-10.0f, 7.0f, -10.0f);
	glTexCoord2f(8.0f,0.0f);glVertex3f(10.0f, 7.0f, -10.0f);
	glTexCoord2f(8.0f,8.0f);glVertex3f(10.0f, 7.0f, 10.0f);
	glTexCoord2f(0.0f,8.0f);glVertex3f(-10.0f, 7.0f, 10.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//glClearColor(0.0f,0.0f,0.0f,0.0f);
}

void Lock()
{
    glPushMatrix();

    glTranslatef(x + lx, 2.5f + ly, z + lz);
    glutWireTeapot(0.5);


    //glBegin(GL_LINES);
      //  glVertex3f(x, 2.5f, z);
		//glVertex3f(x + lx, 2.5f + ly, z + lz);
        //glEnd();


    glPopMatrix();
    //glutPostRedisplay();
}

//extern GLfloat robotHair;
void drawSphere(double r, int lats, int longs) {
    glMaterialfv(GL_FRONT,GL_AMBIENT,robotHair);
    int i, j;
    for(i = 0; i <= lats; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= longs; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(r * x * zr0, r * y * zr0, r * z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(r * x * zr1, r * y * zr1, r * z1);
        }
        glEnd();
    }
}

void sceneProperty(){
    glMaterialfv(GL_FRONT,GL_AMBIENT,whiteMat);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,dimMat);
    //glMaterialfv(GL_FRONT,GL_SPECULAR,blackMat);
}
void scene(){
    sceneProperty();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[4]);
    for(int i=0;i<3;i++){
        for(int j=0;j<5;j++){
            if(i==1 && j==1)
                continue;
            if(i==1 && j==3)
                continue;
            glPushMatrix();
            glTranslatef(j*20.0f,0.0f,i*20.0f);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f,0.0f);glVertex3f(-30.0f,0.0f,-30.0f);
            glTexCoord2f(0.0f,8.0f);glVertex3f(-30.0f,0.0f,-10.0f);
            glTexCoord2f(8.0f,8.0f);glVertex3f(-10.0f,0.0f,-10.0f);
            glTexCoord2f(8.0f,0.0f);glVertex3f(-10.0f,0.0f,-30.0f);
            glEnd();
            glPopMatrix();
        }
    }
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textures[5]);

    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);glVertex3f(-30.0f,0.0f,-30.0f);
    glTexCoord2f(40.0f,0.0f);glVertex3f(70.0f,0.0f,-30.0f);
    glTexCoord2f(40.0f,4.0f);glVertex3f(70.0f,7.0f,-30.0f);
    glTexCoord2f(0.0f,4.0f);glVertex3f(-30.0f,7.0f,-30.0f);
    glEnd();
    glBegin(GL_QUADS);
    //glNormal3f(-1.0f,0.0f,0.0f);
    glTexCoord2f(0.0f,0.0f);glVertex3f(70.0f,0.0f,-30.0f);
    glTexCoord2f(24.0f,0.0f);glVertex3f(70.0f,0.0f,30.0f);
    glTexCoord2f(24.0f,4.0f);glVertex3f(70.0f,7.0f,30.0f);
    glTexCoord2f(0.0f,4.0f);glVertex3f(70.0f,7.0f,-30.0f);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);glVertex3f(70.0f,0.0f,30.0f);
    glTexCoord2f(40.0f,0.0f);glVertex3f(-30.0f,0.0f,30.0f);
    glTexCoord2f(40.0f,4.0f);glVertex3f(-30.0f,7.0f,30.0f);
    glTexCoord2f(0.0f,4.0f);glVertex3f(70.0f,7.0f,30.0f);
    glEnd();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f,0.0f);glVertex3f(-30.0f,0.0f,30.0f);
    glTexCoord2f(24.0f,0.0f);glVertex3f(-30.0f,0.0f,-30.0f);
    glTexCoord2f(24.0f,4.0f);glVertex3f(-30.0f,7.0f,-30.0f);
    glTexCoord2f(0.0f,4.0f);glVertex3f(-30.0f,7.0f,30.0f);
    glEnd();
    glPopMatrix();
}

/*void output(){
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos2f(300,300);
    char *s1="hello";
    int len;
    len=strlen(s1);
    for(int i=0;i<len;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,s1[i]);
    }
}*/

void PrintString(unsigned int base, char *str){
    if((base==0)||(str==NULL)){
        return;
    }
    glPushAttrib(GL_LIST_BIT);
    glListBase(base - 32);
    glCallLists(strlen(str),GL_UNSIGNED_BYTE,str);
    glPopAttrib();
}

void tree(){
    glPushMatrix();
    glTranslatef(-25.0f,0.0f,25.0f);
    t[0].draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25.0f,0.0f,-25.0f);
    t[1].draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(65.0f,0.0f,-25.0f);
    t[2].draw();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(65.0f,0.0f,25.0f);
    t[3].draw();
    glPopMatrix();
}
void display(void) {

	// Clear Color and Depth Buffers


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Reset transformations
	glLoadIdentity();

	//output();
	// Set the camera
	gluLookAt(x, 2.5f, z,
		x + lx, 2.5f + ly, z + lz,
		roll + 0.0f, 2.5f, 0.0f);


    //glPushMatrix();
    //PrintString();
    //glPopMatrix();
    //Lock();
    //glutWireTeapot(0.5);
    ///target
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(x+lx,2.5+ly,z+lz);
    glutSolidSphere(0.005, 20,20);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    //glPushMatrix();
    //Grid();
    //glPopMatrix();

    //glPushMatrix();
    //glTranslatef(-4.25,5.0,0.0);
    //glutSolidTeapot(0.5);
    //glPopMatrix();
    glPushMatrix();
    scene();
    glPopMatrix();
    for(int j=0;j<2;j++){
        glPushMatrix();

    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,textures[1]);
    glTranslatef(j*translate_x,0.0f,0.0f);
    wall();
    //glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    //glLoadIdentity();
    //robot ke globally declare korte hobe so it can be deleted if bullet hits it
    for(int i=0;i<3;i++){

        if(r[3*j+i].alive==true){
            glPushMatrix();
            glTranslatef(i*5+j*translate_x,0,0);
            glScalef(0.5,0.5,0.5);
            //(-10,10,0)
            r[3*j+i].DrawRobot(-10,10,-10);
            r[3*j+i].point1_x=r[3*j+i].point1_x*0.5+i*5+j*translate_x;
            r[3*j+i].point1_y=r[3*j+i].point1_y*0.5;
            r[3*j+i].point1_z=r[3*j+i].point1_z*0.5;
            //cout<<r[i].point1_x<<" "<<r[i].point1_y<<" "<<r[i].point1_z<<endl;
            glPopMatrix();
            }
        }
    }

    //robot r;
    //r.DrawRobot(5,10,5);

    //glFlush();

    if(shoot){
        //bullet bb;
        bb.draw();
    }

    //tree
    tree();

    copter_movement();

    glutSwapBuffers();
}

void reshape(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	halfWidth = (float)(w/2.0);
	halfHeight = (float)(h/2.0);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

bool restrict(float check_x, float check_z){

}

void Keyboard(unsigned char key, int xx, int yy) {
    float fraction = 0.2f;
    if(key == 'w'){
            //if(restrict(x+lx,z+lz))
            //{
                x += lx * fraction;
                z += lz * fraction;
            //}

    } else if(key == 'a'){

        x += sin(angle - M_PI/2.0) * fraction;

		z += -cos(angle - M_PI/2.0) * fraction;

    } else if(key == 's'){

        x -= lx * fraction;


		z -= lz * fraction;
    } else if(key == 'd'){
        x += sin(M_PI/2.0 + angle) * fraction;
		z += -cos(M_PI/2.0 + angle) * fraction;
    } else if(key =='l'){
        //glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    } else if(key =='L'){
        //glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
    }else if(key =='k'){
        //glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT1);
    } else if(key =='K'){
        //glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
    }else if(key =='j'){
        //glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT2);
    } else if(key =='J'){
        //glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT2);
    }


	if (key == 27)
		exit(0);
    //glutPostRedisplay();
}

void processMouseMovement(int xx, int yy){

	mouseX = (float)(halfWidth - xx)/halfWidth;
	mouseY = (float)(halfHeight - yy)/halfHeight;
	//angle -= (0.005f * mouseX);
	angle -= (0.019f * mouseX);
	lx = sin(angle);
	lz = -cos(angle);

	if(abs(yAngle) < (M_PI/2)){
		yAngle += (0.005f * mouseY);
	}
	ly = sin(yAngle);
    //glutPostRedisplay();
}
void animate(){
    for(int i=0;i<6;i++){
        r[i].animateRobot();
    }

    bb.path();

    if(shoot){
        //cout<<"ok"<<endl;
        for(int i=0;i<6;i++){
            if((bb.bullet_z+bb.bullet_lz)-r[i].point1_z<0.001){
              //cout<<"same"<<endl;
              if((bb.bullet_x+bb.bullet_lx)>r[i].point1_x-1 && (bb.bullet_x+bb.bullet_lx)<r[i].point1_x && (2.5f+bb.bullet_ly)<r[i].point1_y && (2.5f+bb.bullet_ly)>r[i].point1_y-1){
                cout<<"hit"<<endl;
                r[i].alive=false;
                //bb.live=true;
                shoot=false;
              }//for front face
            }
            //cout<<bb.bullet_z<<"+"<<bb.bullet_lz<<endl;
            //cout<<"robot: "<<r[i].point1_z<<endl;
        }
    }

    hel.animation();

    glutPostRedisplay();
}


void texture(){
    //glEnable(GL_LIGHT0);
    glGenTextures(6, textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl("C:\\Users\\88016\\Desktop\\FPS\\uni1.bmp");
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader b2("C:\\Users\\88016\\Desktop\\FPS\\wall-2.bmp");
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, b2.iWidth, b2.iHeight, GL_RGB, GL_UNSIGNED_BYTE, b2.textureData );

    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader b3("C:\\Users\\88016\\Desktop\\FPS\\Bloody_Handprint.bmp");
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, b3.iWidth, b3.iHeight, GL_RGB, GL_UNSIGNED_BYTE, b3.textureData );

    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader b4("C:\\Users\\88016\\Desktop\\FPS\\floor-3.bmp");
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, b4.iWidth, b4.iHeight, GL_RGB, GL_UNSIGNED_BYTE, b4.textureData );

    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, textures[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader b5("C:\\Users\\88016\\Desktop\\FPS\\dirt3.bmp");
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, b5.iWidth, b5.iHeight, GL_RGB, GL_UNSIGNED_BYTE, b5.textureData );

    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, textures[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader b6("C:\\Users\\88016\\Desktop\\FPS\\wall.bmp");
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, b6.iWidth, b6.iHeight, GL_RGB, GL_UNSIGNED_BYTE, b6.textureData );

    //glGenTextures(6, textures);
    glBindTexture(GL_TEXTURE_2D, textures[6]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, textures[6]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader b7("C:\\Users\\88016\\Desktop\\FPS\\villager.bmp");
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, b7.iWidth, b7.iHeight, GL_RGB, GL_UNSIGNED_BYTE, b7.textureData );
}

void light(){
    //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
    glEnable(GL_LIGHTING);


    ///ambient light property
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
    glEnable(GL_LIGHT0);
    //glEnable(GL_BLEND);
    //glEnable(GL_TEXTURE_2D);
    //glDisable(GL_LIGHT0);
    ///Diffuse light property
    glLightfv(GL_LIGHT1,GL_DIFFUSE,ambientLight);
    glLightfv(GL_LIGHT1,GL_POSITION,lightPosition);
    glEnable(GL_LIGHT1);

    ///Specular light property
    glLightfv(GL_LIGHT2,GL_SPECULAR,specularLight);
    glLightfv(GL_LIGHT2,GL_POSITION,lightPosition);
    glEnable(GL_LIGHT2);
    ///Specular light material
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat);
    glMaterialf(GL_FRONT,GL_SHININESS,10.0f);

    ///spotlight
    glLightfv(GL_LIGHT3,GL_AMBIENT,whiteMat);
    glLightfv(GL_LIGHT3,GL_DIFFUSE,whiteMat);
    glLightfv(GL_LIGHT3,GL_POSITION,spotlightPosition);

    glLightf(GL_LIGHT3,GL_SPOT_CUTOFF,20.0f);
    glLightf(GL_LIGHT3,GL_SPOT_EXPONENT,10.0f);
    glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,lightDirection);
    glEnable(GL_LIGHT3);
}
void init(){
    light();
    //textures=new GLuint[2];
    //glGenTextures(2,textures);
    //LoadTexture("C:\\Users\\88016\\Desktop\\FPS\\enemy_camo.bmp");
    texture();
    //glDisable(GL_LIGHT0);

    //glDisable(GL_LIGHT0);

}
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("A Time To Kill");
    //glEnable(GL_TEXTURE_2D);
    //glFrontFace(GL_CW);
    //glEnable(GL_CULL_FACE);
    init();

    cout<<"Gameplay"<<endl;
    cout<<"# Press \"w\" to move forward"<<endl;
    cout<<"# Press \"s\" to move backward"<<endl;
    cout<<"# Press \"a\" to move left"<<endl;
    cout<<"# Press \"d\" to move right"<<endl;
    cout<<"# Press \"L\" to turn ambient light on"<<endl;
    cout<<"# Press \"l\" to turn ambient light off"<<endl;
    cout<<"# Press \"K\" to turn diffuse light on"<<endl;
    cout<<"# Press \"k\" to turn diffuse light off"<<endl;
    cout<<"# Press \"J\" to turn specular light on"<<endl;
    cout<<"# Press \"j\" to turn specular light on"<<endl;
    cout<<"# Move mouse to look around"<<endl;
    cout<<"# Left click to shoot"<<endl;


    glutDisplayFunc(display);
    //glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(Keyboard);
    glutPassiveMotionFunc(processMouseMovement);
    //glutIdleFunc(Lock);
    //glutKeyboardUpFunc(KeyboardUp);
    glutIdleFunc(animate);

    // OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);


	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;

}
