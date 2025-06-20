#pragma once
#include "PluginProcessor.h"
#include "TrackComponent.h"
#include "MixerPanel.h"

class SequencerComponent;

class DjIaVstEditor : public juce::AudioProcessorEditor, public juce::MenuBarModel, public juce::Timer
{
public:
	explicit DjIaVstEditor(DjIaVstProcessor&);
	~DjIaVstEditor() override;

	void paint(juce::Graphics&) override;
	void layoutPromptSection(juce::Rectangle<int> area, int spacing);
	void layoutConfigSection(juce::Rectangle<int> area, int reducing);
	void resized() override;
	void timerCallback() override;
	void refreshTrackComponents();
	void updateUIFromProcessor();
	void refreshTracks();

	void initUI();

	juce::Label statusLabel;

	juce::StringArray getMenuBarNames() override;
	juce::PopupMenu getMenuForIndex(int topLevelMenuIndex, const juce::String& menuName) override;
	void menuItemSelected(int menuItemID, int topLevelMenuIndex) override;

	std::vector<std::unique_ptr<TrackComponent>>& getTrackComponents()
	{
		return trackComponents;
	}
	void onGenerationComplete(const juce::String& selectedTrackId, const juce::String& notification);
	MixerPanel* getMixerPanel() { return mixerPanel.get(); }
	void toggleWaveFormButtonOnTrack();
	void setStatusWithTimeout(const juce::String& message, int timeoutMs = 2000);
	void* getSequencerForTrack(const juce::String& trackId);

private:
	DjIaVstProcessor& audioProcessor;
	juce::Image logoImage;
	juce::Image bannerImage;
	juce::Rectangle<int> bannerArea;
	void setupUI();
	void addEventListeners();
	void onGenerateButtonClicked();
	void loadPromptPresets();
	void onPresetSelected();
	void onSavePreset();
	void updateBpmFromHost();
	void onAutoLoadToggled();
	void onLoadSampleClicked();
	void updateLoadButtonState();
	void updateMidiIndicator(const juce::String& noteInfo);
	void onAddTrack();
	void updateSelectedTrack();
	void onSaveSession();
	void onLoadSession();
	void loadSessionList();
	void saveCurrentSession(const juce::String& sessionName);
	void loadSession(const juce::String& sessionName);
	void updateUIComponents();
	void setAllGenerateButtonsEnabled(bool enabled);
	void showFirstTimeSetup();
	void showConfigDialog();
	void mouseDown(const juce::MouseEvent& event) override;
	void editCustomPromptDialog(const juce::String& selectedPrompt);
	void toggleSEQButtonOnTrack();

	juce::File getSessionsDirectory();
	std::unique_ptr<MixerPanel> mixerPanel;
	juce::TextButton showMixerButton;
	bool mixerVisible = false;

	juce::StringArray promptPresets = {
		"Techno kick rhythm",
		"Hardcore kick pattern",
		"Drum and bass rhythm",
		"Dub kick rhythm",
		"Acidic 303 bassline",
		"Deep rolling bass",
		"Ambient flute psychedelic",
		"Dark atmospheric pad",
		"Industrial noise texture",
		"Glitchy percussion loop",
		"Vintage analog lead",
		"Distorted noise chops" };

	juce::Label pluginNameLabel;
	juce::Label developerLabel;
	juce::Typeface::Ptr customFont;
	juce::ComboBox promptPresetSelector;
	juce::TextButton savePresetButton;
	juce::TextEditor promptInput;
	juce::ComboBox styleSelector;
	juce::Slider bpmSlider;
	juce::Label bpmLabel;
	juce::ComboBox keySelector;
	juce::TextButton generateButton;
	juce::TextButton configButton;
	juce::TextButton resetUIButton;
	juce::Label serverUrlLabel;
	juce::TextEditor serverUrlInput;
	juce::Label apiKeyLabel;
	juce::TextEditor apiKeyInput;
	juce::Label stemsLabel;
	juce::ToggleButton drumsButton;
	juce::ToggleButton bassButton;
	juce::ToggleButton otherButton;
	juce::ToggleButton vocalsButton;
	juce::ToggleButton guitarButton;
	juce::ToggleButton pianoButton;
	juce::TextButton playButton;
	juce::ToggleButton hostBpmButton;
	juce::Slider durationSlider;
	juce::Label durationLabel;
	juce::ToggleButton autoLoadButton;
	juce::TextButton loadSampleButton;
	juce::Label midiIndicator;
	juce::String lastMidiNote;
	juce::TextButton testMidiButton;
	juce::Viewport tracksViewport;
	juce::Component tracksContainer;
	std::vector<std::unique_ptr<TrackComponent>> trackComponents;
	juce::TextButton addTrackButton;
	juce::Label tracksLabel;
	juce::TextButton saveSessionButton;
	juce::TextButton loadSessionButton;
	juce::ComboBox sessionSelector;
	std::unique_ptr<juce::MenuBarComponent> menuBar;

	enum MenuIDs
	{
		newSession = 1,
		saveSession,
		saveSessionAs,
		loadSessionMenu,
		exportSession,
		aboutDjIa = 100,
		showHelp,
		addTrack = 200,
		deleteAllTracks,
		resetTracks
	};

	JUCE_DECLARE_WEAK_REFERENCEABLE(DjIaVstEditor)
};