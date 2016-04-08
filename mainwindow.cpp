// --------------------------
// Kevin Doveton
// Copyright 2015
// --------------------------

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	//  Set home frame for start up
	selectedFrame(0);
	hideMusicButtons(); // this is the tab bar at the bottom in the music frame


	// labels for now playing
	// setSongTags(album, artist, song)
	setSongTags("", "", "");
	ui->labelTime->setText(getCurrentTime().c_str());


	// Create Song Model
	// this is used in the now playing view
	model = new QStandardItemModel;
	musicDB.getArtists(model); // set artist
	ui->listviewMusic->setModel(model); // attach model to list
	ui->listviewMusic->setItemDelegate(new listViewMusicDelegate); // attach delegate to list

	// Run Loop
	// this timer will call
	// MainWindow::runLoop()
	// once every second
	QTimer* runLoopTimer = new QTimer(this);
	connect(runLoopTimer, SIGNAL(timeout()), this, SLOT(runLoop()));
	runLoopTimer->start(1000); // 1000ms = 1 seconds


	// Set window to full screens
	QMainWindow::showFullScreen();

	std :: cout << "started"
				<< std :: endl;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::runLoop()
{
	/*	std::cout 	<< "runLoop timed out " 
					<< std::endl;
	*/


	// TIME SECTION
	ui->labelTime->setText(getCurrentTime().c_str()); // set the time



	// MUSIC SECTION
	// check if song has finished played
	// probably not the best way.. this will play a song as soon as you push the stop button
	// could possibly add a stopped variable? not that we even have a stop button
	if ((musicPlayer.currentBassStatus() == 0) && (musicPlayer.getOldBassStatus() == 1)) // song was playing and is now stopped
	{
		if (musicPlayer.playing())
		{
			// update playcount
			upNext[0].setPlayCount(upNext[0].getPlayCount() + 1);
			musicDB.setPlayCount(upNext[0].getPlayCount(), upNext[0].getID());

			// Push to previously played and remove from upNext
			recentlyPlayed.push_back(upNext[0]);
			upNext.erase(upNext.begin());

			// play new song
			int playStatus = musicPlayer.playNewSong(upNext[0].getPath());
			setButtonPlayPauseText(playStatus);
			setSongTags(upNext[0].getTitle(), upNext[0].getAlbum(), upNext[0].getArtist());
		}
	}
	musicPlayer.setOldBassStatus(musicPlayer.currentBassStatus()); // update oldBassStatus, bad things happen if we dont do this
	
}







std::string getCurrentTime() {
	std::stringstream strstream;
	strstream.str() = "";
	// set time
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	strstream << std::put_time(&tm, "%H:%M");
	return strstream.str();
}

void MainWindow :: on_buttonRBHome_released()
{
	selectedFrame(0); 	// 	frames
}


void MainWindow :: hideAllCentreFrames()
{
	ui->frameHome->hide();
	ui->frameMusic->hide();
	ui->framePhone->hide();
	ui->frameMaps->hide();
}

void MainWindow :: on_buttonMusic_released()
{
	// frames
	selectedFrame(1);
}

void MainWindow :: on_buttonPhone_released()
{
	// frames
	selectedFrame(2);
}

void MainWindow :: on_buttonMaps_released()
{
	selectedFrame(3); // frames
}

void MainWindow :: on_buttonVolumeDown_released()
{
	// lower the volume by a percentage..
	std :: cout << "Volume Down"
				<< std :: endl;

	if (systemVolume.getCurrentVolume() >= 0 + systemVolume.VOLUMECHANGE) // check that we won't go below minimum volume
		systemVolume.setMasterVolume(systemVolume.getCurrentVolume() - systemVolume.VOLUMECHANGE);
	else
		systemVolume.setMasterVolume(0);

	std::cout	<< "Current Volume: "
				<< systemVolume.getCurrentVolume()
				<< std::endl;
}

void MainWindow :: on_buttonVolumeUp_released()
{
	// increase the volume by a percentage
	std :: cout << "Volume Up"
				<< std :: endl;

	if (systemVolume.getCurrentVolume() <= 100 - systemVolume.VOLUMECHANGE) // check that we don't go above the max volume
		systemVolume.setMasterVolume(systemVolume.getCurrentVolume() + systemVolume.VOLUMECHANGE);
	else
		systemVolume.setMasterVolume(100);

	std::cout	<< "Current Volume: "
				<< systemVolume.getCurrentVolume()
				<< std::endl;

}

void MainWindow :: on_buttonMusicPlayPause_released()
{

	switch (musicPlayer.currentBassStatus())
	{
		case 0:
			musicDB.shuffleAll(-1, upNext);
			musicPlayer.playNewSong(upNext[0].getPath());
			break;

		case 1:
			musicPlayer.pause();
			break;

		case 3:
			musicPlayer.resume();
			break;

		default:
			break;

	}

	setButtonPlayPauseText(musicPlayer.currentBassStatus());
	setSongTags(upNext[0].getTitle(), upNext[0].getAlbum(), upNext[0].getArtist());
}

void MainWindow :: on_buttonMusicNext_released()
{
	// Update skipcount
	std::cout << "SkipCount: " << upNext[0].getSkipCount() << std::endl;
	upNext[0].setSkipCount(upNext[0].getSkipCount() + 1);
	musicDB.setSkipCount(upNext[0].getSkipCount(), upNext[0].getID());

	if (musicPlayer.currentBassStatus() == 0)
	{
		musicDB.shuffleAll(-1, upNext);
		musicPlayer.playNewSong(upNext[0].getPath());
	}
	else
	{
		if (!upNext.empty())
		{
			recentlyPlayed.push_back(upNext[0]);
			upNext.erase(upNext.begin());
				if (!upNext.empty())
				{
					musicPlayer.playNewSong(upNext[0].getPath());
					setSongTags(upNext[0].getTitle(), upNext[0].getAlbum(), upNext[0].getArtist());
				}
				else
				{
					musicPlayer.stop();
					setSongTags("","","");
				}
		}
	}

	setButtonPlayPauseText(musicPlayer.currentBassStatus());
}

void MainWindow :: on_buttonMusicPrevious_released()
{
	upNext.insert(upNext.begin(), recentlyPlayed.back());
	recentlyPlayed.pop_back();
	int playStatus = musicPlayer.playNewSong(upNext[0].getPath());
	setButtonPlayPauseText(playStatus);
	setSongTags(upNext[0].getTitle(), upNext[0].getAlbum(), upNext[0].getArtist());
}

void MainWindow :: setButtonPlayPauseText(int playStatus)
{
	switch (playStatus)
	{
		case 0:
			//            ui->buttonMusicPlayPause->setText("Play");
			ui->buttonMusicPlayPause->setStyleSheet("background-image: url(./resources/icons/play.png);"
													"background-repeat: no-repeat;");
			break;

		case 1:
			//            ui->buttonMusicPlayPause->setText("Pause");
			ui->buttonMusicPlayPause->setStyleSheet("background-image: url(./resources/icons/pause.png);"
													"background-repeat: no-repeat;");
			break;

		case 2:
			//            ui->buttonMusicPlayPause->setText("2 = Err..");
			break;

		case 3:
			//            ui->buttonMusicPlayPause->setText("Play");
			ui->buttonMusicPlayPause->setStyleSheet("background-image: url(./resources/icons/play.png);"
													"background-repeat: no-repeat;");
			break;

		default:
			//            ui->buttonMusicPlayPause->setText("Err...");
			break;
	}
}

void MainWindow :: setSongTags(std::string title, std::string album, std::string artist)
{
	ui->labelCurrentTrack->setText(title.c_str());
	ui->labelCurrentArtistAlbum->setText((artist + " - " + album).c_str());
}

void MainWindow::on_buttonQuit_released()
{
	quick_exit(0);
}

void MainWindow :: on_listviewMusic_clicked(const QModelIndex &index)
{
	ui->listviewMusic->setViewMode(QListView::IconMode);
	switch (currentView)
	{
		case 1:
			// going to album view now
			artistIDCur = index.sibling(index.row(), 1).data().toInt();
			model->clear();
			if (artistIDCur != -1)
				musicDB.getAlbums(model, artistIDCur);
			else
				musicDB.getAllAlbums(model);


			currentView = 2;
			break;

		case 2:
			// going to the song view now
			albumIDCur = index.sibling(index.row(), 1).data().toInt();
//			std::cout 	<< albumIDCur
//						<< std::endl;
			model->clear();
			if (albumIDCur != -1)
				musicDB.getSongs(model, albumIDCur);
			else
				musicDB.getAllSongs(model, artistIDCur);

			ui->listviewMusic->setViewMode(QListView::ListMode);
			currentView = 3;
			break;

		case 3:
		{
			ui->listviewMusic->setViewMode(QListView::ListMode);
			// selected a song
			songIDCur = index.sibling(index.row(), 1).data().toInt();
			std::cout << songIDCur;
			SongData temp;

			musicDB.getSongPath(songIDCur, temp);
			upNext.clear();
			upNext.push_back(temp);
			musicPlayer.playNewSong(upNext[0].getPath());

			// Picked artist
			// Chose all songs
			if ((artistIDCur == -1) && (albumIDCur == -1))
				musicDB.shuffleAll(songIDCur, upNext);

			// Picked all albums
			// chose all songs
			else if (albumIDCur == -1)
					musicDB.shuffleArtist(songIDCur, upNext);

			// chose album
			else
				musicDB.shuffleAlbum(songIDCur, upNext);

			setButtonPlayPauseText(1);
			setSongTags(upNext[0].getTitle(), upNext[0].getAlbum(), upNext[0].getArtist());
			std::cout 	<< upNext[0].getArtist()
						<< std::endl;
			break;
		}

		default:
			break;

	}
}

void MainWindow :: showMenuButtons()
{
	ui->buttonHome->show();
	ui->buttonMusic->show();
	ui->buttonMaps->show();
	ui->buttonPhone->show();
}


void MainWindow :: showMusicButtons()
{
	ui->buttonBack->show();
	ui->buttonMusicArtist->show();
	ui->buttonMusicAlbum->show();
	ui->buttonMusicSong->show();
}

void MainWindow :: hideMusicButtons()
{
	ui->buttonBack->hide();
	ui->buttonMusicArtist->hide();
	ui->buttonMusicAlbum->hide();
	ui->buttonMusicSong->hide();
}


int MainWindow :: selectedFrame(int selected)
{
	switch (selected)
	{
		case 0:
			ui->frameHome->show();
			ui->frameMusic->hide();
			ui->framePhone->hide();
			ui->frameMaps->hide();
			break;

		case 1:
			ui->frameHome->hide();
			ui->frameMusic->show();
			ui->framePhone->hide();
			ui->frameMaps->hide();
			break;

		case 2:
			ui->frameHome->hide();
			ui->frameMusic->hide();
			ui->framePhone->show();
			ui->frameMaps->hide();
			break;

		case 3:
			ui->frameHome->hide();
			ui->frameMusic->hide();
			ui->framePhone->hide();
			ui->frameMaps->show();
			break;

		default:
			if (ui->frameHome->isVisible())
				selected = 0;
			else if (ui->frameMusic->isVisible())
				selected = 1;
			else if (ui->framePhone->isVisible())
				selected = 2;
			else if (ui->frameMaps->isVisible())
				selected = 3;

			break;

	}
	return selected;
}



void MainWindow::on_buttonBack_released()
{
	hideMusicButtons();
	showMenuButtons();
}

void MainWindow::on_buttonArtist_released()
{
	currentView = 1;
	model->clear();
	musicDB.getArtists(model); // set artist
}

void MainWindow::on_buttonAlbum_released()
{
	currentView = 2;
	model->clear();
	musicDB.getAlbums(model, artistIDCur);
}

void MainWindow::on_buttonSong_released()
{
	currentView = 3;
	std::cout	<< albumIDCur
				<< std::endl;
	model->clear();
	musicDB.getSongs(model, albumIDCur);
}


