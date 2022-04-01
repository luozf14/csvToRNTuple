#include <ROOT/RNTuple.hxx>
#include <ROOT/RNTupleModel.hxx>
#include <ROOT/RField.hxx>

#include <iostream>
#include <fstream>
#include <memory>

using RNTupleModel = ROOT::Experimental::RNTupleModel;
using RFieldBase = ROOT::Experimental::Detail::RFieldBase;
using RNTupleReader = ROOT::Experimental::RNTupleReader;
using RNTupleWriter = ROOT::Experimental::RNTupleWriter;

//Function that can delete the characters of the input string that we do not want, e.g, space, tab...
std::string Trim(std::string& str)
{
    str.erase(0,str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}

int main(int argc, char** argv)
{
    if(argc!=3)
    {
        std::cout<<"Error! Please specify the location of input file and output file!"<<std::endl;
        std::cout<<"Example: ./task2_converter ../input_file.csv output_file.root"<<std::endl;
        return 0;
    }

    char const* inputFile = argv[1];
    std::ifstream in;
    in.open(inputFile); 
    
    std::string input_line;

    //
    //Parse the header.
    //
    getline(in,input_line);
    std::string header_pair;
    //number of columns
    Int_t num_column=0; 
    //vector of pair<column name, column type>. This vector stores the name and type of each column.
    std::vector<std::pair<std::string, std::string> > column; 
    std::stringstream header_stream(input_line);
    while(getline(header_stream, header_pair, ','))
    {
        std::stringstream header_pair_stream(header_pair);
        std::string header_pair_char;
        std::string column_name;
        std::string column_type;
        getline(header_pair_stream, header_pair_char,':');
        column_name = Trim(header_pair_char);
        getline(header_pair_stream, header_pair_char,':');
        column_type = Trim(header_pair_char);
        column.push_back(std::pair<std::string, std::string>(column_name,column_type));
        num_column++;
    }

    //
    //Define the RNTuple
    //
    //Create an empty data model.
    auto model = RNTupleModel::Create(); 
    
    //Creat a vector which stores the pointer of each field. 
    std::vector<void*> _column;
    for(auto it : column)
    {
        //Creat field based on the header (name:type).
        auto field = RFieldBase::Create(it.first, it.second).Unwrap();
        model->AddField(std::move(field));
        std::cout<<"Add field: "<<model->GetField(it.first)->GetName()<<"["<<model->GetField(it.first)->GetType()<<"]"<<std::endl;
        _column.emplace_back(model->GetDefaultEntry()->GetValue(it.first).GetRawPtr());
    }

    //Hand over the data model to a newly created ntuple of name "Data", stored in kNTupleFileName.
    char const* kNTupleFileName = argv[2];
    auto ntuple = RNTupleWriter::Recreate(std::move(model), "Data", kNTupleFileName);

    //Loop the rows. In ecah row, seperate values by ','.
    while(getline(in,input_line))
    {
        int i=0;
        std::string value;
        std::stringstream input_line_stream(input_line);
        while(getline(input_line_stream, value, ','))
        {
            //asign the value of each filed.
            if(column[i].second=="int"){
                *(int*)_column[i]=std::stoi(Trim(value));
            }else if(column[i].second=="float"){
                *(float*)_column[i]=std::stof(Trim(value));
            }           
            i++;
        }
        ntuple->Fill();
    }
    
    in.close();
    return 0;
}