# csvToRNTuple
A program that takes as input a CSV file and generates a RNTuple ROOT file. 

## Features
It take the  first row of the input CSV file as a header and automatically parses it. You do not have to know the number, name or type of the columns.

## How to compile

### Prerequisites

The program is only tested on ROOT 6.26.00. If you are able to build ROOT6.26.00, then you have all the prerequisites to run this program. 

### Compiling

Make a build directory and enter it.
```
$ mkdir build && cd build
```

cmake 
```
$ cmake ../
```
make
```
$ make
```
Now you will have two executable files: `task2_converter` and `task2_analyser`. 

## How to use

### Convert

```
$ ./task2_converter <input_file> <output_file>
```

### Analyse

```
$ ./task2_analyser <output_file> #output_file from above part.
```

## Example
The input file is a CSV file ith 6 columns.
```
An_Integer:int,pX:float,pY:float,pZ:float,Integer_2:int,ProbK:float
0,2.123,1.31,1,0,9132.1433
1,2232.3,3.1,0.1231,2,2.3
2,322.36,45.1,12.1,85,124
56,24.1,2541.2,15,4,83.323
```

Convert it
```
$ ./task2_converter ../input_file.csv output_file.ntuple
Add field: An_Integer[std::int32_t]
Add field: pX[float]
Add field: pY[float]
Add field: pZ[float]
Add field: Integer_2[std::int32_t]
Add field: ProbK[float]
```

Now you have a file named output_file.ntuple in build/.

See what's inside output_file.ntuple.
```
$ ./task2_analyser output_file.ntuple
************************************ NTUPLE ************************************
* N-Tuple : Data                                                               *
* Entries : 4                                                                  *
********************************************************************************
* Field 1   : An_Integer (std::int32_t)                                     *
* Field 2   : pX (float)                                                       *
* Field 3   : pY (float)                                                       *
* Field 4   : pZ (float)                                                       *
* Field 5   : Integer_2 (std::int32_t)                                         *
* Field 6   : ProbK (float)                                                    *
********************************************************************************
The third entry is shown below:
{
  "An_Integer": 2,
  "pX": 322.36,
  "pY": 45.1,
  "pZ": 12.1,
  "Integer_2": 85,
  "ProbK": 124
}
```
