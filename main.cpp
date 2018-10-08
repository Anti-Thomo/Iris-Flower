#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;
vector <float> input;

void getInput(){

    ifstream inputFile;
    inputFile.open("C:\\Users\\User\\CLionProjects\\Iris-Flower\\Iris.txt");

    while (inputFile.good()and !inputFile.eof()){

        string sepal_length;
        string sepal_width;
        string petal_length;
        string petal_width;
        string species;

        getline(inputFile, sepal_length, ',');
        getline(inputFile, sepal_width, ',');
        getline(inputFile, petal_length, ',');
        getline(inputFile, petal_width, ',');
        getline(inputFile, species, '\n');

        input.push_back(stof(sepal_length));
        input.push_back(stof(sepal_width));
        input.push_back(stof(petal_length));
        input.push_back(stof(petal_width));

        cout<<sepal_length<<endl;
        cout<<sepal_width<<endl;
        cout<<petal_length<<endl;
        cout<<petal_width<<endl;
        cout<<species<<endl;

    }

    inputFile.close();
};

class Neuron{
    double w;
    double b;

public:
    double computeActivation(double ){

    }
};

int main(int argc, const char * argv[]) {

    getInput();
    return 0;
}



/*for (unsigned i = 0; i != 50; ++i) {
        vector<float> predict = sig(dot(X, W, 4, 4, 1 ) );
        vector<float> predictError = y - predict;
        vector<float> predictDelta = predictError * sigD(predict);
        vector<float> W_delta = dot(transpose( &X[0], 4, 4 ), predictDelta, 4, 4, 1);
        W = W + W_delta;
    };*/

/*vector <float> dot (const vector <float>& m1, const vector <float>& m2,
                    const int m1_rows, const int m1_columns, const int m2_columns) {

    vector <float> output (m1_rows*m2_columns);

    for( int row = 0; row != m1_rows; ++row ) {
        for( int col = 0; col != m2_columns; ++col ) {
            output[ row * m2_columns + col ] = 0.f;
            for( int k = 0; k != m1_columns; ++k ) {
                output[ row * m2_columns + col ] += m1[ row * m1_columns + k ] * m2[ k * m2_columns + col ];
            }
        }
    }

    return output;
}*/