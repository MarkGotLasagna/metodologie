```toc
```
# Code
```cpp
namespace ND {
	class D {};
} // namespace ND

namespace NC {
	class C {
		public:
			C();
			C(double);
	};
	void foo(int i);
	
	
}

void foo(NC::C c, ND::D d);

int main() {
	NC::C c;
	ND::D d;
	foo(2.0);
}
```
