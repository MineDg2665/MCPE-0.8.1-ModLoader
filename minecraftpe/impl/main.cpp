#ifndef ANDROID
#include <_types.h>
#include <utils.h>
#include <sys/time.h>
#include <util/Random.hpp>
#include <stdio.h>
#include <math/Mth.hpp>
#include <AppPlatform.hpp>
#include <App.hpp>
#include <AppPlatform_sdl.hpp>
#include <utf8proc.h>
#include <util/Util.hpp>
#include <unigl.h>

AppPlatform_sdl appPlatform;
#ifdef __WIN32__
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
#else
int main(){
#endif
	struct timeval start;
	gettimeofday(&start, 0);
	startedAtSec = start.tv_sec;
	appPlatform.init();
	return 0;
}
#endif
