#include <iostream>

int call_By_Value(int a) {
    a = a + 1;
    return a;
}
int call_By_Reference(int* a) {
    *a = *a + 1;
    return *a;
}
int main() {
    int a = 1;
    std::cout << call_By_Value(a) << "\t" << a;
    std::cout << "\n";
    std::cout << call_By_Reference(&a) << "\t" << a;
    return 0;
}