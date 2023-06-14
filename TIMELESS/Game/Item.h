#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "..\Engine\Texture.h"
#include "ItemTypes.h"
#include "Player.h"

// new itme test 0426    ---------------------------------------------------------------
class ItemParents : public GameObject
{
public:
    ItemParents(std::string spriteFile, DataType::fvec2 startPos, ItemType type, double timer);
    ItemParents(std::string spriteFile, GameObject *player, ItemType type, double timer);
    void Update(double dt) override;

    GameObjectType GetObjectType() { return GameObjectType::Item; }
    std::string GetObjectTypeName() { return "Item"; }
    bool CanCollideWith(GameObjectType objectBType) override;
    // void ResolveCollision(GameObject* objectB) override;

    virtual void DuringTimer(){};
    virtual void EndTimerEvent(){};

protected:
    double timer; // timer for speedUp, Invincible,... items.
    double max_timer;
    // int value;      //money amount for coin, range of bomb item?
    int cost; // cost of items in the store. use this when player collide with items.

    GameObject *player;

private:
};

class Bomb : public ItemParents
{
public:
    Bomb(GameObject *player, double timer);
    void DuringTimer() override;
    void EndTimerEvent() override;
    //  void ResolveCollision(GameObject* objectB) override;
};

class Invincible : public ItemParents
{
public:
    Invincible(GameObject *player, double timer);
    void DuringTimer() override;
    void EndTimerEvent() override;
    //  void ResolveCollision(GameObject* objectB) override;
};

class SpeedUp : public ItemParents
{
public:
    SpeedUp(GameObject *player, double timer);
    void DuringTimer() override;
    void EndTimerEvent() override;
    //  void ResolveCollision(GameObject* objectB) override;
};

class PortalRader : public ItemParents
{
public:
    PortalRader(GameObject *player, double timer);
    void Draw(mat3 cameraMatrix) override;
    void DuringTimer() override;
    void EndTimerEvent() override;
    //  void ResolveCollision(GameObject* objectB) override;
};

class EnergyAttack : public ItemParents
{
public:
    EnergyAttack(GameObject *player, double timer);
    void DuringTimer() override;
    void EndTimerEvent() override;
    //  void ResolveCollision(GameObject* objectB) override;
};

class NeonSlow : public ItemParents
{
public:
    NeonSlow(GameObject *player, double timer);
    void DuringTimer() override;
    void EndTimerEvent() override;
};

class NeonSlowFinish : public ItemParents
{
public:
    NeonSlowFinish(GameObject *player, double timer);
    void EndTimerEvent() override;
};

class ViewExpand : public ItemParents
{
public:
    ViewExpand(Player *player, double timer);
    void EndTimerEvent() override;

private:
    Player *player_ptr;
};

class NeonBarricade : public ItemParents
{
public:
    NeonBarricade(DataType::fvec2 pos, double timer);
    void DuringTimer() override;
    void EndTimerEvent() override;
    // void ResolveCollision(GameObject* objectB) override;
private:
    // Player* player_ptr;
};

class Resurrection : public ItemParents
{
public:
    Resurrection(Player *player, double timer);
    void DuringTimer() override;
    void EndTimerEvent() override;

private:
    Player *player_ptr;
    float angle;
    double delta_time;
    double charging_time = 1.0;
};
