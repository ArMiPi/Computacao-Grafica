#include <GL/glut.h>
#include <cmath>

GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // Posição da luz
GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 }; // Cor amarela RGBA
GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 }; // Cor azul RGBA
GLfloat gray[] = { 0.5, 0.5, 0.5, 1.0 }; // Cor cinza RGBA
GLfloat brown[] = { 0.5, 0.3, 0.1, 1.0 }; // Cor marrom RGBA
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 }; // Cor vermelha RGBA

float angle = 0.0; // Ângulo de rotação da esfera azul
float angle_gray = 0.0; // Ângulo de rotação da esfera cinza
float angle_brown = 0.0; // Ângulo de rotação da esfera marrom
float angle_red = 0.0; // Ângulo de rotação da esfera vermelha
float speed_blue = 0.01; // Velocidade de rotação da esfera azul
float speed_gray = 0.04; // Velocidade de rotação da esfera cinza (reduzida)
float speed_brown = 0.03; // Velocidade de rotação da esfera marrom
float speed_red = 0.02; // Velocidade de rotação da esfera vermelha

void drawOrbit(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; ++i) {
        float angle = 2.0f * 3.1415926f * float(i) / float(100);
        float x = radius * cosf(angle);
        float z = radius * sinf(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Posicionando a câmera acima do sistema
    gluLookAt(0.0, 60.0, 50.0,  // Posição da câmera (acima do sistema)
              0.0, 0.0, 0.0,  // Ponto de visão (esfera amarela)
              0.0, 0.0, -1.0); // Vetor de orientação (para baixo)

    // Configuração da luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Material da esfera amarela
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);

    // Desenhar a esfera amarela
    glutSolidSphere(4.0, 50, 50); // Raio 4.0, 50 slices e 50 stacks

    // Desenhar as órbitas
    glDisable(GL_LIGHTING); // Desabilitar iluminação para desenhar órbitas
    glColor3f(1.0, 1.0, 1.0); // Cor branca para as órbitas

    // Órbita da esfera azul
    drawOrbit(24.0);

    // Órbita da esfera marrom
    drawOrbit(12.0);

    // Órbita da esfera vermelha
    drawOrbit(18.0);

    // Restaurar a iluminação
    glEnable(GL_LIGHTING);

    // Salvar a matriz de transformação atual para a esfera azul
    glPushMatrix();

    // Aplicar transformações para posicionar e rotacionar a esfera azul (filha)
    glTranslatef(24.0 * cos(angle), 0.0, 24.0 * sin(angle)); // Movimento orbital da esfera azul
    glRotatef(angle * 180.0 / 3.14, 0.0, 1.0, 0.0); // Rotação da esfera azul em torno do eixo y
    glScalef(0.6, 0.6, 0.6); // Escalar a esfera azul para 60% do tamanho original

    // Material da esfera azul
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);

    // Desenhar a esfera azul
    glutSolidSphere(2.5, 50, 50); // Raio 2.5, 50 slices e 50 stacks

    // Desenhar a órbita da esfera cinza
    glDisable(GL_LIGHTING); // Desabilitar iluminação para desenhar órbita
    glColor3f(1.0, 1.0, 1.0); // Cor branca para a órbita
    drawOrbit(6.0); // Órbita da esfera cinza
    glEnable(GL_LIGHTING); // Restaurar a iluminação

    // Salvar a matriz de transformação atual para a esfera cinza (neta)
    glPushMatrix();

    // Aplicar transformações para posicionar e rotacionar a esfera cinza (neta)
    glTranslatef(6.0 * cos(angle_gray), 0.0, 6.0 * sin(angle_gray)); // Movimento orbital da esfera cinza
    glRotatef(angle_gray * 180.0 / 3.14, 0.0, 1.0, 0.0); // Rotação da esfera cinza em torno do eixo y
    glScalef(0.4, 0.4, 0.4); // Escalar a esfera cinza para 40% do tamanho original

    // Material da esfera cinza
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

    // Desenhar a esfera cinza
    glutSolidSphere(1.2, 50, 50); // Raio 1.2, 50 slices e 50 stacks

    // Restaurar a matriz de transformação para a esfera cinza
    glPopMatrix();

    // Restaurar a matriz de transformação para a esfera azul
    glPopMatrix();

    // Salvar a matriz de transformação atual para a esfera marrom (filha)
    glPushMatrix();

    // Aplicar transformações para posicionar e rotacionar a esfera marrom (filha)
    glTranslatef(12.0 * cos(angle_brown), 0.0, 12.0 * sin(angle_brown)); // Movimento orbital da esfera marrom
    glRotatef(angle_brown * 180.0 / 3.14, 0.0, 1.0, 0.0); // Rotação da esfera marrom em torno do eixo y
    glScalef(0.7, 0.7, 0.7); // Escalar a esfera marrom para 70% do tamanho original

    // Material da esfera marrom
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);

    // Desenhar a esfera marrom
    glutSolidSphere(1.5, 50, 50); // Raio 1.5, 50 slices e 50 stacks

    // Restaurar a matriz de transformação para a esfera marrom
    glPopMatrix();

    // Salvar a matriz de transformação atual para a esfera vermelha (filha)
    glPushMatrix();

    // Aplicar transformações para posicionar e rotacionar a esfera vermelha (filha)
    glTranslatef(18.0 * cos(angle_red), 0.0, 18.0 * sin(angle_red)); // Movimento orbital da esfera vermelha
    glRotatef(angle_red * 180.0 / 3.14, 0.0, 1.0, 0.0); // Rotação da esfera vermelha em torno do eixo y
    glScalef(1.0, 1.0, 1.0); // Escalar a esfera vermelha para o tamanho original

    // Material da esfera vermelha
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);

    // Desenhar a esfera vermelha
    glutSolidSphere(1.8, 50, 50); // Raio 1.8, 50 slices e 50 stacks

    // Restaurar a matriz de transformação para a esfera vermelha
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
}

void update(int value) {
    angle += speed_blue;
    angle_gray += speed_gray;
    angle_brown += speed_brown;
    angle_red += speed_red;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 800);
    glutCreateWindow("Sistema Solar :)");

    glEnable(GL_DEPTH_TEST);

    GLfloat ambient_light[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();

    return 0;
}
