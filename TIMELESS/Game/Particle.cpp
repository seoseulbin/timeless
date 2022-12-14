
//#include "../Engine/Matrix.cpp"
#include "Particle.h"
#include"../Engine/Engine.h"
#include "../Engine/GameObjectManager.h"
#include "GameObjectTypes.h"


//#include "../Engine/GameObjectTypes.h"

ParticleEmitter::ParticleEmitter(std::string spriteFile, int totalParticles, double lifetime,bool displayUnder) : 
	numParticles(totalParticles), lifetime(lifetime)
{
	for (int i = 0; i < numParticles; ++i) {
		Particle* particle = new Particle(spriteFile, displayUnder);
		particles.push_back(particle);
	//	GameObject::AddGOComponent(particle);
		Engine::GetGSComponent<GameObjectManager>()->Add(particle);
		//Engine::GetGameObjectManager().Add(particle);
	//AddGOComponent(new Sprite("assets/data/neon_yellow.spt", this));
	}
	particleToUse = 0;
}
NeonParticles::NeonParticles() : ParticleEmitter("assets/data/neon_yellow.spt", 300, 0.5,true) { }
PlayerDieParticles::PlayerDieParticles() : ParticleEmitter("assets/data/player_die_particle.spt", 30, 1,false) { }

PlayerExplodeParticle_1::PlayerExplodeParticle_1() : ParticleEmitter("assets/data/broken_player_1.spt", 1, 1, false) { }
PlayerExplodeParticle_2::PlayerExplodeParticle_2() : ParticleEmitter("assets/data/broken_player_2.spt", 1, 1, false) { }
PlayerExplodeParticle_3::PlayerExplodeParticle_3() : ParticleEmitter("assets/data/broken_player_3.spt", 1, 1, false) { }

TempHPParticle_0::TempHPParticle_0() : ParticleEmitter("assets/data/hp0.spt", 1, 2, false) {}
TempHPParticle_1::TempHPParticle_1() : ParticleEmitter("assets/data/hp1.spt", 1, 2, false) {}
TempHPParticle_2::TempHPParticle_2() : ParticleEmitter("assets/data/hp2.spt", 1, 2, false) {}

GAME_Particle::GAME_Particle() : ParticleEmitter("assets/data/GAME.spt", 1, 3, false) {}
OVER_Particle::OVER_Particle() : ParticleEmitter("assets/data/OVER.spt", 1, 3, false) {}

void ParticleEmitter::Emit(int toEmit, DataType::fvec2 emitterPosition, DataType::fvec2 emitterVelocity, [[maybe_unused]] DataType::fvec2 emitVector, [[maybe_unused]] double spread) {
	for (int i = 0; i < toEmit; ++i) {
		if (particles[particleToUse]->IsAlive() == true) {
			Engine::GetLogger().LogError("Particle is being overwritten");
		}

		double angleVariation = spread != 0 ? ((rand() % static_cast<int>(spread * 1024)) / 1024.0f) - spread / 2 : 0;
		float timeVariation = 0;
		emitterVelocity = (DataType::RotateMatrix::RotateMatrix(static_cast<float>(angleVariation)) * emitVector);
		if (emitterVelocity.x != 0 && emitterVelocity.y != 0) {
			timeVariation = static_cast<float>(rand() % 100);
			emitterVelocity.x += timeVariation;
			emitterVelocity.y += timeVariation;
		}

		particles[particleToUse]->Revive(emitterPosition, emitterVelocity, lifetime);
		if (static_cast<unsigned int>(particleToUse) >= particles.size() - 1) {
			particleToUse = 0;
		}
		else { 
			++particleToUse;
		}
	}
}

void ParticleEmitter::Clear() {
	particles.clear();
}

//	-	-	-	- particle	-	-	-	-	-	-	-		--		-	--	-	-	-	-	-	

ParticleEmitter::Particle::Particle(std::string spriteFile, bool displayUnder) :
	GameObject{ {0,0} }, life(0), max_life(0),is_display_under(displayUnder) 
{
	//sprite.Load(spriteFile);
	AddGOComponent(new Sprite(spriteFile, this));
}

void ParticleEmitter::Particle::Revive(DataType::fvec2 particlePosition, [[maybe_unused]] DataType::fvec2 particleVelocity, double particleLife) {
	GameObject::SetPosition(particlePosition);
	GameObject::velocity = particleVelocity;
	Particle::life = particleLife;
	Particle::max_life = particleLife;
	Particle::alpha = 1.0f;
//	sprite.PlayAnimation(0);
}

void ParticleEmitter::Particle::Update(double dt) {
	if (IsAlive() == true) {
		life -= dt;
		alpha = (float)life / float(max_life);
		GameObject::Update(dt);
	}
}

void ParticleEmitter::Particle::Draw(mat3 cameraMatrix) {
	if (IsAlive() == true) {
		GameObject::Draw(cameraMatrix, alpha);
	//	neon_image_opengl.Draw_Neon(cameraMatrix * GetMatrix_mat3());
	}
}

GameObjectType ParticleEmitter::Particle::GetObjectType() {
	if (is_display_under)
		return GameObjectType::UnderParticle;
	return GameObjectType::Particle;
}
