# NiCMidi RtMidi
 Keep NiCMidi clean. Adapt only low-level RtMidi class
 
 


 A number of very basic examples from the NiCMidi lib

 **DEMONSTRATORS FOR NicMidi MIDI OUT**

The manager_main example is probably the simplest example for testing newly implemented output drivers
The test_component example has been shown to play single notes in another implementation of the nimBLE output driver

Both examples (as implemented here) lead to a compilation error. See comments in main.cpp.  What is missing?

 **DEMONSTRATORS FOR NicMidi MIDI IN**

The thru or metronome examples are probably the the most suited for this goal.

- msg_main  
- manager_example  
- test_compontent  

  esp-idf/NiCMidi_Rt/libNiCMidi_Rt.a(driver.cpp.obj): in function `MIDIInDriver::MIDIInDriver(int, unsigned int)':
  c:\users\fred\esp_projects\nicmidi-rtmidi\nicmidi_rtmidi\nicmidi_rtmidi_v0\build/../components/NiCMidi_Rt/src/driver.cpp:250: 
  undefined reference to `RtMidiIn::RtMidiIn(RtMidi::Api, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, unsigned int)'

   


 **DEMONSTRATORS (from the RtMidi docs) OF DIRECT CALLS TO RtMidi** (https://www.music.mcgill.ca/~gary/rtmidi/)  

Implemented in V00: 

- basic_main (nameless example default object construction and destruction)
- probing_ports   (midiprobe.cpp    probing of ports)
- midi_output_main (midiout.cpp)
- queued_midi_input_main  (qumidiin.cpp     input via queue via polling)
- midi_input_user_callback_main    (cmidiin.cpp      input via callback called when complete message received)
       
   
   
        
  
   


