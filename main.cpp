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
    void displayMenu();
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

string Courier::generateTrackingID()
{
    ifstream fin(fileName);
    string line;
    int count=0;
    while(getline(fin, line))
    {
        if(!line.empty())
            count++;
    }
    fin.close();
    return "CR"+to_string(1000+count+1);
}

void Courier::saveBooking(const Parcel& p)
{
    ofstream fout(fileName, ios::app);
    if(!fout)
    {
        cout<<"Error opening booking file!"<<endl;
        return;
    }
    fout<<p.trackingID<<"|"
        <<p.customerName<<"|"
        <<p.weight<<"|"
        <<p.length<<"|"
        <<p.width<<"|"
        <<p.height<<"|"
        <<p.serviceType<<"|"
        <<p.distance<<"|"
        <<p.speedClass<<"|"
        <<p.charge<<endl;
    fout.close();
    cout<<endl<<"Booking saved successfully!"<<endl;
}

void Courier::printReceipt(const Parcel& p)
{
    cout<<endl;
    cout<<"============================================"<<endl;
    cout<<"           COURIER BOOKING RECEIPT          "<<endl;
    cout<<"============================================"<<endl;
    cout<<"Tracking ID   : "<<p.trackingID<<endl;
    cout<<"Customer Name : "<<p.customerName<<endl;
    cout<<"Weight        : "<<p.weight<<" kg"<<endl;
    cout<<"Dimensions    : "<<p.length<<" x "<<p.width<<" x "<<p.height<<" cm"<<endl;
    cout<<"Service Type  : ";
    if(p.serviceType==1)
        cout<<"Local"<<endl;
    else if(p.serviceType==2)
        cout<<"Domestic"<<endl;
    else
        cout<<"Express"<<endl;
    if(p.serviceType==2 || p.serviceType==3)
    {
        cout<<"Distance      : "<<p.distance<<" km"<<endl;
    }
    if(p.serviceType==3)
    {
        cout<<"Speed Class   : ";
        if(p.speedClass==1)
            cout<<"Standard Express"<<endl;
        else if(p.speedClass==2)
            cout<<"Priority Express"<<endl;
        else
            cout<<"Same-Day Express"<<endl;
    }
    cout<<"--------------------------------------------"<<endl;
    cout<<"Total Charge  : Rs. "<<p.charge<<endl;
    cout<<"============================================"<<endl;
    cout<<"           Thank You For Booking!           "<<endl;
    cout<<"============================================"<<endl;
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
    p.trackingID=generateTrackingID();
    saveBooking(p);
    printReceipt(p);
}

void Courier::displayMenu()
{
    cout<<endl;
    cout<<"============================================"<<endl;
    cout<<"          COURIER MANAGEMENT SYSTEM         "<<endl;
    cout<<"============================================"<<endl;
    cout<<"1. Book New Parcel"<<endl;
    cout<<"2. Search Booking by Tracking ID"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<"============================================"<<endl;
}

int main()
{
    Courier courier;
    int choice;
    do
    {
        courier.displayMenu();
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                courier.bookParcel();
                break;
            case 2:
                // courier.searchBooking();
                break;
            case 3:
                cout<<endl<<"Thank you for using Courier Management System!"<<endl;
                break;
            default:
                cout<<endl<<"Invalid choice! Please select 1-3."<<endl;
        }
    }while(choice!=3);
    return 0;
}
