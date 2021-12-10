/*************************************************************************************************************************************
*
* A number of very basic examples from the NiCMidi lib
*
* DEMONSTRATORS FOR MIDI OUT
*
* The manager_main example below is probably the simplest example for testing newly implemented output drivers
* The test_component example has been shown to play single notes in another implementation of the nimBLE output driver
*
* Both examples (as implemented here) lead to a compilation error. See below.  What is missing?
*
* DEMONSTRATORS FOR MIDI IN
*
* The thru or metronome examples are probably the the most suited for this goal: 
*
*       **TO BE IMPLEMENTED ** 
*
*
* DEMONSTRATORS OF DIRECT CALLS TO RtMidi from the RtMidi docs (https://www.music.mcgill.ca/~gary/rtmidi/)
*
*       **TO BE IMPLEMENTED ** 
* - nameless example default object construction and destruction:
* - midiprobe.cpp    probing of ports
*  -midiout.cpp      
*  -qumidiin.cpp     input via queue via polling
*  -cmidiin.cpp      input via callback called when complete message received 
*
*  
**************************************************************************************************************************************/


#include "esp_log.h"
    //THE STRUGGLE WITH CMakeLists paths....
    //#include "msg.h"
    //#include "../include/msg.h"
    
    #include "../components/NiCMidi_Rt/include/msg.h" //OK
    #include <iostream> // for std::cout << msg1.MsgToText()
    #include "../components/NiCMidi_Rt/include/manager.h" //OK  
    // #include "msg.h"
    //#include "include/msg.h"  //OK
    //#include "msg.h"  //OK
   
extern "C" {           //FCKX
    void app_main(void);
} 


/*************************************************************************************************************************************************
* example taken from: https://ncassetta.github.io/NiCMidi/docs/html/_m_e_s_s__t_r_a_c_k__m_u_l_t_i.html
**************************************************************************************************************************************************/

//#define MSG_MAIN
#ifdef MSG_MAIN 
int msg_main() {
   MIDIMessage msg1, msg2, msg3;     // creates three empty MIDIMessage objects
   msg1.SetNoteOn(0, 60, 100);       // msg1 becomes a Note On, channel 1, note 60, velocity 100
   msg2.SetVolumeChange(0, 127);     // msg2 becomes a Volume Change (CC 7), channel 1, volume 127
   msg3.SetTimeSig(4, 4);            // msg 3 becomes a system Time Signature, 4/4
   msg1.SetChannel(msg1.GetChannel() + 1);
                                     // increments the msg1 channel by one
   msg2.SetControllerValue(msg2.GetControllerValue() - 10);
                                     // decrements the msg2 volume by 10
   std::cout << msg1.MsgToText();    // prints a description of msg1
   std::cout << msg2.MsgToText();    // prints a description of msg2
   std::cout << msg3.MsgToText();    // prints a description of msg3
   return 0;
}
#endif //MSG_MAIN

//#define MANAGER_EXAMPLE
#ifdef MANAGER_EXAMPLE  //block because of compilation errors
/*************************************************************************************************************************************************
* example taken from: https://ncassetta.github.io/NiCMidi/docs/html/_m_e_s_s__t_r_a_c_k__m_u_l_t_i.html
* After removal of compilation errors in the code (see below), the following compilation remains:
* 
* esp-idf/NiCMidi_Rt/libNiCMidi_Rt.a(driver.cpp.obj): in function `MIDIInDriver::MIDIInDriver(int, unsigned int)':
* c:\users\fred\esp_projects\nicmidi-rtmidi\nicmidi_rtmidi\nicmidi_rtmidi_v0\build/../components/NiCMidi_Rt/src/driver.cpp:250: 
* undefined reference to `RtMidiIn::RtMidiIn(RtMidi::Api, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, unsigned int)'
**************************************************************************************************************************************************/
int manager_main() {
   //MIDIOutDriver* port = MIDIManager::GetOutPort(0);                                       //error: 'GetOutPort' is not a member of 'MIDIManager'
   MIDIOutDriver* port = MIDIManager::GetOutDriver(0);                                          
                                    // gets a pointer to the driver of the 1st hardware out
                                    // port in the system
   port->OpenPort();                // you must open the port before sending MIDI messages
   MIDIMessage msg;
   msg.SetNoteOn(0, 60, 100);       // makes msg1 a Note On message
   //port->OutputMessage(&msg1);    // outputs the message (the note should sound)         //error: 'msg1' was not declared in this scope
   //port->OutputMessage(&msg);     // outputs the message (the note should sound)          //no matching function for call to 'MIDIOutDriver::OutputMessage(MIDIMessage*)'
   port->OutputMessage(msg);        // outputs the message (the note should sound)
   MIDITimer::Wait(2000);           // waits two seconds
   //msg.SetNoteOff(0, 60);         // makes msg the corresponding Note Off                  //error: no matching function for call to 'MIDIMessage::SetNoteOff(int, int)'
   msg.SetNoteOff(0, 60, 0);        // makes msg the corresponding Note Off
   //port->OutputMessage(&msg);     // outputs the message (the note should stop)          //error: no matching function for call to 'MIDIOutDriver::OutputMessage(MIDIMessage*)'
   port->OutputMessage(msg);
   port->ClosePort();               // closes the port
   return 0;
}
#endif

//#define TEST_COMPONENT
#ifdef TEST_COMPONENT
// compilation error: ../components/NiCMidi_Rt/src/driver.cpp:250: undefined reference to 
//`RtMidiIn::RtMidiIn(RtMidi::Api, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, unsigned int)'
// driver.cpp:250    port = new RtMidiIn(RtMidi::RTMIDI_DUMMY);// A non functional MIDI out, which won't throw further exceptions

//same as in manager example above
/*
 *   Example file for NiCMidi - A C++ Class Library for MIDI
 *
 *   Copyright (C) 2021  Nicola Cassetta
 *   https://github.com/ncassetta/NiCMidi
 *
 *   This file is part of NiCMidi.
 *
 *   NiCMidi is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   NiCMidi is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with NiCMidi.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
  Example of a basic custom MIDITickComponent which only plays a note
  every second. The file shows how to redefine the base class methods
  and how to add the component to the MIDIManager queue, making it
  effective.
*/


#include "../include/tick.h"
#include "../include/manager.h"

using namespace std;


// If you want to implement your own MIDITickComponent derived class you must at least redefine
// the StaticTickProc() and TickProc() methods (and probably Start() and Stop() also).
// Before using the class you must add it to the MIDIManager queue with the
// MIDIManager::AddMIDITick().
// This is a very simple example which play a fixed note every second; see the comments
// to every method for details.
//
class TestComp : public MIDITickComponent {
    public:
                                TestComp();
        virtual void            Reset() {}
        virtual void            Start();
        virtual void            Stop();

    protected:
        static void             StaticTickProc(tMsecs sys_time, void* pt);
        virtual void            TickProc(tMsecs sys_time);


        static const tMsecs     NOTE_INTERVAL = 1000;   // the time (in msecs) between two note on
        static const tMsecs     NOTE_LENGTH = 400;      // the time between note on and note off

        tMsecs                  next_note_on;
        tMsecs                  next_note_off;
};


// The constructor must call the base class constructor with the priority and the StaticTickProc
// pointer as parameters.
// In our case, as we have only one object in the MIDIManager queue, the priority is irrelevant.
//
TestComp::TestComp() : MIDITickComponent(PR_PRE_SEQ, StaticTickProc) {}


// The Start() method should initialize the class and then call the base class Start(),
// which loads the sys_time_offset variable with the start time and enables the callback.
//
void TestComp::Start() {
    cout << "Starting the component ... " << endl;
    // opens MIDI out 0 port before playing the notes
    MIDIManager::GetOutDriver(0)->OpenPort();
    next_note_on = 0;                   // relative time of the 1st note on
    next_note_off = NOTE_LENGTH;        // relative time of the 1st note off
    MIDITickComponent::Start();
}


// The Stop() method should first call the base class Stop() which disables the callback.
//
void TestComp::Stop() {
    MIDITickComponent::Stop();
    cout << "Stopping the component ... " << endl;
    MIDIManager::GetOutDriver(0)->ClosePort();
}


// This is the typical implementation of the static callback.
// The MIDIManager gives it two parameters: the now absolute time (sys_time) and the object
// "this" pointer (as void*); the callback only should cast the void pointer to a class
// pointer and then call the (virtual) derived class callback (i.e. TickProc).
//
void TestComp::StaticTickProc(tMsecs sys_time, void* pt) {
    TestComp* c_pt = static_cast<TestComp*>(pt);
    c_pt->TickProc(sys_time);
}


// This is finally the object callback, which does all the work. Its parameter is the absolute
// now time (remember you have the start time in the sys_time_offset variable).
//
void TestComp::TickProc(tMsecs sys_time) {
    MIDITimedMessage msg;
    tMsecs deltat = sys_time - sys_time_offset; // the relative time (now time - start time)

    if (deltat >= next_note_off) {              // we must turn off the note
        msg.SetNoteOff(0, 60, 0);
        MIDIManager::GetOutDriver(0)->OutputMessage(msg);
                                                // sends a note off message to the MIDI 0 port
        cout << "and off" << endl;
        next_note_off += NOTE_INTERVAL;         // updates the next note off time
    }

    if (deltat >= next_note_on) {               // we must turn on the note
        msg.SetNoteOn(0, 60, 127);
        MIDIManager::GetOutDriver(0)->OutputMessage(msg);
                                                // sends a note on message to the MIDI 0 port
        cout << "Note on . . . ";
        next_note_on += NOTE_INTERVAL;          // updates the next note on time
    }
}

// The main() creates a class instance, adds it to the MIDIManager queue and then calls
// Start() and Stop() for enabling and disabling the callback
int component_main() {
    TestComp comp;                              // creates the component
    MIDIManager::AddMIDITick(&comp);            // adds it to the MIDIManager queue
    comp.Start();                               // starts the callback
    cout << "Waiting 10 secs ... " << endl;
    MIDITimer::Wait(10000);                     // waits 10 secs
    comp.Stop();                                // stops the callback
    cout << "Waiting 5 secs without playing ... " << endl;
    MIDITimer::Wait(5000);                      // waits 5 secs
    cout << "Exiting" << endl;
    return EXIT_SUCCESS;
}
#endif

#ifdef TEST_THRU

#endif

#ifdef TEST_METRONOME

#endif   


void app_main(void){
    
    int result;    
    static const char *TAG = "APP_MAIN"; 
    
    #ifdef MANAGER_EXAMPLE
    result = msg_main();
    ESP_LOGI(TAG,"msg_main result %d",result);
    #endif

    #ifdef MANAGER_EXAMPLE
    result = manager_main();
    ESP_LOGI(TAG,"manager_main result %d",result);
    #endif 

    #ifdef TEST_COMPONENT
    result = component_main();
    ESP_LOGI(TAG,"test_component.cpp main() result %d",result);
    #endif

    #ifdef TEST_THRU

    #endif

    #ifdef TEST_METRONOME

    #endif    

    ESP_LOGI(TAG,"reached end of code");

}; //app_main;    