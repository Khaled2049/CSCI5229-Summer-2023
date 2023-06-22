// Name: Khaled Hossain

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <stdbool.h>

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

int rotate_y = 50;
int rotate_x = 50;
bool animate = false;

/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;


GLdouble arr[50000][3];

// Function Prototypes
void createLorenzPoints();
void drawLorenzAttractor();
void display();
void reshape(int,int);
void Print(const char* format , ...);
static void special(int k, int x, int y);
void key(unsigned char ch,int x,int y);


/*
 * This function is called by GLUT when idle
 */
void idle() {
    //  Get elapsed (wall) time in seconds
    double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;

    if (animate == true) {
      if (s < 15 && s > 5) {
        r += fmod(0.01*t, 360);
        s += fmod(0.01*t, 360);
        b += fmod(0.01*t, 360);
      } else {
        s  = 10.0;
        b  = 2.6666;
        r  = 28.0;
      }
    }

    createLorenzPoints();
    drawLorenzAttractor();
    glutPostRedisplay();
}


void key(unsigned char ch,int x,int y) {
    //  Exit on ESC
    if (ch == 27){
      exit(0);
    }
    // Increase value of sigma
    else if (ch == '1') {
        s += 0.1;
    }
    // Increase value of beta
    else if (ch == '2') {
        b += 0.1;
    }
    // Increase value of rho
    else if (ch == '3') {
        r += 0.1;
    }
    // decrease value of sigma
    else if (ch == '4') {
        s -= 0.1;
    }
    // decrease value of beta
    else if (ch == '5') {
        b -= 0.1;
    }
    // decrease value of rho
    else if (ch == '6') {
        r -= 0.1;
    }
    // Toggle animation
    else if (ch == 'a') {
      animate = !animate;
    }
    
    drawLorenzAttractor();  
    glutPostRedisplay();
}

void display() {
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Rotate 
    glRotatef(rotate_x, 1.0, 0.0, 0.0 );  //x coordinate
    glRotatef(rotate_y, 0.0, 1.0, 0.0 );  //y coordinate

    // Draw axis lines
    glBegin(GL_LINES);
    glColor3f(1, 1, 1); //White

    glVertex3f(0, 0, 0);
    glVertex3f(50, 0, 0);

    // Y
    glVertex3f(0, 0, 0);
    glVertex3f(0, 50, 0);

    // Z
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 50);

    glEnd();
    
    glRasterPos3d(50.05,0,0);
    Print("X");
    glRasterPos3d(0,50.05,0);
    Print("Y");
    glRasterPos3d(0,0,50.05);
    Print("Z");
    glEnd();

    // Draw the Lorenz Attractor
    drawLorenzAttractor();

    //  Display rotation angles
    glColor3f(1,1,1);
    glWindowPos2i(5,5);
    Print("Sigma = %1.1f  Beta = %1.1f  Rho = %1.1f", s, b, r);

    //  Display parameters
    glWindowPos2i(5, 980);
    Print("Press a to toggle animation and esc to exit");
    glWindowPos2i(5, 960);
    Print("1, 2, 3 to [+] values of Sigma, Beta, Rho");
    glWindowPos2i(5, 940);
    Print("4, 5, 6 to [-] values of Sigma, Beta, Rho");

    // Force the execution of queued commands
    glFlush();

    //swaps the buffers of the current window if double buffered
    glutSwapBuffers();
}

//  Special keys
static void special(int k, int x, int y) {
    switch (k) {
    case GLUT_KEY_UP:
      rotate_x -= 10.0;
      break;
    case GLUT_KEY_DOWN:
      rotate_x += 10.0;
      break;
    case GLUT_KEY_LEFT:
      rotate_y -= 10.0;
      break;
    case GLUT_KEY_RIGHT:
      rotate_y += 10.0;
      break;
    default:
      return;
    }
    //  Keep angles to +/-360 degrees
    rotate_x %= 360;
    rotate_y %= 360;

    // Marks the current window as needing to be redisplayed
    glutPostRedisplay();
}

// Create the Lorenz Attractor
void drawLorenzAttractor(){
    glLineWidth(1);
    glBegin(GL_LINE_STRIP);
    
    // Calculate the RGB values based on time (i)
    for (int i=0; i<50000; i++){
      float t = (float)i / 50000.0f;
      float red = 0.5f * sin(2.0f * M_PI * t);
      float green = 0.5f * sin(2.0f * M_PI * (t + 1.0f / 3.0f));
      float blue = 0.5f * sin(2.0f * M_PI * (t + 2.0f / 3.0f));
      glColor3f(red, green, blue);
      glVertex3dv(arr[i]);
    }
    glEnd();
}

/*
 * Convenience function for text
 */
#define LEN 8192  //  Maximum amount of text
void Print(const char* format , ...)
{
   char    buf[LEN]; // Text storage
   char*   ch=buf;   // Text pointer
   //  Create text to be display
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display text string
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   double asp = (height>0) ? (double)width/height : 1;
   double dim = 50;   // Dimension of orthogonal box
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}


// Create the points for the Lorenz Attractor
void createLorenzPoints(){
    /*  Coordinates  */
    double x = 1;
    double y = 1;
    double z = 1;

    /*  Time step  */
    double dt = 0.001;

    // printf("%5d %8.3f %8.3f %8.3f\n",0,x,y,z);
    /*
    *  Integrate 50,000 steps (50 time units with dt = 0.001)
    *  Explicit Euler integration
    */
    for (int i=0; i < 50000; i++){
      double dx = s*(y-x);
      double dy = x*(r-z)-y;
      double dz = x*y - b*z;
      x += dt*dx;
      y += dt*dy;
      z += dt*dz;

      // Bulid the array of points
      arr[i][0] = x;
      arr[i][1] = y;
      arr[i][2] = z;
    }
}


int main(int argc, char* argv[]){
    //  Initialize GLUT and process user parameters
    glutInit(&argc,argv);
    //  Request double buffered, true color window 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    //  Request 1000 x 1000 pixel window
    glutInitWindowSize(1000,1000);
    // Create window
    glutCreateWindow("Assignment 1: Khaled Hossain");

    createLorenzPoints();

    #ifdef USEGLEW
      //  Initialize GLEW
      if (glewInit()!=GLEW_OK) return 0;
    #endif


    // Callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);  
    glutIdleFunc(idle);
    glutSpecialFunc(special); 
    glutKeyboardFunc(key);

    //  Pass control to GLUT for events
    glutMainLoop();

    return 0;
}