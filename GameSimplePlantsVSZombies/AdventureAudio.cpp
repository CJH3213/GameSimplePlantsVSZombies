#include "AdventureAudio.h"
#include "AudioSource.h"

void AdventureAudio::Instantiate()
{
	mName = "AdventureAudio";

	// ÃÌº”±≥æ∞“Ù¿÷
	AudioSource* audio = new AudioSource();
	AddComponent(audio);

}
