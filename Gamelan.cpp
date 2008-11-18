#include "../../std_lib_facilities.h"
#include "Gamelan_Window.h"

/** This fill contains the main function that starts the game. Gamelan_Window
 * will handle the rest of the game once it has been instantiated.  This game
 * compiles with fltk 1.1.7
 */
int main()
{
	if( H112 != 200803L ) error("Error: incorrect std_lib_facilities.h version ", H112);

	Gamelan_Window *win = new Gamelan_Window();
	return 0;
}
