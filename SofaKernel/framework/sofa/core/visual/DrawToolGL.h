/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2018 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/


#ifndef SOFA_CORE_VISUAL_DRAWTOOLGL_H
#define SOFA_CORE_VISUAL_DRAWTOOLGL_H

#include <sofa/core/visual/DrawTool.h>
#include <sofa/defaulttype/Vec.h>
#include <sofa/defaulttype/RGBAColor.h>
#include <sofa/helper/system/gl.h>
#include <sofa/helper/gl/BasicShapesGL.h>

namespace sofa
{

namespace core
{

namespace visual
{

class SOFA_CORE_API DrawToolGL : public DrawTool
{

public:
    typedef sofa::defaulttype::Vec4f   Vec4f;
    typedef sofa::defaulttype::Vec3f   Vec3f;
    typedef sofa::defaulttype::Vector3 Vector3;
    typedef sofa::defaulttype::Vec<3,int> Vec3i;
    typedef sofa::defaulttype::Vec<2,int> Vec2i;
    typedef sofa::defaulttype::Quaternion Quaternion;

    DrawToolGL();
    ~DrawToolGL() override;

    void init() override;

    void drawPoint(const Vector3 &p, const Vec4f &c) override;
    //normal on a point is useless
    void drawPoint(const Vector3 &p, const Vector3 &n, const Vec4f &c) override;
    void drawPoints(const std::vector<Vector3> &points, float size,  const Vec4f& colour) override;
    void drawPoints(const std::vector<Vector3> &points, float size, const std::vector<Vec4f>& colour) override;

    void drawLine(const Vector3 &p1, const Vector3 &p2, const Vec4f& colour) override;
    void drawLines(const std::vector<Vector3> &points, float size, const Vec4f& colour) override;
    void drawLines(const std::vector<Vector3> &points, float size, const std::vector<Vec4f>& colours) override;
    void drawLines(const std::vector<Vector3> &points, const std::vector< Vec2i > &index, float size, const Vec4f& colour) override;

    void drawLineStrip(const std::vector<Vector3> &points, float size, const Vec4f& colour) override;
    void drawLineLoop(const std::vector<Vector3> &points, float size, const Vec4f& colour) override;

    void drawTriangle(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,
            const Vector3 &normal) override;
    void drawTriangle(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,
            const Vector3 &normal, const Vec4f &c) override;
    void drawTriangle(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,
            const Vector3 &normal,
            const Vec4f &c1, const Vec4f &c2, const Vec4f &c3) override;
    void drawTriangle(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,
            const Vector3 &normal1, const Vector3 &normal2, const Vector3 &normal3,
            const Vec4f &c1, const Vec4f &c2, const Vec4f &c3) override;
    void drawTriangles(const std::vector<Vector3> &points, const Vec4f& colour) override;
    void drawTriangles(const std::vector<Vector3> &points, const Vector3& normal, const Vec4f& colour) override;
    void drawTriangles(const std::vector<Vector3> &points,
            const std::vector< Vec3i > &index,
            const std::vector<Vector3>  &normal,
            const Vec4f& colour) override;
    void drawTriangles(const std::vector<Vector3> &points,
            const std::vector<Vector3>  &normal,
            const std::vector< Vec4f > &colour) override;

    void drawTriangleStrip(const std::vector<Vector3> &points,
            const std::vector<Vector3>  &normal,
            const Vec4f& colour) override;

    void drawTriangleFan(const std::vector<Vector3> &points,
            const std::vector<Vector3>  &normal,
            const Vec4f& colour) override;

    void drawFrame(const Vector3& position, const Quaternion &orientation, const Vec3f &size) override;
    void drawFrame(const Vector3& position, const Quaternion &orientation, const Vec3f &size, const Vec4f &colour) override;

    void drawSpheres (const std::vector<Vector3> &points, const std::vector<float>& radius, const Vec4f& colour) override;
    void drawSpheres (const std::vector<Vector3> &points, float radius, const Vec4f& colour) override;
    void drawFakeSpheres(const std::vector<Vector3> &points, const std::vector<float>& radius, const Vec4f& colour) override;
    void drawFakeSpheres(const std::vector<Vector3> &points, float radius, const Vec4f& colour) override;

    void drawCone    (const Vector3& p1, const Vector3 &p2, float radius1, float radius2, const Vec4f& colour, int subd=16) override;

    void drawCube    (const float& radius, const Vec4f& colour, const int& subd=16) override;

    void drawCylinder(const Vector3& p1, const Vector3 &p2, float radius, const Vec4f& colour,  int subd=16) override;

    void drawCapsule(const Vector3& p1, const Vector3 &p2, float radius, const Vec4f& colour,  int subd=16) override;

    void drawArrow   (const Vector3& p1, const Vector3 &p2, float radius, const Vec4f& colour,  int subd=16) override;
    void drawArrow   (const Vector3& p1, const Vector3 &p2, float radius, float coneLength, const Vec4f& colour,  int subd=16) override;

    void drawCross(const Vector3&p, float length, const Vec4f& colour) override;

    void drawPlus    (const float& radius, const Vec4f& colour, const int& subd=16) override;

    void drawQuad(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,const Vector3 &p4,
            const Vector3 &normal) override;
    void drawQuad(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,const Vector3 &p4,
            const Vector3 &normal, const Vec4f &c) override;
    void drawQuad(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,const Vector3 &p4,
            const Vector3 &normal,
            const Vec4f &c1, const Vec4f &c2, const Vec4f &c3, const Vec4f &c4) override;
    void drawQuad(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,const Vector3 &p4,
            const Vector3 &normal1, const Vector3 &normal2, const Vector3 &normal3, const Vector3 &normal4,
            const Vec4f &c1, const Vec4f &c2, const Vec4f &c3, const Vec4f &c4) override;
    void drawQuads(const std::vector<Vector3> &points, const Vec4f& colour) override ;


    void drawTetrahedron(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3, const Vec4f &colour) override;
    void drawTetrahedra(const std::vector<Vector3> &points, const Vec4f& colour) override;
    void drawScaledTetrahedra(const std::vector<Vector3> &points, const Vec4f& colour, const float scale) override;

    void drawHexahedron(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, const Vector3 &p3,
        const Vector3 &p4, const Vector3 &p5, const Vector3 &p6, const Vector3 &p7, const Vec4f &colour) override;
    void drawHexahedra(const std::vector<Vector3> &points, const Vec4f& colour) override;
    void drawScaledHexahedra(const std::vector<Vector3> &points, const Vec4f& colour, const float scale) override;

    void drawSphere( const Vector3 &p, float radius) override;
    void drawEllipsoid(const Vector3 &p, const Vector3 &radii) override;

    void drawBoundingBox( const Vector3 &min, const Vector3 &max ) override;

    void draw3DText(const Vector3 &p, float scale, const Vec4f &color, const char* text) override;

    void draw3DText_Indices(const helper::vector<Vector3> &positions, float scale, const Vec4f &color) override;

    void clear() override;

    void setMaterial(const Vec4f &colour) override;

    void resetMaterial(const Vec4f &colour) override;
    void resetMaterial() override;

    void pushMatrix() override;
    void popMatrix() override;
    void multMatrix(float* glTransform ) override;
    void scale( float s ) override;
    void translate(float x, float y, float z) override;

    void writeOverlayText( int x, int y, unsigned fontSize, const Vec4f &color, const char* text ) override;

    void enableBlending() override;
    void disableBlending() override;

    void enableLighting() override;
    void disableLighting() override;

    void enableDepthTest() override;
    void disableDepthTest() override;

    void saveLastState() override;
    void restoreLastState() override;

    void readPixels(int x, int y, int w, int h, float* rgb, float* z = NULL) override;

    void internalDrawSpheres(const helper::vector<Vector3>& centers, const float& radius, const unsigned int rings, const unsigned int sectors);
    void internalDrawSphere(const Vector3& center, const float& radius, const unsigned int rings, const unsigned int sectors);

protected:

    bool mLightEnabled;
    int  mPolygonMode;      //0: no cull, 1 front (CULL_CLOCKWISE), 2 back (CULL_ANTICLOCKWISE)
    bool mWireFrameEnabled;

    helper::gl::BasicShapesGL_Sphere<Vector3> m_sphereUtil;
    helper::gl::BasicShapesGL_FakeSphere<Vector3> m_fakeSphereUtil;

    // utility functions, defining primitives
    virtual void internalDrawPoint(const Vector3 &p, const Vec4f &c);
    virtual void internalDrawPoint(const Vector3 &p, const Vector3 &n, const Vec4f &c);

    virtual void internalDrawLine(const Vector3 &p1, const Vector3 &p2, const Vec4f& colour);

    virtual void internalDrawTriangle(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,
            const Vector3 &normal);
    virtual void internalDrawTriangle(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,
            const Vector3 &normal, const Vec4f &c);
    virtual void internalDrawTriangle(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,
            const Vector3 &normal,
            const Vec4f &c1, const Vec4f &c2, const Vec4f &c3);
    virtual void internalDrawTriangle(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,
            const Vector3 &normal1, const Vector3 &normal2, const Vector3 &normal3,
            const Vec4f &c1, const Vec4f &c2, const Vec4f &c3);

    virtual void internalDrawQuad(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,const Vector3 &p4,
            const Vector3 &normal);
    virtual void internalDrawQuad(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,const Vector3 &p4,
            const Vector3 &normal, const Vec4f &c);
    virtual void internalDrawQuad(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,const Vector3 &p4,
            const Vector3 &normal,
            const Vec4f &c1, const Vec4f &c2, const Vec4f &c3, const Vec4f &c4);
    virtual void internalDrawQuad(const Vector3 &p1,const Vector3 &p2,const Vector3 &p3,const Vector3 &p4,
            const Vector3 &normal1, const Vector3 &normal2, const Vector3 &normal3, const Vector3 &normal4,
            const Vec4f &c1, const Vec4f &c2, const Vec4f &c3, const Vec4f &c4);

public:
    // getter & setter
    void setLightingEnabled(bool _isAnabled) override;

    bool getLightEnabled() {return mLightEnabled;}

    void setPolygonMode(int _mode, bool _wireframe) override;

    int getPolygonMode() {return mPolygonMode;}
    bool getWireFrameEnabled() {return mWireFrameEnabled;}
};

//#if defined(SOFA_EXTERN_TEMPLATE) && !defined(SOFA_HELPER_GL_DRAWTOOLGL_CPP)
//extern template class SOFA_CORE_API BasicShapesGL_Sphere < sofa::defaulttype::Vector3 >;
//#endif // defined(SOFA_EXTERN_TEMPLATE)

}//namespace visual

}//namespace core

}//namespace sofa

#endif // SOFA_CORE_VISUAL_DRAWTOOLGL_H
