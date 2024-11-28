#include <iostream>

namespace ch3_11_1 {
	template <typename T>
	inline T sum(T t) { return t; }

	template <typename T, typename ...P>
	inline T sum(T t, P ...p) {
		return t + sum(p...);
	}

	void run() {
		using namespace std;
		cout << "ch3-11-1" << endl;

		cout << "sum(1) = " << sum(1) << endl;
		cout << "sum(1, 2) = " << sum(1, 2) << endl;
		cout << "sum(1, 2, 3) = " << sum(1, 2, 3) << endl;

		cout << "===========" << endl;

		auto s = sum(-7, 3.7f, 9u, -2.6);
		cout << "s is " << s << " and its type is " << typeid(s).name() << endl;
		auto s2= sum(-7, 3.7f, 9u, -42.6);
		cout << "s2 is " << s2 << " and its type is " << typeid(s2).name() << endl;
	}
}

namespace ch3_11_2 {
	template <typename ...Args>
	void print1(std::ostream& os, const Args& ...args) {
		//(os << args << ", ")...;
		os << std::endl;
	}

	template <typename ...Args>
	void dummy(Args ...) {}

	template <typename ...Args>
	void print2(std::ostream& os, const Args& ...args) {
		//dummy((os << args << ", ")...);
		os << std::endl;
	}

	template <typename ...Args>
	void print3(std::ostream& os, const Args& ...args) {
		dummy((os << args << ", ", 0)...);
		os << std::endl;
	}

	template <typename ...Args>
	void print4(std::ostream& os, const Args& ...args) {
		[[maybe_unused]] auto dummy = {(os << args << ", ", 0)...};
		os << std::endl;
	}

	void run() {
		using namespace std;
		cout << "ch3-11-2" << endl;
		print1(cout, 1, 2, 3);
		print2(cout, 1, 2, 3);
		print3(cout, 1, 2, 3);

		print3(cout, 3, 17.2, "Thingy");

		print4(cout, 3, 17.2, "Thingy");
	}
}

namespace ch3_11_3 {
	struct printer {
		template <typename First, typename ...Rest>
		void operator()(const First& f, const Rest& ...r) const {
			if constexpr(sizeof...(r) == 0) {
				std::cout << f << std::endl;
			} else {
				std::cout << f << ", "; (*this)(r...);
			}
		}
	};

	template <typename ...Args>
	struct caller {
		caller(Args&& ...args) : t(std::forward<Args>(args)...) {}

		template<typename F, size_t ...I>
		auto call_help(F f, std::index_sequence<I...>) const {
			return f(std::get<I>(t)...);
		}

		template<typename F>
		auto call(F f) const {
			call_help(f, std::make_index_sequence<sizeof...(Args)>{});
		}

		template<typename F>
		auto call2(F f) const {
			std::apply(f, t);
		}

		std::tuple<Args...> t;
	};

	void run() {
		using namespace std;
		cout << "ch3-11-3" << endl;

		using seq1 = index_sequence<3, 9, 4, 11>;
		using seq2 = index_sequence<0, 1, 2, 3>;

		using seq3 = make_index_sequence<4>;

		caller<int, double, string> data{1, 2.3, "test"s};
		data.call(printer{});
		data.call_help(printer{}, index_sequence<0, 2>{});

		data.call2(printer{});

	}
}

namespace ch3_11_4 {
	template <typename ...P>
	auto sum(const P& ...p) {
		return (p + ...);
	}

	template <typename ...P>
	auto sum2(const P& ...p) {
		return (0 + ... + p);
	}

	void run() {
		using namespace std;
		cout << "ch3_11_4" << endl;

		cout << sum(1) << endl;
		cout << sum(-7, 3.7f, 9u, -2.6) << endl;
		cout << sum(-7, 3.7f, 9u, -42.6) << endl;
		//cout << sum() << endl;

		cout << sum2(1) << endl;
		cout << sum2(-7, 3.7f, 9u, -2.6) << endl;
		cout << sum2(-7, 3.7f, 9u, -42.6) << endl;
		cout << sum2() << endl;

	}
}

namespace ch3_11_6 {
	using small_set = std::tuple<int, float>;

	template <typename ...Tuples>
	using tuple_cat_type = decltype(std::tuple_cat(std::declval<Tuples>()...));

	using compact_set = tuple_cat_type<small_set, std::tuple<short, double>>;

	template <typename Fun>
	void foreach_type(std::tuple<>, Fun) {}

	template <typename First, typename ...Others, typename Fun>
	void foreach_type(std::tuple<First, Others...>, Fun f) {
		Fun::template eval<First>();
		foreach_type(std::tuple<Others...>{}, f);
	}

	struct identity_test {
		template<typename T>
		static void eval() {
			T zero{0}, one{1}, nine{9};
			if (zero + nine != nine) {
				throw std::logic_error{"Addition wrong"};
			}
			if (one * nine != nine) {
				throw std::logic_error{"Multiplication wrong"};
			}
			std::cout << "Test passed for " << typeid(T).name() << std::endl;
		}
	};


	void run() {
		using namespace std;
		cout << "ch3-11-6" << endl;

		foreach_type(small_set {}, identity_test{});
		foreach_type(compact_set{}, identity_test{});
	}
}

int main() {
	ch3_11_1::run();
	ch3_11_2::run();
	ch3_11_3::run();
	ch3_11_4::run();
	ch3_11_6::run();

	return EXIT_SUCCESS;
}
