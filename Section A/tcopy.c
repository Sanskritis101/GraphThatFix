#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define MAX_POINTS 10

int v;
float input[3][MAX_POINTS], output[3][MAX_POINTS];
float transl[3][3], scale[3][3], rotate[3][3], reflect[3][3], shear[3][3];

void multiply(float a[3][MAX_POINTS], float b[3][3], float c[3][MAX_POINTS])
{
    int i, j, k;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < v; j++)
        {
            c[i][j] = 0;
            for (k = 0; k < 3; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
}

void getdata()
{
    int i;
    printf("Enter the number of vertices: ");
    scanf("%d", &v);
    printf("Enter the coordinates of vertices (x, y):\n");
    for (i = 0; i < v; i++)
    {
        scanf("%f%f", &input[0][i], &input[1][i]);
        input[2][i] = 1;
    }
}

void translation()
{
    float tx, ty;
    printf("Enter the translation factors (tx, ty): ");
    scanf("%f%f", &tx, &ty);

    transl[0][0] = 1;
    transl[0][1] = 0;
    transl[0][2] = tx;
    transl[1][0] = 0;
    transl[1][1] = 1;
    transl[1][2] = ty;
    transl[2][0] = 0;
    transl[2][1] = 0;
    transl[2][2] = 1;
}

void scaling()
{
    float sx, sy;
    printf("Enter the scaling factors (sx, sy): ");
    scanf("%f%f", &sx, &sy);

    scale[0][0] = sx;
    scale[0][1] = 0;
    scale[0][2] = 0;
    scale[1][0] = 0;
    scale[1][1] = sy;
    scale[1][2] = 0;
    scale[2][0] = 0;
    scale[2][1] = 0;
    scale[2][2] = 1;
}

void rotation()
{
    float angle;
    printf("Enter the rotation angle (in degrees): ");
    scanf("%f", &angle);

    float radian = angle * 3.14159 / 180;
    float cos_theta = cos(radian);
    float sin_theta = sin(radian);

    rotate[0][0] = cos_theta;
    rotate[0][1] = -sin_theta;
    rotate[0][2] = 0;
    rotate[1][0] = sin_theta;
    rotate[1][1] = cos_theta;
    rotate[1][2] = 0;
    rotate[2][0] = 0;
    rotate[2][1] = 0;
    rotate[2][2] = 1;
}

void reflection()
{
    int choice;
    printf("Enter the axis of reflection (1 for x-axis, 2 for y-axis, 3 for origin): ");
    scanf("%d", &choice);

    reflect[0][0] = -1;
    reflect[0][1] = 0;
    reflect[0][2] = 0;
    reflect[1][0] = 0;
    reflect[1][1] = -1;
    reflect[1][2] = 0;
    reflect[2][0] = 0;
    reflect[2][1] = 0;
    reflect[2][2] = 1;

    if (choice == 1)
        reflect[1][1] = 1;
    else if (choice == 2)
        reflect[0][0] = 1;
}

void shearing()
{
    float shx, shy;
    printf("Enter the shearing factors (shx, shy): ");
    scanf("%f%f", &shx, &shy);

    shear[0][0] = 1;
    shear[0][1] = shx;
    shear[0][2] = 0;
    shear[1][0] = shy;
    shear[1][1] = 1;
    shear[1][2] = 0;
    shear[2][0] = 0;
    shear[2][1] = 0;
    shear[2][2] = 1;
}

void Draw()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
    for (i = 0; i < v; i++)
    {
        glVertex2f(output[0][i], output[1][i]);
    }
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    int choice;
    getdata();

    printf("Enter your choice:\n");
    printf("1. Translation\n");
    printf("2. Scaling\n");
    printf("3. Rotation\n");
    printf("4. Reflection\n");
    printf("5. Shearing\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        translation();
        multiply(input, transl, output);

        // Initialize OpenGL window and callbacks
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(0, 0);
        glutInitWindowSize(640, 480);
        glutCreateWindow("2dTransformation");
        glClearColor(0.0, 0.0, 0.0, 0);
        gluOrtho2D(0, 640, 0, 480);
        glutDisplayFunc(Draw);
        glutMainLoop();
    }
    else if (choice == 2)
    {
        scaling();
        multiply(input, scale, output);

        // Initialize OpenGL window and callbacks
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(0, 0);
        glutInitWindowSize(640, 480);
        glutCreateWindow("2dTransformation");
        glClearColor(0.0, 0.0, 0.0, 0);
        gluOrtho2D(0, 640, 0, 480);
        glutDisplayFunc(Draw);
        glutMainLoop();
    }
    else if (choice == 3)
    {
        rotation();
        multiply(input, rotate, output);

        // Initialize OpenGL window and callbacks
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowPosition(0, 
