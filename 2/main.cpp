#include <iostream>
#include <GL/glut.h>   //Подключение библиотеки glut.h
#include <cmath>
#include <stdlib.h>

// #include <GL/glew.h>

// #include <GL/gl.h>
// #include <GL/glu.h>
// #include <GL/glext.h>

// const double pi = 3.14159265358979323846;

using namespace std;

double x = 0, y = 0, z = 80;
double lx = 0, ly = 0, lz = 0;
double angle_XY = 0, angle_YZ = 0;

void list_of_commands(void) 
{
  glNewList(1, GL_COMPILE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glPushMatrix();
  glColor3ub(255, 255, 255);
  glutSolidTorus(2, 3, 8, 8);

  glColor3ub(255, 0, 0);
  glutWireCube(10);

  glColor3ub(0, 0, 0);
  glutWireTorus(2, 3, 8, 8);

  glTranslatef(15, 0, 0);
  glColor3ub(255, 0, 0);
  glutWireCube(10);

  glTranslatef(4, 0, 0);
  glColor3ub(255, 255, 255);
  glRotatef(-90.0,0.0,1.0,0.0);
  glutSolidCone(5, 8, 15, 15); 
  
  glColor3ub(0, 0, 0);
  glutWireCone(5, 8, 15, 15); 
  glPopMatrix();

  glPushMatrix();
  glColor3ub(255, 255, 255);
  glTranslatef(-15, 0, 0);
  glutSolidSphere(5, 20, 20);

  glColor3ub(255, 0, 0);
  glutWireCube(10);

  glColor3ub(0, 0, 0);
  glutWireSphere(5, 20, 20);
  glPopMatrix();

  // glPushMatrix();
  // glTranslate(20, 0, 0);
  // glEnableClientState(GL_VERTEX_ARRAY);
  // glVertexPointer(3, GL_DOUBLE, 0, mas);

  // glColor3ub(255, 140, 0);
  // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  // glDrawArrays(GL_QUADS, 0, 400);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glColor3ub(255, 0, 0);
  // glDrawArrays(GL_QUADS, 0, 400);
  // glPopMatrix();

  glEndList();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCallList(1);

  glPushMatrix();
  glTranslatef(0, -15, 0);
  glCallList(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 15, 0);
  glCallList(1);
  glPopMatrix();

  glutSwapBuffers();

  // glMatrixMode(GL_MODELVIEW);
  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // glLoadIdentity();
  // glColor3ub(153, 51, 255); 
  // glScalef(.4, .4, .4);
  // gluLookAt(X, Y, Z, XC, YC, ZC, 0, 1, 0);

  // glTranslatef(-1.0, 1.0, 0);
  // glutSolidTorus(.1, .3, 6, 6); 
  // glColor3f(1.0, 1.0, 1.0); 
  // glutWireTorus(.1, .3, 6, 6);
  
  // glTranslatef(0, -1.0, 0);
  // glutWireTorus(.1, .2, 6, 6);

  // glRotatef(90.0,0.0,1.0,0.0);
  // glTranslatef(0, -1.0, 0);
  // glColor3ub(153, 51, 255); 
  // glutSolidCone(.4, .6, 15, 15); 
  // glColor3f(1.0, 1.0, 1.0); 
  // glutWireCone(.4, .6, 15, 15); 
  // glutWireCone(.5, .7, 15, 15);
   
  // glRotatef(-90.0,0.0,1.0,0.0);
  // glTranslatef(1.2, 2.0, 0);
  // glColor3ub(153, 51, 255); 
  // glutSolidSphere(0.2, 6, 6); 
  // glColor3ub(255, 255, 255); 
  // glutWireSphere(0.2, 6, 6);
  
  // glTranslatef(0, -1.0, 0);
  // glColor3f(0.9, 0.3, 0.2); 
  // glutSolidSphere(0.5, 20, 20); 
  // glColor3f(1.0, 1.0, 1.0); 
  // glutWireSphere(0.5, 20, 20);

  // glTranslatef(0, -1.0, 0);
  // glColor3ub(255, 255, 255); 
  // glutWireSphere(0.3, 18, 18);

  // glTranslatef(1.0, 1.0, 0);
  // glColor3ub(153, 51, 255); 
  // glutSolidCube(.3); 
  // glColor3f(1.0, 1.0, 1.0); 
  // glutWireCube(.3);
  
  // glTranslatef(0, -.7, 0); 
  // glutWireCube(.3); 
  // glutSwapBuffers(); 
}


void special_keyboard_func( int key, int x1, int y1 ) {
  if (key == GLUT_KEY_DOWN) {
    angle_XY += 0.05;
    if (z > 0) {
      ly = sin(angle_XY);
      lz = -cos(angle_XY);
    }
    if (z < 0) {
      ly = sin(angle_XY);
      lz = cos(angle_XY);
    }
  }
  if (key == GLUT_KEY_UP) {
    angle_XY -= 0.05;
    if (z > 0) {
      ly = sin(angle_XY);
      lz = -cos(angle_XY);
    }
    if (z < 0) {
      ly = sin(angle_XY);
      lz = cos(angle_XY);
    }
  }       
  if (key == GLUT_KEY_LEFT) {
    angle_YZ += 0.05;
    lx = sin(angle_YZ);
    lz = -cos(angle_YZ);
  }
  if (key == GLUT_KEY_RIGHT) {
    angle_YZ -= 0.05;
    lx = sin(angle_YZ);
    lz = -cos(angle_YZ);
  }

  glLoadIdentity();

  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
  cout << "z = " << z << endl;
  cout << "lx = " << lx << endl;
  cout << "ly = " << ly << endl;
  cout << "lz = " << lz << endl;

  gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0, 1, 0);
  glutPostRedisplay(); 
}

/* Функція обробляє повідомлення від клавіатури */
void keyboard_func( unsigned char key, int x1, int y1 ) {
#define ESCAPE '\033'
  switch (key) {
     case ESCAPE:  exit(0);
  //   case 'd': fi--; break;
  //   case 'a': fi++; break;
  //   case 'w': if(teta < 90) teta++; break;
  //   case 's': if(teta > -90) teta--; break;
  }

  if ( key == 'm') {
    z += 5;
  }
  if ( key == 'n' ) {
    z -= 5;
  }

  glLoadIdentity();

  cout << "x = " << x << endl;
  cout << "y = " << y << endl;
  cout << "z = " << z << endl;
  cout << "lx = " << lx << endl;
  cout << "ly = " << ly << endl;
  cout << "lz = " << lz << endl;

  

  if ( key == 'q') {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(-40.0, 40.0, -40.0, 40.0, 40, 100);
      glMatrixMode(GL_MODELVIEW);
  }
  if ( key == 'w') {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(40, 1, 1, 400);
      glMatrixMode(GL_MODELVIEW);
  }
  if ( key == 'e') {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(-40, 40, -40, 40, 30, 200);
      glMatrixMode(GL_MODELVIEW);
  }

  gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0, 1, 0);
  glutPostRedisplay();
}

/* Головний цикл додатка */
int main(int argc, char *argv[])
{

  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Lab2");
  
  glClearColor(0, 0, 0, 1);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard_func);
  glutSpecialFunc(special_keyboard_func);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(40, 1, 1, 400);
  glMatrixMode(GL_MODELVIEW);
  
  gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
  // func(mas);
  list_of_commands();
  glutMainLoop();
 
  return 0;
}
 
