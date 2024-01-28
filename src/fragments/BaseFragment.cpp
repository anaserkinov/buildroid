#include "Fragments.hpp"

BaseFragment::BaseFragment(int id) : Fragment(id){

                                     };

void BaseFragment::onCreate(int16_t type, const std::shared_ptr<void>& data) {
    Fragment::onCreate(type, data);
}

void BaseFragment::setDBController(DatabaseController* dbController) {
    this->dbController = dbController;
}

BaseFragment::~BaseFragment(){

};