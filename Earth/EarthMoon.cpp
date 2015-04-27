
 #include "Planet.hpp"
#include "SpaceBox.hpp"




#define TWOPI 2*3.142
//texture[0]: Background texture, texture[1]:Earth texture and texture[2]:Moon texture

static GLuint texture[3];
//Quads for the Sphere		
GLUquadricObj* Sphere;
/*earthAngle is the Earth's angle of Rotation
  moonAngle is the angle of Orbit at which the Moon has to revolve around earth
  lighAngle is the angle of Orbit at which the Sun(Light Source) revolves
  (here we assume the Earth is at centre)*/
float earthAngle=0,moonAngle=0,lightAngle=0;
// angle of rotation for the camera direction
float CameraAngle=0.0;
// actual vector representing the camera's direction
float xPlane=0.0f,zPlane=-1.0f,yPlane=0.0f;
//position of the camera in the XZ plane
float x=0.0f,z=5.0f,y=1.0f;

int pause=0;

//Create an object of the class Planet and SpaceBox
SpaceBox SB;
Planet planet;

//Select the Texture [Press 0-7]
void SelectTexture(unsigned char key, int x, int y)
{ 
  switch(key)
  {
    case '0':
      texture[1]=planet.GetTexture("Images/ColorMap.png",0);
      return;
    case '1':
      texture[1]=planet.GetTexture("Images/Earth1.png",0);
      return;
    case '2':
      texture[1]=planet.GetTexture("Images/Clouds.png",0);
      return;
    case '3':
      texture[1]=planet.GetTexture("Images/Clouds1.png",0);
      return;
    case '4':
      texture[1]=planet.GetTexture("Images/Clouds2.png",0);
      return;
    case '5':
      texture[1]=planet.GetTexture("Images/Night.png",0);
      return;
    case '6':
      texture[1]=planet.GetTexture("Images/Bump.png",0);
      return;
    case '7':
      texture[1]=planet.GetTexture("Images/earth.png",0);
      return;
    case 'w':
      CameraAngle += 0.02f;
      yPlane = sin(CameraAngle);
      zPlane = -cos(CameraAngle);
      break;
    case 's':
      CameraAngle -= 0.02f;
      yPlane = sin(CameraAngle);
      zPlane = -cos(CameraAngle);
      break;
  }
}

//Changing the Camera View
void MoveCamera(int key, int xx, int yy)
{

  float Change = 0.1f;

  switch (key) 
  {
    case GLUT_KEY_LEFT :
      CameraAngle -= 0.02f;
      xPlane = sin(CameraAngle);
      zPlane = -cos(CameraAngle);
      break;
    case GLUT_KEY_RIGHT :
      CameraAngle += 0.02f;
      xPlane = sin(CameraAngle);
      zPlane = -cos(CameraAngle);
      break;
    case GLUT_KEY_UP :
      x += xPlane * Change;
      y += yPlane * Change;
      z += zPlane * Change;
      break;
    case GLUT_KEY_DOWN :
      x -= xPlane * Change;
      z -= zPlane * Change;
      y -= yPlane * Change;
      break;
  }
}

void init() 
{

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  texture[0]=SB.LoadTexture("Images/stars.png");
  Sphere= gluNewQuadric();
  
  glEnable(GL_COLOR_MATERIAL);
  //Earth's Texture
  texture[1]=planet.GetTexture("Images/ColorMap.png",0);
  glutKeyboardFunc(SelectTexture);
  //Moon's Texture
  texture[2]=planet.GetTexture("Images/Moon.png",0);
}

//Resize the window whenever the window dimensions are explicitly changed
void Resize(int w, int h) 
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);

}

void display() 
{ 

  
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //Set the Camera Position
    gluLookAt(x, y, z, x + xPlane, y + yPlane,  z + zPlane, 0.0f, 1.0f,  0.0f);
    

    //render the skybox(in this case SpaceBox) around the earth and moon
    SB.render(0,0,0,250,250,250,texture[0]);

    //Bring the view 16 units away from the centre 
    glTranslatef(0.0f, 0.0f, -16.0f);

    

  	//Enable the Sunlight and intitialize its Position
  	planet.SunLight(lightAngle);

  	//Earth
  	planet.Earth(earthAngle,texture[1],Sphere);

  	//Longitudes and latitudes
  	//planet.LongLat(earthAngle);

  	//Calculate the orbit on which the Moon revolves around Earth
  	float xAxis = (float) sin(moonAngle) * 7;
  	float zAxis = (float) cos(moonAngle) * 5;

  	//display the orbit
  	planet.Orbit(xAxis,zAxis);

    //Moon
  	planet.Moon(xAxis,zAxis,texture[2],Sphere);

  	//Swap the Buffers and display
    glutSwapBuffers();
  
    //Disable the Lights and the textures
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    
    glFlush();
}
void wait(int value)
{ 
    if(!pause)
    {
      moonAngle+=0.005f;
      if(moonAngle>TWOPI)
      {
        	moonAngle=0;
      }

      lightAngle+=0.002f;
      if(lightAngle>TWOPI)
      {
        	lightAngle=0;
      }

      earthAngle+=0.1f;
      if(earthAngle>360.0f)
      {
          	earthAngle=0;
      }
    }

    glutPostRedisplay();
    glutTimerFunc(25,wait,0);
}


//Pause the Rotation
void Pause(int button,int state,int x,int y)
{
  
    if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN) 
    {
       pause=!pause;
       return;
    }
    
}

int main(int argc, char** argv)
{ 
     //Initializers
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
     glutInitWindowSize(800, 600);
     glutInitWindowPosition(100, 100);
     glutCreateWindow("The Earth");
     init();
     //Set the CallBack functions
     glutDisplayFunc(display);
     glutReshapeFunc(Resize);
     glutTimerFunc(25,wait,0);
     glutSpecialFunc(MoveCamera);
     glutMouseFunc(Pause);
    
     //Infinite Loop
     glutMainLoop();
     return 0; 
}