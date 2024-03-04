#ifndef BINARY_H
#define BINARY_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <memory>

template <typename U>
class BinarySerialization
{
public:
    // Serialize operation
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    WriteBinary(const T &item, std::ofstream &output_file);

    void WriteBinary(const std::string &item, std::ofstream &output_file);

    template <typename T>
    void WriteBinary(const std::vector<T> &item, std::ofstream &output_file);

    template <typename Key, typename Value>
    void WriteBinary(const std::pair<Key, Value> &item, std::ofstream &output_file);

    template <typename Key, typename Value>
    void WriteBinary(const std::map<Key, Value> &item, std::ofstream &output_file);

    template <typename T>
    void WriteBinary(const std::list<T> &item, std::ofstream &output_file);

    template <typename T>
    void WriteBinary(const std::set<T> &item, std::ofstream &output_file);

    void WriteBinary(const std::nullptr_t &item, std::ofstream &output_file);

    template <typename T>
    void WriteBinary(const std::unique_ptr<T> &item, std::ofstream &output_file);

    // Deserialize operation
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    ReadBinary(T &item, std::ifstream &input_file);

    void ReadBinary(std::string &item, std::ifstream &input_file);

    template <typename T>
    void ReadBinary(std::vector<T> &item, std::ifstream &input_file);

    template <typename Key, typename Value>
    void ReadBinary(std::pair<Key, Value> &item, std::ifstream &input_file);

    template <typename Key, typename Value>
    void ReadBinary(std::map<Key, Value> &item, std::ifstream &input_file);

    template <typename T>
    void ReadBinary(std::list<T> &item, std::ifstream &input_file);

    template <typename T>
    void ReadBinary(std::set<T> &item, std::ifstream &input_file);

    void ReadBinary(std::nullptr_t &item, std::ifstream &input_file);

    template <typename T>
    void ReadBinary(std::unique_ptr<T> &item, std::ifstream &input_file);

    // Serialize
    template <typename T>
    void Serialize(const T &item, const std::string &filename);

    // Deserialize
    template <typename T>
    void Deserialize(T &item, const std::string &filename);
};

void testBinary();

#endif
