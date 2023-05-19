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
csv文件到csv文件，原来的单个数据集多个算法再一列压缩率值的格式，转化为每个数据集，多列算法对应多个压缩率值
便于office绘图
d  a   r
d1 a1  r1       d   a1 a2
d1 a2  r2   =>  d1  r1 r2
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
        getline(inFile, line);
        // if () {
        //     // boost::algorithm::split(col_names, line, boost::is_any_of(delimeter));
        // }
    };

    bool isEmpty()
    {
        getline(inFile, line);
        return ((line == "") || line.size() < 2 || (!inFile));
    }

    double nextLine()
    {
        if (line != "" && line != "\n")
        {
            // std::vector<std::string> s;
            // boost::algorithm::split(s, line, boost::is_any_of(delimeter));
            // std::vector<double> vec(s.size());
            // std::transform(s.begin(), s.end(), vec.begin(), [](const std::string &val) {
            //     return (val != "") ? double(std::stod(val)) : nan("0");
            // });
            // try{
            std::stringstream sstream(line);
            for (int i = 0; i < 6; i++)
                getline(sstream, val, delimeter[0]);
            // getline(sstream, val, delimeter[0]);
            // getline(sstream, val, ',');
            // getline(sstream, val, ',');
            // getline(sstream, val, ',');
            // getline(sstream, val, ',');
            // getline(sstream, val, ',');
            return double(std::stod(val));
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

vector<string> datasets = {"fenghuo1", "fenghuo2", "fenghuo3", "fenghuo4", "fenghuo6", "fenghuo11",
                           "double-big", "small-positive", "small-negative",
                           "beili-lng", "beili-lat", "beili-speed", "city-temp",
                           "stocks-DE", "Basel-temp", "Basel-wind", "bitcoin-price",
                           "bird-migration-lat", "bird-migration-lon", "air-sensor", "food-prices",
                           "poi-lat", "poi-lon", "blockchain-tr", "SSD_HDD_benchmarks"};
vector<string> algos = {"chimp", "tsxor-exhaust", "tsxor-circa", "tsxor-trail", "tsxor-dual", "tsxor-mix", "gorilla", "zstd", "lz4"};

int main(int argc, char *argv[])
{
    std::string filename(argv[1]);
    // int skip_timestamp = argc > 2;

    CSVReader reader(filename, ",");

    int ct = 0;
    cout.precision(16);
    cout << fixed;
    ofstream ofs("results-compressratio-graph.csv");
    ofs << "dataset";
    for (int j = 0; j < algos.size(); j++)
    {
        ofs << "," + algos[j];
    }
    ofs << endl;
    for (int i = 0; i < datasets.size(); i++)
    {
        std::vector<double> lines;
        ofs << datasets[i];
        for (int j = 0; j < algos.size() && !reader.isEmpty(); j++)
        {
            lines.push_back(reader.nextLine());
            cout << lines[j] << " ";
            ofs << "," << lines[j];
        }
        ofs << endl;
    }
    ofs.close();
    cout << endl;

    std::cout << "File successfully generated!" << std::endl;
    std::cout << filename << std::endl;
}