## Particle System
### Description
A particle system is a collection of small images that, when viewed together, form a more complex object, such as fire, smoke, weather, or fireworks. Importantly, these complex effects are controlled by specifying the behavior of individual particles using properties such as initial position, velocity, and lifetime.

### Introduction
This research project has been developed by Gerard Martinez Garcia.

In this research the main objective where the following: 

- Do a research about Particle Systrems and his different implementations in videogame. 
- Be able to understand how Particle Systems are done and how we can create different types of particles taking into account their variables and characteristics.

### Market Study

Particle Systems are something that has been used practically since the beginning of the creation of games. Thus, being one of the most important things when creating the code of a video game. 

Here I will list a few examples of Particles implemented in videgames: 


![888661d64f8155bc81443d54bd5c20a4](https://user-images.githubusercontent.com/73245381/166168938-5b0e4a5d-acf1-4ff5-b4f0-41e7d2e16683.gif)

As it can be observe, here we see one of the most common uses when creating particles in video games, a particle that has a limited life according to its animation.

![giphy](https://user-images.githubusercontent.com/73245381/166169056-4a7648e1-01ca-41a7-9209-8aedca0df2f0.gif)

In this case, we observe the creation and destruction of a particle from its collision with another object

![170280-sample](https://user-images.githubusercontent.com/73245381/166169124-6daed9cf-9367-4f39-866e-6dc5638e42a7.gif)

Finally we see how there are particles that can be destroyed without having an interaction with a collision or its finalize animation. There are looped particles that can be limited by time.

### Select Aproach

For this personal research I have developed some basic particles such as a Bullet and a Explosion in order to visualize its creation and its different characteristics. 
The interaction of particles with external objects such as a collision has not been taken into account since we are talking about a base particle system. As I said, this are easy particles to implement that work perfectly and that can be used as a basis for future projects.

First of all, we must take into account the creation of the particles and the implementation of their variables, such as position, animation, speed and lifetime

```
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, uint delay)
{
	Particle* p = new Particle(particle);
				
	p->position.x = x;						
	p->position.y = y;						

	particles[lastParticle++] = p;
	lastParticle %= MAX_ACTIVE_PARTICLES;
}
```

In addition to taking into account the initialization of these with their respective animation

```
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
	explosion.anim.speed = 0.3f;

	// Laser Particle
	laser.anim.PushBack({ 104, 171, 80, 14 });
	laser.anim.PushBack({ 185, 170, 80, 16 });
	laser.speed = iPoint(1, 0);
	laser.lifetime = 500;
	laser.anim.loop = true;
	laser.anim.speed = 0.3f;
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
```

Thirdly, we have to take into account the iteration for all the created particles that we must do in the update. To later destroy those that have already reached their time limitation taking into account the frames

```
bool ModuleParticles::Update(float dt)
{
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
```

On the other hand, we will have to do the same iteration for the whole array of particles to draw them on the screen in case the particle is active.

```
bool ModuleParticles::PostUpdate()
{
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
```

Finally, we will have to change the file of our code and go to the Scene cpp, once inside we will have to implement the logic so that the particles are reflected on the screen once the action has been carried out

```
bool Scene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		app->moduleParticles->AddParticle(app->moduleParticles->laser, 300, 400, 0);

	}

	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		app->moduleParticles->AddParticle(app->moduleParticles->explosion, 300, 400, 0);
	}
		
	return true;
}
```
### Possible Improvements 

Taking into account the template that has been created, the next step would be to implement the functionality of interaction with other objects, a clear example could be the implementation of particles with an assigned collider to be able to collide with what could be a wall.

What would be needed to take into account many other code files, such as a Module Collisions that has not been taken into account to create this repository.

### Exercise 

Link to the template with the exercise created to test our knowledge of Particle Systems:

https://github.com/GerardMartinez02/Particle-System/tree/main/ParticleSystem_Handout

Inside it can be observed a series of TODOs in order to complete the template the entire template.  

Finally here we have the solution to the exercises: 

https://github.com/GerardMartinez02/Particle-System/tree/main/ParticleSystem_Solution

### Citations

Information and images:

- https://answers.unity.com/questions/1785183/how-to-make-3-bullets-fire-at-different-angles.html

- https://blog.udemy.com/how-to-make-a-2d-game-in-unity/

- https://www.pinterest.es/pin/609745237032901237/

Support library that has served to implement the code:

- [SDL](https://www.libsdl.org/projects/SDL/)

Tempalte used for the module:

- [Code template used as a base for this Audio and music manager construction](https://github.com/raysan5/game_project_template)
