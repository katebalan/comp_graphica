#include <GL/glut.h>
#include <math.h>

using namespace std;

/* початкова ширина і висота вікна */
//GLint Width = 700, Height = 700;

GLint X = 0, Y = 0;

//Ключи статуса камеры. Переменные инициализируются нулевыми значениями
//когда клавиши не нажаты
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

/* ця функція керує всім виведенням на екран */
void Display(void) {

  glClearColor(1, 1, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);
    
  glColor3ub(0, 128, 255);

  glBegin(GL_TRIANGLES);
      glVertex2i(X + 350, Y + 275);
      glVertex2i(X + 450, Y + 275);
      glVertex2i(X + 350, Y + 375);
  glEnd();
  glBegin(GL_TRIANGLES);
      glVertex2i(X + 350, Y + 275);
      glVertex2i(X + 450, Y + 275);
      glVertex2i(X + 450, Y + 175);
  glEnd();
  glBegin(GL_TRIANGLES);
      glVertex2i(X + 400, Y + 225);
      glVertex2i(X + 350, Y + 175);
      glVertex2i(X + 450, Y + 175);
  glEnd();
  glBegin(GL_TRIANGLES);
      glVertex2i(X + 350, Y + 225);
      glVertex2i(X + 350, Y + 175);
      glVertex2i(X + 400, Y + 225);
  glEnd();
  glBegin(GL_TRIANGLES);
      glVertex2i(X + 325, Y + 275);
      glVertex2i(X + 350, Y + 250);
      glVertex2i(X + 350, Y + 300);
  glEnd();
  glBegin(GL_QUADS);
      glVertex2i(X + 300, Y + 375);
      glVertex2i(X + 350, Y + 375);
      glVertex2i(X + 350, Y + 425);
      glVertex2i(X + 300, Y + 425);
  glEnd();
  glBegin(GL_QUADS);
      glVertex2i(X + 350, Y + 425);
      glVertex2i(X + 425, Y + 425);
      glVertex2i(X + 450, Y + 460);
      glVertex2i(X + 375, Y + 460);
  glEnd();

  glLineWidth(2);   
  glColor3ub(0, 0, 102);

  glBegin(GL_LINE_LOOP);
      glVertex2d(X + 350, Y + 275);
      glVertex2d(X + 450, Y + 275); 
      glVertex2d(X + 350, Y + 375);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2d(X + 350, Y + 275);
      glVertex2d(X + 450, Y + 275);
      glVertex2d(X + 450, Y + 175);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2d(X + 400, Y + 225);
      glVertex2d(X + 350, Y + 175);
      glVertex2d(X + 450, Y + 175);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2f(X + 350, Y + 225);
      glVertex2f(X + 350, Y + 175);
      glVertex2f(X + 400, Y + 225);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2f(X + 325, Y + 275);
      glVertex2f(X + 350, Y + 250);
      glVertex2f(X + 350, Y + 300);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2f(X + 300, Y + 375);
      glVertex2f(X + 350, Y + 375);
      glVertex2f(X + 350, Y + 425);
      glVertex2f(X + 300, Y + 425);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2f(X + 350, Y + 425);
      glVertex2f(X + 425, Y + 425);
      glVertex2f(X + 450, Y + 460);
      glVertex2f(X + 375, Y + 460);
  glEnd();

  glFinish();

  glutSwapBuffers();
}

/* Функція викликається при зміні розмірів вікна */
void Reshape(GLint w, GLint h)  {
    // предотвращение деления на ноль


    /* установлюємо розміри області відображення */
    // установить параметры вьюпорта
     glViewport(0, 0, w, h);   

    // используем матрицу проекции
    glMatrixMode(GL_PROJECTION);
    // обнуляем матрицу
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

    void reshape(int w, int h)
    {
            glViewport(0, 0, w, h);
           
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluOrtho2D(0, w, 0, h);
           
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
    }



void processNormalKeys(unsigned char key, int xx, int yy) {   
 
        if (key == 27)
              exit(0);

} 
 
void pressKey(int key, int xx, int yy) {
 
       switch (key) {
            case GLUT_KEY_UP : 
              if(Y < 240) {
                Y += 10;
              }
              break;
            case GLUT_KEY_DOWN : 
              if(Y > -175) {
                Y -= 10;
              } 
              break;
            case GLUT_KEY_LEFT :
              if(X > -300) {
                X-=10;
              } 
              break;
            case GLUT_KEY_RIGHT :
              if(X < 250) { 
                X += 10; 
              } 
              break;
       }
       glutPostRedisplay();
} 

/* Головний цикл додатка */
int main(int argc, char *argv[]) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);

  glutInitWindowSize (700, 700); 
  glutInitWindowPosition (0, 0);

  glutCreateWindow("OLololoLLOL");

  glutReshapeFunc(reshape);
  glutDisplayFunc(Display);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(pressKey);

  glutMainLoop();

 return 0;
}
