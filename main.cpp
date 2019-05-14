#include<stdlib.h>
#include <GL/glut.h>  
#include<iostream>
#include<vector>
#include <unordered_map> 
#include<cmath>


#define FOR(i,a,b,increment) for(float i=a;i<=b;i=i+increment)
#define FORD(i,a,b,decrement) for(float i=a;i>=b;i=i-decrement)
#define REP(i,n) for(int i=0;i<n;++i)
#define mp(a,b) make_pair(a,b)
#define pb(x) push_back(x);

#define PI 3.14159265
#define toRad(x) ((x)*(PI/180.0))

using namespace std;


void drawText(void *, const char*, float , float );
void displayTitle();
void draw_cube(float, float, float,int);

struct Mouse
{
	float x;			//the x coordinate of the mouse cursor
	float y;			//the y coordinate of the mouse cursor	
	int ButtonClicked;	//is the left button pressed?	
};
typedef struct Mouse Mouse;
static int top[3][3] = { {0,0,0},{0,0,0},{0,0,0} },
righ[3][3] = { {1,1,1},{1,1,1},{1,1,1} },
front[3][3] = { {2,2,2},{2,2,2},{2,2,2} },
back[3][3] = { {3,3,3},{3,3,3},{3,3,3} },
bottom[3][3] = { {4,4,4},{4,4,4},{4,4,4} },
lef[3][3] = { {5,5,5},{5,5,5},{5,5,5} },
temp[3][3];
class Color {
	public:
		int Top;
		int Left;
		int Right;
		int Front;
		int Back;
		int Bottom;

		Color()
		{
			Top = top[0][0];
			Bottom =bottom[0][0];
			Right =righ[0][0];
			Left = lef[0][0];
			Front = front[0][0];
			Back = back[0][0];

		}

		Color(int pt, int pb, int pr, int pl, int pf, int pba)
		{
			Top = pt;
			Bottom = pb;
			Right = pr;
			Left = pl;
			Front = pf;
			Back = pba;
			
		}
};


Mouse mouse = {0,0,0};
GLdouble winX,winY,winZ;
static int winw = 640, winh = 480;
static int window = 0;
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
		glColor3f(0.0, 0.8, 0.0);
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
			glColor3f(0.0f, 0.3f, 0.f);
			glLineWidth(6);
			glBegin(GL_LINE_STRIP);
			glVertex2f(x+0.006 , y + h);
			glVertex2f(x + w, y + h);
			glEnd();
			glLineWidth(10);
			glBegin(GL_LINE_STRIP);
			glVertex2f(x + w, y + h+0.05 );
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


const double cube_size = 1;
int n = 0;
double minValue;
char title[] = "Rubik's Cube";
char selector = ' ';
float selector_value ;
int rotX = 0, rotY = 0, angle = 0, x1 = 0, z1 =0, x2 = 0,y2 =0, z2 =0, x3 = 0, y3 =0, z3 = 0;
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



vector<Color> Colors;

/*
	on face rotations
	0 1 2		6 3	0		
	3 4 5		7 4	1
	6 7 8		8 5	2
*/

void updateColors(char a)
{

	if (a == 'r')
	{
		int temp;
		temp = righ[0][0];
		righ[0][0] = righ[2][0];
		righ[2][0] = righ[2][2];
		righ[2][2] = righ[0][2];
		righ[0][2] = temp;
		temp = righ[1][0];
		righ[1][0] = righ[2][1];
		righ[2][1] = righ[1][2];
		righ[1][2] = righ[0][1];
		righ[0][1] = temp;
	}
	if (a == 't')



	{
		int temp;
		temp = top[0][0];
		top[0][0] = top[2][0];
		top[2][0] = top[2][2];
		top[2][2] = top[0][2];
		top[0][2] = temp;
		temp = top[1][0];
		top[1][0] = top[2][1];
		top[2][1] = top[1][2];
		top[1][2] = top[0][1];
		top[0][1] = temp;
	}
	if (a == 'f')
	{
		int temp;
		temp = front[0][0];
		front[0][0] = front[2][0];
		front[2][0] = front[2][2];
		front[2][2] = front[0][2];
		front[0][2] = temp;
		temp = front[1][0];
		front[1][0] = front[2][1];
		front[2][1] = front[1][2];
		front[1][2] = front[0][1];



		front[0][1] = temp;
	}


	/* 0 1 2	2 5 8
	   3 4 5	1 4 7
	   6 7 8	0 3 6	               */
	if (a == 'l')
	{
		int temp;
		temp = lef[0][0];
		lef[0][0] = lef[0][2];
		lef[0][2] = lef[2][2];
		lef[2][2] = lef[2][0];
		lef[2][0] = temp;
		temp = lef[1][0];
		lef[1][0] = lef[0][1];
		lef[0][1] = lef[1][2];
		lef[1][2] = lef[2][1];
		lef[2][1] = temp;
	}
	if (a == 'k')
	{
		int temp;
		temp = back[0][0];
		back[0][0] = back[2][0];
		back[2][0] = back[2][2];
		back[2][2] = back[0][2];
		back[0][2] = temp;
		temp = back[1][0];



		back[1][0] = back[2][1];
		back[2][1] = back[1][2];
		back[1][2] = back[0][1];
		back[0][1] = temp;
	}

	if (a == 'b')
	{
		int temp;
		temp = bottom[0][0];
		bottom[0][0] = bottom[2][0];
		bottom[2][0] = bottom[2][2];
		bottom[2][2] = bottom[0][2];
		bottom[0][2] = temp;
		temp = bottom[1][0];
		bottom[1][0] = bottom[2][1];
		bottom[2][1] = bottom[1][2];
		bottom[1][2] = bottom[0][1];
		bottom[0][1] = temp;
	}
}

void topc()
{



	updateColors('t');
	int temp1 = front[0][0];
	int temp2 = front[0][1];
	int temp3 = front[0][2];

	front[0][0] = righ[0][0];
	front[0][1] = righ[0][1];
	front[0][2] = righ[0][2];

	righ[0][0] = back[0][0];
	righ[0][1] = back[0][1];
	righ[0][2] = back[0][2];

	back[0][0] = lef[0][0];
	back[0][1] = lef[0][1];
	back[0][2] = lef[0][2];

	lef[0][0] = temp1;
	lef[0][1] = temp2;
	lef[0][2] = temp3;

}

void frontc()
{



	updateColors('f');
	int temp1 = lef[0][2];
	int temp2 = lef[1][2];
	int temp3 = lef[2][2];

	lef[0][2] = bottom[0][0];
	lef[1][2] = bottom[0][1];
	lef[2][2] = bottom[0][2];

	bottom[0][0] = righ[2][0];
	bottom[0][1] = righ[1][0];
	bottom[0][2] = righ[0][0];

	righ[2][0] = top[2][2];
	righ[1][0] = top[2][1];
	righ[0][0] = top[2][0];

	top[2][2] = temp1;
	top[2][1] = temp2;
	top[2][0] = temp3;
}

void rightc()
{
	updateColors('r');



	int temp1 = top[0][0];
	int temp2 = top[1][0];
	int temp3 = top[2][0];

	top[0][0] = back[0][0];
	top[1][0] = back[1][0];
	top[2][0] = back[2][0];

	back[0][0] = bottom[0][0];
	back[1][0] = bottom[1][0];
	back[2][0] = bottom[2][0];
	
	bottom[0][0] = front[2][0];
	bottom[1][0] = front[1][0];
	bottom[2][0] = front[0][0];

	front[0][0] = temp1;
	front[1][0] = temp2;
	front[2][0] = temp3;


	
}

void leftc()
{



	updateColors('l');
	int temp1 = front[0][0];
	int temp2 = front[1][0];
	int temp3 = front[2][0];

	front[0][0] = top[0][0];
	front[1][0] = top[1][0];
	front[2][0] = top[2][0];

	top[0][0] = back[2][0];
	top[1][0] = back[1][0];
	top[2][0] = back[0][0];

	back[0][0] = bottom[0][0];
	back[1][0] = bottom[1][0];
	back[2][0] = bottom[2][0];


	bottom[0][0] = temp3;
	bottom[1][0] = temp2;
	bottom[2][0] = temp1;
}

void backc()
{



	updateColors('k');
	int temp1 = top[0][0];
	int temp2 = top[0][1];
	int temp3 = top[0][2];

	top[0][0] = righ[0][2];
	top[0][1] = righ[1][2];
	top[0][2] = righ[2][2];

	righ[0][2] = bottom[2][2];
	righ[1][2] = bottom[2][1];
	righ[2][2] = bottom[2][0];

	bottom[2][2] = lef[2][0];
	bottom[2][1] = lef[1][0];
	bottom[2][0] = lef[0][0];

	lef[2][0] = temp1;
	lef[1][0] = temp2;
	lef[0][0] = temp3;
}


void bottomc()
{



	updateColors('b');
	int temp1 = front[2][0];
	int temp2 = front[2][1];
	int temp3 = front[2][2];

	front[2][0] = lef[2][0];
	front[2][1] = lef[2][1];
	front[2][2] = lef[2][2];

	lef[2][0] = back[2][0];
	lef[2][1] = back[2][1];
	lef[2][2] = back[2][2];

	back[2][0] = righ[2][0];
	back[2][1] = righ[2][1];
	back[2][2] = righ[2][2];

	righ[2][0] = temp1;
	righ[2][1] = temp2;
	righ[2][2] = temp3;

}

void drawHelp()   //button
{
	twoD();
	Button in = Button(3.5,-3.5,1.5,0.75,0,"HELP");
	in.ButtonPassive();
	in.ButtonDraw();
	if(in.OnButtonClicked())
			window=2;
	glutPostRedisplay();
}
	 


void displayHelp()   //instructions
{
		glPushMatrix();
	glTranslatef(0.5, 0, 0);
	    
		glColor3f(1.0, 1.0, 1.0);
		drawText(GLUT_BITMAP_HELVETICA_18, "L/l-Rotate cube anticlockwise", -0.5, -1.0+0.5);
		drawText(GLUT_BITMAP_HELVETICA_18, "R/r-Rotate cube clockwise", -0.5, -1.5+0.5);
		drawText(GLUT_BITMAP_HELVETICA_18, "U/u-Rotate cube upwards", -0.5, -2.0+0.5);
		drawText(GLUT_BITMAP_HELVETICA_18, "D/d-Rotate cube downwards",-0.5, -2.5+0.5);
	    

		glPopMatrix();
		drawBack();
		
		

	
}
void bindColor()
{	
	Colors.pb(Color(top[0][0], 6, 6, lef[0][0], 6, back[0][0]));
	Colors.pb(Color(top[0][1], 6, 6,6 , 6, back[0][1]));
	Colors.pb(Color(top[0][2], 6,righ[0][0] , 6, 6, back[0][2]));
	Colors.pb(Color(6, 6, 6, lef[0][1], 6, back[1][0]));
	Colors.pb(Color(6, 6, 6, 6, 6, back[1][1]));
	Colors.pb(Color(6, 6, righ[0][1], 6, 6, back[1][2]));
	Colors.pb(Color(6, bottom[0][0], 6, lef[0][2], 6, back[2][0]));
	Colors.pb(Color(6, bottom[0][1], 6, 6, 6, back[2][1]));
	Colors.pb(Color(6, bottom[0][2], righ[0][2], 6, 6, back[2][2]));
	
	Colors.pb(Color(top[1][0], 6, 6, lef[1][0], 6, 6));
	Colors.pb( Color(top[1][1], 6, 6, 6, 6, 6));
	Colors.pb( Color(top[1][2], 6, righ[1][0], 6, 6, 6));
	Colors.pb( Color(6, 6, 6, lef[1][1], 6, 6));
	Colors.pb( Color(6, 6, 6, 6, 6, 6));
	Colors.pb( Color(6, 6, righ[1][1], 6, 6, 6));
	Colors.pb( Color(6, bottom[1][0], 6, lef[1][2], 6, 6));
	Colors.pb( Color(6, bottom[1][1], 6, 6, 6, 6));
	Colors.pb( Color(6, bottom[1][2], righ[1][2], 6, 6, 6));
	
	Colors.pb( Color(top[2][0], 6, 6, lef[2][0], front[0][0], 6));
	Colors.pb( Color(top[2][1], 6, 6, 6, front[0][1], 6));
	Colors.pb( Color(top[2][2], 6, righ[2][0], 6, front[0][2], 6));
	Colors.pb( Color(6, 6, 6, lef[2][1], front[1][0], 6));
	Colors.pb( Color(6, 6, 6, 6, front[1][1], 6));
	Colors.pb( Color(6, 6, righ[2][1], 6, front[1][2], 6));
	Colors.pb( Color(6, bottom[2][0],6, lef[2][2], front[2][0], 6));
	Colors.pb( Color(6, bottom[2][1], 6, 6, front[2][1], 6));
	Colors.pb( Color(6, bottom[2][2], righ[2][2], 6, front[2][2], 6));
}
GLfloat color[][3] = { {1.0,1.0,1.0},  //white 
					{1.0,0.5,0.0},  //orange 
					{0.0,0.0,1.0},  //blue 
					{0.0,1.0,0.0},  //green 
 					{1.0,0.0,0.0}, //red 
					{1.0,1.0,0.0},//yellow
					{0.4,0.4,0.4} };
void drawCube()														  
{		
	threeD();
	double x, y, z;
	if (n & 1)
		minValue = -((n - 1) / 2 * cube_size);
	else
		minValue = -(n / 2 * cube_size - cube_size / 2);

	
	glPushMatrix();
	glRotatef(rotY, 0, 1, 0);
	glRotatef(rotX, 1, 0, 0);
	int count = 0;
		FOR(k, minValue, -minValue, cube_size) {// step through x axis				

		FORD(j, -minValue, minValue, cube_size) {// step down through y axis

			FOR(i, minValue, -minValue, cube_size)// step through z axis
			{
				glPushMatrix();
		
				switch (selector)
				{
				case 'i': if (i == selector_value) glRotatef(angle, 1, 0, 0); break;
				case 'j': if (j == selector_value) glRotatef(angle, 0, 1, 0); break;
				case 'k': if (k == selector_value) glRotatef(angle, 0, 0, 1); break;
				}
				Colors.clear();
				bindColor();
				draw_cube(i, j, k,count);
				count++;
				
				glPopMatrix();
				

			}
		}
	}

	

	

	
	glPopMatrix();

	//gluLookAt(0, 0, 0, 0, 0, 0, 0, 1, 0);

	drawBack();

	drawHelp();


}

/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
	glLoadIdentity(); 
	glTranslatef(0, 0, -10);
	if (window == 0)
	{
		Buttons();
		displayTitle();
	}
	else if(window == 1)
		drawCube();
	else 
	   displayHelp();
		
	glutSwapBuffers();
	glutPostRedisplay();
	
}
void print()
{
	bindColor();
	REP(count,Colors.size())
		cout<<Colors[count].Top<<" "<< Colors[count].Bottom<<" " << Colors[count].Right<<" "<< Colors[count].Left<<" "<< Colors[count].Front<<" "<<Colors[count].Back<<endl;
	
}
void draw_cube(float x, float y, float z,int count)
{

	double gap = 0.04;
	glPushMatrix();
	 glTranslatef(x+x*gap,y+y*gap,z+z*gap);	
	//if (minValue == z)
	n==3 ? glColor3fv(color[Colors[count].Back]) : minValue==z? glColor3fv(color[3]) : glColor3f(0.4, 0.4, 0.4);
	//else
		//glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // back
	glNormal3f(0.0, 0.0, -1.0);  // face normal
	glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
	glEnd();
	//if(minValue == x)
	 n == 3 ? glColor3fv(color[Colors[count].Left]) : minValue == x ? glColor3fv(color[5]) : glColor3f(0.4, 0.4, 0.4);
	//else
		//glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // left
	glNormal3f(-1.0, 0.0, 0.0);  // face normal 
	glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
	glEnd();

	//if (minValue == y)
	n == 3 ? glColor3fv(color[Colors[count].Bottom]):minValue==y? glColor3fv(color[4]) : glColor3f(0.4, 0.4, 0.4);

	//else
		//glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // bottom
	glNormal3f(0.0, -1.0, 0.0);  // face normal
	glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
	glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
	glEnd();

	//if(minValue == -x)
	n == 3 ? glColor3fv(color[Colors[count].Right]) : minValue == -x ? glColor3fv(color[1]) : glColor3f(0.4, 0.4, 0.4);

	//else
		//glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // right
	glNormal3f(1.0, 0.0, 0.0);  // face normal
	glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
	glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
	glEnd();

	//if(minValue == -y)
	 n == 3 ? glColor3fv(color[Colors[count].Top]) : minValue == -y ? glColor3fv(color[0]) : glColor3f(0.4, 0.4, 0.4);

	//else
		//glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);  // top
	glNormal3f(0.0, 1.0, 0.0);  // face normal
	glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
	glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
	glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
	glEnd();

	//if (minValue == -z)
    n == 3 ? glColor3fv(color[Colors[count].Front]) : minValue == -z ? glColor3fv(color[2]) : glColor3f(0.4, 0.4, 0.4);

	//else
		//glColor3f(0.4, 0.4, 0.4);
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
		x1 += 90;
		angle = x1;
		leftc();
	
		
		break;
	case 'I'://side face clockwise
		selector = 'i';
		selector_value = minValue;
			x1-= 90;
			angle = x1;
			leftc(); leftc(); leftc();
			break;
	case 'j':
		selector = 'i';
		selector_value = minValue+cube_size;
		x1 += 45;
		angle = x1;
		
		
		break;
	case 'J':
		selector = 'i';
		selector_value = minValue+cube_size;
		x1 -= 90;
		angle = x1;
		break;

	case 'k':
		selector = 'i';
		selector_value = minValue + 2*cube_size;
		x2 += 90;
		angle = x2;
		//rightc();
		break;

	case 'K':
		selector = 'i';
		selector_value = minValue + 2*cube_size;
		x2 -= 90;
		angle = x2;
		//rightc(); rightc(); rightc();
		break;
	case 'q':
		selector = 'j';
		selector_value = minValue;
		angle -= 45;
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
		case '1' :
			print();
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
