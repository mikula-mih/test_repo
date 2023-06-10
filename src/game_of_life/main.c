#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

int main(void)
{
  int screen_width = 800;
  int screen_height = 600;

  InitWindow(screen_width, screen_height, "SmoothLife GPU");
  SetTargetFPS(60);

  Image image = GenImagePerlinNoise(screen_width, screen_height, 0, 0, 2.0f);
  // Image image = GenImageCellular(screen_width, screen_height, screen_width/6);
  // Image image = GenImageWhiteNoise(screen_width, screen_height, .5f);
  
  // Texture2D texture = LoadTextureFromImage(image);

  RenderTexture2D texture = LoadRenderTexture(screen_width, screen_height);
  UpdateTexture(texture.texture, image.data);

  Shader shader = LoadShader(NULL, "./smoothlife.fs");
  
  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(RED);
      BeginShaderMode(shader);
      DrawTexture(texture.texture, 0, 0, BLUE);
      EndShaderMode();
    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
