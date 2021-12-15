#include "FillPolygon.h"
#include <iostream>
#include <vector>
#include <gl\glut.h>

using namespace std;

#define WinW 830
#define WinH 600
#define STEP 50
int scr = 16;

int sign(double a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

void digitalToDecard(int x, int y, int &X, int &Y) {
    if (x > STEP / 2) X = x - STEP / 2;
    else
        X = -(STEP / 2 - x);
    if (y > STEP / 2) Y = -(y - STEP / 2);
    else
        Y = STEP / 2 - y;
}

void drawPixel(int x, int y, int Red, int Green, int Blue) {
    int X, Y;
    digitalToDecard(x, y, X, Y);
    double sizeX = (float) WinW / (float) STEP;
    double sizeY = (float) WinH / (float) STEP;
    glColor3d(Red, Green, Blue);
    glBegin(GL_QUADS);

    double _x = X * sizeX;
    double _y = Y * sizeY;

    glVertex2d(_x, _y);
    glVertex2d(_x + sizeX, _y);
    glVertex2d(_x + sizeX, _y + sizeY);
    glVertex2d(_x, _y + sizeY);
    glEnd();
}

void decardToDigital(int x, int y, int &X, int &Y) {
    X = (STEP / 2 + x);
    Y = (STEP / 2 - y);
}

void drawBrezehamLine(int x1, int x2, int y1, int y2, vector<vector<int>> &field) {
    int x, y, dx, dy, sx, sy;
    int X, Y;
    x = x1, y = y1;
    dx = abs(x2 - x1), dy = abs(y2 - y1);
    sx = sign(x2 - x1), sy = sign(y2 - y1);
    bool swap = false;

    if (dx < dy) {
        std::swap(dx, dy);
        swap = true;
    }
    int eps = 2 * dy - dx;
    if (sx < 0) x += sx;
    if (sy < 0) y += sy;
    for (int i = 0; i <= dx; i++) {
        decardToDigital(x, y, X, Y);
        field[X][Y] = 1;
        while (eps >= 0) {
            if (swap)
                x += sx;
            else
                y += sy;
            eps -= (2 * dx);
        }
        if (swap)
            y += sy;
        else
            x += sx;
        eps += (2 * dy);
    }
}

void fillPolygon(vector<vector<int>> &field) {
    int point;
    bool f;
    for (int i = 0; i <= scr; ++i) {
        f = false;
        for (int j = 0; j < STEP; ++j) {
            if (field[i][j] == 1) {
                if (field[i][j - 1] == 1) {
                    point = j + 1;
                } else {
                    if (f) {
                        if (field[i - 1][point] != 0) {
                            for (int k = point; k < j; ++k) {
                                field[i][k] = 2;
                            }
                        } else {
                            point = j + 1;
                        }
                    } else {
                        point = j + 1;
                        f = !f;
                    }
                }
            }

        }
    }
}

int minX(vector<vector<int>> &coords) {
    int min_x = coords[0][0];
    for (int i = 0; i < coords.size(); i++) {
        if (coords[i][0] < min_x)
            min_x = coords[i][0];
    }
    return min_x + STEP / 2;
}

int maxX(vector<vector<int>> &coords) {
    int max_x = coords[0][0];
    for (int i = 0; i < coords.size(); i++) {
        if (coords[i][0] > max_x)
            max_x = coords[i][0];
    }
    return max_x + STEP / 2;
}

void drawField(vector<vector<int>> &field) {

    for (int i = 0; i < STEP; ++i) {
        for (int j = 0; j < STEP; ++j) {
            if (field[j][i] == 1) {
                drawPixel(i, j, 0, 0, 0);
            }
            if (field[j][i] == 2) {
                drawPixel(i, j, 0, 1, 1);
            }
        }

    }
}

void drawPolygon(vector<vector<int>> &coords, vector<vector<int>> &field) {
    for (int i = 0; i < coords.size() - 1; ++i) {
        drawBrezehamLine(coords[i][0], coords[i + 1][0], coords[i][1], coords[i + 1][1], field);
    }
    drawBrezehamLine(coords[0][0], coords[coords.size() - 1][0], coords[0][1], coords[coords.size() - 1][1], field);
    fillPolygon(field);
}

void drawGrid() {
    glLineWidth(1);
    glColor3d(0, 0, 0);
    for (float i = -STEP; i < STEP; ++i) {
        glBegin(GL_LINES);
        glVertex2d(i * WinW / (float) STEP, -WinH);
        glVertex2d(i * WinW / (float) STEP, WinH);
        glEnd();
    }
    for (float i = -STEP; i < STEP; ++i) {
        glBegin(GL_LINES);
        glVertex2d(-WinW, i * WinH / (float) STEP);
        glVertex2d(WinW, i * WinH / (float) STEP);
        glEnd();
    }

    glLineWidth(3);
    glColor3d(256, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-WinW, 0);
    glVertex2f(WinW, 0);
    glVertex2f(0, WinH);
    glVertex2f(0, -WinH);
    glEnd();
}

void updateData(vector<vector<int>> coords) {
    int min = minX(coords);
    int max = maxX(coords);
    scr++;
    if (scr > max) {
        scr = min;
    }
}

void display() {
    vector<vector<int>> field;
    field.resize(STEP + 1);
    for (int i = 0; i < STEP + 1; ++i) {
        field[i].resize(STEP + 1);
    }
    vector<vector<int>> coords{{-9, 4},
                               {5,  8},
                               {8,  -2},
            // {-8,  -2},
                               {-7, -13},
                               {-6, -1}};

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    drawPolygon(coords, field);
    drawField(field);
    drawGrid();
    updateData(coords);
    glPopMatrix();
    glutSwapBuffers();
}

void timer(int value) {
    value = 0;
    glutPostRedisplay();
    glutTimerFunc(100, timer, value);
}

void reshape(GLsizei Winw, GLsizei Winh) {
    glViewport(0, 0, Winw, Winh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Winw / 2, Winw / 2, -Winh / 2, Winh / 2, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
