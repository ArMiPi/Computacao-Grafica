#include <GL/glut.h>
#include <cmath>

GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; 	// Posição da luz
GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 }; 			// Cor amarela
GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 }; 			// Cor azul
GLfloat gray[] = { 0.5, 0.5, 0.5, 1.0 }; 			// Cor cinza
GLfloat brown[] = { 0.5, 0.3, 0.1, 1.0 }; 			// Cor marrom
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 }; 			// Cor vermelha

float angulo_terra = 0.0; 			// Ângulo de rotação da Terra
float angulo_lua = 0.0; 			// Ângulo de rotação da Lua
float angulo_mercurio = 0.0; 		// Ângulo de rotação de Mercúrio
float angulo_venus = 0.0; 			// Ângulo de rotação de Vênus
float velocidade_terra = 0.01; 		// Velocidade de rotação da Terra
float velocidade_lua = 0.04; 		// Velocidade de rotação da Lua
float velocidade_mercurio = 0.03; 	// Velocidade de rotação de Mercúrio
float velocidade_venus = 0.02; 		// Velocidade de rotação de Vênus

void drawOrbita(float raio) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; ++i) {
        float angulo = 2.0f * 3.1415926f * float(i) / float(100);
        float x = raio * cosf(angulo);
        float z = raio * sinf(angulo);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Posição da câmera
    gluLookAt(0.0, 60.0, 50.0,  // Posição da câmera (acima do sistema em diagonal)
              0.0, 0.0, 0.0,  	// Ponto de visão (Sol)
              0.0, 0.0, -1.0); 	// Vetor de orientação (para baixo)

    // Configuração da luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Material do Sol
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, yellow);

    // Desenhar o Sol
    glutSolidSphere(4.0, 50, 50);

    // Desenhar as órbitas
    glDisable(GL_LIGHTING); 	// Desabilitar iluminação para desenhar órbitas
    glColor3f(1.0, 1.0, 1.0); 	// Cor branca para as órbitas

    // Órbita da Terra
    drawOrbita(24.0);

    // Órbita de Mercúrio
    drawOrbita(12.0);

    // Órbita de Vênus
    drawOrbita(18.0);

    // Restaurar a iluminação
    glEnable(GL_LIGHTING);
    glPushMatrix();

    // Aplicar transformações para posicionar e rotacionar a Terra
    glTranslatef(24.0 * cos(angulo_terra), 0.0, 24.0 * sin(angulo_terra)); 	// Movimento orbital da Terra
    glRotatef(angulo_terra * 180.0 / 3.14, 0.0, 1.0, 0.0); 					// Rotação da Terra em torno do eixo y
    glScalef(0.6, 0.6, 0.6); 												// Escalar a Terra para 60% do tamanho original

    // Material da Terra
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);

    // Desenhar a Terra
    glutSolidSphere(2.5, 50, 50);

    // Desenhar a órbita da Lua
    glDisable(GL_LIGHTING); 	// Desabilitar iluminação para desenhar órbita
    glColor3f(1.0, 1.0, 1.0); 	// Cor branca para a órbita
    drawOrbita(6.0); 			// Órbita da Lua
    glEnable(GL_LIGHTING); 		// Restaurar a iluminação
    glPushMatrix();

    // Aplicar transformações para posicionar e rotacionar a Lua
    glTranslatef(6.0 * cos(angulo_lua), 0.0, 6.0 * sin(angulo_lua));	// Movimento orbital da Lua
    glRotatef(angulo_lua * 180.0 / 3.14, 0.0, 1.0, 0.0); 				// Rotação da Lua em torno do eixo y
    glScalef(0.4, 0.4, 0.4); 											// Escalar a Lua para 40% do tamanho original

    // Material da Lua
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

    // Desenhar a Lua
    glutSolidSphere(1.2, 50, 50);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    // Aplicar transformações para posicionar e rotacionar Mercúrio
    glTranslatef(12.0 * cos(angulo_mercurio), 0.0, 12.0 * sin(angulo_mercurio)); 	// Movimento orbital de Mercúrio
    glRotatef(angulo_mercurio * 180.0 / 3.14, 0.0, 1.0, 0.0); 						// Rotação de Mercúrio em torno do eixo y
    glScalef(0.7, 0.7, 0.7); 														// Escalar Mercúrio para 70% do tamanho original

    // Material de Mercúrio
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);

    // Desenhar Mercúrio
    glutSolidSphere(1.5, 50, 50);
    glPopMatrix();

    glPushMatrix();
    // Aplicar transformações para posicionar e rotacionar Vênus
    glTranslatef(18.0 * cos(angulo_venus), 0.0, 18.0 * sin(angulo_venus)); 	// Movimento orbital de Vênus
    glRotatef(angulo_venus * 180.0 / 3.14, 0.0, 1.0, 0.0); 					// Rotação de Vênus em torno do eixo y
    glScalef(1.0, 1.0, 1.0); 												// Escalar Vênus para o tamanho original

    // Material de Vênus
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);

    // Desenhar Vênus
    glutSolidSphere(1.8, 50, 50);
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
    angulo_terra += velocidade_terra;
    angulo_lua += velocidade_lua;
    angulo_mercurio += velocidade_mercurio;
    angulo_venus += velocidade_venus;
	
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
