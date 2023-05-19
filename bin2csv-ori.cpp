#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const int MAXN = 1200;

#define valuetype double

/*
用来处理二进制数据集到csv明文数据集 ，不增加主键列，可以控制输出浮点数精度
*/

int main(int argc, char *argv[]) {
    std::string filename(argv[1]);
    std::string rawname = filename.substr(0, filename.find_last_of("."));
    ifstream infile = std::ifstream(filename, std::ios::out | std::ios::binary);

        if (infile.fail()) {
            cout << "File not exist or name error" << endl;
            return -1;
        }
        std::vector<valuetype> values;
        int nitems;
        int typewidth = sizeof(valuetype);
        // automatically recognize the maximum number of floating-point numbers
        for (nitems = 0;; nitems++) {
            valuetype floatvalue;
            infile.read((char *) (&floatvalue), typewidth);
            if (infile.fail())
                break;
            values.push_back(floatvalue);
        }
        
        infile.close();

    filename = rawname + std::string(".csv");

    std::ofstream myfile;
    myfile.open(filename, ios::out | ios::trunc);

    // myfile << "time,value\n";

    // for (int ct = 0; ct < 10; ct++) {
    //  ct * MAXN
    cout.precision(6);
    cout << fixed;

    for (int i = 0; i < MAXN; i++) {
        cout << values[i]  << " ";
        // myfile << std::to_string(i) + ",";
        myfile << setiosflags(ios::fixed) << setprecision(6) << values[i] << endl;
    }
    cout << endl;
    // }

    myfile.close();

    std::cout << "File successfully converted!" << std::endl;
    std::cout << filename << std::endl;

    return 0;
}