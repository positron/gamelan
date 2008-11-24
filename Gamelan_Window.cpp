#pragma once
#include <time.h>
#include "Gamelan_Window.h"
#include "read_song.h"

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
		strings[i] = new Gam_String( Point( 200 + 25*i, 50 ), -105 + 35*i, 700, 6 );
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
	song = read_song_file( "songs/test.txt" );
	//detach start screen objects
	detach( in_name );
	detach( but_amazing );
	detach( but_sweet );
	detach( but_west );

	//attach game objects
	for( int i = 0; i < 7; i++ )
		strings[i]->attach( *this );

	//attach the first several notes
	for( int i = 0; i < 6; i++ )
	{/*
		cout << i << '|';
		increment_all();
		strings[ song[i] ]->add_note();
		cout << '|' << i;
		cout << '\n';*/
	}
	strings[ song[0] ]->add_note();
	increment_all();
	strings[ song[1] ]->add_note();
	increment_all();
	strings[ song[2] ]->add_note();
	increment_all();
	strings[ song[3] ]->add_note();
	increment_all();
	strings[ song[4] ]->add_note();
	increment_all();
	strings[ song[5] ]->add_note();
	increment_all();
	Fl::redraw();

	//set the cursor to be a crosshairs
	cursor( FL_CURSOR_CROSS );

	game = true;
	//start the timer
	time( &start );
}

int Gamelan_Window::handle( int event )
{
	//propogate the event if we don't care about it
	if( event != FL_RELEASE || !game )
		return Window::handle(event);

	//calculate what string it hit by

	//let the event bubble down
	return Window::handle(event);
}

void Gamelan_Window::end_game()
{
	game = false;
	//calculate time elapsed
	time( &end );
	double time = difftime( end, start );

	//set the cursor back to normal
	cursor( FL_CURSOR_DEFAULT );

	//detach game objects
	for( int i = 0; i < 7; i++ )
		strings[i]->detach();

	display_scores();
}

void Gamelan_Window::display_scores()
{
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
