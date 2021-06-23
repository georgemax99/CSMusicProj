#pragma once
#ifndef ArtistTree_HPP
#define ArtistTree_HPP
#include <iostream>
#include <vector>
#include "HashTable.hpp"

using namespace std;

// struct Song{
//     string path; // path of song
//     string title;
//     string artist;
//     string album;
//     Song* next = NULL;
// };

struct Artist
{
	int numSongs = 0;
	string name;
	vector<Song*> songs;
	Artist* left;
	Artist* right;
};

class ArtistTree {
private:
	Artist* createArtist(string name);

	Artist* addArtistHelper(Artist* currNode, string name);

	Song* createSong(string path, string title, string artist, string album);

	Song* addSongHelper(Artist* currNode, string path, string title, string artist, string album);

	Artist* deleteArtistHelper(Artist* currNode, string name);

	Song* deleteSongHelper(Artist* artist, string title);

	void printTreeHelper(Artist* currNode);

	void print2DUtilHelper(Artist* currNode, int space);

	Artist* root;

public:

	Artist* searchArtistHelper(Artist* currNode, string name);

	Song* searchSongHelper(string artist, string title);

	void addArtist(string name);

	void addSong(string path, string title, string artist, string album);

	void deleteArtist(string name);

	bool deleteSong(string artist, string title);

	bool searchSong(string artist, string title);

	Artist* searchArtist(string name);

	void printTree();

	// default constructor
	ArtistTree();

	//~ArtistTree();

	void print2DUtil(int space);

};
#endif
