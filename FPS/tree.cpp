#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include "vase.cpp"
extern const double PI;
using namespace std;
inline GLfloat treeAmbient[]={0.000, 0.392, 0.000,1.0f};
extern float blackMat[];

class tree{
public:
    vase v;
    int L=6;
    int dgre=3;
    int ncpt=L+1;
    int clikd=0;
    int nt = 80;				//number of slices along x-direction
    int ntheta = 40;
GLfloat ctrlpoints[7][3] =
{
    {-4.9,-0.45,0.0},
    {-4.725,0.975,0.0},
    {-5.25,2.825,0.0},
    {-4.575,4.5,0.0},
    {-3.275,5.525,0.0},
    {-2.175,6,0.0}

};//tree;L=6
long long nCr(int n, int r)
{
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

void BezierCurve ( double t,  float xy[2])
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[i][0];
        y+=coef*ctrlpoints[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}
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
void bottleBezier()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }


            glVertex3f (x1, y1, z1);


            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}
void materialColor(){
    glMaterialfv(GL_FRONT,GL_AMBIENT,treeAmbient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,treeAmbient);
    glMaterialfv(GL_FRONT,GL_SPECULAR,blackMat);
}
void draw(){
        materialColor();
        glPushMatrix();

        glScalef(0.25,0.5,0.25);
        glTranslatef(0.0f,7.5f,0.0f);
        glRotatef(90,0,0,1);
        //glRotatef(90,1,0,0);
        bottleBezier();
        glPopMatrix();
        glPushMatrix();
        //glTranslatef(0.0,-2.0f,0.0f);
        glScalef(0.5f,0.5f,0.5f);

        v.draw();
        glPopMatrix();
    }
};

