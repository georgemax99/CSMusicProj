import playsound, sys,os

try:
    songName = sys.argv[1]
    path = os.getcwd()+"/Songs/"
    parameter = path+songName
    print(songName)

    playsound.playsound(parameter, True)

except:
    print("")
    print("An error playing the music has occured")
