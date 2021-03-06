#include <pd/pch/PCH.h>
#include <pd/ecs/sys/dock/DockWidgetRemovalSystem.hpp>

#include <pd/ecs/cmp/root/WidgetsOwner.hpp>
#include <pd/ecs/cmp/dock/Dock.hpp>
#include <pd/ecs/cmp/dock/DockWidgetComponent.hpp>

using namespace ::pd::ecs::sys;
using namespace ::pd::ecs::cmp::dock;
using namespace ::pd::ecs::cmp::root;

// ---------------------------------------------------------------------------------------------------------
void DockWidgetRemovalSystem::update(entt::registry& registry, entt::entity root) const
{
	auto view = registry.view<Component>(entt::exclude<Widget>);

	if (auto* widgetsOwner = registry.try_get<WidgetsOwner>(root))
	{
		for (auto entity : view)
		{
			delete widgetsOwner->docks.at(entity);
			widgetsOwner->docks.erase(entity);
			registry.destroy(entity);
		}
	}
}