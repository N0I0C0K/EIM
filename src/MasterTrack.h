#pragma once

#include "Track.h"
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_utils/juce_audio_utils.h>

class MasterTrack: public SynchronizedAudioProcessorGraph, public juce::AudioPlayHead {
public:
    std::vector<juce::AudioProcessorGraph::Node::Ptr> tracks;
    juce::AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    juce::KnownPluginList knownPluginList;

    using PluginCreationCallback = std::function<void(std::unique_ptr<PluginWrapper>, const std::string&)>;

    MasterTrack();
    ~MasterTrack() { deviceManager.closeAudioDevice(); }

    void scanPlugins();
    void removeTrack(int id);
    juce::AudioProcessorGraph::Node::Ptr createTrack(std::string name, std::string color);
    std::unique_ptr<PluginWrapper> loadPlugin(std::unique_ptr<juce::PluginDescription> desc);
    void loadPluginAsync(std::unique_ptr<juce::PluginDescription> desc, PluginCreationCallback callback);

    virtual bool getCurrentPosition(CurrentPositionInfo& result) override;
    virtual bool canControlTransport() override { return true; }
    virtual void transportPlay(bool shouldStartPlaying) override;
    virtual void transportRecord(bool shouldStartRecording) override { juce::ignoreUnused(shouldStartRecording); }
    virtual void transportRewind() override { }
private:
    double startTime = 0;
    juce::File knownPluginListXMLFile;
    juce::AudioProcessorGraph::NodeID outputNodeID;
    juce::AudioPluginFormatManager manager;
    juce::AudioDeviceManager deviceManager;
    juce::AudioDeviceManager::AudioDeviceSetup setup;
    juce::AudioProcessorPlayer graphPlayer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MasterTrack)
};
