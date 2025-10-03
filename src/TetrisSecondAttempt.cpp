// there is a bug where if u keep pressing s sometimes the lower most block of the Iblock atleast disappears into the block below it 
// need to make is to that the O and I tetrimino start from the top most row of the array

// i have not removed some code which is not being used like the colors code and stuff ill just leave it there for now
// incase i need it for later

//have to fix the reset of Otetrimino and Itetrimino

#include <iostream>
#include <raylib.h>
#include <ctime>
#include <cstdlib>
#include "colors.h"
#include "tetriminos.h"
#include "chrono"
#include "players.h"
#include <stdio.h>
#include "buttons.h"
#include "blocks.h"
#include "sounds.h"

Color bgColor = { 0,0,0,255 };
int cellSize = 45;
const int columns = 10;
const int rows = 20;
int max_lvl = 20;
int current_lvl = 1;
int tetrimino_speed = 500;
int offset_sides = 900;
int offset_height = 50;

Player* current_player = &player1;


int state = 0;
enum states { mainMenu, game_choose, players_1, players_2, audio, game_over , exit_screen_1 , exit_screen_2 };


Tetrimino tetriminos[7] = {Otetrimino,Itetrimino,Ttetrimino,Ltetrimino,Jtetrimino,Stetrimino,Ztetrimino};
int grid[20][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};



void updateGrid(Tetrimino&);
void drawCells(block[]);
void drawTetrimino(Tetrimino , block[]);
void rotateTetrimino(Tetrimino&,int);
void moveTetrimino(Tetrimino&, int, int);
bool movementPossible(Tetrimino);
//sending an int as well cause reset tetriminos is called in this function and reset is different for O & I tetriminos
bool block_sit(Tetrimino&, Player&, int);
bool check_end(Tetrimino&);
void reset_tetrimino(Tetrimino& , int);
bool check_interval(int);
void row_complete(Player&);
void update_score(Tetrimino&,Player&);
void draw_sides_1_player(Tetrimino& , block[]);
void draw_sides_2_player(Tetrimino&, block[]);
void end_game_screen_p1();
void end_game_screen_p2();
void reset_grid();
void reset_scores();



int windowWidth = cellSize * columns + offset_sides; // rn it is 1350
int windowHeight = cellSize * rows + offset_height;  // rn it is 950



int main()
{
	//rn width is 1350 and Height 950
	InitWindow(windowWidth, windowHeight, "TETRIS");
	SetTargetFPS(30);
	InitAudioDevice();

	// they werent working when i was declaring them in the sounds headerfile 
	bgMusic audio1("Sounds\\MainTrack.mp3");
	bgMusic audio2("Sounds\\GtaVRadio.mp3");
	//bgMusic audio3("Sounds\\RickRoll.mp3");
	bgMusic audio3("Sounds\\JagaJaga.mp3");
	bgMusic audio4("Sounds\\SigmaBoy.mp3");
	bgMusic audio5("Sounds\\German.mp3");

	Music currentTrack = audio1.soundTrack;

	// This needs to be called once to start the soundTrack then the UpdatMusicStream() must be run on every itteration of the loop to keep it running
	PlayMusicStream(currentTrack);

	srand(time(0));


	//int active_tetrimino = 0;
	//int next_tetrimino = 0;


	// here i am initializing all the buttons in the game i have set their posistions with respect to the 
	// window height and width so that even if i change the dimensions of the window the buttons do not 
	// need to be alligned again and again 
	// all the divisions and multiplications are purely for allignment purposes i have come up with those 
	// specific numbers through trial and error dividing the width by a bigger values moves the button 
	// more to the left and vice versa whereas dividing the height with a bigger number moves the button
	// more upwards

	// also the 2 parameters at the end are for scaling te button acc to my needs, again i have come up with those 
	// specific numbers through trial and error 

	//essentially just took the mainMenu background as a button but wont do anything else with it obv 
	//button mainMenuScreen("Graphics\\MainMenuScreen1.jpg",{0,0}, 1.968,2.47);
	//button mainMenuScreen("Graphics\\MainMenuScreen2.jpeg", { 0,0 }, 1.85, 1.73);
	button mainMenuScreen("Graphics\\MainMenuScreen.png", { 0,0 }, 1, 1.2321660);
	//button playButton("Graphics\\PlayButton.png", { static_cast<float>(windowWidth / 25),static_cast<float>(windowHeight / 1.8) }, 0.3,0.3);
	//button quitButton("Graphics\\QuitButton.png", { 900,450 }, 1, 1);
	//button soundsButton("Graphics\\SoundsButton.png", { 1000,750 }, 0.2, 0.2);
	button playButton("Graphics\\PlayButton.png", { static_cast<float>(windowWidth / 4.3),static_cast<float>(windowHeight / 1.53) }, 1, 1);
	button soundsButton("Graphics\\SoundsButton1.png", { static_cast<float>(windowWidth / 4.3) + 240,static_cast<float>(windowHeight / 1.53) }, 1, 1);
	button quitButton("Graphics\\QuitButton.png", { static_cast<float>(windowWidth / 4.3) + 495,static_cast<float>(windowHeight / 1.53) }, 1, 1);
	button singlePlayerButton("Graphics\\SinglePlayerButton.png", { static_cast<float>(windowWidth / 6), static_cast<float>(windowHeight / 2.8) }, 0.5, 0.5);
	button multiplayerButton("Graphics\\MultiPlayerButton.png", { static_cast<float>(windowWidth / 6 * 3.5),static_cast<float>((windowHeight / 2.8) - 20) }, 0.325, 0.263);
	button audioButton1("Graphics\\AudioButton.png", { static_cast<float>(windowWidth / 4),static_cast<float>(windowHeight / 6.75) }, 1, 1);
	button audioButton2("Graphics\\AudioButton.png", { static_cast<float>(windowWidth / 4),static_cast<float>(windowHeight / 6.75) + 150 }, 1, 1);
	button audioButton3("Graphics\\AudioButton.png", { static_cast<float>(windowWidth / 4),static_cast<float>(windowHeight / 6.75) + 300 }, 1, 1);
	button audioButton4("Graphics\\AudioButton.png", { static_cast<float>(windowWidth / 4),static_cast<float>(windowHeight / 6.75) + 450 }, 1, 1);
	button audioButton5("Graphics\\AudioButton.png", { static_cast<float>(windowWidth / 4),static_cast<float>(windowHeight / 6.75) + 600 }, 1, 1);
	button audioPageXButton("Graphics\\XButton.png", { 0,0 }, 0.15, 0.15);
	button gameChoosePageXButton("Graphics\\XButton.png", { 0,0 }, 0.15, 0.15);
	button mainMenuButtonEndScreen1("Graphics\\MainMenuButton.png", { static_cast<float>(windowWidth / 4.8),static_cast<float>(windowHeight / 1.8) }, 0.28, 0.28);
	button playAgainButtonEndScreen1("Graphics\\PlayAgainButton.png", { static_cast<float>(windowWidth / 1.6),static_cast<float>(windowHeight / 1.65) }, 0.2, 0.2);
	button mainMenuButtonEndScreen2("Graphics\\MainMenuButton.png", { static_cast<float>(windowWidth / 4.8),static_cast<float>(windowHeight / 1.4) }, 0.28, 0.28);
	button playAgainButtonEndScreen2("Graphics\\PlayAgainButton.png", { static_cast<float>(windowWidth / 1.6),static_cast<float>(windowHeight / 1.31) }, 0.2, 0.2);


	// i cannot initialize these outside of some function for some reason unlike i have done with the colors
	block backGroundCell("Graphics\\BackGroundCell.png", 1, 1);
	block orangeBlock("Graphics\\OrangeBlock.png", 0.716667, 0.716667);
	block purpleBlock("Graphics\\PurpleBlock.png", 0.716667, 0.716667);
	block greenBlock("Graphics\\GreenBlock.png", 0.716667, 0.716667);
	block tealBlock("Graphics\\TealBlock.png", 0.716667, 0.716667);
	block redBlock("Graphics\\RedBlock.png", 0.716667, 0.716667);
	block yellowBlock("Graphics\\YellowBlock.png", 0.716667, 0.716667);
	block blueBlock("Graphics\\BlueBlock.png", 0.716667, 0.716667);

	// the grid and the tetrimino arrays are all ints so i can just access what int value is present at the [i][j] index of the
	// grid or tetrimino and then can get the approprioate block for that int value from the array below
	block blocks[] = { backGroundCell,greenBlock, redBlock, orangeBlock,yellowBlock,purpleBlock,tealBlock,blueBlock };

	int next_tetrimino = rand() % 7;
	int active_tetrimino = rand() % 7;

	while (!WindowShouldClose()) {

		UpdateMusicStream(currentTrack);

		BeginDrawing();
		ClearBackground(bgColor);

		if (state == mainMenu)
		{
			//essentially just took the mainMenu background as a button but wont do anything else with it obv no checking for mouseClick
			mainMenuScreen.draw();
			playButton.draw();
			quitButton.draw();
			soundsButton.draw();

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				if (playButton.check_trigger(GetMousePosition())) {
					state = game_choose;
				}
				else if (quitButton.check_trigger(GetMousePosition())) {
					break;
				}
				else if (soundsButton.check_trigger(GetMousePosition())) {
					state = audio;
				}

			}


		}

		else if (state == audio) {

			audioButton1.draw();
			audioButton2.draw();
			audioButton3.draw();
			audioButton4.draw();
			audioButton5.draw();
			audioPageXButton.draw();


			DrawText("Audio 1", (windowWidth / 4) + 250, (windowHeight / 6.75) + 20, 90, WHITE);
			DrawText("Audio 2", (windowWidth / 4) + 250, (windowHeight / 6.75) + 180, 90, WHITE);
			DrawText("Audio 3", (windowWidth / 4) + 250, (windowHeight / 6.75) + 330, 90, WHITE);
			DrawText("Audio 4", (windowWidth / 4) + 250, (windowHeight / 6.75) + 480, 90, WHITE);
			DrawText("Audio 5", (windowWidth / 4) + 250, (windowHeight / 6.75) + 630, 90, WHITE);


			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

				if (audioButton1.check_trigger(GetMousePosition()))
				{
					//stops the previous music
					StopMusicStream(currentTrack);
					//changes current track
					currentTrack = audio1.soundTrack;
					//starts new current track
					PlayMusicStream(currentTrack);
				}
				else if (audioButton2.check_trigger(GetMousePosition()))
				{
					StopMusicStream(currentTrack);
					currentTrack = audio2.soundTrack;
					PlayMusicStream(currentTrack);
				}
				else if (audioButton3.check_trigger(GetMousePosition()))
				{
					StopMusicStream(currentTrack);
					currentTrack = audio3.soundTrack;
					PlayMusicStream(currentTrack);
				}
				else if (audioButton4.check_trigger(GetMousePosition()))
				{
					StopMusicStream(currentTrack);
					currentTrack = audio4.soundTrack;
					PlayMusicStream(currentTrack);
				}
				else if (audioButton5.check_trigger(GetMousePosition()))
				{
					StopMusicStream(currentTrack);
					currentTrack = audio5.soundTrack;
					PlayMusicStream(currentTrack);
				}
				else if (audioPageXButton.check_trigger(GetMousePosition()))
					state = mainMenu;
			}


		}

		else if (state == game_choose) {

			singlePlayerButton.draw();
			multiplayerButton.draw();
			gameChoosePageXButton.draw();

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				if (singlePlayerButton.check_trigger(GetMousePosition()))
				{
					state = players_1;
					reset_scores();
				}
				else if (multiplayerButton.check_trigger(GetMousePosition()))
				{
					state = players_2;
					reset_scores();
				}
				else if (gameChoosePageXButton.check_trigger(GetMousePosition()))
					state = mainMenu;
			}
		}

		else if (state == exit_screen_1) {
			end_game_screen_p1();
			mainMenuButtonEndScreen1.draw();
			playAgainButtonEndScreen1.draw();

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

				if (mainMenuButtonEndScreen1.check_trigger(GetMousePosition())) {
					state = mainMenu;
				}
				else if (playAgainButtonEndScreen1.check_trigger(GetMousePosition())) {
					state = game_choose;
				}

			}

		}
		else if (state == exit_screen_2) {
			end_game_screen_p2();
			mainMenuButtonEndScreen2.draw();
			playAgainButtonEndScreen2.draw();

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

				if (mainMenuButtonEndScreen2.check_trigger(GetMousePosition())) {
					state = mainMenu;
				}
				if (playAgainButtonEndScreen2.check_trigger(GetMousePosition())) {
					state = game_choose;
				}
			}
		}

		else if (state == players_1 || state == players_2)
			{

				drawCells(blocks);

				if (state == players_1)
					draw_sides_1_player(tetriminos[next_tetrimino], blocks);
				else
					draw_sides_2_player(tetriminos[next_tetrimino], blocks);
				//orangeBlock.draw();

				if ((IsKeyPressed(KEY_D) && current_player == &player1) || (IsKeyPressed(KEY_L) && current_player == &player2))
				{
					moveTetrimino(tetriminos[active_tetrimino], 1, 0);
				}
				else if ((IsKeyDown(KEY_S) && current_player == &player1) || (IsKeyDown(KEY_K) && current_player == &player2))
				{
					if (check_interval(100)) {
						moveTetrimino(tetriminos[active_tetrimino], 0, 1);
					}
				}
				else if ((IsKeyPressed(KEY_A) && current_player == &player1) || (IsKeyPressed(KEY_J) && current_player == &player2))
				{
					moveTetrimino(tetriminos[active_tetrimino], -1, 0);
				}
				else if ((IsKeyPressed(KEY_E) && current_player == &player1) || (IsKeyPressed(KEY_O) && current_player == &player2))
				{
					rotateTetrimino(tetriminos[active_tetrimino], 90);
				}
				else if ((IsKeyPressed(KEY_Q) && current_player == &player1) || (IsKeyPressed(KEY_U) && current_player == &player2))
				{
					rotateTetrimino(tetriminos[active_tetrimino], -90);
				}

				if (check_interval(tetrimino_speed)) {

					tetriminos[active_tetrimino].y += 1;
				}

				drawTetrimino(tetriminos[active_tetrimino], blocks);


				if (check_end(tetriminos[active_tetrimino]))
				{
					reset_grid();
					if (state == players_1)
						state = exit_screen_1;
					else if (state == players_2)
						state = exit_screen_2;
				}

				if (block_sit(tetriminos[active_tetrimino], *current_player, active_tetrimino)) {
					active_tetrimino = next_tetrimino;
					next_tetrimino = rand() % 7;

				}

			}

		EndDrawing();

		}
		CloseWindow();
		return 0;

	}

void drawCells(block blocks[]) {


	for (int i = 0; i < rows; i++) {

		for (int j = 0; j < columns; j++) {

			// offset_sides/2 to offset for border to the left
			// offset_height/2 to offset for the border at the top
			 
			//this line was for when i was not using textures for the blocks
			//DrawRectangle(j * cellSize + 1 + offset_sides/2 , i*cellSize+1 + offset_height/2, cellSize-2, cellSize-2, colors[grid[i][j]]); // the -2 creates the grid effect and +1 adjusts the position accoring to the new size 

			// this line takes the block object at the grid[i][j] index of the blocks array and then calls its draw funcion
			blocks[grid[i][j]].draw({ static_cast<float>(j * cellSize + 1 + offset_sides / 2),static_cast<float>(i * cellSize + 1 + offset_height / 2) });


		}
	}
}
void drawTetrimino(Tetrimino tetrimino , block blocks[]) {
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetrimino.structure[i][j] != 0)


				//this line was for when i was not using textures for the blocks
			//DrawRectangle((tetrimino.x + j ) * cellSize + 1 + offset_sides / 2, (tetrimino.y + i) * cellSize + 1 + offset_height / 2, cellSize - 2, cellSize - 2, colors[tetrimino.structure[i][j]]);

				//the line below takes the block class at the tetrimino[i][j] index of the blocks array and then calls the draw function of the class which takes a vector2 as an argument
				blocks[tetrimino.structure[i][j]].draw({static_cast<float>((tetrimino.x + j) * cellSize + 1 + offset_sides / 2 ),static_cast<float>((tetrimino.y + i) * cellSize + 1 + offset_height / 2 )});
			//else { DrawRectangle((tetrimino.x + j) * cellSize + 1, (tetrimino.y + i) * cellSize + 1, cellSize - 2, cellSize - 2, PINK); }
		}
	}
	

}
void rotateTetrimino(Tetrimino& tetrimino, int rotation) {
	/*Creates a new tetriminos which is rotated and then equates it
	to the current active tetrimino's original*/

	int rotated_structure[4][4];
	int original_structure[4][4];

	for (int i = 0; i < 4; i++) { // saves the original structure
		for (int j = 0; j < 4; j++) {
			original_structure[i][j] = tetrimino.structure[i][j];
		}
	}

	if (rotation == 90) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				rotated_structure[i][j] = tetrimino.structure[4 - 1 - j][i];
			}
		}
		tetrimino.state += 1;
	}
	else if (rotation == -90) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				rotated_structure[i][j] = tetrimino.structure[j][4 - 1 - i];
			}
		}
		tetrimino.state -= 1;
	}

	for (int i = 0; i < 4; i++) { // equates the rotated structure to the tetrimino structure
		for (int j = 0; j < 4; j++) {
			tetrimino.structure[i][j] = rotated_structure[i][j];
		}
	}
	/*Now here if the movementpossible function returns false, it means that the
	rotated structure and the grid structures are overlapping, so it will now allow
	the rotation to take place and equate the tetrimino struction to what it was 
	originally*/
	if (!movementPossible(tetrimino))
	{
		for (int i = 0; i < 4; i++) { // equates the rotated structure to the tetrimino structure
			for (int j = 0; j < 4; j++) {
				tetrimino.structure[i][j] = original_structure[i][j];
			}
		}
	}


}
void moveTetrimino(Tetrimino& tetrimino, int dx, int dy) {

	int initial_x = tetrimino.x;
	int initial_y = tetrimino.y;

	tetrimino.x += dx;
	tetrimino.y += dy;

	if (!movementPossible(tetrimino)) {
		tetrimino.x = initial_x;
		tetrimino.y = initial_y;
	}

}
bool movementPossible(Tetrimino tetrimino){

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (tetrimino.structure[i][j] != 0 && (grid[i + tetrimino.y][j + tetrimino.x] != 0 || j + tetrimino.x >= columns || i + tetrimino.y >= rows || j + tetrimino.x < 0) )
				return false;
		}
	}
	return true;
}
bool block_sit(Tetrimino &tetrimino,Player& player , int active_tetrimino){
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			 
			if (tetrimino.structure[i][j] != 0) {
				if (grid[i + tetrimino.y + 1][j + tetrimino.x] != 0 || tetrimino.y + i +1 >= rows) {
					update_score(tetrimino,player);
					updateGrid(tetrimino);
// checks if a row has been completed and if yes then adds up the score of the currentplayer
					row_complete(*current_player);
					reset_tetrimino(tetrimino, active_tetrimino);
// if game mode is multiplaye changes the turn as soon as the block sits 
					if (state == players_2) {
						if (current_player == &player1)
							current_player = &player2;
						else
							current_player = &player1;
					}
					return true;
				}
			}
		}
	}

	return false;
}
void update_score(Tetrimino& tetrimino, Player& player) {
	int blocks_adjacent = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			if (tetrimino.structure[i][j] != 0) {
				
				int gridY = i + tetrimino.y;
				int gridX = j + tetrimino.x;

				if (gridY < rows-1 && grid[gridY + 1][gridX] != 0)
					blocks_adjacent++;
				if (gridY > 0 && grid[gridY - 1][gridX] != 0)
					blocks_adjacent++;
				if (gridX < columns -1 && grid[gridY][gridX + 1] != 0)
					blocks_adjacent++;
				if (gridX > 0 && grid[gridY][gridX - 1] != 0)
					blocks_adjacent++;
			}
		}
	}
	player.score += blocks_adjacent *10 ;
}
void reset_tetrimino(Tetrimino& tetrimino, int active_tetrimino) {
	
	if (active_tetrimino == 0|| active_tetrimino == 1) {
		tetrimino.x = 3;
		tetrimino.y = -1;
	}
	else {
		tetrimino.x = 3;
		tetrimino.y = 0;
	}
	int rotated_structure[4][4];


			if (tetrimino.state % 4 == 1 || tetrimino.state % 4 == -3) { // will rotate the tetrimino anti clockwise once to get to the original position
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						rotated_structure[i][j] = tetrimino.structure[j][4 - 1 - i];
					}
				}
				for (int i = 0; i < 4; i++) { // equates the rotated structure to the tetrimino structure
					for (int j = 0; j < 4; j++) {
						tetrimino.structure[i][j] = rotated_structure[i][j];
					}
				}
			}

			else if (tetrimino.state % 4 == 2 || tetrimino.state % 4 == -2) { // will rotate the tetrimino 180 degrees
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						rotated_structure[i][j] = tetrimino.structure[4 - 1 - i][4 - 1 - j];
					}
				}
				for (int i = 0; i < 4; i++) { // equates the rotated structure to the tetrimino structure
					for (int j = 0; j < 4; j++) {
						tetrimino.structure[i][j] = rotated_structure[i][j];
					}
				}
			}
			else if (tetrimino.state % 4 == 3 || tetrimino.state % 4 == -1) { // will rotate the tetrimino clockwise once to get to the original position
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 4; j++) {
						rotated_structure[i][j] = tetrimino.structure[4 - 1 - j][i];
					}
				}
				for (int i = 0; i < 4; i++) { // equates the rotated structure to the tetrimino structure
					for (int j = 0; j < 4; j++) {
						tetrimino.structure[i][j] = rotated_structure[i][j];
					}
				}
			}

			tetrimino.state = 0;
		}
bool check_end(Tetrimino& tetrimino) {

	for (int i = 0; i < 4; i++) 
		for (int j = 0; j < 4; j++)
			if (tetrimino.structure[i][j] != 0 && (i + tetrimino.y <= 0 && grid[i + tetrimino.y + 1][j + tetrimino.x] != 0))
				return true;
	return false;
}
bool check_interval(int time) {
	static auto last_time = std::chrono::steady_clock::now(); // Static to retain value across calls
	auto current_time = std::chrono::steady_clock::now();

	// Calculate the time difference in milliseconds
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time);

	if (duration.count() >= time) {
		last_time = current_time; // Update the last recorded time
		return true;
	}
	return false;
}
void updateGrid(Tetrimino& tetrimino) {


	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 4; j++) {
			if (tetrimino.structure[i][j] != 0)
			grid[i+tetrimino.y][j+tetrimino.x] = tetrimino.structure[i][j];

		}
	}

}
void row_complete(Player &player) {

	int temp_grid[rows][columns]; // Temporary grid to store updated state

	// Initialize temp_grid with the current grid
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			temp_grid[i][j] = grid[i][j];
		}
	}

	// Check for complete rows
	for (int i = 0; i < rows; i++) {
		bool row_filled = true;

		// Check if the row is completely filled
		for (int j = 0; j < columns; j++) {
			if (grid[i][j] == 0) { // Empty block found
				row_filled = false;
				break;
			}
		}

		// If the row is filled, clear it and shift everything above downward
		if (row_filled) {

			// when row filled, level will increase and tetrimino speed will increase
			if (current_lvl < max_lvl)
			{
				current_lvl++;
				tetrimino_speed -= 17.5; // 17.5 so it goes from 500 to 150 in 20 levels
			}


			// Shift rows down
			player.score += columns*10*2;
			for (int k = i; k > 0; k--) {
				for (int j = 0; j < columns; j++) {
					grid[k][j] = grid[k - 1][j];
				}
			}

			// Clear the topmost row
			for (int j = 0; j < columns; j++) {
				grid[0][j] = 0;
			}

			// After shifting, check the same row again since it now contains the row above
			i--;
		}
	}

	


}
void draw_sides_1_player(Tetrimino& next_tetrimino, block blocks[]) {

	// the positions of all the texts on the sides have been innitialized here for making it easier to read
	int scoreText_pos_x = (cellSize * columns) + (offset_sides / 2) + (offset_sides / 8); // first term gets the grid width, second the left offset to add up to reach the start of right offset then certain amount it added in to move more right
	int scoreText_pos_y = (cellSize * rows) / 5; // height of grid divided by a certain number
	int score_pos_x = (cellSize * columns) + (offset_sides / 2) + (offset_sides / 6);  // first term gets the grid width, second the left offset to add up to reach the start of right offset then certain amount it added in to move more right
	int score_pos_y = (cellSize * rows) / 3.3; // height of grid divided by a certain number
	int levelText_pos_x = (cellSize * columns) + (offset_sides / 2) + (offset_sides / 8);
	int levelText_pos_y = (cellSize * rows) / 1.8;
	int level_pos_x = (cellSize * columns) + (offset_sides / 2) + (offset_sides / 6);
	int level_pos_y = (cellSize * rows) / 1.5;
	int nextText_pos_x = offset_sides / 6.6;
	int nextText_pos_y = (cellSize * rows) / 2.7;


	DrawText("SCORE", scoreText_pos_x ,scoreText_pos_y , 60, white);
	char str1[20];
	_itoa_s(player1.score, str1, 10);
	DrawText(str1, score_pos_x, score_pos_y, 70, white);

	DrawText("LEVEL", levelText_pos_x,levelText_pos_y , 60, white);
	char str2[20];
	_itoa_s(current_lvl, str2, 10);
	DrawText(str2, level_pos_x, level_pos_y, 70, white);

	DrawText("NEXT",  nextText_pos_x,nextText_pos_y , 60, white);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (next_tetrimino.structure[i][j] != 0)
				// w/o the -12 and +100 the block would be printed on top of the nexttext but they create an offset 
			//DrawRectangle( (j * cellSize + 1) + nextText_pos_x - 12, (i * cellSize + 1) + nextText_pos_y + 100, cellSize-2, cellSize-2, colors[next_tetrimino.structure[i][j]]);
				blocks[next_tetrimino.structure[i][j]].draw({ static_cast<float>((j * cellSize + 1) + nextText_pos_x - 12) ,static_cast<float>((i * cellSize + 1) + nextText_pos_y + 100) });
		
		
		}
	}
}
void draw_sides_2_player(Tetrimino &next_tetrimino, block blocks[]) {

	int scoresText_pos_x = offset_sides / 9; 
	int scoresText_pos_y = (cellSize * rows) / 6; // height of grid divided by a certain number
	int player1Text_pos_x = offset_sides / 9;
	int player1Text_pos_y = (cellSize * rows) / 3;
	int player2Text_pos_x = offset_sides / 9;
	int player2Text_pos_y = (cellSize * rows) / 1.7;
	int player1_score_pos_x = player1Text_pos_x;
	int player1_score_pos_y = (cellSize * rows) / 2.3;
	int player2_score_pos_x = player2Text_pos_x;
	int player2_score_pos_y = (cellSize * rows) / 1.44;

	int levelText_pos_x = (cellSize * columns) + (offset_sides / 2) + (offset_sides / 8);
	int levelText_pos_y = (cellSize * rows) / 1.6;
	int level_pos_x = (cellSize * columns) + (offset_sides / 2) + (offset_sides / 6);
	int level_pos_y = (cellSize * rows) / 1.3;
	int nextText_pos_x = (cellSize * columns) + (offset_sides / 2) + (offset_sides / 8); // first term gets the grid width, second the left offset to add up to reach the start of right offset then certain amount it added in to move more right
	int nextText_pos_y = (cellSize * rows) / 4.8;

	DrawText("NEXT", nextText_pos_x, nextText_pos_y, 60, white);

	if (current_player == &player1)
		DrawText("Player 1", player1Text_pos_x,player1Text_pos_y, 60, green);
	else 
		DrawText("Player 1", player1Text_pos_x, player1Text_pos_y, 60, white);

	if (current_player == &player2)
		DrawText("Player 2", player2Text_pos_x, player2Text_pos_y, 60, green);
	else
		DrawText("Player 2", player2Text_pos_x, player2Text_pos_y, 60, white);

	char str1[20];
	_itoa_s(player1.score, str1, 10);
	DrawText(str1, player1_score_pos_x, player1_score_pos_y, 70, white);

	char str2[20];
	_itoa_s(player2.score, str2, 10);
	DrawText(str2, player2_score_pos_x, player2_score_pos_y, 70, white);


	DrawText("LEVEL", levelText_pos_x, levelText_pos_y, 60, white);
	char str3[20];
	_itoa_s(current_lvl, str3, 10);
	DrawText(str3, level_pos_x, level_pos_y, 70, white);

	DrawText("SCORES", scoresText_pos_x, scoresText_pos_y, 60, white);


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (next_tetrimino.structure[i][j] != 0)
				// w/o the -12 and +100 the block would be printed on top of the nexttext but they create an offset 
			//DrawRectangle( (j * cellSize + 1) + nextText_pos_x - 12, (i * cellSize + 1) + nextText_pos_y + 100, cellSize-2, cellSize-2, colors[next_tetrimino.structure[i][j]]);
				blocks[next_tetrimino.structure[i][j]].draw({ static_cast<float>((j * cellSize + 1) + nextText_pos_x + 12) ,static_cast<float>((i * cellSize + 1) + nextText_pos_y + 100) });


		}
	}
}
void end_game_screen_p1() {
	
	DrawText("GAME OVER!!!", windowWidth/4, windowHeight / 5 , 100, WHITE);
	DrawText("Score: ", windowWidth / 4, windowHeight / 2.5, 100, WHITE);

	char str1[20];
	_itoa_s(player1.score, str1, 10);
	DrawText(str1, windowWidth / 1.8, windowHeight / 2.5, 100, WHITE);


}
void end_game_screen_p2() {

	DrawText("Scores", windowWidth / 3, windowHeight / 10, 100, WHITE);
	DrawText("Player 1", windowWidth / 7, windowHeight / 4, 100, WHITE);
	DrawText("Player 2", windowWidth / 1.8, windowHeight / 4, 100, WHITE);

	char str1[20];
	char str2[20];

	_itoa_s(player1.score, str1, 10);
	_itoa_s(player2.score, str2, 10);

	DrawText(str1, windowWidth / 7, windowHeight / 2.5, 100, WHITE);
	DrawText(str2, windowWidth / 1.8, windowHeight / 2.5, 100, WHITE);


	if (player1.score != player2.score) {
		
		if (player1.score > player2.score)
			DrawText("PLAYER 1 WINS!!!!", windowWidth / 6, windowHeight / 1.7, 100, green);
		else 
			DrawText("PLAYER 2 WINS!!!!", windowWidth / 6, windowHeight / 1.7, 100, green);
	}
	else {
		DrawText("DRAW!!!!!!", windowWidth / 3, windowHeight / 1.7, 100, RED);
	}

}
void reset_grid() {


	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			grid[i][j] = 0;

}
void reset_scores() {

	player1.score = 0;
	player2.score = 0;

	current_lvl = 1;
	tetrimino_speed = 500;

	current_player = &player1;
}


//\n