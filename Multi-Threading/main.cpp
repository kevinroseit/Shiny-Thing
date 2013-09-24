///\/There will be 3 threads running in parallel.
///\/The main thread will call inputThread and stepthread.
///\/The main thread will then enter a loop and asychronously (I may have to make this sync. not sure yet)
///\/take what is in the step thread and output it.
///\/The stepThread takes the data from the inputThread and
///\/works on this data and modifies it. Whether or not this is async. I have not yet determined.
///\/The purpose of this project is to learn more about threads, synchonicity and locks. (maybe futures and atomics too).

#include <iostream>
#include <thread>
#include <mutex>
//I will not use namespaces, I do not preffer to use namespaces.

std::mutex iLock,jLock;//inputLock,stepLock,drawLock;
bool alive = true;
int i;

void inputLoop();
void stepLoop();

void inputLoop(){
    //int dealy = 10;
    while(1){
        int x = try_lock(iLock,jLock);
        if(x){
            if(i < 97){
                i+=3;
                std::cout << "i = " << i << "    inputLoop+3" << std::endl;
                iLock.unlock();
                jLock.unlock();
            }
        }else{
            //std::cout << "inputLoop failed lock" << std::endl;
        }
    }

}

void stepLoop(){
    //in delay = 10;
    while(1){
        if(try_lock(iLock,jLock)){
            if(i < 99){
                i++;
                std::cout << "i = " << i <<  "    stepLoop+1" << std::endl;
                iLock.unlock();
                jLock.unlock();
            }
        }else{
            //std::cout << "stepLoop failed lock" << std::endl;
        }
    }
}

//int drawLoop(){
    //stuff
//}

int main(int argC, char *argV[]){

    i=0;

    std::thread inputThread(inputLoop);
    std::thread stepThread(stepLoop);
    //std::thread drawThread(drawLoop);

    /*while(1){//keep joining thread even if failed
        if(drawThread.joinable()){
            drawThread.join();
            break;
        }else{
            std::cout << "Did not join thread." << std::endl;
        }
    }*/

    while(alive){//wait till 100 then end program
        if(try_lock(iLock,jLock)){
            if(i > 10){
                alive = false;
                std::cout << "Don't worry it's actually counting ----------------" << std::endl;
            }else{
                iLock.unlock();
                jLock.unlock();
            }
        }
    }

    return 0;
}
