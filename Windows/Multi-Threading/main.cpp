///\/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///\/There will be 3 threads running in parallel.
///\/The main thread will call inputThread and stepthread.
///\/The main thread will then enter a loop and asychronously (I may have to make this sync. not sure yet)
///\/take what is in the step thread and output it.
///\/The stepThread takes the data from the inputThread and
///\/works on this data and modifies it. Whether or not this is async. I have not yet determined.
///\/The purpose of this project is to learn more about threads, synchonicity and locks. (maybe futures and atomics too).
///\/Copyright© September 24, 2013
///\/Do not use without the expressed writen consent of the **Insert Team Name** Team
///\/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Includes
#include <iostream>//std::cout, std::endl
#include <thread>//std::thread
#include <mutex>//std::mutex
#include <exception>//exit, std::exception
#include <future>//std::promise, std::future
#include <functional>//std::ref
//I will not use namespaces, I do not preffer to use namespaces.
//End Includes


//Globals
std::mutex iLock,jLock;
int i;
//End Globals


//Function Prototypes
void inputLoop(std::future<int> localFuture);
void stepLoop();
//End Function Prototypes


//Function Definitions
void inputLoop(std::future<int> localFuture){
    //int dealy = 10;
    int test = localFuture.get();
    bool alive = true;

    while(alive){

        if(test > 0){
            alive = false;
            break;
        }

        try{
            throw try_lock(iLock,jLock);
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
               break;
            case 0://iLock failed

               break;
            case 1://jLock failed

                break;
            default:
                break;
            }
        }
    }
}

void stepLoop(){
    //int delay = 10;
    bool alive = true;
    while(alive){

        try{
            throw try_lock(iLock,jLock);
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
               break;
            case 0://iLock failed

               break;
            case 1://jLock fialed

                break;
            default:
                break;
            }
        }
    }
}
//End Function Definitions


///\/********Main************//////////
///\/Pass an int to the program to set i to something other than 1
///\/Pass a string has not yet been handled but I would like it to do something like set debug mode or God mode etc.
///\/********Main************/////////
int main(int argC, char *argV[]){

    //i=0;
    i = argC;

    std::promise<int> iPromise;//create promise
    std::future<int> iFuture = iPromise.get_future();//create future and attach promise to future

    iPromise.set_value(0);

    std::thread inputThread(inputLoop, std::ref(iFuture));
    std::thread stepThread(stepLoop);

    bool alive = true;
    while(alive){//wait till 100 then end program
        try{
           throw try_lock(iLock,jLock);
        }catch (int x){
            switch (x){
            case -1:
               if(i > 999){
                    std::cout << "Don't worry it's actually counting ----------------" << std::endl;
                    iLock.unlock();
                    jLock.unlock();
                    alive = false;
                    break;//breaks switch not while
               }
               if(i > 950){
                    iPromise.set_value(10);
                    iLock.unlock();
                    jLock.unlock();
                    break;//breaks switch not while
               }
               iLock.unlock();
               jLock.unlock();
               break;
            case 0://iLock failed

               break;
            case 1://jLock failed

                break;
            default:
                break;
            }
        }
    }

    try{/////////////////////////////////////////sync and close theads
        throw inputThread.joinable();
    }catch (bool x){
        std::cout << "inputThread.joinable returned" << x << std::endl;
        if(x){
            std::cout << "Joining to Exit Thread" << std::endl;
            inputThread.join();
        }else{
            exit(1000);
        }
    }

    try{/////////////////////////////////////////sync and close threads
        throw stepThread.joinable();
    }catch (bool x){
        std::cout << "stepThread.joinable returned" << x << std::endl;
        if(x){
            std::cout << "Joining to Exit Thread" << std::endl;
            stepThread.join();
        }else{
            exit(1000);
        }
    }

    //End of Program
    return 0;
    //End of Program
}
