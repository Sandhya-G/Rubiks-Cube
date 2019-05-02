
#include <GL/glut.h>  
#include<iostream>
#include<vector>
#include<cmath>

#define FOR(i,a,b,increment) for(float i=a;i<=b;i=i+increment)
#define FORD(i,a,b,decrement) for(float i=a;i>=b;i=i-decrement)
#define REP(i,n) for(int i=0;i<n;++i)
#define PI 3.14
using namespace std;
struct cube_rotate {

	GLfloat angle, x, y, z;

};
GLint rot_x, rot_y, crement, x_0, x_k, y_0, y_k, z_0, z_k;

vector<cube_rotate> cube_rotations[3][3][3];
void apply_rotation(GLfloat angle) {

	vector<cube_rotate> face[3][3];
	int index;
	cube_rotate rotation;

	// copy face to be rotated
	// apply rotation to face
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {

			index = 2 - j % 3;

			if (x_0 == x_k) {
				rotation = { angle, 1.0, 0.0, 0.0 };
				face[index][i] = cube_rotations[x_k][i][j];
			}

			if (y_0 == y_k) {
				rotation = { angle, 0.0, 1.0, 0.0 };
				face[index][i] = cube_rotations[j][y_k][i];
			}

			if (z_0 == z_k) {
				rotation = { -1 * angle, 0.0, 0.0, 1.0 };
				face[index][i] = cube_rotations[j][i][z_k];
			}

			face[index][i].push_back(rotation);

		}

	// copy back rotated face
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j) {

			if (x_0 == x_k)
				cube_rotations[x_k][i][j] = face[i][j];

			if (y_0 == y_k)
				cube_rotations[j][y_k][i] = face[i][j];

			if (z_0 == z_k)
				cube_rotations[j][i][z_k] = face[i][j];
		}

}

// reset face selection parameters
void reset_selected_face() {

	x_0 = 0;
	x_k = 2;
	y_0 = 0;
	y_k = 2;
	z_0 = 0;
	z_k = 2;

}
/*stuff to do
make simulatenous face rotations possible use quaternions or something
bfs
*/
//typedef void(*ButtonCallback)();
#define ROT(x, y, costheta, sintheta) x*costheta - y*sintheta, x*sintheta + y*costheta
GLfloat rotatedegree = 0;

//Code written by Dr. Jeong - Professor of Computer Science at the University of the District of Columbia (UDC)
class CVector {
public:
	CVector() { x = y = z = 0; };
	CVector(float x, float y, float z) { this->x = x; this->y = y; this->z = z; };
	CVector operator+(const CVector& rhs) {
		double r_x, r_y, r_z;
		r_x = this->x + rhs.x;
		r_y = this->y + rhs.y;
		r_z = this->z + rhs.z;
		return CVector(r_x, r_y, r_z);
	};
	CVector operator=(const CVector& rhs)
	{
		x = rhs.x; y = rhs.y; z = rhs.z;
		return *this;
	};
	CVector CrossProduct(CVector rhs) {
		return CVector(y * rhs.z - z * rhs.y,
			z * rhs.x - x * rhs.z,
			x * rhs.y - y * rhs.x);
	};
	CVector operator*(float constant) {
		return CVector(x * constant, y * constant, z * constant);
	};

	CVector vector_scale(float constant, CVector v) {
		return CVector(constant * v.x, constant * v.y, constant * v.z);
	}

	float Size() {
		return sqrt(x * x + y * y + z * z);
	};

	CVector Norm() {
		return *this* (1 / this->Size());
	}
	float DotProduct(CVector rhs) {
		return (x * rhs.x + y * rhs.y + z * rhs.z);
	};

public:
	float x, y, z;
};


class CQuaternion {
public:
	CQuaternion() { s = x = y = z = 0; };
	CQuaternion(float s, float x, float y, float z) { this->s = s; this->x = x; this->y = y; this->z = z; };
	CQuaternion operator*(const CQuaternion& rhs) {
		double r_s, r_x, r_y, r_z;
		r_s = this->s * rhs.s - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z;
		r_x = this->s * rhs.x + this->x * rhs.s + this->y * rhs.z - this->z * rhs.y;
		r_y = this->s * rhs.y - this->x * rhs.z + this->y * rhs.s + this->z * rhs.x;
		r_z = this->s * rhs.z + this->x * rhs.y - this->y * rhs.x + this->z * rhs.s;
		return CQuaternion(r_s, r_x, r_y, r_z);
	};
	CQuaternion Conjugate() {
		return CQuaternion(s, -x, -y, -z);
	};

public:
	float s, x, y, z;
};


CQuaternion CreateQuaternionWithThetha(CVector axis, double angle) {
	return CQuaternion(cos(angle / 2.0),
		axis.x * sin(angle / 2.0),
		axis.y * sin(angle / 2.0),
		axis.z * sin(angle / 2.0));
}

CVector QuaternionRotation(CQuaternion q, CVector v) {
	CQuaternion vq;

	vq = CQuaternion(0, v.x, v.y, v.z);
	vq = q * vq;
	vq = vq * q.Conjugate();
	return CVector(vq.x, vq.y, vq.z);
}

void QuaternionRotationMatrix(CQuaternion q, GLfloat * m) {
	CVector x, y, z;
	CVector x_t, y_t, z_t;

	x = CVector(1, 0, 0);
	y = CVector(0, 1, 0);
	z = CVector(0, 0, 1);

	x_t = QuaternionRotation(q, x);
	y_t = QuaternionRotation(q, y);
	z_t = QuaternionRotation(q, z);

	m[0] = x_t.x;
	m[1] = x_t.y;
	m[2] = x_t.z;
	m[3] = 0;
	m[4] = x.DotProduct(y_t);
	m[5] = y.DotProduct(y_t);
	m[6] = z.DotProduct(y_t);
	m[7] = 0;

	m[8] = x.DotProduct(z_t);
	m[9] = y.DotProduct(z_t);
	m[10] = z.DotProduct(z_t);
	m[11] = 0;

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

CVector downwards = CVector(0, 0, 1);
CVector ball_position = CVector(0, 1, 0);
CQuaternion ball_orientation = CQuaternion(0, 0, 1, 0);
//End Dr. Jeong Code

//Begin Claude C Code
/*void display() {
	GLfloat rotation[16];
	float d;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -20);

	//creating spheres with quaternion implemented
	glPushMatrix();
	glScalef(2, 2, 2);
	QuaternionRotationMatrix(ball_orientation, rotation);
	glMultMatrixf(rotation);
	glColor3f(1, 0, 0);
	glutSolidSphere(2, 15, 15);   // red sphere
	glPopMatrix();

	glPushMatrix();
	glRotatef(rotatedegree, 0, 1, 0);
	glScalef(.6, .6, .6);
	glTranslatef(7, 0, 7);

	glMultMatrixf(rotation);
	glColor3f(0, 0, 1);

	glutSolidSphere(1, 15, 15);		 //blue sphere
	glPopMatrix();
	glutSwapBuffers();
}
*/
//For continuous rotation


//End Claude C
void drawText(void *, const char*, float , float );
void displayTitle();
void draw_cube(float, float, float);

struct Mouse
{
	float x;			//the x coordinate of the mouse cursor
	float y;			//the y coordinate of the mouse cursor	
	int ButtonClicked;	//is the left button pressed?	
};
typedef struct Mouse Mouse;

struct coordinates {
	double x;
	double y;
	double z;
};

std::vector<coordinates> Coordinates;
Mouse mouse = {0,0,0};
GLdouble winX,winY,winZ;
int winw = 640, winh = 480;
int window = 0;
void twoD()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
}
void threeD() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Set background color to black and opaque
	glClearDepth(1.0f);									// Set background depth to farthest
	glEnable(GL_DEPTH_TEST);							// Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);								// Set the type of depth-test
	glShadeModel(GL_SMOOTH);							// Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void WindowCoordinates(GLdouble x, GLdouble y)
{
	
	GLint viewport[4]; //var to hold the viewport info
	GLdouble modelview[16]; //var to hold the modelview info
	GLdouble projection[16]; //var to hold the projection matrix info
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview); //get the modelview info
	glGetDoublev(GL_PROJECTION_MATRIX, projection); //get the projection matrix info
	glGetIntegerv(GL_VIEWPORT, viewport); //get the viewport info
	gluProject(x,y,0.0,modelview,projection,viewport,&winX,&winY,&winZ);
}

class Button {
	public:
	    float x;				
		float   y;			
		float   w;
		float   h;							
		//int	  state;						 
		int	  highlighted;					
		const char* label;						
	    //ButtonCallback callbackFunction;

	Button(const float px, const float py, const float pw,const float ph, int phighlighted,const char* plabel)
	{
		x = px;							//top left x coord of the button 
	    y = py;							// top left y coord of the button 
		w = pw;					        // the width of the button 
		h = ph;							// the height of the button 
		//state =pstate;					// the state, 1 if pressed, 0 otherwise 
		highlighted =phighlighted;	    // is the mouse cursor over the control? 
		label = plabel;				    // the text label of the button 
		//callbackFunction = pcallbackFunction;
	}

	void ButtonDraw()
	{
		float fontx=0;
		float fonty=0;
		glColor3f(0, 0.8, 0);
		//draw background for the button.
		glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x, y + h);
		glVertex2f(x + w, y + h);
		glVertex2f(x + w, y);
		glEnd();
		
		//Draw an outline around the button
		if (!highlighted)
		{
			glColor3f(0.0f, 0.3f, 0.0f);
			glLineWidth(6);
			glBegin(GL_LINE_STRIP);
			glVertex2f(x + 0.006, y + h);
			glVertex2f(x + w+0.006, y + h);
			glEnd();
			glLineWidth(10);
			glBegin(GL_LINE_STRIP);
			glVertex2f(x + w, y + h + 0.05);
			glVertex2f(x + w, y);
			glEnd();
		}
		glColor3f(0, 0, 0);
		fontx = x + w / 4.8;
		fonty = y + h / 2.6;
		//printf_s("x %f \n y %f \n", fontx, fonty);
		glPushMatrix();
		drawText(GLUT_BITMAP_HELVETICA_18, label, fontx, fonty);
		glPopMatrix();
		glutPostRedisplay();
		
	}
	int ButtonArea()
	{
		double WminX, WminY, WmaxX, WmaxY;
		WindowCoordinates(x, -y);
		WminX = winX;
		WminY = winY;
		WindowCoordinates((x+w), -(y+h));
		WmaxX = winX;
		WmaxY = winY;
		//printf_s(" Window x %f \n Window y  %f \n Window x1 %f  Window y1 %f \n", WminX, WminY, WmaxX,WmaxY);
		if (mouse.x > WminX      &&
			mouse.x < WmaxX		 &&
			mouse.y < WminY      &&
			mouse.y > WmaxY)
		
			return 1;
				
		return 0;
	}
	int OnButtonClicked()
	{
		if (ButtonArea() && mouse.ButtonClicked)
			//printf_s("inside x %f \n inside y %f \n", mouse.x, mouse.y);
			return 1;
			//callbackFunction();
		return 0;
	}

	void ButtonPassive()
	{
		
		//printf_s("x %f \n y %f \n", mouse.x, mouse.y);
			//if the mouse moved over the control
			if (ButtonArea())
			{
					//printf_s("inside x %f \n inside y %f \n", mouse.x, mouse.y);
					highlighted = 1;
			}
			else
				highlighted = 0;
			
			glutPostRedisplay();	
	}
};

void TheButtonCallback()
{
	printf("I have been called\n");
}
const double cube_size = 1;
int n = 0;
double minValue;
char title[] = "Cube";
int refreshMills = 500;
char selector = ' ';
float selector_value ;
int rotX = 0,rotY=0;
int angle,angley;
void Buttons()
{
	twoD();
	glColor3f(0, 0, 0);
	Button b2c = Button(-1.2, 1.2, 1.5, 0.75, 0, "2*2*2");
	Button b3c = Button(-1.2,0.15, 1.5, 0.75, 0,"3*3*3");	
	b3c.ButtonPassive();
	b2c.ButtonPassive();
	b2c.ButtonDraw();
	b3c.ButtonDraw();
	
	if (b2c.OnButtonClicked())
	{
		n = 2;
		window = 1;
	}
	if (b3c.OnButtonClicked())
	{
		n = 3;
		window = 1;
	}
	glutPostRedisplay();
}
void drawBack()
{
	twoD();
	Button back = Button(-4.5, -3.5, 1.5, 0.75, 0, "BACK");
	back.ButtonPassive();
	back.ButtonDraw();
	if (back.OnButtonClicked())
		window = 0;
	glutPostRedisplay();
}
int choice=0;
float ang[3][3][3];

void angle1(double a)
{
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			for (int k = 0; k < 2; k++)
			{
				if (i == 0)
					ang[i][j][k] = a;
				else
					ang[i][j][k] = 0;
			}
}
void drawCube()
{
	threeD();
	double x, y, z;
	if (n & 1)
		minValue = -((n - 1) / 2 * cube_size);
	else
		minValue = -(n / 2 * cube_size - cube_size / 2);
	int count = 0;
	
	glPushMatrix();
	//gluLookAt(0.5, 0.5, 0.5, 0, 0, 0, 0, 1, 0);
	GLfloat rotation[16];
	CVector camera = CVector(0, 0, 0);
	//CQuaternion q = CreateQuaternionWithThetha(CVector(0, 1, 0), rotY);
	//CVector v = QuaternionRotation(q, CVector(1, 0, 0));
	//CQuaternion q1 =CQuaternion(0, v.x,v.y,v.z);
	//QuaternionRotationMatrix(q1, rotation);
	//glMultMatrixf(rotation);

	
	//CQuaternion q11 = CreateQuaternionWithThetha(CVector(1, 0, 0), rotX);
	//CVector v1 = QuaternionRotation(q11, CVector(0, 1, 0));
	//CQuaternion q10 = CQuaternion(0, v1.x, v1.y, v1.z);
	//QuaternionRotationMatrix(q10, rotation);
	//glMultMatrixf(rotation);
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotX, 1, 0, 0);



	//GLfloat matrixf[16];
   //Generic rubiks cube
	FOR(i, minValue, -minValue, cube_size) {// step through x axis				

		FOR(j, minValue, -minValue, cube_size) {// step through y axis

			FOR(k, minValue, -minValue, cube_size)// step through z axis
			{
				
				coordinates c;
				c.x = i;
				c.y = j;
				c.z = k;
				Coordinates.push_back(c);
				GLfloat rotation1[16];
				/*glPushMatrix();
				switch (selector)
				{
					
				case 'i': if (i == selector_value) {
					//QuaternionRotationMatrix(CQuaternion(0,1,0,0),rotation);
					// glMultMatrixf(rotation);
					glRotatef(angle,1, 0, 0);
					
					CQuaternion q111 = CreateQuaternionWithThetha(CVector(1, 0, 0), PI/2);
					
					QuaternionRotationMatrix(q111, rotation1);
				
					//glMultMatrixf(rotation1);

					
					
				}break;
				case 'j': if (j == selector_value) {
					glMultMatrixf(rotation1);
					glRotatef(angle, 0, 1, 0);
				
					
				}break;
				case 'k': if (k == selector_value) glRotatef(angle, 0, 0, 1); break;
		
					

				}*/
				//vector<cube_rotate> lrot = cube_rotations[i][j][k];

				draw_cube(i, j, k);
								//if(!choice)
					//render();
				

			}
		}
	}
	
	glPopMatrix();
	//gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);

	drawBack();

}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glLoadIdentity(); 
	glTranslatef(0, 0, -10);
	if (!window)
	{
		Buttons();
		displayTitle();
	}
	else
		drawCube();
	glutSwapBuffers();
	glutPostRedisplay();
}
void draw_cube(float x, float y, float z)
{

	double gap = 0.04;
	glPushMatrix();
	 glTranslatef(x+x*gap,y+y*gap,z+z*gap);	
	if (minValue == z)
		glColor3f(1.0f, 0.5f, 0.0f);
	else
		glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // back
	glNormal3f(0.0, 0.0, -1.0);  // face normal
	glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
	glEnd();
	if(minValue == x)
		glColor3f(0.0f, 0.0f, 1.0f);
	else
		glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // left
	glNormal3f(-1.0, 0.0, 0.0);  // face normal 
	glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
	glEnd();

	if (minValue == y)
		glColor3f(1.0f, 1.0f, 0.0f);
	else
		glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // bottom
	glNormal3f(0.0, -1.0, 0.0);  // face normal
	glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
	glEnd();

	if(minValue == -x)
		glColor3f(0.0f, 1.0f, 0.0f);
	else
		glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // right
	glNormal3f(1.0, 0.0, 0.0);  // face normal
	glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
	glEnd();

	if(minValue == -y)
	glColor3f(1.0f, 1.0f, 1.0f);
	else
		glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // top
	glNormal3f(0.0, 1.0, 0.0);  // face normal
	glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
	glEnd();

	if (minValue == -z)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // front
	glNormal3f(0.0, 0.0, 1.0);  // face normal
	glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
	glEnd();
	

	glPopMatrix();

}

//to display text on the screen
void drawText(void *font, const char *text, float x, float y)
{
	//glPushMatrix();
	glRasterPos2f(x, y);

	while (*text != '\0')
	{
		glutBitmapCharacter(font, *text);
		++text;
	}
	//glPopMatrix();
}
//mouse functions
void MouseButton(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		mouse.ButtonClicked = 1;
	}
	else
		mouse.ButtonClicked = 0;
	mouse.x = x;
	mouse.y = y;
	glutPostRedisplay();
}
void displayTitle() {
	//glPushMatrix();
	//glTranslatef(0.5, 0, 0);
	glColor3f(1.0, 0.27, 0.0);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "R",-2+0.5, 2.5);
	glColor3f(0.9, 0, 0);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "U",-1.6+0.5, 2.5);
	glColor3f(1, 1.0, 0);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "B" ,-1.2+0.5, 2.5);
	glColor3f(0.3, 0.8, 0);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24,"I",-0.8+0.5, 2.5);
	glColor3f(0, 0.5, 1);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24,"K", -0.4+0.5, 2.5);
	glColor3f(0.4, 0.7, 0.1);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24,"S",0.0+0.5,2.5);
	glColor3f(0.68, 0.11, 1.0);
	drawText(GLUT_BITMAP_TIMES_ROMAN_24, "BY", 0.5, -1.5+0.5);
	glColor3f(0.72, 0.45, 0.20);
	drawText(GLUT_BITMAP_HELVETICA_18, "Sahana B S", 0.9, -2.0+0.5);
	drawText(GLUT_BITMAP_HELVETICA_18, "Sandhya G", 0.9, -2.5+0.5);
	drawText(GLUT_BITMAP_HELVETICA_18, "Sushma Ellur", 0.9, -3.0+0.5);
	//glPopMatrix();
}
void MousePassiveMotion(int x, int y)
{
	//double normalizedX = -1.0 + 2.0 * (double)x / 640;
	//double normalizedY = 1.0 - 2.0 *modelview info;
	mouse.x = x;
	mouse.y = y;
	glutPostRedisplay();
}

//keyboard function
void keyboardFunc(unsigned char key, int x, int y)
{

	switch (key) {	
	case 'R': // right
	case 'r':
		rotY += 24;
		
		std::cout << "r" << std::endl;
		break;
	
	case 'L': // left
	case 'l':
		rotY -= 24;
		std::cout << "l" << std::endl;
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
		angle += 22;
		break;
	case 'I'://side face clockwise
		selector = 'i';
		selector_value = minValue;
			angle+= 22;
			break;
	case 'j':
		selector = 'i';
		selector_value = minValue+cube_size;
		angle -= 45;
		break;
	case 'J':
		selector = 'i';
		selector_value = minValue+cube_size;
		angle += 45;
		break;

	case 'k': // up
		selector = 'i';
		selector_value = minValue + 2*cube_size;
		angle -= 45;
		break;

	case 'K':
		selector = 'i';
		selector_value = minValue + 2*cube_size;
		angley += 45;
		break;
	case 'q':
		selector = 'j';
		selector_value = minValue;
		angley -= 45;
		break;
	case 'Q':
		selector = 'j';
		selector_value = minValue;
		angle += 45;
		break;
	
	case 'm':
		selector = 'j';
		selector_value = minValue +  cube_size;
		angle -= 45;
		break;
	case 'M':
		selector = 'j';
		selector_value = minValue +  cube_size;
		angle+= 45;
		break;
	case 'b':
		selector = 'j';
		selector_value = minValue + 2 * cube_size;
		angle -= 45;
		break;

	case 'B':
		selector = 'j';
		selector_value = minValue + 2 * cube_size;
		angle -= 45;
		break;

	
	case 'w':
		selector = 'k';
		selector_value = minValue + 2 * cube_size;
		angle -= 45;
		break;

	case 'W':
		selector = 'k';
		selector_value = minValue + 2 * cube_size;
		angle += 45;
		break;

	case 'E':
		selector = 'k';
		selector_value = minValue + cube_size;
		angle += 45;
		break;
	case 'e':
		selector = 'k';
		selector_value = minValue + cube_size;
		angle -= 45;
		break;

		// y-axis faces
	case 'A':
		selector = 'k';
		selector_value = minValue ;
		angle += 45;
		break;
	case 'a':
		selector = 'k';
		selector_value = minValue;
		angle -= 45;
		break;
	default:
		break;

	}

	glutPostRedisplay();

}
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	winw = width;
	winh = height;
	// Set the viewport to cover the new window
	glViewport(0, 0, winw, winh);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}


/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
	glutInit(&argc, argv);// Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH); // Enable double buffered mode
	glutInitWindowSize(winw, winh);// Set the window's initial width & height
	glutInitWindowPosition(50, 50);// Position the window's initial top-left corner
	glutCreateWindow(title);// Create window with the given title
	glutDisplayFunc(display);// Register callback handler for window re-paint event
	glutReshapeFunc(reshape);// Register callback handler for window re-size event
	//initGL();									
	//glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboardFunc);
	glutMouseFunc(MouseButton);
	glutPassiveMotionFunc(MousePassiveMotion);
	glutMainLoop();// Enter the infinite event-processing loop
	return 0;
}