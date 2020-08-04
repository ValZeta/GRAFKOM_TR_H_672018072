#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include "NFG.h"
#include "TGA.h"


int w = 600, h = 600;
static float ypoz = 0, zpoz = 0, xpoz = 0, a = 0, b = 0, c = 0;
static float xScale = 1, yScale = 1, zScale = 1;

float xrot = 0.0f;
float yrot = 180.0f;
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
    }
}

void processSpecialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        b = b + 0.2;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        b = b - 0.2;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        a = a - 0.2;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        a = a + 0.2;
        glutPostRedisplay();
        break;
    }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glClearDepth(1.0f);
    return;
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);

    glPushMatrix();
    glTranslatef(0.0, -1.0, 0.0);
    glTranslatef(a, b, c);

    glScalef(xScale, yScale, zScale);
    glRotatef(xpoz, 1, 0, 0);
    glRotatef(ypoz, 0, 1, 0);
    glRotatef(zpoz, 0, 0, 1);

    glScalef(xScale, yScale, zScale);
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glColor3ub(255, 255, 255);
    float x1 = 0, x2, x3, y1, y2, y3, z1, z2, z3, u1, u2, u3, v1, v2, v3;
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, _textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
        u1 = coorVertex[Sequence[i].i1].u;
        u2 = coorVertex[Sequence[i].i2].u;
        u3 = coorVertex[Sequence[i].i3].u;
        v1 = coorVertex[Sequence[i].i1].v;
        v2 = coorVertex[Sequence[i].i2].v;
        v3 = coorVertex[Sequence[i].i3].v;
        glBegin(GL_POLYGON);
        glTexCoord2f(u1, v1); glVertex3f(x1, y1, z1);
        glTexCoord2f(u2, v2); glVertex3f(x2, y2, z2);
        glTexCoord2f(u3, v3); glVertex3f(x3, y3, z3);
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
    glOrtho(-1.0, 1.0, -1.0, 1.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    if (!mouseDown)
    {
        yrot += 1.0f;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(w, h);
    glutCreateWindow("TR_GRAFKOM_672018072_672018224_672018239");
    init();
    load("Woman1.nfg");
    LoadTGA_custom("Woman1.tga");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutIdleFunc(renderScene);
    glutSwapBuffers();
    glutTimerFunc(1, timer, 0);
    glutMainLoop();
}