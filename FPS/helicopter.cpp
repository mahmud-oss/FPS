#include<GL/freeglut.h>
#include<GL/gl.h>
#include<GL/glaux.h>
#include<GL/glu.h>
#include<bits/stdc++.h>
using namespace std;
extern float helicopter_rotate;
extern float helicopter_position_vertices[8][3];
extern float helicopter_step_size;
extern float helicopter_vertices_angle;
extern int select;
extern bool radi;
extern float hel_x,hel_z,radius;
extern unsigned int textures[7];
/*

*/
extern float dimMat[];
extern float blackMat[];
extern float whiteMat[];
inline float teal[]={0.529, 0.808, 0.980};
class helicopter{
    public:
        float comp_x,comp_z;
        float radius=15;
    float spin_angle=0;
    int select=0;
    bool first=true;
    float test=0;
    float angular_step=25.0;
    float rotation_angle=0.0;
    float step_size=0.1f;

void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(-Nx,-Ny,-Nz);
}

void draw_body()
{

	glPushMatrix();
	//glMaterialfv(GL_FRONT,GL_AMBIENT,dimMat);
    //glColor3f(0.412,0.412,0.412);
	glScalef(1.0, 1.0, 2.0);
	glutSolidSphere(5.0, 32, 32);
	//glScalef(1.0, 1.0, 0.5);
	glPopMatrix();
}
void draw_rotor()
{
	glPushMatrix();
    glMaterialfv(GL_FRONT,GL_AMBIENT,dimMat);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,dimMat);
	//glColor3f(1.0f,1.0f,0.0f);

	//glLineWidth(5.0);

	//glBegin(GL_LINES);//fan stick
	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(0.0, 10.0, 0.0);
	//glEnd();
    glPushMatrix();
    glRotatef(90,-1,0,0);
    glutSolidCylinder(0.1,10,20,20);
    glPopMatrix();

    glScalef(2.0, 1.0, 2.0);


	//rotor blades
	for(int i=0; i<4; i++)
	{
	glPushMatrix();

	//variable dite hobe
	glRotatef(rotation_angle, 0.0, 1.0, 0.0);


	glTranslatef(0.0, 10.0, 0.0);
	glRotatef(30.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, -10.0, 0.0);

	glBegin(GL_QUADS);

	glVertex3f(0.0, 10.0, -0.5);
	glVertex3f(10.0, 10.0, -1.0);
	glVertex3f(10.0, 10.0, 1.0);
	glVertex3f(0.0, 10.0, 0.5);
    setNormal(0.0, 10.0, -0.5, 10.0, 10.0, -1.0, 10.0, 10.0, 1.0);
	glEnd();
	glPopMatrix();

	glRotatef(90.0, 0.0, 1.0, 0.0);
	}

	//glEnable(GL_LIGHTING);
	glPopMatrix();

}

void draw_tail()
{
  //tail of heli
  glPushMatrix();
  //glMaterialfv(GL_FRONT,GL_AMBIENT,whiteMat);
  	//glDisable(GL_LIGHTING);
//glColor3f(0.0f,0.0f,1.0f);
	//glColor4f(0.4,0.4,0.4,1.0);//grey

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0);glVertex3f(1.2,-2.0,-9.0);
  glTexCoord2f(2.0,0.0);glVertex3f(1.2,2.0,-9.0);
  glTexCoord2f(2.0,1.0);glVertex3f(0.2,0.2,-29.0);
  glTexCoord2f(0.0,1.0);glVertex3f(0.2,-0.2,-29.0);
  setNormal( 1.2,2.0,-9.0,1.2,-2.0,-9.0,0.2,-0.2,-29.0);
  glEnd();


   glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0);glVertex3f(-1.2,-2.0,-9.0);
  glTexCoord2f(2.0,0.0);glVertex3f(-1.2,2.0,-9.0);
  glTexCoord2f(2.0,1.0);glVertex3f(-0.2,0.2,-29.0);
  glTexCoord2f(0.0,1.0);glVertex3f(-0.2,-0.2,-29.0);
  setNormal(-1.2,2.0,-9.0,-1.2,-2.0,-9.0,-0.2,-0.2,-29.0 );
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0);glVertex3f(1.2,2.0,-9.0);
  glTexCoord2f(2.0,0.0);glVertex3f(-1.2,2.0,-9.0);
  glTexCoord2f(2.0,1.0);glVertex3f(-0.2,0.2,-29.0);
  glTexCoord2f(0.0,1.0);glVertex3f(0.2,0.2,-29.0);
  setNormal(-0.2,0.2,-29.0,-1.2,2.0,-9.0,1.2,2.0,-9.0);
  //glNormal3f(0,-1,0);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(0.0,0.0);glVertex3f(1.2,-2.0,-9.0);
  glTexCoord2f(2.0,0.0);glVertex3f(-1.2,-2.0,-9.0);
  glTexCoord2f(2.0,1.0);glVertex3f(-0.2,-0.2,-29.0);
  glTexCoord2f(0.0,1.0);glVertex3f(0.2,-0.2,-29.0);
  //setNormal(1.2,-2.0,-9.0,-1.2,-2.0,-9.0,-0.2,-0.2,-29.0);
  glEnd();

  	//glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
  glPopMatrix();

}

void draw_leg()
{
  //glPushMatrix();

  	//glDisable(GL_LIGHTING);
	//glColor3f(0.7,0.7,0.7);//grey

glPushMatrix();
  glTranslatef(5.0f,-7.0f,-7.0f);
  glutSolidCylinder(0.1,14,20,20);

  glPushMatrix();
    glRotatef(135,-1,0,0);
    glutSolidCylinder(0.1,2,20,20);
    glTranslatef(-10.0f,0.0f,0.0f);
    glutSolidCylinder(0.1,2,20,20);
  glPopMatrix();
    glTranslatef(-10.0f,0.0f,0.0f);
    glutSolidCylinder(0.1,14,20,20);
glPopMatrix();

glPushMatrix();
    glTranslatef(-5.0f,-7.0f,7.0f);
    glRotatef(-45,1,0,0);
    glutSolidCylinder(0.1,2,20,20);
    glTranslatef(10.0f,0.0f,0.0f);
    glutSolidCylinder(0.1,2,20,20);
glPopMatrix();
glPushMatrix();
    glTranslatef(-5.0,-7.0,-5.0);
    glRotatef(90,0,1,0);
    glRotatef(55,-1,0,0);
    glutSolidCylinder(0.1,8.7,20,20);
glPopMatrix();
glPushMatrix();
    glTranslatef(-5.0,-7.0,5.0);
    glRotatef(90,0,1,0);
    glRotatef(55,-1,0,0);
    glutSolidCylinder(0.1,8.7,20,20);
glPopMatrix();
glPushMatrix();
    glTranslatef(0.0,0.0,-5.0);
    glRotatef(90,0,1,0);
    glRotatef(55,1,0,0);
    glutSolidCylinder(0.1,8.7,20,20);
glPopMatrix();
glPushMatrix();
    glTranslatef(0.0,0.1,5.0);
    glRotatef(90,0,1,0);
    glRotatef(55,1,0,0);
    glutSolidCylinder(0.1,8.7,20,20);
glPopMatrix();

  	//glEnable(GL_LIGHTING);

  //glPopMatrix();
}

void draw_tail_fan()
{
	glPushMatrix();
	//glColor3f(1.0f,0.0f,0.0f);
    glTranslatef(0.0,0.0,-28.0);
	glRotatef(-90.0,0.0,0.0,1.0);
	glScalef(0.15,0.11,0.15);
	draw_rotor();
	glPopMatrix();

}

void draw(){
    /*DrawCube(1.0,1.0,1.0);
    cockpit();
    glPushMatrix();
    glTranslatef(3.0,0.75,0.75);
    //glTranslatef(0.5,0.25,0.75);
    glScalef(1.5,0.5,0.5);

    DrawCube(0.0,0.0,0.0);
    glPopMatrix();*/
    //cout<<"Draw==>"<<hel_x<<" "<<hel_z<<endl;
    glMaterialfv(GL_FRONT,GL_SPECULAR,whiteMat);
    glMaterialfv(GL_FRONT,GL_AMBIENT,teal);
    glPushMatrix();
    /*cout<<"d "<<hel_x<<" "<<hel_z<<endl;
    cout<<"d "<<position_vertices[(select+1)%8][0]<<" "<<position_vertices[(select+1)%8][2]<<endl;
    glTranslatef(hel_x,0,hel_z);

    glRotatef(test,0,1,0);*/
   // glRotated(spin_angle,0,1,0);
    //glPushMatrix();

    //glRotated(spin_angle,0,1,0);
    //glTranslatef(radius*cos(spin_angle),0.0,radius*sin(spin_angle));

    //glTranslatef(radius*cos(spin_angle),0.0,radius*sin(spin_angle));
    //glTranslatef(radius*cos(spin_angle),0.0,radius*sin(spin_angle));
    //glPushMatrix();
    //glRotated(spin_angle,0,1,0);
    //glTranslatef(radius*cos(spin_angle),0.0,radius*sin(spin_angle));
    //glRotatef(45,0,0,1);
    draw_body();

	draw_rotor();

   	draw_tail();

	draw_leg();

	draw_tail_fan();
	//glPopMatrix();

	glPopMatrix();
}

void animation(){
    rotation_angle+=angular_step;
    helicopter_rotate+=0.5;
    //cout<<radius<<endl;



    if(radi){
        radius-=3.0;
        if(radius<0)
            radi=false;
    }
    if(!radi){
        radius+=3.0;
        if(radius>100.0){
            radi=true;
        }
    }

    ///linear movement
    /*
        comp_x=helicopter_position_vertices[(select+1)%8][0];
        comp_z=helicopter_position_vertices[(select+1)%8][2];
        cout<<"distance to cover : "<<hel_x-comp_x<<" "<<hel_z-comp_z<<endl;
        if(-0.01<(hel_x-comp_x)<0.01){
            cout<<"hittt======================================================"<<endl;
                select++;
            helicopter_step_size=0.01;
            hel_x=helicopter_position_vertices[select%8][0];
            hel_z=helicopter_position_vertices[select%8][2];

            cout<<"ME: "<<hel_x<<" "<<hel_z<<endl;
            cout<<"TARGET: "<<helicopter_position_vertices[(select+1)%8][0]<<" "<<helicopter_position_vertices[(select+1)%8][2]<<endl;
        }

        cout<<"old me x +: "<<(helicopter_position_vertices[(select+1)%8][0]-helicopter_position_vertices[select%8][0])*helicopter_step_size<<endl;
        cout<<"old me z +: "<<(helicopter_position_vertices[(select+1)%8][2]-helicopter_position_vertices[select%8][2])*helicopter_step_size<<endl;
        //hel_x=helicopter_position_vertices[select%8][0]+
          hel_x+=
            (helicopter_position_vertices[(select+1)%8][0]-helicopter_position_vertices[select%8][0])*helicopter_step_size;
        //hel_z=helicopter_position_vertices[select%8][2]+
          hel_z+=
            (helicopter_position_vertices[(select+1)%8][2]-helicopter_position_vertices[select%8][2])*helicopter_step_size;

        cout<<"New ME: "<<hel_x<<" "<<hel_z<<endl;
        cout<<"TARGET: "<<helicopter_position_vertices[(select+1)%8][0]<<" "<<helicopter_position_vertices[(select+1)%8][2]<<endl;

        helicopter_vertices_angle=180 * (atan2(helicopter_position_vertices[select%8][2],helicopter_position_vertices[select%8][0])-
                        atan2(helicopter_position_vertices[(select+1)%8][2],helicopter_position_vertices[(select+1)%8][0]))/3.1416;
        //cout<<helicopter_vertices_angle<<endl;
        //helicopter_step_size+=0.01;
            //cout<<test<<endl;
    //step_size+=0.1;

    /*if(select>=8){
        select=0;
    }*/
    //spin_angle+=0.01;


}
};

