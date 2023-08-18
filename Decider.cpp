#include "pch.h"
#include "Decider.h"

#include <boost/regex.hpp>

using namespace std;
using namespace boost::algorithm;

Decider::Decider()
{
	this->scene = Scene::UNKNOWN;
	this->ticker = "";
	this->song = "";
}

void Decider::initSceneMap(boost::property_tree::ptree& ptree)
{
	this->sceneMap[Scene::TITLE] = ptree.get<string>("SCENE.title-screen");
	this->sceneMap[Scene::CARD_IN] = ptree.get<string>("SCENE.card-in");
	this->sceneMap[Scene::CARD_OUT] = ptree.get<string>("SCENE.card-out");
	this->sceneMap[Scene::MODE_SELECT] = ptree.get<string>("SCENE.mode-select");

	this->sceneMap[Scene::MUSIC_SELECT] = ptree.get<string>("SCENE.music-select");
	this->sceneMap[Scene::STAGE] = ptree.get<string>("SCENE.stage");
	this->sceneMap[Scene::RESULT] = ptree.get<string>("SCENE.result");

	this->sceneMap[Scene::DAN_SELECT] = ptree.get<string>("SCENE.dan-select");
	this->sceneMap[Scene::DAN_RESULT] = ptree.get<string>("SCENE.dan-result");

	this->sceneMap[Scene::ARENA_LOBBY] = ptree.get<string>("SCENE.arena-lobby");
	this->sceneMap[Scene::ARENA_BEFORE_SONG] = ptree.get<string>("SCENE.arena-before-song");
	this->sceneMap[Scene::ARENA_PODIUM] = ptree.get<string>("SCENE.arena-podium");

	this->sceneMap[Scene::BPL_LOBBY] = ptree.get<string>("SCENE.bpl-lobby");
	this->sceneMap[Scene::BPL_BEFORE_SONG] = ptree.get<string>("SCENE.bpl-before-song");
	this->sceneMap[Scene::BPL_PODIUM] = ptree.get<string>("SCENE.bpl-podium");
}

const string MUSIC_CLEAR_SUFFIX = " CLEAR!";
const string MUSIC_FAIL_SUFFIX = " FAILED..";

std::string getSceneName(Scene scene)
{
	switch (scene) {
	case Scene::UNKNOWN:
	default:
		return "unknown";
	case Scene::TITLE:
		return "Title";
	case Scene::CARD_IN:
		return "Card In";
	case Scene::CARD_OUT:
		return "Card Out";
	case Scene::MODE_SELECT:
		return "Mode Select";
	case Scene::MUSIC_SELECT:
		return "Music Select";
	case Scene::STAGE:
		return "Stage";
	case Scene::RESULT:
		return "Result";
	case Scene::DAN_SELECT:
		return "Dan Select";
	case Scene::DAN_RESULT:
		return "Dan Result";
	case Scene::ARENA_LOBBY:
		return "Arena Lobby";
	case Scene::ARENA_BEFORE_SONG:
		return "Arean Before Song";
	case Scene::ARENA_PODIUM:
		return "Arean Podium";
	case Scene::BPL_LOBBY:
		return "BPL Lobby";
	case Scene::BPL_BEFORE_SONG:
		return "BPL Before Song";
	case Scene::BPL_PODIUM:
		return "BPL Podium";
	}
}

bool isDanSelection(string ticker)
{
	if (
		ticker.compare("KAIDEN") == 0 ||
		ticker.compare("CHUDEN") == 0 ||
		ticker.compare("10TH DAN") == 0 ||
		ticker.compare("9TH DAN") == 0 ||
		ticker.compare("8TH DAN") == 0 ||
		ticker.compare("7TH DAN") == 0 ||
		ticker.compare("6TH DAN") == 0 ||
		ticker.compare("5TH DAN") == 0 ||
		ticker.compare("4TH DAN") == 0 ||
		ticker.compare("3RD DAN") == 0 ||
		ticker.compare("2ND DAN") == 0 ||
		ticker.compare("1ST DAN") == 0 ||
		ticker.compare("CLASS 1") == 0 ||
		ticker.compare("CLASS 2") == 0 ||
		ticker.compare("CLASS 3") == 0 ||
		ticker.compare("CLASS 4") == 0 ||
		ticker.compare("CLASS 5") == 0 ||
		ticker.compare("CLASS 6") == 0 ||
		ticker.compare("CLASS 7") == 0
		) {
		return true;
	}

	return false;
}

string getDanSong(string ticker) {
	boost::regex expr{ "^\\[(?:SINGLE|DOUBLE).*STAGE.*\\] (.+)  (?:BEGINNER|NORMAL|HYPER|ANOTHER|LEGGENDARIA)$" };
	boost::smatch what;
	if (boost::regex_search(ticker, what, expr)) {
		return what[1];
	}
	return "";
}

/**
* Determine the current scene based on 16-segment ticker content
* https://note.com/rest_r2/n/n0a7595f86e90
*/
void Decider::updateTicker(string ticker)
{
	Scene nextScene = Scene::UNKNOWN;

	// Sometimes the ticker is padded with spaces
	trim(ticker);
	LOG_DEBUG << "Ticker: " << ticker << std::endl;

	if (starts_with(ticker, "SELECT FROM")) {
		// Ignore
	}
	else if (boost::starts_with(ticker, "WELCOME TO BEATMANIA IIDX ")) {
		nextScene = Scene::TITLE;
	}
	else if (ticker.compare("ENTRY") == 0) {
		nextScene = Scene::CARD_IN;
		this->isArena = false;
	}
	else if (ticker.compare("MODE?") == 0) {
		nextScene = Scene::MODE_SELECT;
	}
	else if (ticker.compare("ARENA MATCHING") == 0) {
		nextScene = Scene::ARENA_LOBBY;
		this->isArena = true;
	}
	else if (ticker.compare("ARENA READY") == 0) {
		nextScene = Scene::ARENA_BEFORE_SONG;
	}
	else if (ticker.compare("ARENA RESULT") == 0) {
		nextScene = Scene::ARENA_PODIUM;
	}
	else if (ticker.compare("MUSIC SELECT!!") == 0) {
		// Music select
		nextScene = Scene::MUSIC_SELECT;
	}
	else if (this->scene != Scene::MUSIC_SELECT && ticker.compare("THANK YOU FOR PLAYING!!") == 0) {
		nextScene = Scene::CARD_OUT;
	}
	else if (isDanSelection(ticker) == true) {
		nextScene = Scene::DAN_SELECT;
	}
	else if (ticker.compare("SUCCESS") == 0 || ticker.compare("UNSUCCESS") == 0) {
		nextScene = Scene::DAN_RESULT;
	}
	else if (!this->isArena && this->scene == Scene::MUSIC_SELECT) {
		if (ticker.compare(this->ticker) == 0) {
			// Ticker will send the same song name when a song is decided
			this->song = ticker;
			nextScene = Scene::STAGE;
			LOG_INFO << "Stage start: " << this->song;
		}
	}
	else if (this->isArena && this->scene == Scene::ARENA_BEFORE_SONG) {
		this->song = ticker;
		nextScene = Scene::STAGE;
		LOG_INFO << "Arena Stage start: " << this->song;
	}
	else if (this->scene == Scene::STAGE) {
		if (boost::ends_with(ticker, MUSIC_CLEAR_SUFFIX) || boost::ends_with(ticker, MUSIC_FAIL_SUFFIX)) {
			nextScene = Scene::RESULT;
		}
	}
	else if (ticker.compare(this->ticker.append(MUSIC_CLEAR_SUFFIX)) == 0 || ticker.compare(this->ticker.append(MUSIC_FAIL_SUFFIX)) == 0)
	{
		nextScene = Scene::RESULT;
	}
	else if (this->scene == Scene::RESULT && ticker.compare(this->song) == 0) {
		// Quick restart from result
		nextScene = Scene::STAGE;
	}
	else {
		string danSong = getDanSong(ticker);
		if (danSong.length() > 0) {
			nextScene = Scene::STAGE;
			this->song = getDanSong(ticker);
			LOG_INFO << "Dan stage start: " << this->song;
		}
	}

	this->ticker = ticker;

	if (nextScene != Scene::UNKNOWN && nextScene != this->scene) {
		string nextSceneName = getSceneName(nextScene);

		LOG_INFO << "Scene Change: " << nextSceneName << std::endl;
		this->scene = nextScene;

		sendMessage(this->sceneMap[nextScene]);
	}
}