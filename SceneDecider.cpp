#include "pch.h"
#include "SceneDecider.h"

#include <boost/regex.hpp>

using namespace std;
using namespace boost::algorithm;

SceneDecider::SceneDecider()
{
	this->scene = Scene::UNKNOWN;
	this->ticker = "";
	this->song = "";
}

const string MUSIC_CLEAR_SUFFIX = " CLEAR!";
const string MUSIC_FAIL_SUFFIX = " FAILED..";

std::string getSceneName(Scene scene)
{
	switch (scene) {
	case Scene::UNKNOWN:
	default:
		return "unknown";
	case Scene::IIDX_TITLE:
		return "Title";
	case Scene::IIDX_CARD_IN:
		return "Card In";
	case Scene::IIDX_CARD_OUT:
		return "Card Out";
	case Scene::IIDX_MODE_SELECT:
		return "Mode Select";
	case Scene::IIDX_MUSIC_SELECT:
		return "Music Select";
	case Scene::IIDX_SP_STAGE:
		return "SP Stage";
	case Scene::IIDX_RESULT:
		return "Result";
	case Scene::IIDX_DAN_SELECT:
		return "Dan Select";
	case Scene::IIDX_DAN_RESULT:
		return "Dan Result";
	case Scene::IIDX_ARENA_LOBBY:
		return "Arena Lobby";
	case Scene::IIDX_ARENA_BEFORE_SONG:
		return "Arean Before Song";
	case Scene::IIDX_ARENA_PODIUM:
		return "Arean Podium";
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

void SceneDecider::updateTicker(string ticker)
{
	Scene nextScene = Scene::UNKNOWN;

	// Sometimes the ticker is padded with spaces
	trim(ticker);
	LOG_DEBUG << "Ticker: " << ticker << std::endl;

	if (starts_with(ticker, "SELECT FROM")) {
		// Ignore
	}
	else if (boost::starts_with(ticker, "WELCOME TO BEATMANIA IIDX ")) {
		nextScene = Scene::IIDX_TITLE;
	}
	else if (ticker.compare("ENTRY") == 0) {
		nextScene = Scene::IIDX_CARD_IN;
		this->isArena = false;
	}
	else if (ticker.compare("MODE?") == 0) {
		nextScene = Scene::IIDX_MODE_SELECT;
	}
	else if (ticker.compare("ARENA MATCHING") == 0) {
		nextScene = Scene::IIDX_ARENA_LOBBY;
		this->isArena = true;
	}
	else if (ticker.compare("ARENA READY") == 0) {
		nextScene = Scene::IIDX_ARENA_BEFORE_SONG;
	}
	else if (ticker.compare("ARENA RESULT") == 0) {
		nextScene = Scene::IIDX_ARENA_PODIUM;
	}
	else if (ticker.compare("MUSIC SELECT!!") == 0) {
		// Music select
		nextScene = Scene::IIDX_MUSIC_SELECT;
	}
	else if (this->scene != Scene::IIDX_MUSIC_SELECT && ticker.compare("THANK YOU FOR PLAYING!!") == 0) {
		nextScene = Scene::IIDX_CARD_OUT;
	}
	else if (isDanSelection(ticker) == true) {
		nextScene = Scene::IIDX_DAN_SELECT;
	}
	else if (ticker.compare("SUCCESS") == 0 || ticker.compare("UNSUCCESS") == 0) {
		nextScene = Scene::IIDX_DAN_RESULT;
	}
	else if (!this->isArena && this->scene == Scene::IIDX_MUSIC_SELECT) {
		if (ticker.compare(this->ticker) == 0) {
			// Ticker will send the same song name when a song is decided

			// TODO: support DP
			this->song = ticker;
			nextScene = Scene::IIDX_SP_STAGE;
			LOG_INFO << "Stage start: " << this->song;
		}
	}
	else if (this->isArena && this->scene == Scene::IIDX_ARENA_BEFORE_SONG) {
		this->song = ticker;
		nextScene = Scene::IIDX_SP_STAGE;
		LOG_INFO << "Arena Stage start: " << this->song;
	}
	else if (this->scene == Scene::IIDX_SP_STAGE) {
		int tickerLength = ticker.length();
		int songLength = this->song.length();
		
		try {
			string suffix = ticker.substr(this->song.length());

			if (boost::ends_with(ticker, MUSIC_CLEAR_SUFFIX) || boost::ends_with(ticker, MUSIC_FAIL_SUFFIX)) {
				nextScene = Scene::IIDX_RESULT;
			}
		}
		catch (...) {
			LOG_ERROR << "Error deciding end of stage result";
		}
	}
	else if (ticker.compare(this->ticker.append(MUSIC_CLEAR_SUFFIX)) == 0 || ticker.compare(this->ticker.append(MUSIC_FAIL_SUFFIX)) == 0)
	{
		nextScene = Scene::IIDX_RESULT;
	}
	else if (this->scene == Scene::IIDX_RESULT && ticker.compare(this->song) == 0) {
		// Quick restart from result
		nextScene = Scene::IIDX_SP_STAGE;
	}
	else {
		string danSong = getDanSong(ticker);
		if (danSong.length() > 0) {
			nextScene = Scene::IIDX_SP_STAGE;
			this->song = getDanSong(ticker);
			LOG_INFO << "Dan stage start: " << this->song;
		}
	}

	if (nextScene != Scene::UNKNOWN && nextScene != this->scene) {
		LOG_INFO << "Scene Change: " << getSceneName(this->scene) << " > " << getSceneName(nextScene) << std::endl;
		this->scene = nextScene;

		// TODO: use websocket to update OBS scene
	}

	this->ticker = ticker;
}