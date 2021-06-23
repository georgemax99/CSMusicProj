import os, csv

from mp3_tagger import MP3File, VERSION_1, VERSION_2, VERSION_BOTH

# Create MP3File instance.



f=open(os.getcwd()+"/songs.csv",'r+')
w=csv.writer(f)
for path, dirs, files in os.walk(os.getcwd()+"/Songs"):
    for filename in files:
        if filename != '.DS_Store':
            try:
                mp3 = MP3File(os.getcwd()+'/Songs/'+filename)
                mp3.set_version(VERSION_2)
                filename = "".join(filename) + ";"
                artist = "".join(mp3.artist) + ";"
                title = "".join(mp3.song) + ";"
                album = "".join(mp3.album)
                str = filename+artist+title+album
                w.writerow([str])
            except:
                print("")
