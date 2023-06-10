#include "UI.h"
#include "GameObjectTypes.h"


void UI::Draw(mat3 NDCmatrix)
{
	//background.Draw(mat3::build_translation(0, 0), true, Alaha / 255);
	//:Draw(mat3 displayMatrix)
	NDCmatrix = UI::ToNDC(GetPosition());

	Sprite* spritePtr = GetGOComponent<Sprite>();
	//spritePtr->Draw(re);
//	spritePtr->Draw( NDCmatrix);
	
	spritePtr->Draw_Animation_object(NDCmatrix, { GetScale().x,GetScale().y}, 0.f, 1.f);
//	spritePtr->Draw(mat3::build_translation(0.f, 0.f));

}

void UI::Draw(float scroll)
{
	mat3 displayMatrix;
	displayMatrix = UI::ToNDC(DataType::fvec2(GetPosition().x, GetPosition().y));
	displayMatrix *= mat3::build_translation({ 0.0f, scroll });

	Sprite* spritePtr = GetGOComponent<Sprite>();

	spritePtr->Draw_Animation_object(displayMatrix, { GetScale().x, GetScale().y }, 0.f, 1.0f);
	
}

mat3 UI::ToNDC(DataType::fvec2 pos)
{
	//mat3 m
	//{
	//	0.0015384f		   ,	0.f		   ,	-1.f,
	//	0.f		   ,	-0.0025f		   ,	1.f,
	//	0.f,	0.f,	1.f
	//};

	mat3 m
	{
		2.f/1300.f		   ,	0.f		   ,	-1.f,
		0.f		   ,	-2.f/800.f		   ,	1.f,
		0.f,	0.f,	1.f
	};


	vec3 v{ pos.x,pos.y,1 };


	v = { (m.elements[0][0] * v.x) + (m.elements[0][1] * v.y) + (m.elements[0][2] * v.z),
	(m.elements[1][0] * v.x) + (m.elements[1][1] * v.y) + (m.elements[1][2] * v.z),
	(m.elements[2][0] * v.x) + (m.elements[2][1] * v.y) + (m.elements[2][2] * v.z) };



	mat3 re = mat3::build_translation(v.x, v.y);

	return re;
}

GameObjectType UI::GetObjectType()
{
	return GameObjectType::UI;
}
