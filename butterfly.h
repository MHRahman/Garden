#include <iostream>
#include <cstdlib>
#include<cmath>
#include<ctime>
#include <GLUT/glut.h>

using namespace std;

int FLYING=1;
int SITTING=0;
int DEBUG=1;
float  butterfly_body_angle=90;
float angle_wing=2.0f;
float angle_wing_change=2.0f;
GLUquadricObj *quadratic;
int FLOATS =7;
float RAND[7]={-0.05,0.05,-0.05,0.05,-0.05,0.05,0};
float unit=.1f;
int windpaused=0;
	
	
	
	
class Wind{
public:
	float x,y,z;
	float speed,max_speed,change;
	float threshold;
	Wind();
	
	};
Wind::Wind()
	{
		x=1.0;
		y=0.0;
		z=0.0;
		speed=0.0;
		max_speed=1;
		change=0.05;
		threshold=1.0;

	
	}
Wind wind;
class Color{
public:
	float red,green,blue;
	};
class butterfly{
public:
	
//body data
float            baseRadius; 
float            topRadius;
float            height; 
int               slices; 
int               stacks;
Color wing_color;
Color body_color;
Color antenna_color;
Color tail_color;
Color head_color;
//coordinate data
float curx,cury,curz;
float destx,desty,destz;
	
//motion data
//distance to be covered at each drawing in three directions;
float dx,dy,dz;
//unit distance;
float cur_goal_distance,velocity;
	
float xaxis,yaxis,zaxis;
float rotation_angle;
//status: flying or sitting

int status;//FLYING or SITTING

//constructor definition
	
   butterfly(int status);
		
	
	};
	
	
	
class flower
	{
	public:
		Color petal_color;
	    Color stalk_color;
		int petals;
		float petal_radius;
		float growth;
		int stalk_size;
		float stalk_angle;
		float x_axis_stalk;
		float y_axis_stalk;
		float z_axis_stalk;
		
		float x,y,z;
		int hasButterfly;
		butterfly *b;

		flower();
	    
	};

//constructor body
  butterfly::butterfly(int status)
	{
	//random variables;
	//srand(time(0));
		quadratic=gluNewQuadric();
	  this->status=status;
	  this->baseRadius=0.01*(2+rand()%2);
	  this->topRadius=this->baseRadius;
	  this->height=0.1*(2+rand()%2);
	  this->slices=15+rand()%15;
	  this->stacks=15+rand()%15;
	  //creating
		
	  if(status==FLYING)
		  {
	  this->curx=RAND[rand()%FLOATS]*(rand()%200);
      this->cury=-2+0.01*(rand()%200);
	  this->curz=RAND[rand()%FLOATS]*(rand()%200);
	  
	  this->destx=this->curx;
	  this->desty=this->cury;
	  this->destz=this->curz+1;
	  
	  

 	  this->xaxis=0.01*(rand()%100);
	  this->yaxis=0.01*(rand()%100);
	  this->zaxis=0.01*(rand()%100);

		  }
	  this->velocity=status*0.1*(1+rand()%5)+0.05;

	  this->body_color.blue=0.01*(rand()%100);
	  this->body_color.green=0.01*(rand()%100);
	  this->body_color.red=0.01*(rand()%100);

	  this->wing_color.blue=0.01*(rand()%100);
	  this->wing_color.green=0.01*(rand()%100);
	  this->wing_color.red=0.01*(rand()%100);

	  this->antenna_color.red=0.01*(rand()%100);
	  this->antenna_color.green=0.01*(rand()%100);
	  this->antenna_color.blue=0.01*(rand()%100);

	  this->head_color.red=0.01*(rand()%100);
	  this->head_color.green=0.01*(rand()%100);
	  this->head_color.blue=0.01*(rand()%100);

	  this->tail_color.red=0.01*(rand()%100);
	  this->tail_color.green=0.01*(rand()%100);
	  this->tail_color.blue=0.01*(rand()%100);
	  
      
	  this->rotation_angle=1.0*(rand()%360);
	  //derived values;
	  this->cur_goal_distance=sqrtf((curx-destx)*((curx-destx))+(cury-desty)*((cury-desty))+(curz-destz)*((curz-destz)));
      
      /*
	  this->dx=unit;
	  this->dy=(desty-cury)/((destx-curx)/dx);
	  this->dz=(destz-curz)/((destx-curx)/dx);
      */
	  dx=0.0;
	  dy=0.0;
	  dz=unit*velocity;
	  if(DEBUG)
		  {
	  cout<<curx<<" "<<cury<<" "<<curz<<endl;
	  cout<<destx<<" "<<desty<<" "<<destz<<endl;
	  cout<<"distance is "<<cur_goal_distance<<endl;
      cout<<"dx="<<dx<<"dy="<<dy<<"dz="<<dz<<endl;
	  cout<<"velocity="<<velocity<<endl;
      
		  
		  }
      
	  //cout<<curx<<endl;
	} 



  flower::flower()
	  {
	  quadratic=gluNewQuadric();		  
	  this->growth=-4+0.01*(rand()%800);
	  
	  this->petals=3+rand()%3;
	  this->petal_color.blue=0.01*(rand()%100);
	  this->petal_color.green=0.01*(rand()%100);
	  this->petal_color.red=0.01*(rand()%100);
	  
	  this->stalk_color.blue=0.2+0.01*(rand()%80);
	  this->stalk_color.green=0.2+0.01*(rand()%80);
	  this->stalk_color.red=0.0;
	 
	  this->petal_radius=0.01*(15+rand()%15);
      
	  this->stalk_angle=1.0+(rand()%10);
	  
	  this->stalk_size=20*this->petal_radius;
	  
	  this->x_axis_stalk=0.01*(rand()%100);
	  this->y_axis_stalk=0.01*(rand()%100);
	  this->z_axis_stalk=0.01*(rand()%100);

	  this->x=RAND[rand()%FLOATS]*(rand()%200);
	  this->y=-5.0;
	  this->z=RAND[rand()%FLOATS]*(rand()%200);
	  
	  if((rand()%3)==1)
		  {
		  this->hasButterfly=1;
		  this->b=new butterfly(SITTING);

		  
		  }
	  else this->hasButterfly=0;
	  
	  
	  
	  }
void drawButterfly(butterfly *b )
{


glPushMatrix();
    
if(b->status==FLYING)
	{
	glRotatef(wind.speed*5,wind.x,wind.y,wind.z);
    glRotatef(b->rotation_angle,b->xaxis,b->yaxis,b->zaxis);
	b->curx+=b->dx*b->velocity;
	b->cury+=b->dy*b->velocity;
	b->curz+=b->dz*b->velocity;


    glTranslatef(b->curx,b->cury,b->curz);
	//cout<<b->curx<<" "<<b->cury<<" "<<b->curz<<endl;
	//cout<<b->dx<<" "<<b->dy<<" "<<b->dz<<endl;

    //glRotatef(90,0.0,1.0,0.0);//rotate the butterfly;
	}


	
	//drawing the tail;
	glColor3f(b->tail_color.red,b->tail_color.green,b->tail_color.blue);
	gluCylinder(quadratic,0.0,b->topRadius,0.3*b->height,b->slices,0.3*b->stacks);
	
	glPushMatrix();
	    //drawing the body
		glTranslatef(0.0,0.0,+0.3*b->height);
		glColor3f(b->body_color.red,b->body_color.green,b->body_color.blue);
		gluCylinder(quadratic,b->baseRadius,b->topRadius,0.5*b->height,b->slices,0.5*b->stacks);
		//drawing the neck
		glTranslatef(0.0,0.0,0.5*b->height);
		gluCylinder(quadratic,0.7*b->baseRadius,0.7*b->topRadius,0.03*b->height,0.5*b->slices,0.1*b->stacks);
		//drawing the head
		glTranslatef(0.0,0.0,0.1*b->height);
		glColor3f(b->head_color.red,b->head_color.green,b->head_color.blue);
		gluSphere(quadratic,b->baseRadius,0.3*b->slices,0.3*b->stacks);
	
		//drawing the antenna
		glColor3f(b->antenna_color.red,b->antenna_color.green,b->antenna_color.blue);
		
		glPushMatrix();
			//glTranslatef(b->baseRadius,0.0,b->baseRadius);
			glRotatef(-60,1.0,0.0,1.0);
			gluCylinder(quadratic,0.05*b->baseRadius,0.1*b->baseRadius,3*b->baseRadius,5,5);
			glTranslatef(0.0,0.0,3*b->baseRadius);
			glRotatef(-20,1.0,0.0,1.0);
			gluCylinder(quadratic,0.05*b->baseRadius,0.1*b->baseRadius,2*b->baseRadius,5,5); 
	
		glPopMatrix();//end of drawing first antenna
    
		//drawing second antenna;

		glPushMatrix();
    
			//glTranslatef(0.0,0.0,0.9*b->height);
			glRotatef(60,-1.0,0.0,1.0);
			gluCylinder(quadratic,0.05*b->baseRadius,0.1*b->baseRadius,3*b->baseRadius,5,5);
			glTranslatef(0.0,0.0,3*b->baseRadius);
			glRotatef(20,-1.0,0.0,1.0);
			gluCylinder(quadratic,0.05*b->baseRadius,0.1*b->baseRadius,2*b->baseRadius,5,5); 
	
		glPopMatrix();
	
		glTranslatef(0.0,0.0,-b->height*0.9);//placing pen on the middle of the butterfly
		glPushMatrix();
		
		float d=2*b->baseRadius;
		glTranslatef(0.0,0.0,b->height/2);
		glRotatef(-angle_wing*b->velocity,0.0f,0.0f,1.0f);
			glColor3f(b->wing_color.red,b->wing_color.green,b->wing_color.blue);
			glBegin(GL_TRIANGLES);
			//drawing the left wing
			glVertex3f(2*d,d/2,d);
			glVertex3f(0,0,0);
			
			glVertex3f(3*d,d/4,2*d);

			glVertex3f(4*d,d/6,d);
			glVertex3f(0,0,0);
			glVertex3f(5*d,0,0);

			glVertex3f(4.5*d,d/6,-d);
			glVertex3f(0,0,0);
			glVertex3f(3*d,d/4,-3*d);
			
			glVertex3f(2*d,d/4,-3*d);


			glEnd();

   		glPopMatrix();
		//drawing the legs;
		glPushMatrix();
		glTranslatef(0.0,0.0,b->height/2);
			//drawing the left leg
			glPushMatrix();
				glRotatef(145,1.0,0.0,-1.0);
				gluCylinder(quadratic,0.1*b->baseRadius,0.08*b->baseRadius,5*b->baseRadius,4,4);
		
				glTranslatef(0.0,0.0,5*b->baseRadius);

				glRotatef(-80,1.0,0.0,0.0);
				gluCylinder(quadratic,0.08*b->baseRadius,0.09*b->baseRadius,7*b->baseRadius,4,4);
			glPopMatrix();
			//drawing right leg
			glPushMatrix();
			glRotatef(145,1.0,0.0,1.0);
			gluCylinder(quadratic,0.1*b->baseRadius,0.08*b->baseRadius,5*b->baseRadius,4,4);
		
			glTranslatef(0.0,0.0,5*b->baseRadius);

			glRotatef(-80,1.0,0.0,0.0);
			gluCylinder(quadratic,0.08*b->baseRadius,0.09*b->baseRadius,7*b->baseRadius,4,4);
			glPopMatrix();

			//drawing front legs
			//drawing left-fron leg
			glPushMatrix();
				glRotatef(45,1.0,0.0,-1.0);
				gluCylinder(quadratic,0.1*b->baseRadius,0.08*b->baseRadius,4*b->baseRadius,4,4);
		
				glTranslatef(0.0,0.0,5*b->baseRadius);

				glRotatef(80,1.0,0.0,0.0);
				gluCylinder(quadratic,0.08*b->baseRadius,0.09*b->baseRadius,6*b->baseRadius,4,4);
			glPopMatrix();
			//drawing right-front leg
			glPushMatrix();
			glRotatef(45,1.0,0.0,1.0);
			gluCylinder(quadratic,0.1*b->baseRadius,0.08*b->baseRadius,4*b->baseRadius,4,4);
		
			glTranslatef(0.0,0.0,5*b->baseRadius);

			glRotatef(80,1.0,0.0,0.0);
			gluCylinder(quadratic,0.08*b->baseRadius,0.09*b->baseRadius,6*b->baseRadius,4,4);
			glPopMatrix();

		glPopMatrix();

		

		//drawing the right wing

		glPushMatrix();
		glTranslatef(0.0,0.0,b->height/2);
		glRotatef(angle_wing*b->velocity,0.0f,0.0f,1.0f);
			glBegin(GL_TRIANGLES);

			glVertex3f(-2*d,d/2,d);
			glVertex3f(0,0,0);
			
			glVertex3f(-3*d,d/4,2*d);

			glVertex3f(-4*d,d/6,d);
			glVertex3f(0,0,0);
			glVertex3f(-5*d,0,0);

			glVertex3f(-4.5*d,d/6,-d);
			glVertex3f(0,0,0);
			glVertex3f(-3*d,d/4,-3*d);
			
			glVertex3f(-2*d,d/4,-3*d);


			glEnd();
		glPopMatrix();
	glPopMatrix();	
glPopMatrix();
}








void drawFlower(flower *f)
	{
	float x,y,z,x1,angle,radian_angle,y1=0.0,z1,x2,y2,z2;
	float r=2.0;//radius
	float petal=0,angle_petal=90;
	
	glPushMatrix();
	glTranslatef(f->x,f->y,f->z);
	glRotatef(-90,1.0,0.0,0.0);//making the stalk straight upwards
	glColor3f(f->stalk_color.red,f->stalk_color.green,f->stalk_color.blue);
	//glColor3f(1.0,0.0,0.0);
	for(int i=0;i<f->stalk_size;i++)
		{	
		glRotatef(wind.speed*10,wind.x,wind.y,wind.z);
		glRotatef(f->stalk_angle,f->x_axis_stalk,f->y_axis_stalk,f->z_axis_stalk);
		
		gluCylinder(quadratic,0.08*f->petal_radius,0.08*f->petal_radius,5*f->petal_radius,5,5);
		
		glTranslatef(0.0,0.0,5*f->petal_radius);//going to draw next stem;
		if(i>(f->stalk_size-4)&&i<f->stalk_size-1)
			{
			    
			for(petal=0;petal<f->stalk_size-2;petal++)
				{
			
				glRotatef(360/(f->stalk_size-2),0.0,0.0,1.0);
				
			    radian_angle=0;
				y1=0;
				glBegin(GL_QUAD_STRIP);
				for(angle=0;angle<=180;y1-=0.08)
					{   
					//glColor3f(0.5,0.5,0.5);
						
					x1=f->petal_radius*sinf(radian_angle);
					z1=f->petal_radius*cosf(radian_angle)-f->petal_radius;
						//if(i%2)
						//cout<<"angle is"<<angle<<endl;
						//cout<<x1<<" "<<y1<<" "<<z1<<endl;
							{
					   	
							glVertex3f(-x1,y1,z1);
							glVertex3f(x1,y1,z1);
						
						
							}
						if(angle>159)angle+=10;
						else angle+=20;
						radian_angle=(3.1416/180)*angle;
			}
				glEnd();

			
				}
			
			}

			
		
		}
      glColor3f(0.80,0.0,0.0);
	  gluCylinder(quadratic,0.08*f->petal_radius,0.4*f->petal_radius,0.05,5,3);
	glRotatef(90,1.0,0.0,0.0);




	
	glColor3f(f->petal_color.red,f->petal_color.green,f->petal_color.blue);
	
	 /*
	glVertex3f(1,0,0);
	glVertex3f(-1,0,0);
	glVertex3f(2,-0.2,0);
	glVertex3f(-2,-0.2,0);
	
	glVertex3f(5,-0.5,0);
	glVertex3f(-5,-0.5,0);
	// */
	//	/*
	        int i=0;
			
			for(petal=0;petal<f->petals;petal++)
				{
			
				glRotatef(360/f->petals,0.0,1.0,0.0);
				
			    radian_angle=0;
				glBegin(GL_QUAD_STRIP);
				for(angle=0;angle<=180;y1=f->growth*f->petal_radius*sinf(radian_angle))
					{   
					//glColor3f(0.5,0.5,0.5);
						
					x1=f->petal_radius*sinf(radian_angle);
					z1=f->petal_radius*cosf(radian_angle)-f->petal_radius;
						//if(i%2)
						//cout<<"angle is"<<angle<<endl;
						//cout<<x1<<" "<<y1<<" "<<z1<<endl;
							{
					   	
							glVertex3f(-x1,y1,z1);
							glVertex3f(x1,y1,z1);
						
						
							}
						if(angle>159)angle+=10;
						else angle+=20;
						radian_angle=(3.1416/180)*angle;
			}
				glEnd();

			
				}
				//*/
			if(f->hasButterfly)
				{
				glTranslatef(0.0,0.0,-f->b->height/2);
				glTranslatef(0.0,0.2,0.0);
				//glPushMatrix();
				drawButterfly(f->b);
				//glPopMatrix();
				}
	glPopMatrix();
			
			
			
	}
