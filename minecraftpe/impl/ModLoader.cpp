#include <ModLoader.hpp>
#include <dlfcn.h>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <Minecraft.hpp>

#ifdef __ANDROID__
#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "ModLoader", __VA_ARGS__)
#define ERR(...) __android_log_print(ANDROID_LOG_ERROR, "ModLoader", __VA_ARGS__)
#else
#define LOG(...) do { printf("[ModLoader] "); printf(__VA_ARGS__); printf("\n"); } while(0)
#define ERR(...) do { fprintf(stderr, "[ModLoader ERROR] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } while(0)
#endif

ModLoader* ModLoader::instance = nullptr;

ModLoader::ModLoader() : mc(nullptr) {
	instance = this;
	modsPath[0] = 0;
}

ModLoader::~ModLoader() {
	unloadAll();
	instance = nullptr;
}

void ModLoader::init(Minecraft* minecraft) {
	mc = minecraft;

	std::string basePath = mc->dataPathMaybe;
	if (basePath.empty()) {
		basePath = ".";
	}

	std::string fullPath = basePath + "/games/com.mojang/mods";

	std::string p1 = basePath + "/games";
	std::string p2 = p1 + "/com.mojang";
	std::string p3 = p2 + "/mods";

	mkdir(p1.c_str(), 0777);
	mkdir(p2.c_str(), 0777);
	mkdir(p3.c_str(), 0777);

	strncpy(modsPath, fullPath.c_str(), sizeof(modsPath) - 1);
	modsPath[sizeof(modsPath) - 1] = 0;

	LOG("=== ModLoader started ===");
	LOG("Mods path: %s", modsPath);

	loadAll();
}

void ModLoader::loadAll() {
	DIR* dir = opendir(modsPath);
	if (!dir) {
		ERR("Cannot open %s", modsPath);
		return;
	}

	struct dirent* ent;
	while ((ent = readdir(dir))) {
		const char* n = ent->d_name;
		size_t len = strlen(n);
		if (len < 4) continue;
		if (strcmp(n + len - 3, ".so") != 0) continue;

		char path[512];
		snprintf(path, sizeof(path), "%s/%s", modsPath, n);

		void* handle = dlopen(path, RTLD_LAZY);
		if (!handle) {
			ERR("dlopen %s: %s", n, dlerror());
			continue;
		}

		typedef Mod* (*CreateFn)();
		CreateFn create = (CreateFn)dlsym(handle, "create_mod");
		if (!create) {
			ERR("no create_mod() in %s", n);
			dlclose(handle);
			continue;
		}

		Mod* mod = create();
		if (!mod) {
			dlclose(handle);
			continue;
		}

		Entry e;
		e.handle = handle;
		e.mod = mod;
		mods.push_back(e);

		LOG("Loaded mod: %s v%s", mod->name(), mod->version());
		mod->onStart(mc);
	}

	closedir(dir);
	LOG("Total mods loaded: %d", (int)mods.size());
}

void ModLoader::unloadAll() {
	for (size_t i = 0; i < mods.size(); i++) {
		mods[i].mod->onStop();
		delete mods[i].mod;
		dlclose(mods[i].handle);
	}
	mods.clear();
}

void ModLoader::hookTick() {
	for (size_t i = 0; i < mods.size(); i++)
		mods[i].mod->onTick(mc);
}

void ModLoader::hookRender(float delta) {
	for (size_t i = 0; i < mods.size(); i++)
		mods[i].mod->onRender(mc, delta);
}

void ModLoader::hookGUI() {
	for (size_t i = 0; i < mods.size(); i++)
		mods[i].mod->onGUI(mc);
}

bool ModLoader::hookTouch(int action, float x, float y) {
	for (size_t i = 0; i < mods.size(); i++)
		if (mods[i].mod->onTouch(mc, action, x, y))
			return true;
	return false;
}

bool ModLoader::hookKey(int key, bool pressed) {
	for (size_t i = 0; i < mods.size(); i++)
		if (mods[i].mod->onKey(mc, key, pressed))
			return true;
	return false;
}

void ModLoader::hookMouseMove(int x, int y) {
	for (size_t i = 0; i < mods.size(); i++)
		mods[i].mod->onMouseMove(mc, x, y);
}

void ModLoader::hookMouseDown(int button, int x, int y) {
	for (size_t i = 0; i < mods.size(); i++)
		mods[i].mod->onMouseDown(mc, button, x, y);
}

void ModLoader::hookMouseUp(int button, int x, int y) {
	for (size_t i = 0; i < mods.size(); i++)
		mods[i].mod->onMouseUp(mc, button, x, y);
}
