#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <windows.h>
#include <math.h>
#include <glut.h>
#define ESC '\033'

int width = 600, height = 600;
bool side = true;
double angle = 2.0, dScale = 1.2, dMov = 5, dPos = 0.01;
double angleH = 45.0, angleV = -30.0;
double dX, dY, dZ;
double scale = 2000;
int movX = 0, movZ = 0;
float light[] = {0, 0.5, 0, 0.0};// коорд источника+ 
/*Если четвертый компонент этой точки равен нулю, то точечный источник превращается в удаленный, для которого существенно только направление лучей*/

void ChangeCamera()
{ dX = cos(angleV * M_PI / 180.0) * cos(angleH * M_PI / 180.0),
 dZ = cos(angleV * M_PI / 180.0) * sin(angleH * M_PI / 180.0),
 dY = sin(angleV * M_PI / 180.0);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(dX, dY, dZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Timer(int value)
{ angleH += 2.0;
 glutPostRedisplay();

}

void Reshape(int width, int height)
{ glViewport(0, 0, width, height);
 glClearColor(0.0, 0.75, 1.0, 0.0);

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-width/2, width/2, -height/2, height/2, -500, 500);
}

void Display()
{ glTranslated(10, 5, 70);
 glClearColor(0, 0, 0, 1.0);
 glEnable(GL_DEPTH_TEST);//проверка глубины.
 glEnable(GL_COLOR_MATERIAL); // разрешаем давать нашим объектам какой-то цвет
 glEnable(GL_LIGHTING);//разрешаем освещение
 glEnable(GL_NORMALIZE);// задаваемые нормали будут нормироваться 
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// чистим буфер цвета//очистка Z буфера
 
 glOrtho(-width/2, width/2, -height/2, height/2, -800, 800);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(10, 5, 70, 0, 0, 0, 0, 1, 0);

 float color[3] = {0,1,1};
 glLightfv(GL_LIGHT0, GL_DIFFUSE, color);

 ChangeCamera();

 glScaled(scale, scale, scale);
 glTranslated(movX, 0, movZ);

 glPushMatrix();

 glColor3d(1, 1, 1);
 glScaled(5, 5, 5);
 glutSolidDodecahedron();
 glColor3d(0.0, 0.0, 0.0);
 glutWireDodecahedron();

 glTranslated(0, 0, 4);
 glColor3d(0.2, 0.2, 0.8);
 glutSolidOctahedron();
 glColor3d(0.0, 0.0, 0.0);
 glutWireOctahedron();

 glTranslated(0, 0, 3);
 glColor3d(0.2, 0.8, 0.2);
 glutSolidOctahedron();
 glColor3d(0.0, 0.0, 0.0);
 glutWireOctahedron();

 glLightfv(GL_LIGHT0, GL_POSITION, light);
 glEnable(GL_LIGHT0);

 glPopMatrix();

 glutSwapBuffers();//сменить экранные буфера
}

void Keyboard(unsigned char key, int width, int height)
{ switch (key)
 { case '=':
   scale *= dScale;
   glutPostRedisplay();
   break;
  case '-':
   scale /= dScale;
   glutPostRedisplay();
   break;
  case 'w':
   movX += dMov;
   glutPostRedisplay();
   break;
  case 's':
   movX -= dMov;
   glutPostRedisplay();
   break;
  case 'a':
   movZ += dMov;
   glutPostRedisplay();
   break;
  case 'd':
   movZ -= dMov;
   glutPostRedisplay();
   break;
 glutPostRedisplay();
   break;
  case ESC:
   exit(0);
 }
}

void Special(int key, int x, int y)
{ if (key == GLUT_KEY_LEFT)
  angleH -= angle;

 if (key == GLUT_KEY_RIGHT)
  angleH += angle;

 if (key == GLUT_KEY_UP)
  if (angleV < 90) angleV += angle;

 if (key == GLUT_KEY_DOWN)
  if (angleV > -90) angleV -= angle;

 glutPostRedisplay();
}

void Idle()
{ if (light[0] > 1)
 { dPos = -0.0005;
  side = !side;
 }
 if (light[0] < -1)
 { dPos = 0.0005;
  side = !side;
 }
 light[0] += dPos;
 light[2] = (side ? 1 : -1) * sqrtf(abs(1 - light[0] * light[0]));
 glutPostRedisplay();
}



int main(int argc, char *argv[])
{
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
 glutInitWindowSize(width, height);
 glutInitWindowPosition(400, 100);
 glutCreateWindow("Lab3");

 glEnable(GL_DEPTH_TEST);
 glEnableClientState(GL_VERTEX_ARRAY);

 glutReshapeFunc(Reshape);
 glutDisplayFunc(Display);
 glutKeyboardFunc(Keyboard);
 glutSpecialFunc(Special);
 glutIdleFunc(Idle);

 glutMainLoop();


 return 0;
}


/* Головний цикл додатка */
// int main(int argc, char *argv[])
// {

//   glutInit(&argc,argv);

//   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//   glutInitWindowSize(600, 600);
//   glutInitWindowPosition(0, 0);
//   glutCreateWindow("Lab3");
  
//   glClearColor(0, 0, 0, 1);
//   glShadeModel(GL_SMOOTH);
//   glEnable(GL_DEPTH_TEST);
//   glEnableClientState(GL_VERTEX_ARRAY);

//   glutDisplayFunc(display);
//   glutKeyboardFunc(keyboard_func);
//   glutSpecialFunc(special_keyboard_func);
//   // glMatrixMode(GL_PROJECTION);
//   // gluPerspective(40, 1, 1, 400);
//   // glMatrixMode(GL_MODELVIEW);
  
//   gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
//   // func(mas);
//   list_of_commands();
//   glutMainLoop();
 
//   return 0;
// }
