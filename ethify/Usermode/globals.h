#include <mutex>
#include <memory>
namespace globals
{
	inline bool g_aimbot = 1;

	inline bool g_visible_check = 1;

	inline bool g_line = 0;

	inline bool g_isdead = 0;

	inline bool g_fps = 1;

	inline int g_line_type = 0;

	inline inline bool g_textoutline = 0;

	inline float g_aimfov = 100;

	inline int g_hitbox = 0;

	inline inline bool g_target_line;

	inline inline bool g_skeleton = 0;

	inline bool g_box_esp = 1;

	inline bool g_enable_esp = 1;

	inline bool g_distance = 1;

	inline bool g_username = 0;

	inline bool g_head = 0;

	inline bool g_snapline = 0;

	inline bool g_weapon_cfg = 1;

	static float g_color_Visible[3] = { 87 / 255.0f, 173 / 255.0f, 17 / 255.0f };
	static float g_color_invisible[3] = { 173 / 255.0f, 17 / 255.0f, 17 / 255.0f };
	static float g_color[3] = { 1.00f, 1.00f, 1.00f };

	static int g_color_fov[3] = { 1.00f, 1.00f, 1.00f };

	float g_render_distance = 300;

	inline bool g_weapon_esp = 0;

	inline bool g_platform = 0;

	inline int g_box_type = 0;

	inline bool g_outline = 1;

	inline int g_box_thick = 2;

	inline int g_line_thick = 2;

	inline int g_skeleton_thick = 1;

	inline float g_aim_max_dist = 275;

	inline float g_smooth = 6;

	inline bool g_render_fov = 1;

	inline bool g_weapon_rarity = 1;

	inline bool g_render_crosshair = 0;

	inline bool g_render_menu = 0;

	inline bool g_shotguns_only = 1;

	inline bool g_ignore_keybind = 0;

	inline bool in_lobby;

	bool g_triggerbot = 0;
	float g_maximum_distance = 10;
	float g_custom_delay = 20;
	bool g_has_clicked;
	std::chrono::steady_clock::time_point g_tb_begin;
	std::chrono::steady_clock::time_point g_tb_end;
	int g_tb_time_since;
}

namespace rifle
{

	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool visible_check = 1;
	inline bool target_line = 0;
	inline float aim_fov = 15;
	inline float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;
}

namespace shotgun
{

	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool visible_check = 1;
	inline bool target_line = 0;
	inline float aim_fov = 15;
	inline float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;

}

namespace smg
{
	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool visible_check = 1;
	inline bool target_line = 0;
	inline 	float aim_fov = 15;
	inline 	float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;

}

namespace sniper
{
	inline bool aimbot = 1;
	inline bool ignore_downed = 1;
	inline bool ignore_bots = 0;
	inline bool visible_check = 1;
	inline bool target_line = 0;
	inline	float aim_fov = 15;
	inline float smooth = 3;
	inline int hitbox = 0;
	inline int aimkey;
}