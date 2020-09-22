#include <iostream>
#include <vector>
#include <string>
#include<bits/stdc++.h> 
using std::string;
using std::vector;
using std::cin;

using namespace std;

class Hash 
{ 
    int BUCKET;    // No. of buckets 
    // Pointer to an array containing buckets 
    list<int> *table; 
public: 
    Hash(int V);  // Constructor 
  
    // inserts a key into hash table 
    void insertItem(int x); 
  
    // deletes a key from hash table 
    void deleteItem(int key); 
  
    // hash function to map values to key 
    int hashFunction(int x) { 
        return (x % BUCKET); 
    } 
  
    void displayHash(); 
}; 
  
Hash::Hash(int b) 
{ 
    this->BUCKET = b; 
    table = new list<int>[BUCKET]; 
} 
  
void Hash::insertItem(int key) 
{ 
    int index = hashFunction(key); 
    table[index].push_back(key);  
} 
  
void Hash::deleteItem(int key) 
{ 
  // get the hash index of key 
  int index = hashFunction(key); 
  
  // find the key in (inex)th list 
  list <int> :: iterator i; 
  for (i = table[index].begin(); 
           i != table[index].end(); i++) { 
    if (*i == key) 
      break; 
  } 
  
  // if key is found in hash table, remove it 
  if (i != table[index].end()) 
    table[index].erase(i); 
} 
  
// function to display hash table 
void Hash::displayHash() { 
  for (int i = 0; i < BUCKET; i++) { 
    cout << i; 
    for (auto x : table[i]) 
      cout << " --> " << x; 
    cout << endl; 
  } 
} 


struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}

vector<string> N_process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
        } else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        } else {
            string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);
        }
    return result;
}


vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    const int contacts_size=10000000;
    
    vector<string> contacts(contacts_size);

    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            contacts[queries[i].number]= queries[i].name;
        } 
        else if (queries[i].type == "del") {
            contacts[queries[i].number]="";    
        }
        else {
            if(contacts[queries[i].number]=="")
                result.push_back("not found");
            else 
                result.push_back(contacts[queries[i].number]);
        }
    return result;
}

int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}
