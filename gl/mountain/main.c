#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

const int ANGLE_STEP = 5;
GLUquadric *quad;
volatile int angle = 0;

void on_display(void);
void on_idle(void);
void on_resize(int width, int height);

void on_alarm(int signo) {
//  on_display();
  glutPostRedisplay();
}

void on_resize(int width, int height) {
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, ((GLfloat)width)/height, 0.01, 15);
  gluLookAt(3, 3, 0, 0, 0, 0, 0, 1, 0);

  glMatrixMode(GL_MODELVIEW);
}

void on_idle(void) {
	volatile int i, j;
	for (i = 0; i < 1000000; ++i)
	    for (j = 0; j < 10; ++j);
	glutPostRedisplay();
}

void on_display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(0.3, 0.9, 0.1);
  glLoadIdentity();
  glRotatef(angle, 1, 1, 1);

  gluCylinder(quad, 0.5, 0.5, 1, 30, 30);
  //  glutSolidTeapot(0.3);

  /*  glBegin(GL_TRIANGLE_STRIP);
  glVertex3f(1, 0, 0);
  glVertex3f(1, 1, 0);
  glVertex3f(0, 0, 0);
  glEnd();
  */
  glFinish();
  glutSwapBuffers();
  angle = (angle + ANGLE_STEP) % 360;
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowSize(640, 480);	
  glutInitWindowPosition(0, 0);	
  glutCreateWindow("My OpenGL Application");	
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	
  glutDisplayFunc(on_display);
  glutIdleFunc(on_idle);
  glutReshapeFunc(on_resize);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  quad = gluNewQuadric();
  {
    struct itimerval mytimer = {0};
    mytimer.it_value.tv_usec = 0.1 * 1e6;
    mytimer.it_interval.tv_usec = 0.25 * 1e6;
    /*signal(SIGALRM, on_alarm);
    setitimer(ITIMER_REAL, &mytimer, NULL); */
  }
  glutMainLoop();
  gluDeleteQuadric(quad);
  return 0;
}
