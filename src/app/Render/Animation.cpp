#include "Animation.h"
#include <iostream>

Animation::Animation(std::vector<KeyFrame>* frames)
{
	Frames.reset(move(frames));
	int NextFrameDuration = 0;
	int j = 0;
	for (auto i = Frames->begin(); i != Frames->end(); i++)
	{
		Frames->at(j).Sprite->Load();
		Frames->at(j).TimeCode = Duration + NextFrameDuration;
		NextFrameDuration = Frames->at(j).Duration;
		Duration += Frames->at(j).Duration;
		j++;
	}
	Frames->at(Frames->size() - 1).Duration = NextFrameDuration;

}

Animation::~Animation()
{

}

void Animation::MakeStep(int currTime)
{
	int currDuration = currTime % Duration;
	std::cout << "Current dur:  " << currDuration << std::endl;
	size_t i = Frames->size()-1;

	for (;i  != -1;i--)
	{
		KeyFrame& frame = Frames->at(i);
		if (currDuration > frame.TimeCode)
		{
			m_CurrentFrame = &frame;
			CurrentSprite = m_CurrentFrame->Sprite->GetTextureId();
			break;
		}
	}
}


KeyFrame::KeyFrame(std::string path, int duration)
	: Duration(duration)
{
	Sprite.reset(new Texture(path));
}

KeyFrame::KeyFrame(KeyFrame&& frame)
{
	Sprite = move(frame.Sprite);
	Duration = frame.Duration;
	TimeCode = frame.TimeCode;
}

KeyFrame::~KeyFrame()
{
}
