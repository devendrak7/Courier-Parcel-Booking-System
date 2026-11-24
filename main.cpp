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

int main(){
    
    return 0;
}
