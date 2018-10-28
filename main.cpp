#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////

int L = 3;

int N[]={4,5,3};

double w[20][1000][1000];

double b[20][1000];

double a[20][1000][150];

double Z[20][1000][150];

double type[150][3];

double S(double i){
    double out;
    out=1/(1+exp(-i));
    return out;
};

void setWeight(int l, int n, int p, double weight){
    w[l][n][p]=weight;
}

void activationLoop(int i){
    for (int l=1; l<L; ++l) {
        for (int n = 0; n < N[l]; ++n) {
            for (int p = 0; p < N[l - 1]; ++p) {
                Z[l][n][i] = Z[l][n][i] + (w[l][n][p] * a[l - 1][p][i]);
                cout<<"Layer: "<<l<<", Neuron: "<<n<<", PrevNeuron: "<<p<<" --- Weight: "<<w[l][n][p]<<", Activation: "<<a[l-1][p][i]<<endl;
            }
            Z[l][n][i] = Z[l][n][i] + b[l][n];
            a[l][n][i] = S(Z[l][n][i]);
            cout<<a[l][n][i]<< endl;
        }
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////


void getInput(){

    ifstream inputFile;
    inputFile.open(R"(C:\Users\User\CLionProjects\Iris-Flower\Iris.txt)");

    while (inputFile.good()and !inputFile.eof()){
        for (int i=0; i<150; ++i) {
            for (int n = 0; n < N[0]; ++n) {
                string in;
                getline(inputFile, in, ',');
                a[0][n][i]=stod(in);
            }
            string ft;
            getline(inputFile, ft, '\n');

            if (ft=="setosa"){
                type[i][0]=1;
                type[i][1]=0;
                type[i][2]=0;
            }else if (ft=="versicolor"){
                type[i][0]=0;
                type[i][1]=1;
                type[i][2]=0;
            }else if (ft=="virginica"){
                type[i][0]=0;
                type[i][1]=0;
                type[i][2]=1;
            }
        }
    }

    inputFile.close();
};

double getError(int n, int i){
    double err;
    err=pow((type[i][n]-a[L-1][n][i]),2);
    cout<<type[i][n]<<" - "<<a[L-1][n][i]<<" = "<<err<<endl;
    return err;
}


double avgError(){
    double errSum=0;
    double avErr;
    int runs=0;
    for (int i = 0; i < 150; ++i) {
        for (int n = 0; n < N[L - 1]; ++n) {
            errSum = errSum + getError(n, i);
            runs=runs+1;
        }
    }
    avErr=errSum/runs;
    return avErr;
}

void train() {
    int layer = 1 + rand() % (L - 1);
    int neuron = rand() % (N[layer] - 1);
    int prevNeur = rand() % N[layer - 1]-1;
    double change = (((double(rand()) / RAND_MAX) * 2) - 1) * 0.1;
    double prevWeight = w[layer][neuron][prevNeur];

    double errBef=avgError();

    //cout<<"BEFORE: "<<errBef<<endl;

    //cout << prevWeight << " + (" << change << ")" << " = ";
    setWeight(layer, neuron, prevNeur, prevWeight + change);
    //cout << w[layer][neuron][prevNeur] << endl;

    for(int i=0;i<150;++i){
        activationLoop(i);
    }

    double errAft=avgError();

    //cout<<"AFTER: "<<errAft<<endl;

    if(errBef<=errAft){
        setWeight(layer, neuron, prevNeur, prevWeight);
        //cout<<"Unchanged"<<endl;
    }else{
        //cout<<"Changed"<<endl;
    }

    //cout<<"----------------------------------------------"<<endl;

}

int main(int argc, const char * argv[]) {


    for(int l=0;l<20;++l){
        for(int n=0;n<1000;++n){
            for(int p=0;p<1000;++p){
                double setW=((double(rand())/RAND_MAX)*2.0)-1.0;
                setWeight(l,n,p,setW);
            }
        }
    };


    getInput();

    //for(int i=0;i<10000;++i){
      //  train();
    //}

    for(int i=0;i<150;++i){
        activationLoop(i);
    }

    for(int i=0;i<150;++i){
        for(int j=0;j<4;++j){
            cout<<a[0][j][i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}