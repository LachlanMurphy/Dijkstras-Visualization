#ifndef LGRAPH_H
#define LGRAPH_H

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define PI     3.141592654
#define TWO_PI 6.283185307

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

void size(int w, int h);

void display();
void setup();
void onExit();

static void drive() {
    display();
    glFlush();
    glutSwapBuffers();
    glutTimerFunc(1000.0f/60.0f, drive, 0); // 60fps
}

void l_init(int* argc, char* argv[]);

void l_color(unsigned char red,
                    unsigned char green,
                    unsigned char blue,
                    unsigned char alpha);

void l_line(float x1, float y1, float x2, float y2);

void l_circle(float cx, float cy, float r);

void l_arc(int cx, int cy, float r, float start_angle, float end_angle);

int main(int argc, char* argv[]);

#endif // LGRAPH_H