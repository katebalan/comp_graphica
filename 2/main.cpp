#include <iostream>
#include <GL/glut.h>   //Подключение библиотеки glut.h
#include <cmath>
#include <stdlib.h>

#define _USE_MATH_DEFINES

using namespace std;

// double x = 0, y = 0, z = 80;
// double lx = 0, ly = 0, lz = 0;
// double angle_XY = 0, angle_YZ = 0;

int x_camera = 0, y_camera = -20, z_camera = 50;
double x_light = 0, y_light = 20, z_light = 4.0;
double camera_angle = (3 * M_PI) / 2;
double light_angle = 0;
double camera_angle_speed = 0.05
double light_angle_speed = 0.0005
double mas = []
bool stop_animation = False

int matrix_model = [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]]

void init(void) {
  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutInitWindowPosition(0,0);
  glutCreateWindow("Lab3");

  glEnable(GL_DEPTH_TEST);
}

void init_camera(void) {
  gluLookAt(x_camera, y_camera, z_camera, 0, 0, 0, 0, 1, 0)
}

void init_light(void) {
  double ambientLight = [0.0, 0.0, 0.0, 1.0]
  double diffuseLight = [1.0, 1.0, 1.0, 1.0]
  double positionLight = [0.0, 0.0, 100.0, 1.0]
  double specularLight = [1.0, 1.0, 1.0, 1.0]
  double black = [0.0, 0.0, 0.0, 1.0]
  glEnable(GL_LIGHTING)
  // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, black)
  glEnable(GL_LIGHT0)
  // glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, True)

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight)
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight)
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight)
  glLightfv(GL_LIGHT0, GL_POSITION, positionLight)

  // gray = [1.0, 1.0, 1.0, 1]
  // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray)
  
  glEnable(GL_COLOR_MATERIAL)
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE)
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularLight)
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 128)
}

void special_keyboard_func( int key, int x1, int y1 ) {
  if (key == GLUT_KEY_DOWN) {
    my_translate(0, -5, 0);
  }
  if (key == GLUT_KEY_UP) {
    my_translate(0, 5, 0);
  }       
  if (key == GLUT_KEY_LEFT) {
    my_translate(-5, 0, 0);
  }
  if (key == GLUT_KEY_RIGHT) {
    my_translate(5, 0, 0);
  }

  if (key == GLUT_KEY_F1) {
    glutIdleFunc(None);
    stop_animation = True;
  }

  glutPostRedisplay(); 
}

void display(void) {
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
}

/* Функція обробляє повідомлення від клавіатури */
void keyboard_func( unsigned char key, int x1, int y1 ) {
#define ESCAPE '\033'
  switch (key) {
     case ESCAPE:  exit(0);
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
  list_of_commands();
  glutMainLoop();
 
  return 0;
}
