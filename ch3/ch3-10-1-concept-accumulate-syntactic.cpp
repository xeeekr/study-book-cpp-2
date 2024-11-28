#include <iostream>
#include <vector>

namespace ch3_10_1_1 {
	template <typename Iter, typename Value>
	concept Summable = requires (Iter it, Value init) {
		requires std::input_iterator<Iter>;
		requires std::is_copy_constructible_v<Value>;
		Value{init};
		init += *it;
	};

	template <typename Iter, typename Value>
	requires Summable<Iter, Value>
	Value accumulate(Iter first, Iter last, Value init) {
		for ( ; first != last ; ++first) {
			init += *first;
		}
		return init;
	}

	struct uncopyable {
		uncopyable(int v) : v{v} {}
		uncopyable(const uncopyable&) = delete;
		uncopyable(uncopyable&&) = default;

		uncopyable& operator+= (const uncopyable& rhs) & {
			v += rhs.v;
			return *this;
		}
		operator int() const { return v; }
		int v;
	};

	void run() {
		using namespace std;
		cout << "ch3_10_1" << endl;

		vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		// cout << "accumulate(v1, uncopyable{0}) = " << accumulate(v1.begin(), v1.end(), uncopyable{0}) << endl;

	}
}

namespace ch3_10_1_2 {
	template <typename Iter, typename Value>
	concept Summable = requires (Iter it, Value init) {
		requires std::input_iterator<Iter>;
		requires std::is_move_constructible_v<Value>;
		Value{std::move(init)};
		init += *it;
	};

	template <typename Iter, typename Value>
	requires Summable<Iter, Value>
	Value accumulate(Iter first, Iter last, Value init) {
		for ( ; first != last ; ++first) {
			init += *first;
		}
		return init;
	}

	struct uncopyable {
		uncopyable(int v) : v{v} {}
		uncopyable(const uncopyable&) = delete;
		uncopyable(uncopyable&&) = default;

		uncopyable& operator+= (const uncopyable& rhs) & {
			v += rhs.v;
			return *this;
		}
		operator int() const { return v; }
		int v;
	};

	void run() {
		using namespace std;
		cout << "ch3_10_2" << endl;

		vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		cout << "accumulate(v1, uncopyable{0}) = " << accumulate(v1.begin(), v1.end(), uncopyable{0}) << endl;

	}
}

namespace ch3_10_1_3 {
	template <typename Iter, typename Value>
	concept Returnalbe = requires (Iter it, Value init) {
		requires std::input_iterator<Iter>;
		requires std::is_move_constructible_v<Value> || std::is_copy_constructible_v<Value>;
		init += *it;
	};

	template <typename Iter, typename Value>
	requires Returnalbe<Iter, Value>
	Value& accumulate(Iter first, Iter last, Value init) {
		for ( ; first != last ; ++first) {
			init += *first;
		}
		return init;
	}

	struct uncopyable {
		uncopyable(int v) : v{v} {}
		uncopyable(const uncopyable&) = delete;
		uncopyable(uncopyable&&) = default;

		uncopyable& operator+= (const uncopyable& rhs) & {
			v += rhs.v;
			return *this;
		}
		operator int() const { return v; }
		int v;
	};

	struct unmovable {
		unmovable(int v) : v{v} {}
		unmovable(const unmovable&) = default;
		unmovable(unmovable&&) = delete;

		unmovable& operator+= (const unmovable& rhs) & {
			v += rhs.v;
			return *this;
		}
		operator int() const { return v; }
		int v;
	};

	void run() {
		using namespace std;
		cout << "ch3_10_3" << endl;

		vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
		cout << "accumulate(v1, uncopyable{0}) = " << accumulate(v1.begin(), v1.end(), uncopyable{0}) << endl;
		cout << "accumulate(v1, unmovable{0}) = " << accumulate(v1.begin(), v1.end(), unmovable{0}) << endl;

	}
}

namespace ch3_10_1_4 {
	template <typename T>
	concept Returnalbe = std::is_move_constructible_v<T> || std::is_copy_constructible_v<T>;

	template <typename Iter, typename Value, typename Op>
	concept Accumulatable = requires (Iter it, Value init, Op op) {
		requires std::input_iterator<Iter>;
		requires Returnalbe<Value>;
		init = op(init, *it);
	};

	template <typename Iter, Returnalbe Value, typename Op>
	requires Accumulatable<Iter, Value, Op>
	Value accumulate(Iter first, Iter last, Value init, Op op) {
		for ( ; first != last ; ++first) {
			init = op(init, *first);
		}
		return init;
	}

	struct add {
		template <typename T>
		T operator()(T x, T y) const noexcept {
			return x + y;
		}
	};

	void run() {
		using namespace std;
		cout << "ch3_10_4" << endl;

		vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		cout << "accumulate(v1, 0, add{}) = " << accumulate(v1.begin(), v1.end(), 0, add{}) << endl;
		cout << "accumulate(v1, 0, add{}) = " << accumulate(v1.begin(), v1.end(), 0, add{}) << endl;
	}
}

int main() {
	ch3_10_1_1::run();
	ch3_10_1_2::run();
	ch3_10_1_3::run();
	ch3_10_1_4::run();

	return EXIT_SUCCESS;
}
