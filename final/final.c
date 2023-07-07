/*
 *  Khaled Hossain
 *  Homework 3: Lighting and Textures
 *
 *  Demonstrates using lighting and textures.
 *
 *  Key bindings:
 *  l          Toggle lighting on/off
 *  t          Change textures
 *  m          Toggles texture mode modulate/replace
 *  a/A        decrease/increase ambient light
 *  d/D        decrease/increase diffuse light
 *  s/S        decrease/increase specular light
 *  e/E        decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  []         Lower/rise light
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
int mode=0;       //  Texture mode
int ntex=0;       //  Cube faces
int axes=1;       //  Display axes
int th=180;         //  Azimuth of view angle
int ph=50;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=20.5;   //  Size of world
int roof = 1;     //  Roof 
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;  // Light azimuth
int carSpeed  =  10;  // Car speed
float ylight  =   3;  // Elevation of light
unsigned int texture[20]; // Texture names
int pattern = 0; // House patterns
double roomWidth = 10;
double roomHeight = 6.0;
int t_mode = 0;	
int obj=0;
double groundWidth = 16.0;
double groundLength = 9.0;
float time=0;  // Elapsed time
int levelmax = 9; // maximum level of recursion
int nleaf = 2; // number of leafs per branch
float openness = 4.5; // controls how open the leafs are
float factor = 1.5; // controls how fast branch sizes decrease
float zoom = 1; // zoom of visualization
float offset = 0; // controls how crooked branches are   
int    sky[2];   //  Sky textures
int objList;     // Object display list
float RGBA[4] = {1,1,1,1};  //  Colors
float xpos = 0, ypos = -20, zpos = -30, xRotation = 1, yRotation = 1;
int fov=45;   
int night = 1;

void Lcounter(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{

   glPushMatrix();
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glColor3f(0.5f,0.35f,0.05f);
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   //left countertop side
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,1);glVertex3f(-3, 0, 0);
   glTexCoord2f(1,1);glVertex3f(-3,0,1);
   glTexCoord2f(1,0);glVertex3f(-3,-0.16,1);
   glTexCoord2f(0,0);glVertex3f(-3,-0.16,0);
   glEnd();
   //  Front
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,1);glVertex3f(-3,0,+1);
   glTexCoord2f(1,1);glVertex3f(+1.5,0,+1);
   glTexCoord2f(1,0);glVertex3f(+1.5,-0.16,+1);
   glTexCoord2f(0,0);glVertex3f(-3,-0.16,+1);
   glEnd();
   //Bottom
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f(0, -1, 0);
   glTexCoord2f(0,1);glVertex3f(-3,-0.16,+1);
   glTexCoord2f(1,1);glVertex3f(+1.5,-0.16,+1);
   glTexCoord2f(1,0);glVertex3f(+1.5,-0.16,-1);
   glTexCoord2f(0,0);glVertex3f(-3,-0.16,-1);
   glEnd();

   //  Offset, scale and rotate
   glScaled(dx,dy,dz); //don't want to scale above

   //  Front
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,1);glVertex3f(-3,0,0);
   glTexCoord2f(1,1);glVertex3f(+1.5,0,0);
   glTexCoord2f(1,0);glVertex3f(+1.5,-0.16,0);
   glTexCoord2f(0,0);glVertex3f(-3,-0.16,0);
   glEnd();

   //  Right
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f(1/sqrt(2), 0, 1/sqrt(2));
   glTexCoord2f(0,1);glVertex3f(+1.5,0,0);
   glTexCoord2f(1,1);glVertex3f(+4,0,-3);
   glTexCoord2f(1,0);glVertex3f(+4,-0.16,-3);
   glTexCoord2f(0,0);glVertex3f(+1.5,-0.16,0);
   glEnd();

    //  Left
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f(-1,0,0);
   glTexCoord2f(0,1);glVertex3f(-3, 0, -1);
   glTexCoord2f(1,1);glVertex3f(-3,0,0);
   glTexCoord2f(1,0);glVertex3f(-3,-0.16,0);
   glTexCoord2f(0,0);glVertex3f(-3,-0.16,-1);
   glEnd();

   //  Top
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);
   glNormal3f(0, 1, 0);
   glTexCoord2f(0,0);glVertex3f(-3,0,+1);//bottom left
   glTexCoord2f(1,1);glVertex3f(+1.5,0,+1);//bottom right
   glTexCoord2f(1,0);glVertex3f(+3,0,-1);//top left
   glTexCoord2f(0,1);glVertex3f(-3,0,-1);//top left
   glEnd();

   //parallelogram
   //top
   glBegin(GL_QUADS);
   glColor3f(0.5f, 0.35f, 0.05f);//brown
   glNormal3f(0,1,0);
   glTexCoord2f(0,0);glVertex3f(+1,0,-1);
   glTexCoord2f(1,0);glVertex3f(+3,0,-1);
   glTexCoord2f(1,1);glVertex3f(+4.5,0,-3);
   glTexCoord2f(0,1);glVertex3f(+2.5,0,-3);
   glEnd();
   //glDisable(GL_TEXTURE_2D);
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   //  Undo transformations and textures
   glPopMatrix();
   glFlush();    
   glDisable(GL_TEXTURE_2D);

}

void cylinder(float radius,float height,
                   float R, float G,float B, unsigned int texture){

   float x, y, angle  = 0.0;
   float angle_stepsize = 0.1;

   //  Enable textures
   //  Select texture if textures are on
   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glColor3ub(R-40,G-40,B-40);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUAD_STRIP);
   angle = 0.0;

   while( angle < 40) {
      x = radius * cos(angle);
      y = radius * sin(angle);
      const float tc = ( angle / (float)( 2 * M_PI ) );
      glTexCoord2f(tc, 1.0); glVertex3f(x, y , height);
      glTexCoord2f(tc, 0.0); glVertex3f(x, y , 0.0);
      angle = angle + angle_stepsize;
      glNormal3f(Cos(angle), 0, -Sin(angle));   
      glTexCoord2f(0.0, 1.0); glVertex3f(radius, 0.0, height);
      glTexCoord2f(0.0, 0.0); glVertex3f(radius, 0.0, 0.0);
   }
   glEnd(); 
   glFlush(); 
   glDisable(GL_TEXTURE_2D);
}


void carTop(double x, double y, unsigned int texture){
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
   //car top
   glPushMatrix();
   glBegin(GL_QUADS);
   glColor3f(1,0.5,0);
   glNormal3f(0.0, 1, 0); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,0,30);
   glNormal3f(0.0, 1, 0); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,0,30);//right low
   glColor3f(1,0,0);
   glNormal3f(0.0, 1, 0); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,30,30);//right top
   glNormal3f(0.0, 1, 0); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,30,30);
   glEnd();

   // between top and front glass
   glBegin(GL_QUADS);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,30,30);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,30,30);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,32,28);//right top
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,32,28);
   glEnd();

   // between front and back glass
   glBegin(GL_QUADS);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,0,30);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,-3,27);

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x,-3,27);//rihgt low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x,0,30);//right top
   glEnd();

   glBegin(GL_QUADS);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,-3,27);//rihgt low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,0,30);//right top

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x,0,30);//right top
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x,-3,27);//rihgt low

   glEnd();      
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void frontBackGlass(double x, double y, unsigned int texture){
      float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
      glPushMatrix();
   // front glass

   glBegin(GL_QUADS);
   glColor3f(0.502, 0.502, 0.502);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x - 7.5,32,28);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,32,28);//right low
   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+11.5,40,20);//right top
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-11.5,40,20);
   glEnd();

   // back glass
   glBegin(GL_QUADS);
   glColor3f(0.502, 0.502, 0.502);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,-3,27);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,-3,27);//right top
   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+10.5,-9,20);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-10.5,-9,20);
   glEnd();
      glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void topLeftFrame(double x, double y, unsigned int texture){
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
   glPushMatrix();
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(1,0,0);
   //front glass
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(1,1);glVertex3f(x-11.5,40,20);//front right top
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,32,28);//front right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,30,30);//between right low
   //middle of front glass and top base
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,30,28);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,40,20);
   glEnd();

   //base line
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(1,0,0);
   //front glass

   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,30,30);//between right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,0,30);//base right low

   glColor3f(1,0,0);
   //middle of front glass and top base
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7,0,28);//base right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7,30,28);//right low
   glEnd();

   // back glass side
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,0,30);//base right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,-3,27);//rihgt low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-10.5,-9,20);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,-9,20);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7,0,28);//base right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-7.5,0,30);//base right low

   glEnd();


   //horizontal border back glass to front glass
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,-9,20);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-9,18);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,40,18);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,40,20);//
   //front right top

   glEnd();
      glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void topRightFrame(double x,double y, unsigned int texture){
      float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
      glPushMatrix();
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(1,0,0);
   //front glass
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+11.5,40,20);//front right top
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,32,28);//front right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,30,30);//between right low
   //middle of front glass and top base
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,30,28);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,40,20);
   glEnd();

   //base line
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(1,0,0);
   //front glass

   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,30,30);//between right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,0,30);//base right low

   glColor3f(1,0,0);
   //middle of front glass and top base
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,0,28);//base right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,30,28);//right low
   glEnd();

   // back glass side
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,0,30);//base right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,-3,27);//rihgt low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+10.5,-9,20);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,-9,20);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,0,28);//base right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+7.5,0,30);//base right low

   glEnd();


   //horizontal border back glass to front glass
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,-9,20);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-9,18);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,40,18);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,40,20);//
   //front right top

   glEnd();
      glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}


void rightSideWindow(double x, double y, unsigned int texture){  
      float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);       

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);    
      glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(0.502, 0.502, 0.502);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,40,20);//

   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,30,28);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,30,20);//
      //front right top
   glEnd();
   glBegin(GL_POLYGON);
   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,30,28);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,30,20);//

   glColor3f(0.502, 0.502, 0.502);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,18,20);//
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,17.5,28);//right low
   glEnd();

   //right side middle window
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(0.502, 0.502, 0.502);

   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8, 16.5  , 28);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5  , 16.5  , 20);//

   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,1,20);//
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,1.5,28);//right low
   glEnd();

   //right side back window
   glBegin(GL_POLYGON);
   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,0,20);//
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,0.9,28);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,0,28);

   glColor3f(0.502, 0.502, 0.502);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,-9,20);//right low
   glEnd();
   glPopMatrix();
   glDisable(GL_BLEND); 
   glDisable(GL_TEXTURE_2D);
}


void leftSideWindow(double x, double y, unsigned int texture){
      float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
      glPushMatrix();
   //right side front galass window/////////////////////////////////////////////////////////////////////////////////
   glBegin(GL_POLYGON);
   glColor3f(0.502, 0.502, 0.502);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,40,20);//

   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,30,28);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,30,20);//
      //front right top
   glEnd();
   glBegin(GL_POLYGON);
   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,30,28);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,30,20);//

   glColor3f(0.502, 0.502, 0.502);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,18,20);//
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,17.5,28);//right low
   glEnd();

   //right side middle window
   glBegin(GL_POLYGON);
   /* Set the vertices */
   glColor3f(0.502, 0.502, 0.502);

   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8, 16.5  , 28);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5  , 16.5  , 20);//

   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,1,20);//
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,1.5,28);//right low
   glEnd();

   //right side back window
   glBegin(GL_POLYGON);
   glColor3f(0.961, 0.961, 0.961);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,0,20);//
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,0.9,28);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,0,28);

   glColor3f(0.502, 0.502, 0.502);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,-9,20);//right low
   glEnd();
   glPopMatrix();
   glDisable(GL_BLEND); 
   glDisable(GL_TEXTURE_2D);
}


void rightSideWindowDivider(double x, double y, unsigned int texture){
      float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
      glPushMatrix();
   //glass devider one
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,17.5,28);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8, 16.5  , 28);

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5 , 16.5  , 20);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,18,20);
   //right low
   glEnd();

   //glass devider two
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,0.9,28);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+8,1.5,28);

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,1,20);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,0,20);
   glEnd();
      glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void leftSideWindowDivider(double x, double y, unsigned int texture){
      float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
      glPushMatrix();
      //glass devider one
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,17.5,28);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8, 16.5  , 28);

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5  , 16.5  , 20);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,18,20);
         //right low
   glEnd();

   //glass devider two
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,0.9,28);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-8,1.5,28);

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,1,20);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,0,20);
   glEnd();
      glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void backSideBody(double x,double y, unsigned int texture){
      float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
      glPushMatrix();
   //back side of back glass
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,-9,20);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,-9,20);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-9,18);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-9,18);//right low
   glEnd();

   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-9,18);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-9,18);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-10,15);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-10,15);//right low
   glEnd();

   // red light left
   glBegin(GL_POLYGON);
   glColor3f(0.647, 0.165, 0.165);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-9,-10,15);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-10,15);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-10.2,11.2);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-9,-10.2,11.2);//right low
   glEnd();

   // red light right
   glBegin(GL_POLYGON);
   glColor3f(0.647, 0.165, 0.165);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+9,-10,15);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-10,15);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-10.2,11.2);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+9,-10.2,11.2);//right low
   glEnd();



   //number board
   glBegin(GL_QUADS);
   glColor3f(x-6.998, 0.502, 0.502);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-4, -10.04, 15);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+4, -10.04, 15);//right low

   glColor3f(x-6.502, 0.910, 0.667);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+4, -10.24, 11.2);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-4, -10.24, 11.2);//right low

   glEnd();
   // place between two lines
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+9,-10,15);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-9,-10,15);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-9,-10.2,11.2);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+9,-10.2,11.2);//right low

   glEnd();

   //last part of back side
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-10.2,11.2);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-10.2,11.2);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-10.5,7);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+15,-10.5,7);//right low

   glEnd();
      glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void frontBody(double x, double y, unsigned int texture)
{
      float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
      glPushMatrix();
    //between front and front glass
      glBegin(GL_POLYGON);
      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,40,20);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,40,20);//right low

      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-14.5,40,18);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+14.5,40,18);//right low
      glEnd();
        //front hood
      glBegin(GL_POLYGON);
      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-14.5,40,18);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+14.5,40,18);//right low

      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,52,15);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,52,15);//right low
      glEnd();
        //small curv after front hood
      glBegin(GL_POLYGON);
      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,52,15);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,52,15);//right low

      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,53,12);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,53,12);//right low
      glEnd();
        //front end
      glBegin(GL_POLYGON);
      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,53,12);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,53,12);//right low

      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,54,7);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,54,7);//right low
      glEnd();

       //front right
      glBegin(GL_POLYGON);
      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,54,7);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,53,12);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,52,15);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+14.5,40,18);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x+13.5,40,7);//right low
      glEnd();

       //front left
      glBegin(GL_POLYGON);
      glColor3f(1,0,0);
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,54,7);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,53,12);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,52,15);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-14.5,40,18);//right low
      glNormal3f(1,1,1); // Normal vector for lighting
      glTexCoord2f(0,1);glVertex3f(x-13.5,40,7);//right low
      glEnd();
         glPopMatrix();
      glDisable(GL_TEXTURE_2D);

}

void carDoors(double x, double y, unsigned int texture){

   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   
      glPushMatrix();

   //doors right
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(-1,0,0); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,40,18);//right low
   glColor3f(1,0,0);   
   glTexCoord2f(0,1);glVertex3f(x+14.5,10,18);//right low


   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,10,7);//right low   
   glTexCoord2f(0,1);glVertex3f(x+13.5,40,7);//right low

   glEnd();
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,10,18);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-9,18);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-10,15);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+14.5,-10.2,11.2);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+15, -10.5, 7);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x+13.5,10,7);//right low

   glEnd();

   //doors left
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,0,0); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,40,18);//right low
   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,10,18);//right low


   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,10,7);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,40,7);//right low

   glEnd();
   glBegin(GL_POLYGON);
   glColor3f(1,0,0);
   glNormal3f(1,0,0); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,10,18);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-9,18);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-10,15);//right low

   glColor3f(1,0,0);
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5,-10.2,11.2);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-14.5, -10.5, 7);//right low
   glNormal3f(1,1,1); // Normal vector for lighting
   glTexCoord2f(0,1);glVertex3f(x-13.5,10,7);//right low

   glEnd();
      glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}
// code taken from here https://github.com/saiminajagi/3D-car-animation-in-OpenGL/blob/master/carfinal.cpp
void drawCar(double x, double y){
   // top
   glPushMatrix();
   carTop(x,y, texture[4]);
   frontBackGlass(x,y, texture[4]);
   
   // right side 
   topRightFrame(x,y, texture[4]);
   rightSideWindow(x,y, texture[4]);
   rightSideWindowDivider(x,y, texture[4]);

   // left side
   topLeftFrame(x,y, texture[4]);
   leftSideWindow(x,y, texture[4]);
   leftSideWindowDivider(x,y, texture[4]);

   // back side
   backSideBody(x,y, texture[4]);
   frontBody(x,y, texture[4]);

   // doors
   carDoors(x,y, texture[4]);
   glFlush();    
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();

   // wheels
   glPushMatrix();
   glTranslated(-16,0, 9.5);
   // rotate horizontally
   glRotated(90,0,1,0);
   glScaled(4,4,11);      
   cylinder(1.5,3, 0, 0, 0, texture[14]);
   glPopMatrix();

   // wheels
   glPushMatrix();
   glTranslated(-16,40, 9.5);
   // rotate horizontally
   glRotated(90,0,1,0);
   glScaled(4,4,11);      
   cylinder(1.5,3, 0, 0, 0, texture[14]);
   glPopMatrix();
}


/*
 *  Set projection
 */
static void myProject(int mode, double fov,double asp,double dim)
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);

   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode == 0)
      gluPerspective(fov,asp,dim/16,16*dim);
   // First person
   else if (mode == 1) {
      gluPerspective(fov, asp, dim/16, th);
   }
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}



/* 
 *  Draw sky box
 */
static void Sky(double D)
{
   //  Textured white box dimension (-D,+D)
   glPushMatrix();
   glScaled(D,D,D);
   glEnable(GL_TEXTURE_2D);
   glColor3f(1,1,1);

   //  Sides
   glBindTexture(GL_TEXTURE_2D,sky[0]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.00,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(0.25,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(0.25,1); glVertex3f(+1,+1,-1);
   glTexCoord2f(0.00,1); glVertex3f(-1,+1,-1);

   glTexCoord2f(0.25,0); glVertex3f(+1,-1,-1);
   glTexCoord2f(0.50,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(0.50,1); glVertex3f(+1,+1,+1);
   glTexCoord2f(0.25,1); glVertex3f(+1,+1,-1);

   glTexCoord2f(0.50,0); glVertex3f(+1,-1,+1);
   glTexCoord2f(0.75,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(0.75,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0.50,1); glVertex3f(+1,+1,+1);

   glTexCoord2f(0.75,0); glVertex3f(-1,-1,+1);
   glTexCoord2f(1.00,0); glVertex3f(-1,-1,-1);
   glTexCoord2f(1.00,1); glVertex3f(-1,+1,-1);
   glTexCoord2f(0.75,1); glVertex3f(-1,+1,+1);
   glEnd();

   //  Top and bottom
   glBindTexture(GL_TEXTURE_2D,sky[1]);
   glBegin(GL_QUADS);
   glTexCoord2f(0.0,0); glVertex3f(+1,+1,-1);
   glTexCoord2f(0.5,0); glVertex3f(+1,+1,+1);
   glTexCoord2f(0.5,1); glVertex3f(-1,+1,+1);
   glTexCoord2f(0.0,1); glVertex3f(-1,+1,-1);
   glEnd();

   //  Undo
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}

void drawSeat() {
   //  Offset, scale and rotate

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[3]);

   // Seat Top
   glPushMatrix();
   glTranslated(0,1,0);
   glRotated(-90.0,1,0,0);
   cylinder(0.75, 0.25, 1,0,0, texture[3]);
   glPopMatrix();  
   
   // Seat Bottom
   glPushMatrix();
   glTranslated(0,0,0);
   glRotated(-90.0,1,0,0);
   cylinder(0.25, 1.0, 1,0,0, texture[4]);
   glPopMatrix();  

   glFlush();    
   glDisable(GL_TEXTURE_2D);

}

void drawCone(double height, double radius, double r, double g, double b, unsigned int texture)
{
   int k = 0;
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 
    
    //  Enable textures
    //  Select texture if textures are on
    if (ntex<0)
       glDisable(GL_TEXTURE_2D);
    else
    {
       glEnable(GL_TEXTURE_2D);
    }

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture);
    if (ntex) glBindTexture(GL_TEXTURE_2D,texture);

    glColor3f(r,g,b);
    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(0.5, 0.5); glVertex3f(0,0,height);
    for (k=0;k<=360;k+=5){  

      glNormal3f(Cos(k),Sin(k), 0);   
      glTexCoord2f(rep/2*Cos(k)+0.5,rep/2*Sin(k)+0.5);
      glVertex2f(Cos(k),Sin(k));
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawLamp() {
   //  Offset, scale and rotate

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[3]);


   glPushMatrix();
   glTranslated(0,0.5,0);
   glRotated(-90.0,1,0,0);
   glScaled(0.75,0.45,1);
   drawCone(1, 1, 1, 1, 1, texture[3]);
   glPopMatrix();
      
   glPushMatrix();
   glTranslated(0,0,0);
   glRotated(-90.0,1,0,0);
   cylinder(0.25, 0.65, 1, 1, 1, texture[4]);
   glPopMatrix();  

   glFlush();    
   glDisable(GL_TEXTURE_2D);

}


/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, double r, double g, double b,
		 unsigned int texture, int top, int bottom, int front, int back, int left, int right)
{
   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 
   //  Save transformation
   glPushMatrix();

   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);

   //  Enable textures
   //  Select texture if textures are on
   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glColor3f(r,g,b);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);
   //  Front
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);

   if(front == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1, 1);
      glTexCoord2f(rep, 0.0); glVertex3f(+1,-1, 1);
      glTexCoord2f(rep, rep); glVertex3f(+1,+1, 1);
      glTexCoord2f(0.0, rep); glVertex3f(-1,+1, 1);      
   }
   else{
      glVertex3f(-1,-1, 1);
      glVertex3f(+1,-1, 1);
      glVertex3f(+1,+1, 1);
      glVertex3f(-1,+1, 1);
   }
   glEnd();

   //  Back
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   if(back == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep, 0.0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep, rep); glVertex3f(-1,+1,-1);
      glTexCoord2f(0.0, rep); glVertex3f(+1,+1,-1);
   }

   else{
      glVertex3f(+1,-1,-1);
      glVertex3f(-1,-1,-1);
      glVertex3f(-1,+1,-1);
      glVertex3f(+1,+1,-1);
   }
   glEnd();

   //  Right
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);

   if(right == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(+1,-1,+1);
      glTexCoord2f(rep, 0.0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep, rep); glVertex3f(+1,+1,-1);
      glTexCoord2f(0.0, rep); glVertex3f(+1,+1,+1);
   }
   else{
      glVertex3f(+1,-1,+1);
      glVertex3f(+1,-1,-1);
      glVertex3f(+1,+1,-1);
      glVertex3f(+1,+1,+1);
   }
   glEnd();

   //  Left
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);

   if(left == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep, 0.0); glVertex3f(-1,-1,+1);
      glTexCoord2f(rep, rep); glVertex3f(-1,+1,+1);
      glTexCoord2f(0.0, rep); glVertex3f(-1,+1,-1);
   }
   else{
      glVertex3f(-1,-1,-1);
      glVertex3f(-1,-1,+1);
      glVertex3f(-1,+1,+1);
      glVertex3f(-1,+1,-1);
   }
   glEnd();

   //  Top
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);

   if(top == 1){
   glTexCoord2f(0.0, 0.0); glVertex3f(-1,+1,+1);
   glTexCoord2f(rep, 0.0); glVertex3f(+1,+1,+1);
   glTexCoord2f(rep, rep); glVertex3f(+1,+1,-1);
   glTexCoord2f(0.0, rep); glVertex3f(-1,+1,-1);
   }

   else{
      glVertex3f(-1,+1,+1);
      glVertex3f(+1,+1,+1);
      glVertex3f(+1,+1,-1);
      glVertex3f(-1,+1,-1);
   }
   glEnd();

   //  Bottom
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture);
   glBegin(GL_QUADS);
   glNormal3f( 0,-1, 0);

   if(bottom == 1){
      glTexCoord2f(0.0, 0.0); glVertex3f(-1,-1,-1);
      glTexCoord2f(rep, 0.0); glVertex3f(+1,-1,-1);
      glTexCoord2f(rep, rep); glVertex3f(+1,-1,+1);
      glTexCoord2f(0.0, rep); glVertex3f(-1,-1,+1);
   }

   else{
      glVertex3f(-1,-1,-1);
      glVertex3f(+1,-1,-1);
      glVertex3f(+1,-1,+1);
      glVertex3f(-1,-1,+1);
   }
   glEnd();

   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void drawChair(float r, float g, float b)
{
   
   double length = 1.0;
   //legs
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(length/2,0.9,-length/2, 0.04, 0.9, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-length/2,0.9,-length/2, 0.04, 0.9, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(-length/2+(0.075/1.9),0.9/2,length/2-(0.075/1.9), 0.04, 0.9/2, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(length/2-(0.075/1.9),0.9/2,length/2-(0.075/1.9), 0.04, 0.9/2, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //base
   double thickness = 0.2;
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,0.9,0,  length/2,thickness/2 , length/2, 0, r, g, b, texture[5], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   //back support - horizontal
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(2*0.9)-(0.04),-length/2, length/2, 0.04, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(1.85*0.9)-(0.04),-length/2, length/2, 0.04, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,(1.2*0.9)-(0.04),-length/2, length/2, 0.04, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

}


void drawTable(float r, float g, float b)
{
   double length = 3.0;
   double width = 1.5;


   //table top
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0,roomWidth/5,0, length/2,0.025, width/2, 0, r, g, b, texture[3], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   // table legs
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0.75, 1, 0.7, 0.04, 1, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1);
   cube(0.75, 1, -0.7, 0.04, 1, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1); 
   cube(-0.75, 1, -0.7, 0.04, 1, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);
   glDisable(GL_POLYGON_OFFSET_FILL);

   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1,1); 
   cube(-0.75, 1, 0.7, 0.04, 1, 0.04, 0, r, g, b, texture[4], 1,1,1,1,1,1);  
   glDisable(GL_POLYGON_OFFSET_FILL);
}


void drawGrass(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th) {      
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);   
   //  Enable textures
   //  Select texture if textures are on
   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }
   
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[1]);					
   glBegin(GL_QUADS);
   glNormal3f( 0, 1, 0);

   glTexCoord2f(0.0,0.0); 	glVertex3f(-groundWidth/2,0.0,roomHeight);
   glTexCoord2f(3,0.0); 	glVertex3f(-groundWidth/2,0.0,-groundLength);
   glTexCoord2f(3,3); 	glVertex3f(groundWidth/2,0.0,-groundLength);
   glTexCoord2f(0.0,3); 	glVertex3f(groundWidth/2,0.0,roomHeight);
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw vertex in polar coordinates
 */
void Vertex(double th,double ph, double rgb)
{
   //glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
   glColor3f(rgb, rgb, rgb);
   glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}

/*
 *  Draw a bathtub
 *     at (x,y,z)
 *     radius (r)
 */
static void bathtub(double x,double y,double z,double r)
{
   //  Set specular color to white
  float white[] = {1,1,1,1};
  float Emission[]  = {0.0,0.0,0.01*emission,1.0};
  double X=1;    //  Top Right X
  double Y=1;    //  Top Right Y
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

  const int d=5;
  int th,ph;

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , mode?GL_REPLACE:GL_MODULATE);
      glBindTexture(GL_TEXTURE_2D,texture[8]);
   }
   
   glPushMatrix();
   glRotatef(90, 90, 1.0, 0.0);
   glBegin(GL_TRIANGLE_FAN);
   glTexCoord2f(1,1); glVertex3f(0,0,0);
   for (int k=0;k<=360;k+=10)
   {
      glTexCoord2f(2/2*Cos(k)+0.5,rep/2*Sin(k)+0.5);
      glVertex2f(X*Cos(k),Y*Sin(k));
   }
   glEnd();
   glPopMatrix();

  //  Save transformation
  glPushMatrix();
  //  Offset and scale
  glTranslated(x,y,z);
  glScaled(r,r,r);

   glRotatef(180.0, 180, 1.0, 0.0);

  //  Latitude bands
  for (ph=0;ph<90;ph+=d) {
    glBegin(GL_QUAD_STRIP);
    for (th=0;th<=360;th+=d)
    {
     glTexCoord2f(1  ,1); Vertex(th,ph, 1);
     glTexCoord2f(2  ,0.0); Vertex(th,ph+d, 1);
    }
    glEnd();
  }

  //  Undo transformations
  glPopMatrix();

   glPushMatrix();
   glTranslated(0, -0.9, 0);   
   glScaled(1,0.8,1);
   cube(0,0,0, 1, 1, 1, 1, 1, 1, 1, texture[4], 1,1,1,1,1,1);
   glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}


void drawWindow()
{
   // L
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 0.5);
      
   glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/2,0.0,-groundLength); // a
   glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/2,roomWidth/2,-groundLength); // b
   glTexCoord2f(rep, rep);	glVertex3f(-6,roomWidth/2,-groundLength); // c
   glTexCoord2f(0.0, rep);	glVertex3f(-6,0.0,-groundLength); // d
   glEnd();

   // T
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   
   glTexCoord2f(0.0, 0.0);	glVertex3f(-6,3,-groundLength); // a
   glTexCoord2f(rep, 0.0);	glVertex3f(-6,roomWidth/2,-groundLength); // b
   glTexCoord2f(rep, rep);	glVertex3f(-4,roomWidth/2,-groundLength); // c
   glTexCoord2f(0.0, rep);	glVertex3f(-4,3,-groundLength); // d
   glEnd();

   // R
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   
   glTexCoord2f(0.0, 0.0);	glVertex3f(-5,0,-groundLength); // a
   glTexCoord2f(rep, 0.0);	glVertex3f(-5,roomWidth/2,-groundLength); // b
   glTexCoord2f(rep, rep);	glVertex3f(-4,roomWidth/2,-groundLength); // c
   glTexCoord2f(0.0, rep);	glVertex3f(-4,0,-groundLength); // d
   glEnd();

   // B
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   
   glTexCoord2f(0.0, 0.0);	glVertex3f(-6,0,-groundLength); // a
   glTexCoord2f(rep, 0.0);	glVertex3f(-6,1,-groundLength); // b
   glTexCoord2f(rep, rep);	glVertex3f(-5,1,-groundLength); // c
   glTexCoord2f(0.0, rep);	glVertex3f(-4,0,-groundLength); // d
   glEnd();

   // window
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);

   glColor3f(0.778, 0.947, 1);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[0]);	
   glBegin(GL_QUADS);
   glNormal3f( 1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-6,1.0,-groundLength);
   glTexCoord2f(rep, 0.0);	glVertex3f(-6,3,-groundLength);
   glTexCoord2f(rep, rep);	glVertex3f(-5,3,-groundLength);
   glTexCoord2f(0.0, rep);	glVertex3f(-5,1,-groundLength);
   glEnd(); 
   glDisable(GL_BLEND); 
}

void drawVase(double x, double y, double z, double r, double emi, double sc, double rh){
   
   int th,ph;   

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }
   // glColor3f(0.778, 0.947, 1);
   glBindTexture(GL_TEXTURE_2D,texture[12]);	

    // Draw body    

    glPushMatrix();
    glTranslated(x,y+Sin(rh),z);
    glScaled(sc,2*sc,sc);

    glColor3f(0,0,0);

    for (ph=-90;ph<90;ph+=5)
    {
        glBegin(GL_QUAD_STRIP);
         glNormal3f(0,0,1); 
        for (th=0;th<=360;th+=2*5)
        {
            Vertex(th,ph,(r-1.5));
            Vertex(th,ph+5,(r-1.5));
        }
        glEnd();
    }
    glPopMatrix();

   // top stem
   glPushMatrix();
   glTranslated(0,0,0);
   glRotated(-90.0,1,0,0);   
   cylinder(0.5,3, 0, 0, 0, texture[12]);
   glPopMatrix();

   // top top
   glPushMatrix();
   glTranslated(0, 3,0);
   glRotated(-90.0,1,0,0);   
   cylinder(0.75,0.8, 0, 0, 0, texture[12]);
   glPopMatrix();
   
   // bottom
   glPushMatrix();
   glTranslated(0,-2,0);
   glRotated(-90.0,1,0,0);   
   cylinder(0.75,1, 0, 0, 0, texture[12]);
   glPopMatrix();

   glFlush();    
   glDisable(GL_TEXTURE_2D);

}
void drawRoof(unsigned int texture) {

   float yellow[] = {1.0,1.0,0.0,1.0};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0}; 
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission); 

   if (ntex<0)
      glDisable(GL_TEXTURE_2D);
   else
   {
      glEnable(GL_TEXTURE_2D);
   }

   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture);   

   glPushMatrix();
    glBegin(GL_TRIANGLES);

    // Front face
    glNormal3f(1,1,1); // Normal vector for lighting
    glTexCoord2f(0.5f, 1.0f); // Texture coordinates for top vertex
    glVertex3f(0.0f, 1.0f, 0.0f);

    glNormal3f(-0.577f, -0.577f, 0.577f); // Normal vector for lighting
    glTexCoord2f(0.0f, 0.0f); // Texture coordinates for front left vertex
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glNormal3f(0.577f, -0.577f, 0.577f); // Normal vector for lighting
    glTexCoord2f(1.0f, 0.0f); // Texture coordinates for front right vertex
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Back face
    glNormal3f(0.0f, 0.447f, -0.894f); // Normal vector for lighting
    glTexCoord2f(0.5f, 1.0f); // Texture coordinates for top vertex
    glVertex3f(0.0f, 1.0f, 0.0f);

    glNormal3f(0.577f, -0.577f, -0.577f); // Normal vector for lighting
    glTexCoord2f(0.0f, 0.0f); // Texture coordinates for back right vertex
    glVertex3f(1.0f, -1.0f, -1.0f);

    glNormal3f(-0.577f, -0.577f, -0.577f); // Normal vector for lighting
    glTexCoord2f(1.0f, 0.0f); // Texture coordinates for back left vertex
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Left face
    glNormal3f(-0.894f, 0.447f, 0.0f); // Normal vector for lighting
    glTexCoord2f(0.5f, 1.0f); // Texture coordinates for top vertex
    glVertex3f(0.0f, 1.0f, 0.0f);

    glNormal3f(-0.577f, -0.577f, -0.577f); // Normal vector for lighting
    glTexCoord2f(0.0f, 0.0f); // Texture coordinates for back left vertex
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glNormal3f(-0.577f, -0.577f, 0.577f); // Normal vector for lighting
    glTexCoord2f(1.0f, 0.0f); // Texture coordinates for front left vertex
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face
    glNormal3f(0.894f, 0.447f, 0.0f); // Normal vector forlighting
    glTexCoord2f(0.5f, 1.0f); // Texture coordinates for top vertex
    glVertex3f(0.0f, 1.0f, 0.0f);

    glNormal3f(0.577f, -0.577f, 0.577f); // Normal vector for lighting
    glTexCoord2f(0.0f, 0.0f); // Texture coordinates for front right vertex
    glVertex3f(1.0f, -1.0f, 1.0f);

    glNormal3f(0.577f, -0.577f, -0.577f); // Normal vector for lighting
    glTexCoord2f(1.0f, 0.0f); // Texture coordinates for back right vertex
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f); // Normal vector for lighting
    glTexCoord2f(0.0f, 0.0f); // Texture coordinates for back left vertex
    glVertex3f(-1.0f, -1.0f, -1.0f);

    glNormal3f(0.0f, -1.0f, 0.0f); // Normal vector for lighting
    glTexCoord2f(1.0f, 0.0f); // Texture coordinates for back right vertex
    glVertex3f(1.0f, -1.0f, -1.0f);

    glNormal3f(0.0f, -1.0f, 0.0f); // Normal vector for lighting
    glTexCoord2f(0.5f, 1.0f); // Texture coordinates for top vertex
    glVertex3f(0.0f, -1.0f, 1.0f);

   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
 *  Draws the house
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
void drawHouse(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, unsigned int houseTexture, int housePattern)
{

   if (housePattern == 1) {

   if (roof == 1) {
      glPushMatrix();
      glTranslated(0,roomHeight-2.4, -0.8);
      glScaled(5,1,5);   
      drawRoof(texture[4]);
      glPopMatrix();
   }


      // draw bathtub
      glPushMatrix();
      glTranslated(3.3, 1.08, 1.8);
      glScaled(0.5,0.5,1);   
      bathtub(0,0,0,1);
      glPopMatrix();  

      // draw Lcounter
      glPushMatrix();
      glTranslated(2,1, -3);
      glScaled(0.30,0.45,0.45);      
      glRotatef(264, 0, 1, 0);
      Lcounter(0,0,0,1,10,1,5);
      glPopMatrix();

      // counter seats
      glPushMatrix();
      glTranslated(1.25, 0, -3);
      glScaled(0.35,0.35, 0.35);      
      drawSeat();
      glPopMatrix();

      glPushMatrix();
      glTranslated(1.25, 0, -4);
      glScaled(0.35,0.35, 0.35);      
      drawSeat();
      glPopMatrix();
      
      glPushMatrix();
      glTranslated(1.9, 0, -1.5);
      glScaled(0.35,0.35, 0.35);      
      drawSeat();
      glPopMatrix();

      // draw vase
      glPushMatrix();
      glTranslated(-3.5,1.5, -1);
      glScaled(0.15,0.15,0.15);      
      drawVase(0,0,0,2.5,fmod(120*time,360.0),1,fmod(90*time,360.0));
      glPopMatrix();

      // draw lamps
      glPushMatrix();
      glTranslated(-3.75, 0.5, -2.25);
      glScaled(0.25,0.25,0.25);
      drawLamp();
      glPopMatrix();  

      glPushMatrix();
      glTranslated(-3.75, 0.5, -3.75);
      glScaled(0.25,0.25,0.25);
      drawLamp();
      glPopMatrix();  

      // Draw side tables
      glPushMatrix();
      glTranslated(-3.9, 0.0, -2.5);   
      glScaled(0.25,0.25, 0.25);
      cube(1,1,1, 1, 1, 1, 1, 1, 1, 1, texture[6], 1,1,1,1,1,1);
      glPopMatrix();

      glPushMatrix();
      glTranslated(-3.9, 0.0, -4);   
      glScaled(0.25,0.25, 0.25);
      cube(1,1,1, 1, 1, 1, 1, 1, 1, 1, texture[6], 1,1,1,1,1,1);
      glPopMatrix();

      // draw bed
      glPushMatrix();
      glTranslated(-2.8, 0.0, -3);   
      glRotated(90.0,0,1,0);
      glScaled(0.8, 0.35, 2);
      drawChair(0.523, 0.442, 0.161);
      glPopMatrix();

      // dining table
      glPushMatrix();
      glTranslated(-3.5, 0.0, -1);   
      glRotated(90.0,0,1,0);
      glScaled(0.5, 0.5, 0.5);
      drawTable(0.27,0.027,0.035);
      glPopMatrix();

      // living room table
      glPushMatrix();
      glTranslated(-2.3, 0.0, 2.5);      
      glScaled(0.5, 0.5, 0.45);
      drawTable(0.42, 0.42, 0.42);
      glPopMatrix();

      // draw tv
      glPushMatrix();
      glTranslated(-2.67, 1.35, 2.75);      
      glScaled(0.55,0.25, 0.09);
      cube(1,1,1, 1, 1, 1, 1, 1, 1, 1, texture[7], 1,1,1,1,1,1);
      glPopMatrix();


      // Sofa
      glPushMatrix();
      glTranslated(-2.3, 0.0,1);
      glScaled(1.35, 0.5, 0.5);
      drawChair(0.162, 0.252, 0.291);
      glPopMatrix();


      // desk chair
      glPushMatrix();
      glTranslated(-2.95, 0.0, -1);
      glRotated(270,0,1,0);
      glScaled(0.5, 0.5, 0.5);
      drawChair(0.38, 0.38, 0.38);
      glPopMatrix();


      //  Set specular color to white
      float white[] = {1,1,1,1};
      float Emission[]  = {0.0,0.0,0.01*emission,1.0};
      glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
      glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
      //  Save transformation
      glPushMatrix();
      //  Offset, scale and rotate
      glTranslated(x,y,z);
      glRotated(th,0,1,0);
      glScaled(dx,dy,dz);
      //  Enable textures
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
      glColor3f(0.8,0.8,0.8);
      //  Enable textures
      //  Select texture if textures are on
      if (ntex<0)
      glDisable(GL_TEXTURE_2D);
      else
      {
      glEnable(GL_TEXTURE_2D);
      }

      // draw floor
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[0]);					
      glBegin(GL_QUADS);
      glNormal3f( 0, 1, 0);

      glTexCoord2f(0.0,0.0); 	glVertex3f(-groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep,0.0); 	glVertex3f(-groundWidth/2,0.0,-groundLength);
      glTexCoord2f(rep,rep); 	glVertex3f(groundWidth/2,0.0,-groundLength);
      glTexCoord2f(0.0,rep); 	glVertex3f(groundWidth/2,0.0,roomHeight);
      glEnd();
      glDisable(GL_POLYGON_OFFSET_FILL);

      // Draw left wall
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 1, 0, 0);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(rep, rep);	glVertex3f(-groundWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-groundWidth/2,0.0,-groundLength);
      glEnd(); 


      // mid partitions
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 1, 0, 0);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/8,0.0,-1);
      glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/8,roomWidth/2,-1);
      glTexCoord2f(rep, rep);	glVertex3f(-groundWidth/8,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-groundWidth/8,0.0,-groundLength);
      glEnd(); 

      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, -1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-0.5,0.0,0);
      glTexCoord2f(rep, 0.0);	glVertex3f(-0.5,roomWidth/2,0);
      glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,0);
      glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,0);
      glEnd();  


      // Draw right wall
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( -1, 0, 0);

      glTexCoord2f(0.0, 0.0);	glVertex3f(groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep, 0.0);	glVertex3f(groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,-groundLength);
      glEnd();  

      // Draw back wall  
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, -1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,roomHeight);
      glEnd();  

      // Draw front wall  
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-roomWidth/2,0.0,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(-roomWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(-1,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-1,0.0,-groundLength);
      glEnd();

      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(roomWidth/2,0.0,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(roomWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(1,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(1,0.0,-groundLength);
      glEnd();

      glColor3f(0.9,0.8,0.6);
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);	
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-1,roomWidth/2,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(1,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(1,3.5,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-1,3.5,-groundLength);
      glEnd();

      // Draw window
      drawWindow();

      // Draw front 
      glColor3f(0.9,0.8,0.6);
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);	
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(groundWidth/2,0.0,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(groundWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(roomWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(roomWidth/2,0.0,-groundLength);
      glEnd();

      //  Undo transformations and textures
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
   }
   else if (pattern == 2) {
      // draw bathtub
      glPushMatrix();
      glTranslated(3.3, 1.08, 1.8);
      glScaled(0.5,0.5,1);   
      bathtub(0,0,0,1);
      glPopMatrix();  

      // draw lamps
      glPushMatrix();
      glTranslated(-3.75, 0.5, -2.25);
      glScaled(0.25,0.25,0.25);
      drawLamp();
      glPopMatrix();  

      glPushMatrix();
      glTranslated(-3.75, 0.5, -3.75);
      glScaled(0.35,0.45,0.5);
      drawLamp();
      glPopMatrix();  

      // Draw side tables
      glPushMatrix();
      glTranslated(-3.9, 0.0, -2.5);   
      glScaled(0.25,0.25, 0.25);
      cube(1,1,1, 1, 1, 1, 1, 1, 1, 1, texture[6], 1,1,1,1,1,1);
      glPopMatrix();

      glPushMatrix();
      glTranslated(-3.9, 0.0, -4);   
      glScaled(0.25,0.25, 0.25);
      cube(1,1,1, 1, 1, 1, 1, 1, 1, 1, texture[6], 1,1,1,1,1,1);
      glPopMatrix();

      // draw bed
      glPushMatrix();
      glTranslated(-2.8, 0.0, -3);   
      glRotated(90.0,0,1,0);
      glScaled(0.8, 0.35, 2);
      drawChair(0.523, 0.442, 0.161);
      glPopMatrix();

      // dining table
      glPushMatrix();
      glTranslated(2, 0.0, -2);   
      glRotated(90.0,0,1,0);
      glScaled(0.5, 0.5, 0.5);
      drawTable(0.27,0.027,0.035);
      glPopMatrix();

      // living room table
      glPushMatrix();
      glTranslated(-2.3, 0.0, 2.5);      
      glScaled(0.5, 0.5, 0.45);
      drawTable(0.42, 0.42, 0.42);
      glPopMatrix();

      // draw tv
      glPushMatrix();
      glTranslated(-2.67, 1.35, 2.75);      
      glScaled(0.55,0.25, 0.09);
      cube(1,1,1, 1, 1, 1, 1, 1, 1, 1, texture[7], 1,1,1,1,1,1);
      glPopMatrix();


      // Sofa
      glPushMatrix();
      glTranslated(-2.3, 0.0,1);
      glScaled(1.35, 0.5, 0.5);
      drawChair(0.162, 0.252, 0.291);
      glPopMatrix();

      // chair
      glPushMatrix();
      glTranslated(2, 0.0, -3);
      glScaled(0.5, 0.5, 0.5);
      drawChair(0.38, 0.38, 0.38);
      glPopMatrix();

      // chair
      glPushMatrix();
      glTranslated(2, 0.0, -1);
      glRotated(180,0,1,0);
      glScaled(0.5, 0.5, 0.5);
      drawChair(0.38, 0.38, 0.38);
      glPopMatrix();


      //  Set specular color to white
      float white[] = {1,1,1,1};
      float Emission[]  = {0.0,0.0,0.01*emission,1.0};
      glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
      glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
      //  Save transformation
      glPushMatrix();
      //  Offset, scale and rotate
      glTranslated(x,y,z);
      glRotated(th,0,1,0);
      glScaled(dx,dy,dz);
      //  Enable textures
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
      glColor3f(0.8,0.8,0.8);
      //  Enable textures
      //  Select texture if textures are on
      if (ntex<0)
      glDisable(GL_TEXTURE_2D);
      else
      {
      glEnable(GL_TEXTURE_2D);
      }

      // draw floor
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[0]);					
      glBegin(GL_QUADS);
      glNormal3f( 0, 1, 0);

      glTexCoord2f(0.0,0.0); 	glVertex3f(-groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep,0.0); 	glVertex3f(-groundWidth/2,0.0,-groundLength);
      glTexCoord2f(rep,rep); 	glVertex3f(groundWidth/2,0.0,-groundLength);
      glTexCoord2f(0.0,rep); 	glVertex3f(groundWidth/2,0.0,roomHeight);
      glEnd();
      glDisable(GL_POLYGON_OFFSET_FILL);

      // Draw left wall
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 1, 0, 0);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(rep, rep);	glVertex3f(-groundWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-groundWidth/2,0.0,-groundLength);
      glEnd(); 


      // mid partitions
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 1, 0, 0);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/8,0.0,-1);
      glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/8,roomWidth/2,-1);
      glTexCoord2f(rep, rep);	glVertex3f(-groundWidth/8,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-groundWidth/8,0.0,-groundLength);
      glEnd(); 

      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, -1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-0.5,0.0,0);
      glTexCoord2f(rep, 0.0);	glVertex3f(-0.5,roomWidth/2,0);
      glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,0);
      glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,0);
      glEnd();  


      // Draw right wall
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( -1, 0, 0);

      glTexCoord2f(0.0, 0.0);	glVertex3f(groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep, 0.0);	glVertex3f(groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,-groundLength);
      glEnd();  

      // Draw back wall  
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, -1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,roomHeight);
      glEnd();  

      // Draw front wall  
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-roomWidth/2,0.0,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(-roomWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(-1,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-1,0.0,-groundLength);
      glEnd();

      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(roomWidth/2,0.0,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(roomWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(1,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(1,0.0,-groundLength);
      glEnd();

      glColor3f(0.9,0.8,0.6);
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);	
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-1,roomWidth/2,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(1,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(1,3.5,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-1,3.5,-groundLength);
      glEnd();

      // Draw window
      drawWindow();

      // Draw front 
      glColor3f(0.9,0.8,0.6);
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);	
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(groundWidth/2,0.0,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(groundWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(roomWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(roomWidth/2,0.0,-groundLength);
      glEnd();

      //  Undo transformations and textures
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);      
   } 
   else if (pattern == 3) {
            // draw bathtub
      glPushMatrix();
      glTranslated(3.3, 1.08, 1.8);
      glScaled(0.5,0.5,1);   
      bathtub(0,0,0,1);
      glPopMatrix();  

      // draw lamps
      glPushMatrix();
      glTranslated(-3.75, 0.5, -2.25);
      glScaled(0.25,0.25,0.25);
      drawLamp();
      glPopMatrix();  

      glPushMatrix();
      glTranslated(-3.75, 0.5, -3.75);
      glScaled(0.35,0.45,0.5);
      drawLamp();
      glPopMatrix();  

      // Draw side tables
      glPushMatrix();
      glTranslated(-3.9, 0.0, -2.5);   
      glScaled(0.25,0.25, 0.25);
      cube(1,1,1, 1, 1, 1, 1, 1, 1, 1, texture[6], 1,1,1,1,1,1);
      glPopMatrix();

      glPushMatrix();
      glTranslated(-3.9, 0.0, -4);   
      glScaled(0.25,0.25, 0.25);
      cube(1,1,1, 1, 1, 1, 1, 1, 1, 1, texture[6], 1,1,1,1,1,1);
      glPopMatrix();

      // draw bed
      glPushMatrix();
      glTranslated(-2.8, 0.0, -3);   
      glRotated(90.0,0,1,0);
      glScaled(0.8, 0.35, 2);
      drawChair(0.523, 0.442, 0.161);
      glPopMatrix();

      // dining table
      glPushMatrix();
      glTranslated(2, 0.0, -2);   
      glRotated(90.0,0,1,0);
      glScaled(0.5, 0.5, 0.5);
      drawTable(0.27,0.027,0.035);
      glPopMatrix();

      // living room table
      glPushMatrix();
      glTranslated(-2.3, 0.0, 2.5);      
      glScaled(0.5, 0.5, 0.45);
      drawTable(0.42, 0.42, 0.42);
      glPopMatrix();

      // draw tv
      glPushMatrix();
      glTranslated(-2.67, 1.35, 2.75);      
      glScaled(0.55,0.25, 0.09);
      cube(1,1,1, 1, 1, 1, 1, 1, 1, 1, texture[7], 1,1,1,1,1,1);
      glPopMatrix();


      // Sofa
      glPushMatrix();
      glTranslated(-2.3, 0.0,1);
      glScaled(1.35, 0.5, 0.5);
      drawChair(0.162, 0.252, 0.291);
      glPopMatrix();

      // chair
      glPushMatrix();
      glTranslated(2, 0.0, -3);
      glScaled(0.5, 0.5, 0.5);
      drawChair(0.38, 0.38, 0.38);
      glPopMatrix();

      // chair
      glPushMatrix();
      glTranslated(2, 0.0, -1);
      glRotated(180,0,1,0);
      glScaled(0.5, 0.5, 0.5);
      drawChair(0.38, 0.38, 0.38);
      glPopMatrix();


      //  Set specular color to white
      float white[] = {1,1,1,1};
      float Emission[]  = {0.0,0.0,0.01*emission,1.0};
      glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
      glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
      //  Save transformation
      glPushMatrix();
      //  Offset, scale and rotate
      glTranslated(x,y,z);
      glRotated(th,0,1,0);
      glScaled(dx,dy,dz);
      //  Enable textures
      glEnable(GL_TEXTURE_2D);
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
      glColor3f(0.8,0.8,0.8);
      //  Enable textures
      //  Select texture if textures are on
      if (ntex<0)
      glDisable(GL_TEXTURE_2D);
      else
      {
      glEnable(GL_TEXTURE_2D);
      }

      // draw floor
      glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,t_mode?GL_REPLACE:GL_MODULATE);
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[0]);					
      glBegin(GL_QUADS);
      glNormal3f( 0, 1, 0);

      glTexCoord2f(0.0,0.0); 	glVertex3f(-groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep,0.0); 	glVertex3f(-groundWidth/2,0.0,-groundLength);
      glTexCoord2f(rep,rep); 	glVertex3f(groundWidth/2,0.0,-groundLength);
      glTexCoord2f(0.0,rep); 	glVertex3f(groundWidth/2,0.0,roomHeight);
      glEnd();
      glDisable(GL_POLYGON_OFFSET_FILL);

      // Draw left wall
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 1, 0, 0);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(rep, rep);	glVertex3f(-groundWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-groundWidth/2,0.0,-groundLength);
      glEnd();   


      // Draw right wall
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( -1, 0, 0);

      glTexCoord2f(0.0, 0.0);	glVertex3f(groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep, 0.0);	glVertex3f(groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,-groundLength);
      glEnd();  

      // Draw back wall  
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, -1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/2,0.0,roomHeight);
      glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,roomHeight);
      glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,roomHeight);
      glEnd();  

      // Draw front wall  
      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-roomWidth/2,0.0,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(-roomWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(-1,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-1,0.0,-groundLength);
      glEnd();

      glColor3f(0.9,0.8,0.6);	
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(roomWidth/2,0.0,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(roomWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(1,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(1,0.0,-groundLength);
      glEnd();

      glColor3f(0.9,0.8,0.6);
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);	
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(-1,roomWidth/2,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(1,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(1,3.5,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(-1,3.5,-groundLength);
      glEnd();

      // Draw window
      drawWindow();

      // Draw front 
      glColor3f(0.9,0.8,0.6);
      if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,houseTexture);	
      glBegin(GL_QUADS);
      glNormal3f( 0, 0, 1);

      glTexCoord2f(0.0, 0.0);	glVertex3f(groundWidth/2,0.0,-groundLength);
      glTexCoord2f(rep, 0.0);	glVertex3f(groundWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(rep, rep);	glVertex3f(roomWidth/2,roomWidth/2,-groundLength);
      glTexCoord2f(0.0, rep);	glVertex3f(roomWidth/2,0.0,-groundLength);
      glEnd();

      //  Undo transformations and textures
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
   }

      
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
   glPushMatrix();
   glRotated(-90.0,1,0,0);   
   cylinder(1,10, 0, 0, 0, texture[0]);
   glPopMatrix();
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
}


void drawGarage() {
   glPushMatrix();
   cube(-1,0,0, 0.15, 1, 1, 1, 1, 1, 1, texture[4], 1,1,1,1,1,1);
   cube(1,0,0, 0.15, 1, 1, 1, 1, 1, 1, texture[4], 1,1,1,1,1,1);
   cube(0,0,1, 1, 1, 0.15, 1, 1, 1, 1, texture[4], 1,1,1,1,1,1);

   // roof
   cube(0,1,0, 1.25, 0.25, 1.25, 1, 1, 1, 1, texture[4], 1,1,1,1,1,1);
   
   glPopMatrix();
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
   //  Set perspective
   glLoadIdentity();
   if (mode == 0 ){
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Eye position
   if (mode == 1) {
      glRotatef(xRotation,1.0,0.0,0.0);  // rotate camera on the x-axis 
      glRotatef(yRotation,0.0,1.0,0.0);  // rotate camera on the y-axis 
      glTranslated(xpos,ypos,zpos);   // translate the screen to the position of our camera
   }
   glUseProgram(0);
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light direction
      float Position[]  = {20*Cos(zh),ylight,15*Sin(zh),1};
      float Shinyness[] = {16};
      float Emission[]  = {0.0,0.0,0.0,1.0};
      //  Draw light position as ball (still no lighting here)
      glPushMatrix();
      glTranslated(-8, 10, 0);
      // sun
      if (night != 1) {
         // Moon
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D,texture[12]);
         glRotated(180, 0, 1, 0);
         ball(Position[0],Position[1],Position[2] , 1);
         glDisable(GL_TEXTURE_2D);
      } else {
         // Sun
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D,texture[11]);
         glColor3f(1,1,1);
         ball(Position[0],Position[1],Position[2] , 2);
         glDisable(GL_TEXTURE_2D);
      }
      
      glPopMatrix();

      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);



      glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,Shinyness);
      glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,RGBA);
      glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,RGBA);
      glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Specular);
      glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   }
   else{
      glDisable(GL_LIGHTING);
   }
   
   switch (obj) {
   //  Draw scene
   case 0:         
      for (int i=0; i<5; i++) {
         glPushMatrix();
         glTranslated(-30,0.1, -30 + i*15);
         drawTree(1);
         glPopMatrix();
      }
      for (int i=0; i<5; i++) {
         glPushMatrix();
         glTranslated(30,0.1, -30 + i*15);
         drawTree(1);
         glPopMatrix();
      }
      for (int i=0; i<5; i++) {
         glPushMatrix();
         glTranslated(-50,0.1, -25 + i*15);
         drawTree(1);
         glPopMatrix();
      }
      for (int i=0; i<5; i++) {
         glPushMatrix();
         glTranslated(50,0.1, -25 + i*15);
         drawTree(1);
         glPopMatrix();
      }
      
      glPushMatrix();
      glTranslated(0,0.1,0);
      drawHouse(0,0.1,0 , 0.5,0.5,0.5 , 0, texture[4], 1);
      glPopMatrix();

      glPushMatrix();
      glTranslated(0,0.1,14);
      drawHouse(0,0.1,0 , 0.5,0.5,0.5 , 0, texture[2], 1);
      glPopMatrix();

      glPushMatrix();
      glTranslated(0,0.1, -15);
      drawHouse(0,0.1,0, 0.5,0.5,0.5 , 0, texture[3], 1);
      glPopMatrix();

      // Draw Car
      glPushMatrix();
      glTranslated(-7, 0, carSpeed);
      
      glRotated(270, 360, 1, 0);
      glScaled(0.05,0.05,0.05);      
      drawCar(0, 0);
      glPopMatrix();
      
      // Draw road
      cube(-8,0,-22, 1.5, 0.1, 70, 1, 1, 1, 1, texture[10], 1,1,1,1,1,1);

      // draw horizontal road
      cube(-5,0,6, 15, 0.1, 1, 1, 1, 1, 1, texture[10], 1,1,1,1,1,1);
      cube(-5,0,-9, 15, 0.1, 1, 1, 1, 1, 1, texture[10], 1,1,1,1,1,1);


      glPushMatrix();
      glTranslated(-14,0.1,0);
      drawHouse(0,0.1,0, 0.5,0.5,0.5 , 0, texture[2], 1);
      glPopMatrix();

      glPushMatrix();
      glTranslated(-14,0.1,14);
      drawHouse(0,0.1,0 , 0.5,0.5,0.5 , 0, texture[3], 1);
      glPopMatrix();

      glPushMatrix();
      glTranslated(-14,0.1,-14);
      drawHouse(0,0.1,0 , 0.5,0.5,0.5 , 0, texture[4], 1);
      glPopMatrix();

      drawGrass(0,0,0 , 8,8,8 , 0);
      glTranslated(0,40, 0);
      Sky(3.5*dim);
      break;

   case 1:
      // draw bed
      glPushMatrix();
      glTranslated(0,0,0);   
      glRotated(90.0,0,1,0);
      glScaled(1.8, 1.35, 3);
      drawChair(0.523, 0.442, 0.161);
      glPopMatrix();
      break;
   case 2:
      // draw table
      glPushMatrix();
      glTranslated(0,0,0);      
      glScaled(1.5, 1.5, 1.45);
      drawTable(0.42, 0.42, 0.42);
      glPopMatrix();
      break;
   case 3:
      // draw bathtub
      glPushMatrix();
      glTranslated(0, 0, 0);
      glScaled(1.5,1.5,2);   
      bathtub(0,0,0,1);
      glPopMatrix();  
      break;
   case 4:
      // draw lamp
      glPushMatrix();
      glTranslated(0,0,0);
      glScaled(1.35,1.45,1.5);
      drawLamp();
      glPopMatrix();  
      break;
   case 5:
      // chair
      glPushMatrix();
      glTranslated(0,0,0);
      glScaled(1.5, 1.5, 1.5);
      drawChair(0.38, 0.38, 0.38);
      glPopMatrix();
      break;

   case 6:
      // seat
      glPushMatrix();
      glTranslated(0,0, 0);
      glScaled(1.5, 1.5, 1.5);      
      drawSeat();
      glPopMatrix();
      break;
   case 7:
      // counter
      glPushMatrix();
      glTranslated(0,0, 0);
      glScaled(1.5, 1.5, 1.5);      
      Lcounter(0,0,0,1,10,1,5);
      glPopMatrix();
      break;
   case 8:
      // roof
      glPushMatrix();
      glTranslated(0,0, 0);
      drawRoof(texture[4]);
      glPopMatrix();
      break;
   case 9:
      // vase
      glPushMatrix();
      glTranslated(0,0, 0);
      glScaled(0.5,0.5,0.5);      
      drawVase(0,0,0,2.5,fmod(120*time,360.0),1,fmod(90*time,360.0));
      glScaled(8,8,8);            
      glPopMatrix();
      break;
   case 10:
      // car
      glPushMatrix();
      glTranslated(0,0, 0);
      
      // rotate car
      glRotated(270, 360, 1, 0);
      glScaled(0.24,0.24,0.24);      
      // drawGarage();
      drawCar(0, 0);
      glPopMatrix();
      break;
   }
   
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      const double len=2.0; //  Length of axes
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f Light=%s Texture=%s",th,ph,dim,light?"On":"Off",mode?"Replace":"Modulate");
   if (light)
   {
      glWindowPos2i(5,25);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(45*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene   
   carSpeed = fmod(-20*t, 150) + 50;
   // print carspeed
   // printf("car spped %i\n", carSpeed) ;
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   if (mode == 1) {         
      if (mode == 1) {
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
   } else {
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
      else if (key == GLUT_KEY_DOWN && ph>5)
         ph -= 5;
      //  PageUp key - increase dim
      else if (key == GLUT_KEY_PAGE_DOWN)
         dim += 0.1;
      //  PageDown key - decrease dim
      else if (key == GLUT_KEY_PAGE_UP && dim>1)
         dim -= 0.1;
      //  Keep angles to +/-360 degrees
      th %= 360;
      ph %= 360;
   }
   //  Update projection
   // Project(45,asp,dim);
   myProject(mode, fov, asp, dim);
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
      //  Change field of view angle
   else if (ch == '-')
      fov++;
   else if (ch == '+')
      fov--;
   
   else if (ch == 'r') {
      // print camera position
      dim = 5;

      printf("xpos %f, ypos %f, zpos %f\n", xpos, ypos, zpos);
   }
   else if (ch == 'R') {
      dim = 20.5;
   }
   else if (ch == 't') {
      if (roof == 1) {
         roof = 0;
      } else {
         roof = 1;   
      }
   }

   else if (mode == 1) {
      // w to move forward
      if (ch =='w' || ch =='W')
      {
         float xRotationrad, yRotationrad;
         yRotationrad = (yRotation / 180 * M_PI);
         xRotationrad = (xRotation / 180 * M_PI);
         xpos -= (sin(yRotationrad));
         zpos += (cos(yRotationrad));
         ypos += (sin(xRotationrad));
      }
      // a to move left
      else if (ch=='a' || ch =='A')
      {
         float yRotationrad;
         yRotationrad = (yRotation / 180 * M_PI);
         xpos += (cos(yRotationrad)) * 0.2;
         zpos += (sin(yRotationrad)) * 0.2;
      }
      // s to move backward
      else if (ch =='s' || ch =='S')
      {
         float xRotationrad, yRotationrad;
         yRotationrad = (yRotation / 180 * M_PI);
         xRotationrad = (xRotation / 180 * M_PI);
         xpos += (sin(yRotationrad));
         zpos -= (cos(yRotationrad)) ;
         ypos -= (sin(xRotationrad));
      }
      // d to move right
      else if (ch =='d' || ch =='D')
      {
         float yRotationrad;
         yRotationrad = (yRotation / 180 * M_PI);
         xpos -= (cos(yRotationrad)) * 0.2;
         zpos -= (sin(yRotationrad)) * 0.2;
      }

   }
   else if (ch == 'c' || ch == 'C'){
      mode += 1;
      if( mode > 1) {
         mode = 0;
      }
   }
   //  Reset view angle
   else if (ch == '0')
      th = 180;
   //  Toggle texture mode
   else if (ch == 'm' || ch == 'M'){
      mode += 1;
      if( mode > 1) {
         mode = 0;
      }
   }
   // Toggle day and night
   if (ch == 'n' || ch == 'N'){
      night += 1;
      ambient = 30;
      diffuse = 100;
      specular = 0;
      emission = 0;

      if(night > 1) {
         night = 0;
         ambient = 5;
         diffuse = 40;
         specular = 5;
         emission = 0;
         shininess = 1;
      }
   }
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Toggle textures mode
   else if (ch == 't')
      ntex = 1-ntex;
   //  Cycle objects
   else if (ch == 'o' || ch == 'O')
      //  objects
      obj = (obj+1)%14;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0 && mode == 0)
      ambient -= 5;
   else if (ch=='A' && ambient<100 && mode == 0)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0 && mode == 0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100 && mode == 0)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100 && mode == 0)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0 && mode == 0)
      emission -= 5;
   else if (ch=='E' && emission<100 && mode == 0)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1 && mode == 0)
      shininess -= 1;
   else if (ch=='N' && shininess<7 && mode == 0)
      shininess += 1;
   //  Repitition
   else if (ch=='+')
      rep++;
   else if (ch=='-' && rep>1)
      rep--;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   myProject(mode, fov, asp, dim);
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
   myProject(mode,fov,asp,dim);
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
   glutInitWindowSize(1000,800);
   glutCreateWindow("Khaled Hossain - Final");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("./textures/wood.bmp");
   texture[1] = LoadTexBMP("./textures/grass.bmp");
   texture[2] = LoadTexBMP("./textures/brick.bmp");
   texture[3] = LoadTexBMP("./textures/wood.bmp");
   texture[4] = LoadTexBMP("./textures/table.bmp");
   texture[5] = LoadTexBMP("./textures/wall.bmp");
   texture[6] = LoadTexBMP("./textures/crate.bmp");
   texture[7] = LoadTexBMP("./textures/netflix.bmp");
   texture[8] = LoadTexBMP("./textures/water.bmp");
   texture[9] = LoadTexBMP("./textures/sky1.bmp"); 
   texture[10] = LoadTexBMP("./textures/road.bmp");
   texture[11] = LoadTexBMP("./textures/sun.bmp");
   texture[12] = LoadTexBMP("./textures/moon.bmp");
   texture[13] = LoadTexBMP("./textures/light_wood.bmp");
   texture[14] = LoadTexBMP("./textures/tire.bmp");

   sky[0] = LoadTexBMP("./textures/sky.bmp");
   sky[1] = LoadTexBMP("./textures/sky1.bmp");
   int scale = 1;
   if (argc >= 3)
      scale = strtod(argv[2], NULL);
   if (scale<=0) scale = 1;
   //  Set color
   if (argc>=6) RGBA[0] = strtod(argv[3],NULL);
   if (argc>=6) RGBA[1] = strtod(argv[4],NULL);
   if (argc>=6) RGBA[2] = strtod(argv[5],NULL);
   objList = LoadOBJ("Lowpoly_tree_sample.obj");
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
