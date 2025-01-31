#include <vector>
#include <memory>
#include "Render/Texture.h"

class KeyFrame
{
public:
	int TimeCode = 0;
	int Duration = 0;
	std::unique_ptr<Texture> Sprite = NULL;

public:
	KeyFrame(std::string path, int duration);
	KeyFrame(KeyFrame&& frame);
	~KeyFrame();
};

class Animation
{
public:
	int Duration = 0;
	int FramesPerSecond = 0;
	uint32_t CurrentSprite = 0;
	std::unique_ptr<std::vector<KeyFrame>> Frames;
private:
	KeyFrame* m_CurrentFrame = nullptr;
	KeyFrame* m_NextFrame = nullptr;
public:
	Animation(std::vector<KeyFrame>* frames);
	~Animation();

	void MakeStep(int currTime);
};