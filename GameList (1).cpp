
#include <iostream>
#include "Game.h"
#include "mersenne-twister.h"
#include "GameList.h"
using namespace std;

// gamenode constrctor default constructor to just set the data
GameNode::GameNode(Game f) {
    this->data = f;
    this->link = nullptr;
}
// gamenode constructor with data as well link
GameNode::GameNode(Game theData, GameNode* theLink) {
    this->data = theData;
    this->link = theLink;
}

// function that return gamenode's link
GameNode* GameNode::getLink() const {
    return link;
}
// function that return gamenode's data
Game GameNode::getData() const {
    return data;
}
// function that set gamenode's data
void GameNode::setData(Game theData) {
    data = theData;
}
// function that set gamenode's link
void GameNode::setLink(GameNode* theLink) {
    link = theLink;
}

// deafult constructor for linked list
GameList::GameList() {
    this->head = nullptr;
}
// function to add a new game object in the beginning of the linked list
void GameList::addGame(Game f) { 
    // make a new node                                     
    GameNode* newNode = new GameNode(f, nullptr);
    // set the new nodes link with head
	newNode->setLink(head);
    // point head to new node
	head = newNode;
}
// function to undo the game which removes the first node and points head to the next one
bool GameList::undoGame() {
    // if head or the next link is nullptr then it shows that undo move is not possible
	if (head == nullptr || head -> getLink() == nullptr){
		cout << "Cannot undo." << endl;
		return false;
	}
    // if undo is possible then move head to point at next link and delete the first node
    GameNode* temp = head;
    head = head->getLink();
    delete temp;
    return true;
}
// function that returns the current first node's data i.e the last added game
Game GameList::getCurrentGame(){
    // if the head is nullptr then it will show an error message
    if (head == nullptr){
        cout << "error no game found" << endl;
		return Game();
	}
    // otherwise returns the latest data
    Game game = head -> getData();
	return game;
}