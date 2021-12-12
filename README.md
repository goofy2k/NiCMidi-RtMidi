# NiCMidi RtMidi
Keep NiCMidi clean. Adapt only low-level RtMidi class
 
 

## Basic demonstrators / tests

A number of very basic examples from the NiCMidi lib

### NiCMidi DEMONSTRATORS (MIDI OUT and IN)

The manager_main example is probably the simplest example for testing newly implemented output drivers
The test_component example has been shown to play single notes in another implementation of the nimBLE output driver

Both examples (as implemented here) lead to a compilation error. See comments in main.cpp.  What is missing?

The thru or metronome examples are probably the the most suited for this goal.

Implemented in V00: 

- msg_main         running OK
- manager_example  compilation error, see below
- test_component   compilation error, see below

    esp-idf/NiCMidi_Rt/libNiCMidi_Rt.a(driver.cpp.obj): in function `MIDIInDriver::MIDIInDriver(int, unsigned int)':
    c:\users\fred\esp_projects\nicmidi-rtmidi\nicmidi_rtmidi\nicmidi_rtmidi_v0\build/../components/NiCMidi_Rt/src/driver.cpp:250: 
    undefined reference to `RtMidiIn::RtMidiIn(RtMidi::Api, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, unsigned int)'
 
These compilation errors should be solved before the underlying calls to RtMidi can succesfully tested

To be implemented:

- test_thru
- test_metronome  

 ### RtMidi DEMONSTRATORS (from the RtMidi docs)** (https://www.music.mcgill.ca/~gary/rtmidi/)  

These examples demostrate direct calls to RtMidi. 
 
Implemented in V00: 

- basic_main                       (nameless example default object construction and destruction)  OK
- probing_ports                    (midiprobe.cpp    probing of ports)                             OK, but does not find ports
- midi_output_main                 (midiout.cpp)                                                   OK, but does not find ports
- queued_midi_input_main           (qumidiin.cpp     input via queue via polling)   Compilation error: the signal lib cannot be used under esp-idf. An alternative test must be found.
- midi_input_user_callback_main    (cmidiin.cpp      input via callback called when complete message received)
 
 All well compiling RtMidi examples report: 'MidiInDummy: This class provides no functionality.'
 
 ### Next steps
 
 - #### Implement drivers in RtMidi for nimBLE output and MQTT input. 
 
 To this end the RtMidi.cpp/.h files will be adapted.  
       
  - #### Run / debug the NicMidi examples using the new RtMidi   
   
        
  
   


