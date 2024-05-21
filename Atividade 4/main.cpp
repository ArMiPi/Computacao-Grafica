#include <GL/glut.h>
#include <iostream>

// Variáveis para controlar a posição, rotação e escala do objeto
float translateX = 0.0f;
float translateY = 0.0f;
float rotationAngle = 0.0f;
float scaleFactor = 1.0f;

void display() {
    // Limpar o buffer de cor
    glClear(GL_COLOR_BUFFER_BIT);

    // Configurar a matriz de modelo
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Aplicar as transformações
    glTranslatef(translateX, translateY, 0.0f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
    glScalef(scaleFactor, scaleFactor, 1.0f);

    // Desenhar o objeto (neste exemplo, um quadrado)
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    // Trocar os buffers
    glutSwapBuffers();
}

void reshape(int w, int h) {
    // Configurar a viewport
    glViewport(0, 0, w, h);

    // Configurar a projeção ortogonal
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
        rotationAngle -= 5.0f;
        break;
    case 'd':
        rotationAngle += 5.0f;
        break;
    case 'w':
        scaleFactor += 0.1f;
        break;
    case 's':
        scaleFactor -= 0.1f;
        break;
    }

    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        translateX -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        translateX += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        translateY -= 0.1f;
        break;
    case GLUT_KEY_UP:
        translateY += 0.1f;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // Inicializar GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Transformations");

    // Registrar as funções de callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    // Configurar o fundo da janela
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Iniciar o loop de eventos GLUT
    glutMainLoop();

    return 0;
}

