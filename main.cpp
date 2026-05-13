// #include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

float degreeX = 0;
float degreeY = 0;
float degreeZ = 0;
float scale = 0.5;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void Quads(float x, float y, float z)
{
    glBegin(GL_QUADS);
    float max_x = x + 1.0f;
    float max_y = y + 1.0f;
    float max_z = z + 1.0f;

    // red front
    glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(x, max_y, z);
    glVertex3f(max_x, max_y, z);
    glVertex3f(max_x, y, z);
    glVertex3f(x, y, z);

    // yellow left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(x, max_y, max_z);
    glVertex3f(x, max_y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, max_z);

    // blue back
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(max_x, max_y, max_z);
    glVertex3f(x, max_y, max_z);
    glVertex3f(x, y, max_z);
    glVertex3f(max_x, y, max_z);

    // green right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(max_x, max_y, z);
    glVertex3f(max_x, max_y, max_z);
    glVertex3f(max_x, y, max_z);
    glVertex3f(max_x, y, z);

    // magenta bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(max_x, y, max_z);
    glVertex3f(x, y, max_z);
    glVertex3f(x, y, z);
    glVertex3f(max_x, y, z);

    // cyan top
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(max_x, max_y, z);
    glVertex3f(x, max_y, z);
    glVertex3f(x, max_y, max_z);
    glVertex3f(max_x, max_y, max_z);

    glEnd();
}

static void rubiks_cube()
{

    glPushMatrix();

    const float gap = 0.1f;
    const float step = 1.0f + gap;
    const float span = 3.0f * 1.0f + 2.0f * gap;
    const float base = -span / 2.0f;
    glTranslated(base, base, base);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                Quads(i * step, j * step, k * step);
            }
        }
    }

    glPopMatrix();
}

static void sphare()
{
    glPushMatrix();
    glTranslatef(3.5, 0, 0);
    glutSolidSphere(1.5, 30, 30);
    glPopMatrix();
}

static void circle(float z = 0, float radius = 1, bool is_top = true)
{
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, is_top ? -1 : 1);
    for (int i = 0; i < 360; i++)
    {
        float theta = 2 * 3.1416 * i / 360;
        float x = cos(theta);
        float y = sin(theta);
        glVertex3f(x * radius, y * radius, z);
    }
    glEnd();
}

static void cylinder()
{
    glPushMatrix();

    glTranslatef(-3, 0, 0);
    circle(-1, 0.5);
    circle(1, 0.5, false);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i++)
    {
        float theta = 2 * 3.1416 * i / 360;
        float x = cos(theta);
        float y = sin(theta);
        glColor3f(1, 1, 1);
        glNormal3f(x, y, 0);
        glVertex3f(x * 0.5, y * 0.5, 1);
        glVertex3f(x * 0.5, y * 0.5, -1);
    }
    glEnd();
    glPopMatrix();
}

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3d(1, 0, 0);

    glTranslated(0, 0, -7);

    GLfloat light_position1[] = {-2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat light_diffuse1[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_ambient1[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_specular1[] = {1, 1, 1, 1.0f};
    
    GLfloat light_position2[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat light_diffuse2[] = {1.0f, 1.0f, 0.0f, 1.0f};
    GLfloat light_ambient2[] = {0.2f, 0.2f, 0.0f, 1.0f};
    GLfloat light_specular2[] = {1, 1, 1, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular1);


    glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular2);


    glRotated(degreeX, 1.0, 0.0, 0.0);
    glRotated(degreeY, 0.0, 1.0, 0.0);
    glRotated(degreeZ, 0.0, 0.0, 1.0);
    glScalef(scale, scale, scale);

    glDisable(GL_COLOR_MATERIAL);
    const GLfloat mat_ambient4[] = {0.5f, 0.5f, 0.5f, 1.0f};
    const GLfloat mat_diffuse4[] = {0.5f, 0.5f, 0.5f, 0.6f};
    const GLfloat mat_specular4[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLfloat high_shininess4[] = {100.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess4);

    rubiks_cube();
    sphare();
    cylinder();

    glEnable(GL_COLOR_MATERIAL);

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;

    case 'a':
        degreeX += 2.5;
        break;

    case 'b':
        degreeX -= 2.5;
        break;

    case 'c':
        degreeY += 2.5;
        break;

    case 'd':
        degreeY -= 2.5;
        break;

    case 'e':
        degreeZ += 2.5;
        break;

    case 'f':
        degreeZ -= 2.5;
        break;

    case 'm':
        if (scale < 2.0)
        {
            scale += 0.05;
        }
        break;
    case 'n':
        if (scale > 0.1)
        {
            scale -= 0.05;
        }
    case '0':
        glDisable(GL_LIGHT0);
        break;
    case '1':
        glEnable(GL_LIGHT0);
        break;
    case '7':
        glDisable(GL_LIGHT1);
        break;
    case '8':
        glEnable(GL_LIGHT1);
        break;
    }
    glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{
    const int mods = glutGetModifiers();
    const bool shift = mods == GLUT_ACTIVE_SHIFT;
    switch (key)
    {
    case GLUT_KEY_LEFT:
        glTranslated(-0.05, 0, 0);
        break;
    case GLUT_KEY_RIGHT:
        glTranslated(0.05, 0, 0);
        break;
    case GLUT_KEY_UP:
        if (shift)
        {
            glTranslated(0, 0, -0.05);
        }
        else
        {
            glTranslated(0, 0.05, 0);
        }
        break;
    case GLUT_KEY_DOWN:
        if (shift)
        {
            glTranslated(0, 0, 0.05);
        }
        else
        {
            glTranslated(0, -0.05, 0);
        }
        break;
    }
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{

    cout << "------------- Keyboard Input -------------" << endl;
    cout << "a: Rotate X-axis +2.5 degree" << endl;
    cout << "b: Rotate X-axis -2.5 degree" << endl;
    cout << "c: Rotate Y-axis +2.5 degree" << endl;
    cout << "d: Rotate Y-axis -2.5 degree" << endl;
    cout << "e: Rotate Z-axis +2.5 degree" << endl;
    cout << "f: Rotate Z-axis -2.5 degree" << endl;
    cout << "m: Scale up +0.05" << endl;
    cout << "n: Scale down -0.05" << endl;
    cout << "up/down arrow: Move up/down" << endl;
    cout << "left/right arrow: Move left/right" << endl;
    cout << "shift + up/down arrow: Move forward/backward" << endl;
    cout << "----------------------------------------" << endl;

    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("2023000000202");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutIdleFunc(idle);

    glClearColor(0.3, 0.3, 0.3, 1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glutMainLoop();

    return EXIT_SUCCESS;
}
