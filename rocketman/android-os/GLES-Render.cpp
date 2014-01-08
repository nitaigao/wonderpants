#import "GLES-Render.h"

#include "cocos2d.h"
USING_NS_CC;

#ifdef __IPHONE_OS_VERSION_MAX_ALLOWED
#import <OpenGLES/EAGL.h>
#elif defined(__MAC_OS_X_VERSION_MAX_ALLOWED)
#import <OpenGL/OpenGL.h>
#endif



GLESDebugDraw::GLESDebugDraw()
	: mRatio( 1.0f )
{
}
GLESDebugDraw::GLESDebugDraw( float32 ratio )
	: mRatio( ratio )
{
}

void GLESDebugDraw::DrawPolygon(const b2Vec2* old_vertices, int32 vertexCount, const b2Color& color)
{
	ccVertex2F vertices[vertexCount];
	
	for( int i=0;i<vertexCount;i++) {
		b2Vec2 tmp = old_vertices[i];
		tmp *= mRatio;
		vertices[i].x = tmp.x;
		vertices[i].y = tmp.y;
	}

	glColor4f(color.r, color.g, color.b,1);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);	
}

void GLESDebugDraw::DrawSolidPolygon(const b2Vec2* old_vertices, int32 vertexCount, const b2Color& color)
{
	ccVertex2F vertices[vertexCount];
	
	for( int i=0;i<vertexCount;i++) {
		b2Vec2 tmp = old_vertices[i];
		tmp = old_vertices[i];
		tmp *= mRatio;
		vertices[i].x = tmp.x;
		vertices[i].y = tmp.y;
	}
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	
	glColor4f(color.r*0.5f, color.g*0.5f, color.b*0.5f,0.5f);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
	
	glColor4f(color.r, color.g, color.b,1);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}

void GLESDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
		
	const float32 k_segments = 16.0f;
	int vertexCount=16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	
	GLfloat				glVertices[vertexCount*2];
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i*2]=v.x * mRatio;
		glVertices[i*2+1]=v.y * mRatio;
		theta += k_increment;
	}
	
	glColor4f(color.r, color.g, color.b,1);
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}

void GLESDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
		
	const float32 k_segments = 16.0f;
	int vertexCount=16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;
	
	GLfloat				glVertices[vertexCount*2];
	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i*2]=v.x * mRatio;
		glVertices[i*2+1]=v.y * mRatio;
		theta += k_increment;
	}
	
	glColor4f(color.r *0.5f, color.g*0.5f, color.b*0.5f,0.5f);
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
	glColor4f(color.r, color.g, color.b,1);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
	
	// Draw the axis line
	DrawSegment(center,center+radius*axis,color);
}

void GLESDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	glColor4f(color.r, color.g, color.b,1);
	GLfloat				glVertices[] = {
		p1.x * mRatio, p1.y * mRatio,
		p2.x * mRatio, p2.y * mRatio
	};
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_LINES, 0, 2);
}

void GLESDebugDraw::DrawTransform(const b2Transform& xf)
{
//	b2Vec2 p1 = xf.position, p2;
//	const float32 k_axisScale = 0.4f;
//
//	p2 = p1 + k_axisScale * xf.R.col1;
//	DrawSegment(p1,p2,b2Color(1,0,0));
//	
//	p2 = p1 + k_axisScale * xf.R.col2;
//	DrawSegment(p1,p2,b2Color(0,1,0));
}

void GLESDebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	glColor4f(color.r, color.g, color.b,1);
	glPointSize(size);
	GLfloat				glVertices[] = {
		p.x * mRatio, p.y * mRatio
	};
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_POINTS, 0, 1);
	glPointSize(1.0f);
}

void GLESDebugDraw::DrawString(int x, int y, const char *string, ...)
{
//	LOG(@"DrawString: unsupported: %s", string);
	//printf(string);
	/* Unsupported as yet. Could replace with bitmap font renderer at a later date */
}

void GLESDebugDraw::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	glColor4f(c.r, c.g, c.b,1);

	GLfloat				glVertices[] = {
		aabb->lowerBound.x * mRatio, aabb->lowerBound.y * mRatio,
		aabb->upperBound.x * mRatio, aabb->lowerBound.y * mRatio,
		aabb->upperBound.x * mRatio, aabb->upperBound.y * mRatio,
		aabb->lowerBound.x * mRatio, aabb->upperBound.y * mRatio
	};
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_LINE_LOOP, 0, 8);
	
}