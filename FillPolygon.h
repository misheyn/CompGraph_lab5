#ifndef COMPGRAPH_LAB5_FILLPOLYGON_H
#define COMPGRAPH_LAB5_FILLPOLYGON_H

#include <GL/gl.h>
#include <vector>

using namespace std;

int sign(double a);

void drawPixel(int x, int y, int Red, int Green, int Blue);

void drawField(vector<vector<int>> &field);

void drawBrezehamLine(int x1, int x2, int y1, int y2, vector<vector<int>> &field);

void drawPolygon(vector<vector<int>> &coords, vector<vector<int>> &field);

void drawGrid();

void digitalToDecard(int x, int y, int &X, int &Y);

void decardToDigital(int x, int y, int &X, int &Y);

int maxX(vector<vector<int>> &coords);

int minX(vector<vector<int>> &coords);

void fillPolygon(vector<vector<int>> &field);

void timer(int value);

void display();

void reshape(GLsizei Winw, GLsizei Winh);

#endif //COMPGRAPH_LAB5_FILLPOLYGON_H
