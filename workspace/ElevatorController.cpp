#include <vector>
#include <numeric>
#include "Elavator.cpp"
using namespace std;

class ElevatorController{
    private:
        int numElevators = 0;
        int numFloors = 0;
        Elavator a = Elavator(10,numFloors);
    public:
        ElevatorController(int numElevators, int numFloors)
        {
            this->numElevators = numElevators;
            this->numFloors = numFloors;
            a = Elavator(10,numFloors);
        }
        ElevatorController()
        {
            this->numElevators = 0;
            this->numFloors = 0;
        }
        
        int getNumFloors()
        {
            return numFloors;
        }
        
        int getNumElevators()
        {
            return numElevators;
        }
        
        void updateControls(vector<vector<int>> peopleOnFloor)
        {
            int floor = a.getFloor();
            bool up = a.getDirection();
            
        }
        
        bool isEverythingEmpty(vector<vector<int>> peopleOnFloor)
        {
            int sum = 0;
            for(int i = 0; i <peopleOnFloor.size(); i++)
            {
                for(int j = 0; j < peopleOnFloor.at(i).size(); j++)
                {
                   sum += peopleOnFloor.at(i).at(j);
                }
            }
            return (sum+a.getnumPeople())==0;
        }
        void goToBottom()
        {
            cout << "The system is Empty Going Down to Lobby" << endl;
            if(a.getFloor()==0)
            {
                a.setDirection(true);
            }
            else
            {
                a.setDirection(false);
                a.moveElavator();
            }
        }
        
        
        vector<vector<int>> timeStepControllerP2(vector<vector<int>> peopleOnFloor)
        {
            //System is Empty
            if(isEverythingEmpty(peopleOnFloor))
            {
                goToBottom();   
                cout << "The system is Empty" << endl;
            }
            //System is not empty
            else
            {
                //If the elevator is moving up
                if(a.getDirection())
                {
                    //Are people Below going down
                    vector<bool> stopOnFloorsUp = getNewStops(peopleOnFloor,a.getFloor(),a.getDirection());
                    // cout << "Floors to stop on Up: ";
                    // for(int i = 0; i< stopOnFloors.size(); i++)
                    // {
                    //     cout << stopOnFloors.at(i) << ", ";
                    // }
                    // cout << endl;
                    int numPeopleAboveGoinUp = accumulate(stopOnFloorsUp.begin(), stopOnFloorsUp.end(), 0);
                    //Are people above going Down
                    vector<bool> stopOnFloorsDown = getNewStops(peopleOnFloor,numFloors-1,false);
                     int numPeopleAboveGoinDown = accumulate(stopOnFloorsDown.begin(), stopOnFloorsDown.end(), 0);
                    //Nobody on any floors
                    if(numPeopleAboveGoinDown== 0 && numPeopleAboveGoinUp == 0)
                    {
                        if(a.getStops().at(a.getFloor()))
                        {
                            peopleOnFloor.at(a.getFloor()) = a.peopleGetOnandOff(peopleOnFloor.at(a.getFloor()));
                        }
                        
                        if(isEverythingEmpty(peopleOnFloor))
                        {
                            goToBottom();   
                        }
                        else
                        {
                        a.moveElavator();
                        }
                    }
                    //People Above are going up
                    else if(numPeopleAboveGoinUp != 0)
                    {
                        a.updateStops(stopOnFloorsUp);
                        if(a.getStops().at(a.getFloor()))
                        {
                            peopleOnFloor.at(a.getFloor()) = a.peopleGetOnandOff(peopleOnFloor.at(a.getFloor()));
                        }
                        
                        if(isEverythingEmpty(peopleOnFloor))
                        {
                            goToBottom();   
                        }
                        else
                        {
                        a.moveElavator();
                        }
                    }
                    //Nobody above is going up
                    else
                    {   
                        a.updateStops(stopOnFloorsDown);
                        vector<bool> stops= a.getStops();
                        int peopleAbove = accumulate(stops.begin()+a.getFloor()+1,stops.end(), 0);
                        if(peopleAbove == 0)
                        {
                            a.changeDirection();
                        }
                        
                        if(a.getStops().at(a.getFloor()))
                        {
                            peopleOnFloor.at(a.getFloor()) = a.peopleGetOnandOff(peopleOnFloor.at(a.getFloor()));
                        }

                        
                       if(isEverythingEmpty(peopleOnFloor))
                        {
                            goToBottom();   
                        }
                        else
                        {
                        a.moveElavator();
                        }
                    }
                }
                //Moving Down
                else
                {
                // //Are people Below going down
                    vector<bool> stopOnFloorsDown = getNewStops(peopleOnFloor,a.getFloor(),a.getDirection());
                    // cout << "Floors to stop on Up: ";
                    // for(int i = 0; i< stopOnFloors.size(); i++)
                    // {
                    //     cout << stopOnFloors.at(i) << ", ";
                    // }
                    // cout << endl;
                    int numPeopleAboveGoinDown = accumulate(stopOnFloorsDown.begin(), stopOnFloorsDown.end(), 0);
                    //Are people above going Down
                    vector<bool> stopOnFloorsUp = getNewStops(peopleOnFloor,0,true);
                    int numPeopleBelowGoinUp = accumulate(stopOnFloorsUp.begin(), stopOnFloorsUp.end(), 0);
                    //Nobody on any floors
                    if(numPeopleAboveGoinDown== 0 && numPeopleBelowGoinUp == 0)
                    {
                        if(a.getStops().at(a.getFloor()))
                        {
                            peopleOnFloor.at(a.getFloor()) = a.peopleGetOnandOff(peopleOnFloor.at(a.getFloor()));
                        }
                        if(isEverythingEmpty(peopleOnFloor))
                        {
                            goToBottom();   
                        }
                        else
                        {
                        a.moveElavator();
                        }
                    }
                    //People Below are going down
                    else if(numPeopleAboveGoinDown != 0)
                    {
                        a.updateStops(stopOnFloorsDown);
                        if(a.getStops().at(a.getFloor()))
                        {
                            peopleOnFloor.at(a.getFloor()) = a.peopleGetOnandOff(peopleOnFloor.at(a.getFloor()));
                        }
                        
                        if(isEverythingEmpty(peopleOnFloor))
                        {
                            goToBottom();   
                        }
                        else
                        {
                        a.moveElavator();
                        }
                    }
                    //Nobody below is going down
                    else
                    {
                        a.updateStops(stopOnFloorsUp);
                        vector<bool> stops= a.getStops();
                        int peopleBelow = accumulate(stops.begin(),stops.end()-(numFloors-a.getFloor()-1), 0);
                        if(peopleBelow == 0)
                        {
                            a.changeDirection();
                        }
                        
                        if(a.getStops().at(a.getFloor()))
                        {
                            peopleOnFloor.at(a.getFloor()) = a.peopleGetOnandOff(peopleOnFloor.at(a.getFloor()));
                        }
                        
                        if(isEverythingEmpty(peopleOnFloor))
                        {
                            goToBottom();   
                        }
                        else
                        {
                        a.moveElavator();
                        }
                    }
                }
                cout << "The system is Not Empty" << endl;
            }
            return peopleOnFloor;
        }
        
        //Checks if anyone in currDirection needs to go the sane way 
        vector<bool> getNewStops(vector<vector<int>> peopleOnFloor, int floor, bool dir)
        {
            vector<bool> ret;
            if(dir)
            {
                ret = arePeopleAboveGoingUp(peopleOnFloor, floor);
            }
            else
            {
                ret = arePeopleBelowGoingDown(peopleOnFloor, floor);
            }
            return ret;
        }
        
        vector<bool> arePeopleAboveGoingUp(vector<vector<int>> peopleOnFloor,int floor)
        {
            vector<bool> floors(numFloors,false);
            for(int i = floor; i < numFloors-1; i++)
            {
                if(getSumOfVectorU(peopleOnFloor.at(i),i)>0)
                {
                    floors.at(i) = true;
                }
            }
            return floors;
        }
        
        vector<bool> arePeopleBelowGoingDown(vector<vector<int>> peopleOnFloor, int floor)
        {
            vector<bool> floors(numFloors,false);
            for(int i = floor; i > 0; i--)
            {
                if(getSumOfVectorD(peopleOnFloor.at(i),i)>0)
                {
                    floors.at(i) = true;
                }
            }
            return floors;
        }
        
        int getSumOfVectorU(vector<int> floor, int i)
        {
            return accumulate(floor.begin()+i+1, floor.end(), 0);
        }
        int getSumOfVectorD(vector<int> floor, int i)
        {
            return accumulate(floor.begin(), floor.end()-(numFloors-i-1), 0);
        }
        int controllerGetFloor()
        {
            return a.getFloor();
        }
        
        int controllerGetNumPeople()
        {
            return a.getnumPeople();
        }
};