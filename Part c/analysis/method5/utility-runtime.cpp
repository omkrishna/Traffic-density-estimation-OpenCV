#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char **argv)
{

    string baseline, parameter;
    string val1, val2;
    ofstream outp_f("utility.txt", ios_base::app);
    ifstream baseline_f("baseline.txt");
    ifstream parameter_f(argv[1]);

    float err;
    float err_tot = 0.0;

    while (getline(baseline_f, baseline))
    {
        getline(parameter_f, parameter);

        istringstream iss(baseline);
        istringstream iss2(parameter);

        iss >> val1;
        iss2 >> val2;

        size_t comma = val1.find(",");
        if (comma != string::npos)
        {
            val1 = val1.substr(val1.find(",", comma + 1) + 1);
        }

        size_t comma_2 = val2.find(",");
        if (comma_2 != string::npos)
        {
            val2 = val2.substr(val2.find(",", comma_2 + 1) + 1);
        }

        if (val1.substr(0, 4) != "Time")
        {
            err = stof(val1) - stof(val2);
            err_tot += abs(err);
        }
    }

    outp_f << err_tot / 382 << ",";
    outp_f << stof(parameter.substr(parameter.find(":") + 1)) / 1000 << endl;

    // Close the file
    baseline_f.close();
    parameter_f.close();
}