#include<iostream>

class Size {
	private:
		int value;
	public:
		int getValue() {
			return value;
		}
	public:
		void setValue(int value) {
			 this->value = value;
	}
};
template<class C,int N, typename T>
class Array {
private:
	T m_Array[N];
	C size;
public:
	C getSize(C size)  {
		return size;
	}
};
void classTemplateMain() {
	std::cout << "\nclass template output\n";
	Size size;
	size.setValue(5);
	Array<Size, 5, int> arr;
	std::cout << arr.getSize(size).getValue();
}