#pragma once

#include "../../std_lib_facilities.h"

/** This file contains a function that reads in a song file into a vector
 * of ints. It returns an empty vector of an error occurs.
 */
vector<int> read_song_file( string filename )
{
	vector<int> notes;
	ifstream indata;
	indata.open( filename.c_str() );
	if( !indata )
	{
		cerr << "Error: file could not be opened" << endl;
		//return empty vector if the file can't be opened
		return notes;
	}
	
	int num = 0;
	while( !indata.eof() )
	{
		indata >> num;
		notes.push_back( num );
	}
	indata.close();
	return notes;
}

//for testing
int main()
{
	vector<int> song = read_song_file( "test.txt" );

	//test loop to print contents of song
	for( int i = 0; i < song.size(); i++ )
		cout << song[i] << " ";
	keep_window_open();
}
