
#include "Planet.hpp"

using namespace std;

Planet::Planet()
{
	return;
}

GLuint Planet::GetTexture(string  file)
{
  	const char * filename = file.c_str();
  	GLuint texture_id;
  	int width, height;
  	unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
  	texture_id= SOIL_load_OGL_texture(
     	   filename,
     	   SOIL_LOAD_AUTO,
    	    SOIL_CREATE_NEW_ID,
     	   SOIL_FLAG_POWER_OF_TWO
     	   | SOIL_FLAG_MIPMAPS
     	   | SOIL_FLAG_MULTIPLY_ALPHA
     	   | SOIL_FLAG_COMPRESS_TO_DXT
     	   | SOIL_FLAG_DDS_LOAD_DIRECT| SOIL_FLAG_INVERT_Y
     	   );
  	
    if( texture_id > 0 )
    { 
      delete image;
      return texture_id;
    }
    else
      return 0;
}

//Set Background texture
/*void BackGroundTexture() 
{
  glMatrixMode(GL_PROJECTION);
  //glPushMatrix();
  //glOrtho(0, 1, 0, 1, 0, 1);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  
  
  texture[0]=GetTexture("stars.png");
  glEnable(GL_TEXTURE_2D);
  glBindTexture( GL_TEXTURE_2D, texture[0] );
  glBegin( GL_QUADS ); 
    glTexCoord2f( 0, 0 );glVertex2f( 0, 0 );
    glTexCoord2f( 0, 800 );glVertex2f( 0, 800 );
    glTexCoord2f( 600, 800 );glVertex2f( 600, 800 );
    glTexCoord2f( 600, 0 );glVertex2f( 600, 0 );
  glEnd();

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  //glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}*/
void Planet::SunLight(float lightAngle)
{
	float XPos=-9,ZPos=9;
  	XPos = (float) sin(lightAngle) * 11;
  	ZPos = (float) cos(lightAngle) * 8;
  	//glColor3f(1, 0, 0);
  	glEnable(GL_LIGHTING);
  	glEnable(GL_LIGHT0);
  
  	float ambientLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
  	float diffuseLight[] = { 1.0f, 1.0f, 1.0f, 0.0f };
  	//float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
  	float position[] = { XPos, 0.0f, ZPos, 1.0f }; 
  	//Assign created components to GL_LIGHT0 
  	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); 
  	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); 
  	//glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight); 
  	glLightfv(GL_LIGHT0, GL_POSITION, position);

}

//render Earth
void Planet::Earth(float earthAngle,GLuint texture,GLUquadricObj* Sphere)
{
	glPushMatrix();
  	glEnable(GL_TEXTURE_2D);
  	glBindTexture(GL_TEXTURE_2D, texture);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  	glRotatef(90.0,1.0f,0.0f,0.0f);
  	glRotatef(180.0,0.0f,1.0f,0.0f);
  	glRotatef(earthAngle,0.0f,0.0f,1.0f);
  	gluQuadricDrawStyle(Sphere, GLU_FILL);
  	gluQuadricTexture(Sphere, TRUE);
  	gluQuadricNormals(Sphere, GLU_SMOOTH);
  	gluSphere(Sphere,3,32,32);
  	glPopMatrix();
}

//render Moon
void Planet::Moon(float xAxis,float zAxis,GLuint texture,GLUquadricObj* Sphere)
{
	glPushMatrix();
  	glTranslatef(0,1,1);
  	glBindTexture(GL_TEXTURE_2D, texture);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  	glTranslatef(xAxis, 0,zAxis);
  	gluQuadricDrawStyle(Sphere, GLU_FILL);
  	gluQuadricTexture(Sphere, TRUE);
  	gluQuadricNormals(Sphere, GLU_SMOOTH);
  	gluSphere(Sphere,0.9f,32,32);
  	glPopMatrix();
}

//display the Orbit
void Planet::Orbit(float x,float z)
{
	glPushMatrix();
  	glColor3f(1,1,1);
  	glVertex3f(x,0,z);
  	glPopMatrix();
}

//display the Longitudes and Latitudes
void Planet::LongLat(float earthAngle)
{
	glPushMatrix();

  	glColor3f(1,1,1);
  	glRotatef(90.0,1.0f,0.0f,0.0f);
  	glRotatef(earthAngle,0.0f,0.0f,-1.0f);
  	glutWireSphere(3.03f,36,18);
 	//glClearColor(1,1,1,1);
  	glPopMatrix();

  	return;
}