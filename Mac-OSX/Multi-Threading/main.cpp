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

std::mutex iLock,jLock;
int i;

void inputLoop();
void stepLoop();

void inputLoop(){
    //int dealy = 10;
    bool alive = true;
    while(alive){
        int x = try_lock(iLock,jLock);//try_lock needs at least 2 objects
        if(x < 0){//locked all objects
            if(i < 97){
                i+=3;
                std::cout << "i = " << i << "    inputLoop+3" << std::endl;//locks on cout ensure a clean command line prompt, else cout prints all over the place
                iLock.unlock();//unlock when ever you're done with stuff that can only be safely accessed by things one at a time
                jLock.unlock();
            }else{
                alive = false;//end loop and consequently the thread
                iLock.unlock();
                jLock.unlock();
            }
        }//else{
            //std::cout << "inputLoop failed lock" << std::endl;//obviously causes cout problems...
        //}
    }

}

void stepLoop(){
    //int delay = 10;
    bool alive = true;
    while(alive){
        int x = try_lock(iLock,jLock);
        if(x < 0){
            if(i < 100){
                i++;
                std::cout << "i = " << i <<  "    stepLoop+1" << std::endl;
                iLock.unlock();
                jLock.unlock();
            }else{
                alive = false;
                iLock.unlock();
                jLock.unlock();
            }
        }
    }
}

//int drawLoop(){
    //stuff
//}

int main(int argC, char *argV[]){

    bool alive = true;
    i=0;

    std::thread inputThread(inputLoop);
    std::thread stepThread(stepLoop);
    //std::thread drawThread(drawLoop);

    while(alive){//wait till 100 then end program
        int x = try_lock(iLock,jLock);//CPlusPlus.com recommended using try_lock as such, not sure what the performance difference is if not using variable storage
        if(x < 0){
            if(i > 99){
                std::cout << "Don't worry it's actually counting ----------------" << std::endl;
                iLock.unlock();
                jLock.unlock();
                alive = false;
            }else{
                iLock.unlock();
                jLock.unlock();
            }
        }else{
            for(int y = 0; y < 10; y++);//this would try to offset this from the other thread cycle, not sure if it does anything or if it's needed.
        }
    }

    for(int y = 0; y < 200; y++);//this is here to let all threads catch up and die off, not sure if it's needed or not

    return 0;
}
