#pragma once
#include <time.h>
#include "Gamelan_Window.h"
#include "read_song.h"
#include "scores.h"

//Window constants (DEF_TITLE, etc) are defined in Gamelan_Window.h
Gamelan_Window::Gamelan_Window()
	:Window( DEF_LOCATION, DEF_WIDTH, DEF_HEIGHT, DEF_TITLE ),
	strings( 7, NULL ),
	index(0), game(false),

	//start screen objects
	in_name( Point( 200, 200 ), 200, 30, "Name: "),
	but_amazing( Point((x_max()-400),(y_max()-200)),200,20,"Amazing Grace", cb_amazing),
	but_sweet( Point((x_max()-400),(y_max()-150)),200,20,"Swing Low, Sweet Chariot", cb_sweet),
	but_west( Point((x_max()-400),(y_max()-100)),200,20,"Westminster", cb_west),

	//Final Screen objects
	score1( Point(100,275), "" ),
	score2( Point(100,300), "" ),
	score3( Point(100,325), "" ),
	score4( Point(100,350), "" ),
	score5( Point(100,375), "" )
{
	for( int i = 0; i < 7; i++ )
		strings[i] = new Gam_String( Point( 200 + 25*i, 50 ), -105 + 35*i, 700, NUM_DIVISIONS );
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

void Gamelan_Window::play( string filename )
{
	song = read_song_file( "songs/" + filename + ".txt"  );
	user_name = in_name.get_string();
	if( user_name == "" )
		user_name = "Anonymous";
	//detach start screen objects
	detach( in_name );
	detach( but_amazing );
	detach( but_sweet );
	detach( but_west );

	//attach game objects
	for( int i = 0; i < 7; i++ )
		strings[i]->attach( *this );

	//attach the first several notes
	for( int i = 0; i < NUM_DIVISIONS; i++ )
	{
		increment_all();
		strings[ song[i] ]->add_note();
	}
	//set the index to the next note
	index = NUM_DIVISIONS;
	Fl::redraw();

	//set the cursor to be a crosshairs
	cursor( FL_CURSOR_CROSS );

	game = true;

	//start the timer
	time( &start );
}

int Gamelan_Window::handle( int event )
{
	//propogate the event if we don't care about it (because it isn't a mouse
	//release event or because the game isn't running
	if( event != FL_RELEASE || !game )
		return Window::handle( event );

	int x = Fl::event_x();
	int y = Fl::event_y();
	//if the event could not have hit a note then throw it away
	if( y < 720 || y > 780 || x < 65 || x > 484 )
		return Window::handle( event );

	//calculate what string it hit by
	int str = (x - 65) / 60;
	//normalize the point so 0,0 is the center of the string
	bool hit = strings[ str ]->handle_mouse( x - 65 - 60*str, y - 750 );
	if( hit )
	{
		increment_all();
		index++;
		//is there another note to add?
		if( index < song.size() )
			strings[ song[index] ]->add_note();
		//was this the last note? ie is the game over?
		if( index == song.size() + NUM_DIVISIONS - 1 )
			end_game();
		Fl::redraw();
	}

	//let the event bubble down
	return Window::handle( event );
}

//called when the game ends
void Gamelan_Window::end_game()
{
	game = false;
	//calculate time elapsed
	time( &end );
	double time = difftime( end, start );
	int score = song.size() * 1000.0 / time;
	cout << score << '\n';

	//set the cursor back to normal
	cursor( FL_CURSOR_DEFAULT );

	//detach game objects
	for( int i = 0; i < 7; i++ )
		strings[i]->detach();

	display_scores( score );
}

//update high scores file and display scores
void Gamelan_Window::display_scores( int score )
{
	Score_IO::add_score( user_name, score );
	vector<string> scores = Score_IO::top_scores();

	//Attach the high scores: alternate colors and set font to a monospace font
	//so the spacing works
	score1.set_font_size(18);
	score1.set_font(Font::courier_bold);
	//score1.set_color(Color::white);
	attach( score1 );
	score1.set_label( scores[0] );

	//check if there is a score2 to display
	if( scores.size() < 2 ) return;
	score2.set_font_size(18);
	score2.set_font(Font::courier_bold);
	score2.set_color(Color::white);
	attach( score2 );
	score2.set_label( scores[1] );

	if( scores.size() < 3 ) return;
	score3.set_font_size(18);
	score3.set_font(Font::courier_bold);
	//score3.set_color(Color::white);
	attach( score3 );
	score3.set_label( scores[2] );

	if( scores.size() < 4 ) return;
	score4.set_font_size(18);
	score4.set_font(Font::courier_bold);
	score4.set_color(Color::white);
	attach( score4 );
	score4.set_label( scores[3] );

	if( scores.size() < 5 ) return;
	score5.set_font_size(18);
	score5.set_font(Font::courier_bold);
	//score5.set_color(Color::white);
	attach( score5 );
	score5.set_label( scores[4] );
	Fl::redraw();
}

//increment all strings (ie slide all notes down)
void Gamelan_Window::increment_all()
{
	for( int i = 0; i < 7; i++ )
		strings[i]->increment();
}

void Gamelan_Window::cb_amazing( Address, Address gw )
{
	static_cast<Gamelan_Window*>(gw) -> play( "amazing" );
}

void Gamelan_Window::cb_sweet( Address, Address gw )
{
	static_cast<Gamelan_Window*>(gw) -> play( "sweet" );
}

void Gamelan_Window::cb_west( Address, Address gw )
{
	static_cast<Gamelan_Window*>(gw) -> play( "west" );
}
