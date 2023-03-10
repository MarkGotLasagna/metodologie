```cpp
// c++11
class Rational {
	private:
		
	public:
		Razionale() = default;
		~Razionale() = default;
		Razionale(const Razionale&) = default;
		Razionale(Razionale&&) = default;
		Razionale& operator=(const Razionale&) = default;
		Razionale& operator=(Razionale&&) = default;
		
		using Int = long;
		
		explicit Razionale(Int n); // avoids implicit conversion
		Razionale(Int n, Int d);
		
		Razionale operator+(const Razionale& a2) const;
		Razionale operator-(const Razionale& a2) const;
		Razionale operator/(const Razionale& a2) const;
		Razionale operator*(const Razionale& a2) const;
		
		Razionale& operator+=(const Razionale& a2);
		Razionale& operator-=(const Razionale& a2);
		Razionale& operator/=(const Razionale& a2);
		Razionale& operator*=(const Razionale& a2);
		
		Razionale operator-() const;
		Razionale operator+() const;
		
		Razionale& operator++();
		Razionale operator++(int); // post-increments
}; // class Razionale
```