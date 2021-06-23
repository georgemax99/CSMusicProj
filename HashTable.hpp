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
    Song* next;
};

class HashTable {
  public:
    HashTable(int hashTableSize);
    ~HashTable();
    void addSong(string songName, string songArtist, string songAlbum);
    bool isInTable(string songName);
    int getNumCollisions();
    int getTotalNumSongs();
    string shuffle();

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
