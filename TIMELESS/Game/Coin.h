#pragma once
#include "UI.h"
#include "GameObjectTypes.h"
#include "..\Engine\Texture.h"
#include "..\Engine\GameObject.h"
#include "../Engine/Font.h"

class Coin : public UI
{
public:
    Coin(DataType::fvec2 pos);

    void Update(double dt) override;
    void Draw(mat3 NDCmatrix) override;
    void Draw(float scroll) override;

private:
    Texture testFont;
    Texture timerFont;
};

class Timer : public UI
{
public:
    Timer(DataType::fvec2 pos);

    void Update(double dt) override;
    void Draw(mat3 NDCmatrix) override;
    void Draw(float scroll) override;

private:
    Texture timerFont;
};

class LevelInfo : public UI
{
public:
    LevelInfo(DataType::fvec2 pos, double timer, std::string text);

    void Update(double dt) override;
    void Draw(mat3 NDCmatrix) override;
    void Draw(float scroll) override;

private:
    Texture levelFont;
    double visible_timer;
    std::string str;
};
