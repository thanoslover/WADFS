#pragma once
#include <string>
#include <vector>

using namespace std;

struct Lump {
    int offset;
    int length;
    char name[9];
    char* data;

    Lump() : offset(0), length(0), name("\0") {}
};

struct node
{
    Lump* element;

    node* parent;
    vector<node*> children;

    node(Lump* e, node* p) : element(e), parent(p) {}
};

class Wad
{
    private:
        char magic [4];
        int n_descriptors;
        int offset;
        Lump* lumps;
        node* root;

    public:
        Wad();
        static void operator delete (void* w);
        static Wad* loadWad(const string &path);
        string getMagic();
        bool isContent(const string &path);
        bool isDirectory(const string &path);
        int getSize(const string &path);
        int getContents(const string &path, char *buffer, int length, int offset = 0);
        int getDirectory(const string &path, vector<string> *directory);
        void deletePrivate();
        node* getNode(const string &path);
};