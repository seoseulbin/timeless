//
//#include "Score.h"
//#include "../Engine/Fonts.h"
//#include "../Engine/Engine.h"
//
//Score::Score(int startingScore, Fonts fontToUse)
//	:score(startingScore), fontToUse(fontToUse)
//{
//	RenderText();
//}
//
//void Score::AddScore(int newPoints)
//{
//	score += newPoints;
//}
//
//void Score::Draw(DataType::fvec2 location)
//{
//	RenderText();
//	//scoreTexture.Draw(DataType::TranslateMatrix{ DataType::fvec2{location.x,location.y - scoreTexture.GetSize().y - 5.f } },false);
//	scoreTexture.Draw(DataType::TranslateMatrix(location),true);
//	
//}
//
//void Score::RenderText()
//{
//	std::string scoreString = "Score: " + std::to_string(score / 100) + std::to_string((score % 100) / 10) + std::to_string(score % 10);
//	switch (fontToUse)
//	{
//	case Fonts::Font1:
//		//scoreTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString);
//		scoreTexture.Load(Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString));
//		break;
//	case Fonts::Font2:
//		scoreTexture = Engine::GetSpriteFont(static_cast<int>(fontToUse)).DrawTextToTexture(scoreString);
//		break;
//	default:
//		break;
//	}
//}