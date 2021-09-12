#include<iostream>

using namespace std;

class Random {
	private:
		int state = 92;

		static const int A;
		static const int M;
		static const int Q;
		static const int R;
	public:
		Random (int initVal = 1) : state(initVal) {}

		// Uniform distribution
		double randomReal();
		int randomInt (int low, int high);
		int randomInt ();
		
		// Non-uniform distribution
		int poisson (double expectedVal);
		double negExp (double expectedVal);
			
};

const int Random::A = 48271;
const int Random::M = 2147483647;
const int Random::Q = M / A;
const int Random::R = M % A;

// randInt returns the next random number and updates state.
int Random::randomInt () {
	int tmpState = A * ( state % Q) -  R * ( state / Q ) ;
	return state = (tmpState >= 0 ? tmpState:tmpState + M);
}

int main() {
	Random generator1;
	for ( int i = 0; i < 10; i++)
		cout << "\t" << generator1.randomInt();
	return 0;
}
