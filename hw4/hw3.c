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
double dim=12.5;   //  Size of world
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   3;  // Elevation of light
unsigned int texture[9]; // Texture names
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
   cylinder(0.75, 0.25, 0,0,0, texture[3]);
   glPopMatrix();  
   
   // Seat Bottom
   glPushMatrix();
   glTranslated(0,0,0);
   glRotated(-90.0,1,0,0);
   cylinder(0.25, 1.0, 0,0,0, texture[4]);
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

   glColor3f(0,0,1);
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

#define PI 3.14159265358979323846
#define BASE_RADIUS 0.5
#define TOP_RADIUS 0.2
#define HEIGHT 1.0
#define SEGMENTS 50

void drawVase(double x, double y, double z, double r, double emi, double sc, double rh){
    
    int th,ph;
    float Emission1[] = {Sin(emi),Sin(emi),Sin(emi),1};    

    // Draw body
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission1);
    glPushMatrix();
    glTranslated(x,y+Sin(rh),z);
    glScaled(sc,2*sc,sc);

    glColor3f(0,0,0);

    for (ph=-90;ph<90;ph+=5)
    {
        glBegin(GL_QUAD_STRIP);
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
   cylinder(0.5,3, 0, 0, 0, texture[3]);
   glPopMatrix();

   // top top
   glPushMatrix();
   glTranslated(0, 3,0);
   glRotated(-90.0,1,0,0);   
   cylinder(0.75,0.8, 0, 0, 0, texture[3]);
   glPopMatrix();
   
   // bottom
   glPushMatrix();
   glTranslated(0,-2,0);
   glRotated(-90.0,1,0,0);   
   cylinder(0.75,1, 0, 0, 0, texture[3]);
   glPopMatrix();

}


void drawChandelier(double x, double y, double z, double r, double emi, double sc, double rh){
    
    int th,ph;
    float Emission1[] = {Sin(emi),Sin(emi),Sin(emi),1};
    float Emission2[] = {Cos(emi),Cos(emi),Cos(emi),1};
    float Emission3[] = {0,0,0,1};

    // Draw core
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission1);
    glPushMatrix();
    glTranslated(x,y+Sin(rh),z);
    glScaled(sc,2*sc,sc);

    glColor3f(0,0,0);

    for (ph=-90;ph<90;ph+=5)
    {
        glBegin(GL_QUAD_STRIP);
        for (th=0;th<=360;th+=2*5)
        {
            Vertex(th,ph,(r-1.5));
            Vertex(th,ph+5,(r-1.5));
        }
        glEnd();
    }
    glPopMatrix();

    // Draw tentacle 1
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission2);
    glPushMatrix();
    glTranslated(x,y+Sin(rh),z);
    glScaled(sc,sc,sc);
    glColor3f(1,0,0);
    glRotated(-fmod(90*time,360.0),0,1,0);

    double ty = 0, s = r-1;
    double tx,tz;
    for (ph=0;ph<3000*sc;ph+=10, ty-=0.05, s-=0.005)
    {
        glBegin(GL_POINTS);
        tx = Sin(ph)*s;
        tz = Cos(ph)*s;
        glVertex3d(tx,ty,tz);
        glEnd();
    }
    glPopMatrix();

    // Draw tentacle 2
    glPushMatrix();
    glTranslated(x,y+Sin(rh),z);
    glScaled(sc,sc,sc);
    glColor3f(0,1,0);
    glRotated(fmod(90*time,360.0),0,1,0);

    ty = 0, s = r-1.5;
    for (ph=0;ph<3000*sc;ph+=10, ty-=0.05, s-=0.003)
    {
        glBegin(GL_POINTS);
        tx = Sin(ph)*s;
        tz = Cos(ph)*s;
        glVertex3d(tx,ty,tz);
        glEnd();
    }
    glPopMatrix();

    // Draw tentacle 3
    glPushMatrix();
    glTranslated(x,y+Sin(rh),z);
    glScaled(sc,sc,sc);
    glColor3f(1,1,0);
    glRotated(fmod(90*time,360.0),0,1,0);

    ty = 0, s = r-2;
    for (ph=0;ph<3000*sc;ph+=10, ty-=0.05, s-=0.002)
    {
        glBegin(GL_POINTS);
        tx = Sin(ph)*s;
        tz = Cos(ph)*s;
        glVertex3d(tx,ty,tz);
        glEnd();
    }
    glPopMatrix();

    // Draw outer shell
    glPushMatrix();
    glTranslated(x,y+Sin(rh),z);
    glScaled(sc,sc,sc);
    glRotated(90,1,0,0);
    glColor3f(0,0.3,0);
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission3);    
    for (ph=-90;ph<50;ph+=5)
    {
        glBegin(GL_POINTS);
        glColor3f(1,1,1);
        for (th=0;th<=360;th+=2*5)
        {
            double lx = Sin(th)*Cos(ph)*r;
            double ly = Cos(th)*Cos(ph)*r;
            double lz = Sin(ph)*r;
            glVertex3d(lx,ly,lz);
        }
        glEnd();
    }
    glPopMatrix();
}




/*
 *  Draws the house
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void drawHouse(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
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
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/2,0.0,roomHeight);
   glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/2,roomWidth/2,roomHeight);
   glTexCoord2f(rep, rep);	glVertex3f(-groundWidth/2,roomWidth/2,-groundLength);
   glTexCoord2f(0.0, rep);	glVertex3f(-groundWidth/2,0.0,-groundLength);
   glEnd(); 


   // mid partitions
   glColor3f(0.9,0.8,0.6);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/8,0.0,-1);
   glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/8,roomWidth/2,-1);
   glTexCoord2f(rep, rep);	glVertex3f(-groundWidth/8,roomWidth/2,-groundLength);
   glTexCoord2f(0.0, rep);	glVertex3f(-groundWidth/8,0.0,-groundLength);
   glEnd(); 

   glColor3f(0.9,0.8,0.6);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, -1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-0.5,0.0,0);
   glTexCoord2f(rep, 0.0);	glVertex3f(-0.5,roomWidth/2,0);
   glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,0);
   glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,0);
   glEnd();  


   // Draw right wall
   glColor3f(0.9,0.8,0.6);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( -1, 0, 0);

   glTexCoord2f(0.0, 0.0);	glVertex3f(groundWidth/2,0.0,roomHeight);
   glTexCoord2f(rep, 0.0);	glVertex3f(groundWidth/2,roomWidth/2,roomHeight);
   glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,-groundLength);
   glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,-groundLength);
   glEnd();  
   
   // Draw back wall  
   glColor3f(0.9,0.8,0.6);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, -1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-groundWidth/2,0.0,roomHeight);
   glTexCoord2f(rep, 0.0);	glVertex3f(-groundWidth/2,roomWidth/2,roomHeight);
   glTexCoord2f(rep, rep);	glVertex3f(groundWidth/2,roomWidth/2,roomHeight);
   glTexCoord2f(0.0, rep);	glVertex3f(groundWidth/2,0.0,roomHeight);
   glEnd();  

   // Draw front wall  
   glColor3f(0.9,0.8,0.6);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(-roomWidth/2,0.0,-groundLength);
   glTexCoord2f(rep, 0.0);	glVertex3f(-roomWidth/2,roomWidth/2,-groundLength);
   glTexCoord2f(rep, rep);	glVertex3f(-1,roomWidth/2,-groundLength);
   glTexCoord2f(0.0, rep);	glVertex3f(-1,0.0,-groundLength);
   glEnd();

   glColor3f(0.9,0.8,0.6);	
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);

   glTexCoord2f(0.0, 0.0);	glVertex3f(roomWidth/2,0.0,-groundLength);
   glTexCoord2f(rep, 0.0);	glVertex3f(roomWidth/2,roomWidth/2,-groundLength);
   glTexCoord2f(rep, rep);	glVertex3f(1,roomWidth/2,-groundLength);
   glTexCoord2f(0.0, rep);	glVertex3f(1,0.0,-groundLength);
   glEnd();

   glColor3f(0.9,0.8,0.6);
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
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
   if (ntex >= 0) glBindTexture(GL_TEXTURE_2D,texture[2]);	
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


void draw_fractal(double x0, double y0, double angle0, int level)
{
   
   if(level > levelmax) return;
   float r = 0.15/pow(factor,level-1);
   float angle;
   float x, y, coss, sinn;
   int i;
   for(i = 0; i < nleaf; i++)
   {
      angle = offset + angle0 + i*2*M_PI/nleaf/openness - (nleaf-1)*2*M_PI/nleaf/openness/2;
      coss = cos(angle);
      sinn = sin(angle);
      x = x0 + r*coss;
      y = y0 + r*sinn;
      glBegin(GL_LINES);
      glVertex2f(x0, y0);
      glVertex2f(x, y);      
      
      glEnd();
      draw_fractal(x, y, atan2((y-y0), (x-x0)), level+1);
   }
}

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
   glDisable(GL_TEXTURE_2D);

}

void drawGarage() {
   glPushMatrix();
   cube(-1,0,0, 0.15, 1, 1, 1, 1, 1, 1, texture[4], 1,1,1,1,1,1);
   cube(1,0,0, 0.15, 1, 1, 1, 1, 1, 1, texture[4], 1,1,1,1,1,1);
   cube(0,0,1, 1, 1, 0.15, 1, 1, 1, 1, texture[4], 1,1,1,1,1,1);

   // roof
   cube(0,1,0, 1.25, 0.25, 1, 1, 1, 1, 1, texture[4], 1,1,1,1,1,1);
   
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Eye position
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Set perspective
   glLoadIdentity();
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light direction
      float Position[]  = {5*Cos(zh),ylight,5*Sin(zh),1};
      //  Draw light position as ball (still no lighting here)
      // sun
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1);

      // Moon
      glRotated(180, 0, 1, 0);
      ball(Position[0],Position[1],Position[2] , 0.1);
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
   }
   else{
      glDisable(GL_LIGHTING);
   }
   
   switch (obj) {
   //  Draw scene
   case 0:
      drawHouse(0,0.1,0 , 0.5,0.5,0.5 , 0);
      drawGrass(0,0,0 , 1.25,1.25,1.25 , 0);

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
      // lamp base
      glPushMatrix();
      glTranslated(0,0,-4);
      glScaled(1.5, 1.5, 1.5);      
      cylinder(1.5,3, 0, 0, 0, texture[4]);
      glPopMatrix();
      break;
   case 7:
      // seat
      glPushMatrix();
      glTranslated(0,0, 0);
      glScaled(1.5, 1.5, 1.5);      
      drawSeat();
      glPopMatrix();
      break;
   case 8:
      // seat
      glPushMatrix();
      glTranslated(0,0, 0);
      glScaled(1.5, 1.5, 1.5);      
      Lcounter(0,0,0,1,10,1,5);
      glPopMatrix();
      break;
   case 9:
      // seat
      glPushMatrix();
      glTranslated(0,0, 0);
      glScaled(0.5,0.5,0.5);      
      drawChandelier(0,0,0,2.5,fmod(120*time,360.0),1,fmod(90*time,360.0));
      glPopMatrix();
      break;
   case 10:
      // seat
      glPushMatrix();
      glTranslated(0,0, 0);
      glScaled(0.5,0.5,0.5);      
      drawVase(0,0,0,2.5,fmod(120*time,360.0),1,fmod(90*time,360.0));
      glScaled(8,8,8);      
      draw_fractal(0,0.45, M_PI/2, 1);
      glPopMatrix();
      break;
   case 11:
      // fractal
      glPushMatrix();
      glTranslated(0,0, 0);
      glScaled(8,8,8);      
      draw_fractal(0,0, M_PI/2, 1);
      glPopMatrix();
      break;
   case 12:
      // garage
      glPushMatrix();
      glTranslated(0,0, 0);
      drawGarage();
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
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
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
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
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
   //  Reset view angle
   else if (ch == '0')
      th = 180;
   //  Toggle texture mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
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
      obj = (obj+1)%13;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Repitition
   else if (ch=='+')
      rep++;
   else if (ch=='-' && rep>1)
      rep--;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(45,asp,dim);
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
   Project(45,asp,dim);
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
   glutCreateWindow("Khaled Hossain - HW3");
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
   texture[0] = LoadTexBMP("wood.bmp");
   texture[1] = LoadTexBMP("grass.bmp");
   texture[2] = LoadTexBMP("brick.bmp");
   texture[3] = LoadTexBMP("wood.bmp");
   texture[4] = LoadTexBMP("table.bmp");
   texture[5] = LoadTexBMP("wall.bmp");
   texture[6] = LoadTexBMP("crate.bmp");
   texture[7] = LoadTexBMP("sky0.bmp");
   texture[8] = LoadTexBMP("water.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
