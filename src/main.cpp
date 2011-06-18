/*
 * main.cpp
 *
 *  Created on: Feb 14, 2011
 *      Author: khanh
 */

#include "Material_Window.h"

int main(void){

    Material_Window mwin(800,650,"MatEdit 1.02");
    mwin.resizable(&mwin);
    mwin.end();
    mwin.show();

    return (Fl::run());
}
