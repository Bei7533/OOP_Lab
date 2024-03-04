#include "../include/Binary.h"

// Serialize operation
// Write the binary of arithmetic type
template <typename U>
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
BinarySerialization<U>::WriteBinary(const T &item, std::ofstream &output_file)
{
    output_file.write(reinterpret_cast<const char *>(&item), sizeof(item));
}

// Write the binary of string type
template <typename U>
void BinarySerialization<U>::WriteBinary(const std::string &item, std::ofstream &output_file)
{
    size_t size = item.size();
    output_file.write(reinterpret_cast<const char *>(&size), sizeof(size_t)); // Write the size of string
    output_file.write(item.c_str(), size);                                    // Write the string
}

// Write the binary of vector type
template <typename U>
template <typename T>
void BinarySerialization<U>::WriteBinary(const std::vector<T> &item, std::ofstream &output_file)
{
    size_t size = item.size();
    output_file.write(reinterpret_cast<const char *>(&size), sizeof(size_t)); // Write the size of vector
    for (const auto &it : item)                                               // Write the binary of each element
        WriteBinary(it, output_file);
}

// Write the binary of pair type
template <typename U>
template <typename Key, typename Value>
void BinarySerialization<U>::WriteBinary(const std::pair<Key, Value> &item, std::ofstream &output_file)
{
    WriteBinary(item.first, output_file);  // Write the binary of first element
    WriteBinary(item.second, output_file); // Write the binary of second element
}

// Write the binary of map type
template <typename U>
template <typename Key, typename Value>
void BinarySerialization<U>::WriteBinary(const std::map<Key, Value> &item, std::ofstream &output_file)
{
    size_t size = item.size();
    output_file.write(reinterpret_cast<const char *>(&size), sizeof(size_t)); // Write the size of map
    for (const auto &it : item)                                               // Write the binary of each element
        WriteBinary(it, output_file);
}

// Write the binary of list type
template <typename U>
template <typename T>
void BinarySerialization<U>::WriteBinary(const std::list<T> &item, std::ofstream &output_file)
{
    size_t size = item.size();
    output_file.write(reinterpret_cast<const char *>(&size), sizeof(size_t)); // Write the size of list
    for (const auto &it : item)                                               // Write the binary of each element
        WriteBinary(it, output_file);
}

// Write the binary of set type
template <typename U>
template <typename T>
void BinarySerialization<U>::WriteBinary(const std::set<T> &item, std::ofstream &output_file)
{
    size_t size = item.size();
    output_file.write(reinterpret_cast<const char *>(&size), sizeof(size_t)); // Write the size of set
    for (const auto &it : item)                                               // Write the binary of each element
        WriteBinary(it, output_file);
}

// Write the binary of unique_ptr type
template <typename U>
void BinarySerialization<U>::WriteBinary(const std::nullptr_t &item, std::ofstream &output_file)
{
    // Do nothing
}

// Write the binary of unique_ptr type
template <typename U>
template <typename T>
void BinarySerialization<U>::WriteBinary(const std::unique_ptr<T> &item, std::ofstream &output_file)
{
    if (item == nullptr) // If the unique_ptr is nullptr
        WriteBinary(nullptr, output_file);
    else
        WriteBinary(*item, output_file);
}

// Deserialize operation
// Read the binary of arithmetic type
template <typename U>
template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
BinarySerialization<U>::ReadBinary(T &item, std::ifstream &input_file)
{
    input_file.read(reinterpret_cast<char *>(&item), sizeof(item));
}

// Read the binary of string type
template <typename U>
void BinarySerialization<U>::ReadBinary(std::string &item, std::ifstream &input_file)
{
    size_t size;
    input_file.read(reinterpret_cast<char *>(&size), sizeof(size_t)); // Read the size of string
    item.resize(size);
    input_file.read(&item[0], size); // Read the string
}

// Read the binary of vector type
template <typename U>
template <typename T>
void BinarySerialization<U>::ReadBinary(std::vector<T> &item, std::ifstream &input_file)
{
    size_t size;
    input_file.read(reinterpret_cast<char *>(&size), sizeof(size_t)); // Read the size of vector
    item.resize(size);
    for (auto &it : item) // Read the binary of each element
        ReadBinary(it, input_file);
}

// Read the binary of pair type
template <typename U>
template <typename Key, typename Value>
void BinarySerialization<U>::ReadBinary(std::pair<Key, Value> &item, std::ifstream &input_file)
{
    ReadBinary(item.first, input_file);
    ReadBinary(item.second, input_file);
}

// Read the binary of map type
template <typename U>
template <typename Key, typename Value>
void BinarySerialization<U>::ReadBinary(std::map<Key, Value> &item, std::ifstream &input_file)
{
    size_t size;
    input_file.read(reinterpret_cast<char *>(&size), sizeof(size_t)); // Read the size of map
    item.clear();
    for (size_t i = 0; i < size; ++i) // Read the binary of each element
    {
        Key key;
        Value value;
        ReadBinary(key, input_file);
        ReadBinary(value, input_file);
        item[key] = value;
    }
}

// Read the binary of list type
template <typename U>
template <typename T>
void BinarySerialization<U>::ReadBinary(std::list<T> &item, std::ifstream &input_file)
{
    size_t size;
    input_file.read(reinterpret_cast<char *>(&size), sizeof(size_t)); // Read the size of list
    item.clear();
    for (size_t i = 0; i < size; ++i) // Read the binary of each element
    {
        T value;
        ReadBinary(value, input_file);
        item.push_back(value);
    }
}

// Read the binary of set type
template <typename U>
template <typename T>
void BinarySerialization<U>::ReadBinary(std::set<T> &item, std::ifstream &input_file)
{
    size_t size;
    input_file.read(reinterpret_cast<char *>(&size), sizeof(size_t)); // Read the size of set
    item.clear();
    for (size_t i = 0; i < size; ++i) // Read the binary of each element
    {
        T value;
        ReadBinary(value, input_file);
        item.insert(value);
    }
}

// Read the binary of unique_ptr type
template <typename U>
void BinarySerialization<U>::ReadBinary(std::nullptr_t &item, std::ifstream &input_file)
{
    item = nullptr; // Set the unique_ptr to nullptr
}

// Read the binary of unique_ptr type
template <typename U>
template <typename T>
void BinarySerialization<U>::ReadBinary(std::unique_ptr<T> &item, std::ifstream &input_file)
{
    item = std::make_unique<T>();
    if (input_file.peek() == std::ifstream::traits_type::eof()) // If the file is empty
        item = nullptr;
    else
        ReadBinary(*item, input_file);
}

// Function to serialize
template <typename U>
template <typename T>
void BinarySerialization<U>::Serialize(const T &item, const std::string &filename)
{
    std::ofstream output_file("../../data/bin/" + filename, std::ios::binary); // Open the file
    if (output_file.is_open())
    {
        WriteBinary(item, output_file); // Write the binary of item
        output_file.close();
        std::cout << "File saved successfully" << std::endl;
    }
    else
        std::cout << "Can not open the file!" << std::endl;
}

// Function to deserialize
template <typename U>
template <typename T>
void BinarySerialization<U>::Deserialize(T &item, const std::string &filename)
{
    std::ifstream input_file("../../data/bin/" + filename, std::ios::binary); // Open the file
    if (!input_file)
    {
        std::cout << "Can not find the file!\n";
        return;
    }
    if (input_file.is_open())
    {
        ReadBinary(item, input_file); // Read the binary of item
        input_file.close();
        std::cout << "File loaded successfully" << std::endl;
    }
}

// implement the serialization of user-defined type
struct UserDefinedType
{
    int idx;
    std::string name;
    std::vector<double> data;
    // serialize operation
    void Serialize_User(const std::string &filename)
    {
        std::string idx_str = std::to_string(idx); // Convert the elements to string
        std::string name_str = name;
        std::string data_str;
        for (const auto &it : data)
            data_str += std::to_string(it) + "\n";
        std::vector<std::string> item = {idx_str, name_str, data_str}; // Store the elements in a vector
        BinarySerialization<std::vector<std::string>> user_ser;        // Create a BinarySerialization object
        user_ser.Serialize(item, filename);
    }
    // deserialize operation
    void Deserialize_User(const std::string &filename)
    {
        BinarySerialization<std::vector<std::string>> user_ser; // Create a BinarySerialization object
        std::vector<std::string> item;
        user_ser.Deserialize(item, filename); // Deserialize the file
        idx = std::stoi(item[0]);             // Convert the string to the elements
        name = item[1];
        std::string flag = "\n";
        std::string s = item[2];
        size_t position = 0;
        data.clear();
        while ((position = s.find(flag, position)) != std::string::npos) // Split the string to get the elements of vector
        {
            std::string sub = s.substr(0, position);
            data.push_back(std::stod(sub));
            s.erase(0, position + flag.length());
        }
    }
};

// Function to test the serialization and deserialization
void testBinary()
{
    std::cout << "*************** Testing binary serialization/deserialization ***************" << std::endl;
    // test the serialization and deserialization of arithmetic types
    std::cout << "***** Testing serialization and deserialization of arithmetic types *****" << std::endl;
    BinarySerialization<int> itest;
    int i = 10;
    itest.Serialize(i, "int.bin");
    int i1;
    itest.Deserialize(i1, "int.bin");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << i1 << std::endl;
    double d = 5.36;
    BinarySerialization<double> dtest;
    dtest.Serialize(d, "double.bin");
    double d1;
    dtest.Deserialize(d1, "double.bin");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << d1 << std::endl;

    // test the serialization and deserialization of a string
    std::cout << "***** Testing serialization and deserialization of a string *****" << std::endl;
    BinarySerialization<std::string> stest;
    std::string s = "Hello World";
    stest.Serialize(s, "string.bin");
    std::string s1;
    stest.Deserialize(s1, "string.bin");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << s1 << std::endl;

    // test the serialization and deserialization of a pair
    std::cout << "***** Testing serialization and deserialization of a pair *****" << std::endl;
    BinarySerialization<std::pair<int, std::string>> ptest;
    std::pair<int, std::string> p;
    p.first = 1;
    p.second = "Hello";
    ptest.Serialize(p, "pair.bin");
    std::pair<int, std::string> ptest1;
    ptest.Deserialize(ptest1, "pair.bin");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << ptest1.first << ": " << ptest1.second << std::endl;

    // test the serialization and deserialization of a map
    std::cout << "***** Testing serialization and deserialization of a map *****" << std::endl;
    BinarySerialization<std::map<int, std::string>> test;
    std::map<int, std::string> m;
    m[1] = "Hello";
    m[2] = "World";
    test.Serialize(m, "map.bin");
    std::map<int, std::string> t;
    test.Deserialize(t, "map.bin");
    std::cout << "The result of deserialize: " << std::endl;
    for (const auto &it : t)
        std::cout << it.first << ": " << it.second << std::endl;

    // test the serialization and deserialization of a vector
    std::cout << "***** Testing serialization and deserialization of a vector *****" << std::endl;
    BinarySerialization<std::vector<std::string>> vtest;
    std::vector<std::string> v;
    v.push_back("Hello");
    v.push_back("World");
    vtest.Serialize(v, "vector.bin");
    std::vector<std::string> vtest2;
    vtest.Deserialize(vtest2, "vector.bin");
    std::cout << "The result of deserialize: " << std::endl;
    for (const auto &it : vtest2)
        std::cout << it << std::endl;

    // test the serialization and deserialization of a list
    std::cout << "***** Testing serialization and deserialization of a list *****" << std::endl;
    BinarySerialization<std::list<int>> test2;
    std::list<int> l;
    l.push_back(1);
    l.push_back(2);
    test2.Serialize(l, "list.bin");
    std::list<int> t2;
    test2.Deserialize(t2, "list.bin");
    std::cout << "The result of deserialize: " << std::endl;
    for (const auto &it : t2)
        std::cout << it << std::endl;

    // test the serialization and deserialization of a set
    std::cout << "***** Testing serialization and deserialization of a set *****" << std::endl;
    BinarySerialization<std::set<int>> setest;
    std::set<int> se;
    se.insert(1);
    se.insert(2);
    setest.Serialize(se, "set.bin");
    std::set<int> setest2;
    setest.Deserialize(setest2, "set.bin");
    std::cout << "The result of deserialize: " << std::endl;
    for (const auto &it : setest2)
        std::cout << it << std::endl;

    // test the serialization and deserialization of a user-defined type
    std::cout << "***** Testing serialization and deserialization of a user-defined type *****" << std::endl;
    UserDefinedType udt;
    udt.idx = 123;
    udt.name = "Li Hua";
    udt.data.push_back(1.1);
    udt.data.push_back(2.2);
    udt.data.push_back(3.3);
    udt.Serialize_User("UserDefinedType.bin");
    UserDefinedType udt1;
    udt1.Deserialize_User("UserDefinedType.bin");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << "ID: " << udt1.idx << std::endl
              << "Name: "
              << udt1.name << std::endl
              << "Data: ";
    for (const auto &it : udt1.data)
        std::cout << it << " ";
    std::cout << std::endl;

    // test the serialization and deserialization of a unique_ptr
    std::cout << "***** Testing serialization and deserialization of a unique_ptr *****" << std::endl;
    BinarySerialization<std::unique_ptr<int>> utest;
    std::unique_ptr<int> u(new int(10));
    utest.Serialize(u, "unique_ptr.bin");
    std::unique_ptr<int> utest1;
    utest.Deserialize(utest1, "unique_ptr.bin");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << *utest1 << std::endl;

    // test the serialization and deserialization of a nullptr
    std::cout << "***** Testing serialization and deserialization of a nullptr *****" << std::endl;
    BinarySerialization<std::unique_ptr<int>> ntest;
    std::unique_ptr<int> np = nullptr;
    ntest.Serialize(np, "nullptr.bin");
    std::unique_ptr<int> ntest1;
    ntest.Deserialize(ntest1, "nullptr.bin");
    std::cout << "The result of deserialize: " << std::endl;
    if (ntest1 == nullptr)
        std::cout << "nullptr" << std::endl;
    else
        std::cout << *ntest1 << std::endl;
    std::cout << std::endl;
}
