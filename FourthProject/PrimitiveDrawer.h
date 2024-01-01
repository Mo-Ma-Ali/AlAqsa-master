#pragma once
#include "Point.h"
#ifndef PRIMITIVEDRAWER_H
#define PRIMITIVEDRAWER_H

class PrimitiveDrawer {
public:
	PrimitiveDrawer();
	void drawSphere(Point center, float radius, int numSlices, int numStacks);
	void drawSphereWithTexture(Point center, float radius, int numSlices, int numStacks, int textureID);
	void drawCylinder(Point center, float radius, float height, int numSlices);
	void drawCylinderWithTexture(Point center, float radius, float height, int numSlices, int textureID);
	void DrawPoint(Point point);
	void DrawLine(Point start, Point end);

	void DrawQuad(Point v1, Point v2, Point v3, Point v4);
	void DrawQuadWithTexture(Point v1, Point v2, Point v3, Point v4, int image);
	void QuadWithHigh(Point v1, float wedth, float size, float high);
	void QuadWithHighAndTexture(Point v1, float width, float size, float height, int bottomImage, int frontImage, int rightImage, int leftImage, int backImage, int topImage);
	void QuadWithHighAndTextureMainGround(Point v1, float width, float size, float height, int image,int norepeat);
	void QuadWithHighAndTextureMainWall(Point v1, float width, float size, float height, int image, int noRepeat);
	void DrawTr(Point v1, Point v2, Point v3);

	void DrawTrWithTexture(Point v1, Point v2, Point v3, int image);
	void SmallMinaret(Point v1, float scaleX, float scaleY, float scaleZ);
	void SmallMinaretWithTexture(Point v1, float scaleX, float scaleY, float scaleZ, int bottomImage, int frontImage, int rightImage, int leftImage, int backImage, int topImage, int sphereTexture);
	void Columns(Point v1, int bottomImage, int frontImage, int rightImage, int leftImage, int backImage, int topImage);
	void ColumnsWithTexture(Point v1, int image);
	void ColumnsWithTextureAndNum(Point v1, int numColumns, int image);
	void Stairs(Point v1, float num, int width, float angle);
};

#endif
