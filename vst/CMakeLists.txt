﻿cmake_minimum_required(VERSION 3.16)
project(DjIaVst VERSION 1.0.0)

add_subdirectory(JUCE)
add_subdirectory(soundtouch)

juce_add_plugin(ObsidianVST
    VERSION "1.0.0"
    PLUGIN_MANUFACTURER_CODE "OBSI"
    PLUGIN_CODE "Obsi"
    COMPANY_NAME "InnerMost47"
    BUNDLE_ID "com.innermost47.obsidian-neural-vst" 
    FORMATS VST3
    PRODUCT_NAME "OBSIDIAN-Neural"
    IS_SYNTH TRUE
    WANTS_MIDI_INPUT TRUE
    PRODUCES_MIDI_OUTPUT TRUE
    IS_MIDI_EFFECT FALSE)

target_sources(ObsidianVST
    PRIVATE
        src/PluginProcessor.cpp
        src/PluginEditor.cpp
        src/BinaryData.cpp  
        src/PluginEntry.cpp
        src/MidiLearnManager.cpp
        src/MixerChannel.cpp
        src/TrackComponent.cpp
        src/MasterChannel.cpp
        src/WaveformDisplay.cpp
        src/SequencerComponent.cpp
        )

target_include_directories(ObsidianVST
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/soundtouch/include)

target_compile_definitions(ObsidianVST
    PRIVATE
        JucePlugin_IsSynth=1
        JucePlugin_WantsMidiInput=1
        JucePlugin_ProducesMidiOutput=1
        JucePlugin_IsMidiEffect=0
        JucePlugin_VSTNumMidiInputs=16
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=1
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0)

target_link_libraries(ObsidianVST 
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_gui_extra
        SoundTouch 
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    set_target_properties(ObsidianVST PROPERTIES
        CXX_CLANG_TIDY "${CLANG_TIDY_EXE};-checks=-*,readability-*,performance-*,bugprone-*,clang-analyzer-*"
    )
endif()