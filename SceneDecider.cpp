#include "pch.h"
#include "SceneDecider.h"

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
	case Scene::IIDX_MUSIC_SELECT:
		return "Music Select";
	case Scene::IIDX_SP_STAGE:
		return "SP Stage";
	case Scene::IIDX_RESULT:
		return "Result";
	}
}

void SceneDecider::updateTicker(string ticker)
{
	Scene nextScene = Scene::UNKNOWN;

	// Sometimes the ticker is padded with spaces
	trim(ticker);

	if (starts_with(ticker, "SELECT FROM")) {
		// Ignore
	}
	else if (ticker.compare("MUSIC SELECT!!") == 0) {
		// Music select
		nextScene = Scene::IIDX_MUSIC_SELECT;
	}
	else if (this->scene == Scene::IIDX_MUSIC_SELECT) {
		if (ticker.compare(this->ticker) == 0) {
			// Ticker will send the same song name when a song is decided

			// TODO: support DP
			this->song = ticker;
			nextScene = Scene::IIDX_SP_STAGE;
		}
	}
	else if (this->scene == Scene::IIDX_SP_STAGE) {
		string suffix = ticker.substr(this->song.length());

		LOG_INFO << "Stage end: " << suffix << endl;

		if (suffix.compare(MUSIC_CLEAR_SUFFIX) == 0 || suffix.compare(MUSIC_FAIL_SUFFIX) == 0) {
			nextScene = Scene::IIDX_RESULT;
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

	if (nextScene != Scene::UNKNOWN && nextScene != this->scene) {
		LOG_INFO << "Scene Change: " << getSceneName(this->scene) << " > " << getSceneName(nextScene) << std::endl;
		this->scene = nextScene;

		// TODO: use websocket to update OBS scene
	}

	this->ticker = ticker;
}