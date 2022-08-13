#include <iostream>
#include "bitsnarl.hpp"
#include <cstddef>

using namespace std;

int main() {
    vector<uint8_t> data;
    const uint8_t N = 10;
    for(uint8_t i = 0; i < N; i++) {
        data.push_back(i);
    }
    cout << "Original" << endl;
    for(auto& e : data) {
        cout << (int)e << " ";
    }
    cout << endl;

    bitsn::scramble(data);
    cout << "Scrambled" << endl;
    for(auto& e : data) {
        cout << (int)e << " ";
    }
    cout << endl;

    bitsn::un_scramble(data);
    cout << "Un-Scrambled" << endl;
    for(auto& e : data) {
        cout << (int)e << " ";
    }
    cout << endl;

    bitsn::scramble(data); // restore original

    data[0] += 1; // contaminate with an error
    bitsn::un_scramble(data);
    cout << "Un-Scrambled under error" << endl;
    for(auto& e : data) {
        cout << (int)e << " ";
    }
    cout << endl;

    return 0;
}
