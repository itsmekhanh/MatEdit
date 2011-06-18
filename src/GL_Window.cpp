/*
 * GL_Window.cpp
 *
 *  Created on: Feb 14, 2011
 *      Author: khanh Luc
 * Description: Openscenegraph window that is embedded inside the GUI
 */

#include "GL_Window.h"
GL_Window::GL_Window(int x, int y, int w, int h, const char *label):
    Fl_Gl_Window(x, y, w, h, label)
{
    _gw = new osgViewer::GraphicsWindowEmbedded(x,y,w,h);

    root = new osg::Group;
    geode = new osg::Geode;

    osg::ref_ptr<osg::Capsule> myCapsule (new osg::Capsule(osg::Vec3f(),1,2));
    osg::ref_ptr<osg::Box> myBox (new osg::Box(osg::Vec3f(),2,2,2));
    osg::ref_ptr<osg::Cylinder> myCylinder (new osg::Cylinder(osg::Vec3f(),.75,2.5));
    osg::ref_ptr<osg::Sphere> mySphere (new osg::Sphere(osg::Vec3f(),1.5));
    osg::ref_ptr<osg::Cone> myCone (new osg::Cone(osg::Vec3f(),1,2));

    shape_vec.push_back(new osg::ShapeDrawable(myBox.get()));
    shape_vec.push_back(new osg::ShapeDrawable(myCapsule.get()));
    shape_vec.push_back(new osg::ShapeDrawable(myCone.get()));
    shape_vec.push_back(new osg::ShapeDrawable(myCylinder.get()));
    shape_vec.push_back(new osg::ShapeDrawable(mySphere.get()));

    geode->addDrawable(shape_vec[1].get());     // default shape to pick from

    root->addChild(geode.get());

    stateset = geode->getOrCreateStateSet();

    // initial material properties
    diffuse_color.set(1, 1, 1, 1.0);
    specular_color.set(1,1,1,1);
    ambient_color.set(1,1,1,1);
    shininess = 10;
    alpha = 1;

    // apply the properties to the material
    material = new osg::Material;
    material->setDiffuse(osg::Material::FRONT, diffuse_color);
    material->setSpecular(osg::Material::FRONT, specular_color);
    material->setShininess(osg::Material::FRONT, shininess);
    material->setAmbient(osg::Material::FRONT, ambient_color);

    stateset->setAttribute(material.get());
    //stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    texture = new osg::Texture2D;

    getCamera()->setViewport(new osg::Viewport(0,0,w,h));
    getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(w)/static_cast<double>(h), 1.0f, 10000.0f);
    getCamera()->setGraphicsContext(_gw.get());

    setSceneData(root.get());
    setCameraManipulator(new osgGA::TrackballManipulator);
    addEventHandler(new osgViewer::StatsHandler);
    setThreadingModel(osgViewer::Viewer::SingleThreaded);
}

void GL_Window::resize(int x, int y, int w, int h){

    _gw->getEventQueue()->windowResize(x, y, w, h );
    _gw->resized(x,y,w,h);

    Fl_Gl_Window::resize(x,y,w,h);
}

int GL_Window::handle(int event)
{
    switch(event){
        case FL_PUSH:
            _gw->getEventQueue()->mouseButtonPress(Fl::event_x(), Fl::event_y(), Fl::event_button());
            return 1;
        case FL_MOVE:
            break;
        case FL_DRAG:
            _gw->getEventQueue()->mouseMotion(Fl::event_x(), Fl::event_y());
            redraw();
            return 1;
        case FL_RELEASE:
            _gw->getEventQueue()->mouseButtonRelease(Fl::event_x(), Fl::event_y(), Fl::event_button());
            return 1;
        case FL_KEYDOWN:
            _gw->getEventQueue()->keyPress((osgGA::GUIEventAdapter::KeySymbol)Fl::event_key());
            return 1;
        case FL_KEYUP:
            _gw->getEventQueue()->keyRelease((osgGA::GUIEventAdapter::KeySymbol)Fl::event_key());
            return 1;
        default:
            // pass other events to the base class
            return Fl_Gl_Window::handle(event);
    }
    return 0;
}

void GL_Window::draw(){
    frame();
}

void GL_Window::updateProperties(float dr, float dg, float db,
                                 float sr, float sg, float sb,
                                 float ar, float ag, float ab,
                                 float _shine,
                                 float _alpha) {

    diffuse_color.set(dr, dg, db, 1.0);
    specular_color.set(sr, sg, sb, 1.0);
    ambient_color.set(ar, ag, ab, 1.0);
    shininess = _shine;
    alpha = _alpha;

    material->setDiffuse(osg::Material::FRONT, diffuse_color);
    material->setSpecular(osg::Material::FRONT, specular_color);
    material->setAmbient(osg::Material::FRONT, ambient_color);
    material->setShininess(osg::Material::FRONT, shininess);
    material->setAlpha(osg::Material::FRONT, alpha);

    redraw();
}

void GL_Window::addTexture(string name, string path){
    //printf("name is: %s and path is: %s\n", name.c_str(), path.c_str());
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(path);
    texture_vec.push_back(image);
}

void GL_Window::getTexture(int index){

    if(index != 0){
        osg::ref_ptr<osg::Image> image = texture_vec[index];
        texture->setImage(image.get());
        stateset->setTextureAttributeAndModes (0, texture.get(), osg::StateAttribute::ON);
    }
    else
    {
        //printf("turning textures off\n");
        stateset->setTextureAttributeAndModes (0, texture.get(), osg::StateAttribute::OFF);
    }
    redraw();
}

void GL_Window::changeShape(int old,int next){
    //printf("in changeShape: old %d and next: %d\n", old, next);
    geode->removeDrawable(shape_vec[old]);
    geode->addDrawable(shape_vec[next]);
    redraw();
}

GL_Window::~GL_Window(){
}
