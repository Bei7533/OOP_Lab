#include "../include/XML.h"

// Serialize operation
// Write the XML of arithmetic type
template <typename T>
template <typename U>
typename std::enable_if<std::is_arithmetic<U>::value>::type
XMLSerialization<T>::WriteXML(const U &item, XMLElement *root)
{
    root->SetAttribute("type", "arithmetic");                       // Set the type of the element
    XMLElement *child = root->GetDocument()->NewElement("element"); // Create a new element
    child->SetText(item);                                           // Set the text of the element
    root->InsertEndChild(child);                                    // Insert the element to the end of the root
}

// Write the XML of string type
template <typename T>
void XMLSerialization<T>::WriteXML(const std::string &item, XMLElement *root)
{
    root->SetAttribute("type", "string");
    XMLElement *child = root->GetDocument()->NewElement("element");
    child->SetText(item.c_str()); // Set the text of the element
    root->InsertEndChild(child);
}

// Write the XML of vector type
template <typename T>
template <typename U>
void XMLSerialization<T>::WriteXML(const std::vector<U> &item, XMLElement *root)
{
    root->SetAttribute("type", "vector");
    for (auto &it : item) // Iterate the vector to write the XML of each element
    {
        XMLElement *child = root->GetDocument()->NewElement("element");
        WriteXML(it, child);
        root->InsertEndChild(child);
    }
}

// Write the XML of pair type
template <typename T>
template <typename Key, typename Value>
void XMLSerialization<T>::WriteXML(const std::pair<Key, Value> &item, XMLElement *root)
{
    root->SetAttribute("type", "pair");
    XMLElement *child = root->GetDocument()->NewElement("element");
    XMLElement *first = root->GetDocument()->NewElement("first");
    XMLElement *second = root->GetDocument()->NewElement("second");
    WriteXML(item.first, first);   // Write the XML of the first element
    WriteXML(item.second, second); // Write the XML of the second element
    child->InsertEndChild(first);
    child->InsertEndChild(second);
    root->InsertEndChild(child);
}

// Write the XML of map type
template <typename T>
template <typename Key, typename Value>
void XMLSerialization<T>::WriteXML(const std::map<Key, Value> &item, XMLElement *root)
{
    root->SetAttribute("type", "map");
    for (auto &it : item) // Iterate the map to write the XML of each element
    {
        XMLElement *child = root->GetDocument()->NewElement("element");
        XMLElement *key = root->GetDocument()->NewElement("key");
        XMLElement *value = root->GetDocument()->NewElement("value");
        WriteXML(it.first, key);
        WriteXML(it.second, value);
        child->InsertEndChild(key);
        child->InsertEndChild(value);
        root->InsertEndChild(child);
    }
}

// Write the XML of list type
template <typename T>
template <typename U>
void XMLSerialization<T>::WriteXML(const std::list<U> &item, XMLElement *root)
{
    root->SetAttribute("type", "list");
    for (auto &it : item) // Iterate the list to write the XML of each element
    {
        XMLElement *child = root->GetDocument()->NewElement("element");
        WriteXML(it, child);
        root->InsertEndChild(child);
    }
}

// Write the XML of set type
template <typename T>
template <typename U>
void XMLSerialization<T>::WriteXML(const std::set<U> &item, XMLElement *root)
{
    root->SetAttribute("type", "set");
    for (auto &it : item) // Iterate the set to write the XML of each element
    {
        XMLElement *child = root->GetDocument()->NewElement("element");
        WriteXML(it, child);
        root->InsertEndChild(child);
    }
}

// Write the XML of nullptr type
template <typename T>
void XMLSerialization<T>::WriteXML(const std::nullptr_t &item, XMLElement *root)
{
    root->SetAttribute("type", "nullptr");
    // Write nothing
}

// Write the XML of unique_ptr type
template <typename T>
template <typename U>
void XMLSerialization<T>::WriteXML(const std::unique_ptr<U> &item, XMLElement *root)
{
    root->SetAttribute("type", "unique_ptr");
    XMLElement *child = root->GetDocument()->NewElement("element");
    if (item == nullptr) // If the unique_ptr is nullptr, write the XML of nullptr
        WriteXML(nullptr, child);
    else
        WriteXML(*item, child);
    root->InsertEndChild(child);
}

// read the XML of arithmetic type
template <typename T>
template <typename U>
typename std::enable_if<std::is_arithmetic<U>::value>::type
XMLSerialization<T>::ReadXML(U &item, XMLElement *root)
{
    XMLElement *child = root->FirstChildElement("element");
    item = child->DoubleText();
}

// read the XML of string type
template <typename T>
void XMLSerialization<T>::ReadXML(std::string &item, XMLElement *root)
{
    XMLElement *child = root->FirstChildElement("element");
    item = child->GetText(); // Get the text of the element
}

// read the XML of vector type
template <typename T>
template <typename U>
void XMLSerialization<T>::ReadXML(std::vector<U> &item, XMLElement *root)
{
    XMLElement *child = root->FirstChildElement("element");
    while (child != nullptr) // Iterate the XML child to read the XML of each element
    {
        U value;
        ReadXML(value, child);
        item.push_back(value);
        child = child->NextSiblingElement("element");
    }
}

// read the XML of list type
template <typename T>
template <typename Key, typename Value>
void XMLSerialization<T>::ReadXML(std::pair<Key, Value> &item, XMLElement *root)
{
    XMLElement *child = root->FirstChildElement("element");
    ReadXML(item.first, child->FirstChildElement("first"));   // Read the XML of the first element
    ReadXML(item.second, child->FirstChildElement("second")); // Read the XML of the second element
}

// read the XML of map type
template <typename T>
template <typename Key, typename Value>
void XMLSerialization<T>::ReadXML(std::map<Key, Value> &item, XMLElement *root)
{
    XMLElement *child = root->FirstChildElement("element");
    while (child != nullptr) // Iterate the XML child to read the XML of each element
    {
        Key key;
        Value value;
        ReadXML(key, child->FirstChildElement("key"));
        ReadXML(value, child->FirstChildElement("value"));
        item[key] = value;
        child = child->NextSiblingElement("element");
    }
}

// read the XML of list type
template <typename T>
template <typename U>
void XMLSerialization<T>::ReadXML(std::list<U> &item, XMLElement *root)
{
    XMLElement *child = root->FirstChildElement("element");
    while (child != nullptr) // Iterate the XML child to read the XML of each element
    {
        U value;
        ReadXML(value, child);
        item.push_back(value);
        child = child->NextSiblingElement("element");
    }
}

// read the XML of set type
template <typename T>
template <typename U>
void XMLSerialization<T>::ReadXML(std::set<U> &item, XMLElement *root)
{
    XMLElement *child = root->FirstChildElement("element");
    while (child != nullptr) // Iterate the XML child to read the XML of each element
    {
        U value;
        ReadXML(value, child);
        item.insert(value);
        child = child->NextSiblingElement("element");
    }
}

// read the XML of nullptr type
template <typename T>
void XMLSerialization<T>::ReadXML(std::nullptr_t &item, XMLElement *root)
{
    XMLElement *child = root->FirstChildElement("element");
    item = nullptr;
}

// read the XML of unique_ptr type
template <typename T>
template <typename U>
void XMLSerialization<T>::ReadXML(std::unique_ptr<U> &item, XMLElement *root)
{
    item = std::make_unique<U>();
    XMLElement *child = root->FirstChildElement("element");
    const char *attribute = child->FirstAttribute()->Value();
    std::string nullp = "nullptr";
    if (nullp.compare(attribute) == 0) // If the unique_ptr is nullptr, set the unique_ptr to nullptr
        item = nullptr;
    else
        ReadXML(*item, child);
}

// Function to serialize the object to XML file
template <typename T>
void XMLSerialization<T>::Serialize(const T &item, const std::string &filename)
{
    XMLDocument doc;
    XMLDeclaration *declaration = doc.NewDeclaration(); // Create the XML declaration
    doc.InsertEndChild(declaration);
    XMLElement *root = doc.NewElement("root"); // Create the root element
    WriteXML(item, root);                      // Write the XML of the object
    doc.InsertEndChild(root);
    std::string file = "../../data/xml/" + filename; // Set the file path
    if (doc.SaveFile(file.c_str()) == XML_SUCCESS)   // Save the XML document to the file
        std::cout << "File saved successfully" << std::endl;
    else
        std::cout << "Error in saving file" << std::endl;
}

// Function to deserialize the object from XML file
template <typename T>
void XMLSerialization<T>::Deserialize(T &item, const std::string &filename)
{
    XMLDocument doc;
    std::string file = "../../data/xml/" + filename; // Set the file path
    if (doc.LoadFile(file.c_str()) == XML_SUCCESS)   // Load the XML document from the file
    {
        XMLElement *root = doc.RootElement();
        ReadXML(item, root);
        std::cout << "File loaded successfully" << std::endl;
    }
    else
    {
        std::cout << "Error in loading file" << std::endl;
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
        for (auto &it : data) // Convert the vector to string
            data_str += std::to_string(it) + "\n";
        std::vector<std::string> item = {idx_str, name_str, data_str}; // Store the elements in a vector
        XMLSerialization<std::vector<std::string>> user_ser;           // Create the XMLSerialization object
        user_ser.Serialize(item, filename);
    }

    void Deserialize_User(const std::string &filename)
    {
        XMLSerialization<std::vector<std::string>> user_ser;
        std::vector<std::string> item;
        user_ser.Deserialize(item, filename); // Deserialize the XML file to the vector
        idx = std::stoi(item[0]);             // Convert the elements to the corresponding type
        name = item[1];
        std::string flag = "\n";
        std::string s = item[2];
        size_t position = 0;
        data.clear();
        while ((position = s.find(flag, position)) != std::string::npos) // Convert the string to vector
        {
            std::string sub = s.substr(0, position);
            data.push_back(std::stod(sub));
            s.erase(0, position + flag.length());
        }
    }
};

// Function to test the serialization and deserialization
void testXML()
{
    std::cout << "*************** Testing XML serialization/deserialization ***************" << std::endl;

    // test the serialization and deserialization of arithmetic types
    std::cout << "***** Testing serialization and deserialization of arithmetic types *****" << std::endl;
    XMLSerialization<int> itest;
    int i = 10;
    itest.Serialize(i, "int.xml");
    int i1;
    itest.Deserialize(i1, "int.xml");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << i1 << std::endl;
    double d = 5.36;
    XMLSerialization<double> dtest;
    dtest.Serialize(d, "double.xml");
    double d1;
    dtest.Deserialize(d1, "double.xml");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << d1 << std::endl;

    // test the serialization and deserialization of a string
    std::cout << "***** Testing serialization and deserialization of a string *****" << std::endl;
    XMLSerialization<std::string> stest;
    std::string s = "Hello World";
    stest.Serialize(s, "string.xml");
    std::string s1;
    stest.Deserialize(s1, "string.xml");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << s1 << std::endl;

    // test the serialization and deserialization of a pair
    std::cout << "***** Testing serialization and deserialization of a pair *****" << std::endl;
    XMLSerialization<std::pair<int, std::string>> ptest;
    std::pair<int, std::string> p;
    p.first = 1;
    p.second = "Hello";
    ptest.Serialize(p, "pair.xml");
    std::pair<int, std::string> ptest1;
    ptest.Deserialize(ptest1, "pair.xml");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << ptest1.first << ": " << ptest1.second << std::endl;

    // test the serialization and deserialization of a map
    std::cout << "***** Testing serialization and deserialization of a map *****" << std::endl;
    XMLSerialization<std::map<int, std::string>> test;
    std::map<int, std::string> m;
    m[1] = "Hello";
    m[2] = "World";
    test.Serialize(m, "map.xml");
    std::map<int, std::string> t;
    test.Deserialize(t, "map.xml");
    std::cout << "The result of deserialize: " << std::endl;
    for (const auto &it : t)
        std::cout << it.first << ": " << it.second << std::endl;

    // test the serialization and deserialization of a vector
    std::cout << "***** Testing serialization and deserialization of a vector *****" << std::endl;
    XMLSerialization<std::vector<std::string>> vtest;
    std::vector<std::string> v;
    v.push_back("Hello");
    v.push_back("World");
    vtest.Serialize(v, "vector.xml");
    std::vector<std::string> vtest2;
    vtest.Deserialize(vtest2, "vector.xml");
    std::cout << "The result of deserialize: " << std::endl;
    for (const auto &it : vtest2)
        std::cout << it << std::endl;

    // test the serialization and deserialization of a list
    std::cout << "***** Testing serialization and deserialization of a list *****" << std::endl;
    XMLSerialization<std::list<int>> test2;
    std::list<int> l;
    l.push_back(1);
    l.push_back(2);
    test2.Serialize(l, "list.xml");
    std::list<int> t2;
    test2.Deserialize(t2, "list.xml");
    std::cout << "The result of deserialize: " << std::endl;
    for (const auto &it : t2)
        std::cout << it << std::endl;

    // test the serialization and deserialization of a set
    std::cout << "***** Testing serialization and deserialization of a set *****" << std::endl;
    XMLSerialization<std::set<int>> setest;
    std::set<int> se;
    se.insert(1);
    se.insert(2);
    setest.Serialize(se, "set.xml");
    std::set<int> setest2;
    setest.Deserialize(setest2, "set.xml");
    std::cout << "The result of deserialize: " << std::endl;
    for (const auto &it : setest2)
        std::cout << it << std::endl;

    // test the serialization and deserialization of user defined type
    std::cout << "***** Testing serialization and deserialization of user defined type *****" << std::endl;
    UserDefinedType udt;
    udt.idx = 123;
    udt.name = "Li Hua";
    udt.data.push_back(1.1);
    udt.data.push_back(2.2);
    udt.data.push_back(3.3);
    udt.Serialize_User("UserDefinedType.xml");
    UserDefinedType udt1;
    udt1.Deserialize_User("UserDefinedType.xml");
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
    XMLSerialization<std::unique_ptr<int>> utest;
    std::unique_ptr<int> u(new int(10));
    utest.Serialize(u, "unique_ptr.xml");
    std::unique_ptr<int> utest1;
    utest.Deserialize(utest1, "unique_ptr.xml");
    std::cout << "The result of deserialize: " << std::endl;
    std::cout << *utest1 << std::endl;

    // test the serialization and deserialization of a nullptr
    std::cout << "***** Testing serialization and deserialization of a nullptr *****" << std::endl;
    XMLSerialization<std::unique_ptr<int>> ntest;
    std::unique_ptr<int> np = nullptr;
    ntest.Serialize(np, "nullptr.xml");
    std::unique_ptr<int> ntest1;
    ntest.Deserialize(ntest1, "nullptr.xml");
    std::cout << "The result of deserialize: " << std::endl;
    if (ntest1 == nullptr)
        std::cout << "nullptr" << std::endl;
    else
        std::cout << *ntest1 << std::endl;
}
