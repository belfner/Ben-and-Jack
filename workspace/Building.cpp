#include <vector>
#include <iostream>
#include "ElevatorController.cpp"
#include <stdlib.h>
//#include "Elavator.cpp"
using namespace std;

class Building
{
    private:
        int numFloors;
        vector<vector<int>> peopleOnFloor;
        vector<vector<double>> floorChance;
        vector<double> chanceOfPerson;
        int numElevators;
        double seconds = 40;
        ElevatorController cont;
    public:
        Building(int numFloors,int numElevators)
        {
            //seed random
            srand (time(NULL));
            //Initializes the controller
            cont = ElevatorController(numElevators, numFloors);
            this->numFloors = numFloors;
            this->numElevators = numElevators;
            
            //Gen Chance of Going to Floor
            for(int i = 0;i<numFloors;i++)
            {
                vector<double> second (numFloors,0.0);
                floorChance.push_back(second);
                for(int j = 0; j<numFloors; j++)
                {
                    
                    if(i == 0)
                    {
                        if(j == i)
                        {
                            floorChance.at(i).at(j) = 0.0;
                            cout << floorChance.at(i).at(j) << ", ";
                        }
                        else
                        {
                            floorChance.at(i).at(j) = 1.0/(numFloors-1);
                            cout << floorChance.at(i).at(j) << ", ";
                        }
                    }
                    else
                    {
                        if(j == i)
                        {
                            floorChance.at(i).at(j) = 0.0;
                            cout << floorChance.at(i).at(j) << ", ";
                        }
                        else if(j == 0)
                        {
                            floorChance.at(i).at(j) = .50;
                            cout << floorChance.at(i).at(j) << ", ";
                        }
                        else
                        {
                            floorChance.at(i).at(j) = .50/(numFloors-2);
                            cout << floorChance.at(i).at(j) << ", "; 
                        }
                    }
                    
                }
                cout << endl;
            }
            cout << endl;
            
            //Gen chance of person each second
            
            for(int i = 0; i<numFloors; i++)
            {
                if(i == 0)
                {
                    chanceOfPerson.push_back(.5/seconds);
                    cout << chanceOfPerson.at(i) << ", ";
                }
                else
                {
                    chanceOfPerson.push_back((5.0/(numFloors-1))/seconds);
                    cout << chanceOfPerson.at(i) << ", ";
                }
            }
            cout << endl;
            
            //init people on floor
            for(int i = 0; i< numFloors; i++)
            {
                vector<int> second (numFloors,0);
                peopleOnFloor.push_back(second);
            }
            cout << endl;
            cout << endl;
        }
    
        void printPeople()
        {
           for(int i = numFloors-1;i>=0;i--)
            {
                cout << "Floor:" << i << "   ";
                for(int j = 0; j<numFloors; j++)
                { 
                    cout << peopleOnFloor.at(i).at(j) << ", ";
                }
                if (i == cont.controllerGetFloor())
                    {
                        cout << " <[" << cont.controllerGetNumPeople() << "]>";
                    }
                cout << endl;
            }
        }
        
        //Adds people and assigns floor
        void genPeople()
        {
            
            for (int i = 0; i< numFloors; i++)
            {
                double num = rand() / (RAND_MAX + 1.);
                double sum = chanceOfPerson.at(i);
                if(num<sum)
                {
                    cout << "Floor " << i << endl;
                    int floor = -1;
                    bool person = false;
                    double num = rand() / (RAND_MAX + 1.);
                    vector<double> curr = floorChance.at(i);
                    sum = 0;
                    sum += curr.at(0);
                    for(int j = 0; j< numFloors; j++)
                    {
                        if(num<sum)
                        {
                            peopleOnFloor.at(i).at(j)++;
                            break;
                        }
                        sum += curr.at(j+1);
                    }
                    
                }
            }
        }
        void timeStep()
        {
            cout << "----------------------------------------------" << endl;
            genPeople();
            //printPeople();
            peopleOnFloor = cont.timeStepControllerP2(peopleOnFloor);
            printPeople();
            
            cout << endl;
        }
};


