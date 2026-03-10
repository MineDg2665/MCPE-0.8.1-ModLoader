#pragma once

#include <vector>
#include <string>

struct Minecraft;

class Mod {
public:
	virtual ~Mod() {}
	virtual const char* name() = 0;
	virtual const char* version() { return "1.0"; }
	virtual void onStart(Minecraft* mc) {}
	virtual void onStop() {}
	virtual void onTick(Minecraft* mc) {}
	virtual void onRender(Minecraft* mc, float delta) {}
	virtual void onGUI(Minecraft* mc) {}
	virtual bool onTouch(Minecraft* mc, int action, float x, float y) { return false; }
	virtual bool onKey(Minecraft* mc, int key, bool pressed) { return false; }
	virtual void onMouseMove(Minecraft* mc, int x, int y) {}
	virtual void onMouseDown(Minecraft* mc, int button, int x, int y) {}
	virtual void onMouseUp(Minecraft* mc, int button, int x, int y) {}
};

#define REGISTER_MOD(cls) extern "C" Mod* create_mod() { return new cls(); }

class ModLoader {
public:
	static ModLoader* instance;
	Minecraft* mc;

	ModLoader();
	~ModLoader();

	void init(Minecraft* minecraft);
	void hookTick();
	void hookRender(float delta);
	void hookGUI();
	bool hookTouch(int action, float x, float y);
	bool hookKey(int key, bool pressed);
	void hookMouseMove(int x, int y);
	void hookMouseDown(int button, int x, int y);
	void hookMouseUp(int button, int x, int y);

private:
	struct Entry { void* handle; Mod* mod; };
	std::vector<Entry> mods;
	char modsPath[512];
	void loadAll();
	void unloadAll();
};
