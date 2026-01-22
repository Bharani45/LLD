#include <bits/stdc++.h>
using namespace std;
class MusicPlayer;
class State{
    public:
        virtual void playmusic(MusicPlayer* ptr)=0;
        virtual void stopmusic(MusicPlayer* ptr)=0;
        virtual void pausemusic(MusicPlayer* ptr)=0;
};

class MusicPlayer{
public:
    State* cur;

    void setstate(State* ptr){
        cur = ptr;
    }

    void play(){
        cur->playmusic(this);
    }

    void pause(){
        cur->pausemusic(this);
    }

    void stop(){
        cur->stopmusic(this);
    }
};

class Play:public State{
    public:
        void playmusic(MusicPlayer* ptr){
            cout<<"Already Playing"<<endl;
        }
        void pausemusic(MusicPlayer* ptr) override;
        void stopmusic(MusicPlayer* ptr)override;
};
class Pause:public State{
    public:
        void playmusic(MusicPlayer* ptr) override{
            cout<<"Resuming Music"<<endl;
            ptr->setstate(new Play);
        }
        void pausemusic(MusicPlayer* ptr)override{
            cout<<"Already Paused"<<endl;
        } 
        void stopmusic(MusicPlayer* ptr)override;
};

class Stop:public State{
    public:
        void playmusic(MusicPlayer* ptr) override{
            cout<<"Playing Music"<<endl;
            ptr->setstate(new Play);
        }
        void pausemusic(MusicPlayer* ptr) override{
            cout<<"Stopping Music"<<endl;
            ptr->setstate(new Pause);
        }
        void stopmusic(MusicPlayer* ptr) override{
            cout<<"Music already stopped"<<endl;
        }
};
void Play::pausemusic(MusicPlayer* ptr){
    cout<<"Pausing music"<<endl;
    ptr->setstate(new Pause);
}

void Play::stopmusic(MusicPlayer* ptr){
    cout<<"Stopping Music"<<endl;
    ptr->setstate(new Stop);
}
void Pause::stopmusic(MusicPlayer* ptr){
    cout<<"Stopping Music"<<endl;
    ptr->setstate(new Stop);
}

int main(){
    MusicPlayer* ptr=new MusicPlayer;
    ptr->setstate(new Stop);
    ptr->play();
    ptr->play();
    ptr->stop();
    ptr->play();
    ptr->pause();
    return 0;
}