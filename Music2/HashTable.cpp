#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "HashTable.hpp"

using namespace std;

HashTable::HashTable(int hashTableSize){

  numCollisions = 0;
  numSongs = 0;

  this->hashTableSize = hashTableSize;
  hashTable = new Song*[hashTableSize];
  for(int i=0;i<hashTableSize;i++){
    hashTable[i] = nullptr;
  }

}

HashTable::~HashTable(){
  for(int i = 0; i < hashTableSize; i++){
    if(hashTable[i] != nullptr){
        Song *tmp = hashTable[i];
        Song *next = tmp->next;
        while(tmp!=nullptr){
          hashTable[i] = next;
          delete tmp;
          tmp = next;
          if(tmp==nullptr){
              break;
          }
          next = tmp->next;

        }
    }
  }
}

void HashTable::addSong(string songName, string songArtist, string songAlbum, string path){
  if(isInTable(songName) == false){
    unsigned int hash = getHash(songName);

    Song *song = new Song;
    song->name = songName;
    song->artist = songArtist;
    song->album = songAlbum;
    song->path = path;

    if(hashTable[hash] != nullptr){

      song->next = hashTable[hash];
      hashTable[hash] = song;
      numCollisions++;

    } else {
      song->next = nullptr;
      hashTable[hash] = song;

    }
  }
}

unsigned int HashTable::getHash(string song){
  unsigned int hashValue = 5381;
  int length = song.length();
  for (int i=0;i<length;i++)
  {
  hashValue=((hashValue<<5)+hashValue) + song[i];
  }
  hashValue %= hashTableSize;
  return hashValue;
}

Song* HashTable::searchSongs(string song){
  return searchTable(song);
}

Song* HashTable::searchTable(string song){
  int hash = getHash(song);
  Song *tmp = hashTable[hash];
  while(tmp != nullptr){
    if(tmp->name == song){
      return tmp;
    }
    tmp=tmp->next;
  }
  return nullptr;
}

bool HashTable::isInTable(string songName){
  Song *tmp = searchTable(songName);
  if(tmp == nullptr){
    return false;
  } else {
    return true;
  }
}

int HashTable::getNumCollisions(){
  return numCollisions;
}
int HashTable::getTotalNumSongs(){
  return numSongs;
}

void HashTable::showAllSongs(){
  Song* tmp = new Song;
  for(int i = 0; i < hashTableSize; i++){
    tmp=hashTable[i];
    while(tmp!=nullptr){
      cout<<tmp->name<<" by "<<tmp->artist<<endl;
      tmp=tmp->next;
    }
  }
}

Song* HashTable::randomSong(){
  int index = rand()%(hashTableSize);
  int random = rand()%(300);
  Song* temp = hashTable[index];
  for(int i = 0; i < random; i++){
    if(temp->next != nullptr){
      temp = temp->next;
    } else {
      temp = hashTable[index];
    }
  }
  return temp;
}

Song* HashTable::shuffle(){
  Song* temp = randomSong();
  return temp;
}
