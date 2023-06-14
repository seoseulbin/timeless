#include "Animation.h"
#include "Engine.h"

Animation::Animation() : Animation("assets/data/none.anm") {}

Animation::Animation(const std::filesystem::path &anmFile) : animSequenceIndex(0)
{
	if (anmFile.extension() != ".anm")
	{
		throw std::runtime_error("Bad Filetype.  " + anmFile.generic_string() + " not a sprite info file (.anm)");
	}
	std::ifstream inFile(anmFile);
	if (inFile.is_open() == false)
	{
		throw std::runtime_error("Failed to load " + anmFile.generic_string());
	}

	std::string label;
	while (inFile.eof() == false)
	{
		inFile >> label;
		if (label == "PlayFrame")
		{
			int frame;
			float targetTime;
			inFile >> frame;
			inFile >> targetTime;

			animation.push_back(new PlayFrame(frame, targetTime));
		}
		else if (label == "Loop")
		{
			int loopToFrame;
			inFile >> loopToFrame;
			animation.push_back(new Loop(loopToFrame));
		}
		else if (label == "End")
		{
			animation.push_back(new End());
		}
		else
		{
			Engine::GetLogger().LogError("Unknown command " + label + " in anm file " + anmFile.generic_string());
		}
	}
	ResetAnimation();
}

Animation::~Animation()
{
	for (CommandData *command : animation)
	{
		delete command;
	}
	animation.clear();
}

void Animation::Update(double dt)
{
	currPlayFrameData->Update(dt);
	if (currPlayFrameData->IsFrameDone() == true)
	{
		currPlayFrameData->ResetTime();
		++animSequenceIndex;
		if (animation[animSequenceIndex]->GetType() == Command::PlayFrame)
		{
			currPlayFrameData = static_cast<PlayFrame *>(animation[animSequenceIndex]);
		}
		else if (animation[animSequenceIndex]->GetType() == Command::Loop)
		{
			Loop *loopData = static_cast<Loop *>(animation[animSequenceIndex]);
			animSequenceIndex = loopData->GetLoopToIndex();
			if (animation[animSequenceIndex]->GetType() == Command::PlayFrame)
			{
				currPlayFrameData = static_cast<PlayFrame *>(animation[animSequenceIndex]);
			}
			else
			{
				Engine::GetLogger().LogError("Loop does not go to PlayFrame");
				ResetAnimation();
			}
		}
		else if (animation[animSequenceIndex]->GetType() == Command::End)
		{
			isAnimationDone = true;
			return;
		}
		else
		{
			Engine::GetLogger().LogError("Animation abruptly ends");
		}
	}
}

int Animation::GetDisplayFrame()
{
	return currPlayFrameData->GetFrameNum();
}

void Animation::ResetAnimation()
{
	animSequenceIndex = 0;
	currPlayFrameData = static_cast<PlayFrame *>(animation[animSequenceIndex]);
	isAnimationDone = false;
}

bool Animation::IsAnimationDone()
{
	return isAnimationDone;
}

Animation::PlayFrame::PlayFrame(int frame, double duration) : frame(frame), targetTime(duration), timer(0) {}
void Animation::PlayFrame::Update(double dt) { timer += dt; }
bool Animation::PlayFrame::IsFrameDone() { return timer >= targetTime; }
void Animation::PlayFrame::ResetTime() { timer = 0; }
int Animation::PlayFrame::GetFrameNum() { return frame; }

Animation::Loop::Loop(int loopToIndex) : loopToIndex(loopToIndex) {}
int Animation::Loop::GetLoopToIndex() { return loopToIndex; }
