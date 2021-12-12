# NiCMidi RtMidi
 Keep NiCMidi clean. Adapt only low-level RtMidi class
 
 


 A number of very basic examples from the NiCMidi lib

 **DEMONSTRATORS FOR NicMidi MIDI OUT**

 The manager_main example is probably the simplest example for testing newly implemented output drivers
 The test_component example has been shown to play single notes in another implementation of the nimBLE output driver

 Both examples (as implemented here) lead to a compilation error. See comments in main.cpp.  What is missing?

 **DEMONSTRATORS FOR NicMidi MIDI IN**

 The thru or metronome examples are probably the the most suited for this goal: 

       ~~TO BE IMPLEMENTED~~ 


 **DEMONSTRATORS (from the RtMidi docs) OF DIRECT CALLS TO RtMidi** (https://www.music.mcgill.ca/~gary/rtmidi/)  

       ~~TO BE IMPLEMENTED~~   
       
 - nameless example default object construction and destruction:  
 - midiprobe.cpp    probing of ports    
 - midiout.cpp        
 - qumidiin.cpp     input via queue via polling  
 - cmidiin.cpp      input via callback called when complete message received   


