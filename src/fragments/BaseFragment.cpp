#include "Fragments.hpp"

BaseFragment::BaseFragment(int id): Fragment(id){
    
};

void BaseFragment::setDBController(DatabaseController* dbController) {
    this->dbController = dbController;
}

BaseFragment::~BaseFragment() {
    
};