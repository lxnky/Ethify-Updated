#include "spoofer.h"
#include "SkCrypt.h"
#include "sdk.h"
#include "ImGui/imgui.h"
#include <d3d9.h>
#include "ImGui/imgui_impl_win32.h"
#include "driver.hpp"
#include "globals.h"
#include "imports.h"
ImFont* MenuFont;
ImFont* GameFont;
ImFont* IconsFont;

inline int center_x;
inline int center_y;

class entity {
public:
	uintptr_t
		entity,
		skeletal_mesh,
		root_component,
		player_state;
	int
		team_index;
	fvector
		relative_location;
	float
		lastrendertime;
	bool
		is_visible;
};

std::vector<entity> entity_list;
std::vector<entity> temporary_entity_list;
namespace o {
class p
{
	public:

		uintptr_t
			uworld,
			game_instance,
			game_state,
			local_player,
			player_controller,
			acknowledged_pawn,
			skeletal_mesh,
			player_state,
			root_component,
			player_array;
		int
			team_index,
			player_array_size;
		fvector
			relative_location,
			velocity;
	};
} static o::p* g_ptr = new o::p();




