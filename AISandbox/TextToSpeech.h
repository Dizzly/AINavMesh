#pragma once

#include "Singleton.h"
#include "NonCopyable.h"

#include <sapi.h>

#include <string>
class TextToSpeech;
typedef Singleton<TextToSpeech> TheTextToSpeech;
class TextToSpeech:public NonCopyable
{
public:

	~TextToSpeech();
	bool Init();
	void Say(const std::string& words);
	void Say(const char* words);
private:
	TextToSpeech();
	friend TheTextToSpeech;
private:
	ISpVoice* pVoice_;
};