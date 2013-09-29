///\/There will be 3 threads running in parallel.
///\/The main thread will call inputThread and stepthread.
///\/The main thread will then enter a loop and asychronously (I may have to make this sync. not sure yet)
///\/take what is in the step thread and output it.
///\/The stepThread takes the data from the inputThread and
///\/works on this data and modifies it. Whether or not this is async. I have not yet determined.
///\/The purpose of this project is to learn more about threads, synchonicity and locks. (maybe futures and atomics too).
///\/Copyright© September 24, 2013
///\/Do not use without the expressed writen consent of the **Insert Team Name** Team
#include <iostream>
#include <thread>
#include <mutex>
#include <exception>
//I will not use namespaces, I do not preffer to use namespaces.

std::mutex iLock,jLock;
int i;

void inputLoop();
void stepLoop();

void inputLoop(){
    //int dealy = 10;
    bool alive = true;
    while(alive){

        try{
            throw try_lock(iLock,jLock);//CPlusPlus.com recommended using try_lock as such, not sure what the performance difference is if not using variable storage
        }catch (int x){//handle exception
            switch (x){
            case -1:
               if(i < 997){
                    i+=3;
                    std::cout << "i = " << i << "    inputLoop+3" << std::endl;//locks on cout ensure a clean command line prompt, else cout prints all over the place
                    iLock.unlock();//unlock when ever you're done with stuff that can only be safely accessed by things one at a time
                    jLock.unlock();
               }else{
                    alive = false;//end loop and consequently the thread
                    iLock.unlock();
                    jLock.unlock();
               }
            case 0://iLock failed

               break;
            case 1://jLock failed

                break;
            default:
                break;
            }
        }
        /*
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
        */
    }
    //std::terminate();//apparently this terminates the whole program...

}

void stepLoop(){
    //int delay = 10;
    bool alive = true;
    while(alive){

        try{
            throw try_lock(iLock,jLock);//CPlusPlus.com recommended using try_lock as such, not sure what the performance difference is if not using variable storage
        }catch (int x){
            switch (x){
            case -1:
               if(i < 1000){
                    i++;
                    std::cout << "i = " << i <<  "    stepLoop+1" << std::endl;
                    iLock.unlock();
                    jLock.unlock();
               }else{
                    alive = false;
                    iLock.unlock();
                    jLock.unlock();
               }
            case 0://iLock failed

               break;
            case 1://jLock fialed

                break;
            default:
                break;
            }
        }
        /*
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
        }*/
    }
    //std::terminate();//apparently this termiantes the whole program...
}

//int drawLoop(){
    //stuff
//}

int main(int argC, char *argV[]){


    i=0;

    std::thread inputThread(inputLoop);
    std::thread stepThread(stepLoop);
    //std::thread drawThread(drawLoop);

    bool alive = true;
    while(alive){//wait till 100 then end program
        //int x = try_lock(iLock,jLock);//CPlusPlus.com recommended using try_lock as such, not sure what the performance difference is if not using variable storage
        try{
           throw try_lock(iLock,jLock);//CPlusPlus.com recommended using try_lock as such, not sure what the performance difference is if not using variable storage
        }catch (int x){
            switch (x){
            case -1:
               if(i > 999){
                    std::cout << "Don't worry it's actually counting ----------------" << std::endl;
                    iLock.unlock();
                    jLock.unlock();
                    alive = false;
               }else{
                    iLock.unlock();
                    jLock.unlock();
               }
            case 0:

               break;
            case 1:

                break;
            default:
                break;
            }
        }
        /*if(x < 0){
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
            throw 1;
            for(int y = 0; y < 10; y++);//this would try to offset this from the other thread cycle, not sure if it does anything or if it's needed.
        }*/
    }

    try{//sync and close theads
        throw inputThread.joinable();
    }catch (bool x){
        std::cout << "inputThread.joinable returned" << x << std::endl;
        if(x){
            std::cout << "Still alive" << std::endl;
            inputThread.join();
            //std::terminate();// this might be terminating main thread... not the thread I want
            //std::thread ~inputThread;
        }else{
            exit(1000);
        }
    }

    try{//sync and close threads
        throw stepThread.joinable();
    }catch (bool x){
        if(x){
            stepThread.join();
            //std::terminate();// this might be terminating main thread... not the thread I want
            //std::thread ~stepThread;
        }else{
            exit(1000);
        }
    }
    //for(int y = 0; y < 200; y++);//this is here to let all threads catch up and die off, not sure if it's needed or not



    return 0;
}
