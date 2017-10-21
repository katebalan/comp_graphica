#include <stdlib.h>
/* підключаємо бібліотеку GLUT */
#include <gl/glut.h>
/* початкова ширина і висота вікна */
GLint Width = 512, Height = 512;
/* розмір куба */
const int CubeSize = 200;
/* ця функція керує всім виведенням на екран */
void Display(void)
{
int left, right, top, bottom;
left = (Width - CubeSize) / 2;
right = left + CubeSize;
bottom = (Height - CubeSize) / 2;
top = bottom + CubeSize;
glClearColor(0, 0, 0, 1);
glClear(GL_COLOR_BUFFER_BIT);
glColor3ub(255,0,0);
glBegin(GL_QUADS);
glVertex2f(left,bottom);
glVertex2f(left,top);
glVertex2f(right,top);
glVertex2f(right,bottom);
glEnd();
}
glFinish();
/* Функція викликається при зміні розмірів вікна */
void Reshape(GLint w, GLint h)
{
Width = w;Height = h;
/* установлюємо розміри області відображення */
glViewport(0, 0, w, h);
/* ортографічна проекція */
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(0, w, 0, h, -1.0, 1.0);
}
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
/* Функція обробляє повідомлення від клавіатури */
void Keyboard( unsigned char key, int x, int y ) {
	#define ESCAPE '\033'
}glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Red square example");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
if( key == ESCAPE )
	exit(0);

/* Головний цикл додатка */
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("Red square example");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}
