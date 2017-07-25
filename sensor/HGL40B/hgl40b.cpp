/*
 * The MIT License (MIT)

Copyright (c) 2015 Jetsonhacks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <jetsonGPIO.h>
#include "hgl40b.h"
#include <iostream>

using namespace std;

    struct timeval tval_before,tval_after;
int a = 0;
int timeInput = 1, timeresult = 0;

pthread_mutex_t tval_after_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t tval_result_mutex = PTHREAD_MUTEX_INITIALIZER;

// Set the GPIO pins for the trigger and the echo to the HC-SR04
HGL40B::HGL40B(jetsonGPIO triggerGPIO, jetsonGPIO echoGPIO) {
    HGL40BTrigger = triggerGPIO ;
    HGL40BEcho = echoGPIO ;
    pthread_create(&p_thread_Trigger, NULL, &HGL40B::Triggerthread_function, (void*)&HGL40BTrigger);
    pthread_create(&p_thread_Echo, NULL, &HGL40B::Echothread_function, (void*)&HGL40BEcho);
}

HGL40B::~HGL40B() {
	a = 1;

    pthread_join(p_thread_Trigger, NULL);
    pthread_join(p_thread_Echo, NULL);
}

// Make GPIO available in user space
void HGL40B::exportGPIO ( void ) {
    gpioExport(HGL40BTrigger) ;
    gpioExport(HGL40BEcho) ;
}

void HGL40B::unexportGPIO ( void ) {
    gpioUnexport(HGL40BTrigger) ;
    gpioUnexport(HGL40BEcho) ;
}

void HGL40B::setDirection ( void ) {
    // Set the pin directions - Trigger is output, Echo is input
    gpioSetDirection(HGL40BTrigger,outputPin) ;
    gpioSetDirection(HGL40BEcho,inputPin) ;
}

// Send the trigger sound from the HC-SR04
bool HGL40B::triggerPing ( void ) {
    unsigned int maxEcho = MAX_SENSOR_DISTANCE*ROUNDTRIP_CM + MAX_SENSOR_DELAY + SONIC_MAKE_DELAY;
    unsigned int echoValue = low ;
	// figure out duration of the pulse
    //struct timeval tval_before, tval_after, tval_result;
    // Set trigger low to get ready to start
    /*
    gpioSetValue(HGL40BTrigger,low) ;
    usleep(4) ;
    // Pull trigger high for 10 microseconds to initiate echo location
    gpioSetValue(HGL40BTrigger,high) ;
    usleep(10) ;
    gpioSetValue(HGL40BTrigger,low) ;
    gettimeofday(&tval_before, NULL);
    */
    //gpioSetValue(HGL40BTrigger,low) ;	//..
    if(timeInput != 0){
        return false;
    }
                //..
    //gpioGetValue(HGL40BEcho,&echoValue) ;
    //if (echoValue) {
      //  return false ;  // Previous echo not finished
    //}
    /*
    while (echoValue != high) {
        gpioGetValue(HGL40BEcho,&echoValue) ;
        gettimeofday(&tval_after, NULL);
        timersub(&tval_after, &tval_before, &tval_result);
        if (tval_result.tv_usec > maxEcho) {
            return false ;
        }
    }*/
    return true ;
}

// Return the duration of an echo from the HC-SR04 in uSecs
// The duration can then be converted to distance
// Divide by 58 for Centimeters
// Divide by 148 for Inches
// A return of 0 is NO_ECHO ; Objects are either too close or too far away to detect
unsigned int HGL40B::ping ( void ) {
    int tval_result_usec  = 0;
    // trigger a ping, then wait for the echo//..
    			 //..
   // pthread_mutex_lock(&tval_after_mutex);

    //unsigned int echoValue = low ;
	//cout<<timeInput<<" trigger\n";

  //  pthread_mutex_unlock(&tval_after_mutex);
    //if (!triggerPing()) {
        // Timed out ; No objects or objects too close to sensor to measure
      //  return NO_ECHO ;
    //}
        //unsigned int maxEcho = MAX_SENSOR_DISTANCE*ROUNDTRIP_CM + MAX_SENSOR_DELAY ;
        //unsigned int echoValue = high ;
        // figure out duration of the pulse
        //struct timeval tval_before, tval_after, tval_result;
        //gettimeofday(&tval_before, NULL);
        /*while (echoValue != low) {
            gpioGetValue(HGL40BEcho,&echoValue) ;
            if (echoValue==low) {
                break;
            }

            gettimeofday(&tval_after, NULL);
            timersub(&tval_after, &tval_before, &tval_result);
            if (tval_result.tv_usec > maxEcho) {
                return NO_ECHO ;
            }
        }
	*/
/*	while (echoValue != high) {
            gpioGetValue(HGL40BEcho,&echoValue) ;
            if (echoValue==high) {
                break;
            }

            gettimeofday(&tval_after, NULL);
            timersub(&tval_after, &tval_before, &tval_result);
            if (tval_result.tv_usec > maxEcho) {
                return NO_ECHO ;
            }
        }
      gettimeofday(&tval_after, NULL);
*/
	//pthread_mutex_lock(&tval_after_mutex);

	//cout<<timeInput<<" result\n";
/*
    gpioGetValue(HGL40BEcho,&echoValue) ;
        //gettimeofday(&tval_before, NULL);
        while (echoValue != high) {
              gpioGetValue(HGL40BEcho,&echoValue) ;

              if (echoValue==high) {
                    break;
             }
        }
        gettimeofday(&tval_after, NULL);
*/
    pthread_mutex_lock(&tval_result_mutex);
    if(timeresult == 1){
        //pthread_mutex_lock(&tval_result_mutex);

        timersub(&tval_after, &tval_before, &tval_result);

        cout<<"result\n";
        timeresult = 0;
        //pthread_mutex_unlock(&tval_result_mutex);
    }
        pthread_mutex_unlock(&tval_result_mutex); 
        tval_result_usec = tval_result.tv_sec*1000000+tval_result.tv_usec - SONIC_MAKE_DELAY;
        if(tval_result_usec >= 0){
            return tval_result_usec;
        }
        else{
            return 0;
        }
        // convert to microseconds
       // second conversion not necessary

}

void * HGL40B::Echothread_function(void *arg){
    jetsonGPIO HGL40BEcho;
    HGL40BEcho = *(jetsonGPIO *)arg;
    timeval tval_result, tval_after_echo;
    bool ismaxEchoOver = false;
    unsigned int echoValue = low ;
    unsigned int maxEcho = MAX_SENSOR_DISTANCE*ROUNDTRIP_CM + MAX_SENSOR_DELAY + SONIC_MAKE_DELAY;
while(a != 1){
	//cout<<timeInput<<" Echo\n";
    if(timeInput == 0){
    gpioGetValue(HGL40BEcho,&echoValue) ;


    	//gettimeofday(&tval_before, NULL);
    	while (echoValue != high) {
                ismaxEchoOver = false;
              gpioGetValue(HGL40BEcho,&echoValue) ;
	
          	  if (echoValue==high) {
        	        break;
           	 }
              gettimeofday(&tval_after_echo, NULL);
              timersub(&tval_after_echo, &tval_before, &tval_result);
              if (tval_result.tv_sec*1000000+tval_result.tv_usec > maxEcho) {
                    ismaxEchoOver = true;
                    cout<<"afterFalse1 "<<tval_result.tv_sec*1000000+tval_result.tv_usec<< "\n";
                    break;
              }
        }
        if(!ismaxEchoOver){
            cout<<"after\n";
        gettimeofday(&tval_after, NULL);
        timersub(&tval_after, &tval_before, &tval_result);
        //if (tval_result.tv_usec <= maxEcho) {
            pthread_mutex_lock(&tval_result_mutex);
            timeresult = 1;
             pthread_mutex_unlock(&tval_result_mutex);
        //}
        }

        pthread_mutex_lock(&tval_after_mutex);
        timeInput = 1;
        pthread_mutex_unlock(&tval_after_mutex);
        usleep(49000 - tval_result.tv_usec );

    }
    echoValue = low;

}
}

void * HGL40B::Triggerthread_function(void *arg){
    jetsonGPIO HGL40BTrigger;
    HGL40BTrigger = *(jetsonGPIO *)arg;
while(a != 1){
    if(timeInput == 1){
    //cout<<timeInput<<" Echo\n";

/*
    gpioSetValue(HGL40BTrigger,low) ;
    usleep(12.5) ;
    gpioSetValue(HGL40BTrigger,high) ;
    usleep(12.5) ;
    gpioSetValue(HGL40BTrigger,low) ;
*/
pthread_mutex_lock(&tval_after_mutex);

gettimeofday(&tval_before, NULL);
            cout<<"before\n";
    timeInput = 0;
    pthread_mutex_unlock(&tval_after_mutex);
    for(int i=0; i<40; i++){
        usleep(12.5) ;
        gpioSetValue(HGL40BTrigger,high) ;
        usleep(12.5) ;
        gpioSetValue(HGL40BTrigger,low) ;
    }
    }
    usleep(49000);

}
}

unsigned int HGL40B::calculateMedian (int count, unsigned int sampleArray[]) {
    unsigned int tempValue ;
    int i,j ;   // loop counters
    for (i=0 ; i < count-1; i++) {
        for (j=0; j<count; j++) {
            if (sampleArray[j] < sampleArray[i]) {
                // swap elements
                tempValue = sampleArray[i] ;
                sampleArray[i] = sampleArray[j] ;
                sampleArray[j] = tempValue ;
            }
        }
    }

    if (count%2==0) {
        // if there are an even number of elements, return mean of the two elements in the middle
        return ((sampleArray[count/2] + sampleArray[count/2-1]) / 2.0) ;
    } else {
        // return the element in the middle
        return (sampleArray[count/2]) ;
    }
    //return sampleArray[0];
}

// Return the median duration of a number of pings
unsigned int HGL40B::pingMedian (int iterations) {
    unsigned int pings[iterations] ;
    unsigned int lastPing ;
    int index = 0 ;
    int samples = iterations ;
    int cursor = 0 ;
    pings[0] = NO_ECHO ;
    while (index < iterations) {
        lastPing = ping() ;
        if (lastPing != NO_ECHO) {
             //Add this to the samples array
            pings[cursor] = lastPing ;
            cursor ++ ;
        } else {
             //Nothing detected, don't add to samples.
            samples -- ;
        }
        index ++ ;
        usleep(1000) ; // delay a millisecond between pings
    }
    // Figure out the median of the samples
    if (samples == 0) return NO_ECHO ;
    return calculateMedian(samples,pings) ;
    //return lastPing;
}
