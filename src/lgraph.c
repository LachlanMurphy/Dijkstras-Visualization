#include "lgraph.h"

unsigned int WIDTH = 0;
unsigned int HEIGHT = 0;

void size(int w, int h) {
    WIDTH = w;
    HEIGHT = h;
}

void l_init(int* argc, char* argv[]) {
    glutInit(argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello World");
    glutDisplayFunc(drive);
    atexit(onExit);
    
    // make 0,0 top left and y increase down
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, 0.0f, 1.0);
    // glScalef(1.f, -1.f, 1.f);

    glutMainLoop();
}

void l_color(unsigned char red,
                    unsigned char green,
                    unsigned char blue,
                    unsigned char alpha)
{
    glColor4ub(red, green, blue, alpha);
}

void l_line(float x1, float y1, float x2, float y2) {
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}



void l_circle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int ii = 0; ii <= 60; ii++)   {
        float theta = TWO_PI * (float) ii / (float)60;//get the current angle 
        float x = r * cosf(theta);//calculate the x component 
        float y = r * sinf(theta);//calculate the y component 
        glVertex2f(x + cx, y + cy);//output vertex 
    }
    glEnd();
}

void l_arc(int cx, int cy, float r, float start_angle, float end_angle) {
    glBegin(GL_LINE_STRIP);
    float da = (end_angle - start_angle) / 60;
    for (float a = start_angle; a <= end_angle; a += da) {
        float x = r * cosf(a);
        float y = r * sinf(a);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}



int main(int argc, char* argv[])
{
    setup();
    l_init(&argc, argv);
}