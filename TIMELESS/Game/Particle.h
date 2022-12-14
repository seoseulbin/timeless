#pragma once
#include <string>

#include <vector>
#include "../Engine/Vec2.h"
#include "../Engine/Component.h"
#include"../Engine/GameObject.h"
#include"../Engine/Sprite.h"


class ParticleEmitter : public Component {
public:
    ParticleEmitter(std::string spriteFile, int totalParticles, double lifetime, bool displayUnder);
    void Emit(int toEmit, DataType::fvec2 emitterPosition, DataType::fvec2 emitterVelocity, DataType::fvec2 emitVector, double spread);
    void Clear();
private:
    class Particle : public GameObject {
    public:
        Particle(std::string spriteFile, bool displayUnder);
        void Revive(DataType::fvec2 particlePosition, DataType::fvec2 particleVelocity, double particleLife);
        void Update(double dt) override;
        void Draw(mat3 cameraMatrix) override;
        bool IsAlive() { return life > 0; }

        GameObjectType GetObjectType() override;
        std::string GetObjectTypeName() { return "Particle"; }
    private:
        double life;
        double max_life;
        float alpha;

        bool is_display_under;
    };

    int numParticles;
    std::vector<Particle*> particles;
    int particleToUse;
    double lifetime;
};

class NeonParticles : public ParticleEmitter {
public:
    NeonParticles();
};

class PlayerDieParticles : public ParticleEmitter {
public:
    PlayerDieParticles();
};

class PlayerExplodeParticle_1 : public ParticleEmitter {
public:
    PlayerExplodeParticle_1();
};
class PlayerExplodeParticle_2 : public ParticleEmitter {
public:
    PlayerExplodeParticle_2();
};
class PlayerExplodeParticle_3 : public ParticleEmitter {
public:
    PlayerExplodeParticle_3();
};


class TempHPParticle_0 :public ParticleEmitter {
public:
    TempHPParticle_0();
};
class TempHPParticle_1 :public ParticleEmitter {
public:
    TempHPParticle_1();
};
class TempHPParticle_2 :public ParticleEmitter {
public:
    TempHPParticle_2();
};

class GAME_Particle :public ParticleEmitter {
public:
    GAME_Particle();
};
class OVER_Particle :public ParticleEmitter {
public:
    OVER_Particle();
};