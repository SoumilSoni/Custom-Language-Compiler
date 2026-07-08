#include<bits/stdc++.h>
#include "scope.h"
using namespace std;

Scope::Scope(Scope* parent){
    this->parent=parent;
}

bool Scope::insert(const Symbol& symbol){
    // auto [it, inserted] = symbols.insert({symbol.name, symbol});
    auto result=symbols.insert({symbol.name,symbol});
    return result.second;
}

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
