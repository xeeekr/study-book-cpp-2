#include <iostream>
#include <random>
#include <complex>
#include <limits>

namespace ch4_2_2_1 {
	std::default_random_engine& global_urng() {
		static std::default_random_engine u{};
		return u;
	}
	void randomize() {
		static std::random_device rd{};
		global_urng().seed(rd());
	}
	int pick(int from, int thru) {
		static std::uniform_int_distribution<> d{};
		using parm_t = decltype(d)::param_type;
		return d(global_urng(), parm_t{from, thru});
	}
	double pick(double from, double upto) {
		static std::uniform_real_distribution<> d{};
		using parm_t = decltype(d)::param_type;
		return d(global_urng(), parm_t{from, upto});
	}

	void run() {
		using namespace std;
		cout << "ch4.2.2.1" << endl;

		randomize();
		cout << "Now, we roll dice: \n";
		for (int i = 0 ; i < 15 ; ++i) {
			cout << pick(1, 6) << endl;
		}

		cout << "\nLet's roll continuous dice now: ;-)\n";
		for (int i = 0 ; i < 15 ; ++i) {
			cout << pick(1.0, 6.0) << endl;
		}
	}
}

namespace ch4_2_2_2 {
	using namespace std;

//	template <typename T>
//	inline complex<T> operator*(const complex<T>& c1, const complex<T>& c2) {
//		return complex<T>(real(c1) * real(c2) - imag(c1) * imag(c2),
//									 real(c1) * imag(c2) + imag(c1) * real(c2));
//	}

	template <typename T>
	inline bool similar(complex<T> x, complex<T> y) {
		const double eps = 10 * numeric_limits<T>::epsilon();
		T sum = abs(x) + abs(y);
		if (sum < 1000 * numeric_limits<T>::min()) {
			return true;
		}
		return abs(x - y) / sum <= eps;
	}

	struct distributivity_violated {};

	template <typename T>
	inline void test(complex<T> a, complex<T> b, complex<T> c) {
		if (!similar(a * (b + c), a * b + a * c)) {
			cerr << "Test detected that " << a << ", " << b << ", " << c << endl;
			throw distributivity_violated();
		}
	}

	void run() {
		const int max_test = 20;

		const double from = -10.0, upto = 10.0;
		auto mypick = [from, upto]() { return complex<double>{ch4_2_2_1::pick(from, upto), ch4_2_2_1::pick(from, upto)}; };

		ch4_2_2_1::randomize();
		for (int i = 0 ; i < max_test ; ++i) {
			complex<double> a = mypick();
			for (int j = 0 ; j < max_test ; ++j) {
				complex<double> b = mypick();
				for (int k = 0 ; k < max_test ; ++k) {
					complex<double> c = mypick();
					test<double>(a, b, c);
				}
			}
		}
	}
}

namespace ch4_2_2_3 {
	using namespace std;
	void random_numbers() {
#if 0
		default_random_engine re;
#endif
#if 0
		static default_random_engine re;
#endif

#if 1
		random_device rd;
		default_random_engine re{rd()};
#endif

		cout << "Random numbers: ";
		for (int i = 0 ; i < 4 ; ++i) {
			cout << re() << (i < 3 ? ", " : "");
		}
		cout << endl;
	}

	void run() {
		random_numbers();
		random_numbers();
	}
}

namespace ch4_2_2_5 {
	using namespace std;

	void test1() {
		default_random_engine re{random_device{}()};
		normal_distribution<> normal;

		for (int i = 0 ; i < 6 ; ++i) {
			cout << normal(re) << endl;
		}
	}

	void test2() {
		auto normal = bind(normal_distribution<>{}, default_random_engine{random_device{}()});
		for (int i = 0 ; i < 6 ; ++i) {
			cout << normal() << endl;
		}
	}

	void test3() {
		auto normal = [re = default_random_engine{random_device{}()}, n = normal_distribution<>{}]() mutable {
			return n(re);
		};

		for (int i = 0 ; i < 6 ; ++i) {
			cout << normal() << endl;
		}
	}

	void test4() {
		auto normal = []() mutable {
			default_random_engine re{random_device{}()};
			normal_distribution<> normal;

			return normal(re);
		};

		for (int i = 0 ; i < 6 ; ++i) {
			cout << normal() << endl;
		}
	}

	void run() {
		test1();
		test2();
		test3();
		test4();
	}
}

int main() {
//	ch4_2_2_1::run();
//	ch4_2_2_2::run();
//	ch4_2_2_3::run();
	ch4_2_2_5::run();

	return EXIT_SUCCESS;
}
