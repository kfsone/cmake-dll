#include <iostream>

int __declspec(dllexport) dynamic_fn() { std::cout << "in dll\n"; return 42; }
