#pragma once
#include <time.h>
#include "Gamelan_Window.h"

//Window constans (DEF_TITLE, etc) are defined in Gamelan_Window.h
Gamelan_Window::Gamelan_Window()
	:Window( DEF_LOCATION, DEF_WIDTH, DEF_HEIGHT, DEF_TITLE ),
	strings( 7, NULL ),
	num_notes(0), game(false),

	//start screen objects
	in_name( Point( 200, 200 ), 200, 30, "Name: "),
	but_amazing( Point((x_max()-400),(y_max()-200)),200,20,"Amazing Grace", cb_amazing),
	but_sweet( Point((x_max()-400),(y_max()-150)),200,20,"Swing Low, Sweet Chariot", cb_sweet),
	but_west( Point((x_max()-400),(y_max()-100)),200,20,"Westminster", cb_west)
{
//	for( int i = 0; i < 7; i++ )
//		strings[i] = new Gam_String();
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
	Fl::redraw();
	attach( in_name );
	attach( but_amazing );
	attach( but_sweet );
	attach( but_west );
}

void Gamelan_Window::play()
{
	detach( in_name );
	detach( but_amazing );
	detach( but_sweet );
	detach( but_west );
	//start the timer
	time( &start );
}

void Gamelan_Window::end_game()
{
	time( &end );
	double time = difftime( end, start );
}

void Gamelan_Window::cb_amazing( Address, Address gw )
{
	static_cast<Gamelan_Window*>(gw) -> play();
}

void Gamelan_Window::cb_sweet( Address, Address gw )
{
	static_cast<Gamelan_Window*>(gw) -> play();
}

void Gamelan_Window::cb_west( Address, Address gw )
{
	static_cast<Gamelan_Window*>(gw) -> play();
}
