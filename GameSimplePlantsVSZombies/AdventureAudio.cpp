#include "AdventureAudio.h"
#include "AudioSource.h"

void AdventureAudio::Instantiate()
{
	mName = "AdventureAudio";

	// ��ӱ�������
	AudioSource* audio = new AudioSource();
	AddComponent(audio);

}
