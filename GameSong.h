#ifndef GAMESONG_H_INCLUDED
#define GAMESONG_H_INCLUDED
#include <SFML/Audio.hpp>
#include <string>
using namespace std;
class GameSong
{
    public:
        GameSong() {
            songs = "sound/mario-circuit.wav";
        }
        GameSong(string songInput)
        {
            this -> songs = songInput; //declares song as songInput
        }
        string getSongs()const {return songs;}
        void setSongs(string songInput) {this -> songs = songInput;}
    private:
        string songs;

};


#endif // GAMESONG_H_INCLUDED
