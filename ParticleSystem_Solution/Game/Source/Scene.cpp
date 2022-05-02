#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "ModuleParticles.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	img = app->tex->Load("Assets/Textures/test.png");
	app->audio->PlayMusic("Assets/Audio/Music/music_spy.ogg");
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// TODO 4: Shoot lasers when the player hits 1

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		app->moduleParticles->AddParticle(app->moduleParticles->laser, 150, 400, 0);

	}

	// TODO 5: Make an explosion when the player hits 2

	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		app->moduleParticles->AddParticle(app->moduleParticles->explosion, 300, 400, 0);
	}
		
	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
