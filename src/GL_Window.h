/*
 * GL_Window.h
 *
 *  Created on: Feb 14, 2011
 *      Author: khanh
 */

#ifndef GL_WINDOW_H_
#define GL_WINDOW_H_

#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/Texture2D>
#include <osg/Image>
#include <osgGA/StateSetManipulator>
#include <osg/Texture>

#include <FL/Fl_Gl_Window.H>
#include <FL/Fl.H>

#include <vector>
#include <iostream>

using namespace std;


class GL_Window : public Fl_Gl_Window, public osgViewer::Viewer
{
public:
    GL_Window(int x, int y, int w, int h, const char *label=0);
    virtual ~GL_Window();
    virtual void resize(int x, int y, int w, int h);
    void updateProperties(float dr, float dg, float db,
                          float sr, float sg, float sb,
                          float ar, float ag, float ab,
                          float _shine, float _alpha);
    //void addTexture(string name, string path);
    void getTexture(osg::ref_ptr<osg::Image>);
    void changeShape(int old, int next);

private:
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _gw;
    osg::ref_ptr<osg::Group> root;
    osg::ref_ptr<osg::Geode> geode;
    osg::ref_ptr<osg::StateSet> stateset;
    osg::ref_ptr<osg::Material> material;
    osg::ref_ptr<osg::Texture2D> texture;
    osg::ref_ptr<osg::ShapeDrawable> shape;

    osg::Vec4f diffuse_color;
    osg::Vec4f specular_color;
    osg::Vec4f ambient_color;
    float shininess;
    float alpha;

    vector< osg::ref_ptr<osg::Image> > texture_vec;
    vector< osg::ref_ptr<osg::ShapeDrawable> > shape_vec;

    virtual int handle(int event);
    virtual void draw();
};

#endif /* GL_WINDOW_H_ */
