#include <GL/glut.h> 
#include "Vector3.h"

#define SURFACE_FROM_X -2
#define SURFACE_FROM_Y -2
#define SURFACE_TO_X 2
#define SURFACE_TO_Y 2
#define SURFACE_STEP 0.1

#define WINDOW_WIDTH 920
#define WINDOW_HEIGHT 720

#define PI 3.1415926
#define ANGLE 6.0

Vector3 cameraPos;

GLfloat lightAngle = 0.0f;
GLfloat lightRadius = 200.0f;

GLfloat scaleShift = 1.0f;
GLfloat translateShift = 0.0f;
GLfloat rotateShift = 0.0f;

/// Обновить размещение источника освещения 
void updateLight()
{
	GLfloat x = lightRadius * cos(lightAngle);
	GLfloat y = 0;
	GLfloat z = lightRadius * sin(lightAngle);

	//(x, y, z) задают вектор направления, а компонента 
	// w всегда равна нулю(иначе источник превратится в точечный)
	GLfloat pos[] = { x, y, z, 0 }; 
	//(x, y, z) - направление прожектора (ось ограничивающего конуса)
	GLfloat direction[] = { 
		-x / lightRadius, 
		-y / lightRadius, 
		-z / lightRadius 
		};

	//Источники направленного света
	glLightfv(GL_LIGHT0, GL_POSITION, pos); 
	//куда будет светить
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction); 
}

/// Поворот фигуры путeм умножения на матрицу поворота 
void rotate(GLfloat angle, Vector3 vector) 
{
	GLfloat x = vector.X();
	GLfloat y = vector.Y();
	GLfloat z = vector.Z();

	GLfloat rotationMatrix[] = {
		cos(angle) + x * x * (1 - cos(angle)),
		x * y * (1 - cos(angle)) - z * sin(angle),
		x * z * (1 - cos(angle)) + y * sin(angle),
		0.0f,

		y * x * (1 - cos(angle)) + z * sin(angle),
		cos(angle) + y * y * (1 - cos(angle)),
		y * z * (1 - cos(angle)) - x * sin(angle),
		0.0f,

		z * x * (1 - cos(angle)) - y * sin(angle),
		z * y * (1 - cos(angle)) + x * sin(angle),
		cos(angle) + z * z * (1 - cos(angle)),
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
		};

	glMultMatrixf(rotationMatrix);
}

/// Скалирование путћм умножения на матрицу скалирования 
void scale(Vector3 vector)
{
	GLfloat x = vector.X();
	GLfloat y = vector.Y();
	GLfloat z = vector.Z();

	GLfloat scaleMatrix[] = {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
		};
	glMultMatrixf(scaleMatrix);
}

/// Смещение путeм умножения на матрицу смещения 
void translate(Vector3 vector)
{
	GLfloat x = vector.X();
	GLfloat y = vector.Y();
	GLfloat z = vector.Z();

	GLfloat translateMatrix[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, y, z, 1
		};
	glMultMatrixf(translateMatrix);
}


/// Создать список фигур 
void setFiguresList(const int listIndex) 
{
	//назване списка, режим компиляции
	glNewList(listIndex, GL_COMPILE);
	{
		//положить в стек текущюю матрицу***
		glPushMatrix(); 
		//умнож текущей матрицы на матрицу перевода (координаты вектора перевода)
		glTranslatef(0, 4, 0); 
		glColor3f(0.345, 0.27, 0.06); // 139 69 19
		//Включается управление свойствами материала(для робот glColor3f)
		glEnable(GL_COLOR_MATERIAL); 
		//Свойства задаются для лицевой стороны поверхности. Одновременное 
		// управление фоновым и рассеянным свойствами отражения. 
		// Значение по умолчанию.
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); 
		glRotated(90, -1.0, 0.0, 0.0);
		glutWireSphere(1.3, 15, 40);
		//вытащить со стека положеную туда матрицу
		glPopMatrix(); 

		glTranslatef(0, 0, 0);
		glColor3d(0.8, 0.36, 0.36); // 205 92 92
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glutSolidTorus(0.5, 1, 8, 8);
		glColor3f(0.545, 0.27, 0.07);
		glutWireTorus(0.5, 1, 8, 8);

		// glColor3d(0.8, 0.31, 0.223); // 205 79 57
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// glutSolidCube(1.0);

		glTranslatef(0, -4, 0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		int _width = (int)((SURFACE_TO_X - SURFACE_FROM_X) / SURFACE_STEP);
		int _height = (int)((SURFACE_TO_Y - SURFACE_FROM_Y) / SURFACE_STEP);
		int _pointsCount = _width * _height;

		// инициализация матрицы высот
		Vector3** _pointsArray = new Vector3*[_height];

		for (int i = 0; i < _height; i++) {
			_pointsArray[i] = new Vector3[_width];

			for (int j = 0; j < _width; j++)
			{
				GLfloat x = SURFACE_FROM_X + j * SURFACE_STEP;
				GLfloat z = SURFACE_FROM_Y + i * SURFACE_STEP;
				GLfloat y = sin(x) + cos(z);

				_pointsArray[i][j].X(x);
				_pointsArray[i][j].Y(y);
				_pointsArray[i][j].Z(z);
			}
		}

		for (int i = 0; i < _height - 1; i++)
		{
			for (int j = 0; j < _width - 1; j++) {
				auto a = _pointsArray[i][j];
				auto b = _pointsArray[i][j + 1];
				auto c = _pointsArray[i + 1][j];
				auto d = _pointsArray[i + 1][j + 1];
				glColor3f(1.0, 0.5, 0.275);//255 130 71

				// отрисовка поверхности
				glBegin(GL_TRIANGLE_STRIP); 
				{
					glVertex3d(a.X(), a.Y(), a.Z());
					glVertex3d(b.X(), b.Y(), b.Z());
					glVertex3d(c.X(), c.Y(), c.Z());
					glVertex3d(d.X(), d.Y(), d.Z());
				}
				glEnd();
				glColor3f(0.8, 0.4, 0.223);//205 104 57

				// отрисовка сетки на поверхности
				glBegin(GL_LINE_LOOP);
				{
					glVertex3d(a.X(), a.Y(), a.Z());
					glVertex3d(b.X(), b.Y(), b.Z());
					glVertex3d(c.X(), c.Y(), c.Z());
				}
				glEnd();

				glBegin(GL_LINE_LOOP);
				{
					glVertex3d(b.X(), b.Y(), b.Z());
					glVertex3d(c.X(), c.Y(), c.Z());
					glVertex3d(d.X(), d.Y(), d.Z());
				}
				glEnd();
			}
		}
		updateLight();
	}
	glEndList();
}

void idle()
{
	// lightAngle -= 0.003;
	cameraPos.Fi(cameraPos.Fi() + 0.05 * PI / 180);
	glutPostRedisplay();
}

/// Отображение фигур 
void display(void)
{
	//очистка буфера rgb цвета и глубины
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	//замена текущей матрицы на единичн !считывает текущую матрицу.
	glLoadIdentity(); 

	setFiguresList(1);

	//указываем какая матрица текущая (матрица проекции ) !команды 
	// относятся к проекту
	glMatrixMode ( GL_PROJECTION ); 
	glLoadIdentity(); 
	//умножаем текущ матрицу на матрицу перспектвы (near 
	// and far відстань між ближн і дальн точками глубини)
	glFrustum ( -1, 1, -1, 1, 1.8, 40); 
	//!команды относятся к просмотру
	glMatrixMode ( GL_MODELVIEW ); 

	Vector3 translateVector(0, translateShift, 0);
	Vector3 rotateVector(0.9f, 0.05f, 0.05f);
	Vector3 scaleVector(scaleShift, scaleShift, scaleShift);

	for (int i = 0; i < 3; i++) {
		glLoadIdentity();
		// координаты позиции глаза налюдателя (вращение камеры)
		gluLookAt(cameraPos.X(), cameraPos.Y(), cameraPos.Z(), 
			// координаты точки, распологающейся в центре экрана
			0.0f, 0.0f, 0.0f, 
			// направление вектора, задающего поворот сцены.
			0.0f, 1.0f, 0.0f); 

		translate(translateVector);
		rotate(2 * rotateShift * PI / 180.0f, rotateVector);
		scale(scaleVector);

		//умнож текущей матрицы на матрицу перевода 
		// (координаты вектора перевода)
		glTranslatef(-4 + 4 * i, 0, 0); 
		glCallList(1);
	}
	//После отрисовки мы переставляем (заменяем) буфера***
	glutSwapBuffers(); 
}

/// Обработка нажатий клавиш 
void special(int key, int x, int y)
{
	Vector3 rotateVector(1.0f, 1.0f, 0.0f);
	switch (key)
	{
		case GLUT_KEY_DOWN:
			if ((cameraPos.Teta() - ANGLE * PI / 180) > 0) { //если угол стенет меньше 0
				cameraPos.Teta(cameraPos.Teta() - ANGLE * PI / 180);
			}
			break;
		case GLUT_KEY_UP:
			if ((cameraPos.Teta() + ANGLE * PI / 180) < PI) {
				cameraPos.Teta(cameraPos.Teta() + ANGLE * PI / 180);
			}
			break;
		case GLUT_KEY_LEFT:
			cameraPos.Fi(cameraPos.Fi() - ANGLE * PI / 180);
			break;
		case GLUT_KEY_RIGHT:
			cameraPos.Fi(cameraPos.Fi() + ANGLE * PI / 180);
			break;
		case GLUT_KEY_F2:
			rotateShift--;
			break;
		case GLUT_KEY_F3:
			rotateShift++;
			break;
		case GLUT_KEY_F4:
			scaleShift /= 1.1f;
			break;
		case GLUT_KEY_F5:
			scaleShift *= 1.1f;
			break;
		case GLUT_KEY_F6:
			translateShift += 0.1f;
			break;
		case GLUT_KEY_F7:
			translateShift -= 0.1f;
			break;
	}
	glutPostRedisplay();
}

/// Точка входа в программу 
int main(int argc, char* argv[])
{
	//иницал библиотеки
	glutInit(&argc, argv); 
	//режим состояния экрана (Окно с двойным буфером|Режим RGB|Окно с буфером глубины)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
	//Установка размеров окна
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); 
	//Открытие окна
	glutCreateWindow("Lab3"); 

	//указывает на функцию, которая будет вызываться системой 
	// всякий раз, когда приложение ничего не делает
	glutIdleFunc(idle); 
	//указывает на функцию, которая будет отвечать за рисование в окне
	glutDisplayFunc(display); 
	//указывает на функцию обратного вызова
	glutSpecialFunc(special); 

	cameraPos.X(12.0f);
	cameraPos.Y(0.0f);
	cameraPos.Z(0.0f);

	//включается буффер глубины 
	glEnable(GL_DEPTH_TEST); 
	// less equal (рисуется все, что имеет глубину, 
	// меньшую или равную текущей)
	glDepthFunc(GL_LEQUAL); 

	//источник направленного света, точечный источник света, прожектор
	//расчет освещения
	glEnable(GL_LIGHTING); 
	//включаем нулевой источник света
	glEnable(GL_LIGHT0); 
	//автоматическое приведение нормалей к единичной длине
	glEnable(GL_NORMALIZE); 

	glClearColor(0.7, 0.4, 0.247, 1); // 205 133 63

	GLfloat mat[] = { 1,1,1,1 };
	//свойства материала отражать различные компоненты 
	// освещения: фоновую, рассеянную и зеркальную
	//Свойства задаются для лицевой стороны поверхности. 
	// цвет зеркального отражения материала
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat); 
	//установка коэффициента блеска (степень в формуле 
	// зеркального отражения (коэффициент блеска). Допускаются 
	// значения в интервале [0; 128].)
	glMaterialf(GL_FRONT, GL_SHININESS, 128.0f); 

	//Начинает основной цикл GLUT обработки событий. 
	// В цикле событий обрабатываются все сообщения клавиатуры, мыши, 
	// таймера, перерисовывания и другие сообщения окна. Функция 
	// не возвращает ничего, пока программа не завершится.
	glutMainLoop(); 
	return 0;
}
