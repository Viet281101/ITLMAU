
#include <GL/glut.h>

#define BOARD_SIZE 8
#define CELL_SIZE 50

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            // Choose colors for board
            if ((x + y) % 2 == 0) {
                glColor3f(1.0, 1.0, 1.0); // White
            } else {
                glColor3f(0.0, 0.0, 0.0); // Black
            }

            // Draw the chessboard squares
            glRecti(x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE);
        }
    }

    // draw othello chess pieces

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, BOARD_SIZE * CELL_SIZE, 0.0, BOARD_SIZE * CELL_SIZE);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Othello Game");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}