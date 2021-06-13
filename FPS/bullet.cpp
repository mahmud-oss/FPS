#include <GL/freeglut.h>
#include <GL/glaux.h>
#include <bits/stdc++.h>
#include <math.h>
using namespace std;

extern float x,z,lx,ly,lz;
extern bool shoot;
//float pseudo_lx;
//float pseudo_ly;
//float pseudo_lz;
//extern class robot r[3];
class bullet{
public:
    float pseudo_lx;
    float pseudo_ly;
    float pseudo_lz;
    float bullet_x;
    float bullet_y;
    float bullet_z;
    float bullet_lx;
    float bullet_ly;
    float bullet_lz;
    bool live=true;
    void draw(){
        if(live){
                //cout<<r[0].alive<<endl;
            bullet_x=x;
            bullet_y=2.5;
            bullet_z=z;
            bullet_lx=0;
            bullet_ly=0;
            bullet_lz=0;
            pseudo_lx=lx;
            pseudo_ly=ly;
            pseudo_lz=lz;
            live=false;
        }
        glPushMatrix();
        //glColor3f(1.0f,0.0f,0.0f);

        //glTranslatef(bullet_x+bullet_lx,bullet_y,bullet_z);

        glTranslatef(bullet_x+bullet_lx,2.5f+bullet_ly,bullet_z+bullet_lz);

        //cout<<"=========================================="<<endl;
        //cout<<bullet_x<<" "<<"2.5"<<" "<<bullet_z<<endl;
        //cout<<bullet_lx<<" "<<bullet_ly<<" "<<bullet_lz<<endl;
        //cout<<bullet_x+pseudo_lx<<" "<<2.5f+pseudo_ly<<" "<<bullet_z+pseudo_lz<<endl;
        //cout<<bullet_x+bullet_lx<<" "<<2.5f+bullet_ly<<" "<<bullet_z+bullet_lz<<endl;

        glutSolidSphere(0.05f,20,20);
        //glutSolidSphere(5.0f,20,20);
        glPopMatrix();
    }
    void path(){
        if(bullet_x+pseudo_lx>bullet_x){
            bullet_lx+=0.1;
            //bullet_lx+=1;
        }
        else if(bullet_x+pseudo_lx==bullet_x){
            bullet_lx=bullet_lx;
        }
        else{
            bullet_lx-=0.1;
            //bullet_lx-=1;
        }

        //bullet_ly=(((bullet_x+bullet_lx)*pseudo_ly+(2.5f*pseudo_ly-bullet_x*pseudo_ly))/pseudo_lx)-2.5f;
        //bullet_ly=(pseudo_ly/pseudo_lx)*(bullet_x+bullet_lx-bullet_x);
        bullet_ly=(pseudo_ly/pseudo_lx)*(bullet_lx);
        //bullet_lz=(((pseudo_lz*(2.5f+bullet_ly))+(bullet_z*pseudo_ly-2.5f*pseudo_lz))/pseudo_ly)-bullet_z;
        bullet_lz=(pseudo_lz/pseudo_ly)*bullet_ly;

        //if(bullet_x+pseudo_lx>bullet_x){
        //    bullet_lx+=0.001;
        //}
        //else if(bullet_x+pseudo_lx==bullet_x){
        //    bullet_lx=bullet_lx;
        //}
        //else{
        //    bullet_lx-=0.001;
        //}
        //bullet_y=(bullet_ly*bullet_x+2.5*bullet_ly-bullet_x*bullet_ly)/bullet_lx;
        //bullet_z=
        if(sqrt(bullet_lx*bullet_lx+bullet_ly*bullet_ly+bullet_lz*bullet_lz)>=10.01){
            shoot=false;
            live=true;
            //cout<<"0"<<endl;
        }
        //glutPostRedisplay();

    }

};
