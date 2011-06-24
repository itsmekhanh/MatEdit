/*
 * Material_Window.cpp
 *
 *    Created on: Feb 15, 2011
 *  Last updated: May 17, 2011
 *        Author: Khanh Luc
 *
 */

#include "Material_Window.h"

static int fromKeyboard;

Material_Window::Material_Window(int w, int h, const char* label):
    Fl_Window(w,h,label)
{

    fromKeyboard = 0;                   // if input is from keyboard
    changed = 0;                        // if file has changed
    iTexture = 0;                       // index of texture being used
    iShape = 1;
    string temp;

    const int base_y = 60;				// y location of top slider
    const int input_x = w-295;			// x location of top input box
    const int slider_x = input_x+50;	// x location of top input slider
    const int input_width = 50;			// input width
    const int slider_width = 215;		// slider width

    const int tab_width = 295;			// tab width
    const int tab_height = 500;			// tab heights
    const int base_y_tab = 50;			// y location of top tab

    const int variable_base_x = 200;    // base_x coordinate of variable label
    const int variable_base_y = 10;     // base_y coordinate of variable label

    // clear filename
    memset(filename,'\0', 1024);
    memset(current_name, '\0', 1024);

    // menubar to open and save settings
    menubar = new Fl_Menu_Bar(0,0, w, 20);
    menubar->add("File/New",0,Menu_CB, (void*)this);
    menubar->add("File/Open",0,Menu_CB, (void*)this);
    menubar->add("File/Save",0,Menu_CB, (void*)this);
    menubar->add("File/Save as...",0,Menu_CB, (void*)this);
    menubar->add("File/Exit",0,Menu_CB, (void*)this);

    menubar->add("Shape/Box",0,Menu_CB, (void*)this);
    menubar->add("Shape/Capsule", 0,Menu_CB, (void*)this);
    menubar->add("Shape/Cone", 0,Menu_CB, (void*)this);
    menubar->add("Shape/Cylinder", 0,Menu_CB, (void*)this);
    menubar->add("Shape/Sphere", 0,Menu_CB, (void*)this);

    menubar->add("Set/Variable Names...", 0, Menu_CB, (void*)this);

    // graphics window on left-hand side
    glwin = new GL_Window(10,30,480,610);

    // settings tabs on right-hand side
    tabs  = new Fl_Tabs(w-300,30,tab_width, tab_height);
    {
        material_tab = new Fl_Group(w-300, base_y_tab,tab_width,tab_height-10, "Material");
        {
            /* diffuse sliders and inputs */
            Rdiffuse_input = new Fl_Float_Input(input_x,base_y,input_width,20);
            Rdiffuse_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            Rdiffuse_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            Rdiffuse_input->value("1.000");

            Rdiffuse_slider = new Fl_Slider(slider_x,base_y,slider_width,20, "Diffuse - R");
            Rdiffuse_slider->type(1);
            Rdiffuse_slider->bounds(0,1);
            Rdiffuse_slider->value(1);
            Rdiffuse_slider->callback(UpdateMaterial, (void*)this);


            Gdiffuse_input = new Fl_Float_Input(input_x,base_y+40,input_width,20);
            Gdiffuse_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            Gdiffuse_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            Gdiffuse_input->value("1.000");

            Gdiffuse_slider = new Fl_Slider(slider_x,base_y+40,slider_width,20, "Diffuse - G");
            Gdiffuse_slider->type(1);
            Gdiffuse_slider->bounds(0,1);
            Gdiffuse_slider->value(1);
            Gdiffuse_slider->callback(UpdateMaterial, (void*)this);


            Bdiffuse_input = new Fl_Float_Input(input_x,base_y+80,input_width,20);
            Bdiffuse_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            Bdiffuse_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            Bdiffuse_input->value("1.000");

            Bdiffuse_slider = new Fl_Slider(slider_x,base_y+80,slider_width,20, "Diffuse - B");
            Bdiffuse_slider->type(1);
            Bdiffuse_slider->bounds(0,1);
            Bdiffuse_slider->value(1);
            Bdiffuse_slider->callback(UpdateMaterial, (void*)this);

            /* specular sliders and input */
            Rspecular_input = new Fl_Float_Input(input_x,base_y+120,input_width,20);
            Rspecular_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            Rspecular_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            Rspecular_input->value("1.000");

            Rspecular_slider = new Fl_Slider(slider_x,base_y+120,slider_width,20, "Specular - R");
            Rspecular_slider->type(1);
            Rspecular_slider->bounds(0,1);
            Rspecular_slider->value(1);
            Rspecular_slider->callback(UpdateMaterial, (void*)this);


            Gspecular_input = new Fl_Float_Input(input_x,base_y+160,input_width,20);
            Gspecular_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            Gspecular_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            Gspecular_input->value("1.000");

            Gspecular_slider = new Fl_Slider(slider_x,base_y+160,slider_width,20, "Specular - G");
            Gspecular_slider->type(1);
            Gspecular_slider->bounds(0,1);
            Gspecular_slider->value(1);
            Gspecular_slider->callback(UpdateMaterial, (void*)this);


            Bspecular_input = new Fl_Float_Input(input_x,base_y+200,input_width,20);
            Bspecular_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            Bspecular_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            Bspecular_input->value("1.000");

            Bspecular_slider = new Fl_Slider(slider_x,base_y+200,slider_width,20, "Specular - B");
            Bspecular_slider->type(1);
            Bspecular_slider->bounds(0,1);
            Bspecular_slider->value(1);
            Bspecular_slider->callback(UpdateMaterial, (void*)this);

            /* ambient slider and input */
            Rambient_input = new Fl_Float_Input(input_x,base_y+240,input_width,20);
            Rambient_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            Rambient_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            Rambient_input->value("1.000");

            Rambient_slider = new Fl_Slider(slider_x,base_y+240,slider_width,20, "Ambient - R");
            Rambient_slider->type(1);
            Rambient_slider->bounds(0,1);
            Rambient_slider->value(1);
            Rambient_slider->callback(UpdateMaterial, (void*)this);


            Gambient_input = new Fl_Float_Input(input_x,base_y+280,input_width,20);
            Gambient_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            Gambient_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            Gambient_input->value("1.000");

            Gambient_slider = new Fl_Slider(slider_x,base_y+280,slider_width,20, "Ambient - G");
            Gambient_slider->type(1);
            Gambient_slider->bounds(0,1);
            Gambient_slider->value(1);
            Gambient_slider->callback(UpdateMaterial, (void*)this);


            Bambient_input = new Fl_Float_Input(input_x,base_y+320,input_width,20);
            Bambient_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            Bambient_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            Bambient_input->value("1.000");

            Bambient_slider = new Fl_Slider(slider_x,base_y+320,slider_width,20, "Ambient - B");
            Bambient_slider->type(1);
            Bambient_slider->bounds(0,1);
            Bambient_slider->value(1);
            Bambient_slider->callback(UpdateMaterial, (void*)this);

            /* shininess */
            shininess_input = new Fl_Float_Input(input_x, base_y+360, input_width, 20);
            shininess_input->callback(UpdateMaterialFromKeyboard, (void*)this);
            shininess_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
            shininess_input->value("10.00");

            shininess_slider = new Fl_Slider(slider_x,base_y+360,slider_width,20, "Shininess");
            shininess_slider->type(1);
            shininess_slider->bounds(0,100);
            shininess_slider->value(10);
            shininess_slider->callback(UpdateMaterial, (void*)this);

            /* alpha */
            alpha_input = new Fl_Float_Input(input_x, base_y+400, input_width, 20);
			alpha_input->callback(UpdateMaterialFromKeyboard, (void*)this);
			alpha_input->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
			alpha_input->value("1.00");

			alpha_slider = new Fl_Slider(slider_x,base_y+400,slider_width,20, "alpha");
			alpha_slider->type(1);
			alpha_slider->bounds(0,1);
			alpha_slider->value(1);
			alpha_slider->callback(UpdateMaterial, (void*)this);
        }
        material_tab->end();

        texture_tab = new Fl_Group(w-300, base_y_tab,tab_width,tab_height, "Texture" );
        {
            texture_choices = new Fl_Choice(slider_x+20, base_y, slider_width-5, 20, "Textures");
    		texture_choices->clear();
            temp.clear();

    		texture_choices->add("none",0, Texture_CB, (void*)this);

    		struct texture_element none;
    		none.name = "/none";
    		none.path = "none";
    		none.image = '\0';

    		loaded_textures.push_back(none);

    		//loaded_textures.push_back("/none");
			//loaded_texture_paths.push_back("none");
			//glwin->addTexture("none", "none");

            //printf("in texture_tab - number of texture choices: %d\n", texture_choices->size());
            //printf("choice 0: %s\n", texture_choices->value(0));
            //printf("choice 1: %s\n", texture_choices->value(1));

            getTextures("textures");

            load_texture_btn = new Fl_Button(w-290,base_y_tab+40, 120,20, "Load Texture...");
            load_texture_btn->callback(Load_Texture_CB, (void*)this);

            /*
            // Texture filters
            MIN_filterMode_choices = new Fl_Choice(slider_x+40, base_y+90, 190, 20, "MIN_FILTER");
            MIN_filterMode_choices->add("none",0, Set_Texture_Filter_CB, (void*)this);
            MIN_filterMode_choices->add("LINEAR",0, Set_Texture_Filter_CB, (void*)this);
            MIN_filterMode_choices->add("LINEAR_MIPMAP_LINEAR",0, Set_Texture_Filter_CB, (void*)this);
            MIN_filterMode_choices->add("LINEAR_MIPMAP_NEAREST",0, Set_Texture_Filter_CB, (void*)this);
            MIN_filterMode_choices->add("NEAREST",0, Set_Texture_Filter_CB, (void*)this);
            MIN_filterMode_choices->add("NEAREST_MIPMAP_LINEAR",0, Set_Texture_Filter_CB, (void*)this);
            MIN_filterMode_choices->add("NEAREST_MIPMAP_NEAREST",0, Set_Texture_Filter_CB, (void*)this);

            MAG_filterMode_choices = new Fl_Choice(slider_x+40, base_y+110, 190, 20, "MAG_FILTER");
            MAG_filterMode_choices->add("none",0, Set_Texture_Filter_CB, (void*)this);
            MAG_filterMode_choices->add("LINEAR",0, Set_Texture_Filter_CB, (void*)this);
            MAG_filterMode_choices->add("LINEAR_MIPMAP_LINEAR",0, Set_Texture_Filter_CB, (void*)this);
            MAG_filterMode_choices->add("LINEAR_MIPMAP_NEAREST",0, Set_Texture_Filter_CB, (void*)this);
            MAG_filterMode_choices->add("NEAREST",0, Set_Texture_Filter_CB, (void*)this);
            MAG_filterMode_choices->add("NEAREST_MIPMAP_LINEAR",0, Set_Texture_Filter_CB, (void*)this);
            MAG_filterMode_choices->add("NEAREST_MIPMAP_NEAREST",0, Set_Texture_Filter_CB, (void*)this); */

        }
        texture_tab->end();

        /* Will do later
        presets_tab = new Fl_Group(w+300, base_y_tab,tab_width,tab_height, "Presets" );
        {

        }
        presets_tab->end(); */
    }
    tabs->end();


    // generate_code button for all tabs
    generateCode_btn = new Fl_Button(w-265, h-40, 220, 20, "Generate Code");
    generateCode_btn->callback(UpdateCode, (void*)this);

    // windows for code generation
    code_window = new Fl_Double_Window(640, 480, "Code");
    code_scroll = new Fl_Scroll(0,0,640,480);
    code_text = new Fl_Multiline_Input(0,0,1000,1000);
    code_scroll->end();
    code_window->end();
    code_window->resizable(code_window);

    // window to change variable names (default values are given)
    variable_window = new Fl_Window(450, 300, "Variable Names");

    material_var = new Fl_Input(variable_base_x,variable_base_y, 200, 20, "osg::Material");
    material_var->value("material");
    material_var_s = material_var->value();

    texture_var = new Fl_Input(variable_base_x, variable_base_y+20, 200, 20, "osg::Texture2D");
    texture_var->value("texture");
    texture_var_s = texture_var->value();

    image_var = new Fl_Input(variable_base_x, variable_base_y+40, 200, 20, "osg::Image");
    image_var->value("image");
    image_var_s = image_var->value();

    diffuse_var = new Fl_Input(variable_base_x, variable_base_y+80, 200, 20, "Diffuse (osg::Vec4f)");
    diffuse_var->value("diffuse");
    diffuse_var_s = diffuse_var->value();

    specular_var = new Fl_Input(variable_base_x, variable_base_y+100, 200, 20, "Specular (osg::Vec4f)");
    specular_var->value("specular");
    specular_var_s = specular_var->value();

    ambient_var = new Fl_Input(variable_base_x, variable_base_y+120, 200, 20, "Ambient (osg::Vec4f)");
    ambient_var->value("ambient");
    ambient_var_s = ambient_var->value();

    shininess_var = new Fl_Input(variable_base_x, variable_base_y+160, 200, 20, "Shininess (float)");
    shininess_var->value("shininess");
    shininess_var_s = shininess_var->value();

    alpha_var = new Fl_Input(variable_base_x, variable_base_y+180, 200, 20, "Alpha (float)");
    alpha_var->value("alpha");
    alpha_var_s = alpha_var->value();

    variable_OKAY_btn = new Fl_Button(variable_base_x, variable_base_y+220, 50, 20, "OK");
    variable_OKAY_btn->callback(Update_Variables_OK_CB, (void*)this);

    variable_CANCEL_btn = new Fl_Button(variable_base_x+70, variable_base_y+220, 90, 20, "Cancel");
    variable_CANCEL_btn->callback(Update_Variables_CANCEL_CB, (void*)this);

    variable_window->callback(Update_Variables_CANCEL_CB, (void*)this);

    variable_window->end();


}

void Material_Window::UpdateMaterial(Fl_Widget *w, void *data){
    ((Material_Window*)data)->UpdateMaterial2();
}

void Material_Window::UpdateMaterialFromKeyboard(Fl_Widget *w, void *data){

    fromKeyboard = 1;
    ((Material_Window*)data)->UpdateMaterial2();
}
void Material_Window::UpdateMaterial2(){
     //printf("%f, %f, %f\n",Rcolor_slider->value(), Gcolor_slider->value(), Bcolor_slider->value());

     float dr,dg,db, sr, sg, sb, ar, ag, ab, shine, alpha;
     char Dred[10];
     char Dgreen[10];
     char Dblue[10];
     char Sred[10];
     char Sgreen[10];
     char Sblue[10];
     char Ared[10];
     char Agreen[10];
     char Ablue[10];
     char shine_char[10];
     char alpha_char[10];

     if(fromKeyboard)
     {
        sscanf(Rdiffuse_input->value(), "%f", &dr);
        sscanf(Gdiffuse_input->value(), "%f", &dg);
        sscanf(Bdiffuse_input->value(), "%f", &db);

        sscanf(Rspecular_input->value(), "%f", &sr);
        sscanf(Gspecular_input->value(), "%f", &sg);
        sscanf(Bspecular_input->value(), "%f", &sb);

        sscanf(Rambient_input->value(), "%f", &ar);
        sscanf(Gambient_input->value(), "%f", &ag);
        sscanf(Bambient_input->value(), "%f", &ab);

        sscanf(shininess_input->value(), "%f", &shine);
        sscanf(alpha_input->value(), "%f", &alpha);

        Rdiffuse_slider->value(dr);
        Gdiffuse_slider->value(dg);
        Bdiffuse_slider->value(db);

        Rspecular_slider->value(sr);
        Gspecular_slider->value(sg);
        Bspecular_slider->value(sb);

        Rambient_slider->value(ar);
        Gambient_slider->value(ag);
        Bambient_slider->value(ab);
        shininess_slider->value(shine);
        alpha_slider->value(alpha);
     }
     else
     {
        dr = Rdiffuse_slider->value();
        dg = Gdiffuse_slider->value();
        db = Bdiffuse_slider->value();

        sr = Rspecular_slider->value();
        sg = Gspecular_slider->value();
        sb = Bspecular_slider->value();

        ar = Rambient_slider->value();
        ag = Gambient_slider->value();
        ab = Bambient_slider->value();

        shine = shininess_slider->value();
        alpha = alpha_slider->value();

        sprintf(Dred, "%.3f", Rdiffuse_slider->value() );
        sprintf(Dgreen, "%.3f", Gdiffuse_slider->value() );
        sprintf(Dblue, "%.3f", Bdiffuse_slider->value() );

        sprintf(Sred, "%.3f", Rspecular_slider->value() );
        sprintf(Sgreen, "%.3f", Gspecular_slider->value() );
        sprintf(Sblue, "%.3f", Bspecular_slider->value() );

        sprintf(Ared, "%.3f", Rambient_slider->value() );
        sprintf(Agreen, "%.3f", Gambient_slider->value() );
        sprintf(Ablue, "%.3f", Bambient_slider->value() );

        sprintf(shine_char, "%.2f", shininess_slider->value() );
        sprintf(alpha_char, "%.2f", alpha_slider->value() );

        Rdiffuse_input->value(Dred);
        Gdiffuse_input->value(Dgreen);
        Bdiffuse_input->value(Dblue);

        Rspecular_input->value(Sred);
        Gspecular_input->value(Sgreen);
        Bspecular_input->value(Sblue);

        Rambient_input->value(Ared);
        Gambient_input->value(Agreen);
        Bambient_input->value(Ablue);
        shininess_input->value(shine_char);
        alpha_input->value(alpha_char);
     }
     fromKeyboard=0;
     changed = 1;
     glwin->updateProperties(dr, dg, db, sr, sg, sb, ar, ag, ab, shine, alpha);
}

void Material_Window::UpdateCode(Fl_Widget *w, void *data){
    ((Material_Window*)data)->UpdateCode2();
}

void Material_Window::UpdateCode2(){

    string temp;
    string code;

    code.append("osg::ref_ptr<osg::Material> ");
    code.append(material_var->value());
    code.append(";\n");


    if(iTexture != 0){
    code.append("osg::ref_ptr<osg::Texture2D> ");
    code.append(texture_var->value());
    code.append(";\n");


    code.append("osg::ref_ptr<osg::Image> ");
    code.append(image_var->value());
    code.append(";\n");

    }

    code.append("osg::Vec4f ");
    code.append(diffuse_var->value());
    code.append(";\n");

    code.append("osg::Vec4f ");
    code.append(specular_var->value());
    code.append(";\n");

    code.append("osg::Vec4f ");
    code.append(ambient_var->value());
    code.append(";\n");

    code.append("float ");
    code.append(shininess_var->value());
    code.append(";\n");

    code.append("float ");
    code.append(alpha_var->value());
    code.append(";\n\n");


    temp = (string)diffuse_var->value()+".set("+
             (string)Rdiffuse_input->value()+", "
            +(string)Gdiffuse_input->value()+", "
            +(string)Bdiffuse_input->value()+", "
            +"1.0);\n";
    code.append(temp);

    temp = (string)specular_var->value()+".set("+
             (string)Rspecular_input->value()+", "
            +(string)Gspecular_input->value()+", "
            +(string)Bspecular_input->value()+", "
            +"1.0);\n";
    code.append(temp);

    temp = (string)specular_var->value()+".set("+
                 (string)Rambient_input->value()+", "
                +(string)Gambient_input->value()+", "
                +(string)Bambient_input->value()+", "
                +"1.0);\n";
    code.append(temp);

    temp = (string)shininess_var->value()+" = "+(string)shininess_input->value()+";\n\n";
    code.append(temp);

    temp = (string)alpha_var->value()+" = "+(string)alpha_input->value()+";\n\n";
    code.append(temp);

    code.append((string)material_var->value()+" = new osg::Material;\n");
    code.append((string)material_var->value()+"->setDiffuse(osg::Material::FRONT, "+(string)diffuse_var->value()+");\n");
    code.append((string)material_var->value()+"->setSpecular(osg::Material::FRONT, "+(string)specular_var->value()+");\n");
    code.append((string)material_var->value()+"->setAmbient(osg::Material::FRONT, "+(string)ambient_var->value()+");\n");
    code.append((string)material_var->value()+"->setShininess(osg::Material::FRONT, "+(string)shininess_var->value()+");\n");
    code.append((string)material_var->value()+"->setAlpha(osg::Material::FRONT, "+(string)alpha_var->value()+");\n\n");

    if(iTexture != 0){

    code.append((string)image_var->value()+" = osgDB::readImageFile(\""+loaded_textures[iTexture].path+"\");\n");
    code.append((string)texture_var->value()+" = new osg::Texture2D;\n");
    code.append((string)texture_var->value()+"->setImage("+(string)image_var->value()+".get());\n");

    }
    code_text->value(code.c_str());
    code_window->show();
}

void Material_Window::Menu_CB(Fl_Widget *w, void *data){
	Material_Window *o = (Material_Window*)data;
	o->Menu_CB2();
}

void Material_Window::Menu_CB2(){
	char selected[80];

	// grab selection
	menubar->item_pathname(selected, sizeof(selected)-1);

	// handle appropriate callbacks
	if(strcmp(selected, "File/New")==0){
	    //printf("selected New\n");
	    memset(current_name, '\0', 1024);
	    new_cb();
	}
	else if(strcmp(selected, "File/Open")==0){
	    //printf("selected Open\n");
	    memset(current_name, '\0', 1024);
	    open_cb();
	}
	else if(strcmp(selected, "File/Save")==0){
	    //printf("selected Save\n");
	    save_cb();
	}
	else if(strcmp(selected, "File/Save as...")==0){
	    //printf("selected Save as...\n");
	    saveas_cb();
	}
	else if(strcmp(selected, "Shape/Box")==0){
        //printf("selected Shape/Box...\n");
        glwin->changeShape(iShape,0);
        iShape = 0;
	}
	else if(strcmp(selected, "Shape/Capsule")==0){
        //printf("selected Shape/Box...\n");
        glwin->changeShape(iShape,1);
        iShape = 1;
	}
	else if(strcmp(selected, "Shape/Cone")==0){
        //printf("selected Shape/Cone...\n");
        glwin->changeShape(iShape,2);
        iShape = 2;
	}
	else if(strcmp(selected, "Shape/Cylinder")==0){
        //printf("selected Shape/Cylinder...\n");
        glwin->changeShape(iShape,3);
        iShape = 3;
	}
	else if(strcmp(selected, "Shape/Sphere")==0){
        //printf("selected Shape/Sphere...\n");
        glwin->changeShape(iShape,4);
        iShape = 4;
	}
	else if(strcmp(selected, "Set/Variable Names...")==0){

	    variable_window->show();
	}

	else if(strcmp(selected, "File/Exit")==0){
	    exit(0);
	}

}

void Material_Window::Texture_CB(Fl_Widget *w, void *data){
	Material_Window *o = (Material_Window*)data;
	o->Texture_CB2();
}

void Material_Window::Texture_CB2(){
	char selected[1024];
	memset(selected, '\0', 1024);
	unsigned int i;

	// grab texture
	texture_choices->item_pathname(selected, sizeof(selected)-1);

	for(i=0; i < loaded_textures.size(); i++){
		if(!strcmp(loaded_textures[i].name.c_str(),selected)){
			glwin->getTexture(loaded_textures[i].image);
			iTexture = i;
			printf("iTexture selected %d\n", iTexture);
		}
	}
	changed = 1;
}

void Material_Window::Load_Texture_CB(Fl_Widget* w, void* data){
    Material_Window *o = (Material_Window*)data;
    o->Load_Texture_CB2();
}

void Material_Window::Load_Texture_CB2(){
    char* newfile;
    FILE *fp;
    memset(filename,'\0', 1024);
    size_t found;
    string *path;
    string file;

    newfile = fl_file_chooser("Load Texture?", "*", filename);
    if(newfile != '\0')
    {

        fp = fopen(newfile, "r");
        if(fp != '\0')
        {
            path = new string(newfile);
            found = path->find_last_of("/\\");
            file = path->substr(found+1);




            for(int i=0; i<loaded_textures.size(); i++){
                if(!strcmp(loaded_textures[i].name.c_str(),("/"+file).c_str())){
                    return;
                }
            }
            texture_choices->add(file.c_str(),0,Texture_CB, (void*)this);

            struct texture_element te;
            te.name = "/"+file;
            te.path = *path;
            te.image = osgDB::readImageFile(*path);

            loaded_textures.push_back(te);
            new_textures.push_back(te);

        }
        else
        {
            string message = "The file ";
            message.append(newfile);
            message.append(" is not found.\n");
            fl_alert(message.c_str(), "OKay");
        }
    }
}

/* will-do */
void Material_Window::Set_Texture_Filter_CB(Fl_Widget* w, void* data){}

/* will-do */
void Material_Window::Set_Texture_Filter_CB2(){}


void Material_Window::new_cb(){
    // reset all values and then prompt the user to save current file
    int choice = 0;

    if(changed){
        if(filename[0] == '\0')
        {
            choice = fl_choice("The current file has not been saved.\nWould you like to save now?\n", "Cancel", "Yes", "No");
        }
        else
            choice = fl_choice("%s has been changed, do you want to save now?\n", filename, "Cancel", "Yes", "No");

        if(choice == 1)
        {
           	save_cb();
           	memset(filename,'\0', 1024);
           	new_file();
        }
        else if(choice == 2){
            memset(filename,'\0', 1024);
            new_file();
        }
    }
    else
    {
    	memset(filename,'\0', 1024);
    	new_file();
    }
}

void Material_Window::open_cb(){
    int choice = 0;
    char* newfile;

    if(changed){
        if(filename[0] == '\0')
        {
            choice = fl_choice("The current file has not been saved.\nWould you like to save now?\n", "Cancel", "Yes", "No");
        }
        else
            choice = fl_choice("%s has been changed, do you want to save now?\n", filename, "Cancel", "Yes", "No");

        if(choice == 1)
        {
            save_cb();
            newfile = fl_file_chooser("Open File?", "*.mat", filename);
            if(newfile != NULL){
                open_file(newfile);
            }
        }
        else if(choice == 2){
            newfile = fl_file_chooser("Open File?", "*.mat", filename);
            if(newfile != NULL){
                open_file(newfile);
            }
        }
    }
    else{
        newfile = fl_file_chooser("Open File?", "*.mat", filename);
        if(newfile != NULL){
            open_file(newfile);
        }
    }
}

void Material_Window::save_cb(){
    // make sure that it has a filename
   // printf("current_name: %s\n", current_name);
    if(current_name[0] == '\0')
    {
        saveas_cb();
        return;
    }
    else
    {
        //printf("in save_cb\n");
        save_file(current_name);
    }
}


void Material_Window::saveas_cb(){
    char* newfile;

    newfile = fl_file_chooser("Save File As?", "*.mat", filename);

    if(newfile != '\0'){
        string *temp = new string(newfile);

        if(temp->find(".mat") == (size_t)-1)
        {
            temp->append(".mat");
            newfile = (char *)temp->c_str();
            memset(current_name, '\0', 1024);
            memcpy(current_name, newfile, 1024);
        }

        //printf("in saveas_cb: current_name is: %s\n", current_name);
        if(newfile != NULL){
            save_file(newfile);
        }
    }
}

void Material_Window::save_file(char* f){
    printf("file to be saved is: %s\n", f);
    string temp = "";
    FILE *fp;
    mxml_node_t     *tree;              // root <xml>
    mxml_node_t     *material_node;     // <material>
    mxml_node_t     *diffuse_node;      // <diffuse>
    mxml_node_t     *ambient_node;      // <ambient>
    mxml_node_t     *specular_node;     // <specular>
    mxml_node_t     *shininess_node;    // <shininess>
    mxml_node_t     *alpha_node;        // <alpha>
    mxml_node_t     *r_node;            // <R>
    mxml_node_t     *g_node;            // <G>
    mxml_node_t     *b_node;            // <B>
    mxml_node_t		*texture_node;      // <texture>
    mxml_node_t		*name_node;			// <name>
    mxml_node_t		*path_node;			// <path>
    mxml_node_t		*shape_node;		// <shape>

    tree            = mxmlNewXML("1.0");
    material_node   = mxmlNewElement(tree, "material");

    diffuse_node    = mxmlNewElement(material_node, "diffuse");
    r_node          = mxmlNewElement(diffuse_node, "R");
    mxmlNewText(r_node, 0, Rdiffuse_input->value());
    g_node          = mxmlNewElement(diffuse_node, "G");
    mxmlNewText(g_node, 0, Gdiffuse_input->value());
    b_node          = mxmlNewElement(diffuse_node, "B");
    mxmlNewText(b_node, 0, Bdiffuse_input->value());

    specular_node    = mxmlNewElement(material_node, "specular");
    r_node          = mxmlNewElement(specular_node, "R");
    mxmlNewText(r_node, 0, Rspecular_input->value());
    g_node          = mxmlNewElement(specular_node, "G");
    mxmlNewText(g_node, 0, Gspecular_input->value());
    b_node          = mxmlNewElement(specular_node, "B");
    mxmlNewText(b_node, 0, Bspecular_input->value());

    ambient_node    = mxmlNewElement(material_node, "ambient");
    r_node          = mxmlNewElement(ambient_node, "R");
    mxmlNewText(r_node, 0, Rambient_input->value());
    g_node          = mxmlNewElement(ambient_node, "G");
    mxmlNewText(g_node, 0, Gambient_input->value());
    b_node          = mxmlNewElement(ambient_node, "B");
    mxmlNewText(b_node, 0, Bambient_input->value());

    shininess_node  = mxmlNewElement(material_node, "shininess");
    mxmlNewText(shininess_node, 0, shininess_input->value());

    alpha_node      = mxmlNewElement(material_node, "alpha");
    mxmlNewText(alpha_node, 0, alpha_input->value());

    texture_node = mxmlNewElement(material_node, "texture_index");
    char index[5];
    sprintf(index, "%d", iTexture);
    mxmlNewText(texture_node,0,index);

    // saves new textures
    for(int i=0; i<new_textures.size(); i++){
        texture_node    = mxmlNewElement(material_node, "texture");
        name_node       = mxmlNewElement(texture_node, "name");
        mxmlNewText(name_node,0,new_textures[i].name.c_str());
        path_node       = mxmlNewElement(texture_node, "path");
        mxmlNewText(path_node,0,new_textures[i].path.c_str());
    }

    // grab only index of shape in library
    shape_node    = mxmlNewElement(material_node, "shape");
    mxmlNewInteger(shape_node, iShape);

    fp = fopen(f, "w");
    mxmlSaveFile(tree, fp, MXML_NO_CALLBACK);
    fclose(fp);
    changed = 0;

}

void Material_Window::open_file(char* f){
    FILE *fp;
    mxml_node_t *tree;
    mxml_node_t *top_node;
    mxml_node_t *working_node;
    int next;

    //printf("in open_file. filename is %s\n", f);
    fp = fopen(f, "r");

    printf("in open_file - sizeof new_textures: %d\n", new_textures.size());
    // clear previous textures
    for(int i=0; i<new_textures.size(); i++){
            texture_choices->remove(texture_choices->size()-2);
            loaded_textures.pop_back();
    }
    new_textures.clear();

    if(fp != '\0'){
        tree = mxmlLoadFile(NULL, fp, MXML_TEXT_CALLBACK);

        /* find the first element with "diffuse" attribute */
        top_node = mxmlFindElement(tree, tree, "diffuse", NULL, NULL, MXML_DESCEND);

            // Red value
        working_node = top_node->child->child;
        Rdiffuse_input->value(working_node->value.text.string);

            // Green value
        working_node = top_node->child->next->child;
        Gdiffuse_input->value(working_node->value.text.string);

            // Blue value
        working_node = top_node->child->next->next->child;
        Bdiffuse_input->value(working_node->value.text.string);

        /* find the first element with "specular" attribute */
        top_node = mxmlFindElement(tree, tree, "specular", NULL, NULL, MXML_DESCEND);

            // Red value
        working_node = top_node->child->child;
        Rspecular_input->value(working_node->value.text.string);

            // Green value
        working_node = top_node->child->next->child;
        Gspecular_input->value(working_node->value.text.string);

            // Blue value
        working_node = top_node->child->next->next->child;
        Bspecular_input->value(working_node->value.text.string);

        /* find the first element with "ambient" attribute */
        top_node = mxmlFindElement(tree, tree, "ambient", NULL, NULL, MXML_DESCEND);

            // Red value
        working_node = top_node->child->child;
        Rambient_input->value(working_node->value.text.string);

            // Green value
        working_node = top_node->child->next->child;
        Gambient_input->value(working_node->value.text.string);

            // Blue value
        working_node = top_node->child->next->next->child;
        Bambient_input->value(working_node->value.text.string);

        /* find the first element with "shininess" attribute */
        top_node = mxmlFindElement(tree, tree, "shininess", NULL, NULL, MXML_DESCEND);
        working_node = top_node->child;
        shininess_input->value(working_node->value.text.string);

        /* find the first element with "alpha" attribute */
        top_node = mxmlFindElement(tree, tree, "alpha", NULL, NULL, MXML_DESCEND);
        working_node = top_node->child;
        alpha_input->value(working_node->value.text.string);

        /* grab index of the texture being used */
        top_node = mxmlFindElement(tree, tree, "texture_index", NULL, NULL, MXML_DESCEND);
        iTexture = atoi(top_node->child->value.text.string);

        /* find the first element with "texture" attribute */
        for(top_node = mxmlFindElement(tree, tree, "texture", NULL, NULL, MXML_DESCEND);
            top_node != '\0';
            top_node = mxmlFindElement(top_node, tree, "texture", NULL, NULL, MXML_DESCEND))
        {
            struct texture_element elem;

            working_node = top_node->child->child;

            elem.name = working_node->value.text.string;
            string choice_name = elem.name.substr(1,elem.name.length()-1);

            working_node = top_node->child->next->child;
            elem.path = working_node->value.text.string;


            elem.image = osgDB::readImageFile(elem.path);

            texture_choices->add(choice_name.c_str(),0,Texture_CB, (void*)this);
            //printf("loading extra textures: %s\n", elem.name.c_str());
            loaded_textures.push_back(elem);
            new_textures.push_back(elem);
        }

        /* find the first element with "shape" attribute */
        top_node = mxmlFindElement(tree, tree, "shape", NULL, NULL, MXML_DESCEND);
        working_node = top_node->child;
        next = atoi(working_node->value.text.string);

        fromKeyboard = 1;

        printf("iTexture to load is: %d\n", iTexture);

        UpdateMaterial2();
        //glwin->getTexture
        glwin->getTexture(loaded_textures[iTexture].image);
        texture_choices->value(iTexture);

        glwin->changeShape(iShape, next);
        iShape = next;

        changed = 0;
        memset(current_name, '\0', 1024);
        memcpy(current_name, f, 1024);

        fclose(fp);
    }
    else
    {
        string message = "The file ";
        message.append(f);
        message.append(" is not found.\n");
        fl_alert(message.c_str());
    }
}

void Material_Window::new_file(){

    // reset all values
    Rdiffuse_input->value("1.000");
    Gdiffuse_input->value("1.000");
    Bdiffuse_input->value("1.000");

    Rspecular_input->value("1.000");
    Gspecular_input->value("1.000");
    Bspecular_input->value("1.000");

    Rambient_input->value("1.000");
    Gambient_input->value("1.000");
    Bambient_input->value("1.000");

    alpha_input->value("1.000");
    shininess_input->value("10");

    glwin->getTexture(loaded_textures[0].image);

    printf("in new_file - size of new_textures: %d\n", new_textures.size());
    printf("in new_file - size of current textures: %d\n", texture_choices->size());
    printf("size of texture choices: %d\n", texture_choices->size());

    // remove uploaded textures
    for(int i=0; i<new_textures.size(); i++){
        texture_choices->remove(texture_choices->size()-2);
        loaded_textures.pop_back();
    }
    new_textures.clear();

    fromKeyboard = 1;
    changed = 0;
    UpdateMaterial2();

}

void Material_Window::Update_Variables_OK_CB(Fl_Widget* w, void* data){
    Material_Window *o = (Material_Window*)data;
    o->Update_Variables_OK_CB2();
}

void Material_Window::Update_Variables_OK_CB2(){
	material_var_s = material_var->value();
	texture_var_s = texture_var->value();
	image_var_s = image_var->value();
	diffuse_var_s = diffuse_var->value();
	specular_var_s = specular_var->value();
	ambient_var_s = ambient_var->value();
	shininess_var_s = shininess_var->value();
	alpha_var_s = alpha_var->value();
	variable_window->hide();
}

void Material_Window::Update_Variables_CANCEL_CB(Fl_Widget* w, void* data){
    //printf("in cancel callback\n");
    Material_Window *o = (Material_Window*)data;
    o->Update_Variables_CANCEL_CB2();
}

void Material_Window::Update_Variables_CANCEL_CB2(){
	material_var->value(material_var_s.c_str());
	texture_var->value(texture_var_s.c_str());
	image_var->value(image_var_s.c_str());
	diffuse_var->value(diffuse_var_s.c_str());
	specular_var->value(specular_var_s.c_str());
	ambient_var->value(ambient_var_s.c_str());
	shininess_var->value(shininess_var_s.c_str());
	alpha_var->value(alpha_var_s.c_str());
	variable_window->hide();
}


void Material_Window::test_func(){
    printf("in test_func\n");
}

void Material_Window::getTextures(const char* directory){
	DIR *dir;
	struct dirent *ent;
	dir = opendir(directory);
	string temp = "";
    printf("number of pre-loaded textures before: %d\n", texture_choices->size());

	if(dir != NULL){
		while( ((ent = readdir(dir)) != NULL) )
		{
			if(ent->d_name[0] != '.'){

				texture_choices->add(ent->d_name,0,Texture_CB, (void*)this);

				struct texture_element te;

				temp.clear();
				temp.append("/");
				temp.append(ent->d_name);
				te.name = temp;

				temp.clear();
				temp.append(directory);
				temp.append("/");
				temp.append(ent->d_name);
				te.path = temp;

				te.image = osgDB::readImageFile(temp);
				loaded_textures.push_back(te);
			}
		}
		closedir(dir);
	}
	else{
		perror("Invalid directory\n");
	}
}
