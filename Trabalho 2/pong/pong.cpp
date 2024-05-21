#include <GL/glut.h>
#include <iostream>

// Tamanho da janela
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Tamanho dos paddles
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 100;

// Posições iniciais dos paddles
float LEFT_PADDLE_Y = (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2;
float RIGHT_PADDLE_Y = (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2;

// Posição e velocidade da bola
float BALL_X = WINDOW_WIDTH / 2;
float BALL_Y = WINDOW_HEIGHT / 2;
float BALL_SPEED_X = 3;
float BALL_SPEED_Y = 3;
const int BALL_SIZE = 10;

// Pontuações dos jogadores
int LEFT_SCORE = 0;
int RIGHT_SCORE = 0;

unsigned int FPS = int(1000 / 60);


// Função para desenhar um paddle
void drawPaddle(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + PADDLE_WIDTH, y);
    glVertex2f(x + PADDLE_WIDTH, y + PADDLE_HEIGHT);
    glVertex2f(x, y + PADDLE_HEIGHT);
    glEnd();
}

// Função para desenhar a bola
void drawBall(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + BALL_SIZE, y);
    glVertex2f(x + BALL_SIZE, y + BALL_SIZE);
    glVertex2f(x, y + BALL_SIZE);
    glEnd();
}

// Função para desenhar uma linha pontilhada
void drawMiddleLine(float x, float y1, float y2) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
    glBegin(GL_LINES);
    glVertex2f(x, y1);
    glVertex2f(x, y2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

// Função para desenhar texto na tela
void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// Função de display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Desenha os paddles
    drawPaddle(10, LEFT_PADDLE_Y);
    drawPaddle(WINDOW_WIDTH - 20, RIGHT_PADDLE_Y);
    
    // Desenha a bola
    drawBall(BALL_X, BALL_Y);

    // Desenha a linha do meio
    drawMiddleLine(WINDOW_WIDTH/2, 0, WINDOW_HEIGHT);

    // Desenha o placar
    std::string left_score_str = std::to_string(LEFT_SCORE);
    std::string right_score_str = std::to_string(RIGHT_SCORE);
    drawText(WINDOW_WIDTH/2 - 50, WINDOW_HEIGHT - 30, left_score_str.c_str());
    drawText(WINDOW_WIDTH/2 + 30, WINDOW_HEIGHT - 30, right_score_str.c_str());
    
    glutSwapBuffers();
}

// Função de atualização
void update(int value) {
    // Move a bola
    BALL_X += BALL_SPEED_X;
    BALL_Y += BALL_SPEED_Y;
    
    // Verifica colisão com as bordas superior e inferior
    if (BALL_Y <= 0 || BALL_Y + BALL_SIZE >= WINDOW_HEIGHT) {
        BALL_SPEED_Y = -BALL_SPEED_Y;
    }
    
    // Verifica colisão com as paddles
    if (BALL_X <= 20 && BALL_Y >= LEFT_PADDLE_Y && BALL_Y <= LEFT_PADDLE_Y + PADDLE_HEIGHT) {
        BALL_SPEED_X = -BALL_SPEED_X;
    }
    if (BALL_X + BALL_SIZE >= WINDOW_WIDTH - 20 && BALL_Y >= RIGHT_PADDLE_Y && BALL_Y <= RIGHT_PADDLE_Y + PADDLE_HEIGHT) {
        BALL_SPEED_X = -BALL_SPEED_X;
    }
    
    // Verifica se a bola saiu pela esquerda ou direita
    if (BALL_X <= 0) {
        // Jogador direito marca ponto
        RIGHT_SCORE++;
        // Reinicia a posição da bola
        BALL_X = WINDOW_WIDTH/2;
        BALL_Y = WINDOW_HEIGHT/2;
    }
    if (BALL_X + BALL_SIZE >= WINDOW_WIDTH) {
        // Jogador esquerdo marca ponto
        LEFT_SCORE++;
        // Reinicia a posição da bola
        BALL_X = WINDOW_WIDTH/2;
        BALL_Y = WINDOW_HEIGHT/2;
    }
    
    // Redesenha a tela
    glutPostRedisplay();
    glutTimerFunc(FPS, update, 0);
}

// Função de reset do jogo
void resetGame() {
    // Reinicia a posição das raquetes
    LEFT_PADDLE_Y = (WINDOW_HEIGHT - PADDLE_HEIGHT)/2;
    RIGHT_PADDLE_Y = (WINDOW_HEIGHT - PADDLE_HEIGHT)/2;

    // Reinicia a posição e velocidade da bola
    BALL_X = WINDOW_WIDTH/2;
    BALL_Y = WINDOW_HEIGHT/2;
    BALL_SPEED_X = 3;
    BALL_SPEED_Y = 3;

    // Reinicia as pontuações
    LEFT_SCORE = 0;
    RIGHT_SCORE = 0;
}

// Função de teclado
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            if (LEFT_PADDLE_Y + PADDLE_HEIGHT < WINDOW_HEIGHT) {
                LEFT_PADDLE_Y += 20;
            }
            break;
        case 's':
            if (LEFT_PADDLE_Y > 0) {
                LEFT_PADDLE_Y -= 20;
            }
            break;
        case 'r':
            resetGame();
            break;
    }
}

// Função de teclas especiais (setas)
void handleSpecialKeypress(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            if (RIGHT_PADDLE_Y + PADDLE_HEIGHT < WINDOW_HEIGHT) {
                RIGHT_PADDLE_Y += 20;
            }
            break;
        case GLUT_KEY_DOWN:
            if (RIGHT_PADDLE_Y > 0) {
                RIGHT_PADDLE_Y -= 20;
            }
            break;
    }
}

// Função de inicialização
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT);
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Pong");

    init();
    
    glutDisplayFunc(display);
    glutTimerFunc(FPS, update, 0);
    glutKeyboardFunc(handleKeypress);
    glutSpecialFunc(handleSpecialKeypress);
    
    glutMainLoop();
    return 0;
}
