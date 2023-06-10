#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

int main(void)
{
  int screen_width = 800;
  int screen_height = 600;

  InitWindow(screen_width, screen_height, "SmoothLife GPU");
  SetTargetFPS(60);

  Image image = GenImagePerlinNoise(screen_width, screen_height, 0, 0, 5.0f);
  // Image image = GenImageCellular(screen_width, screen_height, screen_width/6);
  // Image image = GenImageWhiteNoise(screen_width, screen_height, .5f);
  
  RenderTexture2D state[2];
  state[0] = LoadRenderTexture(screen_width, screen_height);
  state[1] = LoadRenderTexture(screen_width, screen_height);
  UpdateTexture(state[0].texture, image.data);

  Shader shader = LoadShader(NULL, "./smoothlife.fs");
  
  size_t i = 0; // swap between 0, 1 by using i = 1 - i;

  while (!WindowShouldClose()) {
    BeginTextureMode(state[1 - i]);
      ClearBackground(BLACK);
      BeginShaderMode(shader);
        DrawTexture(state[i].texture, 0, 0, BLUE);
      EndShaderMode();
    EndTextureMode();

    BeginDrawing();
      ClearBackground(BLACK);
      DrawTexture(state[1 - i].texture, 0, 0, BLUE);
    EndDrawing();

    i = 1 - i; // swap between 0, 1
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
