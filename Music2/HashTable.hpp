#ifndef HW_7_HASH_TABLE
#define HW_7_HASH_TABLE

#include <string>
#include <fstream>

using namespace std;
// struct to store word + count combinations
struct Song
{
    string name;
    string artist;
    string album;
    string path;
    Song* next;
};

class HashTable {
  public:
    HashTable(int hashTableSize);
    ~HashTable();
    void addSong(string songName, string songArtist, string songAlbum, string path);
    bool isInTable(string songName);
    void showAllSongs();
    int getNumCollisions();
    int getTotalNumSongs();
    Song* searchSongs(string song);
    Song* shuffle();

  private:
    /* member functions */
    unsigned int getHash(string song);
    Song* searchTable(string song);
    Song* randomSong();

    /* instance variables */
    Song** hashTable;
    int hashTableSize;
    int numSongs;
    int numCollisions;
};




#endif
