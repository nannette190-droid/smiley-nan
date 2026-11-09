#include "PluginProcessor.h"

SoundheadGainAudioProcessor::SoundheadGainAudioProcessor()
  : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                    .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
    parameters (*this, nullptr, "PARAMETERS",
                { std::make_unique<juce::AudioParameterFloat>(
                    juce::ParameterID { "gain", 1 }, "Gain",
                    juce::NormalisableRange<float> (-60.0f, 12.0f, 0.1f), 0.0f) })
{
}

void SoundheadGainAudioProcessor::prepareToPlay (double, int) {}
void SoundheadGainAudioProcessor::releaseResources() {}

void SoundheadGainAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    const auto db = parameters.getRawParameterValue ("gain")->load();
    const auto linearGain = juce::Decibels::decibelsToGain (db, -60.0f);
    buffer.applyGain (linearGain);
}

juce::AudioProcessorEditor* SoundheadGainAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

void SoundheadGainAudioProcessor::getStateInformation (juce::MemoryBlock& dest)
{
    if (auto state = parameters.copyState().createXml())
        copyXmlToBinary (*state, dest);
}

void SoundheadGainAudioProcessor::setStateInformation (const void* data, int size)
{
    if (auto state = getXmlFromBinary (data, size))
        if (state->hasTagName (parameters.state.getType()))
            parameters.replaceState (juce::ValueTree::fromXml (*state));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SoundheadGainAudioProcessor();
}
