#include <ROOT/RNTuple.hxx>
#include <ROOT/RNTupleModel.hxx>

#include <iostream>
#include <fstream>
#include <memory>

using RNTupleReader = ROOT::Experimental::RNTupleReader;
using ENTupleShowFormat = ROOT::Experimental::ENTupleShowFormat;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error! Please specify the location of the output file!" << std::endl;
        std::cout << "Example: ./task2_analyser output_file.root" << std::endl;
        return 0;
    }

    char const *kNTupleFileName = argv[1];

    auto ntuple = RNTupleReader::Open("Data", kNTupleFileName);
    ntuple->PrintInfo();
    std::cout << "The third entry is shown below:" << std::endl;
    ntuple->Show(2, ENTupleShowFormat::kCompleteJSON);
    return 0;
}