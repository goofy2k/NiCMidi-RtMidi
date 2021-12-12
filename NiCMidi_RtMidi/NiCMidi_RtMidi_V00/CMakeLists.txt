# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

# set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/system/console/components)

# set(EXTRA_COMPONENT_DIRS C:/Users/Fred/esp_projects/NiCMidi-RtMidi/NiCMidi_RtMidi/NiCMidi_RtMidi_V0/components/NiCMidi/rtmidi-4.0.0 )

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
set(SUPPORTED_TARGETS esp32)
project(fckx_sequencer)
