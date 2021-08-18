#include<iostream>
#include<vector>
#include<climits>
using namespace std;

class changeCoin {
	private:
		vector<int>  coins;
		vector<int>  cache;
	public:
		changeCoin(vector<int>  &c, int amt) {
			coins = c;
			cache.resize(c.size(), INT_MAX);
			cout << "The min coin used to make change is: " << change(amt,0);
		}
		
		int change(int amt, int coin_index) {
			if (amt == 0)
				return 0;

			if ( coin_index == coins.size())
				return INT_MAX;
		
			return min(1+change(amt - coins[coin_index], coin_index), change(amt, coin_index+1));
		}
};


int main() {
	vector<int>	coin_list = {1,2,4};
	changeCoin p1(coin_list, 10);

	return 0;
}
