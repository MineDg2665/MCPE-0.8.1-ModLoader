#include <_pengine.hpp>
#ifdef ANDROID
#include <android/log.h>
#include <Minecraft.hpp>
#include <android_native_app_glue.h>
#include <main.hpp>
#include <android/AppPlatform_android.hpp>

void engine_handle_cmd(android_app* a1, int a2){
	std::string v26 = "???";
	ENGINE* engine = (ENGINE*) a1->userData;

	__android_log_print(ANDROID_LOG_ERROR, "MCPEDECOMP", "CMD %d", a2);
	switch(a2){
		case APP_CMD_INIT_WINDOW:
			if(engine->state->window){
				int v30;
				EGLConfig v31;
				int format;
				EGLint attrs[] = {
					EGL_SURFACE_TYPE, 4,
					EGL_DEPTH_SIZE, 16,
					EGL_STENCIL_SIZE, 8,
					EGL_RENDERABLE_TYPE, 1,
					EGL_NONE
				};
				EGLDisplay display = eglGetDisplay(0);
				eglInitialize(display, 0, 0);
				eglChooseConfig(display, attrs, &v31, 1, &v30);
				eglGetConfigAttrib(display, v31, 12334, &format);
				ANativeWindow_setBuffersGeometry(engine->state->window, 0, 0, format);
				eglChooseConfig(display, attrs, 0, 0, &v30);
				EGLConfig* v9 = new EGLConfig[v30]; //TODO check
				eglChooseConfig(display, attrs, v9, v30, &v30);
				EGLSurface selSurface;
				EGLConfig selConfig;
				for(int v8 = 0; v8 < v30; ++v8){
					EGLSurface surface = eglCreateWindowSurface(display, v9[v8], engine->state->window, 0);
					if ( surface )
					{
						selSurface = surface;
						selConfig = v9[v8];
						break;
					}
				}
				if(v9){
					delete[] v9;
				}
				EGLContext ctx = eglCreateContext(display, selConfig, 0, 0);
				if ( eglMakeCurrent(display, selSurface, selSurface, ctx) )
				{
					EGLint width, height;
					eglQuerySurface(display, selSurface, EGL_WIDTH, &width);
					eglQuerySurface(display, selSurface, EGL_HEIGHT, &height);
					EGLint v15 = width;
					EGLint v16 = height;
					engine->appCtx.field_0 = display;
					if ( v15 < v16 )
					{
						height = v15;
						width = v16;
					}

					engine->field_8 = display;
					engine->height = height;
					engine->appCtx.field_4 = ctx;
					engine->field_10 = ctx;
					engine->appCtx.field_8 = selSurface;
					engine->surface = selSurface;
					engine->width = width;
					glViewport(0, 0, width, height);
					if ( engine->field_24 )
					{
						engine->minecraft->context = engine->appCtx;
						for(auto&& l : AppPlatform::_singleton->listeners){
							l.second->onAppResumed();
						}

						engine->minecraft->setSize(width, height);
						engine->field_1C = 1;
					}
					eglSwapInterval(eglGetCurrentDisplay(), 2);
					engine->field_24 = 1;
				}
			}
			break;
		case APP_CMD_TERM_WINDOW:
			v26 = "APP_CMD_TERM_WINDOW";
			engine->field_1C = 0;
			engine_term_display(engine);
			break;
		case APP_CMD_GAINED_FOCUS:
			v26 = "APP_CMD_GAINED_FOCUS";
			engine->field_1C = 1;
			break;
		case APP_CMD_LOST_FOCUS:
			v26 = "APP_CMD_LOST_FOCUS";
			engine->field_1C = 1;
			break;
		case APP_CMD_SAVE_STATE:
			void *savedState;
			int savedStateSize;
			engine->minecraft->saveState(&savedState, &savedStateSize);
			if(savedStateSize > 0){
				a1->savedStateSize = savedStateSize;
				a1->savedState = savedState;
			}
			break;
		default:
			break;
	}
}
void engine_term_display(ENGINE* a1){
	a1->field_1C = 0;
	appPlatform._fireAppSuspended();
	__android_log_print(5, "MinecraftPE", "Native app suspended!\n");
	if ( a1->field_8 )
	{
		eglMakeCurrent(a1->field_8, 0, 0, 0);
		if ( a1->field_10 )
		{
			eglDestroyContext(a1->field_8, a1->field_10);
		}
		if ( a1->surface )
		{
			eglDestroySurface(a1->field_8, a1->surface);
		}
		eglTerminate(a1->field_8);
	}
	a1->field_8 = 0;
	a1->field_10 = 0;
	contextWasLost = 1;
}

int engine_handle_input(struct android_app* app, struct AInputEvent* event){
	//TODO
	__android_log_write(ANDROID_LOG_ERROR, "MCPE081DECOMP",
						"engine_handle_input - not implemented <_>");

	return 0;
}
#endif