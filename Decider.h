#pragma once

using namespace std;
using namespace boost;

enum class Scene {
	// Default state
	UNKNOWN,

	TITLE, CARD_IN, CARD_OUT, MODE_SELECT,

	MUSIC_SELECT, STAGE, RESULT,
	
	DAN_SELECT, DAN_RESULT,

	ARENA_LOBBY, ARENA_BEFORE_SONG, ARENA_PODIUM, 
	
	BPL_LOBBY, BPL_BEFORE_SONG, BPL_PODIUM,
};

class Decider
{
private:
	string ticker;
	string song;
	bool isArena;
	Scene scene;
	map<Scene, string> sceneMap;

public:
	Decider();
	void initSceneMap(property_tree::ptree& ptree);
	void updateTicker(string text);
};

