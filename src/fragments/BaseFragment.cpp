#include "Fragments.hpp"

BaseFragment::BaseFragment(int id) : Fragment(id){

                                     };

void BaseFragment::onCreate(const Message::Ptr& lastMessage) {
    dbController->updateFragmentState(lastMessage->from->id, fragmentId);
}

void BaseFragment::setDBController(DatabaseController* dbController) {
    this->dbController = dbController;
}

BaseFragment::~BaseFragment(){

};