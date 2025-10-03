#pragma once
#include <raylib.h>


class button {

public:

	button(const char*, Vector2, float, float);

	~button();

	void draw();
	bool check_trigger(Vector2);

private:
	
	Texture2D texture;
	Vector2 position;
	Rectangle rectangle;

};

button::button(const char *imagePath, Vector2 position, float scaleWidth , float scaleHeight) {

	texture = LoadTexture(imagePath);
	this  -> position = position;

	Image image = LoadImageFromTexture(texture);


	ImageResize(&image, static_cast<int>(image.width * scaleWidth), static_cast<int>(image.height * scaleHeight));

	texture = LoadTextureFromImage(image);

	rectangle = {position.x,position.y,float(image.width),float(image.height)};

}

button::~button() {
	UnloadTexture(texture);
}

void button::draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
}

bool button::check_trigger(Vector2 mousePosition) {
	if (CheckCollisionPointRec(mousePosition, rectangle)) {
		return true;
	}
	return false;
}