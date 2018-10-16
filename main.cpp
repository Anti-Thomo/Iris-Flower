#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////

int L = 3;

int N[]={4,5,3};

double w[20][1000][1000] = {0.5};

double b[20][1000]={1};

double a[20][1000];

double Z[20][1000];

double type[150][3];

double S(double i){
    double out;
    out=1/(1+exp(-i));
    return out;
};

void activationLoop(){
    for (int l=1; l<=L; ++l){
        for (int n=0; n<=N[l]; ++n){
            for (int p=0; p<=N[l-1]; ++p){
                Z[l][n] = Z[l][n] + (w[l][n][p] * a[l-1][p]);
            }
            Z[l][n] = Z[l][n] + b[l][n];
            a[l][n] = S(Z[l][n]);
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////


void getInput(){

    ifstream inputFile;
    inputFile.open(R"(C:\Users\User\CLionProjects\Iris-Flower\Iris.txt)");

    while (inputFile.good()and !inputFile.eof()){
        for (int n=0; n<150; ++n) {
            for (int i = 0; i < N[0]; ++i) {
                string in;
                getline(inputFile, in, ',');
                a[0][i]=stof(in);
            }
            string ft;
            getline(inputFile, ft, '\n');

            if (ft=="setosa"){
                type[n][0]=1;
                type[n][1]=0;
                type[n][2]=0;
            }else if (ft=="versicolor"){
                type[n][0]=0;
                type[n][1]=1;
                type[n][2]=0;
            }else if (ft=="virginica"){
                type[n][0]=0;
                type[n][1]=0;
                type[n][2]=1;
            }
        }
    }

    inputFile.close();
};

int main(int argc, const char * argv[]) {

    getInput();
    activationLoop();
    return 0;
}

// Needs error backpropogation

