#include "BloomNeon.h"
#include "angles.h"

//make rectangle with sf::rectangle
void BloomNeon::OneColor_NeonBoxes(sf::Vector2f neonPosition, sf::Vector2f neonScale, sf::Color neonColor)
{
	R_neon.setPosition(neonPosition);
	R_neon.setFillColor(neonColor);
	R_neon.setSize(neonScale);
	R_neon.setOrigin(0, 0);
}

//make rectangle with vertex position
void BloomNeon::fourColor_NeonBoxes(sf::Vector2f neonPosition, sf::Vector2f neonScale, sf::Color neonColor1, sf::Color neonColor2, sf::Color neonColor3, sf::Color alphaColor)
{

	//rectangle.getPrimitiveType(sf::);
	////= sf::Vector2f(neonPosition);
	////neon.color = (neonColor);
	////neon.color = sf::Vector3f();
	//neon.scale = sf::Vector2f(neonScale);
	//neon.NeonOrigin = sf::Vector2f(NeonOrigin_x, NeonOrigin_y);


	//neonPosition -> origin point
	sf::Vector2f neonPosition1 = { neonPosition.x - neonScale.x / 2, neonPosition.y - neonScale.y / 2 };   //left and up
	sf::Vector2f neonPosition2 = { neonPosition.x + neonScale.x / 2, neonPosition.y - neonScale.y / 2 };  //right and up
	sf::Vector2f neonPosition3 = { neonPosition.x - neonScale.x / 2, neonPosition.y + neonScale.y / 2 };   //left down
	sf::Vector2f neonPosition4 = { neonPosition.x + neonScale.x / 2, neonPosition.y + neonScale.y / 2 };   //right down


	sf::VertexArray rectangle(sf::Quads, 4);

	rectangle[0].position = sf::Vector2f(neonPosition1);
	rectangle[1].position = sf::Vector2f(neonPosition2);
	rectangle[2].position = sf::Vector2f(neonPosition3);
	rectangle[3].position = sf::Vector2f(neonPosition4);

	rectangle[0].color = neonColor1;
	rectangle[1].color = neonColor2;
	rectangle[2].color = neonColor3;
	rectangle[3].color = alphaColor;

}

//make origin because of NeonOrigin whicj is in fourColor_NeonBoxes function
void BloomNeon::makeOrigin(sf::Vector2f neonPosition, sf::Vector2f neonScale)
{
	NeonOrigin_x = neonPosition.x + neonScale.x / 2;
	NeonOrigin_y = neonPosition.y - neonScale.y / 2;
}

void BloomNeon::bloomEffect([[maybe_unused]]sf::Vector2f neonPosition, [[maybe_unused]] sf::Vector2f neonScale, float neonColor1, float neonColor2, float neonColor3, float alphaColor)
{
	constexpr int slices = 30;
	constexpr int count = slices + 2;
	sf::VertexArray rectangle(sf::TriangleFan, count);

	std::vector<sf::Vector2f> pos_vtx(count);
	std::vector<sf::Color> color_vtx(count);

	pos_vtx[0] = sf::Vector2f{ 0.f, 0.f };

	for (int i = 0; i <= slices; i++)
	{
		color_vtx[i + 1] = sf::Color(static_cast<sf::Uint8>(neonColor1), static_cast<sf::Uint8>(neonColor2), static_cast<sf::Uint8>(neonColor3), static_cast<sf::Uint8>(alphaColor));

		float x = cos(util::to_radians(360.0f / slices) * i);
		float y = sin(util::to_radians(360.0f / slices) * i);

		pos_vtx[i + 1] = sf::Vector2f{ x, y };
	}

}
