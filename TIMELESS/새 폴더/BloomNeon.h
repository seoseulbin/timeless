#pragma once
#include <SFML/Graphics/Glsl.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class BloomNeon
{
public:

	struct NeonObj
	{
		sf::Vector2f position = { 0, 0 };
		sf::Vector2f scale = { 1.0f, 1.0f };
		sf::Color color = sf::Color::White;
		sf::Vector2f NeonOrigin = { 0, 0 };
		//sf::Vector3f color = { 0, 0, 0 };
		//sf::Vector2f texCoords = { 0, 0 };
	};

	//struct BloomObj
	//{
	//	sf::Vector2f position = { 0, 0 };
	//	sf::Vector2f scale = { 1.0f, 1.0f };
	//	//sf::Color color = sf::Color::White;
	//	sf::Vector2f NeonOrigin = { 0, 0 };
	//	//sf::Vector2f texCoords = { 0, 0 };
	//};

	sf::RectangleShape R_neon;

	//NeonObj N_Obj;
	//BloomObj B_Obj;
	//sf::VertexArray NeonBox;


private:
	void OneColor_NeonBoxes(sf::Vector2f neonPosition, sf::Vector2f neonScale, sf::Color neonColor);
	void fourColor_NeonBoxes(sf::Vector2f neonPosition, sf::Vector2f neonScale, sf::Color neonColor1, sf::Color neonColor2, sf::Color neonColor3, sf::Color alphaColor);
	void makeOrigin(sf::Vector2f neonPosition, sf::Vector2f neonScale);
	void bloomEffect(sf::Vector2f neonPosition, sf::Vector2f neonScale, float neonColor1, float neonColor2, float neonColor3, float alphaColor);

	float NeonOrigin_x = 0.0f;
	float NeonOrigin_y = 0.0f;
};

