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
    void bookParcel();
    string generateTrackingID();
    void saveBooking(const Parcel& p);
    void printReceipt(const Parcel& p);
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



void Courier::bookParcel()
{
    Parcel p;
    cout<<endl<<"========== NEW PARCEL BOOKING =========="<<endl;
    cout<<"Customer Name: ";
    cin.ignore();
    getline(cin, p.customerName);
    while(p.customerName.empty())
    {
        cout<<"Name cannot be empty! Enter Customer Name: ";
        getline(cin, p.customerName);
    }
    cout<<"Enter Weight (kg): ";
    cin>>p.weight;
    cout<<"Enter Length (cm): ";
    cin>>p.length;
    cout<<"Enter Width (cm): ";
    cin>>p.width;
    cout<<"Enter Height (cm): ";
    cin>>p.height;
    cout<<endl<<"Select Service Type:"<<endl;
    cout<<"1. Local"<<endl;
    cout<<"2. Domestic"<<endl;
    cout<<"3. Express"<<endl;
    cout<<"Enter choice (1-3): ";
    cin>>p.serviceType;
    while(p.serviceType<1 || p.serviceType>3)
    {
        cout<<"Invalid choice! Enter 1, 2 or 3: ";
        cin>>p.serviceType;
    }
    p.distance=0;
    p.speedClass=0;
    if(p.serviceType==1)
    {
        p.charge=calculateCharge(p.weight);
    }
    else if(p.serviceType==2)
    {
        cout<<"Enter Distance (km): ";
        cin>>p.distance;
        p.charge=calculateCharge(p.weight, p.distance);
    }
    else
    {
        cout<<"Enter Distance (km): ";
        cin>>p.distance;
        cout<<endl<<"Select Speed Class:"<<endl;
        cout<<"1. Standard Express"<<endl;
        cout<<"2. Priority Express"<<endl;
        cout<<"3. Same-Day Express"<<endl;
        cout<<"Enter choice (1-3): ";
        cin>>p.speedClass;
        while(p.speedClass<1 || p.speedClass>3)
        {
            cout<<"Invalid choice! Enter 1, 2 or 3: ";
            cin>>p.speedClass;
        }
        p.charge=calculateCharge(p.weight, p.distance, p.speedClass);
    }
    // p.trackingID=generateTrackingID();
    // saveBooking(p);
    // printReceipt(p);
}
int main(){

    return 0;
}
