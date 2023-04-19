// N07_HW03_Task02.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    smart_array(smart_array& other) {
        size = other.get_size();
        next_element = other.get_next_element();
        arr = new int[size]();
        for (int i = 0; i < size; i++)
        {
            arr[i] = other.get_element(i);
        }
    }
    smart_array& operator=(smart_array& other) {
        if (&other != this)
        {
            delete[] arr;
            size = other.get_size();
            //next_element = size;
            next_element = other.get_next_element();
            arr = new int[size]();
            for (int i = 0; i < size; i++)
            {
                arr[i] = other.get_element(i);
            }
        }
        
        
        return *this;
    }
    
    ~smart_array() {
        delete[] arr;
    }

    int get_element(int i) {
        try {
            if (i < 0) {
                throw MyException("Некорректный индекс");
                return 0;
            }
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
    int get_size() {
        return size;
    }
    int get_next_element() {
        return next_element;
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
            return;
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
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.print_dynamic_array();

        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);
        new_array.print_dynamic_array();

        arr = new_array;
        arr.print_dynamic_array();

        // --- copy ---

        new_array.add_element(49);
        smart_array array_copy(new_array);
        array_copy.print_dynamic_array();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}
