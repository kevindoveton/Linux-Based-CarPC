// --------------------------
// Kevin Doveton
// Copyright 2015
// --------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Constants
#include "Constants.h"

// QT
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QTimer>


// General
#include <iostream>								// General IO (cout/cin)
#include <string>								// Strings - STD :: String
#include <sstream>								// String Streams - STD :: stringstream
#include <iomanip>								// IOMainIP - time
#include <ctime>								// C-Time - time
#include <chrono>								// Chrono - STD :: chrono
#include <vector>


// GUI
#include "ui_mainwindow.h"						// Main Form


// Music
#include "libraries/bass/bass.h"				// Bass
#include <alsa/asoundlib.h>						// Alsa (System Volume)
#include <taglib/tag.h>							// Taglib (ID3 Tags)
#include <taglib/taglib.h>						// Taglib
#include <taglib/tstring.h>						// Taglib
#include <taglib/fileref.h>						// Taglib
#include <sqlite3.h>							// SQLite (Data Storage)
#include "libraries/SQLiteCpp/SQLiteCpp.h"		// SQLiteCPP (SQLite API)


// Clases
#include "ClassMusic.h"							// Song Data
//#include "ClassSong.h"							
#include "ClassMusicDB.h"
#include "listviewmusicdelegate.h"				// listviewMusic Delegate
#include "ClassMusicPlayer.h"


namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		// --------------------------------------
		// frameTopBar
		// --------------------------------------

		void on_buttonVolumeUp_released(); 
		// --------------------------------------
		// TODO
		// Volume up in top frame
		// Turns volume up by 5%

		void on_buttonVolumeDown_released();
		// --------------------------------------
		// TODO
		// Volume down in top frame
		// Turns volume down by 5%

		void on_buttonMusicPlayPause_released();
		// Play/Pause button top frame
		// Swaps image from play/pause
		// Play/Pause music
		// --------------------------------------
		// TODO
		// Plays random song if nothing selected 

		void on_buttonMusicNext_released();
		// Next button in top frame
		// Removes current song from upNext and
		// places in recentlyPlayed
		// Plays next song in upNext
		// --------------------------------------
		// TODO
		// Error check // no song next

		void on_buttonMusicPrevious_released();
		// Previous button in top frame
		// Removes current song from upNext and
		// places in recentlyPlayed
		// removes last element from recentlyPlayed
		// and places as first element in upNext
		// Plays song
		// --------------------------------------
		// TODO
		// Error check // no song



		// --------------------------------------
		// frameTabBar
		// --------------------------------------

		void on_buttonHome_released();
		// Switches to home frame
		// switches selected label to home

		void on_buttonMusic_released();
		// Switches to music frame
		// Switches selected label to music

		void on_buttonPhone_released();
		// Switches to phone frame
		// Switches selected label to phone

		void on_buttonMaps_released();
		// Switches to maps frame
		// Switches selected label to map



		// --------------------------------------
		//musicTabBar
		// --------------------------------------

		void on_buttonBack_released();
		// Switches tab bar to standard tab bar
		// Selected label to music

		void on_buttonArtist_released();
		// Switches to artist view
		// Selected label to artists

		void on_buttonAlbum_released();
		// Switches to album view for last selected artist
		// Selected label to album

		void on_buttonSong_released();
		// Switches to song view for last selected artist
		// Selected label to song

		// --------------------------------------
		// frameHome
		// --------------------------------------

		void on_buttonQuit_released();
		// Quit button, home screen
		// On release, program will quit.



		// --------------------------------------
		// frameMusic
		// --------------------------------------

		void on_listviewMusic_clicked(const QModelIndex &index);
		// Items on music frame
		// switch statement, on click will go from artist -> album
		// -> song view -> play song



		// --------------------------------------
		// Loops
		// --------------------------------------

		void runLoop();
		// general run loop
		// checks time
		// checks music

	private:
		Ui::MainWindow *ui;

		void setSongTags(std::string title, std::string album, std::string artist);
		// set the song labels

		void setButtonPlayPauseText(int playStatus);
		// set the text according to current playing ness

		void hideAllCentreFrames();
		// hide all the frames in the centre

		void hideMenuButtons();
		// hide standard menu buttons

		void showMenuButtons();
		// show standard menu buttons

		void showMusicButtons();
		// show music specific buttons

		void hideMusicButtons();
		// hide music specific buttons

		int selectedFrame(int selected = -1);
		// set selected frame
		// 0 = home, 1 = music, 2 = phone, 3 = maps
		// if set blank or incorrectly will return the
		// currently selected frame

		int selectedButton(int selected = -1);
		// Set selected label on bottom tab bar
		// if set blank or incorrectly will return the
		// currently selected button


		void hideAllTabSelected();
		// hide all the selected labels for the tab bar

		int artistIDCur;
		int albumIDCur;
		int songIDCur;
		QStringList artists;

		std::vector<SongData> upNext;
		std::vector<SongData> recentlyPlayed;

		int currentView = 1; // start up in artist mode
		song nowPlaying;
		SongData currentSong;
		QStandardItemModel* model;

		// Music Player
		MusicPlayer musicPlayer;
		MusicDB musicDB;
};

std::string getCurrentTime();
// return current time as string



#endif // MAINWINDOW_H
