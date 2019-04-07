
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include<iostream>

char title[] = "Cube";
GLfloat angleCube = 0.0f;     //angle
int refreshMills =500;
void draw_cube(float, float, float);
void initGL() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	
	// Render a color-cube consisting of 6 quads with different colors
	glLoadIdentity(); 
	// Reset the model-view matrix
	glPushMatrix();
	glTranslated(0, 0, -7);
	//glPushMatrix();
	glRotatef(angleCube, 0.0f,1.0f, 0.0f);
	
	double cube_size = 1;
	double gap = 0.04;
	int n = 3;
	double k = n / 2 * cube_size / 2;
	if (n & 1)
		k = -((n - 1) / 2 * cube_size / 2 + cube_size / 2 );
	else
		k = -(n / 2 * cube_size / 2 );

	double x, y, z,x1,y1,z1;
	x = y = z = k;//std::cout << x << std::endl << y << std::endl << z << std::endl;
	//std::cout << "k " << k << "N" << n << std::endl << std::endl;
	//Generic rubiks cube
	for (int i = 0; i < n; i++) {// step through x axis
		x = k; y = k; if (i != 0) z = z + cube_size;
		for (int j = 0; j < n; j++) {// step through y axis
			x = k;
			if (j != 0)
				y += cube_size;
			for (int k = 0; k < n; k++) // step through z axis
			{
				if (k != 0)
					x += cube_size;
				(x > 0  ) ? x1 = x + gap :(x!=0)?  x1 = x - gap : x1=x;
				(y > 0 ) ? y1 = y + gap : (y!=0)? y1 = y - gap: y1=y;
				z > 0 ? z1 = z + gap :(z!=0)? z1= z - gap :z1=z;
				draw_cube(x1, y1, z1);
				
				std::cout << x1 << std::endl << y1 << std::endl << z1 << std::endl;
			}//std::cout << "\n" << std::endl;
		}
		//std::cout << "\n" << std::endl;
	}

	
	glPopMatrix();
	glutSwapBuffers(); 
	//if (angleCube < 90)
		angleCube += 12.0f;// Swap the front and back frame buffers (double buffering)
	//else
	
		//angleCube = 0.0;
}
void draw_cube(float x, float y, float z)
{

	//vector<cube_rotate> lrot = cube_rotations[x][y][z];
	//glLoadIdentity();
	glPushMatrix();
	 glTranslatef(x,y,z);


	float cube_size = 1.0;
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);  // front
	glNormal3f(0.0, 0.0, 1.0);  // face normal
	glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
	glEnd();

	glColor3f(1.0f, 0.5f, 0.0f);
	glBegin(GL_QUADS);  // back
	glNormal3f(0.0, 0.0, -1.0);  // face normal
	glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);  // left
	glNormal3f(-1.0, 0.0, 0.0);  // face normal 
	glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);  // right
	glNormal3f(1.0, 0.0, 0.0);  // face normal
	glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);  // top
	glNormal3f(0.0, 1.0, 0.0);  // face normal
	glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
	glEnd();

	glColor3f(1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);  // bottom
	glNormal3f(0.0, -1.0, 0.0);  // face normal
	glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
	glEnd();

	glPopMatrix();

}




void timer(int value) {
	glutPostRedisplay();      // Post re-paint request to activate display()
	glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
	//print();

	//gluLookAt(angleCube, angleCube,angleCube+7, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


 

/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);            // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH); // Enable double buffered mode
	glutInitWindowSize(640, 480);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutCreateWindow(title);   
	// Create window with the given title
	glutDisplayFunc(display);       // Register callback handler for window re-paint event
	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
	initGL();                       // Our own OpenGL initialization
	glutTimerFunc(0, timer, 0);
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}