
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include<iostream>
#include<vector>

/*stuff to do
make simulatenous face rotations possible use quaternions or something
make it presentable
bfs
*/

struct cube {

	GLfloat  x, y, z;

};
void draw_cube(float, float, float);

double cube_size = 1;
double gap = 0.04;
int n = 0;
double minValue;
char title[] = "Cube";
int refreshMills = 500;
char selector = ' ';
float selector_value ;
int rotX = 0,rotY=0;
int angle;
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
	glLoadIdentity(); 
	double x, y, z;
	if (n & 1)
		minValue = -((n - 1) / 2 * cube_size);
	else
		minValue = -(n / 2 * cube_size - cube_size / 2);
	int count = 0;

	glTranslated(0, 0, -10);
	glPushMatrix();
	glRotatef(rotX, 1.0, 0.0, 0.0); // rotate in y axis
	glRotatef(rotY, 0.0, 1.0, 0.0); // rotate in x axis

	

	

		
		//Generic rubiks cube
	for (float i = minValue; i <= (-1*minValue) ; i+=cube_size) {// step through x axis
				
		for (float j = minValue; j <=(-1*minValue); j+=cube_size) {// step through y axis

										
			for (float k = minValue; k <=(-1*minValue); k+=cube_size) // step through z axis
			{
				
				x = i+ i * gap;
				y = (j) + j* gap;
				z = (k) + k * gap;
				glPushMatrix();
		
				switch (selector)
				{
				case 'i': if (i == selector_value) glRotatef(angle, 1, 0, 0); break;
				case 'j': if (j == selector_value) glRotatef(angle, 0, 1, 0); break;
				case 'k': if (k ==  selector_value) glRotatef(angle, 0, 0, 1); break;
					
				}

				

				draw_cube(x, y, z);

				glPopMatrix();
				//std::cout << x<< std::endl << y<< std::endl << z<< std::endl;
			}
		}
		
		
	}

	
	
	//glPushMatrix();
	//glRotatef(angleCube, 0, 0, 1);
	//draw_cube(-0.75, 0.75, -10.0);
	//glPopMatrix()
	//glRotatef(angleCube, 0, 1, 0);
	/*for (int i = 0; i < 3; i++)
	{
		x = k;
		if (i!= 0)
			y += cube_size;

		for (int j = 0; j < 3; j++)
		{
			if (j != 0)
				x += cube_size;
			(x > 0) ? x1 = x + gap : (x != 0) ? x1 = x - gap : x1 = x;
			(y > 0) ? y1 = y + gap : (y != 0) ? y1 = y - gap : y1 = y;
			//draw_cube(x1, k+1, y1);
		}
	}*/
	//glRotatef(angleCube, 1, 1, 1);
	
	glutSwapBuffers(); 
	//if (angleCube < 90)
		// Swap the front and back frame buffers (double buffering)
	//else
		
	//angle+ =12 ;
		glPopMatrix();
		
}

void print()
{
	std::vector<cube> a[3][3][3];
		
		for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			

		}
	}

}

void draw_cube(float x, float y, float z)
{

	//vector<cube_rotate> lrot = cube_rotations[x][y][z];
	//glLoadIdentity();
	glPushMatrix();
	 glTranslatef(x,y,z);
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


void keyboardFunc(unsigned char key, int x, int y)
{

	switch (key) {

	case '1':
		n = 2;
		break;

	case '2':
		n = 3;
		break;
	
	case 'R': // right
	case 'r':
		rotY += 24;
		std::cout << "l" << std::endl;
		break;
	
	case 'L': // left
	case 'l':
		rotY -= 24;
		std::cout << "r" << std::endl;
		break; 
	
	case 'U': //Up
	case 'u':
		std::cout << "u" << std::endl;
		rotX += 24;
			break;

	case 'D': // Down
	case 'd':
		std::cout << "d" << std::endl;
		rotX -= 24;
			break;
	case 'i'://side face antiClockwise
		selector = 'i';
		selector_value = minValue;
		angle -= 90;
		break;
	case 'I'://side face clockwise
		selector = 'i';
		selector_value = minValue;
			angle+= 90;
			break;


	case 'j':
		selector = 'i';
		selector_value = minValue+cube_size;
		angle -= 90;
		break;
	case 'J':
		selector = 'i';
		selector_value = minValue+cube_size;
		angle += 90;
		break;

	case 'k': // up
		selector = 'i';
		selector_value = minValue + 2*cube_size;
		angle -= 90;
		break;

	case 'K':
		selector = 'i';
		selector_value = minValue + 2*cube_size;
		angle += 90;
		break;
		//rot_x = (rot_x - crement) % 360;
		break;
		// end of view rotation

		// cube movements

		// select cube face
		// x-axis faces
	case 'q':
		selector = 'j';
		selector_value = minValue;
		angle -= 90;
		break;
	case 'Q':
		selector = 'j';
		selector_value = minValue;
		angle += 90;
		break;
	
	case 'm':
		selector = 'j';
		selector_value = minValue +  cube_size;
		angle -= 90;
		break;
	case 'M':
		selector = 'j';
		selector_value = minValue +  cube_size;
		angle+= 90;
		break;
	case 'b':
		selector = 'j';
		selector_value = minValue + 2 * cube_size;
		angle -= 90;
		break;

	case 'B':
		selector = 'j';
		selector_value = minValue + 2 * cube_size;
		angle -= 90;
		break;

	
	case 'w':
		selector = 'k';
		selector_value = minValue + 2 * cube_size;
		angle -= 90;
		break;

	case 'W':
		selector = 'k';
		selector_value = minValue + 2 * cube_size;
		angle += 90;
		break;

	case 'E':
		selector = 'k';
		selector_value = minValue + cube_size;
		angle += 90;
		break;
	case 'e':
		selector = 'k';
		selector_value = minValue + cube_size;
		angle -= 90;
		break;

		// y-axis faces
	case 'A':
		selector = 'k';
		selector_value = minValue ;
		angle += 90;
	case 'a':
		selector = 'k';
		selector_value = minValue;
		angle -= 90;
		
		break;

	

		// z-axis faces
	case 'C':
	case 'c':

		break;

	case 'X':
	case 'x':
	
		break;

	case 'Z':
	case 'z':
		
		break;

		// move selected face
	

		// end of cube movements

	default:
		break;

	}

	glutPostRedisplay();

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
	glutKeyboardFunc(keyboardFunc);
	glutMainLoop();                 // Enter the infinite event-processing loop
	return 0;
}