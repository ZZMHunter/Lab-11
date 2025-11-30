/*
    Author: Zhao Zhang
    Course: CSCI-135
    Instructor: Tong Yi
    Assignment: Lab-11 B

    Class Network: Adds new users, following, posting messages

    Array of user "profiles"
    Integer "numUsers" stores number of users
    Size of "profiles" array defined as MAX_USERS=20
*/
#include <iostream>
#include <string>

using namespace std;
//A
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
//B
class Network{
    private:
        static const int MAX_USERS = 20;
        int numUsers;
        Profile profiles[MAX_USERS];
        int findID(string usrn){
            for(int i = 0; i < MAX_USERS; i++){
                if (profiles[i].getUsername()==usrn){
                    return i;
                }
            }
            return 0;
        }
    public:
        Network(){
            numUsers = 0;
        }
        bool addUser(string usrn, string dspn){
            if (numUsers >= MAX_USERS) {
                return false;
            }
            if (usrn == "") {
                return false;
            }
            for (char c : usrn) {
                if (!isalnum(c)) {
                    return false;
                }
            }
            for (int i = 0; i < numUsers; i++) {
                if (profiles[i].getUsername() == usrn) {
                    return false;
                }
            }
            profiles[numUsers] = Profile(usrn, dspn);
            numUsers++;
            return true;
        }
};

int main() {
    Network nw;
    cout << nw.addUser("mario", "Mario") << endl;     // true (1)
    cout << nw.addUser("luigi", "Luigi") << endl;     // true (1)

    cout << nw.addUser("mario", "Mario2") << endl;    // false (0)
    cout << nw.addUser("mario 2", "Mario2") << endl;  // false (0)
    cout << nw.addUser("mario-2", "Mario2") << endl;  // false (0)

    for(int i = 2; i < 20; i++)
        cout << nw.addUser("mario" + to_string(i), 
                    "Mario" + to_string(i)) << endl;   // true (1)

    cout << nw.addUser("yoshi", "Yoshi") << endl;     // false (0)
} 