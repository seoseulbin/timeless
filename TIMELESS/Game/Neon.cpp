#include"../Engine/Engine.h"
#include"../Engine/Vec2.h"
#include "Neon.h"
#include "Stage1.h"
#include"GameObjectTypes.h"
#include"Option.h"
//#include <random>
//#include "../Engine/GameState.h"

#include"ItemTypes.h"

NeonCreator::NeonCreator(int totalSize, int stageLevel)//, GameObject()
{

	level = stageLevel; 
	numNeonCores = totalSize;
	for (int i = 0; i < numNeonCores; ++i) {
		NeonCore* neon = new NeonCore();
		NeonCores.push_back(neon);
		Engine::GetGSComponent<GameObjectManager>()->Add(neon); 
	} 
	coreToUse = 0;

	num_lights = totalSize;  
	for (int i = 0; i < num_lights; ++i) { 
		NeonLight* neon = new NeonLight();
		NeonLights.push_back(neon);
	} 
	lightToUse = 0;


	timer = 0;
	delta_time = 0;
	data_index = 0;
	warning_delay = 0;
}
void NeonCreator::Unload() {
	NeonCores.clear();
	Engine::GetLogger().LogDebug("vector capacity : " + to_string(NeonCores.capacity()));
	std::vector<NeonCore*>().swap(NeonCores);
	Engine::GetLogger().LogDebug("after swap vector capacity : " + to_string(NeonCores.capacity()));

	NeonLights.clear();
	Engine::GetLogger().LogDebug("vector capacity : " + to_string(NeonLights.capacity()));
	std::vector<NeonLight*>().swap(NeonLights);
	Engine::GetLogger().LogDebug("after swap vector capacity : " + to_string(NeonLights.capacity()));

}
// delay / speed / direction  / 이동거리 / 좌표1 / (좌표2, (생략 가능))

void NeonCreator::Creat(int speed, DataType::fvec2 dir, int dist, DataType::fvec2 first_coord, DataType::fvec2 last_coord)
{
	//Engine::GetLogger().LogDebug("NEON SPAWN test");
	//line raster
	//vector for loop
	std::vector<DataType::fvec2> neons = Rasterize(first_coord, last_coord);

	for (auto& n : neons) {
		if (NeonCores[coreToUse]->IsAlive() == true) {
			Engine::GetLogger().LogError("object is being overwritten");
		}


		DataType::fvec2 neon_pos{ Stage1::x_pos + (Stage1::grid_width * n.x) + (Stage1::grid_width / 2)    ,
	 Stage1::y_pos + (Stage1::grid_height / 2) + (Stage1::grid_width * n.y) };
		DataType::fvec2 goal_pos;
		goal_pos = dir * dist * Stage1::grid_width;
		goal_pos = goal_pos + neon_pos;
		NeonCores[coreToUse]->Revive(neon_pos, dir, speed, goal_pos);

		for (int i = 0; i < 5; i++) {
			int angle = rand() % 360;
			double range = Stage1::grid_width / 2;
			DataType::fvec2 particle_start;
			DataType::fvec2 particle_goal;
			particle_start.x = neon_pos.x + static_cast<float>(range * cos(angle));
			particle_start.y = neon_pos.y + static_cast<float>(range * sin(angle));
			particle_goal.x  = goal_pos.x + static_cast<float>(range * cos(angle));
			particle_goal.y  = goal_pos.y + static_cast<float>(range * sin(angle));
			Engine::GetGSComponent<PlayerDieParticles>()->Emit(1, particle_start, { 1,1 }, (particle_goal - particle_start)/10, 0);
		}


		if (static_cast<unsigned int>(coreToUse) >= NeonCores.size() - 1) {
			coreToUse = 0;
		}
		else {
			++coreToUse;
		}
	}

}

std::vector<DataType::fvec2> NeonCreator::Rasterize(DataType::fvec2 first_coord, DataType::fvec2 last_coord)
{
	std::vector<DataType::fvec2> return_vec;

	int dx = static_cast<int>(last_coord.x - first_coord.x);
	int dy = static_cast<int>(last_coord.y - first_coord.y);
	int x = static_cast<int>(first_coord.x);
	int y = static_cast<int>(first_coord.y);
	return_vec.push_back(DataType::fvec2((float)x, (float)y));

	if (last_coord.x == -9999.f && last_coord.y == -9999.f) {
		return return_vec;
	}


	int x_dir = 0;
	int y_dir = 0;

	if (dx < 0) {
		x_dir = -1;
		dx = -dx;
	}
	else {
		x_dir = 1;
	}

	if (dy < 0) {
		y_dir = -1;
		dy = -dy;
	}
	else {
		y_dir = 1;
	}

	int d = 2 * dy - dx;            /* Initial value of d */
	int incrE = 2 * dy;             /* Increment used for move to E */
	int incrNE = 2 * (dy - dx);     /* Increment used for move to NE */


	if (dx >= dy) {

		d = 2 * dy - dx;            /* Initial value of d */
		incrE = 2 * dy;             /* Increment used for move to E */
		incrNE = 2 * (dy - dx);     /* Increment used for move to NE */

		while (x != last_coord.x) {
			if (d <= 0) {
				d += incrE;
				x += x_dir;
			}
			else {
				d += incrNE;
				x += x_dir;
				y += y_dir;
			}

			//setpixel(x, y, color);
			return_vec.push_back(DataType::fvec2((float)x, (float)y));
		}
	}
	else {

		d = 2 * dx - dy;            /* Initial value of d */
		incrE = 2 * dx;             /* Increment used for move to E */
		incrNE = 2 * (dx - dy);     /* Increment used for move to NE */

		while (y != last_coord.y) {
			if (d <= 0) {
				d += incrE;
				y += y_dir;
			}
			else {
				d += incrNE;
				x += x_dir;
				y += y_dir;
			}
			//setpixel(x, y, color);
			return_vec.push_back(DataType::fvec2((float)x, (float)y));
		}
	}


	return return_vec;
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
	PatternData* pattern_data = Engine::GetFileInput().GetPatternData(level, data_index);

	double warning_time = 0.5;
	if (pattern_data->GetDelay() - warning_time <= delta_time && delta_time - warning_delay>= 0.1 ) {		//add warning effect
		//make helper function , use rasterize
		std::vector<DataType::fvec2> neons = Rasterize(pattern_data->GetFirstCoord(), pattern_data->GetLastCoord());

		int check_next_index = data_index + 1;
		if (Engine::GetFileInput().GetDataSize(level) <= check_next_index) {
			check_next_index = 0;
		}
		PatternData* next_data = Engine::GetFileInput().GetPatternData(level, check_next_index);;

		while (next_data->GetDelay() == 0) {
			

			std::vector<DataType::fvec2> add_neons = Rasterize(next_data->GetFirstCoord(), next_data->GetLastCoord());

			neons.insert(neons.end(), add_neons.begin(), add_neons.end());

			check_next_index++;
			if (Engine::GetFileInput().GetDataSize(level) <= check_next_index) {
				check_next_index = 0;
			}
			next_data = Engine::GetFileInput().GetPatternData(level, check_next_index);;
		}


		for (auto& n : neons) {

			DataType::fvec2 neon_center_pos{ Stage1::x_pos + (Stage1::grid_width * n.x) + (Stage1::grid_width / 2)    ,
	Stage1::y_pos + (Stage1::grid_height / 2) + (Stage1::grid_width * n.y) };

			int angle = rand() % 360;
			double range = Stage1::grid_width / 2 * (pattern_data->GetDelay() - delta_time) / warning_time;
			DataType::fvec2 neon_outline_pos{ neon_center_pos.x + static_cast<float>(range * cos(angle)), neon_center_pos.y + static_cast<float>(range * sin(angle)) };

			//Engine::GetGSComponent<PlayerDieParticles>()->Emit(1, neon_outline_pos, (neon_center_pos - neon_outline_pos)*100, {100,100}, 0);
			Engine::GetGSComponent<PlayerDieParticles>()->Emit(1, neon_outline_pos, { 1,1 }, (neon_center_pos - neon_outline_pos), 0);
		}
		warning_delay = delta_time;

	}


	if (pattern_data->GetDelay() <= delta_time) {

		Creat(pattern_data->GetSpeed(), pattern_data->GetDirection(), pattern_data->GetDistance(), pattern_data->GetFirstCoord(), pattern_data->GetLastCoord());
		data_index++;
		if (Engine::GetFileInput().GetDataSize(level) <= data_index) {
			data_index = 0;
		}




		delta_time = 0;
		warning_delay = 0;
	}


	//for (auto& element : NeonCores) {
	//	if (element->IsAlive() == true) {
	//		//element->Update(dt);
	//		//

	//		if (element->IsNeonMoved() == true) {
	//			//create NeonLight;
	//			SetNeonLights(element->GetHitboxPosition(), 8);
	//		}

	//	}
	//}

	//for (auto& element : NeonLights) {
	//	if (element->IsAlive() == true) {
	//		element->Update(dt);

	//	}
	//}




	timer += dt;
	delta_time += dt;
}

void NeonCreator::Create_ending(int speed, DataType::fvec2 dir, int dist, DataType::fvec2 first_coord, DataType::fvec2 last_coord)
{
	std::vector<DataType::fvec2> neons = Rasterize(first_coord, last_coord);

	for (auto& n : neons) {
		if (NeonCores[coreToUse]->IsAlive() == true) {
			Engine::GetLogger().LogError("object is being overwritten");
		}


		DataType::fvec2 neon_pos{ 0.0f + (Stage1::grid_width * n.x) + (Stage1::grid_width / 2)    ,
	 0.0f + (Stage1::grid_height / 2) + (Stage1::grid_width * n.y) };
		DataType::fvec2 goal_pos;
		goal_pos = dir * dist * Stage1::grid_width;
		goal_pos = goal_pos + neon_pos;
		NeonCores[coreToUse]->Revive(neon_pos, dir, speed, goal_pos);

		for (int i = 0; i < 5; i++) {
			int angle = rand() % 360;
			double range = Stage1::grid_width / 2;
			DataType::fvec2 particle_start;
			DataType::fvec2 particle_goal;
			particle_start.x = neon_pos.x + static_cast<float>(range * cos(angle));
			particle_start.y = neon_pos.y + static_cast<float>(range * sin(angle));
			particle_goal.x = goal_pos.x + static_cast<float>(range * cos(angle));
			particle_goal.y = goal_pos.y + static_cast<float>(range * sin(angle));
			Engine::GetGSComponent<PlayerDieParticles>()->Emit(1, particle_start, { 1,1 }, (particle_goal - particle_start) / 10, 0);
		}


		if (static_cast<unsigned int>(coreToUse) >= NeonCores.size() - 1) {
			coreToUse = 0;
		}
		else {
			++coreToUse;
		}
	}

}

void NeonCreator::Update_ending(double dt)
{
	PatternData* pattern_data = Engine::GetFileInput().GetPatternData(7, data_index);

	double warning_time = 0.5;
	if (pattern_data->GetDelay() - warning_time <= delta_time && delta_time - warning_delay >= 0.1) {		//add warning effect
		//make helper function , use rasterize
		std::vector<DataType::fvec2> neons = Rasterize(pattern_data->GetFirstCoord(), pattern_data->GetLastCoord());

		int check_next_index = data_index + 1;
		if (Engine::GetFileInput().GetDataSize(7) <= check_next_index) {
			check_next_index = 0;
		}
		PatternData* next_data = Engine::GetFileInput().GetPatternData(7, check_next_index);;

		while (next_data->GetDelay() == 0) {


			std::vector<DataType::fvec2> add_neons = Rasterize(next_data->GetFirstCoord(), next_data->GetLastCoord());

			neons.insert(neons.end(), add_neons.begin(), add_neons.end());

			check_next_index++;
			if (Engine::GetFileInput().GetDataSize(7) <= check_next_index) {
				check_next_index = 0;
			}
			next_data = Engine::GetFileInput().GetPatternData(7, check_next_index);;
		}


		for (auto& n : neons) {

			DataType::fvec2 neon_center_pos{ 0.0f + (Stage1::grid_width * n.x) + (Stage1::grid_width / 2)    ,
	0.0f + (Stage1::grid_height / 2) + (Stage1::grid_width * n.y) };

			int angle = rand() % 360;
			double range = Stage1::grid_width / 2 * (pattern_data->GetDelay() - delta_time) / warning_time;
			DataType::fvec2 neon_outline_pos{ neon_center_pos.x + static_cast<float>(range * cos(angle)), neon_center_pos.y + static_cast<float>(range * sin(angle)) };

			//Engine::GetGSComponent<PlayerDieParticles>()->Emit(1, neon_outline_pos, (neon_center_pos - neon_outline_pos)*100, {100,100}, 0);
			Engine::GetGSComponent<PlayerDieParticles>()->Emit(1, neon_outline_pos, { 1,1 }, (neon_center_pos - neon_outline_pos), 0);
		}
		warning_delay = delta_time;

	}


	if (pattern_data->GetDelay() <= delta_time) {

		Create_ending(pattern_data->GetSpeed(), pattern_data->GetDirection(), pattern_data->GetDistance(), pattern_data->GetFirstCoord(), pattern_data->GetLastCoord());
		data_index++;
		if (Engine::GetFileInput().GetDataSize(7) <= data_index) {
			data_index = 0;
		}
		delta_time = 0;
		warning_delay = 0;
	}
	timer += dt;
	delta_time += dt;
}


void NeonCreator::Draw(mat3 cameraMatrix)
{
	for (auto& element : NeonLights)
	{
		if (element->IsAlive())
		{

			neon_image_opengl.Draw_particle_effect(cameraMatrix * mat3::build_translation(element->GetPositionF().x, element->GetPositionF().y), element->GetAlphaF());

		}
	}
}

void NeonCreator::SetNeonLights(DataType::fvec2 neonPosition, int alphaDecrease)
{
	if (NeonLights[lightToUse]->IsAlive() == true) {
		Engine::GetLogger().LogError("NeonLIGHT is being overwritten");
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


NeonCreator::NeonCore::NeonCore() : GameObject(DataType::fvec2{ 0,0 })
{
	AddGOComponent(new Sprite(Option::neon_file_path, this));
	
	SetPosition(DataType::fvec2{ (float)hitbox_position.x, (float)hitbox_position.y });
}


void NeonCreator::NeonCore::Revive(DataType::fvec2 neonPosition, DataType::fvec2 neonDirection, int set_speed, DataType::fvec2 goalPosition)
{
	position = neonPosition;
	previous_position = neonPosition;
	hitbox_position = neonPosition;
	direction = neonDirection;
	speed = (float)set_speed;
	original_speed = speed;
	slow_speed = speed / 4;
	goal_position = goalPosition;
	neon_moved = true;
	is_alived = true;
	SetPosition(DataType::fvec2{ (float)position.x, (float)position.y });

	//	Engine::GetLogger().LogDebug("NEEEEEEEEEEEEEONNNNNNNNN REVIVEEEEEEEEEEEEE");
}
void NeonCreator::NeonCore::Update(double dt)
{

	if (is_alived == true) {
		GameObject::Update(dt);
		position += direction * speed * dt;	//

		if (sqrt(pow(position.x - previous_position.x, 2) + pow(position.y - previous_position.y, 2)) >= 80) {
			
			Engine::GetGSComponent<NeonParticles>()->Emit(1, previous_position, DataType::fvec2{ 0,0 }, DataType::fvec2{ 0,0 }, 1);
			//Engine::GetGSComponent<NeonParticles>()->Emit(1, previous_position, DataType::fvec2{ 400,400 }, DataType::fvec2{ 10,30 }, 3.14 / 2);

			if (previous_position == goal_position)
			{
				is_alived = false;
				//Engine::GetGSComponent<NeonParticles>()->Emit(1, goal_position, DataType::fvec2{ 0,0 }, DataType::fvec2{ 0,0 }, 1);
			}
			else {
				previous_position += direction * Stage1::grid_width;
				hitbox_position = previous_position;
				neon_moved = true;
			}





		}
		SetPosition(DataType::fvec2{ (float)hitbox_position.x, (float)hitbox_position.y });



		////if (  sqrt(pow(position.x - goal_position.x, 2) + pow(position.y - goal_position.y, 2)) < 15  ) 
		//if ( hitbox_position == goal_position ) 
		//{
		//	is_alived = false;
		//	//Engine::GetGSComponent<NeonParticles>()->Emit(1, goal_position, DataType::fvec2{ 0,0 }, DataType::fvec2{ 0,0 }, 1);
		//}
		//
	}

	if (!is_alived) {
		hitbox_position = DataType::fvec2{ -99999,-99999 };
		SetPosition(DataType::fvec2{ (float)hitbox_position.x, (float)hitbox_position.y });
	}

	//if ( !sqrt(pow(position.x - goal_position.x, 2) + pow(position.y - goal_position.y, 2)) > 15) {
	//	is_alived = false;
	//	Engine::GetGSComponent<NeonParticles>()->Emit(1, goal_position, DataType::fvec2{ 0,0 }, DataType::fvec2{ 0,0 }, 1);
	//}

}
void NeonCreator::NeonCore::Draw([[maybe_unused]] mat3 cameraMatrix)
{
	if (is_alived == true) {

		GameObject::Draw(cameraMatrix);

	}
}

//	-	-	-	-	-	-	-
void NeonCreator::NeonLight::Revive(DataType::fvec2 neonPosition, int alphaDecrease)
{
	position = neonPosition;
	decrease = alphaDecrease;

}
void NeonCreator::NeonLight::Update(double /*dt*/)
{
}
void NeonCreator::NeonLight::Draw()
{
}




GameObjectType NeonCreator::NeonCore::GetObjectType()
{
	return GameObjectType::Neon;
}

std::string NeonCreator::NeonCore::GetObjectTypeName()
{
	return "Neon";
}

bool NeonCreator::NeonCore::CanCollideWith(GameObjectType objectB)
{
	//if (objectB == GameObjectType::Neon) {
	//	return false;
	//}
	//else {
	//	return true;
	//}

	switch (objectB)
	{
	case GameObjectType::Player:
		return true;
		break;
	case GameObjectType::Item:

		//switch (objectB)
		//{
		//case ItemType::BombExplosion:
		//	return true;
		//	break;
		//default:
		//	return false;
		//	break;
		//}

		return true;
		break;
	default:
		return false;
		break;
	}
}

void NeonCreator::NeonCore::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Item)
	{
		//Engine::GetLogger().LogDebug("TTTTTTTTTTTTTTTTTTTTTTTTTTTessssssssssssssst");

		switch (objectB->GetItemType())
		{
		case ItemType::EnergyAttack:
		case ItemType::BombExplosion:
			Engine::GetLogger().LogDebug("DESTROY NEON");
			is_alived = false;
			//RemoveGOComponent<Collision>();
			break;
		case ItemType::NeonSlow:
			SetSpeed(slow_speed);
			break;
		case ItemType::NeonSlowFinish:
			SetSpeed(original_speed);
			break;
		case ItemType::NeonBaricade:
			Engine::GetLogger().LogDebug("collide with barricade");
			is_alived = false;
			objectB->RemoveGOComponent<Collision>();
			break;
		default:
			break;
		}




	}




}