#include "GameController.h"

int main()
{
    GameController::GetInstance().Initialize();
    GameController::GetInstance().Run();

    return 0;
}
