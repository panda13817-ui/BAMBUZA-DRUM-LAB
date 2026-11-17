cmake_minimum_required(VERSION 3.22)

project(BambuzaDrumLab VERSION 0.1.0 LANGUAGES C CXX)

# Build configuration for the initial JUCE plugin foundation.
# JUCE is intentionally not vendored yet. Configure JUCE_DIR to a locally
# installed JUCE source/build tree, or add a pinned submodule in a later commit.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BAMBUZA_FETCH_JUCE "Fetch JUCE from the official repository" OFF)
set(JUCE_DIR "" CACHE PATH "Path to a JUCE checkout or installation")

if(BAMBUZA_FETCH_JUCE)
    include(FetchContent)
    FetchContent_Declare(
        JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG 8.0.10
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(JUCE)
elseif(JUCE_DIR)
    add_subdirectory("${JUCE_DIR}" "${CMAKE_BINARY_DIR}/JUCE")
else()
    message(FATAL_ERROR
        "JUCE not configured. Set -DJUCE_DIR=/path/to/JUCE or "
        "-DBAMBUZA_FETCH_JUCE=ON. Review JUCE licensing before commercial distribution.")
endif()

if(APPLE)
    set(BAMBUZA_PLUGIN_FORMATS VST3 AU Standalone)
else()
    set(BAMBUZA_PLUGIN_FORMATS VST3 Standalone)
endif()

juce_add_plugin(BambuzaDrumLab
    COMPANY_NAME "Bambuza Components"
    BUNDLE_ID "com.bambuza.components.drumlab"
    PLUGIN_MANUFACTURER_CODE Bmbz
    PLUGIN_CODE BdL1
    FORMATS ${BAMBUZA_PLUGIN_FORMATS}
    PRODUCT_NAME "Bambuza Drum Lab"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    COPY_PLUGIN_AFTER_BUILD FALSE
    VST3_CAN_REPLACE_VST2 FALSE
)

# Generate JuceHeader.h for the plugin source files.
juce_generate_juce_header(BambuzaDrumLab)

target_sources(BambuzaDrumLab
    PRIVATE
        Source/Plugin/PluginProcessor.cpp
        Source/Plugin/PluginProcessor.h
        Source/Plugin/PluginEditor.cpp
        Source/Plugin/PluginEditor.h
)

target_compile_definitions(BambuzaDrumLab
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(BambuzaDrumLab
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

if(WIN32)
    target_compile_definitions(BambuzaDrumLab PRIVATE _USE_MATH_DEFINES)
endif()
