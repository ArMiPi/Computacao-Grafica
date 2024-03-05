/**
 * Programa que:
 *  - Desenha traços na tela ao clicar e arrastar o mouse
 *  - Cria um menu com o botão direito do mouse com opções para o desenho
 *      - 3 cores diferentes
 *      - 3 espessuras para o traçado
 *  - Tecla D limpa a tela
 *  - Opção borracha no menu
*/
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

enum Color { RED, GREEN, BLUE, ERASER };

Color currentColor;
float pointSize;

void drawPoint(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void setDrawingColor(Color color) {
    switch (color) {
        case RED:
            glColor3f(1.0, 0.0, 0.0);
            break;
        case GREEN:
            glColor3f(0.0, 1.0, 0.0);
            break;
        case BLUE:
            glColor3f(0.0, 0.0, 1.0);
            break;
        case ERASER:
            glColor3f(0.0, 0.0, 0.0);
            break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    currentColor = RED;
    pointSize = 4.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void mouseFunc(GLint button, GLint state, GLint x, GLint y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        setDrawingColor(currentColor);
        glPointSize(pointSize);
    }
}

void motionFunc(GLint x, GLint y) {
    y = 480 - y;
    drawPoint(x, y);
    glutSwapBuffers();
}

void colorMenuFunc(GLint op) {
    switch (op) {
        case 0:
            currentColor = RED;
            break;
        case 1:
            currentColor = GREEN;
            break;
        case 2:
            currentColor = BLUE;
        default:
            break;
    }
}

void pointSizeMenuFunc(GLint op) {
    switch (op) {
        case 4:
            pointSize = 4.0;
            break;
        case 8:
            pointSize = 8.0;
            break;
        case 10:
            pointSize = 10.0;
            break;
        default:
            break;
    }
}

void menuFunc(GLint op) {
    switch (op) {
    case 2:
        currentColor = ERASER;
        break;
    default:
        break;
    }
}

void keyboardFunc(unsigned char key, GLint x, GLint y) {
    if (key == 'd') {
        display();
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Paint (beta)");
    
    init();
    glutDisplayFunc(display);

    glutMouseFunc(mouseFunc);
    glutMotionFunc(motionFunc);
    glutKeyboardFunc(keyboardFunc);

    GLint colorMenu = glutCreateMenu(colorMenuFunc);
    glutAddMenuEntry("Vermelho", RED);
    glutAddMenuEntry("Verde", GREEN);
    glutAddMenuEntry("Azul", BLUE);

    GLint pointSizeMenu = glutCreateMenu(pointSizeMenuFunc);
    glutAddMenuEntry("Pequeno", 4);
    glutAddMenuEntry("Medio", 8);
    glutAddMenuEntry("Grande", 10);

    GLint mainMenu = glutCreateMenu(menuFunc);
    glutAddSubMenu("Cor", colorMenu);
    glutAddSubMenu("Tracado", pointSizeMenu);
    glutAddMenuEntry("Eraser", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}