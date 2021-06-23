#include <iostream>
#include <vector>
#include "ArtistTree.hpp"
#include "HashTable.hpp"

using namespace std;

ArtistTree::ArtistTree()
{
	root = NULL;
}


/*creates a new Artist pointer with the name of specified by the parameter*/
Artist* ArtistTree::createArtist(string name)
{
	Artist* newArtist = new Artist;
	newArtist->name = name;
	newArtist->right = NULL;
	newArtist->left = NULL;
	return newArtist;
}

/*creates a new Song pointer with data members specified by the parameters*/
Song* ArtistTree::createSong(string path, string title, string artist, string album)
{
	Song* newSong = new Song;
	newSong->path = path;
	newSong->name = title;
	newSong->artist = artist;
	newSong->album = album;
	return newSong;
}

/*searches the tree starting at currNode looking for a node with the same name
as the variable in the parameter, name

returns NULL if not found*/
Artist* ArtistTree::searchArtistHelper(Artist* currNode, string name)
{
	while (currNode != NULL) // loops until it hits the bottom of the tree
	{
		if (currNode->name == name) // found the artist
			return currNode;

		if (currNode->name < name) // artist name is later in the alphabet
		{
			currNode = currNode->right;
		}

		else if (currNode->name > name) // artist name is earlier in the alphabet
		{
			currNode = currNode->left;
		}
		/*cout << "name: " << name << endl;
		cout << currNode->name << endl;*/
	}
	return NULL;
}

/* searches the tree for a song with title=title and artist=artist

returns NULL if not found*/
Song* ArtistTree::searchSongHelper(string artist, string title)
{
	Artist* tempArtist = searchArtistHelper(root, artist); // finding the correct artist
	if (tempArtist == NULL) // artist doesnt exist
		return NULL;

	Song* tempSong;
	for (int i = 0; i < tempArtist->songs.size(); i++) // looping through all the songs belonging to the correct artist
	{
		tempSong = tempArtist->songs[i];
		if (tempSong->name == title) // found the correct song
			return tempSong;
	}
	return NULL;
}

/*calls searchSongHelper

returns flase if not found, true otherwise*/
bool ArtistTree::searchSong(string artist, string title)
{
	Song* tempSong = searchSongHelper(artist, title);
	if (tempSong == NULL) // not found
		return false;

	else // found
		return true;
}


Artist* ArtistTree::searchArtist(string name){
	return searchArtistHelper(root, name);
}
/*creates a new artist pointer using createArtist and adds it to the tree

returns NULL if the artist is already in the tree
returns the artist ponter otherwise*/
Artist* ArtistTree::addArtistHelper(Artist* currNode, string name)
{
	Artist* newArtist = createArtist(name); // new artist pointer
	if (currNode == NULL) // tree is empty
		root = newArtist;

	while (currNode != NULL) // loop until the end of the tree
	{
		if (newArtist->name == currNode->name) // artist already in tree
		{
			cout << "Artist already added" << endl;
			return NULL;
		}

		if (name < currNode->name) // must look left
		{
			if (currNode->left == NULL) // found where to add the artist
			{
				currNode->left = newArtist;
				return newArtist;
			}

			else
				currNode = currNode->left;
		}

		if (name > currNode->name) // must look right
		{
			if (currNode->right == NULL) // found where to add the artist
			{
				currNode->right = newArtist;
				return newArtist;
			}

			else
				currNode = currNode->right;
		}
	}
	return newArtist;
}

/*calls addArtistHelper from the root*/
void ArtistTree::addArtist(string name)
{
	addArtistHelper(root, name);
}

/*creates a new Song pointer and adds it to the vector belonging to the correct artist

returns the new Song*/
Song* ArtistTree::addSongHelper(Artist* currNode, string path, string title, string artist, string album)
{
	Song* newSong = createSong(path, title, artist, album);
	Artist* tempArtist = searchArtistHelper(root, artist); // searching for correct artist
	if (tempArtist == NULL) // artist does not exist
		tempArtist = addArtistHelper(root, artist); // creates new artist if it was not already in tree

	tempArtist->songs.push_back(newSong); // adds the song to the artist's vector
	return newSong;
}

/*calls addSongHelper from the root*/
void ArtistTree::addSong(string path, string title, string artist, string album)
{
	addSongHelper(root, path, title, artist, album);
}

/*prints all the artists and their songs in an in order fashion starting from currNode*/
void ArtistTree::printTreeHelper(Artist* currNode)
{
	if (currNode == NULL) // base case
		return;

	printTreeHelper(currNode->left); // first step of in order traversal

	cout << "-----" << currNode->name << "-----" << endl; // artist name
	for (int i = 0; i < currNode->songs.size(); i++) // all songs along with the album they belong to
		cout << i + 1 << ": " << (currNode->songs[i])->name << " - " << (currNode->songs[i])->album << endl;
	cout << endl;

	printTreeHelper(currNode->right); // last step if in order traversal
}

/*calls printTreeHelper from the root*/
void ArtistTree::printTree()
{
	printTreeHelper(root);
}

/*deletes the song with the specified title from the specified artist pointer's
vector of songs.

returns the deleted song if succsessful, NULL if not*/
Song* ArtistTree::deleteSongHelper(Artist* artist, string title)
{
	Song* tempSong;
	for (int i = 0; i < artist->songs.size(); i++) // loops through the entire songs vector
	{
		tempSong = artist->songs[i];
		if (tempSong->name == title) // compares title of the current song being looked at to the desired title
		{
			artist->songs.erase(artist->songs.begin() + i); // deletes the song from the vector and deals with memory management
			return tempSong;
		}
	}
	return NULL; // did not find the song
}

/*uses the searchArtistHelper function to find the specified artist. If the artist
exists, calls deleteSongHelper with the artist pointer and title and stores the return

returns false if the artist does not exist or the song does not exist
returns true if succsessful*/
bool ArtistTree::deleteSong(string artist, string title)
{
	Artist* tempArtist = searchArtistHelper(root, artist);
	if (tempArtist == NULL)
		return false;

	Song* tempSong = deleteSongHelper(tempArtist, title);

	if (tempSong == NULL)
		return false;

	else
		return true;
}
