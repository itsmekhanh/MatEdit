/*
 * Material_Window.h
 *
 *  Created on: Feb 15, 2011
 *      Author: Khanh Luc
 *      Updated: Apr 11, 2011
 */

#ifndef MATERIAL_WINDOW_H_
#define MATERIAL_WINDOW_H_

#include "GL_Window.h"
//#include "Code_Window.h"
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Double_Window.H>

#include <fstream>
#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <mxml.h>
#include <string.h>
#include <dirent.h>

#include <vector>

using namespace std;

struct texture_element{
	string name;
	string path;
	osg::ref_ptr<osg::Image> image;
};

class Material_Window: public Fl_Window{

public:
    Material_Window(int w, int h, const char *label=0);
    static void UpdateMaterial(Fl_Widget *w, void *data);
    static void UpdateMaterialFromKeyboard(Fl_Widget *w, void *data);
    void UpdateMaterial2();

    /* generate code */
    static void UpdateCode(Fl_Widget *w, void *data);
    void UpdateCode2();

    /* menu operations */
    static void Menu_CB(Fl_Widget* w, void* data);
    void Menu_CB2();

    /* file management */
    void new_cb(void);
    void open_cb(void);
    void save_cb(void);
    void saveas_cb(void);
    void save_file(char* );
    void open_file(char* );
    void new_file();

    /* texture callbacks */
    void getTextures(const char* directory);

    static void Texture_CB(Fl_Widget* w, void* data);
    void Texture_CB2();

    static void Load_Texture_CB(Fl_Widget* w, void* data);
    void Load_Texture_CB2();

    static void Set_Texture_Filter_CB(Fl_Widget* w, void* data);
    void Set_Texture_Filter_CB2();

    static void Update_Variables_OK_CB(Fl_Widget* w, void* data);
    void Update_Variables_OK_CB2();


    static void Update_Variables_CANCEL_CB(Fl_Widget* w, void* data);
    void Update_Variables_CANCEL_CB2();


    /* for debugging */
    static void test_func();

private:
    GL_Window*  glwin;              // OpenGL Window
    Fl_Tabs*    tabs;               // Right-hand tabs
    Fl_Group*   material_tab;       // tabs for material properties
    Fl_Group*   texture_tab;        // tabs for material textures
    Fl_Group*   presets_tab;        // tabs for presets


/* -------------------- Material Tab ----------------------------*/

    /* rgb diffuse colors */
    Fl_Slider*      Rdiffuse_slider;
    Fl_Slider*      Gdiffuse_slider;
    Fl_Slider*      Bdiffuse_slider;
    Fl_Float_Input* Rdiffuse_input;
    Fl_Float_Input* Bdiffuse_input;
    Fl_Float_Input* Gdiffuse_input;

    /* rgb specular colors */
    Fl_Slider*      Rspecular_slider;
    Fl_Slider*      Gspecular_slider;
    Fl_Slider*      Bspecular_slider;
    Fl_Float_Input* Rspecular_input;
    Fl_Float_Input* Bspecular_input;
    Fl_Float_Input* Gspecular_input;

    /* rgb ambient colors */
    Fl_Slider*      Rambient_slider;
    Fl_Slider*      Gambient_slider;
    Fl_Slider*      Bambient_slider;
    Fl_Float_Input* Rambient_input;
    Fl_Float_Input* Bambient_input;
    Fl_Float_Input* Gambient_input;

    /* shininess colors */
    Fl_Slider*      shininess_slider;
    Fl_Float_Input* shininess_input;

    /* alpha */
    Fl_Slider*	    alpha_slider;
    Fl_Float_Input*	alpha_input;

/* ----------------------- Texture tab -----------------------------*/
    Fl_Choice *texture_choices;				// pull-down menu of texure items
    Fl_Button *load_texture_btn;          	// import texture button

    Fl_Choice *MIN_filterMode_choices;      // MIN filter Modes
    Fl_Choice *MAG_filterMode_choices;      // MAG filter Modes

    //vector<string> loaded_textures;			// textures stored in memory <name in list, filepath>
    //vector<string> loaded_texture_paths;    // paths of the texture files
    vector<texture_element> loaded_textures;    // textures stored in memory (name, path, image)

    int iTexture;
/* ----------------------- code generation -------------------------*/

    Fl_Button*      generateCode_btn;   // button to callback generateCode
    Fl_Multiline_Input *code_text;      // actual code of the rendering
    Fl_Double_Window *code_window;      // window holding the code
    Fl_Scroll *code_scroll;             // scroller for large codes
    //Code_Window*    cw;                 // popup window with generated code

/* ----------------------- menu bar options ------------------------*/

    Fl_Menu_Bar* 	menubar;            // menu bar

    /* xml file management and structure */
    Fl_File_Chooser* filechooser;       // file browser to save/open files
    int				changed;	        // flag to check if file was changed
    char			filename[1024];		// name of the file
    char*           current_name;       // current name of the file
    int             iShape;             // index of current shape
    vector<string>  shapes;             // vector of shape names

    /* variable options */
    Fl_Window *variable_window;         // variables window
    Fl_Input *material_var;
    Fl_Input *texture_var;
    Fl_Input *image_var;
    Fl_Input *diffuse_var;
    Fl_Input *specular_var;
    Fl_Input *ambient_var;
    Fl_Input *shininess_var;
    Fl_Input *alpha_var;

    string material_var_s;				// local copies of variable names
    string texture_var_s;
    string image_var_s;
    string diffuse_var_s;
    string specular_var_s;
    string ambient_var_s;
    string shininess_var_s;
    string alpha_var_s;

    Fl_Button *variable_OKAY_btn;      // okay button for variable window
    Fl_Button *variable_CANCEL_btn;
};
#endif /* MATERIAL_WINDOW_H_ */
