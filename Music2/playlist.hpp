#pragma once
#include <iostream>
#include "HashTable.hpp"

/*
struct Song
{
    std::string name;         // name of song
    std::string artist;      // name of artist
    std::string album;
    std::string path;
    Song* next = NULL;            // pointer to the next song
}; */

class PlayList {
    private:
        // pointer to head of linked-list of countries
        Song* head;
    public:
        // See writeup for method descriptions
        PlayList();
        std::string p_name;
        bool isEmpty();
        void addSong(Song* newSong);
        void deleteSong(std::string songName);
        void loadDefaultSetup();
        Song* searchPlayList(std::string songName);
        void deletePlayList();
        void randomizeList();
        void printPath();
        Song* front(){return head;};
};
