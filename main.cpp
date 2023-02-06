#include <iostream>

extern int __declspec(dllimport) dynamic_fn();

int main() { std::cout << "in main\n"; return dynamic_fn() + 1; }
