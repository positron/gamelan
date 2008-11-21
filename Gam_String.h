#pragma once

#include "Gamelan_Window.h"
#include "../../Graph.h"
#include "../../Point.h"

using namespace Graph_lib;

//forward declares
class Gamelan_Window;

/** This class knows it's slope and position, so it can calculate how to
 * display itself.  You can add notes to it and it will display them too. When
 * you call increment() all the notes on the string will slide down one notch.
 * You set the number of notches with num_divisions.
 */
class Gam_String
{
	public:
		Gam_String( Point top_pt, int dxx, int dyy, int num_divisions );
		~Gam_String();

		void increment();
		void add_note();

		//handle mouse events. Returns true if it hit a note.
		bool handle_mouse( int x, int y );

		//attach and detach. We need to store the window to draw notes on
		void attach( Gamelan_Window& w );
		void detach();

	private:
		vector<Circle*> notes;
		Point top;
		int dx, dy, divisions;

		Gamelan_Window* win;
};
