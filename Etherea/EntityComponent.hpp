#pragma once

class EntityComponent {
public:
	EntityComponent() : enabled(true) {}
	virtual ~EntityComponent() = default;

	EntityComponent(EntityComponent const&) = delete;
	void operator=(EntityComponent const&) = delete;

	bool isEnabled() { return enabled; }
	void enable() { enabled = true; }
	void disable() { enabled = false; }
private:
	bool enabled;
};
