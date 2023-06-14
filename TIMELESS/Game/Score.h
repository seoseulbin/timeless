// #pragma once
// #include"..\Engine\Texture.h"
// #include "..\Engine\Component.h"
//
// enum class Fonts;
//
// class Score : public Component {
// public:
//     Score(int startingScore, Fonts fontToUse);
//     void AddScore(int newPoints);
//     void Draw(DataType::fvec2 location);
//     unsigned int GetScore() { return score; }
// private:
//     void RenderText();
//
//     Fonts fontToUse;
//     unsigned int score;
//
//     Texture scoreTexture;
// };