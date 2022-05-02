#include "ModuleParticles.h"

#include "App.h"

#include "Textures.h"
#include "Render.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;

	// Explosion Particle
	explosion.anim.PushBack({ 818, 884, 50, 50 });
	explosion.anim.PushBack({ 921, 869, 83, 70 });
	explosion.anim.PushBack({ 1012, 860, 94, 83 });
	explosion.anim.PushBack({ 1113, 858, 98, 90 });
	explosion.anim.PushBack({ 1220, 857, 98, 94 });
	explosion.anim.PushBack({ 1328, 858, 100, 95 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.005f;

	// Laser Particle
	laser.anim.PushBack({ 302, 494, 246, 47 });
	laser.anim.PushBack({ 537, 494, 238, 52 });
	laser.speed = iPoint(1, 0);
	laser.lifetime = 800;
	laser.anim.loop = true;
	laser.anim.speed = 0.001f;
}

ModuleParticles::~ModuleParticles()
{
	
}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = app->tex->Load("Assets/Textures/particles.png");
	
	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleParticles::Update(float dt)
{
	// TODO 2: Create a loop (for) to iterate all the Particles

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		

		// Call particle Update. If it has reached its lifetime, destroy it
		

	}

	return true;
}

bool ModuleParticles::PostUpdate()
{
	// TODO 3: Create a loop (for) to iterate all the particle array to draw them if any particle is active 

	
	return true;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, uint delay)
{
	Particle* p = new Particle(particle);
	
	// TODO 1: Create the necesary variables for the Particles


}