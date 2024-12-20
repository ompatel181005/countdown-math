// class that creates nodes for the linked list that stores Game object as data
class GameNode
{
private:
    // data hold the game object
    Game data;
    // link holds the address to the next node in the linked list
    GameNode* link;
public:
    GameNode(Game f);
    GameNode(Game theData, GameNode* theLink);
    GameNode* getLink() const;
    Game getData() const;
    void setData(Game theData);
    void setLink(GameNode* theLink);

};
// class that creates the linked list and does changes in it
class GameList
{
private:
	GameNode* head;

public:
	GameList();
	void addGame(Game f);
	bool undoGame();
	Game getCurrentGame();
};