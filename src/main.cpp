#include <iostream>
#include <cstdlib>
#include "butterfly.h"
//#include "flower.h"
#include<ctime>
#include <GLUT/glut.h>

using namespace std;
#define MAX_BUTTERFLY 15;
float eyex=0.0,eyey=0.0,eyez=0.0,centerx=0.0,centery=0.0,centerz=-3.0,upx=0.0,upy=1.0,upz=0.0;
butterfly *butterflies[500];
flower *flowers[1000];
int butterfly_count=0;
int flower_count=0;
int paused=0;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	

	

	switch (key) {
		case 27: //Escape key
			exit(0);
		
		case 66:
		case 98:
			if(butterfly_count<500)
			{
				srand(time(0)+butterfly_count*(rand()%20000));
				//cout<<"Drawing butterfly "<<butterfly_count<<endl;
				butterflies[butterfly_count]=new butterfly(FLYING);
				butterfly_count++;
			}
			break;
		case 70:
			
		case 102:
			if(flower_count<1000)
			{
				srand(time(0)+flower_count*(rand()%20000));
				//cout<<"Drawing flower "<<flower_count<<endl;
				flowers[flower_count]=new flower();
				flower_count++;
			}
			break;
		case ' ':
		
			cout<<"paused"<<endl;
			paused=1-paused;
			break;
		case 'w'://detect W or w press
		case 'W':
			    
				windpaused=1-windpaused;
				//if(windpaused)
				//	wind.speed=0.0;
				break;





	}
}
float thta=5;
void specialKeyPressed(int key, int x, int y)
	{
	 switch (key) {
		 case GLUT_KEY_DOWN:
			//cout<<"down pressed"<<endl;
			eyez+=0.2;
			centerz+=0.2;
			break;
		case GLUT_KEY_UP:
			eyez-=0.2;
			centerz-=0.2;
			break;
		case GLUT_KEY_RIGHT:
			eyex+=3*sinf(thta*3.1416/180);
			eyez+=3*cosf(thta*3.1416/180)-3;
			
			//eyex+=0.2;
			//centerx+=0.2;
			break;
		case GLUT_KEY_LEFT:
			eyex-=0.2;
			centerx-=0.2;
			break;


			/*
			eyey=centery-sqrt((centerx-eyex)*(centerx-eyex)+(centery-eyey)*(centery-eyey)-(centerx-eyex+0.2)*(centerx-eyex+0.2));
			eyex-=0.2;
			*/
			break;

		case GLUT_KEY_PAGE_DOWN:
			eyey-=0.2;
			centery-=0.2;
			break;
		case GLUT_KEY_PAGE_UP:
			eyey+=0.2;
			centery+=0.2;
			break;
		


		 }
	
	
	}
//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//glShadeModel(GL_SMOOTH); //Enable smooth shading

}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 30.0f;
float _cameraAngle = 0.0f;
float gardepth=50.0,garlength=50.0,garwidth=30.0,garheight=2.0,garbase=-5;
//Draws the 3D scene





void update_butterfly_position(int value)
	{
	
	  butterfly *b=butterflies[rand()%(1+butterfly_count)];
      b->curx = b->curx + b->dx * b->velocity;
      b->cury = b->cury + b->dy * b->velocity;
      b->curz = b->curz + b->dz * b->velocity;

	glutPostRedisplay(); //Tell GLUT that the display has changed
	
	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(300/butterfly_count, update_butterfly_position, 0);
	}

void drawGarden()
	{		
	float x,y,z;
	z=-gardepth/2;
    x=-garwidth/2;
	glPushMatrix();
	glTranslatef(0,garbase,z);
    glRotatef(_cameraAngle,0.0,1.0,0.0);
	glRotatef(-90,1.0,0.0,0.0);
	glColor3f(1.0,0.2,0.2);
	for(x=0;x<garwidth;x+=1)
		{
		glTranslatef(1,0.0,0.0);
		gluCylinder(quadratic,0.05,0.05,3.0,2,2);
		/*glLineWidth(10);
		glBegin(GL_LINE);
		
		glVertex3f(0.0,0.0,0.0);
			glVertex3f(0.0,2.0,0.0);
		glEnd();
		 // */  
		}
	for(z=0;z<gardepth;z+=1)
		{
			glTranslatef(0.0,1,0.0);
			gluCylinder(quadratic,0.05,0.05,3.0,2,2);
			
		
		
		}
	glPopMatrix();
	
	}






void handleWind()
	{
	if(windpaused)return;
		
	if(wind.speed==0)
		{
			wind.x=-1.0+0.1*(rand()%20);
			wind.y=-1.0+0.1*(rand()%20);
			wind.z=-1+0.1*(rand()%20);	
		}
	if (wind.max_speed<wind.threshold)
		{
			if((rand()%2)==0)wind.max_speed-=0.05;
			else wind.max_speed+=0.05;
		}
	else{
		if((rand()%3)==0)wind.max_speed=1;

		}

	
		if(wind.speed>wind.max_speed)
			wind.change=-0.02;
		else if(wind.speed<-wind.max_speed)
			wind.change=0.02;
		
		wind.speed+=wind.change;
		
	
	}
void drawScene() {
	

	glClearColor(0.0,0.33,0.33,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	gluLookAt(eyex,eyey,eyez,centerx,centery,centerz,upx,upy,upz);
	
	
    glTranslatef(0.0f, 0.0f, -15.0f);
    
	//drawGarden();
	//flower *f=new flower();
	//f->drawFlower();
	
	glRotatef(_cameraAngle,0.0,1.0,0.0);
	
	//drawGarden();
	handleWind();
		for(int i=0;i<flower_count;i++)
		{
			drawFlower(flowers[i]);
		
		}
   
	//gluDisk(quadratic,1.0,2.0,20,10);
	//glRotatef(-_cameraAngle, 0.0f, 1.0f, 0.0f); //Rotate the camera 
	//Add ambient light
	glColor3f(0.33,0.33,0.33);
	//glTranslatef(0.0f, 0.0f, -3.0f); //Move forward 5 units
	
	//glRotatef(_angle, 1.0f,1.0f, 0.0f); //Rotate about the z-axis
	//glPushMatrix(); //Save the transformations performed thus far
    //glTranslatef(0.0f, -1.0f, 0.0f); //Move to the center of the trapezoid
	
	for(int i=0;i<butterfly_count;i++)
		{
		 drawButterfly(butterflies[i]);

		}
    //butterfly* b= new butterfly(0.1f,0.1f,1.0f,32,32);
	//drawButterfly(b);
	//glPopMatrix();

	//glRotatef(-90,0.0f,1.0f,0.0f);
    /*glBegin(GL_TRIANGLES);
    glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

    glEnd();
	*/
    


	//glPopMatrix();
	//
	/*
	glBegin(GL_QUADS);
	
	//Trapezoid
	glVertex3f(-0.7f, -0.5f, 0.0f);
	glVertex3f(0.7f, -0.5f, 0.0f);
	glVertex3f(0.4f, 0.5f, 0.0f);
	glVertex3f(-0.4f, 0.5f, 0.0f);
	
	glEnd();
	
	glPopMatrix(); //Undo the move to the center of the trapezoid
	glPushMatrix(); //Save the current state of transformations
	glTranslatef(1.0f, 1.0f, 0.0f); //Move to the center of the pentagon
	glRotatef(_angle, 0.0f, 1.0f, 0.0f); //Rotate about the y-axis
	glScalef(0.7f, 0.7f, 0.7f); //Scale by 0.7 in the x, y, and z directions
	
	glBegin(GL_TRIANGLES);
	
	//Pentagon
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	
	glEnd();
	
	glPopMatrix(); //Undo the move to the center of the pentagon//stops rotation
	glPushMatrix(); //Save the current state of transformations
	glTranslatef(-1.0f, 1.0f, 0.0f); //Move to the center of the triangle
	glRotatef(_angle, 1.0f, 2.0f, 3.0f); //Rotate about the the vector (1, 2, 3)
	
	glBegin(GL_TRIANGLES);
	
	//Triangle
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	
	glEnd();
	
	glPopMatrix(); //Undo the move to the center of the triangle
	*/
	glutSwapBuffers();
}


void update(int value) {
	_angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	
	if(angle_wing>=90.0)
		   angle_wing_change=-20.0f;
	   else if(angle_wing<=-60.0)
		   angle_wing_change=+20.0f;
	angle_wing+=angle_wing_change;
	
    if(!paused)
	_cameraAngle+=0.5f;
	if(_cameraAngle>360)
		_cameraAngle-=360;

	
	glutPostRedisplay(); //Tell GLUT that the display has changed
	
	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(10, update, 0);
}


void errorCallback(GLenum errorCode)
{
	const GLubyte *estring;
	
	estring = gluErrorString(errorCode);
	fprintf(stderr, "Quadric Error: %s\n", estring);
	exit(0);
}


int main(int argc, char** argv) {
	//Initialize GLUT
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1400, 960);
	
    quadratic=gluNewQuadric();
	//butterflies[0]=new butterfly(0.1f,0.1f,1.0f,32,32);


	//Create the window
	glutCreateWindow("A Garden By Habib");
	initRendering();
//	butterflies[0]=new butterfly(FLYING);
//	butterfly_count++;
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);

	glutSpecialFunc(specialKeyPressed);
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(2000, update, 0); //Add a timer
	if(butterfly_count)
	glutTimerFunc(300/butterfly_count,update_butterfly_position,0);
	glutMainLoop();
	return 0;
}