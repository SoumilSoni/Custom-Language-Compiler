#include<bits/stdc++.h>
#include "scope.h"
using namespace std;


//Constructor of the scope 
Scope::Scope(Scope* parent){
    this->parent=parent;
}

//This function insert the symbol in the map and identify whether that same variable is declared in the same scope earlier
bool Scope::insert(const Symbol& symbol){
    // auto [it, inserted] = symbols.insert({symbol.name, symbol});
    auto result=symbols.insert({symbol.name,symbol});
    return result.second; //returns true if the variable is inserted in the map and false if inserting variable already exisit in the map
}

//This function is used to find the variable in the current or outer scope and return the reference of that symbol
Symbol* Scope::lookup(const string &name){
    Scope* currScope=this;
    while(currScope!=nullptr){
        auto ptr=currScope->symbols.find(name);
        if(ptr!=currScope->symbols.end()){
            return &(ptr->second);
        }
        currScope=currScope->parent;
    }
    return nullptr;
}
