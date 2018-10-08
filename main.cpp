#include <iostream>
#include <vector>
#include <cmath>

using namespace std;



int main(int argc, const char * argv[]) {
    for (unsigned i = 0; i != 50; ++i) {
        vector<float> predict = sig(dot(X, W, 4, 4, 1 ) );
        vector<float> predictError = y - predict;
        vector<float> predictDelta = predictError * sigD(predict);
        vector<float> W_delta = dot(transpose( &X[0], 4, 4 ), predictDelta, 4, 4, 1);
        W = W + W_delta;
    };
    return 0;
}