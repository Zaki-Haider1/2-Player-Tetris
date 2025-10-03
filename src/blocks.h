#pragma once
#include <raylib.h>

class block {
public:

	block(const char* , float,float);
	~block();

	void draw(Vector2);
	Texture2D texture;

private:
	
};


block::block(const char *imagePath, float scaleWidth, float scaleHeight) {


	texture = LoadTexture(imagePath);

	Image image = LoadImageFromTexture(texture);

	ImageResize(&image, static_cast<int>(image.width * scaleWidth), static_cast<int>(image.height * scaleHeight));

	texture = LoadTextureFromImage(image);

}

void block::draw(Vector2 position) {

	DrawTexture(texture, position.x, position.y, WHITE);

}
block::~block() {
	UnloadTexture(texture);
}

/*
block orangeBlock("Graphics\\OrangeBlock.png",0.716667, 0.716667);
block purpleBlock("Graphics\\PurpleBlock.png", 0.716667, 0.716667);
block greenBlock("Graphics\\GreenBlock.png", 0.716667, 0.716667);
block tealBlock("Graphics\\TealBlock.png", 0.716667, 0.716667);
block redBlock("Graphics\\RedBlock.png", 0.716667, 0.716667);
block yellowBlock("Graphics\\YellowBlock.png", 0.716667, 0.716667);
block blueBlock("Graphics\\BlueBlock.png", 0.716667, 0.716667);
*/