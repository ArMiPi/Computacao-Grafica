//
//  projecao2d.cpp
//  opengl_aula1
//
//  Created by Gilberto Fernandes Junior on 20/04/23.
//  Updated by Arthur Miasato Pimont


#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void myInit(void);
void myDisplay(void);
void idleFunc();

GLfloat panX = 0.0f;
GLfloat panX_step = 0.15f;
GLfloat panY = 0.0f;
GLfloat panY_step = 0.15f;
GLfloat zoom = 1.0f;
GLfloat zoom_step = 0.005f;


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Transformações 2D");
    
    myInit();
    
    glutDisplayFunc(myDisplay);
    glutIdleFunc(idleFunc);

    glutMainLoop();
}


void myInit(void) {
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4.0);
    glLineWidth(2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, 2.0, 0, 2.0); // esq / dir / baixo / cima
    glPushMatrix();
}


void desenhaTriangulo() {
    glBegin(GL_TRIANGLES);
        glVertex2i(0, 50);
        glVertex2i(50, -50);
        glVertex2i(-50, -50);
    glEnd();
}

void desenhaMoldura() {
    glBegin(GL_LINE_LOOP);
        glVertex2f(-100, 100);
        glVertex2f(100, 100);
        glVertex2f(100, -100);
        glVertex2f(-100, -100);
    glEnd();
}

void idleFunc() {
    if(panX > 50 || panX < -50)
        panX_step = -panX_step;
    panX += panX_step;

    if(panY > 50 || panY < -50)
        panY_step = -panY_step;
    panY += panY_step;

    if(zoom > 2.0f || zoom < 0.5f)
        zoom_step = -zoom_step;
    zoom += zoom_step;
    
    glutPostRedisplay();
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT); //desenha o fundo (limpa a janela)
    
    glMatrixMode(GL_PROJECTION);
    
    //1a janela glOrtho2D(xw_min, xw_max, yw_min, yw_max) = (-100, 100, -100, 10) | sist. de coordenadas do mundo (-oo,oo,-oo,oo) | sist. de coordenadas da janela (0,400, 0,600)
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(0, 300, 300, 300);
    glColor3f(1.0f, 0.0f, 0.0f);
    desenhaTriangulo();

    // 2a janela
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(300 + panX, 300, 300, 300);
    glColor3f(0.0f, 1.0f, 0.0f);
    desenhaTriangulo();

    // 3a janela
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    glViewport(0, 0 + panY, 300, 300);
    glColor3f(0.0f, 0.0f, 1.0f);
    desenhaTriangulo();

    // 4a janela
    glLoadIdentity();
    gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
    
    int baseViewportSize = 300;
    int newViewportSize = int(baseViewportSize / zoom);
    int viewportX = 300 + (baseViewportSize - newViewportSize) / 2;
    int viewportY = (baseViewportSize - newViewportSize) / 2;
    
    glViewport(viewportX, viewportY, newViewportSize, newViewportSize);
    glColor3f(1.0f, 0.0f, 1.0f);
    desenhaTriangulo();
    
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
    glViewport(0, 0, 600, 600);
    // GL_MODELVIEW utilizada para aplicar transformações geométricas às coorden dos objetos
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();

    glColor3f(0.0f, 0.0f, 0.0f);
    // Seção 3
    glTranslatef(-100, -100, 0);
    desenhaMoldura();

    // Seção 4
    glLoadIdentity ();
    glTranslatef(100, -100, 0);
    desenhaMoldura();

    // Seção 1
    glLoadIdentity ();
    glTranslatef(-100, 100, 0);
    desenhaMoldura();

    // Seção 2
    glLoadIdentity ();
    glTranslatef(100, 100, 0);
    desenhaMoldura ();

    glLoadIdentity();
    
    glutSwapBuffers();
    glFlush();
}

