#pragma once
#include "../../GUI.h"
#include "../../Graph.h"
#include <time.h>
#include "Gamelan_Window.h"

//Window constans (DEF_TITLE, etc) are defined in Gamelan_Window.h
Gamelan_Window::Gamelan_Window()
	:Window( DEF_LOCATION, DEF_WIDTH, DEF_HEIGHT, DEF_TITLE ),
	strings( 7, NULL ),
	num_notes(0), game(false)
{
	for( int i = 0; i < 7; i++ )
		strings[i] = new Gam_String();
	init();
}

//delete any objects made with "new"
Gamelan_Window::~Gamelan_Window()
{
	for( int i = 0; i < 7; i++ )
		delete strings[i];
}

void Gamelan_Window::init()
{
	//start the event loop (so the screen doesn't just close again right away)
	Fl::run();
}

void Gamelan_Window::play()
{
	time( &start );
}

void Gamelan_Window::end_game()
{
	time( &end );
	double time = difftime( end, start );
}
