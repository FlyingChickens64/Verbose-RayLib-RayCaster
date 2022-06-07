#include <raylib.h> // RayLib Header File, Manages The Window And Input.
#include <math.h> // Math Header File, Needed For Sin And Cos Functions.

int main() { // The Main Function, Return An Integer On Exit.
	float screenX = 0; // Column Of The Screen Being Drawn.
	float screenW = 512; // The Window's Width.
	float screenH = 512; // The Window's Height.
	float screenR = screenH/screenW; // Screen Height To Width Ratio, Negates The Stretch In Ratios That Are Not 1:1.
	InitWindow(screenW, screenH, "RayLib RayCaster"); // Create The Window.
	float playerX = 4; // The Player's X Position.
	float playerY = 2; // The Player's Y Position.
	float playerA = 0; // The Player's Viewing Angle.
	float playerM = 0.05; // The Player's Movement Speed.
	float playerT = 0.05; // The Player's Turning Speed.
	float rayX = 0; // The Ray's X Position.
	float rayY = 0; // The Ray's Y Position.
	float rayA = 0; // The Ray's Angle.
	float rayD = 0; // The Ray's Distance.
	float rayC = 8; // Maximum Distance To Cast For.
	float rayQ = 0.01; // How Far To Step While Casting.
	int lineH = 0; // Height Of The Line To Draw.
	int lineT = 0; // Start Of The Line On Screen.
	int lineB = 0; // End Of The Line On Screen.
	int map[8][8] = { // The Map, Initialized As An Integer Array.
		1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,1,
		1,1,0,0,0,0,0,1,
		1,0,0,0,1,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,1,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};
	SetTargetFPS(60); // Run The Game At 60 FPS.
	while(!WindowShouldClose()) { // While The Game Is Still Running.
		if(IsKeyDown(KEY_W) && map[(int)(playerX + cos(playerA) * playerM)][(int)(playerY + sin(playerA) * playerM)] == 0) { // If The W Key Was Pressed, Make Sure There Is Nothing In Front Of The Player.
			playerX += cos(playerA) * playerM; // Increase The Player's X Position And Take Into Account Where The Player Is Looking.
			playerY += sin(playerA) * playerM; // Increase The Player's Y Position And Take Into Account Where The Player Is Looking.
		}
		if(IsKeyDown(KEY_A) && map[(int)(playerX + sin(playerA) * playerM)][(int)(playerY - cos(playerA) * playerM)] == 0) { // If The A Key Was Pressed, Make Sure There Is Nothing Left Of The Player.
			playerX += sin(playerA) * playerM; // Increase The Player's X Position And Take Into Account Where The Player Is Looking.
			playerY -= cos(playerA) * playerM; // Decrease The Player's Y Position And Take Into Account Where The Player Is Looking.
		}
		if(IsKeyDown(KEY_S) && map[(int)(playerX - cos(playerA) * playerM)][(int)(playerY - sin(playerA) * playerM)] == 0) { // If The S Key Was Pressed, Make Sure There Is Nothing Behind The Player.
			playerX -= cos(playerA) * playerM; // Decrease The Player's X Position And Take Into Account Where The Player Is Looking.
			playerY -= sin(playerA) * playerM; // Decrease The Player's Y Position And Take Into Account Where The Player Is Looking.
		}
		if(IsKeyDown(KEY_D) && map[(int)(playerX - sin(playerA) * playerM)][(int)(playerY + cos(playerA) * playerM)] == 0) { // If The D Key Was Pressed, Make Sure There Is Nothing Right Of The Player.
			playerX -= sin(playerA) * playerM; // Decrease The Player's X Position And Take Into Account Where The Player Is Looking.
			playerY += cos(playerA) * playerM; // Increase The Player's Y Position And Take Into Account Where The Player Is Looking.
		}
		if(IsKeyDown(KEY_LEFT)) playerA -= playerT; // If The Left Key Was Pressed, Decrease The Player's Viewing Angle.
		if(IsKeyDown(KEY_RIGHT)) playerA += playerT; // If The Right Key Was Pressed, Increase The Player's Viewing Angle.
		BeginDrawing(); // Tell RayLib To Start Drawing.
		ClearBackground(BLACK); // Clear The Screen To Black.
		for(screenX = 0; screenX < screenW; screenX++) { // For Every Column On The Screen.
			rayA = playerA - 0.5 + screenX / screenW; // Set The Ray's Angle Offset Based On The Player's View Position And Column On Screen Compared To The Screen's Width, This Equates to A ~90° FOV.
			for(rayD = 0; rayD < rayC; rayD += rayQ) { // Until The Ray Has Not Reached The Maximum Distance, Increase The Ray Distance By The Stepping Distance.
				rayX = playerX + rayD * cos(rayA); // The Ray's X Position Based On The Player's X Position, Where The Ray Is Headed, And How Far The Ray Has Gone.
				rayY = playerY + rayD * sin(rayA); // The Ray's Y Position Based On The Player's Y Position, Where The Ray Is Headed, And How Far The Ray Has Gone.
				if(map[(int)rayX][(int)rayY]) { // If The Ray's Current Position Intersects With A Wall.
					lineH = screenH / screenR / (rayD * cos(rayA - playerA)); // How High The Line Should Be On The Screen Based On The Ray's Distance Compared To The Screen's Height, The Screen's Height To Width Ratio, And A Formula To Negate The FishEye Effect.
					lineT = -lineH / 2 + screenH / 2; // Start Of The Line To Be Drawn On The Screen.
					lineB = lineH / 2 + screenH / 2; // End Of The Line To Be Drawn On The Screen.
					DrawLine(screenX, lineT, screenX, lineB, WHITE); // Draw A White Line On Screen With The Coordinates Defined Previously.
					break; // Stop Casting For This Column, A Wall Has Already Been Hit.
				}
			}
		}
		DrawFPS(0, 0); // Display Current FPS In The Top Left.
		EndDrawing(); // Tell RayLib To Stop Drawing.
	}
	return 0; // Tell The System That The Program Exited Successfully.
}
