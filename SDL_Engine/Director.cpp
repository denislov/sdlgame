#include "Director.h"
#include "SDL_image.h"
#include "PoolManager.h"
Director *Director::pInstance = nullptr;

Director::Director() : _window(nullptr),
					   _renderer(nullptr),
					   _currentScene(nullptr),
					   _nextScene(nullptr),
					   _running(false),
					   _secondPerFrame(1 / 60.f),
					   _lastFrame(0),
					   _lastTick(0),
					   _currentFrame(0),
					   _nextTick(0),
					   _lastTime(0),
					   _dispalyStates(true),
					   _totalFrames(0),
					   _eventDispather(nullptr),
					   _deleteRunningScene(false)
{
	_eventDispather = new InputHandler();
	_textureCache = new TextureCache();
	_name = "Director";
}
Director::~Director()
{

	for (auto iter = _children.begin(); iter != _children.end();)
	{
		auto scene = *iter;
		iter = _children.erase(iter);
		scene->onExit();
		scene->release();
	}

	_currentScene = nullptr;
	_nextScene = nullptr;
	_renderer->release();
	_window->release();
	_textureCache->release();
	_eventDispather->release();
	IMG_Quit();
	SDL_Quit();
}
Director *Director::getInstance()
{
	if (pInstance == nullptr)
		pInstance = new Director();
	return pInstance;
}

bool Director::init()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);
	_window = Window::create("SDLGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 700, SDL_WINDOW_SHOWN);
	_renderer = Renderer::create(_window, -1, SDL_RENDERER_ACCELERATED);
	_window->retain();
	_renderer->retain();
	_running = true;
	_platform = SDL_GetPlatform();
	printf("the current platform is %s\n", _platform.c_str());
	return true;
}

void Director::update()
{

	Uint32 currentTick = SDL_GetTicks();
	if (currentTick >= _nextTick)
	{
		++_totalFrames;
		++_currentFrame;

		float dt = _secondPerFrame;
		_lastTick = currentTick;
		_nextTick = _lastTick + (Uint32)(_secondPerFrame * 1000);

		this->drawScene(dt);
	}
	_eventDispather->update();
	this->handleScenes();

	this->updateStates();
}
void Director::drawScene(float dt)
{
	_renderer->renderClear();
	if (_currentScene != nullptr)
		_currentScene->visit();
	_renderer->renderPresent();
}
void Director::handleScenes()
{
	if (_nextScene)
	{
		if (_currentScene)
			_currentScene->onExit();
		if (_deleteRunningScene)
		{
			_currentScene->release();
			_deleteRunningScene = false;
		}
		_currentScene = _nextScene;
		_currentScene->onEnter();
		_nextScene = nullptr;
	}
}
void Director::updateStates()
{
	if (SDL_GetTicks() - _lastTime >= 1000)
	{
		_lastFrame = _currentFrame;
		_currentFrame = 0;
		_lastTime = SDL_GetTicks();

		if (_dispalyStates)
		{
			printf("FPS:%d\n", _lastFrame);
		}
	}
}

void Director::runWithScene(Scene *scene)
{
	pushScene(scene);
}

void Director::repalceScene(Scene *scene)
{
	if (_currentScene == nullptr)
	{
		runWithScene(scene);
		_deleteRunningScene = false;
	}
	if (_currentScene == scene)
		return;
	scene->retain();
	_children.pop_back();
	_children.push_back(scene);
	_deleteRunningScene = true;
	_nextScene = scene;
}
void Director::pushScene(Scene *scene)
{
	_children.push_back(scene);
	scene->retain();
	_nextScene = scene;
	_deleteRunningScene = false;
}
void Director::popScene()
{
	int size = _children.size();
	if (size == 1)
		_running = false;
	else
	{
		_children.pop_back();
		_deleteRunningScene = true;
		_nextScene = _children.back();
	}
}

void Director::purge()
{
	this->release();
}
Window *Director::getWindow() const
{
	return _window;
}
Renderer *Director::getRenderer() const
{
	return _renderer;
}
Size Director::getVisibleSize()
{
	return _window->getWindowSize();
}
void Director::setRunning(bool running)
{
	_running = running;
}
bool Director::isRunning()
{
	return _running;
}
void Director::setDisplayStates(bool dispalyStates)
{
	_dispalyStates = dispalyStates;
}
bool Director::isDisplayStates() const
{
	return _dispalyStates;
}
void Director::setSecondPerFrame(float secondPerFrame)
{
	_secondPerFrame = secondPerFrame;
}
InputHandler *Director::getEventDispather()
{
	return _eventDispather;
}
TextureCache *Director::getTextureCache()
{
	return _textureCache;
}