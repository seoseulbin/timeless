#include"Font.h"
#include"Engine.h"

Font::Font(const std::string filePath)
{
	image.loadFromFile(filePath);
	x_width = 0;
	y_width = 0;
}

void Font::Load( unsigned int x, unsigned int y)
{
	
	y_width = 0;
	StringTexture.create(x, y); // x * y 크기의 큰 비어있는 아무것도 없는 텍스쳐 생성.
	x_width = 0;
}
// 기본 구조
// 각각의 단어를 작은 텍스쳐로 가정하고
// 완성된 문장을 큰 텍스쳐라 가정했을 때,
// 작은 텍스쳐로 이루어진 큰 텍스쳐라 생각하면 됨.

void Font::Draw(DataType::ivec2 texelPos, DataType::ivec2 framesize)
{
	sf::IntRect settings(texelPos.x, texelPos.y, framesize.x, framesize.y);//세팅 값을 설정함으로써 이미지의 x,y 좌표 위치에 framesize x, y의 크기만큼 잘라내기 위함
	texture.loadFromImage(image, settings);// 폰트 이미지에서 세팅값에 따라 자른 이미지를 작은 텍스쳐로 저장.
	StringTexture.update(texture,x_width,0); // x_width , 0위치에 이미지에서 잘라온 작은 텍스쳐를 큰 텍스쳐에 업데이트
	x_width += framesize.x; // 이어서 그리기 위해 x_width의 값에 잘라온 프레임 사이즈 x값을 더 함으로써 다음 x_width의 위치에 다른 단어가 오게끔 만들기 위함.
}
// 하나하나 텍스쳐를 그려도 되는데 그렇게 하니 이미지 깨짐 현상 발생 -> 따라서 각각의 텍스쳐들을 하나의 큰 텍스쳐에 그려놓은 후 그 전체 텍스쳐를 리턴함.
sf::Color Font::GetPixel(unsigned int x, unsigned int y) 
{
	return image.getPixel(x, y);
}
// x,y 위치의 픽셀 색깔 값을 리턴.
// CS230버전은 각각의 rgb값을 비트이동을 이용하여 값을 도출 -> 두들의 이미지는 [] 오퍼레이터를 지원함으로써 가능한 일.
// sfml의 텍스쳐나 이미지는 []오퍼레이터를 지원하지 않기에, 직접적으로 픽셀 값을 리턴시키는 getPixel(x,y)를 이용했음.
// sfml의 getPixel(x,y) 는 x,y위치의 픽셀 컬러값을 리턴함.

DataType::ivec2 Font::GetSize()
{
	int x = image.getSize().x;
	int y = image.getSize().y;

	return { x,y };
}

sf::Texture Font::GetTexture()
{
	return StringTexture; // 완성된 문장의 텍스쳐를 리턴
}

