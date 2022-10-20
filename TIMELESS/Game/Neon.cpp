#include<SFML/Graphics.hpp>
#include"../Engine/Engine.h"
#include"../Engine/Vec2.h"
#include "Neon.h"
#include "Stage1.h"


//test용 neon pattern	-	-	-	-	-	-

//NeonCreator::NeonCreator(int totalSize) : numNeonCores(totalSize)
//{
//	for (int i = 0; i < numNeonCores; ++i) {
//		NeonCore* neon = new NeonCore();
//		NeonCores.push_back(neon);
//		//Engine::GetGameObjectManager().Add(particle);
//	}
//	coreToUse = 0;
//}

NeonCreator::NeonCreator() : zKey(sf::Keyboard::Z), wKey(sf::Keyboard::W), sKey(sf::Keyboard::S), aKey(sf::Keyboard::A), dKey(sf::Keyboard::D) {}

void NeonCreator::Load(int totalSize) {
	numNeonCores = totalSize;
	for (int i = 0; i < numNeonCores; ++i) {
		NeonCore* neon = new NeonCore();
		NeonCores.push_back(neon);
	}
	coreToUse = 0;

	num_lights = totalSize;
	for (int i = 0; i < num_lights; ++i) {
		NeonLight* neon = new NeonLight();
		NeonLights.push_back(neon);
	}
	lightToUse = 0;
}

void NeonCreator::Creat(int toCreate, DataType::vec2 createPosition, DataType::vec2 createDirection, DataType::vec2 setGoalPosition)
{
	for (int i = 0; i < toCreate; ++i) {
		if (NeonCores[coreToUse]->IsAlive() == true) {
			Engine::GetLogger().LogError("object is being overwritten");
		}
		NeonCores[coreToUse]->Revive(createPosition, createDirection, setGoalPosition);
		if (static_cast<unsigned int>(coreToUse) >= NeonCores.size() - 1) {
			coreToUse = 0;
		}
		else {
			++coreToUse;
		}
	}
}

void NeonCreator::Clear()
{
	NeonCores.clear();
}

//temporary varialbes	-	-	
bool test = true; // 네온 생성 test용 
int test_2 = 0;
float delay_test = 300.0f;
bool is_z_pressed = false;
//	-	-	-	-	-	-	
void NeonCreator::Update(double dt)
{


	if (zKey.IsKeyDown() && delay_test > 60.0f && is_z_pressed == false ) {
		is_z_pressed = true;
		delay_test = 0.0f;
	}
	if (zKey.IsKeyDown() && delay_test > 60.0f && is_z_pressed == true) {
		is_z_pressed = false;
		delay_test = 0.0f;

	}

	if (is_z_pressed && delay_test > 60.0f) {
		DataType::vec2 neon_pos{ Stage1::x_pos + (Stage1::grid_width * test_2) + (Stage1::grid_width / 2)    ,  Stage1::y_pos + (Stage1::grid_height / 2) - (Stage1::grid_width * 3) };
		DataType::vec2 dir{ 0,1 };
		DataType::vec2 goal_pos{ Stage1::x_pos + (Stage1::grid_width * test_2) + (Stage1::grid_width / 2) ,  Stage1::y_pos + (Stage1::grid_height * Stage1::column_size) - (Stage1::grid_height / 2) + (Stage1::grid_width * 3) };
		Creat(1, neon_pos, dir, goal_pos);
		delay_test = 0.0f;
		test_2++;
		if (test_2 >= Stage1::row_size) {
			test_2 = 0;
		}
	}

	if (sKey.IsKeyDown() && delay_test > 60.0f) {


		for (int i = 0; i < Stage1::row_size; i++) {

			DataType::vec2 neon_pos{ Stage1::x_pos + (Stage1::grid_width * i) + (Stage1::grid_width / 2)    ,  Stage1::y_pos + (Stage1::grid_height / 2) - (Stage1::grid_width * 3) };
			DataType::vec2 dir{ 0,1 };
			DataType::vec2 goal_pos{ Stage1::x_pos + (Stage1::grid_width * i) + (Stage1::grid_width / 2) , Stage1::y_pos + (Stage1::grid_height * Stage1::column_size) - (Stage1::grid_height / 2) + (Stage1::grid_width * 3) };
			Creat(1, neon_pos, dir, goal_pos);
		}

		delay_test = 0.0f;
	}

	if (wKey.IsKeyDown() && delay_test > 60.0f) {

		for (int i = 0; i < Stage1::row_size; i++) {

			DataType::vec2 goal_pos{ Stage1::x_pos + (Stage1::grid_width * i) + (Stage1::grid_width / 2)    ,  Stage1::y_pos + (Stage1::grid_height / 2) - (Stage1::grid_width * 3) };
			DataType::vec2 dir{ 0,-1 };
			DataType::vec2 neon_pos{ Stage1::x_pos + (Stage1::grid_width * i) + (Stage1::grid_width / 2) ,  Stage1::y_pos + (Stage1::grid_height * Stage1::column_size) - (Stage1::grid_height / 2) + (Stage1::grid_width * 3) };
			Creat(1, neon_pos, dir, goal_pos);
		}
		delay_test = 0.0f;

	}

	if (aKey.IsKeyDown() && delay_test > 60.0f) {

		for (int i = 0; i < Stage1::column_size; i++) {

			DataType::vec2 neon_pos{ Stage1::x_pos + (Stage1::grid_width * Stage1::row_size) + (Stage1::grid_width / 2) + (Stage1::grid_width * 3),  Stage1::y_pos + (Stage1::grid_height * i) + (Stage1::grid_height / 2) };
			DataType::vec2 goal_pos{ Stage1::x_pos + (Stage1::grid_width / 2) - (Stage1::grid_width * 3)  ,   Stage1::y_pos + (Stage1::grid_height * i) + (Stage1::grid_height / 2) };
			DataType::vec2 dir{ -1,0 };

			Creat(1, neon_pos, dir, goal_pos);
		}
		delay_test = 0.0f;

	}
	if (dKey.IsKeyDown() && delay_test > 60.0f) {

		for (int i = 0; i < Stage1::column_size; i++) {

			DataType::vec2 neon_pos{ Stage1::x_pos + (Stage1::grid_width / 2) - (Stage1::grid_width * 3)  ,   Stage1::y_pos + (Stage1::grid_height * i) + (Stage1::grid_height / 2) };
			DataType::vec2 goal_pos{ Stage1::x_pos + (Stage1::grid_width * Stage1::row_size) + (Stage1::grid_width / 2) + (Stage1::grid_width * 3),  Stage1::y_pos + (Stage1::grid_height * i) + (Stage1::grid_height / 2) };
			DataType::vec2 dir{ 1,0 };

			Creat(1, neon_pos, dir, goal_pos);
		}
		delay_test = 0.0f;

	}

	delay_test += 5.0f;
	//	-	-	-	-	-	-	-	-	-

	for (auto& element : NeonCores) {
		if (element->IsAlive() == true) {
			element->Update(dt);
			if (element->IsNeonMoved() == true) {
				//create NeonLight;
				SetNeonLights(element->GetHitboxPosition(), 5);
			}

		}
	}

	for (auto& element : NeonLights) {
		if (element->IsAlive() == true) {
			element->Update(dt);
		}
	}
}

void NeonCreator::Draw()
{
	for (auto& element : NeonCores) {
		if (element->IsAlive() == true) {
			element->Draw();
		}
	}
	for (auto& element : NeonLights) {
		if (element->IsAlive() == true) {
			element->Draw();
		}
	}

}

void NeonCreator::SetNeonLights(DataType::vec2 neonPosition, int alphaDecrease) 
{
	if (NeonLights[lightToUse]->IsAlive() == true) {
		Engine::GetLogger().LogError("object is being overwritten");
	}
	NeonLights[lightToUse]->Revive(neonPosition, alphaDecrease);
	if (static_cast<unsigned int>(lightToUse) >= NeonLights.size() - 1) {
		lightToUse = 0;
	}
	else {
		++lightToUse;
	}
}


//	-	-	-	-	-	-	-

void NeonCreator::NeonCore::Revive(DataType::vec2 neonPosition, DataType::vec2 neonDirection, DataType::vec2 goalPosition)
{
	position = neonPosition;
	previous_position = neonPosition;
	hitbox_position = neonPosition;
	direction = neonDirection;
	goal_position = goalPosition;
	neon_moved = true;
	//Engine::GetLogger().LogDebug("neon set start position");

	neon.setSize(sf::Vector2f((float)80, (float)80));
	neon.setFillColor(sf::Color::Yellow);
	neon.setOutlineColor(sf::Color::Black);
	neon.setOutlineThickness(1.0f);
	neon.setPosition((float)hitbox_position.x, (float)hitbox_position.y);
	neon.setOrigin((float)80 / 2, (float)80 / 2);

	test_neon.setRadius((float)50 / 2);
	test_neon.setFillColor(sf::Color::Red);
	test_neon.setOrigin((float)50 / 2, (float)50 / 2);
	test_neon.setPosition((float)position.x, (float)position.y);

}
void NeonCreator::NeonCore::Update(double dt)
{
	position += direction * 500 * dt;	//
	neon.setPosition((float)hitbox_position.x, (float)hitbox_position.y);
	test_neon.setPosition((float)position.x, (float)position.y);

	if (sqrt(pow(position.x - previous_position.x, 2) + pow(position.y - previous_position.y, 2)) >= 80) {
		previous_position += direction * Stage1::grid_width;
		hitbox_position = previous_position;
		neon_moved = true;
	}
}
void NeonCreator::NeonCore::Draw()
{
	//Engine::GetWindow().Draw(neon);

	//Engine::GetWindow().Draw(test_neon);
}

//	-	-	-	-	-	-	-
void NeonCreator::NeonLight::Revive(DataType::vec2 neonPosition, int alphaDecrease)
{
	position = neonPosition;
	decrease = alphaDecrease;
	alpha = 255;
	neon.setSize(sf::Vector2f((float)80, (float)80));
	neon.setFillColor(sf::Color(255,255,0,static_cast<sf::Uint8>(alpha)));
	neon.setOutlineColor(sf::Color(0,0,0,0));
	neon.setOutlineThickness(0.0f);
	neon.setPosition((float)position.x, (float)position.y);
	neon.setOrigin((float)80 / 2, (float)80 / 2);
	
}
void NeonCreator::NeonLight::Update(double /*dt*/)
{
	neon.setFillColor(sf::Color(255, 255, 0, static_cast<sf::Uint8>(alpha)));
	alpha -= decrease;// * dt;
}
void NeonCreator::NeonLight::Draw() 
{
	Engine::GetWindow().Draw(neon);
}