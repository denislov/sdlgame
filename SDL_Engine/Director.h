
#if !defined(_DIRECTOR_H)
#define _DIRECTOR_H

#include "Object.h"
#include "Node.h"
#include "Window.h"
#include "Renderer.h"
#include "Scene.h"
#include "InputHandler.h"
#include "TextureCache.h"
#include <SDL2/SDL.h>
class Director : public Object
{

  private:
	static Director *pInstance;

	Window *_window;
	Renderer *_renderer;

	bool _running;

	float _secondPerFrame;
	bool _dispalyStates;

	Uint32 _lastTick;
	Uint32 _nextTick;

	int _currentFrame;
	int _lastFrame;
	long _lastTime;
	unsigned int _totalFrames;

	InputHandler *_eventDispather;

	TextureCache *_textureCache;
	std::string _platform;

	std::vector<Scene *> _children;
	Scene *_currentScene;
	Scene *_nextScene;

	bool _deleteRunningScene;

  private:
	Director();
	~Director();

  public:
	static Director *getInstance();
	void purge();

	bool init();

	void update();

	void setRunning(bool running);
	bool isRunning();

	InputHandler *getEventDispather();
	TextureCache *getTextureCache();

	void runWithScene(Scene *scene);
	void repalceScene(Scene *scene);
	void pushScene(Scene *scene);
	void popScene();

	void setSecondPerFrame(float secondPerFrame);

	void setDisplayStates(bool dispalyStates);
	bool isDisplayStates() const;

	void drawScene(float dt);

	Window *getWindow() const;
	Renderer *getRenderer() const;
	Size getVisibleSize();

  private:
	void handleScenes();
	void updateStates();
};
typedef Director TheDirector;

#endif // _DIRECTOR_H

