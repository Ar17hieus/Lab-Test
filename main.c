#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "raygui.h"
#include "raymath.h"

struct objectData
{
    Model model;
    Color color;
    Vector3 position;
    BoundingBox bounds;
    Vector3 size;
    float scale;
    bool isSelected;
    bool isEmpty;
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
    int selectNum = 0;
    int cameraType = 1;




    /** ======================================================================
    INFO
    HOW TO ADD OBJECT
    1)Add variable to set max object
    2)Set Model's default value (for colors and isSelected)
    3)Load Models
    4)Load Texture
    5)Set Model's Default Position
    6)Set Model's Size (Used to create bounding box)
    
  
    ARRAY GUIDE
    object[x][y];
    // x = object type (chair,table,etc2)
    // y = object id (chair1,chair2,chair3, etc2)

    Current Models
    [0] - Tables
    [1] - Laptop
    [2] - Chair
    [3] - Projector
    [4] - Lamp
    ======================================================================**/


    //total Objects
    int totalType = 5; //Increment if add new type of models
    int totalID = 10;
    int totalTable = 6;
    int totalChair= 6;

    //Declare Object
    struct objectData object[totalType][totalID];

    //--------------------------------------------------------
    // set Object's default values
    //--------------------------------------------------------
    for(int h = 0; h < totalType; h++)
    {
        for (int i = 0; i < totalID; i++)
        {
            object[h][i].color= WHITE;
            object[h][i].isSelected= false;
            object[h][i].isEmpty= true;
        }
    }
    
    //--------------------------------------------------------
    //Load Models
    //--------------------------------------------------------
    //Tables
    Model tempModel;

    tempModel = LoadModel("models/table.obj");
    for(int i = 0; i<totalTable; i++)
    {
        object[0][i].model = tempModel; 
        object[0][i].scale = 0.1f;
        object[0][i].isEmpty = false;
    }
    

    tempModel = LoadModel("models/laptop.obj");
    object[1][0].model = tempModel; 
    object[1][0].isEmpty = false; 
    object[1][0].isSelected = false; 
    object[1][0].scale = 2;
    
   
   
    tempModel = LoadModel("models/chair.obj");
    for(int i = 0; i<totalChair; i++)
    {
        object[2][i].model = tempModel; 
        object[2][i].model.transform = MatrixRotateXYZ((Vector3){ 0, 80.2, 0 });
        object[2][i].isEmpty = false; 
        object[2][i].isSelected = false; 
        object[2][i].scale = 0.17;
    }
    

    //--------------------------------------------------------
    //Loads Texture
    //--------------------------------------------------------
    // Texture2D tempTexture; 

    // tempTexture = LoadTexture("texture/table.png");
    // object[0][0].model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = tempTexture; 

    
    // tempTexture = LoadTexture("texture/laptop.png");
    //object[1][0].model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = tempTexture; 
    
    //--------------------------------------------------------
    // Set model position
    //--------------------------------------------------------
    object[0][0].position = (Vector3){-10,6,30};
    object[0][1].position = (Vector3){-10,6,0};
    object[0][2].position = (Vector3){-10,6,-30};

    object[0][3].position = (Vector3){25,6,30};
    object[0][4].position = (Vector3){25,6,0};
    object[0][5].position = (Vector3){25,6,-30};

    object[1][0].position = (Vector3){-10,12,30};


    object[2][0].position = (Vector3){5,10,30};
    object[2][1].position = (Vector3){5,10,0};
    object[2][2].position = (Vector3){5,10,-30};

    object[2][3].position = (Vector3){20,10,30};
    object[2][4].position = (Vector3){20,10,0};
    object[2][5].position = (Vector3){20,10,-30};
    
    //--------------------------------------------------------
    // Set model Size (for bounding box)
    //--------------------------------------------------------
    for (int i = 0; i < totalTable; i++)
    {
        object[0][i].size = (Vector3){15,12,20};
    }

    object[1][0].size = (Vector3){10,8,10};
    

    
    //SetCameraMode(camera, CAMERA_FREE);     // Set a free camera mode

    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);
        

        //Set bounding Box
        for(int h = 0; h< totalType; h++)
        {
            for(int i = 0; i < totalID ;i++)
            {
                if(!object[h][i].isEmpty)
                {
                    object[h][i].bounds = (BoundingBox){(Vector3){ object[h][i].position.x -  object[h][i].size.x/2,  object[h][i].position.y - object[h][i].size.y/2,  object[h][i].position.z -  object[h][i].size.z/2 },
                                            (Vector3){ object[h][i].position.x +  object[h][i].size.x/2,  object[h][i].position.y +  object[h][i].size.y/2,  object[h][i].position.z +  object[h][i].size.z/2 }};     
                }
                else
                {
                    object[h][i].bounds =(BoundingBox){0,0};
                }
            }
        }
           
        //Camera option
        if (IsKeyPressed(KEY_C))
        {
            if (cameraType == 1)
            {
                cameraType = 2;
                camera.position = (Vector3){ 20.0f, 20.0f, 5.0f }; // Camera position
                camera.target = (Vector3){ -10.0f, 10.0f, 0.0f };     // Camera looking at point
                camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
                camera.fovy = 60.0f;                                // Camera field-of-view Y
                camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
                SetCameraMode(camera, CAMERA_FIRST_PERSON);     // Set a fps camera mode    
            }

            else if (cameraType == 2)
            {
                cameraType = 1;
                camera.position = (Vector3){ 50.0f, 50.0f, 50.0f }; // Camera position
                camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
                camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
                camera.fovy = 45.0f;                                // Camera field-of-view Y
                camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type
                SetCameraMode(camera, CAMERA_FREE);     // Set a free camera mode                 
            }
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
                
                selectedType = 0;
                selectedId = 0;
        
                bool foundModel = false; //to avoid higlighting multiple objects
                isGUIOpen = false;
                currentlySelecting = false;
                for(int h = 0; h < totalType; h++)
                {
                    for(int i = 0; i < totalID; i++)
                    {
                        if(GetRayCollisionBox(GetMouseRay(GetMousePosition(), camera), object[h][i].bounds).hit && !foundModel)
                        {
                            object[h][i].isSelected = true;

                            selectedType = h;
                            selectedId = i;
                            currentlySelecting = true;
                            foundModel = true;
                            isGUIOpen = true;
                        }
                        else
                        {
                            object[h][i].isSelected = false; 
                        }
                    }
                }

            }
        }
    

        //Moving Objects
        if (currentlySelecting)
        {
            double moveSpeed = 0.3;
            if (IsKeyDown(KEY_W))
            {
                object[selectedType][selectedId].position.z = object[selectedType][selectedId].position.z + moveSpeed;
            }
            else if(IsKeyDown(KEY_S))
            {
                object[selectedType][selectedId].position.z =  object[selectedType][selectedId].position.z - moveSpeed;
            }
        
        
            if (IsKeyDown(KEY_A))
            {
                object[selectedType][selectedId].position.x = object[selectedType][selectedId].position.x + moveSpeed;
            }
            else if(IsKeyDown(KEY_D))
            {
                object[selectedType][selectedId].position.x = object[selectedType][selectedId].position.x - moveSpeed;
            }

            if (IsKeyDown(KEY_LEFT_SHIFT))
            {
                object[selectedType][selectedId].position.y = object[selectedType][selectedId].position.y + moveSpeed;
            }
            else if(IsKeyDown(KEY_LEFT_CONTROL))
            {
                object[selectedType][selectedId].position.y = object[selectedType][selectedId].position.y - moveSpeed;
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
                for(int h = 0; h< totalType; h++)
                {
                    for(int i = 0; i < totalID; i++)
                    {
                        
                        if(!object[h][i].isEmpty)
                        {
                            DrawModel(object[h][i].model,object[h][i].position,object[h][i].scale,object[h][i].color);
                            DrawModelWires(object[h][i].model,object[h][i].position,object[h][i].scale,BLACK);
                        
                            if(object[h][i].isSelected)
                            {
                                DrawBoundingBox(object[h][i].bounds,GREEN);
                            }
                        }
                        
                    }
                }

                
              
                DrawGrid(50, 10.0f);         // Draw a grid
                
            EndMode3D();

            //GUI
            if(isGUIOpen)
            {
                
               //DrawLine(GetScreenWidth() -  GetScreenWidth()/4, 0, GetScreenWidth() -  GetScreenWidth()/4, GetScreenHeight(), Fade(LIGHTGRAY, 0.6f));
                DrawRectangle(GetScreenWidth() -  GetScreenWidth()/4, 0, GetScreenWidth()/4, GetScreenHeight()/2, Fade(LIGHTGRAY, 0.3f));

                DrawRectangle(GetScreenWidth() -  GetScreenWidth()/4, GetScreenHeight()/2, GetScreenWidth()/4, GetScreenHeight()/2, Fade(GRAY, 0.3f));

                //Set Color
                object[selectedType][selectedId].color.r = (int)GuiSliderBar((Rectangle){ 1000, 90, 105, 20 }, "Red", NULL, object[selectedType][selectedId].color.r, 0, 255);
                object[selectedType][selectedId].color.g = (int)GuiSliderBar((Rectangle){ 1000, 120, 105, 20 }, "Green", NULL, object[selectedType][selectedId].color.g, 0, 255);
                object[selectedType][selectedId].color.b = (int)GuiSliderBar((Rectangle){ 1000, 150, 105, 20 }, "Blue",NULL, object[selectedType][selectedId].color.b, 0, 255);

            }
            
            DrawRectangle(GetScreenWidth() -  GetScreenWidth()/4, GetScreenHeight()/2, GetScreenWidth()/4, GetScreenHeight()/2, Fade(WHITE, 1));
            (int)GuiSpinner((Rectangle){ 1100, 550, 105, 20 }, "Select Type", &selectNum, 0, 5, false);

            if (GuiButton((Rectangle){ 1100, 600, 105, 20 }, GuiIconText(ICON_HAND_POINTER, "ADD Objects")))
            {
                int currentSlot = 0;
                int selectedSlot;
                bool slotFound = false;
                //Find Empty Slot
                while(currentSlot < totalID && !slotFound )
                {
                    if(object[selectNum][currentSlot].isEmpty)
                    {
                        slotFound = true;
                        selectedSlot = currentSlot;
                    }
                    currentSlot++;
                }

                if(selectNum == 0)
                {
                    //DrawText(TextFormat("%d", selectedSlot), GetScreenWidth() - 300, 10, 30, BLACK);
                    tempModel = LoadModel("models/table.obj");   
                    object[selectNum][selectedSlot].model = tempModel; 
                    object[selectNum][selectedSlot].scale = 0.1f;
                    object[selectNum][selectedSlot].isEmpty = false;  

                    object[selectNum][selectedSlot].position = (Vector3){1,6,1};   
                    object[selectNum][selectedSlot].size = (Vector3){15,15,20};           
                }
                else if(selectNum == 1)
                {
                    tempModel = LoadModel("models/table.obj");   
                    object[selectNum][selectedSlot].model = tempModel; 
                    object[selectNum][selectedSlot].scale = 0.1f;
                    object[selectNum][selectedSlot].isEmpty = false;  

                    object[selectNum][selectedSlot].position = (Vector3){1,6,1};   
                    object[selectNum][selectedSlot].size = (Vector3){15,15,20};           
                }
            }
            
            // if (currentlySelecting) 
            // {
                
            //    DrawText("1", GetScreenWidth() - 110, 10, 30, GREEN);
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