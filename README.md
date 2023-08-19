# StreamKit

My attempt to learn how to write a hook for __redacted__.

## Building the Project

[vcpkg](https://vcpkg.io/en/) is used to manage dependencies. For the ease of usage, all the packages are installed as x64-static.

The following libraries are required:

* websocketpp
* boost (probably only needs part of it, but I forgot to keep track of what subpackages were used)
* minhook
* nlohmann
* cryptopp

## Scene Switching

Based on the wonderful projects [SceneTwoDeluxe](https://github.com/Radioo/SceneTwoDeluxe) and [TickerHook](https://github.com/Radioo/TickerHook) by Radioo.

I can't do reverse engineering, so I wondered if I can just use the ticker changes to deduce the current scene, and send scene changing command to OBS instead.

The flow of 16-segment display is explained [here](https://note.com/rest_r2/n/n0a7595f86e90) and it is not likely to dramatically changed between versions. Likewise, the addresses of current scene doesn't need to be found whenever there is a new datecode.

BPL flow is currently unsupported.

OBS Authentication is also supported.

### Usage

![Usage](docs/setup.png?raw=true "How to Setup")

I tried to add a reconnection flow but websocketpp seems to have a [bad memory leak](https://github.com/zaphoyd/websocketpp/issues/754) whenever a failed connection occurs. So please start OBS before starting the game.

## Other Features

Coming soon. I will probably add the ability to post a capture of result screen to a discord server through API key.