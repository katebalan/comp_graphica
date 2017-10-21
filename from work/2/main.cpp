#include <GL/glut.h>


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClearColor(1, 1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(0, 128, 255);

    glBegin(GL_TRIANGLES);
    glVertex2i(350, 275);
    glVertex2i(450, 275);
    glVertex2i(350, 375);
    glEnd();
   glBegin(GL_TRIANGLES);
    glVertex2i(350, 275);
    glVertex2i(450, 275);
    glVertex2i(450, 175);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(400, 225);
    glVertex2i(350, 175);
    glVertex2i( 450, 175);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i(350, 225);
    glVertex2i(350, 175);
    glVertex2i(400, 225);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2i( 325,  275);
    glVertex2i( 350, 250);
    glVertex2i(350, 300);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2i( 300, 375);
    glVertex2i( 350,  375);
    glVertex2i( 350,  425);
    glVertex2i( 300,  425);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2i( 350,425);
    glVertex2i( 425, 425);
    glVertex2i( 450,  460);
    glVertex2i( 375,  460);
    glEnd();

    glLineWidth(2);   
  glColor3ub(0, 0, 102);

  glBegin(GL_LINE_LOOP);
      glVertex2d(350, 275);
      glVertex2d( 450, 275); 
      glVertex2d( 350, 375);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2d(350, 275);
      glVertex2d(450, 275);
      glVertex2d(450, 175);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2d(400, 225);
      glVertex2d( 350, 175);
      glVertex2d( 450,  175);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2f( 350,  225);
      glVertex2f(350,  175);
      glVertex2f( 400,  225);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2f( 325,  275);
      glVertex2f(350,  250);
      glVertex2f( 350,  300);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2f( 300,  375);
      glVertex2f( 350,  375);
      glVertex2f( 350,  425);
      glVertex2f( 300,  425);
  glEnd();
  glBegin(GL_LINE_LOOP);
      glVertex2f( 350,  425);
      glVertex2f( 425,  425);
      glVertex2f( 450,  460);
      glVertex2f( 375,  460);
  glEnd();

 //glFinish();
glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int xx, int yy) {   

    if (key == 27)
      exit(0);

} 

void OnSpecialKeyPressed(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
     {
      glTranslatef(-5, 0, 0);
      glutPostRedisplay();
    }
    if (key == GLUT_KEY_UP)
    {
        
        glTranslatef(0, 5, 0); 
        glutPostRedisplay();
  
    }
  if (key == GLUT_KEY_RIGHT)
  {
      glTranslatef(5, 0, 0);
      glutPostRedisplay();
  }
  if (key == GLUT_KEY_DOWN)
  {
      glTranslatef(0, -5, 0);
      glutPostRedisplay();
  }
}
int main (int argc, char * argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL lesson 1");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(OnSpecialKeyPressed);

    glutMainLoop();

    return 0;
}