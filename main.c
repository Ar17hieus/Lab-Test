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
    bool enableWireframe;


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
    [5] - TrashCan
    [6] - Board
    ======================================================================**/


    //total Objects
    int totalType = 7; //Increment if add new type of models
    int totalID = 10;
    int totalTable = 7;
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
    

    tempModel = LoadModel("models/projector.obj");
    object[3][0].model = tempModel; 
    object[3][0].isEmpty = false; 
    object[3][0].isSelected = false; 
    object[3][0].scale = 0.3;
    

    tempModel = LoadModel("models/lamp.obj");
    object[4][0].model = tempModel; 
    object[4][0].isEmpty = false; 
    object[4][0].isSelected = false; 
    object[4][0].scale = 0.4;


    tempModel = LoadModel("models/trashcan.obj");
    object[5][0].model = tempModel; 
    object[5][0].isEmpty = false; 
    object[5][0].isSelected = false; 
    object[5][0].scale = 0.05;


    tempModel = LoadModel("models/board.obj");
    object[6][0].model = tempModel; 
    object[6][0].isEmpty = false; 
    object[6][0].isSelected = false; 
    object[6][0].scale = 0.3;


    //--------------------------------------------------------
    // Set model position
    //--------------------------------------------------------
    object[0][0].position = (Vector3){-10,6,30};
    object[0][1].position = (Vector3){-10,6,0};
    object[0][2].position = (Vector3){-10,6,-30};

    object[0][3].position = (Vector3){25,6,30};
    object[0][4].position = (Vector3){25,6,0};
    object[0][5].position = (Vector3){25,6,-30};

    object[0][6].position = (Vector3){-30,6,-35};

    
    object[1][0].position = (Vector3){-10,12,30};


    object[2][0].position = (Vector3){5,10,30};
    object[2][1].position = (Vector3){5,10,0};
    object[2][2].position = (Vector3){5,10,-30};

    object[2][3].position = (Vector3){35,10,30};
    object[2][4].position = (Vector3){35,10,0};
    object[2][5].position = (Vector3){35,10,-30};


    object[3][0].position = (Vector3){-33,13,-30};

    object[4][0].position = (Vector3){-37,9,45};

    object[5][0].position = (Vector3){43,1,-44};

    object[6][0].position = (Vector3){-46,12,0};

    //--------------------------------------------------------
    // Set model Size (for bounding box)
    //--------------------------------------------------------
    for (int i = 0; i < totalTable; i++)
    {
        object[0][i].size = (Vector3){15,12,20};
    }

    object[1][0].size = (Vector3){10,8,10};
    

    for (int i = 0; i < totalChair; i++)
    {
        object[2][i].size = (Vector3){10,8,10};
    }

    object[3][0].size = (Vector3){10,8,10};
    
    object[4][0].size = (Vector3){15,15,15};

    object[5][0].size = (Vector3){10,10,10};

    object[6][0].size = (Vector3){20,30,20};


    //--------------------------------------------------------
    // Set model Size (for bounding box)
    //--------------------------------------------------------

    for (int i = 0; i < totalTable; i++)
    {
        object[0][i].color = BROWN;
    }

    object[1][0].color = GRAY;
    

    for (int i = 0; i < totalChair; i++)
    {
        object[2][i].color = LIGHTGRAY ;
    }

    object[3][0].color = GRAY;
    
    object[4][0].color = MAROON;

    object[5][0].color = LIGHTGRAY;

    object[6][0].color = LIGHTGRAY;


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
            if (IsKeyDown(KEY_UP))
            {
                object[selectedType][selectedId].position.x = object[selectedType][selectedId].position.x + moveSpeed;
            }
            else if(IsKeyDown(KEY_DOWN))
            {
                object[selectedType][selectedId].position.x =  object[selectedType][selectedId].position.x - moveSpeed;
            }
        
        
            if (IsKeyDown(KEY_LEFT))
            {
                object[selectedType][selectedId].position.z = object[selectedType][selectedId].position.z + moveSpeed;
            }
            else if(IsKeyDown(KEY_RIGHT))
            {
                object[selectedType][selectedId].position.z = object[selectedType][selectedId].position.z - moveSpeed;
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
                DrawCube((Vector3){-50,26.5,1},5,50,97,BEIGE);
                DrawCubeWires((Vector3){-50,26.5,1},5,50,97,BLACK);

                //Wall 2
                DrawCube((Vector3){1,26.5,-50},96.9,50,5,BEIGE);
                DrawCubeWires((Vector3){1,26.5,-50},96.9,50,5,BLACK);


                //Draw Models
                for(int h = 0; h< totalType; h++)
                {
                    for(int i = 0; i < totalID; i++)
                    {
                        
                        if(!object[h][i].isEmpty)
                        {
                            DrawModel(object[h][i].model,object[h][i].position,object[h][i].scale,object[h][i].color);

                            if(enableWireframe)
                            {
                                DrawModelWires(object[h][i].model,object[h][i].position,object[h][i].scale,BLACK);

                            }

                            if(object[h][i].isSelected)
                            {
                                DrawBoundingBox(object[h][i].bounds,GREEN);
                            }
                        }
                        
                    }
                }

                DrawGrid(50, 10.0f);        // Draw a grid
                
            EndMode3D();

            //GUI
            if(isGUIOpen)
            {
                
                DrawRectangle(GetScreenWidth() -  GetScreenWidth()/4, 0, GetScreenWidth()/4, GetScreenHeight()/2, Fade(LIGHTGRAY, 0.3f));

                DrawRectangle(GetScreenWidth() -  GetScreenWidth()/4, GetScreenHeight()/2, GetScreenWidth()/4, GetScreenHeight()/2, Fade(GRAY, 0.3f));

                //Set Color
                DrawText("Change Color", 980, 50, 19, BLACK);
                object[selectedType][selectedId].color.r = (int)GuiSliderBar((Rectangle){ 1000, 90, 105, 20 }, "Red", NULL, object[selectedType][selectedId].color.r, 0, 255);
                object[selectedType][selectedId].color.g = (int)GuiSliderBar((Rectangle){ 1000, 120, 105, 20 }, "Green", NULL, object[selectedType][selectedId].color.g, 0, 255);
                object[selectedType][selectedId].color.b = (int)GuiSliderBar((Rectangle){ 1000, 150, 105, 20 }, "Blue",NULL, object[selectedType][selectedId].color.b, 0, 255);
                DrawText("Arrow Key to Move Object", 980, 260, 19, BLACK);
                DrawText("Press shift to Increase height", 980, 280, 19, BLACK);
                DrawText("Press control to Lower height", 980, 300, 19, BLACK);

            }
            
            DrawRectangle(GetScreenWidth() -  GetScreenWidth()/4, GetScreenHeight()/2, GetScreenWidth()/4, GetScreenHeight()/2, Fade(WHITE, 1));

            enableWireframe =  GuiCheckBox((Rectangle){ 1000, 600, 20, 20 }, "Enable Wire frame:", enableWireframe);
            
            (int)GuiSpinner((Rectangle){ 1100, 630, 105, 20 }, "Select Type", &selectNum, 0, 5, false);
            
            DrawText("W,A,S,D for Movement", 1000, 400, 19, BLACK);
            DrawText("Press 'C' to change camera", 1000, 420, 19, BLACK);
            DrawText("0. Tables", 1000, 460, 15, BLACK);
            DrawText("1. Laptop", 1000, 480, 15, BLACK);
            DrawText("2. Chair", 1000, 500, 15, BLACK);
            DrawText("3. Projector", 1000, 520, 15, BLACK);
            DrawText("4. Lamp", 1000, 540, 15, BLACK);
            DrawText("5. Trash Can", 1000, 560, 15, BLACK);


            if (GuiButton((Rectangle){ 1100, 660, 105, 20 }, GuiIconText(ICON_HAND_POINTER, "ADD Objects")))
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
                    tempModel = LoadModel("models/table.obj");   
                    object[selectNum][selectedSlot].model = tempModel; 
                    object[selectNum][selectedSlot].scale = 0.1f;
                    object[selectNum][selectedSlot].isEmpty = false;  

                    object[selectNum][selectedSlot].position = (Vector3){20,20,20};   
                    object[selectNum][selectedSlot].size = (Vector3){15,15,20};    
                    object[selectNum][selectedSlot].color = BROWN;       
                }
                else if(selectNum == 1)
                {
                    tempModel = LoadModel("models/laptop.obj");   
                    object[selectNum][selectedSlot].model = tempModel; 
                    object[selectNum][selectedSlot].scale = 2;
                    object[selectNum][selectedSlot].isEmpty = false;  

                    object[selectNum][selectedSlot].position = (Vector3){20,20,20};   
                    object[selectNum][selectedSlot].size = (Vector3){10,8,10}; 

                    object[selectNum][selectedSlot].color = GRAY;           
                }
                else if(selectNum == 2)
                {
                    tempModel = LoadModel("models/chair.obj"); 
                    object[selectNum][selectedSlot].model = tempModel; 
                    object[selectNum][selectedSlot].scale = 0.17;
                    object[selectNum][selectedSlot].isEmpty = false;  

                    object[selectNum][selectedSlot].position = (Vector3){20,20,20};   
                    object[selectNum][selectedSlot].size = (Vector3){10,8,10};    
                    object[selectNum][selectedSlot].model.transform = MatrixRotateXYZ((Vector3){ 0, 80.2, 0 });

                    object[selectNum][selectedSlot].color = LIGHTGRAY; 
                }
                else if(selectNum == 3)
                {
                    tempModel = LoadModel("models/projector.obj"); 
                    object[selectNum][selectedSlot].model = tempModel; 
                    object[selectNum][selectedSlot].scale = 0.3;
                    object[selectNum][selectedSlot].isEmpty = false;  

                    object[selectNum][selectedSlot].position = (Vector3){20,20,20};   
                    object[selectNum][selectedSlot].size = (Vector3){10,8,10};  

                    object[selectNum][selectedSlot].color = GRAY;  
                }
                else if(selectNum == 4)
                {
                    tempModel = LoadModel("models/lamp.obj"); 
                    object[selectNum][selectedSlot].model = tempModel; 
                    object[selectNum][selectedSlot].scale = 0.4;
                    object[selectNum][selectedSlot].isEmpty = false;  

                    object[selectNum][selectedSlot].position = (Vector3){20,20,20};   
                    object[selectNum][selectedSlot].size = (Vector3){15,15,15};   

                    object[selectNum][selectedSlot].color = MAROON; 
                }
                else if(selectNum == 5)
                {
                    tempModel = LoadModel("models/trashcan.obj"); 
                    object[selectNum][selectedSlot].model = tempModel; 
                    object[selectNum][selectedSlot].scale = 0.05;
                    object[selectNum][selectedSlot].isEmpty = false;  

                    object[selectNum][selectedSlot].position = (Vector3){20,20,20};   
                    object[selectNum][selectedSlot].size = (Vector3){10,10,10};  

                    object[selectNum][selectedSlot].color = LIGHTGRAY;  
                }
                    
            }
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