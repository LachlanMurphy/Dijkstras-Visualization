#include "lgraph.h"

unsigned int WIDTH = 0;
unsigned int HEIGHT = 0;

int mousex = 0;
int mousey = 0;

void size(int w, int h) {
    WIDTH = w;
    HEIGHT = h;
}

void l_init(int* argc, char* argv[]) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello World");
    glutDisplayFunc(drive);
    glutKeyboardFunc(keypressed);
    glutKeyboardUpFunc(keyup);
    glutMouseFunc(mouseUpdate);
    // glClearColor(0.5, 0.5, 0.5, 0);

    // update mouse position when mouse is not pressed and when it is pressed
    glutPassiveMotionFunc(update_mouse_pos);
    glutMotionFunc(update_mouse_pos);

    // runs when the program terminates
    atexit(onExit);
    
    // make 0,0 top left and y increase down
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, 0.0f, 1.0);
    // glScalef(1.f, -1.f, 1.f);

    glutMainLoop();
}

void update_mouse_pos(int x, int y) {
    mousex = x;
    mousey = y;
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

void l_background(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
}

// printing text
void l_text(float x, float y, char *format,...) {
    va_list args;
    char buffer[200], *p;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    glPushMatrix();
    int str_width = 0;
    int str_height = glutStrokeHeight(GLUT_STROKE_MONO_ROMAN);
    for (p = buffer; *p; p++) {
        str_width += glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, *p);\
    }
    glTranslatef(x-str_width*0.3/2, y+str_height*0.3/2, 0);
    glScalef(0.3, -0.3, 0.3);
    for (p = buffer; *p; p++)
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);
    glPopMatrix();
}


// support functions
double dis(double x1, double y1, double x2, double y2) {
    double square_difference_x = (x2 - x1) * (x2 - x1);
    double square_difference_y = (y2 - y1) * (y2 - y1);
    double sum = square_difference_x + square_difference_y;
    double value = sqrt(sum);
    return value;
}