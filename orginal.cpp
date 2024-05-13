#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class rack {
    public:
        
        string name = "regular";

        int rScore[5] = {1,1,1,1,2};
        int mScore[5] = {2,2,2,2,2};
        int pScore[5] = {3,0,0,0,0};
        int bScore[5] = {0,0,0,0,0};
        
        string scoreMark = "O";
        string pScoreMark = "W";
        string mScoreMark = "M";
        string fail = "X";
        string bMark[5] = {"", "", "", "", ""};

        bool bBool[5] = {true, true, true, true, true};

        void changeType(string type);
        void replace(int s[], string m, int len);
        void print_balls();
        void change_bool(bool bBool[]);
};

void change_bool(bool bBool[]) {



}

void rack :: replace(int s[], string m, int len) {
    for(int i = 0; i < len; i++) {
        bScore[i] = s[i];
        bMark[i] = m;
    }
}

void rack :: changeType(string type) {
    if (type == "reg") {
        replace(rScore, scoreMark, 5);
    } else if (type == "money") {
        replace(mScore, mScoreMark, 5);
    } else if (type == "starry") {
        replace(pScore, pScoreMark, 1);
    }
}

void rack :: print_balls() {
    for (int i = 0; i < 5; i++) {
        cout << " " << bMark[i];
    }
    cout << endl;
}

void print_racks(rack racks[], int size) {
    for (int i = 0; i < size; i++) {
        cout << i+1 << "  ";
        racks[i].print_balls();
    }
}

void setup_racks(rack racks[], int size) {
    int pos = 0;

    cout << "which position do you want the money ball rack to be? (1-5): ";
    cin >> pos;
    
    for (int i = 0; i < 7; i++) {
        if (i != 2 && i != 5) {
            racks[i].changeType("reg");
        }
    }

    if (pos-1 >= 2) pos++;
    if (pos-1 >= 5) pos++;
    racks[pos-1].changeType("money");

    racks[2].changeType("starry");
    racks[5].changeType("starry");

}

void create_racks(rack *& array, int size) {
    array = new rack [size];
}

int main() {
    
    int RACK_SIZE = 7;

    srand(time(0));
    cout << rand() << endl; //_--------------------------------------------------------------------------- GET 0 - 1 rand Num

    rack* racks;
    create_racks(racks, RACK_SIZE);

    setup_racks(racks, 7);
    print_racks(racks, 7);

    return 0;
}