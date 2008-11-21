#pragma once
#include "../../GUI.h"
#include "../../Graph.h"
#include <time.h>
#include "Gam_String.h"

using namespace Graph_lib;

/** Gamelan_Window will manage the game from start to end.  All it needs to do
 * is bre created.  When it is created the constructor calls init, which starts
 * the event loop.  Init sets up the game and displays the start screen. When
 * the user clicks on a start button it calls play(), which detaches start
 * screen objects and starts the game. After the song is finished end_game() is
 * called, which detaches the game objects, calculates the score, and calls
 * display_scores(), which displays the final results and high scores.
 */
class Gamelan_Window : public Window
{
	public:
		Gamelan_Window();
		~Gamelan_Window();

		void init();
		void play();
		void end_game();
		void display_scores();

		inline bool get_game() { return game; }

		//callbacks
		static void cb_play( Address, Address );
		static void cb_amazing( Address, Address );
		static void cb_sweet( Address, Address );
		static void cb_west( Address, Address );

	private:
		vector<Gam_String *> strings;
		string user_name;
		int num_notes;
		vector<int> song;
		time_t start, end; //use double difftime(time_t start, time_t end);

		bool game; //is true when the game is being played, and false when not

		//start screen objects
		In_box in_name;
		Button but_amazing;
		Button but_sweet;
		Button but_west;
};

//defaults
static Point DEF_LOCATION = Point(50,50);
static const int DEF_WIDTH = 600;
static const int DEF_HEIGHT = 800;
static string DEF_TITLE = "Gamelan Hero";
