#include <iostream>

#include <stdio.h>
#include <cxxabi.h>

#define GET_TEST_DATA \
int a = 0; \
const int b = 0; \
int *c = nullptr; \
const int *d = nullptr; \
int &e = a; \
const int &f = a;


template<typename T>
void foo1(T t, const char *artualName/*实参*/) {

    // 推导形参
    char *formatName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    printf("%-15s ->         %-15s   ->  %s\n", artualName, formatName, formatName);
    free(formatName);
}

template<typename T>
void foo2(const T t, const char *artualName/*实参*/) {

    // 推导形参
    char *formatName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    printf("%-15s ->         %-15s   ->  const %s\n", artualName, formatName, formatName);
    free(formatName);
}

template<typename T>
void foo3(T *t, const char *artualName/*实参*/) {

    // 推导形参
    char *formatName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    printf("%-15s ->         %-15s   ->  %s*\n", artualName, formatName, formatName);
    free(formatName);
}

template<typename T>
void foo4(const T *t, const char *artualName/*实参*/) {

    // 推导形参
    char *formatName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    printf("%-15s ->         %-15s   ->  const %s*\n", artualName, formatName, formatName);
    free(formatName);
}

template<typename T>
void foo5(T &t, const char *artualName/*实参*/) {

    // 推导形参
    char *formatName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    printf("%-15s ->         %-15s   ->   %s &\n", artualName, formatName, formatName);
    free(formatName);
}

template<typename T>
void foo6(const T &t, const char *artualName/*实参*/) {

    // 推导形参
    char *formatName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    printf("%-15s ->         %-15s   ->  const %s &\n", artualName, formatName, formatName);
    free(formatName);
}

// 完美转发
template<typename T>
void foo7(T&& t, const char *artualName/*实参*/) {

    // 推导形参
    char *formatName = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
    printf("%-15s ->         %-15s\n", artualName, formatName);
    free(formatName);
}

void T() {
    printf("T\n");

    GET_TEST_DATA;

    printf("%-15s      ->         %-15s        -> %s\n", "传递实参", "推导形参(T)", "实际参数(t)");
    foo1(a, "int");
    foo1(b, "const int");
    foo1(c, "int *");
    foo1(d, "const int *");
    foo1(e, "int&");
    foo1(f, "const int&");

    printf("--------------------\n");
}

void TConst() {
    printf("const T\n");

    GET_TEST_DATA;

    printf("%-15s      ->         %-15s        -> %s\n", "传递实参", "推导形参(T)", "实际参数(t)");
    foo2(a, "int");
    foo2(b, "const int");
    foo2(c, "int *");
    foo2(d, "const int *");
    foo2(e, "int&");
    foo2(f, "const int&");

    printf("--------------------\n");
}

void TP() {
    printf("T*(这个有问题 const int * 应该被推导成 T=const int的)\n");

    GET_TEST_DATA;

    printf("%-15s      ->         %-15s        -> %s\n", "传递实参", "推导形参(T)", "实际参数(t)");
    //foo3(a, "int");
    //foo3(b, "const int");
    foo3(c, "int *");
    foo3(d, "const int *");
    //foo3(e, "int&");
    //foo3(f, "const int&");

    printf("--------------------\n");
}

void TPConst() {
    printf("const T*\n");

    GET_TEST_DATA;

    printf("%-15s      ->         %-15s        -> %s\n", "传递实参", "推导形参(T)", "实际参数(t)");
    //foo4(a, "int");
    //foo4(b, "const int");
    foo4(c, "int *");
    foo4(d, "const int *");
    //foo4(e, "int&");
    //foo4(f, "const int&");

    printf("--------------------\n");
}

void TReference() {
    printf("T&\n");

    GET_TEST_DATA;

    printf("%-15s      ->         %-15s        -> %s\n", "传递实参", "推导形参(T)", "实际参数(t)");
    foo5(a, "int");
    foo5(b, "const int");
    foo5(c, "int *");
    foo5(d, "const int *");
    foo5(e, "int&");
    foo5(f, "const int&");

    printf("--------------------\n");
}

void TReferenceConst() {
    printf("const T&\n");

    GET_TEST_DATA;

    printf("%-15s      ->         %-15s        -> %s\n", "传递实参", "推导形参(T)", "实际参数(t)");
    foo6(a, "int");
    foo6(b, "const int");
    foo6(c, "int *");
    foo6(d, "const int *");
    foo6(e, "int&");
    foo6(f, "const int&");

    printf("--------------------\n");
}

// 完美转发
void TPerfectForwarding() {
    printf("T&&\n");

    GET_TEST_DATA;

    printf("%-15s      ->         %-15s\n", "传递实参", "推导形参(T)");
    foo7(a, "int");
    foo7(b, "const int");
    foo7(c, "int *");
    foo7(d, "const int *");
    foo7(e, "int&");
    foo7(f, "const int&");

    int && g = std::move(a);
    foo7(g, "int &&");

    printf("--------------------\n");
}

int main() {
    T();
    TConst();
    TP();
    TPConst();
    TReference();
    TReferenceConst();
    //TPerfectForwarding();
}
