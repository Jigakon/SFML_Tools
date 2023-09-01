//Attention aux includes sp�cifiques � openGL, aux fichiers .lib et .dll 
//� indiquer au projet et mettre au bon endroit

#include "Definitions.h"
#include "Init.h"
#include "Update.h"
#include "Display.h"

GameData gameData;

void main()
{
 
    Init(gameData);

    while (gameData.window.isOpen())
    {
        Update(gameData);

        Display(gameData);
    }
}