#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;
/*
used to verify the dataset format, and batch adjust the field of header
*/

bool isNum(string str) {
    stringstream sin(str);
    double d;
    char c;
    if (!(sin >> d)) {
        return false;
    }
    if (sin >> c) {
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    string option = string(argv[1]);
    if (option == "1") {
        std::string filename(argv[2]);
        // filename check
        ifstream infile;
        infile.open(filename);
        if (infile.fail()) {
            cout << "File not exist or name error" << endl;
            return -1;
        }
        string line;
        string val;
        bool isdouble = false;
        bool isint = false;
        bool hasproblem = false;

        // csv header
        getline(infile, line);
        if (line[0] != '#') {
            hasproblem = true;
            cout << "The header of the dataset file is not correct" << endl;
        }
        stringstream ss(line.substr(2, line.size() - 2));
        getline(ss, val, ':');
        if (val != "domain") {
            hasproblem = true;
            cout << "There is no domain field in the header of the dataset file" << endl;
        } else {
            getline(ss, val, ':');
            if (val.find("data collection") == string::npos && val != "APM" && val != "finance" && val != "non time series") {
                hasproblem = true;
                cout << "The domain field of dataset is not correct" << endl;
            }
        }

        getline(infile, line);
        if (line[0] != '#') {
            hasproblem = true;
            cout << "The header of the dataset file is not correct" << endl;
        }

        stringstream ss0(line.substr(2, line.size() - 2));
        getline(ss0, val, ':');
        if (val != "source") {
            // cout << "val is " << val << "\nline is " << ss0.str() << endl;
            hasproblem = true;
            cout << "There is no source field in the header of the dataset file" << endl;
        }

        getline(infile, line);
        if (line[0] != '#') {
            hasproblem = true;
            cout << "The header of the dataset file is not correct" << endl;
        }

        stringstream ss1(line.substr(2, line.size() - 2));
        getline(ss1, val, ':');
        if (val != "scenario") {
            // cout << "val is " << val << "\nline is " << ss1.str() << endl;
            hasproblem = true;
            cout << "There is no scenario field in the header of the dataset file" << endl;
        }

        getline(infile, line);
        if (line[0] != '#') {
            hasproblem = true;
            cout << "The header of the dataset file is not correct" << endl;
        }

        stringstream ss2(line.substr(2, line.size() - 2));
        getline(ss2, val, ':');
        if (val != "datatype") {
            hasproblem = true;
            cout << "There is no datatype field in the header of the dataset file" << endl;
        } else {
            getline(ss2, val, ':');
            if (val != "float" && val.find("int") == string::npos) {
                // cout << "val " << val << endl << "line " << ss2.str() << endl;
                hasproblem = true;
                cout << "The datatype field of dataset is not correct" << endl;
            }
            if (val == "float")
                isdouble = true;
            else if (val == "int")
                isint = true;
        }

        getline(infile, line);
        if (line[0] != '#') {
            hasproblem = true;
            cout << "The header of the dataset file is not correct" << endl;
        }

        stringstream ss3(line.substr(2, line.size() - 2));
        getline(ss3, val, ':');
        if (val != "precision") {
            hasproblem = true;
            cout << "There is no precision field in the header of the dataset file" << endl;
        } else {
            getline(ss3, val, ':');
            if (isdouble && val != "8" && val != "4") {
                hasproblem = true;
                cout << "The precision field of dataset is not correct" << endl;
            } else if (isint && val != "8" && val != "4" && val != "2" && val != "1") {
                hasproblem = true;
                cout << "The precision field of dataset is not correct" << endl;
            }
        }

        getline(infile, line);
        if (line[0] != '#') {
            hasproblem = true;
            cout << "The header of the dataset file is not correct" << endl;
        }

        stringstream ss4(line.substr(2, line.size() - 2));
        getline(ss4, val, ':');
        if (val != "length") {
            hasproblem = true;
            cout << "There is no length field in the header of the dataset file" << endl;
        } else {
            getline(ss4, val, ':');
            if (!isNum(val)) {
                hasproblem = true;
                cout << "The length field of dataset is not correct" << endl;
            }
        }

        getline(infile, line);
        if (line[0] != '#') {
            hasproblem = true;
            cout << "The header of the dataset file is not correct" << endl;
        }

        stringstream ss5(line.substr(2, line.size() - 2));
        getline(ss5, val, ':');
        if (val != "confidentiality") {
            hasproblem = true;
            cout << "There is no confidentiality field in the header of the dataset file" << endl;
        } else {
            getline(ss5, val, ':');
            if (val != "public" && val.find("confidential") == string::npos && val != "restricted") {
                hasproblem = true;
                cout << "The confidentiality field of dataset is not correct" << endl;
            }
        }

        getline(infile, line);
        if (line[0] != '#') {
            hasproblem = true;
            cout << "The header of the dataset file is not correct" << endl;
        }

        stringstream ss6(line.substr(2, line.size() - 2));
        getline(ss6, val, ':');
        if (val != "description") {
            hasproblem = true;
            cout << "There is no description field in the header of the dataset file" << endl;
        }

        getline(infile, line);
        if (line[0] != '#' && (line.size() < 2 || line[1] != ',')) {
            hasproblem = true;
            cout << "The value of the dataset is not correct or lack delimeter" << endl;
        }
        if (!hasproblem)
            cout << "This dataset check passed" << endl;
    } else if (option == "2") {
        std::string filename(argv[2]);
        string field(argv[3]);
        string newkey(argv[4]);

        string tmpfile("tmp.csv");
        ifstream infile;
        infile.open(filename);
        if (infile.fail()) {
            cout << "File not exist or name error" << endl;
            return -1;
        }
        std::ofstream ofs;
        ofs.open(tmpfile, ios::out | ios::trunc);

        string line;
        string val;
        // csv header  domain source
        for (int i = 0;; i++) {
            getline(infile, line);
            if ((line == "") || line == "\n" || (!infile)) break;
            stringstream ss(line.substr(2, line.size() - 2));
            getline(ss, val, ':');
            if (val == field) {
                getline(ss, val, ':');
                ofs << "# " + newkey + ":" + val << endl;
            } else {
                ofs << line << endl;
            }
        }
        infile.close();
        ofs.close();

        infile.open(tmpfile);
        ofs.open(filename, ios::out | ios::trunc);

        if (infile.fail() || ofs.fail()) {
            cout << "File not exist or name error" << endl;
            return -1;
        }

        // csv header  domain source
        for (int i = 0;; i++) {
            getline(infile, line);
            if ((line == "") || line == "\n" || (!infile)) break;
            ofs << line << endl;
        }
        infile.close();
        ofs.close();
    } else if (option == "3" || option == "4") {
        // > field key: scenario, do you want to modify? (y/n)
        // > y
        // > Input new key:
        // > class
        // > Finished, continue? (y/n)
        std::string filename(argv[2]);

        string tmpfile("tmp.csv");
        ifstream infile;
        infile.open(filename);
        if (infile.fail()) {
            cout << "File not exist or name error" << endl;
            return -1;
        }
        std::ofstream ofs;
        ofs.open(tmpfile, ios::out | ios::trunc);

        string line;
        string val;
        bool isquit = false;
        string ack;
        string newkey;

        // csv header  domain source
        for (int i = 0;; i++) {
            getline(infile, line);
            if ((line == "") || line == "\n" || (!infile)) break;
            if (line[0] != '#')
                isquit = true;

            if (!isquit) {
                stringstream ss(line.substr(2, line.size() - 2));
                getline(ss, val, ':');
                cout << "field key: " + val + ", do you want to modify? (y/n): ";
                while (isspace(cin.peek())) {
                    cin.get();
                }
                getline(cin, ack);
                if (ack == "y" || ack == "Y") {
                    cout << "Input new key: ";
                    while (isspace(cin.peek())) {
                        cin.get();
                    }
                    getline(cin, newkey);
                    getline(ss, val, ':');
                    ofs << "# " + newkey + ":" + val << endl;
                    cout << "Finished, continue to modify? (n/y): ";
                    while (isspace(cin.peek())) {
                        cin.get();
                    }
                    getline(cin, ack);
                    if (ack == "n" || ack == "N") {
                        isquit = true;
                    }
                } else {
                    ofs << line << endl;
                }
            } else {
                ofs << line << endl;
            }
        }
        infile.close();
        ofs.close();

        infile.open(tmpfile);
        ofs.open(filename, ios::out | ios::trunc);

        if (infile.fail() || ofs.fail()) {
            cout << "File not exist or name error" << endl;
            return -1;
        }

        // csv header  domain source
        for (int i = 0;; i++) {
            getline(infile, line);
            if ((line == "") || line == "\n" || (!infile)) break;
            ofs << line << endl;
        }
        infile.close();
        ofs.close();
    } else {
        cout << "The option of script is not correct, should be 0-4" << endl;
    }
    return 0;
}