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
	explosion.anim.PushBack({ 274, 296, 33, 30 });
	explosion.anim.PushBack({ 313, 296, 33, 30 });
	explosion.anim.PushBack({ 346, 296, 33, 30 });
	explosion.anim.PushBack({ 382, 296, 33, 30 });
	explosion.anim.PushBack({ 419, 296, 33, 30 });
	explosion.anim.PushBack({ 457, 296, 33, 30 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.005f;

	// Laser Particle
	laser.anim.PushBack({ 104, 171, 80, 14 });
	laser.anim.PushBack({ 185, 170, 80, 16 });
	laser.speed = iPoint(1, 0);
	laser.lifetime = 900;
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
	// TODO 2: Create a loop (for) to iterate all the particles

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleParticles::PostUpdate()
{
	// TODO 3: Create a loop (for) to iterate all the particle array to draw them if any particle is active 

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			app->render->DrawTexture(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return true;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, uint delay)
{
	Particle* p = new Particle(particle);
	
	// TODO 1: Create the necesary variables for the Particles
			
	p->position.x = x;						
	p->position.y = y;						

	particles[lastParticle++] = p;
	lastParticle %= MAX_ACTIVE_PARTICLES;
}