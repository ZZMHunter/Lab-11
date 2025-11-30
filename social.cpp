/*
    Author: Zhao Zhang
    Course: CSCI-135
    Instructor: Tong Yi
    Assignment: Lab-11 A

    Implement class Profile that can store the info about a user of the network.
    Two priate properties type string: displayName and username.
    Public Interface consists of two constructors and three functions:
    -getUsername
    -getFullName
    -setDisplayname.
*/
#include <iostream>
#include <string>

using namespace std;
class Profile{
    private:
        string username;
        string displayName;
    public:
        Profile(string usrn, string dspn){
            username = usrn;
            displayName = dspn;
        }
        Profile(){
            username = "";
            displayName = "";
        }
        string getUsername(){
            return username;
        }
        string getFullName(){
            string result = displayName;
            result += " (@";
            result += username;
            result += ")";
            return result;
        }
        void setDisplayName(string dspn){
            displayName = dspn;
        }
};

int main() {
    Profile p1("marco","Marco");
    cout << p1.getUsername() << endl;
    cout << p1.getFullName() << endl;

    p1.setDisplayName("Marco Rossi");
    cout << p1.getUsername() << endl;
    cout << p1.getFullName() << endl;

    Profile p2("tarma1", "Tarma Roving");
    cout << p2.getUsername() << endl;
    cout << p2.getFullName() << endl;
}