#ifndef XML_H
#define XML_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <memory>
#include "../lib/tinyxml2.h"

using namespace tinyxml2;

template <typename T>
class XMLSerialization
{
public:
    template <typename U>
    typename std::enable_if<std::is_arithmetic<U>::value>::type
    WriteXML(const U &item, XMLElement *root);

    void WriteXML(const std::string &item, XMLElement *root);

    template <typename U>
    void WriteXML(const std::vector<U> &item, XMLElement *root);

    template <typename Key, typename Value>
    void WriteXML(const std::pair<Key, Value> &item, XMLElement *root);

    template <typename Key, typename Value>
    void WriteXML(const std::map<Key, Value> &item, XMLElement *root);

    template <typename U>
    void WriteXML(const std::list<U> &item, XMLElement *root);

    template <typename U>
    void WriteXML(const std::set<U> &item, XMLElement *root);

    void WriteXML(const std::nullptr_t &item, XMLElement *root);

    template <typename U>
    void WriteXML(const std::unique_ptr<U> &item, XMLElement *root);

    template <typename U>
    typename std::enable_if<std::is_arithmetic<U>::value>::type
    ReadXML(U &item, XMLElement *root);

    void ReadXML(std::string &item, XMLElement *root);

    template <typename U>
    void ReadXML(std::vector<U> &item, XMLElement *root);

    template <typename Key, typename Value>
    void ReadXML(std::pair<Key, Value> &item, XMLElement *root);

    template <typename Key, typename Value>
    void ReadXML(std::map<Key, Value> &item, XMLElement *root);

    template <typename U>
    void ReadXML(std::list<U> &item, XMLElement *root);

    template <typename U>
    void ReadXML(std::set<U> &item, XMLElement *root);

    void ReadXML(std::nullptr_t &item, XMLElement *root);

    template <typename U>
    void ReadXML(std::unique_ptr<U> &item, XMLElement *root);

    void Serialize(const T &item, const std::string &filename);

    void Deserialize(T &item, const std::string &filename);
};

void testXML();

#endif