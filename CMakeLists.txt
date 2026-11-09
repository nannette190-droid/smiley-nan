cmake_minimum_required(VERSION 3.22)
project(SoundheadDevelopment VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(JUCE
  GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
  GIT_TAG 8.0.10
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(JUCE)

set(FORMATS VST3)
if(APPLE)
  list(APPEND FORMATS AU)
endif()

juce_add_plugin(SoundheadGain
  COMPANY_NAME "Soundhead Development"
  BUNDLE_ID "com.soundheaddevelopment.gain"
  PLUGIN_MANUFACTURER_CODE ShDv
  PLUGIN_CODE ShGn
  FORMATS ${FORMATS}
  PRODUCT_NAME "Soundhead Gain"
  IS_SYNTH FALSE
  NEEDS_MIDI_INPUT FALSE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  COPY_PLUGIN_AFTER_BUILD FALSE
)
target_sources(SoundheadGain PRIVATE
  src/PluginProcessor.cpp
  src/PluginProcessor.h
)
target_compile_features(SoundheadGain PRIVATE cxx_std_17)
target_compile_definitions(SoundheadGain PUBLIC
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
)
target_link_libraries(SoundheadGain PRIVATE
  juce::juce_audio_utils
  juce::juce_dsp
  juce::juce_recommended_config_flags
  juce::juce_recommended_warning_flags
)

enable_testing()
add_test(NAME source_sanity
  COMMAND ${CMAKE_COMMAND} -DPROJECT_ROOT=${CMAKE_SOURCE_DIR} -P ${CMAKE_SOURCE_DIR}/tests/source_sanity.cmake)
