#pragma once

enum class Scene {
	// Default state
	UNKNOWN,
	// IIDX
	IIDX_SP_STAGE, IIDX_DP_STAGE, IIDX_RESULT, IIDX_MUSIC_SELECT, IIDX_MONITOR_CHECK, IIDX_ATTRACT, IIDX_TITLE,
	IIDX_CARD_IN, IIDX_MODE_SELECT, IIDX_TEST_MENU, IIDX_DAN_SELECT, IIDX_DAN_RESULT, IIDX_CARD_OUT,
	IIDX_ARENA_LOBBY, IIDX_ARENA_BEFORE_SONG, IIDX_ARENA_PODIUM, IIDX_BPL_LOBBY, IIDX_BPL_BEFORE_SONG,
	IIDX_BPL_PODIUM, IIDX_DJVIP_PASS_SELECT, IIDX_ATTRACT_TUTORIAL, IIDX_DEMO_PLAY, IIDX_EXPERT_SELECT,
	IIDX_EXPERT_RESULT,
	// SDVX
	SDVX_MUSIC_SELECT, SDVX_MUSIC_SELECT_DELAY, SDVX_STAGE, SDVX_STAGE_DELAY, SDVX_RESULT, SDVX_RESULT_DELAY, SDVX_ATTRACT, SDVX_TITLE, SDVX_TEST_MENU, SDVX_COURSE_SELECT,
	SDVX_COURSE_RESULT
};

class SceneDecider
{
private:
	std::string ticker;
	std::string song;

	Scene scene;

public:
	SceneDecider();
	void updateTicker(std::string text);
};

