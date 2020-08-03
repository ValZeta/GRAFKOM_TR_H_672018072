#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "NFG.h"

int w = 600, h = 600;
static float ypoz = 0, zpoz = 0, xpoz = 0, a = 0, b = 0, c = 0;
static float xScale = 1, yScale = 1, zScale = 1;

float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
int is_depth;


void idle() {
    if (!mouseDown)
    {
        xrot += 0.3f;
        yrot += 0.4f;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
    }
    else
        mouseDown = false;
}

void mouseMotion(int x, int y) {
    if (mouseDown)
    {
        yrot = x - xdiff;
        xrot = y + ydiff;

        glutPostRedisplay();
    }
}

void myKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        xScale += 0.1;
        yScale += 0.1;
        zScale += 0.1;
        break;
    case 's':
        xScale -= 0.1;
        yScale -= 0.1;
        zScale -= 0.1;
        break;
    case 'x': // X axis
        xpoz = xpoz + 5;
        if (xpoz > 360) xpoz = 0;
        glutPostRedisplay();
        break;
    case 'y': // Y axis
        ypoz = ypoz + 5;
        if (ypoz > 360) ypoz = 0;
        glutPostRedisplay();
        break;
    case 'z': // Z axis
        zpoz = zpoz + 1;
        if (zpoz > 360) zpoz = 0;
        glutPostRedisplay();
        break;
    case 'q': // Zoom in
        c = c + 1;
        glutPostRedisplay();
        break;
    case 'e': // Zoom out
        c = c - 1;
        glutPostRedisplay();
        break;
    }
}

void processSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        b = b + 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        b = b - 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        a = a - 1;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        a = a + 1;
        glutPostRedisplay();
        break;
    }
}

void init() {
    float ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    float specularLight[] = { 0.1f, 0.1f, 0.1f, 2.0f };
    float lampPosition[] = { 0.0f, 1.0f, 0.0f, 1.0f };

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glClearDepth(1.0f);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lampPosition);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    return;
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    glLoadIdentity();
    //gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, -1.0, 0.0);
    glTranslatef(a, b, c);

    //glScalef(xScale, yScale, zScale);
    glRotatef(xpoz, 1, 0, 0);
    glRotatef(ypoz, 0, 1, 0);
    glRotatef(zpoz, 0, 0, 1);

    glScalef(xScale, yScale, zScale);

    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glColor3ub(255, 255, 255);
    float x1 = 0, x2, x3, y1, y2, y3, z1, z2, z3;
    for (int i = 0; i < 718; i++) {

        x1 = coorVertex[Sequence[i].i1].x;
        x2 = coorVertex[Sequence[i].i2].x;
        x3 = coorVertex[Sequence[i].i3].x;
        y1 = coorVertex[Sequence[i].i1].y;
        y2 = coorVertex[Sequence[i].i2].y;
        y3 = coorVertex[Sequence[i].i3].y;
        z1 = coorVertex[Sequence[i].i1].z;
        z2 = coorVertex[Sequence[i].i2].z;
        z3 = coorVertex[Sequence[i].i3].z;
        glBegin(GL_LINE_LOOP);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x3, y3, z3);
        glEnd();
    }
    float d1[] = { 0.2, 0.5, 0.8, 1.0 };
    float d2[] = { 0.3, 0.5, 0.6, 1.0 };
    float d3[] = { 0.4, 0.2, 0.2, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d3);
    glPopMatrix();
    glutSwapBuffers();
}

void resize(int w1, int h1) {
    glViewport(0, 0, w1, h1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45.0, (float)w1 / (float)h1, 1.0, 300.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(w, h);
    glutCreateWindow("TR_GRAFKOM_672018072_672018224_672018239");

    load("Woman1.nfg");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutIdleFunc(renderScene);
    glutSwapBuffers();
    glutTimerFunc(1, timer, 0);

    init();
    glutMainLoop();
}