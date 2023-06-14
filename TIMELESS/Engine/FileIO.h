#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Vec2.h"

// delay / speed / direction  / 이동거리 / 좌표1 / (좌표2, (생략 가능))
// 2.0  300  LEFT  10  1,3
//

class PatternData
{
public:
	PatternData(double delay, int speed, DataType::fvec2 dir, int dist, DataType::fvec2 first_coord, DataType::fvec2 last_coord)
		: delay(delay), speed(speed), direction(dir), distance(dist), first_coordinate(first_coord), last_coordinate(last_coord) {}

	double GetDelay() { return delay; }
	int GetSpeed() { return speed; }
	DataType::fvec2 GetDirection() { return direction; }
	int GetDistance() { return distance; }
	DataType::fvec2 GetFirstCoord() { return first_coordinate; }
	DataType::fvec2 GetLastCoord() { return last_coordinate; }

private:
	double delay;
	int speed;
	// string direction;
	DataType::fvec2 direction;
	int distance;
	DataType::fvec2 first_coordinate;
	DataType::fvec2 last_coordinate{-9999, -9999};
};

class FileInput
{ // Engine에 벡터 저장하고 관리하는 class 따로 빼서 분리
public:
	void Read(std::string path);
	// std::vector<PatternData*> GetPatterndata(int index) {
	//	return pattern_data[index - 1];
	// }

	PatternData *GetPatternData(int stage, int index)
	{
		return pattern_data[stage][index];
	}
	int GetDataSize(int stage)
	{
		return static_cast<int>(pattern_data[stage].size());
	}

	std::vector<char> GetMapData(int stage)
	{
		return map_data[stage];
	}
	void ClearWallGrid()
	{
		wall_grid_data.clear();
		std::vector<std::vector<DataType::fvec2>>().swap(wall_grid_data);
	}

	static bool CheatMode;

private:
	// std::vector<PatternData> pattern_data;

	std::vector<std::vector<PatternData *>> pattern_data;
	std::vector<std::vector<char>> map_data;

	std::vector<std::vector<DataType::fvec2>> wall_grid_data;
	DataType::fvec2 goal_grid_position;
	// std::vector<std::vector<PatternData*> > pattern_data{ 10 };
	// pattern_data.resize(10);
};