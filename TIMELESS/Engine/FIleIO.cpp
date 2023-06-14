#include "FileIO.h"
#include "Engine.h"

using namespace std;

bool FileInput::CheatMode = false;

// dataÁ¾·ù (Pattern, Savefile, ... ) / (stage¹øÈ£)
// delay / speed / direction  / ÀÌµ¿°Å¸® / ÁÂÇ¥1.x / ÁÂÇ¥1.y / (ÁÂÇ¥2.x  / ÁÂÇ¥2.y )

/*
Pattern 1
2.0  300  DOWN  10  1  3
2.0  300  LEFT  15  3  3   3   6
*/

// map
/*
Map 1
#01000000
001000000
000000000
*/
void FileInput::Read(string path)
{

	std::ifstream source;

	source.open(path, ios_base::in);

	if (!source)
	{
		cerr << "Can't open Data!\n";
	}
	else
	{

		string type_input;
		std::getline(source, type_input);
		std::istringstream input(type_input);

		string filetype;
		input >> filetype;

		int stage_level;
		int total_stage;
		if (filetype == "Pattern")
		{ // if file data is about pattern

			input >> stage_level;

			Engine::GetLogger().LogEvent("Read pattern for stage " + to_string(stage_level));

			// vector<PatternData*> temp_pattern;
			for (std::string line; std::getline(source, line);)
			{
				std::istringstream in(line);

				double delay;
				int speed;
				string str_direction;
				DataType::fvec2 direction;
				int distance;
				DataType::fvec2 first_coordinate;
				DataType::fvec2 last_coordinate{-9999, -9999};

				in >> delay >> speed >> str_direction >> distance >> first_coordinate.x >> first_coordinate.y >> last_coordinate.x >> last_coordinate.y;

				if (str_direction == "LEFT")
				{
					direction = DataType::fvec2(-1, 0);
				}
				else if (str_direction == "RIGHT")
				{
					direction = DataType::fvec2(1, 0);
				}
				else if (str_direction == "UP")
				{
					direction = DataType::fvec2(0, -1);
				}
				else if (str_direction == "DOWN")
				{
					direction = DataType::fvec2(0, 1);
				}

				if (line.empty())
				{
					break;
				}

				PatternData *p_new = new PatternData(delay, speed, direction, distance, first_coordinate, last_coordinate);
				pattern_data[stage_level].push_back(p_new);
				// temp_pattern.push_back(p_new);
			}

			//  pattern_data.push_back(temp_pattern);
		}
		else if (filetype == "Map")
		{ // if file data is about Map design
			input >> stage_level;
			Engine::GetLogger().LogEvent("Read map for stage " + to_string(stage_level));

			char character;
			while (true)
			{
				source.get(character);
				if (source.fail())
				{
					break;
				}
				// cout << character; //test
				if (character != '\n')
				{
					// map_data[stage_level - 1].push_back(character);
				}
				map_data[stage_level].push_back(character);
			}

			while (map_data[stage_level].back() == '\n')
			{
				map_data[stage_level].pop_back();
			}
		}
		else if (filetype == "Savefile")
		{ // if file data is about savefile
		}
		else if (filetype == "Gamedata")
		{ // if file data is about Gamedata
			Engine::GetLogger().LogEvent("Read Game Data");
			input >> total_stage;

			// vector<PatternData*> temp_p;
			// for (int i = 0; i < total_stage; i++) {
			//     pattern_data.push_back(temp_p);
			// }

			pattern_data.resize(total_stage + 1);
			map_data.resize(total_stage + 1);
		}

		else if (filetype == "Cheat")
		{
			string cheatMode;
			input >> cheatMode;
			if (cheatMode == "false")
			{
				CheatMode = false;
				std::cout << "Cheat Mode : DISABLE" << std::endl;
			}
			else if (cheatMode == "true")
			{
				CheatMode = true;
				std::cout << "Cheat Mode : ENABLE" << std::endl;
			}
			else
			{
				CheatMode = false;
				std::cout << "Cheat Mode : DISABLE" << std::endl;
			}
		}
	}
}
