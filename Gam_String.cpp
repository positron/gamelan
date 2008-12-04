#include "Gam_String.h"

/** Construct a Gamelan String object. This takes 4 variables.
 * top_pt: the point of the string on the top of the window
 * dxx: the number of pixels to go right or left from top_pt (can be negative)
 * dyy: the number of pixels to go down from top_pt
 * num_divisions: the number of notes that can fit on a string at a time
 *                this also tells how many times it takes to shift a note down
 *                the entire string
 */
Gam_String::Gam_String( Point top_pt, int dxx, int dyy, int num_divisions, Color col )
	:top(top_pt), dx(dxx), dy(dyy), divisions(num_divisions), notes( num_divisions ),
	 line( top_pt, Point( top_pt.x + dxx, top_pt.y + dyy ) )
{
	for( int i = 0; i < num_divisions; i++ )
		notes[i].circ = create_note( i, col );
}

Gam_String::~Gam_String()
{
}

//adds a note (ie makes visible) to the top of this string
void Gam_String::add_note()
{
	notes[0].displayed = true;
	win->attach( notes[0].circle() );
}

//creates a note at the ith division of this string with correctly computed
//radius and position
Circle* Gam_String::create_note( int i, Color col )
{
	Point pt( top.x + (double)(i)/(divisions-1)*dx, top.y + (double)(i)/(divisions-1)*dy );
	//radius is 10 at top and 30 at bottom
	int radius = 10 + (double)(i)/(divisions-1)*20.0;
	//we must make a new circle otherwise it would go out of scope when this function ends
	Circle * c = new Circle( pt, radius/2 );
	c->set_style( Line_style( Line_style::solid, radius ) );
	c->set_color( col );
	return c;
}

/** Slide all the notes down one.
 */
void Gam_String::increment()
{
	for( int i = divisions - 1; i > 0; i-- )
	{
		if( !notes[i].displayed && notes[i-1].displayed )
		{
			notes[i].displayed = true;
			win->attach( notes[i].circle() );
		}
		else if( notes[i].displayed && !notes[i-1].displayed )
		{
			notes[i].displayed = false;
			win->detach( notes[i].circle() );
		}
	}
	if( notes[0].displayed )
	{
		notes[0].displayed = false;
		win->detach( notes[0].circle() );
	}
}

bool Gam_String::handle_mouse( int x, int y )
{
	//if there is no note to even click, return false
	if( !notes[ divisions - 1 ].displayed ) return false;

	//use distance formula to calculate distance between click and center of the note
	int distance = sqrt( x*x + y*y );
	//cout << x << " " << y << " " << distance << "\n"; //debug
	//the user hit the note if the distance is less than the radius (30)
	return distance < 30;
}

void Gam_String::attach( Gamelan_Window& w )
{
	win = &w;
	win->attach( line );
}

//detach the string. detach remaining notes
void Gam_String::detach()
{
	win->detach( line );
	for( int i = 0; i < notes.size(); i++ )
		if( notes[i].displayed )
			win->detach( notes[i].circle() );
}
