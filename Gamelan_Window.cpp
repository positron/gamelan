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
	for( int i = 0; i < 7; i++ )
		strings[i] = new Gam_String( Point( 200 + 25*i, 20 ), -90 + 30*i, 500, 6 );
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
	//detach start screen objects
	detach( in_name );
	detach( but_amazing );
	detach( but_sweet );
	detach( but_west );

	//attach game objects
	for( int i = 0; i < 7; i++ )
		strings[i]->attach( *this );
	strings[2]->add_note();
	strings[2]->add_note(4);
	strings[0]->add_note();
	strings[0]->add_note(3);
	strings[6]->add_note();
	strings[6]->add_note(2);
	increment_all();
	increment_all();

	//start the timer
	time( &start );
}

void Gamelan_Window::end_game()
{
	//calculate time elapsed
	time( &end );
	double time = difftime( end, start );

	//detach game objects
	for( int i = 0; i < 7; i++ )
		strings[i]->detach();
}

//increment all strings (ie slide all notes down)
void Gamelan_Window::increment_all()
{
	for( int i = 0; i < 7; i++ )
		strings[i]->increment();
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
