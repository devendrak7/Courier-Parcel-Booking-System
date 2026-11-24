#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Courier
{
public:
    struct Parcel
    {
        string trackingID;
        string customerName;
        int weight, length, width, height;
        int serviceType;
        int distance;
        int speedClass;
        int charge;
    };

    Courier(){
    fileName="bookings.txt";
    }
    int calculateCharge(int weight);
    int calculateCharge(int weight, int distance);
    int calculateCharge(int weight, int distance, int speedClass);


private:
    string fileName;
};
int Courier::calculateCharge(int weight)
{
    return 50+(weight*20);
}
int Courier::calculateCharge(int weight, int distance)
{
    return 70+(weight*15)+(distance/2);
}
int Courier::calculateCharge(int weight, int distance, int speedClass)
{
    int extraCharge=0;
    if(speedClass==2)
        extraCharge=100;
    else if(speedClass==3)
        extraCharge=200;
    return 100+(weight*25)+distance+extraCharge;
}
int main(){

    return 0;
}
