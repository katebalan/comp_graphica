#include <iostream>
#include <GL/glut.h>   //Подключение библиотеки glut.h
#include <cmath>
#include <stdlib.h>
#include <vector>

#define _USE_MATH_DEFINES

using namespace std;

int x_camera = 0, y_camera = -20, z_camera = 50;
double x_light = 0, y_light = 20, z_light = 4.0;
double camera_angle = (3 * M_PI) / 2;
double light_angle = 0;
double camera_angle_speed = 0.05;
double light_angle_speed = 0.0005;
vector< int > mas;
bool stop_animation = False;

int matrix_model = [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]];

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

/* Функція обробляє повідомлення від клавіатури */
void keyboard_func( unsigned char key, int x1, int y1 ) {
#define ESCAPE '\033'
  switch (key) {
     case ESCAPE:  exit(0);
  }

  if ( key == 'w') {
      my_scale(2, 1, 1);
  }
  if ( key == 's') {
      my_scale(0.5, 1, 1);
  }
  if ( key == 'a') {
      my_rotate(pi/2);
  }
  if ( key == 'd') {
      my_rotate(-pi/2);
  }

  glutPostRedisplay();
}

void func(vector< int > mas) {
  for( int i = 0; i < 10; i++) {
    for( int j = 0; j < 10; j ++) {
      mas.insert(mas.end(), i);
      mas.insert(mas.end(), j);
      mas.insert(mas.end(), sin(i) + cos(j));

      mas.insert(mas.end(), i + 1);
      mas.insert(mas.end(), j);
      mas.insert(mas.end(), sin(i + 1) + cos(j));

      mas.insert(mas.end(), i);
      mas.insert(mas.end(), j + 1);
      mas.insert(mas.end(), sin(i) + cos(j + 1));

      mas.insert(mas.end(), i + 1);
      mas.insert(mas.end(), j + 1);
      mas.insert(mas.end(), sin(i + 1) + cos(j + 1));
    }
  }
}

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

  glEndList();
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

// Function for setting camera and light. Can be used after 
// changeing some parametrs, for example when 
// coordinates of light was changed
void set_camera_and_light(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x_camera, y_camera, z_camera, 0, 0, 0, 0, 1, 0);

    positionLight = [x_light, y_light, z_light, 1.0];
    glLightfv(GL_LIGHT0, GL_POSITION, positionLight);
}

// Function that are used 
// when nothing happend
// the keys are not using and so on
void idf(void) {
    light_angle += light_angle_speed;
    x_light = 20 * cos(light_angle);
    y_light = 20 * sin(light_angle);

    set_camera_and_light();
    glutPostRedisplay();
}

// Function. that are used with some period
void timf() {

}

// This function are read current value of matrix
void read_matrix(void) {

}

// Function for transfer
void my_translate(int x, int y, int z) {

}

// Function for changing scale
void my_scale(int x, int y, int z) {

}

// Function to rotate
void my_rotate(double angle) {
  double mas1 = [[cos(angle), sin(angle), 0, 0], [-sin(angle), cos(angle), 0, 0],
            [0, 0, 1, 0], [0, 0, 0, 1]];
}

// Main loop of application
int main(int argc, char *argv[]) {
  init();
  
  glClearColor(0, 0, 0, 1);

  glutDisplayFunc(display);
  glutIdleFunc(idf);
  glutTimerFunc(40, timf, 0);
  glutKeyboardFunc(keyboard_func);
  glutSpecialFunc(special_keyboard_func);

  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  gluPerspective(40, 1, 1, 400);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  init_camera();
  init_light();

  // func(mas);
  list_of_commands();

  glutMainLoop();
  return 0;
}
