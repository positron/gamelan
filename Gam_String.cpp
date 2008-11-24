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
	:top(top_pt), dx(dxx), dy(dyy), divisions(num_divisions), notes( num_divisions, NULL ),
	 line( top_pt, Point( top_pt.x + dxx, top_pt.y + dyy ) )
{
}

Gam_String::~Gam_String()
{
}

//adds a note to the top of this String (position 0 in the vector)
void Gam_String::add_note()
{
	add_note( 0 );
}

//add a note at the ith division of this string with correctly computed radius
void Gam_String::add_note( int i )
{
	//sanity check: if there is already a note at the top don't do anything
	if( notes[i] ) return;
	Point pt( top.x + (double)(i)/(divisions-1)*dx, top.y + (double)(i)/(divisions-1)*dy );
	//radius is 10 at top and 30 at bottom
	int radius = 10 + (double)(i)/(divisions-1)*20.0;
	notes[i] = new Circle( pt, radius );
	//cout << pt.x << " " << pt.y << " " << radius << "\n";
	win->attach( * notes[i] );
}

/** Slide all the notes down one.
 */
void Gam_String::increment()
{
	//delete last note if it exists
	if( notes[ divisions - 1 ] )
	{
		cout << 'r';
//		win->detach( * notes[ divisions - 1 ] );
//		delete notes[ divisions - 1 ];
	}
	Circle * temp1 = NULL;
	Circle * temp2 = NULL;
	for( int i = 0; i < notes.size(); i++ )
	{
		if( notes[i] )
		{
			cout << i;
			//because rounding errors tend to accumulate, we first calculate where
			//the center square should be, then add the right amound to get it there
			//instead of just adding the same amount each time
			int radius = 10 + (double)(i)/(divisions-1)*20.0;
			notes[i]->set_radius( radius );
			//where it's supposed to be
			int x = top.x + (double)(i)/(divisions-1)*dx;
			int y = top.y + (double)(i)/(divisions-1)*dy;
			//movement required to get there
			x = x - notes[i]->center().x;
			y = y - notes[i]->center().y;
			notes[i]->move( x, y );
			cout << i;
		}
		temp1 = notes[i];
		notes[i] = temp2;
		temp2 = temp1;
	}
}

bool Gam_String::handle_mouse( int x, int y )
{
	//if there is no note to even click, return false
	if( !notes[ divisions - 1 ] ) return false;
}

void Gam_String::attach( Gamelan_Window& w )
{
	win = &w;
	win->attach( line );
}

//detach the string. detach remaining notes and free their memory
void Gam_String::detach()
{
	win->detach( line );
}
