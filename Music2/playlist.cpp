#include "playlist.hpp"

using namespace std;

PlayList::PlayList() {
  head = NULL;
  return;
}

bool PlayList::isEmpty() {
  if(head==NULL){
    return true;
  } else {return false;}
}

void PlayList::addSong(Song* newSong) {
  if(newSong == NULL){
    cout << "Song file not found, cannot add" << endl;
    return;
  }

  //cout << "adding: " << newSong->name;

  Song* newNode = new Song;
  newNode->name = newSong->name;
  newNode->artist = newSong->artist;
  newNode->album = newSong->album;
  newNode->path = newSong->path;
  newNode->next = NULL;

  if(head == NULL){
    head = newNode;
    return;
  }

  Song* temp = head;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = newNode;
  return;

}

void PlayList::deleteSong(string songName) {
  if(head == NULL){
    return;
  }
  if(head->name == songName){
    Song *temp = head;
  	head = temp->next;
  	delete temp;
    return;
  }

  Song *pres = head;
  Song *prev = NULL;

  while(pres != NULL){
    if(pres->name == songName){
      break;
    }
    prev=pres;
    pres = pres->next;
  }
  if(pres == NULL){
    cout << "Song does not exist." << endl;
  }
  else{
    prev->next = prev->next->next;
    delete pres;
  }

  return;
}

Song* PlayList::searchPlayList(string songName)
{
  Song* temp = head;
  while (temp != NULL){
    if (temp->name == songName){
      return temp;
    }
    temp = temp->next;
  }
  if (temp == NULL){
    return NULL;
  }
}

void PlayList::deletePlayList()
{
  if(head == NULL){
    return;
  }

  while(head != NULL){
    //cout << "deleting: " << head->name << endl;
    deleteSong(head->name);
  }
  cout << "Deleted Playlist" << endl;

  return;
}

void PlayList::printPath()
{
  if(head == NULL){
    cout << "nothing in playlist" << endl;
  }
  else{
    Song* temp = head;
    while(temp != NULL){
      cout << temp->name << " -> ";
      temp = temp->next;
    }
    cout << "NULL" << endl;
  }

  cout << "===" << endl;

  return;
}

Song* splitAtHalf(Song* first) {
  Song* fast = first;
  while (fast->next->next != NULL) {
    fast = fast->next->next;
    first = first->next;
  }
  /* Split the list at this point. */
  Song* result = first->next;
  first->next = NULL;
  return result;
}

Song* recInterleave(Song* first, Song* second, Song** tail) {
  if (second == NULL) return NULL;
  if (*tail == NULL) {
    *tail = second;
  } else {
    (*tail)->next = second;
    *tail = second;
  }

  second->next = recInterleave(second->next, first, tail);
  return second;
}

void interleave(Song* first, Song* second) {
  Song* tail = NULL;
  recInterleave(first, second, &tail);
}

void shuffleList(Song** head) {
  if (* head == NULL) return;

  Song* half = splitAtHalf(*head);
  interleave(*head, half);
  *head = half;
}

void PlayList::randomizeList(){
  //Shuffle Function taken from: https://web.stanford.edu/class/cs9/sample_probs/ListShuffling.pdf
  shuffleList(&head);
}
