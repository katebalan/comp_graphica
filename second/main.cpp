#include <iostream>
#include <GL/glut.h>   //Подключение библиотеки glut.h
#include <math.h>
#include <stdlib.h>

const double pi = 3.14159265358979323846;

using namespace std;

/* початкова ширина і висота вікна */
GLint Width = 750, Height = 750;

double R = 0.5;
double fi = 90, teta = 0;
double X = 0, Y = 0, Z = 1;
double XC = 0, YC = 0, ZC = 0;
double delta = 0.5;

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
}

/* ця функція керує всім виведенням на екран */
void Display(void)
{
 

  glNewList(1, GL_COMPILE);
    glTranslated(4.0, 0.0, 0.0); 
    glColor3f(0.9, 0.3, 0.2); 
    glutSolidSphere(2.8, 20, 20); 
    glColor3f(1.0, 1.0, 1.0); 
    glutWireSphere(2.8, 20, 20);
    glTranslated(2.0, 0.0, 0.0);
  glEndList();

  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glColor3ub(153, 51, 255); 
  /* draw scene */
  glScalef(.08, .08, .08);
  gluLookAt(X, Y, Z, XC, YC, ZC, 0, 1, 0);


    double vertex[300];
    double x = 0, y = 0, z = 0, d = 1;
     for (int i = 0; i<10; i++)
     { for (int j = 0; j<10; j++)
      { int k = (i*10 + j)*3;
       z = sin(x) + cos(y);
       vertex[k] = x;
       vertex[k + 1] = y;
       vertex[k + 2] = z;
       x += d;
      }
      x = 0;
      y += d;
     }

   int quads[324];
   int index = 0;
   for (int i = 0; i<10; i++)
   { for (int j = 0; j<9; j++)
    { int k = i*9 + j;
     if (k % 10 == 9)
      continue;
     quads[index] = k;
     quads[index + 1] = k + 1;
     quads[index + 2] = k + 11;
     quads[index + 3] = k + 10;
     index += 4;
    }
   }
    glTranslatef(-4, -1, 0);
  glEnableClientState(GL_VERTEX_ARRAY);
   glVertexPointer(3, GL_DOUBLE, 0, vertex);

   glColor3d(1.0, 1.0, 1.0);
   glPolygonMode(GL_FRONT, GL_FILL);
   glDrawElements(GL_QUADS, 324, GL_UNSIGNED_INT, quads);

   glColor3d(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glDrawElements(GL_QUADS, 324, GL_UNSIGNED_INT, quads);
glDisableClientState(GL_VERTEX_ARRAY);

 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glTranslatef(-6,-4,0);
    glColor3f (0.7, 0, 1);
   glCallList(1);
   glCallList(1);
   glCallList(1);

    
    // glFlush();
  glutSwapBuffers(); 
}

/* Функція обробляє повідомлення від клавіатури */
void Keyboard( unsigned char key, int x, int y ) {
#define ESCAPE '\033'
  switch (key) {
    case ESCAPE:  exit(0);
    case 'd': fi--; break;
    case 'a': fi++; break;
    case 'w': if(teta < 90) teta++; break;
    case 's': if(teta > -90) teta--; break;
  }

  X = R * cos(teta * pi / 180) * cos(fi * pi / 180);
  Y = R * sin(teta * pi / 180);
  Z = R * cos(teta * pi / 180) * sin(fi * pi / 180);

  glutPostRedisplay();
}

/* Головний цикл додатка */
int main(int argc, char *argv[])
{

  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  /* setup the size, position, and display mode for new windows */
  glutInitWindowSize(Width,Height);
  glutInitWindowPosition(0,0);
  
  /* create and set up a window */
  glutCreateWindow("Lab2");
  init();
  //glutReshapeFunc(reshape);
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  /* tell GLUT to wait for events */
  glutMainLoop();
 
 return 0;
}
 
