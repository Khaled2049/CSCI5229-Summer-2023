// Khaled Hossain 

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif


int mode=0;       //  Projection mode
int th=10;         //  Azimuth of view angle
int ph=8;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=2;     //  Aspect ratio
double dim=8;   //  Size of world

float xpos = -0.12, ypos = 4.10, zpos = 12.99, xRotation = 16, yRotation = 1;

//  Macro for sin & cos in degrees
#define PI 3.14159265358979323846
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
#define SIZE 4
#define CHECKER_SIZE 1
/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Check for OpenGL errors
 */
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

/*
 *  Set projection
 */
static void Project(int mode, double fov,double asp,double dim)
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode == 1)
      gluPerspective(fov,asp,dim/4,4*dim);
   //  Orthogonal transformation
   else if (mode == 0)
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   else if (mode == 2) {
      th = -5;

      // printf("xpos: %f\n", xpos);
      // printf("ypos: %f\n", ypos);
      // printf("zpos: %f\n", zpos);
      // printf("xRotation: %f\n", xRotation);
      // printf("yRotation: %f\n", yRotation);
      // printf("th: %d\n", th);
      // printf("ph: %d\n", ph);      
      // printf("asp: %f\n", asp);
      // printf("dim: %f\n", dim);
      // printf("-------------------\n");

      gluPerspective(fov, asp, dim/4, th);
   }
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
   //  Front
   glVertex3f(-1,-1, 1);
   glVertex3f(+1,-1, 1);
   glVertex3f(+1,+1, 1);
   glVertex3f(-1,+1, 1);
   //  Back   
   glVertex3f(+1,-1,-1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,+1,-1);
   glVertex3f(+1,+1,-1);
   //  Right   
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);
   //  Left   
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);
   //  Top   
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);
   //  Bottom   
   glVertex3f(-1,-1,-1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,-1,+1);
   glVertex3f(-1,-1,+1);
   //  End
   glEnd();
   //  Undo transofrmations
   glPopMatrix();
}

// Draw checkerd house floor
void drawCheckeredPlane() {   
    glBegin(GL_QUADS);
    for (int i = -SIZE; i < SIZE; i++) {
        for (int j = -SIZE; j < SIZE; j++) {
            if ((i + j) % 2 == 0)
                glColor3f(1.0, 1.0, 1.0);  // White color
            else
                glColor3f(0.0, 0.0, 0.0);  // Black color

            float x = i * CHECKER_SIZE;
            float z = j * CHECKER_SIZE;

            glVertex3f(x, -8, z);
            glVertex3f(x + CHECKER_SIZE, -8, z);
            glVertex3f(x + CHECKER_SIZE, -8, z + CHECKER_SIZE);
            glVertex3f(x, -8, z + CHECKER_SIZE);
        }
    }
    glEnd();
}

void drawRoof(double x, double y, double z) {
   glColor3f(1.0f, 1.0f, 0.0f);
   glTranslatef(x, 0, z);
   GLfloat pyramidWidth = 8.25f;   // Width of the pyramid   
   GLfloat cubeHeight = 5.0f;  // Height of the cube
   
   GLfloat halfWidth = pyramidWidth / 2.0f;

   glBegin(GL_TRIANGLES);
   // Front face
   glVertex3f(0.0f, cubeHeight, 0.0f);
   glVertex3f(-halfWidth, 0.0f, halfWidth);
   glVertex3f(halfWidth, 0.0f, halfWidth);

   // Right face
   glVertex3f(0.0f, cubeHeight, 0.0f);
   glVertex3f(halfWidth, 0.0f, halfWidth);
   glVertex3f(halfWidth, 0.0f, -halfWidth);

   // Back face
   glVertex3f(0.0f, cubeHeight, 0.0f);
   glVertex3f(halfWidth, 0.0f, -halfWidth);
   glVertex3f(-halfWidth, 0.0f, -halfWidth);

   // Left face
   glVertex3f(0.0f, cubeHeight, 0.0f);
   glVertex3f(-halfWidth, 0.0f, -halfWidth);
   glVertex3f(-halfWidth, 0.0f, halfWidth);   
   glEnd();
}



/*
 *  Draw a house
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void drawHouse(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{   
   
   //  Save transformation
   glPushMatrix();
   drawRoof(x, y, z);   
   drawCheckeredPlane();
   //  Offset
   glTranslatef(0, -4, 0);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Cube
   glBegin(GL_QUADS);
   //  Front with door
   glColor3f(1,0.25,0.75);

   glVertex3f(-1, 1, 1);
   glVertex3f(-1, 0, 1);
   glVertex3f(1, 0, 1);
   glVertex3f(1, 1, 1);
   
   glVertex3f(-1, -1, 1);
   glVertex3f(-0.25, -1, 1);
   glVertex3f(-0.25, 1, 1);
   glVertex3f(-1, 1, 1);

   glVertex3f(1, 1, 1);
   glVertex3f(0.25, 1, 1);
   glVertex3f(0.25, -1, 1);
   glVertex3f(1, -1, 1);


   //  Back
   glColor3f(0.5,0.25,0.75);
   glVertex3f(+1,-1,-1);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,+1,-1);
   glVertex3f(+1,+1,-1);

   //  Right
   glColor3f(0.3,0.25,0.75);
   glVertex3f(+1,-1,+1);
   glVertex3f(+1,-1,-1);
   glVertex3f(+1,+1,-1);
   glVertex3f(+1,+1,+1);

   //  Left
   glColor3f(0.3,1,0.75);
   glVertex3f(-1,-1,-1);
   glVertex3f(-1,-1,+1);
   glVertex3f(-1,+1,+1);
   glVertex3f(-1,+1,-1);

   //  Top
   glColor3f(0.3,0.25,0.9);
   glVertex3f(-1,+1,+1);
   glVertex3f(+1,+1,+1);
   glVertex3f(+1,+1,-1);
   glVertex3f(-1,+1,-1);

   //  End
   glEnd();
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
{
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
static void sphere2(double x,double y,double z,double r)
{
   const int d=15;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);
   
   //  Latitude bands
   for (int ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
}


void drawCylinder(float radius, float height) {
    int numSlices = 20;
    float angleStep = 2 * PI / numSlices;
    
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numSlices; i++) {
        float angle = i * angleStep;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        glVertex3f(x,  height, z);
        glVertex3f(x, -height, z);
    }
    
    glEnd();
}

/*
 * Icosahedron defined as triangles
 */
const int Ni=60;
//  Vertex coordinates and colors
const float xyzrgb[] =
{
    0.276, 0.851, 0.447,  0.0,0.0,1.0,
    0.894, 0.000, 0.447,  0.0,0.0,1.0,
    0.000, 0.000, 1.000,  0.0,0.0,1.0,
   -0.724, 0.526, 0.447,  0.0,1.0,0.0,
    0.276, 0.851, 0.447,  0.0,1.0,0.0,
    0.000, 0.000, 1.000,  0.0,1.0,0.0,
   -0.724,-0.526, 0.447,  0.0,1.0,1.0,
   -0.724, 0.526, 0.447,  0.0,1.0,1.0,
    0.000, 0.000, 1.000,  0.0,1.0,1.0,
    0.276,-0.851, 0.447,  1.0,0.0,1.0,
   -0.724,-0.526, 0.447,  1.0,0.0,1.0,
    0.000, 0.000, 1.000,  1.0,0.0,1.0,
    0.894, 0.000, 0.447,  1.0,1.0,0.0,
    0.276,-0.851, 0.447,  1.0,1.0,0.0,
    0.000, 0.000, 1.000,  1.0,1.0,0.0,
    0.000, 0.000,-1.000,  0.0,0.0,1.0,
    0.724, 0.526,-0.447,  0.0,0.0,1.0,
   -0.276, 0.851,-0.447,  0.0,0.0,1.0,
    0.000, 0.000,-1.000,  0.0,1.0,0.0,
   -0.276, 0.851,-0.447,  0.0,1.0,0.0,
   -0.894, 0.000,-0.447,  0.0,1.0,0.0,
    0.000, 0.000,-1.000,  0.0,1.0,1.0,
   -0.894, 0.000,-0.447,  0.0,1.0,1.0,
   -0.276,-0.851,-0.447,  0.0,1.0,1.0,
    0.000, 0.000,-1.000,  1.0,0.0,0.0,
   -0.276,-0.851,-0.447,  1.0,0.0,0.0,
    0.724,-0.526,-0.447,  1.0,0.0,0.0,
    0.000, 0.000,-1.000,  1.0,0.0,1.0,
    0.724,-0.526,-0.447,  1.0,0.0,1.0,
    0.724, 0.526,-0.447,  1.0,0.0,1.0,
    0.894, 0.000, 0.447,  1.0,1.0,0.0,
    0.276, 0.851, 0.447,  1.0,1.0,0.0,
    0.724, 0.526,-0.447,  1.0,1.0,0.0,
    0.276, 0.851, 0.447,  0.0,0.0,1.0,
   -0.724, 0.526, 0.447,  0.0,0.0,1.0,
   -0.276, 0.851,-0.447,  0.0,0.0,1.0,
   -0.724, 0.526, 0.447,  0.0,1.0,0.0,
   -0.724,-0.526, 0.447,  0.0,1.0,0.0,
   -0.894, 0.000,-0.447,  0.0,1.0,0.0,
   -0.724,-0.526, 0.447,  0.0,1.0,1.0,
    0.276,-0.851, 0.447,  0.0,1.0,1.0,
   -0.276,-0.851,-0.447,  0.0,1.0,1.0,
    0.276,-0.851, 0.447,  1.0,0.0,0.0,
    0.894, 0.000, 0.447,  1.0,0.0,0.0,
    0.724,-0.526,-0.447,  1.0,0.0,0.0,
    0.276, 0.851, 0.447,  1.0,0.0,1.0,
   -0.276, 0.851,-0.447,  1.0,0.0,1.0,
    0.724, 0.526,-0.447,  1.0,0.0,1.0,
   -0.724, 0.526, 0.447,  1.0,1.0,0.0,
   -0.894, 0.000,-0.447,  1.0,1.0,0.0,
   -0.276, 0.851,-0.447,  1.0,1.0,0.0,
   -0.724,-0.526, 0.447,  0.0,0.0,1.0,
   -0.276,-0.851,-0.447,  0.0,0.0,1.0,
   -0.894, 0.000,-0.447,  0.0,0.0,1.0,
    0.276,-0.851, 0.447,  0.0,1.0,0.0,
    0.724,-0.526,-0.447,  0.0,1.0,0.0,
   -0.276,-0.851,-0.447,  0.0,1.0,0.0,
    0.894, 0.000, 0.447,  0.0,1.0,1.0,
    0.724, 0.526,-0.447,  0.0,1.0,1.0,
    0.724,-0.526,-0.447,  0.0,1.0,1.0,
};

static unsigned int vbo3=0; //  Icosahedron VBO
static void icosahedron3(float x,float y,float z,float s,float th)
{
   //  Bind VBO
   if (vbo3)
      glBindBuffer(GL_ARRAY_BUFFER,vbo3);
   //  Initialize VBO on first call
   else
   {
      //  Get buffer name
      glGenBuffers(1, &vbo3);
      //  Bind VBO
      glBindBuffer(GL_ARRAY_BUFFER, vbo3);
      //  Copy icosahedron to VBO
      glBufferData(GL_ARRAY_BUFFER,sizeof(xyzrgb),xyzrgb,GL_STATIC_DRAW);
   }

   //  Define vertexes
   glVertexPointer(3,GL_FLOAT,6*sizeof(float),(void*)0);
   glEnableClientState(GL_VERTEX_ARRAY);
   //  Define colors for each vertex
   glColor3f(0,0.44,0.2);
   // glEnableClientState(GL_COLOR_ARRAY);
   //  Draw icosahedron
   glPushMatrix();
   glTranslatef(x,y,z);
   glRotatef(th,1,0,0);
   glScalef(s,s,s);
   glDrawArrays(GL_TRIANGLES,0,Ni);
   glPopMatrix();
   //  Disable vertex array
   glDisableClientState(GL_VERTEX_ARRAY);
   //  Disable color array
   glDisableClientState(GL_COLOR_ARRAY);
   //  Release VBO
   glBindBuffer(GL_ARRAY_BUFFER,0);
}

void drawTree(float size) {
   glScaled(size, size, size);
   icosahedron3(0,10,0,5, 3);
   glColor3f(0.3,0.24,0);
   drawCylinder(1, 7);
}


void drawRobot(double dx,double dy,double dz) {
   glTranslatef(dx, dy, dz);
   
   // Draw head & body
   glColor3f(0.0f, 0.5f, 0.0f);
   cube(0,0.2,0 , 0.25,0.3,0.2 , 0);
   
   glColor3f(0.3, 0.25, 0.5);
   sphere2(0,0.7,0 , 0.2);
   
   glColor3f(0, 0.5, 0);
   // Draw arms
   glPushMatrix();
   glTranslatef(-0.3, 0.1, 0.0);
   drawCylinder(0.1, 0.4);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.3, 0.1, 0.0);
   drawCylinder(0.1, 0.4);
   glPopMatrix();
   
   glColor3f(0, 0, 0.5);
   // Draw legs
   glPushMatrix();
   glTranslatef(-0.12, -0.5, 0.0);
   drawCylinder(0.1, 0.7);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.12, -0.5, 0.0);
   drawCylinder(0.1, 0.7);
   glPopMatrix();

   glTranslatef(-dx, -dy, -dz);
}


/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Overhead perspective;
   if (mode == 1)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Overhead orthogonal;
   else if (mode == 0)
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
   // First person perspective.
   else if (mode == 2)
   {    
    glRotatef(xRotation,1.0,0.0,0.0);  // rotate camera on the x-axis 
    glRotatef(yRotation,0.0,1.0,0.0);  // rotate camera on the y-axis 
    glTranslated(-xpos,-ypos,-zpos);   // translate the screen to the position of our camera
   }

   glScaled(0.25,0.25,0.25);       

   //  Display parameters
   glWindowPos2i(5,5);
   
   glColor3f(1, 0, 0);
   Print("Angle=%d,%d  Dim=%.1f FOV=%d",th,ph,dim,fov);
   if (mode == 0) {
      Print(" Camera = Perpective");
   } else if (mode == 1) {
      Print(" Camera = Orthogonal");
   } else if (mode == 2) {
      Print(" Camera = First Person");
   }

      
   // Sun
   glColor3f(1, 0.5, 0);   
   sphere2(0, 20, 0 , 4.5);

   // Houses
   drawHouse(-10,-4,0 , 4,4,4 , 0);   
   drawHouse(0,-4,0 , 4,4,4 , 0);   
   drawHouse(10,-4,0 , 4,4,4 , 0);   

   // Robots
   drawRobot(0, -6.75, 0);
   drawRobot(-1, -6.75, 0);
   
   drawRobot(-8, -6.75, 3);
   drawRobot(-7, -6.75, 1);

   drawRobot(10, -6.75, 3);
   drawRobot(13, -6.75, 1);

   drawRobot(-6, -6.75, 8);
   drawRobot(3, -6.75, 8);
   drawRobot(10, -6.75, 8);
   
   glColor3f(1, 0.75, 0);
   cube(0,-8.25,0 , 20,0,20 , 0);

   glTranslatef(-10, -0.5,-7);
   drawTree(1);

   glTranslatef(15.75, -4, 16);
   drawTree(0.5);

   glTranslatef(19, 6, 14);
   drawTree(2);
   


   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{

   if (mode == 2) {         
      if (mode == 2) {
         if (key == GLUT_KEY_DOWN) {
            xRotation += 5;
            if (xRotation >360) xRotation -= 360;
         }
         else if (key == GLUT_KEY_UP)
         {
            xRotation -= 5;
            if (xRotation < -360) xRotation += 360;
         }
         if (key == GLUT_KEY_RIGHT)
         {
            yRotation += 5;
            if (yRotation >360) yRotation -= 360;
         }
         else if (key == GLUT_KEY_LEFT)
         {
            yRotation -= 5;
            if (yRotation < -360) yRotation += 360;
         }
      }
   }
   else {
      //  Right arrow key - increase angle by 5 degrees
      if (key == GLUT_KEY_RIGHT)
         th += 5;
      //  Left arrow key - decrease angle by 5 degrees
      else if (key == GLUT_KEY_LEFT)
         th -= 5;
      //  Up arrow key - increase elevation by 5 degrees
      else if (key == GLUT_KEY_UP)
         ph += 5;
      //  Down arrow key - decrease elevation by 5 degrees
      else if (key == GLUT_KEY_DOWN)
         ph -= 5;
      //  Keep angles to +/-360 degrees
      th %= 360;
      ph %= 360;
   }


   //  Update projection
   Project(mode, fov, asp, dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0); 
   //  Switch display mode
   else if (ch == 'm' || ch == 'M'){
      mode += 1;
      if( mode > 2) {
         mode = 0;
      }
   }
   //  Change field of view angle
   else if (ch == '-')
      fov++;
   else if (ch == '+')
      fov--;

   // w to move forward
   else if (ch =='w' || ch =='W')
   {
      float xRotationrad, yRotationrad;
      yRotationrad = (yRotation / 180 * PI);
      xRotationrad = (xRotation / 180 * PI);
      xpos += (sin(yRotationrad));
      zpos -= (cos(yRotationrad));
      ypos -= (sin(xRotationrad));
   }
   // a to move left
   else if (ch=='a' || ch =='A')
   {
      float yRotationrad;
      yRotationrad = (yRotation / 180 * PI);
      xpos -= (cos(yRotationrad)) * 0.2;
      zpos -= (sin(yRotationrad)) * 0.2;
   }
   // s to move backward
   else if (ch =='s' || ch =='S')
   {
      float xRotationrad, yRotationrad;
      yRotationrad = (yRotation / 180 * PI);
      xRotationrad = (xRotation / 180 * PI);
      xpos -= (sin(yRotationrad));
      zpos += (cos(yRotationrad)) ;
      ypos += (sin(xRotationrad));
   }
   // d to move right
   else if (ch =='d' || ch =='D')
   {
      float yRotationrad;
      yRotationrad = (yRotation / 180 * PI);
      xpos += (cos(yRotationrad)) * 0.2;
      zpos += (sin(yRotationrad)) * 0.2;
   }

   //  Reproject
   Project(mode,fov,asp,dim);
   
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project(mode, fov, asp, dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(1000,1000);
   glutCreateWindow("Khaled Hossain");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
