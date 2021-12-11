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

//SELECT NiCMidi examples here:
#define MSG_MAIN                          //RESULT:
//#define MANAGER_EXAMPLE                 //RUNTIME ERROR: 0x400d63bd: MIDIManager::GetOutDriver(unsigned int) at c:\users\fred\esp_projects\nicmidi-rtmidi\nicmidi_rtmidi\nicmidi_rtmidi_v0\build/../components/NiCMidi/src/manager.cpp:119
//#define TEST_COMPONENT                  //RUNTIME ERROR: 0x400d63bd: MIDIManager::GetOutDriver(unsigned int) at c:\users\fred\esp_projects\nicmidi-rtmidi\nicmidi_rtmidi\nicmidi_rtmidi_v0\build/../components/NiCMidi/src/manager.cpp:119

//#ifdef TEST_THRU                        //NOT YET IMPLEMENTED
//#ifdef TEST_METRONOME                   //NOT YET IMPLEMENTED

//SELECT RtMidi examples here:
#define BASIC_MAIN                        //RESULT:
#define PROBING_PORTS                     //RESULT:
#define MIDI_OUTPUT_MAIN                  //RESULT:
//#define QUEUED_MIDI_INPUT_MAIN          //COMPILATION ERROR: main.cpp:450: undefined reference to `signal'
#define MIDI_INPUT_USER_CALLBACK_MAIN     //RESULT:


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
    //THE STRUGGLE WITH CMakeLists paths....
    //#include "msg.h"
    //#include "../include/msg.h"
    
    #include "../components/NiCMidi/include/msg.h" //OK
        #include "../components/NiCMidi/rtmidi-4.0.0/RtMidi.h" //OK
    #include <iostream> // for std::cout << msg1.MsgToText()
    #include "../components/NiCMidi/include/manager.h" //OK  
    // #include "msg.h"
    //#include "include/msg.h"  //OK
    //#include "msg.h"  //OK
   
extern "C" {           //FCKX
    void app_main(void);
} 


/*************************************************************************************************************************************************
* Examples taken from: https://ncassetta.github.io/NiCMidi/docs/html/_m_e_s_s__t_r_a_c_k__m_u_l_t_i.html and the NiCMidi repo examples
**************************************************************************************************************************************************/


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



/*************************************************************************************************************************************************
* Examples taken from the RtMidi tutorial : https://www.music.mcgill.ca/~gary/rtmidi/
**************************************************************************************************************************************************/

#ifdef BASIC_MAIN
// The following code example demonstrates default object construction and destruction:
//#include "RtMidi.h"
int basic_main() {
  try {
    RtMidiIn midiin;
  } catch (RtMidiError &error) {
    // Handle the exception here
    error.printMessage();
  }
  return 0;
}
#endif

#ifdef PROBING_PORTS
//Probing Ports / Devices
//A client generally must query the available MIDI ports before deciding which to use. The following example outlines how this can be done.

// midiprobe.cpp
//#include <iostream>
#include <cstdlib>
//#include "RtMidi.h"
int probing_ports_main()
{
  RtMidiIn  *midiin = 0;
  RtMidiOut *midiout = 0;
  // RtMidiIn constructor
  try {
    midiin = new RtMidiIn();
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }
  // Check inputs.
  unsigned int nPorts = midiin->getPortCount();
  std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
  std::string portName;
  for ( unsigned int i=0; i<nPorts; i++ ) {
    try {
      portName = midiin->getPortName(i);
    }
    catch ( RtMidiError &error ) {
      error.printMessage();
      goto cleanup;
    }
    std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
  }
  // RtMidiOut constructor
  try {
    midiout = new RtMidiOut();
  }
  catch ( RtMidiError &error ) {
    error.printMessage();
    exit( EXIT_FAILURE );
  }
  // Check outputs.
  nPorts = midiout->getPortCount();
  std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
  for ( unsigned int i=0; i<nPorts; i++ ) {
    try {
      portName = midiout->getPortName(i);
    }
    catch (RtMidiError &error) {
      error.printMessage();
      goto cleanup;
    }
    std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
  }
  std::cout << '\n';
  // Clean up
 cleanup:
  delete midiin;
  delete midiout;
  return 0;
}

#endif

#ifdef MIDI_OUTPUT_MAIN
/*
MIDI Output
The RtMidiOut class provides simple functionality to immediately send messages over a MIDI connection. No timing functionality is provided. Note that there is an overloaded RtMidiOut::sendMessage() function that does not use std::vectors.

In the following example, we omit necessary error checking and details regarding OS-dependent sleep functions. For a complete example, see the midiout.cpp program in the tests directory.
*/

// midiout.cpp
//#include <iostream>
//#include <cstdlib>
//#include "RtMidi.h"
int midi_output_main()
{
  RtMidiOut *midiout = new RtMidiOut();
  std::vector<unsigned char> message;
  // Check available ports.
  unsigned int nPorts = midiout->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No ports available!\n";
    goto cleanup;
  }
  // Open first available port.
  midiout->openPort( 0 );
  // Send out a series of MIDI messages.
  // Program change: 192, 5
  message.push_back( 192 );
  message.push_back( 5 );
  midiout->sendMessage( &message );
  // Control Change: 176, 7, 100 (volume)
  message[0] = 176;
  message[1] = 7;
  message.push_back( 100 );
  midiout->sendMessage( &message );
  // Note On: 144, 64, 90
  message[0] = 144;
  message[1] = 64;
  message[2] = 90;
  midiout->sendMessage( &message );
  //SLEEP( 500 ); // Platform-dependent ... see example in tests directory.
  vTaskDelay(10 / portTICK_PERIOD_MS);
  // Note Off: 128, 64, 40
  message[0] = 128;
  message[1] = 64;
  message[2] = 40;
  midiout->sendMessage( &message );
  // Clean up
 cleanup:
  delete midiout;
  return 0;
}
#endif 

#ifdef QUEUED_MIDI_INPUT_MAIN
/*
MIDI Input
The RtMidiIn class uses an internal callback function or thread to receive incoming MIDI messages from a port or device. These messages are then either queued and read by the user via calls to the RtMidiIn::getMessage() function or immediately passed to a user-specified callback function (which must be "registered" using the RtMidiIn::setCallback() function). Note that if you have multiple instances of RtMidiIn, each may have its own thread. We'll provide examples of both usages.

The RtMidiIn class provides the RtMidiIn::ignoreTypes() function to specify that certain MIDI message types be ignored. By default, system exclusive, timing, and active sensing messages are ignored.

Queued MIDI Input
The RtMidiIn::getMessage() function does not block. If a MIDI message is available in the queue, it is copied to the user-provided std::vector<unsigned char> container. When no MIDI message is available, the function returns an empty container. The default maximum MIDI queue size is 1024 messages. This value may be modified with the RtMidiIn::setQueueSizeLimit() function. If the maximum queue size limit is reached, subsequent incoming MIDI messages are discarded until the queue size is reduced.

In the following example, we omit some necessary error checking and details regarding OS-dependent sleep functions. For a more complete example, see the qmidiin.cpp program in the tests directory.
*/

// qmidiin.cpp
//#include <iostream>
//#include <cstdlib>
#include <signal.h>
//#include "RtMidi.h"
bool done;
static void finish(int ignore){ done = true; }
int queued_midi_input_main()
{
  RtMidiIn *midiin = new RtMidiIn();
  std::vector<unsigned char> message;
  int nBytes, i;
  double stamp;
  // Check available ports.
  unsigned int nPorts = midiin->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No ports available!\n";
    goto cleanup;
  }
  midiin->openPort( 0 );
  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );
  // Install an interrupt handler function.
  done = false;
  (void) signal(SIGINT, finish);
  // Periodically check input queue.
  std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";
  while ( !done ) {
    stamp = midiin->getMessage( &message );
    nBytes = message.size();
    for ( i=0; i<nBytes; i++ )
      std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
    if ( nBytes > 0 )
      std::cout << "stamp = " << stamp << std::endl;
    // Sleep for 10 milliseconds ... platform-dependent.
    //SLEEP( 10 );
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
  // Clean up
 cleanup:
  delete midiin;
  return 0;
}

#endif


#ifdef MIDI_INPUT_USER_CALLBACK_MAIN

/*
MIDI Input with User Callback
When set, a user-provided callback function will be invoked after the input of a complete MIDI message. It is possible to provide a pointer to user data that can be accessed in the callback function (not shown here). It is necessary to set the callback function immediately after opening the port to avoid having incoming messages written to the queue (which is not emptied when a callback function is set). If you are worried about this happening, you can check the queue using the RtMidi::getMessage() function to verify it is empty (after the callback function is set).

In the following example, we omit some necessary error checking. For a more complete example, see the cmidiin.cpp program in the tests directory.
*/
// cmidiin.cpp
//#include <iostream>
//#include <cstdlib>
//#include "RtMidi.h"
void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
  unsigned int nBytes = message->size();
  for ( unsigned int i=0; i<nBytes; i++ )
    std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
  if ( nBytes > 0 )
    std::cout << "stamp = " << deltatime << std::endl;
}
int midi_input_user_callback_main()
{
  RtMidiIn *midiin = new RtMidiIn();
  // Check available ports.
  unsigned int nPorts = midiin->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No ports available!\n";
    goto cleanup;
  }
  midiin->openPort( 0 );
  // Set our callback function.  This should be done immediately after
  // opening the port to avoid having incoming messages written to the
  // queue.
  midiin->setCallback( &mycallback );
  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );
  std::cout << "\nReading MIDI input ... press <enter> to quit.\n";
  char input;
  std::cin.get(input);
  // Clean up
 cleanup:
  delete midiin;
  return 0;
}

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


    #ifdef BASIC_MAIN
    result = basic_main();
    ESP_LOGI(TAG,"RtMidi basic_main result %d",result);
    #endif


    #ifdef PROBING_PORTS
    result = probing_ports_main();
    ESP_LOGI(TAG,"RtMidi probing_ports result %d",result);
    #endif
    
    #ifdef MIDI_OUTPUT_MAIN
    result = midi_output_main();
    ESP_LOGI(TAG,"RtMidi midi_output_main result %d",result);
    #endif
    
    #ifdef QUEUED_MIDI_INPUT_MAIN
    result = queued_midi_input_main();
    ESP_LOGI(TAG,"RtMidi queued_midi_input_main result %d",result);    
    #endif
    
    #ifdef MIDI_INPUT_USER_CALLBACK_MAIN
    result = midi_input_user_callback_main();
    ESP_LOGI(TAG,"RtMidi midi_input_user_callback_main %d",result);    
    #endif
    
    

    ESP_LOGI(TAG,"reached end of code");

}; //app_main;    