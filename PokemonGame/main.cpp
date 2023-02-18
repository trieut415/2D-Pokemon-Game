#include <iostream>
#include <math.h>
#include <string>

#include "Point2D.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "Building.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "Trainer.h"
#include "Model.h"
#include "View.h"
#include "GameCommand.h"
#include "Input_Handling.h"

using namespace std;

int main()
{
    Model model;
    View view;
    model.Display(view);

    while(true)
    {
        char command;
        int id1;
        int id2;
        int potion_amount;
        int battle_amount;
        Point2D position1;

        cout << "Enter the game command: ";
        cin >> command;
        try{
            switch (command)
            {
            case 'm':
            {
                cin >> id1;
                cin >> position1.x;
                cin >> position1.y;
                DoMoveCommand(model, id1, position1);
                break;
            }
            case 'c':
            {
                cin >> id1;
                cin >> id2;
                DoMoveToCenterCommand(model, id1, id2);

                break;
            }
            case 'g':
            {
                cin >> id1;
                cin >> id2;
                DoMoveToGymCommand(model, id1, id2);
                break;
            }
            case 's':
            {
                cin >> id1;
                DoStopCommand(model, id1);
                break;
            }
            case 'p':
            {
                cin >> id1;
                cin >> potion_amount;
                DoRecoverInCenterCommand(model, id1, potion_amount);
                break;
            }
            case 'b':
            {
                cin >> id1;
                cin >> battle_amount;
                DoBattleCommand(model, id1, battle_amount);
                break;
            }
            case 'a':
            {
                DoAdvanceCommand(model, view);
                break;
            }
            case 'r':
            {
                DoRunCommand(model, view);
                break;
            }
            case 'q':
            {                
                cout << "Program Terminated" << endl;
                return 0;
            }
            case 'n':
            {
                char type;
                int id;
                double x, y;
                Point2D loc;
                cin >> type;
                cin >> id;
                cin >> x;
                cin >> y;
                loc.x = x;
                loc.y = y;
                DoNewObjectCommand(model, type, id, loc);
                break;
            }
            default:
            {
                throw command;
                //throw Invalid_Input("Default chosen");
                break;
            }
            }
        }
        catch (char exception){
            cout << "Invalid input -> " << command << endl;
        }
        /*catch (Invalid_Input& exception){
            cout << "Invalid input -> " << exception << endl;
        }*/
     
    }
}