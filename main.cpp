#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

// getInput vectors

vector <float> inputSL;
vector <float> inputSW;
vector <float> inputPL;
vector <float> inputPW;
vector <string> inSpec;

// computeNeuron vectors

vector <float> n1;
vector <float> n2;
vector <float> n3;
vector <float> n4;
vector <float> n5;

vector <float> n1Weight{
    0.5, 0.5, 0.5, 0.5
};
vector <float> n2Weight{
    0.5, 0.5, 0.5, 0.5
};
vector <float> n3Weight{
    0.5, 0.5, 0.5, 0.5
};
vector <float> n4Weight{
    0.5, 0.5, 0.5, 0.5
};
vector <float> n5Weight{
    0.5, 0.5, 0.5, 0.5
};

// computeOutput vectors

vector <float> setoWeight{
    0.5, 0.5, 0.5, 0.5, 0.5
};
vector <float> versWeight{
    0.5, 0.5, 0.5, 0.5, 0.5
};
vector <float> virgWeight{
    0.5, 0.5, 0.5, 0.5, 0.5
};

vector <float> setoProb;
vector <float> versProb;
vector <float> virgProb;

// getActual vectors

vector <float> setoActual;
vector <float> versActual;
vector <float> virgActual;

/////////////////////////////////////////////////////////////////////////////////////////////////

int L = 3;

int N[]={4,5,3};

double w[20][1000][1000] = {0.5};

double b[20][1000]={};

double a[20][1000];

double Z[20][1000];

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

        for(int i=0; i<=N[0]; ++i){

            getline(inputFile,a[0][i],',');

        }

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

        inputSL.push_back(stof(sepal_length));
        inputSW.push_back(stof(sepal_width));
        inputPL.push_back(stof(petal_length));
        inputPW.push_back(stof(petal_width));
        inSpec.push_back(species);

    }

    inputFile.close();
};

void computeNeuron(){

    float inp=0;
    float out=0;

    for (int i=0; i!=inputSL.size();++i) {

        inp = inputSL[i]*n1Weight[0]
                +inputSW[i]*n1Weight[1]
                +inputPL[i]*n1Weight[2]
                +inputPW[i]*n1Weight[3];

        out = 1/(1+exp(-inp));

        n1.push_back(out);

        inp = inputSL[i]*n2Weight[0]
                +inputSW[i]*n2Weight[1]
                +inputPL[i]*n2Weight[2]
                +inputPW[i]*n2Weight[3];

        out = 1/(1+exp(-inp));

        n2.push_back(out);

        inp = inputSL[i]*n3Weight[0]
                +inputSW[i]*n3Weight[1]
                +inputPL[i]*n3Weight[2]
                +inputPW[i]*n3Weight[3];

        out = 1/(1+exp(-inp));

        n3.push_back(out);

        inp = inputSL[i]*n4Weight[0]
                +inputSW[i]*n4Weight[1]
                +inputPL[i]*n4Weight[2]
                +inputPW[i]*n4Weight[3];

        out = 1/(1+exp(-inp));

        n4.push_back(out);

        inp = inputSL[i]*n5Weight[0]
                +inputSW[i]*n5Weight[1]
                +inputPL[i]*n5Weight[2]
                +inputPW[i]*n5Weight[3];

        out = 1/(1+exp(-inp));

        n5.push_back(out);
    }
};

void computeOutput(){

    float inp=0;
    float out=0;

    for (int i=0; i!=n1.size();++i) {
        inp=n1[i]*setoWeight[0]
                +n2[i]*setoWeight[1]
                +n3[i]*setoWeight[2]
                +n4[i]*setoWeight[3]
                +n5[i]*setoWeight[4];

        out=1/(1+exp(-inp));

        setoProb.push_back(out);

        inp=n1[i]*versWeight[0]
            +n2[i]*versWeight[1]
            +n3[i]*versWeight[2]
            +n4[i]*versWeight[3]
            +n5[i]*versWeight[4];

        out=1/(1+exp(-inp));

        versProb.push_back(out);

        inp=n1[i]*virgWeight[0]
            +n2[i]*virgWeight[1]
            +n3[i]*virgWeight[2]
            +n4[i]*virgWeight[3]
            +n5[i]*virgWeight[4];

        out=1/(1+exp(-inp));

        virgProb.push_back(out);
    }

}

void getActual(){
    for (int i =0; i!=inSpec.size(); ++i){

        if (inSpec[i]=="setosa"){
            setoActual.push_back(1);
            versActual.push_back(0);
            virgActual.push_back(0);

        }else if (inSpec[i]=="versicolor"){
            setoActual.push_back(0);
            versActual.push_back(1);
            virgActual.push_back(0);
        }else if (inSpec[i]=="virginica"){
            setoActual.push_back(0);
            versActual.push_back(0);
            virgActual.push_back(1);
        }

    }
}

int main(int argc, const char * argv[]) {

    getInput();
    computeNeuron();
    computeOutput();
    getActual();
    for (int i=0; i!=setoActual.size(); ++i){
        cout<<"Predicted: ("<<setoProb[i]<<", "<<versProb[i]<<", "<<virgProb[i]<<") | "
            <<"Actual: ("<<setoActual[i] <<", "<<versActual[i]<<", "<<virgActual[i]<<")"<<endl;
    }
    return 0;
}

// Needs error backpropogation

