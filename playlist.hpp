//Taken from CountryNetwork (Assignment3)
//Lab-4

#pragma once
#include <iostream>

struct Song
{
    std::string name;         // name of song
    std::string artist;      // name of artist
    int duration;       // length of song
    Song *next;            // pointer to the next song
};

class PlayList {
    private:
        // pointer to head of linked-list of countries
        Song* head;
    public:
        // See writeup for method descriptions
        PlayList();
        bool isEmpty();
        void addSong(std::string songName, std::string songArtist, int duration);
        void deleteSong(std::string songName);
        void loadDefaultSetup();
        Song* searchPlayList(std::string songName);
        void deletePlayList();
        void randomizeList();
        void printPath();
};
