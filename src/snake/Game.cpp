#include "Game.hpp"

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glkos.h>

const int kScreenWidth = 640;
const int kScreenHeight = 480;
const int kBlockSize = 480 / 50;

inline void prologue(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear both buffers
    glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

inline const void epilogue()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Color4ub
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void fill_rect(const Vector3 pts[4], const Color4ub color)
{
	prologue();

	glColor4ub(color.r, color.g, color.b, color.a);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(pts[0].x, pts[0].y, pts[0].z);
	glVertex3f(pts[1].x, pts[1].y, pts[1].z);
	glVertex3f(pts[3].x, pts[3].y, pts[3].z);
	glVertex3f(pts[2].x, pts[2].y, pts[2].z);
	glEnd();

	epilogue();
}

void draw_gl(void)
{
    prologue();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear both buffers

    float s = 50.f;
    float z = -10.f;  // Keep it static for now to ensure visibility

    glLoadIdentity();
    
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 0.0f, 0.0f);  // Red
    glVertex3f( 0.0f,  s,  z);  // Top
    
    glColor3f(0.0f, 1.0f, 0.0f);  // Green
    glVertex3f(-s, -s, z);  // Bottom left
    
    glColor3f(0.0f, 0.0f, 1.0f);  // Blue
    glVertex3f( s, -s, z);  // Bottom right
    
    glEnd();
    epilogue();
}

Game::Game()
{
    glKosInit();
}


void Game::run()
{
    maple_device_t *controller;
    cont_state_t *cont;
    int w = 640;
    int h = 480;
    glKosInit();
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f); // This Will Clear The Background Color To Black
	glClearDepth(1.0);					  // Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);				  // The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);			  // Enables Depth Testing
	glShadeModel(GL_FLAT);				  // Enables Smooth Color Shading
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h); // Reset The Current Viewport And Perspective Transformation

	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	
    glMatrixMode(GL_MODELVIEW);
    float z = -10.0f;
    float r = 0.0f;
    while (true)
    {
        r += 0.5f;
        if(r > 360.0f)r = 0.0f;
        const Color4ub green_ub(0, 255, 0, 255);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glClearColor(0.52f, 0.8f, 0.9f, 1.0f);
        // glClear for Color buffer may trigger issue on dreamcast (to check)
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        glRotatef(r, 0.0f, 0.0f, 1.0f);
        fill_rect((Vector3[4]){{0, 0, z}, {0, 50, z}, {50, 50, z}, {50, 0, z}}, green_ub);
        glRotated(-r, 0.0f, 0.0f, 1.0f);
        //z+= 0.5f;
        if(z > 100.0f)z = -50.0f;
        glMatrixMode(GL_MODELVIEW);
        glKosSwapBuffers();
    }
}
