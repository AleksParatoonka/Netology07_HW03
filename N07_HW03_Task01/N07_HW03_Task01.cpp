// N07_HW03_Task01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

class MyException : public std::exception
{
private:
    std::string err;
public:
    MyException(std::string error) : err(error) {}
    const char* getError() {
        return err.c_str();
    }
    virtual const char* what() const noexcept override
    {
        return err.c_str();
    }
};

class smart_array {
private:
    int* arr;
    int size;
    int next_element = 0;
public:

    smart_array(int size_) {
        size = size_;
        arr = new int[size_]();
    }

    ~smart_array() {
        delete[] arr;
    }

    int get_element(int i) {
        try {
            if (i >= size) {
                throw MyException("Запрашиваемого индекса нет в массиве");
                return 0;
            }
            return arr[i];
        }
        catch (MyException& err) {
            std::cerr << err.what() << std::endl;
        }        
    }

    void add_element(int input) {

        if (next_element < size) {
            arr[next_element] = input;
            next_element += 1;
            return; 
        }
        else {

            int* arr_new = new int[size]();
            for (int i = 0; i < size; i++) {
                arr_new[i] = arr[i];
            }
            delete[] arr;

            arr = new int[size + 1]();
            for (int i = 0; i < size; i++) {

                arr[i] = arr_new[i];
            }
            delete[] arr_new;
            arr[size] = input;
            size += 1;
            next_element += 1;
            return ;
        }
    }

    void print_dynamic_array() {

        std::cout << "Динамический массив: ";
        for (int i = 0; i < size; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    try {
        smart_array arr(5);
        arr.print_dynamic_array();
        arr.add_element(1);
        arr.print_dynamic_array();
        arr.add_element(4);
        arr.print_dynamic_array();
        arr.add_element(155);
        arr.print_dynamic_array();
        arr.add_element(14);
        arr.print_dynamic_array();
        arr.add_element(15);
        arr.print_dynamic_array();
        std::cout << "\n Ошибка " << arr.get_element(12) << std::endl;
        arr.print_dynamic_array();
        std::cout << "\n Uiiiii !!! " << arr.get_element(4) << std::endl;
        arr.print_dynamic_array();
        arr.add_element(25);
        arr.print_dynamic_array();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}

