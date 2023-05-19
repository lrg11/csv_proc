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
用来处理 csv文件到csv文件，保持原来数据集不变，仅识别出数据条数，增加头部描述信息,在文件自身基础上修改
*/

class CSVReader
{
    std::string filename;
    std::string delimeter;
    std::ifstream inFile;
    // std::vector<std::string> col_names;
    std::string line;
    std::string val;

public:
    CSVReader(std::string f, std::string del = ",")
        : filename(f), delimeter(del)
    {
        inFile.open(filename);
        if (!inFile)
        {
            std::cout << "Unable to open file";
            exit(1); // terminate with error
        }

        // Get the header of file
        // for (int i = 0; i < 8983; i++)
        // getline(inFile, line);
        // if () {
        //     // boost::algorithm::split(col_names, line, boost::is_any_of(delimeter));
        // }
    };

    bool isEmpty()
    {
        getline(inFile, line);
        return ((line == "") || (!inFile));
    }

    string nextLine()
    {
        if (line != "" && line != "\n")
        {
            return line;
            // std::vector<std::string> s;
            // boost::algorithm::split(s, line, boost::is_any_of(delimeter));
            // std::vector<double> vec(s.size());
            // std::transform(s.begin(), s.end(), vec.begin(), [](const std::string &val) {
            //     return (val != "") ? double(std::stod(val)) : nan("0");
            // });
            // try{
            // std::stringstream sstream(line);
            // for (int i = 0; i < 1; i++)
            //     getline(sstream, val, delimeter[0]);
            // // getline(sstream, val, delimeter[0]);
            // // getline(sstream, val, ',');
            // // getline(sstream, val, ',');
            // // getline(sstream, val, ',');
            // // getline(sstream, val, ',');
            // // getline(sstream, val, ',');
            // return double(std::stod(val));
            // }
            // exception{

            // }
        }
        else
        {
            inFile.close();
            exit(EXIT_FAILURE);
        }
    }

    ~CSVReader()
    {
        inFile.close();
    }
};

const int MAXN = 1200;

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);
    std::string rawname = filename.substr(0, filename.find_last_of("."));
    // int skip_timestamp = argc > 2;

    CSVReader reader(filename, ",");
    

    std::ofstream ofs;
    filename = std::string("p-") + rawname + std::string(".csv");
    ofs.open(filename, ios::out | ios::trunc);
   


    int j = 0;
    // false indicates int, true -> float
    bool type = false;
    for (j = 0; !reader.isEmpty(); j++)
    {
        ofs << j << ",";
        string value = reader.nextLine();
        if(!type && value.find(".") != string::npos) {
            type = true;
        }
        ofs << value << endl; 
    }

    ofs.close();
    
    CSVReader reader1(filename, ",");

    std::ofstream ofs1;
    ofs1.open(argv[1], ios::out | ios::trunc);

    ofs1 << "domain:safety\n" << "source:fenghuo\n" << "datatype:float\n"
    << "precision:8\n" << "length:" << j << "\nconfidentiality:confidential\n"
     << "\ndescription:\n";

    // ofs1 << "domain:transportation\n" << "source:lixiang\n" << "datatype:float\n"
    // << "precision:8\n" << "length:" << lines.size() << "\nconfidentiality:confidential\n" << "\ndescription:\n";


   
    // ofs1 << "domain:security\n" << "subdomain:fenghuo\n" << "datatype:" << (type ? "float":"int") << "\n" 
    // << "precision:8\n" << "length:" << j << "\ndescription:\n";
    
    for (int i = 0; i < j && !reader1.isEmpty();i++)
    {
        ofs1 << reader1.nextLine() << endl; 
    }
    ofs1.close();

    std::cout << "File successfully converted!" << std::endl;
    std::cout << filename << std::endl;
}