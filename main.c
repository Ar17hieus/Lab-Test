#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Lab 4");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    Model model[3];
    model[0] = LoadModel("resources/models/obj/castle.obj");    // Load model 1
    model[1] = LoadModel("resources/models/obj/market.obj");    // Load model 2
                 
    Texture2D texture = LoadTexture("resources/models/obj/castle_diffuse.png"); // Load model texture 1 
    model[0].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;            // Set map diffuse texture 1 

    texture = LoadTexture("resources/models/obj/market_diffuse.png");
    model[1].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; 

    Vector3 position[3];
    // Set model position 1
    position[0].x = 0.0f; 
    position[0].y = 0.0f; 
    position[0].z = 0.0f;    
    
    // Set model position 2
    position[1].x = 20.0f; 
    position[1].y = 0.0f; 
    position[1].z = 20.0f; 

    BoundingBox bounds[3];

    Vector3 modelSize[3];

    modelSize[0].x = 30.0f;
    modelSize[0].y = 30.0f;
    modelSize[0].z = 30.0f;

    modelSize[1].x = 20.0f;
    modelSize[1].y = 25.0f;
    modelSize[1].z = 20.0f;


    // NOTE: bounds are calculated from the original size of the model,
    // if model is scaled on drawing, bounds must be also scaled

    SetCameraMode(camera, CAMERA_FREE);     // Set a free camera mode

    int selected = 3;          // Selected object flag
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);
        
        // Set model bounds 1
        bounds[0]= (BoundingBox){(Vector3){position[0].x - modelSize[0].x/2, position[0].y - modelSize[0].y/20, position[0].z - modelSize[0].z/2},
                                  (Vector3){position[0].x + modelSize[0].x/2, position[0].y + modelSize[0].y, position[0].z + modelSize[0].z/2}};
                                
                                 
        // Set model bounds 2
        bounds[1]= (BoundingBox){(Vector3){position[1].x - modelSize[1].x/2, position[1].y - modelSize[1].y/10, position[1].z - modelSize[1].z/2},
                                (Vector3){position[1].x + modelSize[1].x/2, position[1].y + modelSize[1].y/2, position[1].z + modelSize[1].z/2}};

        // Select model on mouse click
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (GetRayCollisionBox(GetMouseRay(GetMousePosition(), camera), bounds[0]).hit)
            {
                selected = 0;
            } 
            else if(GetRayCollisionBox(GetMouseRay(GetMousePosition(), camera), bounds[1]).hit)
            {
                selected = 1;
            } 
            else selected = 3;
        }


        //Move model input
       if (IsKeyDown(KEY_W))
       {
            position[selected].z ++;
       }
       else if(IsKeyDown(KEY_S))
       {
            position[selected].z --;
       }
       
       
       if (IsKeyDown(KEY_A))
       {
            position[selected].x ++;
       }
       else if(IsKeyDown(KEY_D))
       {
            position[selected].x --;
       }

       
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModel(model[0], position[0], 1.0f, WHITE);   
                DrawModel(model[1], position[1], 1.0f, WHITE);       // Draw 3d model with texture

                DrawGrid(20, 10.0f);         // Draw a grid

                if (selected == 0) DrawBoundingBox(bounds[0], GREEN);  
                else if (selected == 1) DrawBoundingBox(bounds[1], GREEN); // Draw selection box
             
            EndMode3D();

            if (selected != 3) 
            {
                DrawText("MODEL SELECTED", GetScreenWidth() - 110, 10, 10, GREEN);

            }
            DrawText("(c) Castle 3D model by Alberto Cano", screenWidth - 200, screenHeight - 20, 10, GRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);     // Unload texture
    UnloadModel(model[0]); 
    UnloadModel(model[1]);        // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}