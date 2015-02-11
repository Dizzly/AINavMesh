#include "TextToSpeech.h"

TextToSpeech::TextToSpeech()
{
	pVoice_=0;
}

bool TextToSpeech::Init()
{
	if(FAILED(::CoInitialize(NULL)))
	{return false;}

	HRESULT hr = CoCreateInstance(CLSID_SpVoice,NULL,CLSCTX_ALL, IID_ISpVoice,(void **)&pVoice_);
	if(FAILED(hr))
	{return false;}
	return true;
}

void TextToSpeech::Say(const std::string& words)
{
	if(pVoice_)
	{
		wchar_t wtext[1000];
		mbstowcs_s(NULL,wtext,words.data(),words.size());
		pVoice_->Speak(wtext,0,NULL);
	}
}

void TextToSpeech::Say(const char* words)
{
	if(pVoice_)
	{
		wchar_t wtext[1000];
		mbstowcs_s(NULL,wtext,words,strlen(words));
		pVoice_->Speak(wtext,0,NULL);
	}
}

TextToSpeech::~TextToSpeech()
{
	if(pVoice_)pVoice_->Release();
	::CoUninitialize();
}