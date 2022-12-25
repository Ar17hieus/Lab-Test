#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "raygui.h"

struct objectData
{
    Model model;
    Color color;
    Vector3 position;
    BoundingBox bounds;
    Vector3 size;
    float scale;
    bool isSelected;
};


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Lab Test 2");



    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type


    //Misc Variable
    int selectedType = 0;
    int selectedId = 0;
    bool currentlySelecting = false;
    bool isGUIOpen = false;

    /** ======================================================================
    INFO
    HOW TO ADD OBJECT
    1)Add variable to set max object
    2)Load Models
    3)Load Texture
    4)Set Model's Default Position
    5)Set Model's Size (Used to create bounding box)
    6)Set Model's default value (for colors and isSelected)
  
    ARRAY GUIDE
    object[x][y];
    // x = object type (chair,table,etc2)
    // y = object id (chair1,chair2,chair3, etc2)

    Current Models
    [0] - Tables
    ======================================================================**/

    //Declare Object
    struct objectData object[3][10];

    //total Objects
    int totalType = 1;
    int totalTable = 3;

    
    //Load Models
    //Tables
    Model tempModel;

    tempModel = LoadModel("models/table.obj");
    for(int i = 0; i<totalTable; i++)
    {
        object[0][i].model = tempModel; 
        object[0][i].scale = 0.1f;
    }
    

    //Loads Texture
    Texture2D tempTexture = LoadTexture("resources/models/obj/castle_diffuse.png"); // Load model texture 1 

    tempTexture = LoadTexture("resources/table/tex/WoodSeemles1.png");
    object[0][0].model.materials[0].maps[MATERIAL_MAP_OCCLUSION].texture = tempTexture; 
    
    
    // Set model position
    object[0][0].position = (Vector3){-10,6,30};
    object[0][1].position = (Vector3){-10,6,0};
    object[0][2].position = (Vector3){-10,6,-30};


    // Set model Size (for bounding box)
    for (int i = 0; i < totalTable; i++)
    {
        object[0][i].size = (Vector3){15,15,20};
    }
    

    // set Object's default values
    for (int i = 0; i < totalTable; i++)
    {
        object[0][i].color= WHITE;
        object[0][i].isSelected= false;
    }

  
    SetCameraMode(camera, CAMERA_FREE);     // Set a free camera mode

    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);
        

        //Set bounding Box
        for(int i = 0; i < totalTable; i++)
        {
            object[0][i].bounds = (BoundingBox){(Vector3){ object[0][i].position.x -  object[0][i].size.x/2,  object[0][i].position.y - object[0][i].size.y/2,  object[0][i].position.z -  object[0][i].size.z/2 },
                                        (Vector3){ object[0][i].position.x +  object[0][i].size.x/2,  object[0][i].position.y +  object[0][i].size.y/2,  object[0][i].position.z +  object[0][i].size.z/2 }}; 
        }

    
        //Select Object
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            //Make sure that mouse is not using GUI
            bool mouseInGUI = false;
            if(GetMousePosition().x >(GetScreenWidth() -  GetScreenWidth()/4)) //Mouse is in GUI Panel
            {
                mouseInGUI = true;
            }

            if(!(mouseInGUI && isGUIOpen))
            {
                bool foundModel = false; //to avoid higlighting multiple objects
                isGUIOpen = false;
                currentlySelecting = false;
                for(int i = 0; i < totalTable; i++)
                {
                    if(GetRayCollisionBox(GetMouseRay(GetMousePosition(), camera), object[0][i].bounds).hit && !foundModel)
                    {
                        object[0][i].isSelected = true;
                        selectedType = 0;
                        selectedId = i;
                        currentlySelecting = true;
                        foundModel = true;
                        isGUIOpen = true;
                    }
                    else
                    {
                        object[0][i].isSelected = false; 
                    }

                }
           
            }
        }
        

        //Moving Objects
        if (currentlySelecting)
        {
            if (IsKeyDown(KEY_W))
            {
                object[selectedType][selectedId].position.z++;
            }
            else if(IsKeyDown(KEY_S))
            {
                object[selectedType][selectedId].position.z--;
            }
        
        
            if (IsKeyDown(KEY_A))
            {
                object[selectedType][selectedId].position.x++;
            }
            else if(IsKeyDown(KEY_D))
            {
                object[selectedType][selectedId].position.x--;
            }
        }
       
        //----------------------------------------------------------------------------------
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                //Floor
                DrawCube((Vector3){0,1,0},100,1,100,GRAY);
                DrawCubeWires((Vector3){0,1,0},100,1,100,BLACK);

                //Wall 1
                DrawCube((Vector3){-50,26.5,1},5,50,97,WHITE);
                DrawCubeWires((Vector3){-50,26.5,1},5,50,97,BLACK);

                //Wall 2
                DrawCube((Vector3){1,26.5,-50},96.9,50,5,WHITE);
                DrawCubeWires((Vector3){1,26.5,-50},96.9,50,5,BLACK);


                //Draw Models
                for(int i = 0; i < totalTable; i++)
                {
                    DrawModel(object[0][i].model,object[0][i].position,object[0][i].scale,object[0][i].color);
                    DrawModelWires(object[0][i].model,object[0][i].position,object[0][i].scale,BLACK);
                    
                    if(object[0][i].isSelected)
                    {
                        DrawBoundingBox(object[0][i].bounds,GREEN);
                    }
                  
                }
               
                DrawGrid(50, 10.0f);         // Draw a grid

             
            EndMode3D();

            //GUI
            if(isGUIOpen)
            {
                
                DrawLine(GetScreenWidth() -  GetScreenWidth()/4, 0, GetScreenWidth() -  GetScreenWidth()/4, GetScreenHeight(), Fade(LIGHTGRAY, 0.6f));
                DrawRectangle(GetScreenWidth() -  GetScreenWidth()/4, 0, GetScreenWidth()/4, GetScreenHeight(), Fade(LIGHTGRAY, 0.3f));


                //Set Color
                object[selectedType][selectedId].color.r = (int)GuiSliderBar((Rectangle){ 1000, 90, 105, 20 }, "Red", NULL, object[selectedType][selectedId].color.r, 0, 255);
                object[selectedType][selectedId].color.g = (int)GuiSliderBar((Rectangle){ 1000, 120, 105, 20 }, "Green", NULL, object[selectedType][selectedId].color.g, 0, 255);
                object[selectedType][selectedId].color.b = (int)GuiSliderBar((Rectangle){ 1000, 150, 105, 20 }, "Blue",NULL, object[selectedType][selectedId].color.b, 0, 255);

            }
            
            
            // if (currentlySelecting) 
            // {
            //     DrawText("1", GetScreenWidth() - 110, 10, 30, GREEN);

            // }
            
            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    //UnloadTexture(texture);     // Unload texture
    //UnloadModel(model[0]); 
    //UnloadModel(model[1]);        // Unload model

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}