#include<iostream>
#include<vector>
#include<climits>
using namespace std;

class changeCoin {
	private:
		vector<int>  coins;
		vector<vector<int> >  cache;
	public:
		changeCoin(vector<int>  &c, int amt) {
			coins = c;

			cache.resize(c.size()+1);
			for(auto i:cache)
				i.resize(amt, -1);

			cout << "The min coin used to make change is: " << change(amt,c.size() -1);
		}
		~changeCoin() {
			cout << endl << "Cache:" << endl;
			for(auto i:cache) {
				for(auto j:i)
					cout << "\t" << j;
				cout << endl;
			}
		}
		
		int change(int amt, int coin_index) {


			if (coin_index < 0)
				return INT_MAX;

			if (amt == 0)
				return 0;

			if (amt < 0)
				return 0;
		
			return  min(1+change(amt - coins[coin_index], coin_index), change(amt, coin_index-1));
		}
};


int main() {
	vector<int>	coin_list = {1,2,4};
	changeCoin p1(coin_list, 3);

	return 0;
}
