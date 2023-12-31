#include <windows.h>		// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <cmath>
#include "texture.h"
#include "Point.h"
#include "PrimitiveDrawer.h"

#include "camera.h"

GLUquadricObj* b = gluNewQuadric();
PrimitiveDrawer::PrimitiveDrawer() {}
float M_PI = 3.14159265358979323846;
void PrimitiveDrawer::drawSphere(Point center, float radius, int numSlices, int numStacks) {
    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);

    //const float PI = 3.14159265358979323846;

    for (int i = 0; i <= numSlices; ++i) {
        float lat0 = PI * (-0.5 + (float)(i - 1) / numSlices);
        float z0 = radius * sin(lat0);
        float zr0 = radius * cos(lat0);

        float lat1 = PI * (-0.5 + (float)i / numSlices);
        float z1 = radius * sin(lat1);
        float zr1 = radius * cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= numStacks; ++j) {
            float lng = 2 * PI * (float)(j - 1) / numStacks;
            float x = cos(lng);
            float y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);

            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }

    glPopMatrix();
}
void PrimitiveDrawer::drawSphereWithTexture(Point center, float radius, int numSlices, int numStacks, int textureID) {
    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);

    for (int i = 0; i < numSlices; ++i) {
        float lat0 = PI * (-0.5 + (float)(i - 1) / numSlices);
        float z0 = radius * sin(lat0);
        float zr0 = radius * cos(lat0);

        float lat1 = PI * (-0.5 + (float)i / numSlices);
        float z1 = radius * sin(lat1);
        float zr1 = radius * cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= numStacks; ++j) {
            float lng = 2 * PI * (float)j / numStacks;
            float x = cos(lng);
            float y = sin(lng);

            glTexCoord2f((float)i / numSlices, (float)j / numStacks);
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);

            glTexCoord2f((float)(i + 1) / numSlices, (float)j / numStacks);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


void PrimitiveDrawer::drawCylinder(Point center, float radius, float height, int numSlices) {
    glPushMatrix();

    glTranslatef(center.x, center.y + 1, center.z);
    glRotated(90, 1, 0, 0);
    //const float PI = 3.14159265358979323846;

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numSlices; ++i) {
        float angle = 2.0 * PI * (float)i / numSlices;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Bottom point
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x, y, 0.0f);

        // Top point
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x, y, height);
    }
    glEnd();

    // Draw the top and bottom circles
    glBegin(GL_POLYGON);
    for (int i = 0; i <= numSlices; ++i) {
        float angle = 2.0 * PI * (float)i / numSlices;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Bottom circle
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x, y, 0.0f);

        // Top circle
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x, y, height);
    }
    glEnd();

    glPopMatrix();
}

void PrimitiveDrawer::drawCylinderWithTexture(Point center, float radius, float height, int numSlices, int textureID) {
    glPushMatrix();
    glTranslatef(center.x, center.y + 1, center.z);
    glRotated(90, 1, 0, 0);

    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);

    // Draw the sides of the cylinder
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= numSlices; ++i) {
        float angle = 2.0 * PI * (float)i / numSlices;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Bottom point
        glTexCoord2f((float)i / numSlices, 0.0);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x, y, 0.0f);

        // Top point
        glTexCoord2f((float)i / numSlices, 1.0);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x, y, height);
    }
    glEnd();

    // Draw the top and bottom circles
    glBegin(GL_POLYGON);
    for (int i = 0; i <= numSlices; ++i) {
        float angle = 2.0 * PI * (float)i / numSlices;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Bottom circle
        glTexCoord2f(0.5 + 0.5 * cos(angle), 0.5 + 0.5 * sin(angle));
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(x, y, 0.0f);

        // Top circle
        glTexCoord2f(0.5 + 0.5 * cos(angle), 0.5 + 0.5 * sin(angle));
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(x, y, height);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}




// Draw a point at the given position.
void PrimitiveDrawer::DrawPoint(Point point) {
    glBegin(GL_POINTS);
    //  glColor3b(1, 0,0);
    glVertex3f(point.x, point.y, point.z);
    glEnd();
}

// Draw a line between the given two positions.
void PrimitiveDrawer::DrawLine(Point start, Point end) {
    glBegin(GL_LINES);
    glVertex3f(start.x, start.y, start.z);
    glVertex3f(end.x, end.y, end.z);
    glEnd();
}
void PrimitiveDrawer::DrawTr(Point v1, Point v2, Point v3)
{
    glBegin(GL_TRIANGLES);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glEnd();
}

void PrimitiveDrawer::DrawTrWithTexture(Point v1, Point v2, Point v3, int image)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, image);
    glBegin(GL_TRIANGLES);

    // Texture coordinates for each vertex
    glTexCoord2f(0, 0);
    glVertex3f(v1.x, v1.y, v1.z);

    glTexCoord2f(0, 1);
    glVertex3f(v2.x, v2.y, v2.z);

    glTexCoord2f(1, 1);
    glVertex3f(v3.x, v3.y, v3.z);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}




void PrimitiveDrawer::DrawQuad(Point v1, Point v2, Point v3, Point v4) {
    glBegin(GL_QUADS);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glVertex3f(v4.x, v4.y, v4.z);
    glEnd();
}void PrimitiveDrawer::DrawQuadWithTexture(Point v1, Point v2, Point v3, Point v4,int image) {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, image);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(0, -1);
    glVertex3f(v2.x, v2.y, v2.z);
    glTexCoord2f(-1, -1);

    glVertex3f(v3.x, v3.y, v3.z);
   
    glTexCoord2f(-1, 0);
    glVertex3f(v4.x, v4.y, v4.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}









void PrimitiveDrawer::QuadWithHigh(Point v1, float width, float size, float height) {
    glBegin(GL_QUADS);
    // Bottom face
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v1.x + width, v1.y, v1.z);
    glVertex3f(v1.x + width, v1.y + size, v1.z);
    glVertex3f(v1.x, v1.y + size, v1.z);
    glEnd();

    glBegin(GL_QUADS);
    // Front face
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v1.x + width, v1.y, v1.z);
    glVertex3f(v1.x + width, v1.y, v1.z + height);
    glVertex3f(v1.x, v1.y, v1.z + height);
    glEnd();
    // Right face
    glBegin(GL_QUADS);
    glVertex3f(v1.x + width, v1.y, v1.z);
    glVertex3f(v1.x + width, v1.y + size, v1.z);
    glVertex3f(v1.x + width, v1.y + size, v1.z + height);
    glVertex3f(v1.x + width, v1.y, v1.z + height);
    glEnd();
    // Left face
    glBegin(GL_QUADS);

    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v1.x, v1.y + size, v1.z);
    glVertex3f(v1.x, v1.y + size, v1.z + height);
    glVertex3f(v1.x, v1.y, v1.z + height);
    glEnd();
    // Back face
    glBegin(GL_QUADS);
    glVertex3f(v1.x, v1.y + size, v1.z);
    glVertex3f(v1.x + width, v1.y + size, v1.z);
    glVertex3f(v1.x + width, v1.y + size, v1.z + height);
    glVertex3f(v1.x, v1.y + size, v1.z + height);
    glEnd();
    // Top face
    glBegin(GL_QUADS);
    glVertex3f(v1.x, v1.y, v1.z + height);
    glVertex3f(v1.x + width, v1.y, v1.z + height);
    glVertex3f(v1.x + width, v1.y + size, v1.z + height);
    glVertex3f(v1.x, v1.y + size, v1.z + height);

    glEnd();
}
void PrimitiveDrawer::QuadWithHighAndTexture(Point v1, float width, float size, float height, int bottomImage, int frontImage, int rightImage, int leftImage, int backImage, int topImage) {
    // Bottom face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, bottomImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + width, v1.y, v1.z);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + width, v1.y + size, v1.z);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + size, v1.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Front face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, frontImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + width, v1.y, v1.z);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + width, v1.y, v1.z + height);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y, v1.z + height);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Right face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, rightImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(v1.x + width, v1.y, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + width, v1.y + size, v1.z);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + width, v1.y + size, v1.z + height);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x + width, v1.y, v1.z + height);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Left face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, leftImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(v1.x, v1.y, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x, v1.y + size, v1.z);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x, v1.y + size, v1.z + height);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y, v1.z + height);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Back face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(v1.x, v1.y + size, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + width, v1.y + size, v1.z);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + width, v1.y + size, v1.z + height);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + size, v1.z + height);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Top face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, topImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(v1.x, v1.y, v1.z + height);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + width, v1.y, v1.z + height);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + width, v1.y + size, v1.z + height);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + size, v1.z + height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void PrimitiveDrawer::SmallMinaret(Point v1,float scaleX ,float scaleY,float scaleZ)
{
    glPushMatrix(); // Save the current matrix

    // Translate to the specified position
    glTranslatef(v1.x, v1.y, v1.z);

    // Apply scaling
    glScalef(scaleX, scaleY, scaleZ);
    // Draw the cube
    glBegin(GL_QUADS);
    // Bottom face
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(2,  2, 0);
    glVertex3f(0,  2, 0);
    glEnd();

    glBegin(GL_QUADS);
    // Front face
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);
    glVertex3f(2, 0, 2);
    glVertex3f(0, 0, 2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glVertex3f(2, 0, 0);
    glVertex3f(2, 2, 0);
    glVertex3f(2, 2, 2);
    glVertex3f(2, 0, 2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(0, 2, 2);
    glVertex3f(0, 0, 2);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glVertex3f(0, 2, 0);
    glVertex3f(2, 2, 0);
    glVertex3f(2,2,2);
    glVertex3f(0, 2,  2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 2);
    glVertex3f(2, 0, 2);
    glVertex3f(2, 2, 2);
    glVertex3f(0, 2, 2);
    glEnd();

   
    // Draw the sphere on top of the cube
    PrimitiveDrawer r = PrimitiveDrawer();
    r.drawSphere(Point( 1, 2, 1), 0.75, 50, 50);
    glPopMatrix();
}

void PrimitiveDrawer::SmallMinaretWithTexture(Point v1, float scaleX, float scaleY, float scaleZ,
    int bottomImage, int frontImage, int rightImage,
    int leftImage, int backImage, int topImage,
    int sphereTexture)
{
    glPushMatrix(); // Save the current matrix

    // Translate to the specified position
    glTranslatef(v1.x, v1.y, v1.z);

    // Apply scaling
    glScalef(scaleX, scaleY, scaleZ);

    // Draw the cube with textured faces
    glEnable(GL_TEXTURE_2D);

    // Bottom face
    glBindTexture(GL_TEXTURE_2D, bottomImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(2, 0, 0);
    glTexCoord2f(1, 1); glVertex3f(2, 2, 0);
    glTexCoord2f(0, 1); glVertex3f(0, 2, 0);
    glEnd();

    // Front face
    glBindTexture(GL_TEXTURE_2D, frontImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(2, 0, 0);
    glTexCoord2f(1, 1); glVertex3f(2, 0, 2);
    glTexCoord2f(0, 1); glVertex3f(0, 0, 2);
    glEnd();

    // Right face
    glBindTexture(GL_TEXTURE_2D, rightImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(2, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(2, 0, 2);
    glTexCoord2f(1, 1); glVertex3f(2, 2, 2);
    glTexCoord2f(0, 1); glVertex3f(2, 2, 0);
    glEnd();

    // Left face
    glBindTexture(GL_TEXTURE_2D, leftImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 2);
    glTexCoord2f(1, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(1, 1); glVertex3f(0, 2, 0);
    glTexCoord2f(0, 1); glVertex3f(0, 2, 2);
    glEnd();

    // Back face
    glBindTexture(GL_TEXTURE_2D, backImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0, 2, 2);
    glTexCoord2f(1, 0); glVertex3f(2, 2, 2);
    glTexCoord2f(1, 1); glVertex3f(2, 2, 0);
    glTexCoord2f(0, 1); glVertex3f(0, 2, 0);
    glEnd();

    // Top face
    glBindTexture(GL_TEXTURE_2D, topImage);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 2);
    glTexCoord2f(1, 0); glVertex3f(2, 0, 2);
    glTexCoord2f(1, 1); glVertex3f(2, 2, 2);
    glTexCoord2f(0, 1); glVertex3f(0, 2, 2);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Draw the sphere on top of the cube with a texture
    PrimitiveDrawer r = PrimitiveDrawer();
    r.drawSphereWithTexture(Point(1, 2, 1), 0.75, 50, 50, sphereTexture);

    glPopMatrix();
}








void PrimitiveDrawer::Columns(Point v1, int bottomImage, int frontImage, int rightImage, int leftImage, int backImage, int topImage)
{
    int rightSideMosqueFront2front;
    PrimitiveDrawer r = PrimitiveDrawer();
    rightSideMosqueFront2front = LoadTexture("wall2.bmp", 255);
    // Draw the four columns
    for (int i = 0; i < 8; i += 2)
    {
       
        r.drawCylinderWithTexture(Point(v1.x + 0.5, v1.y, v1.z + i + 0.5), 0.3, -4, 50, rightSideMosqueFront2front);
    }
    
    // Draw the quads above the cylinders
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, bottomImage);
    glBegin(GL_QUADS);
    // Bottom face
    glVertex3f(v1.x, v1.y + 5, v1.z);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + 7);
    glVertex3f(v1.x, v1.y + 5, v1.z + 7);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, frontImage);
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(v1.x, v1.y + 5, v1.z);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + 7);
    glVertex3f(v1.x, v1.y + 5, v1.z + 7);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Right face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, rightImage);
    glBegin(GL_QUADS);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + 7);
    glVertex3f(v1.x + 1, v1.y + 4, v1.z + 7);
    glVertex3f(v1.x + 1, v1.y + 4, v1.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Left face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, leftImage);
    glBegin(GL_QUADS);
    glVertex3f(v1.x, v1.y + 5, v1.z);
    glVertex3f(v1.x, v1.y + 5, v1.z + 7);
    glVertex3f(v1.x, v1.y + 4, v1.z + 7);
    glVertex3f(v1.x, v1.y + 4, v1.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // Back face
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, backImage);
    glBegin(GL_QUADS);
    glVertex3f(v1.x, v1.y + 5, v1.z + 7);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + 7);
    glVertex3f(v1.x + 1, v1.y + 4, v1.z + 7);
    glVertex3f(v1.x, v1.y + 4, v1.z + 7);
    glEnd();
    glDisable(GL_TEXTURE_2D);


}
void PrimitiveDrawer::ColumnsWithTexture(Point v1, int image)
{
    PrimitiveDrawer r = PrimitiveDrawer();

    // Draw the four columns
    for (int i = 0; i < 8; i += 2)
    {
        r.drawCylinderWithTexture(Point(v1.x + 0.5, v1.y, v1.z + i + 0.5), 0.5, -4, 50, image);
    }

    // Draw the quads above the cylinders
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, image);

    glBegin(GL_QUADS);
    // Bottom face
    glTexCoord2f(0, 0);
    glNormal3f(0, -1, 0);
    glVertex3f(v1.x, v1.y + 5, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + 7);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + 5, v1.z + 7);
    glEnd();

    // Front face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glNormal3f(0, 0, -1);
    glVertex3f(v1.x, v1.y + 5, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + 7);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + 5, v1.z + 7);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glNormal3f(1, 0, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + 7);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + 1, v1.y + 4, v1.z + 7);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x + 1, v1.y + 4, v1.z);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glNormal3f(-1, 0, 0);
    glVertex3f(v1.x, v1.y + 5, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x, v1.y + 5, v1.z + 7);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x, v1.y + 4, v1.z + 7);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + 4, v1.z);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glNormal3f(0, 0, 1);
    glVertex3f(v1.x, v1.y + 5, v1.z + 7);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + 7);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + 1, v1.y + 4, v1.z + 7);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + 4, v1.z + 7);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void PrimitiveDrawer::ColumnsWithTextureAndNum(Point v1, int numColumns, int image)
{
    PrimitiveDrawer r = PrimitiveDrawer();

    // Draw the columns
    for (int i = 0; i < numColumns*2; i+=2)
    {
        r.drawCylinderWithTexture(Point(v1.x + 0.5, v1.y, v1.z + i + 0.5), 0.5, -4, 50, image);
    }

    // Draw the quads above the cylinders
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, image);

  
   
    glBegin(GL_QUADS);
    // Bottom face
    glTexCoord2f(0, 0);
    glNormal3f(0, -1, 0);
    glVertex3f(v1.x, v1.y + 5, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z );
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z );
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + 5, v1.z );
    glEnd();

    // Front face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glNormal3f(0, 0, -1);
    glVertex3f(v1.x, v1.y + 5, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + numColumns * 2 - 1);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + 5, v1.z + numColumns * 2 - 1);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glNormal3f(1, 0, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + numColumns * 2 - 1);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + 1, v1.y + 4, v1.z + numColumns * 2 - 1);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x + 1, v1.y + 4, v1.z);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glNormal3f(-1, 0, 0);
    glVertex3f(v1.x, v1.y + 5, v1.z);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x, v1.y + 5, v1.z + numColumns * 2 - 1);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x, v1.y + 4, v1.z + numColumns * 2 - 1);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + 4, v1.z);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glNormal3f(0, 0, 1);
    glVertex3f(v1.x, v1.y + 5, v1.z + numColumns * 2 - 1);
    glTexCoord2f(1, 0);
    glVertex3f(v1.x + 1, v1.y + 5, v1.z + numColumns * 2 - 1);
    glTexCoord2f(1, 1);
    glVertex3f(v1.x + 1, v1.y + 4, v1.z + numColumns * 2 - 1);
    glTexCoord2f(0, 1);
    glVertex3f(v1.x, v1.y + 4, v1.z + numColumns * 2 - 1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
