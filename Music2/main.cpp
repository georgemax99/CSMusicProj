
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <future>
#include "HashTable.hpp"
#include "ArtistTree.hpp"
#include "playlist.hpp"
using namespace std;

void playMusic(Song* song){
  string path1 = "playMusic.py";
  string command = "python ";
  string parameter1 = command+path1+" "+"\""+song->path+"\"";
  system(parameter1.c_str());
}

void edit_PlayList(PlayList* p, HashTable* h){
  int choice = 0;
  //PlayList p;
  while(choice!=4){
    cout << endl << "________PlayList [" << p->p_name << "]________" << endl;
    cout << "(1) Add new song" << endl;
    cout << "(2) Remove a song" << endl;
    cout << "(3) Play your playlist" << endl; //Or change to save to file/etc
    cout << "(4) Exit" << endl;

    cin >> choice;
    if(choice == 1){
      cout << "Enter name of song to add: " << endl;
      string title;
      cin.ignore();
      getline(cin, title);

      Song* song = h->searchSongs(title);
      p->addSong(song);
    }
    else if(choice==2){
      cout << "Enter name of song to delete:" << endl;
      string title;
      cin.ignore();
      getline(cin, title);

      p->deleteSong(title);
    }
    else if(choice==3){
      Song* temp = p->front();
      while(temp!=NULL){
        playMusic(temp);
        temp = temp->next;
      }
    }
  }
}

void menu(){
  cout<<endl;
  cout<<"Welcome to Max, Robert, and Eric's Music Player"<<endl;
  cout<<"The music has been loaded in from your songs folder"<<endl;
  cout<<"(1) Search for song"<<endl;
  cout<<"(2) Shuffle all songs"<<endl;
  cout<<"(3) Search for artist and play all of their songs"<<endl;
  cout<<"(4) Show all songs"<<endl;
  cout<<"(5) View playlists"<<endl;
  cout<<"(6) Exit"<<endl;
}

int main(){
  string path0 = "replaceSpaces.py";
  string path = "createSongCSV.py";
  string command = "python ";
  string parameter = command+path;
  string parameter0 = command+path0;
  int res = system(parameter.c_str());
  system(parameter0.c_str());



  string songsList = "songs.csv";

  ifstream file;

  file.open(songsList);

  HashTable hashTable = HashTable(10);
  ArtistTree artistTree;

  if(file.is_open()){
    string line;
    while(getline(file,line)){
      string element;
      istringstream ss(line);
      int count = 0;
      string path;
      string title;
      string artist;
      string album;

      while(getline(ss, element, ';')){
        if(count == 0){
          path = element;
          if(path[0] == '\"'){
            path.erase(0,1);
          }
        } else if(count == 1) {
          artist = element;
        } else if(count == 2) {
          title = element;
        } else if(count == 3) {
          album = element;
        }
        count++;
      }
      count = 0;
      artistTree.addSong(path, title, artist, album);
      hashTable.addSong(title, artist, album, path);


    }

    vector<PlayList> p_vec; //Declare playlist vector
    string p_list = "Playlists.csv";
    ifstream myfile(p_list);
    if (myfile.is_open()){
      string l;
      int iterator = 0;

      while(getline(myfile,l)){
        stringstream ss;
        string item;
        ss << l;

        getline(ss,item,',');
        if(item == "Playlist:"){
          iterator++;
          getline(ss,item,',');
          PlayList p; p.p_name = item;
          p_vec.push_back(p);
        }
        else{
          Song* song = hashTable.searchSongs(item);
          (p_vec.at(iterator-1)).addSong(song);
        }
      }
    } myfile.close();

    int input = 0;
    while(input != 6){
      menu();
      cin>>input;
      switch(input) {
        case 1: {
          string songname;
          Song* song = nullptr;
          while(song == nullptr){
            cout<<"Enter the name of the song you want to play."<<endl;
            cin.ignore();
            getline(cin, songname);
            song = hashTable.searchSongs(songname);
          }
          playMusic(song);

          break;
        }

        case 2: {
          int numSongs = 0;
          cout<<"Enter a number of songs you want to be shuffled and played"<<endl;
          cin>>numSongs;
          cout<<"Pressed control+c to skip the song"<<endl;
          for(int i = 0 ; i < numSongs; i++){
            Song* song = hashTable.shuffle();
            playMusic(song);
          }
          break;
        }

        case 3: {
          string artistName;
          Artist* artist = nullptr;
          while(artist == nullptr) {
            cout<<"Enter a artist who you want to play music from."<<endl;
            cin.ignore();
            getline(cin,artistName);
            artist = artistTree.searchArtist(artistName);
          }
          for(int i = 0; i < artist->songs.size(); i++){
            playMusic(artist->songs.at(i));
          }
        }

        case 4: {
          hashTable.showAllSongs();
          break;
        }

        case 5: {
          int choice = 0;
          while(choice!=5){
            cout << endl;
            cout << "________PlayLists________" << endl;
            cout << "(1) Add new playlist" << endl;
            cout << "(2) Access playlist" << endl;
            cout << "(3) Delete playlist" << endl;
            cout << "(4) Display playlists" << endl;
            cout << "(5) Exit" << endl; //Writes to csv

            cin >> choice;
            if(choice==1){ //Add playlist to vector and have user edit
              cout << "Enter name of playlist" << endl;
              string name;
              cin.ignore();
              getline(cin,name);

              PlayList p; p.p_name = name;
              p_vec.push_back(p);
              edit_PlayList(&(p_vec.back()),&hashTable);
            }
            else if(choice==2){ //Call edit function
              string name;
              cout << "Enter name of playlist to edit" << endl;
              cin.ignore();
              getline(cin,name);

              int num=-1;
              for(int i=0; i<p_vec.size(); i++){
                if(p_vec.at(i).p_name == name){num = i;}
              }
              if(num==-1){cout<<"Could not find playlist"<<endl;}
              else{edit_PlayList(&(p_vec.at(num)),&hashTable);}
            }
            else if(choice==3){ //Erase data of playlist vector at element
              string name;
              cout << "Enter name of playlist to delete" <<endl;
              cin.ignore();
              getline(cin,name);

              int num=-1;
              for(int i=0; i<p_vec.size(); i++){
                if(p_vec.at(i).p_name == name){num = i;}
              }
              if(num==-1){cout<<"Could not find playlist"<<endl;}
              else{
                p_vec.erase(p_vec.begin()+num);
              }

            }
            else if(choice==4){
              for(int i=0; i<p_vec.size(); i++){
                cout << "==PlayList [" << p_vec.at(i).p_name << "]==" << endl;
                p_vec.at(i).printPath();
              }
            }
            else if(choice==5){ //Read playlists to csv file
              ofstream myfile;
              myfile.open("Playlists.csv");
              for(int i=0; i<p_vec.size(); i++){
                //Read playlist name to file
                myfile << "Playlist:," << p_vec.at(i).p_name << "\n";
                //Read music to file
                Song* temp = p_vec.at(i).front();
                while(temp!= NULL){
                  //cout << temp->name << endl;
                  myfile << temp->name << "\n";
                  temp = temp->next;
                }
              }
              myfile.close();
            }
          }
          break;
        }

        case 6: {
          cout<<"Thank you for using our music player.  GoodBye."<<endl;
          break;
        }
      }
    }
    p_vec.clear(); //Clear data of playlists
  } else {
    cout<<"There was an error loading your music."<<endl;
  }




}
