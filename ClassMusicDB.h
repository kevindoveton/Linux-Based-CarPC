// --------------------------
// Kevin Doveton
// Copyright 2015
// --------------------------

// QT
#include <QtCore>
#include <QtGui>

// General
#include <iostream>								// General IO (cout/cin)
#include <string>								// Strings - STD :: String
#include <sstream>								// String Streams - STD :: stringstream
#include <iomanip>								// IOMainIP - time
#include <ctime>								// C-Time - time
#include <chrono>								// Chrono - STD :: chrono
#include <vector>

// Music
#include <sqlite3.h>							// SQLite (Data Storage)
#include "libraries/SQLiteCpp/SQLiteCpp.h"		// SQLiteCPP (SQLite API)

#include "ClassMusic.h"

class MusicDB
{
	public:
		void getAllArtists(QStandardItemModel* model);
		// Get all artists from DB
		// Place into QStandardItemModel

		bool getPlaylist(std::string path);
		// --------------------------------------
		// TODO

		void getArtist(QStandardItemModel& model);
		// --------------------------------------
		// TODO

		void getAlbums(QStandardItemModel* model, int artistID);
		// Converts artistID to list of albums in the form of a 
		// model
		// Requires artistID, QStandardItemModel
		
		void getSongPath(int songID, SongData& currentSong);
		// Convert songID to a SongData containing all info 
		// about a song
		// Requires songID, SongData

		void getSongs(QStandardItemModel* model, int albumID);
		// Coverts albumID to list of songs in the form of a
		// model
		// Requires albumID, QStandardItemModel

		void shuffleAlbum(int currentSongID, std::vector<SongData>& playlist);
		// Populate a vector with a playlist of songs

	private:
		std::string DBPATH = "resources/music/musicLibrary.sqlite3";

};
