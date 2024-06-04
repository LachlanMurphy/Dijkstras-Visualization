#ifndef LGRAPH_H
#define LGRAPH_H

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define PI     3.141592654
#define TWO_PI 6.283185307

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

extern int mousex;
extern int mousey;

void size(int w, int h);

void display();
void setup();
void onExit();
void keypressed(unsigned char c, int x, int y);
void mouseUpdate(int button, int mouse_up, int x, int y);

static void drive() {
    // clear screen and z buffer
    glClear(GL_COLOR_BUFFER_BIT);

    display();

    // flush and swap buffers
    glFlush();
    glutSwapBuffers();
    glutTimerFunc(1000.0f/60.0f, drive, 0); // 60fps
}

void update_mouse_pos(int x, int y);

void l_init(int* argc, char* argv[]);

void l_color(unsigned char red,
                    unsigned char green,
                    unsigned char blue,
                    unsigned char alpha);

void l_line(float x1, float y1, float x2, float y2);

void l_circle(float cx, float cy, float r);

void l_arc(int cx, int cy, float r, float start_angle, float end_angle);

double dis(double x1, double y1, double x2, double y2);

int main(int argc, char* argv[]);

#endif // LGRAPH_H