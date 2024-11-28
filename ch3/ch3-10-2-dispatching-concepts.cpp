#include <iostream>
#include <list>

namespace ch3_10_2 {
//	template <typename Iter>
//	requires std::input_or_output_iterator<Iter>
	template <std::input_or_output_iterator Iter>
	void advance1(Iter& it, unsigned n) {
		while (n-- > 0) {
			++it;
		}
	}

//	template <typename Iter>
//	requires std::bidirectional_iterator<Iter>
	template <std::bidirectional_iterator Iter>
	void advance(Iter& it, int n) {
		if (n >= 0) {
			while (n-- > 0) {
				++it;
			}
		} else {
			while (n++ < 0) {
				--it;
			}
		}
	}

//	template <typename Iter>
//	requires std::random_access_iterator<Iter>
	template <std::random_access_iterator Iter>
	void advance(Iter& it, int n) {
		it += n;
	}

	void run() {
		using namespace std;
		cout << "3_10_2" << endl;

		list<int> li{1, 2, 3, 4, 5, 6, 7, 8, 9};

		auto iter = li.begin();
		cout << "iter = " << *iter << endl;

		ch3_10_2::advance(iter, 3);
		cout << "iter = " << *iter << endl;

		ch3_10_2::advance(iter, -3);
		cout << "iter = " << *iter << endl;

		cout << "==========" << endl;

		vector<int> ve{1, 2, 3, 4, 5, 6, 7, 8, 9};
		auto viter = ve.begin();
		cout << "viter = " << *viter << endl;

		ch3_10_2::advance(viter, 3);
		cout << "viter = " << *viter << endl;

		ch3_10_2::advance(viter, -3);
		cout << "viter = " << *viter << endl;
	}
}

int main() {
	ch3_10_2::run();

	return EXIT_SUCCESS;
}
