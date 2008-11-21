#include "Gam_String.h"

/** Construct a Gamelan String object. This takes 4 variables.
 * top_pt: the point of the string on the top of the window
 * dxx: the number of pixels to go right or left from top_pt (can be negative)
 * dyy: the number of pixels to go down from top_pt
 * num_divisions: the number of notes that can fit on a string at a time
 *                this also tells how many times it takes to shift a note down
 *                the entire string
 */
Gam_String::Gam_String( Point top_pt, int dxx, int dyy, int num_divisions )
	:top(top_pt), dx(dxx), dy(dyy), divisions(num_divisions), notes( num_divisions, NULL )
{
}

Gam_String::~Gam_String()
{
}

//adds a note to the top of this String
void Gam_String::add_note()
{
}

/** Slide all the notes down one. If there is a note on the bottom string
 * detach it and free it's memory.
 */
void Gam_String::increment()
{
	Circle * temp = notes[0];
	for( int i = 1; i < divisions; i++ )
	{
		notes[i] = temp;
		temp = notes[i];
		//redraw
	}
}

void Gam_String::attach( Gamelan_Window& w )
{
	win = &w;
}

//detach the string. detach remaining notes and free their memory
void Gam_String::detach()
{
}
