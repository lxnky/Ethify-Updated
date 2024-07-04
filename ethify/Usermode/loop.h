#include <list>
#include <string>
#include "offsets.h"
#include <string.h>
#include "xorst.h"
#include "functions.h"
#include <iostream>
#include "aimbot.h"

using namespace uee;

#define debug_cache false

#define debug_weapons  false

__forceinline auto skeleton(uintptr_t mesh) -> void
{
	const int color = ImColor(255, 255, 255);
	fvector bonePositions[] = {
		ue5->get_bone_3d(mesh, 109),  // HeadBone
		ue5->get_bone_3d(mesh, 2),   // Hip
		ue5->get_bone_3d(mesh, 66),  // Neck
		ue5->get_bone_3d(mesh, 9),   // UpperArmLeft
		ue5->get_bone_3d(mesh, 38),  // UpperArmRight
		ue5->get_bone_3d(mesh, 10),  // LeftHand
		ue5->get_bone_3d(mesh, 39),  // RightHand
		ue5->get_bone_3d(mesh, 11),  // LeftHand1
		ue5->get_bone_3d(mesh, 40),  // RightHand1
		ue5->get_bone_3d(mesh, 78),  // RightThigh
		ue5->get_bone_3d(mesh, 71),  // LeftThigh
		ue5->get_bone_3d(mesh, 79),  // RightCalf
		ue5->get_bone_3d(mesh, 72),  // LeftCalf
		ue5->get_bone_3d(mesh, 75),  // LeftFoot 
		ue5->get_bone_3d(mesh, 82)   // RightFoot
	};

	fvector2d bonePositionsOut[16];
	for (int i = 0; i < 16; ++i) {
		bonePositionsOut[i] = ue5->w2s(bonePositions[i]);
	}

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[1].x, bonePositionsOut[1].y), ImVec2(bonePositionsOut[2].x, bonePositionsOut[2].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[3].x, bonePositionsOut[3].y), ImVec2(bonePositionsOut[2].x, bonePositionsOut[2].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[4].x, bonePositionsOut[4].y), ImVec2(bonePositionsOut[2].x, bonePositionsOut[2].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[5].x, bonePositionsOut[5].y), ImVec2(bonePositionsOut[3].x, bonePositionsOut[3].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[6].x, bonePositionsOut[6].y), ImVec2(bonePositionsOut[4].x, bonePositionsOut[4].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[5].x, bonePositionsOut[5].y), ImVec2(bonePositionsOut[7].x, bonePositionsOut[7].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[6].x, bonePositionsOut[6].y), ImVec2(bonePositionsOut[8].x, bonePositionsOut[8].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[10].x, bonePositionsOut[10].y), ImVec2(bonePositionsOut[1].x, bonePositionsOut[1].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[9].x, bonePositionsOut[9].y), ImVec2(bonePositionsOut[1].x, bonePositionsOut[1].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[12].x, bonePositionsOut[12].y), ImVec2(bonePositionsOut[10].x, bonePositionsOut[10].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[11].x, bonePositionsOut[11].y), ImVec2(bonePositionsOut[9].x, bonePositionsOut[9].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[13].x, bonePositionsOut[13].y), ImVec2(bonePositionsOut[12].x, bonePositionsOut[12].y), color, 1.7f);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(bonePositionsOut[14].x, bonePositionsOut[14].y), ImVec2(bonePositionsOut[11].x, bonePositionsOut[11].y), color, 1.7f);
}

namespace g_loop {
	class g_fn	 {
	public:

	

		fvector2d head;
		fvector2d root;
		fvector2d pelvis;
		fvector2d left_shoulder;
		fvector2d left_elbow;
		fvector2d left_hand;
		fvector2d right_shoulder;
		fvector2d neck;

		fvector2d right_elbow;
		fvector2d right_hand;
		fvector2d left_knee;
		fvector2d left_foot;
		fvector2d right_knee;
		fvector2d right_foot;

		
		auto cache_entities( ) -> void {

			temporary_entity_list.clear ( );

			g_ptr -> uworld = read <uintptr_t> ( virtualaddy + offset::uworld );
			g_ptr -> game_instance = read <uintptr_t> ( g_ptr -> uworld + offset::game_instance );
			g_ptr -> local_player = read <uintptr_t> (read <uintptr_t>( g_ptr -> game_instance + offset::local_player ) );
			g_ptr -> player_controller = read <uintptr_t> ( g_ptr -> local_player + offset::player_controller );
			g_ptr -> acknowledged_pawn = read <uintptr_t> ( g_ptr -> player_controller + offset::acknowledged_pawn );
			g_ptr -> skeletal_mesh = read <uintptr_t> ( g_ptr -> acknowledged_pawn + offset::skeletal_mesh );
			g_ptr -> player_state = read <uintptr_t> ( g_ptr -> acknowledged_pawn + offset::player_state );
			g_ptr -> root_component = read <uintptr_t> ( g_ptr -> acknowledged_pawn + offset::root_component );
			g_ptr -> relative_location = read <fvector> ( g_ptr -> root_component + offset::relative_location );
			g_ptr -> team_index = read <int> ( g_ptr -> player_state + offset::team_index );

			if ( debug_cache )
			{
				std::cout << E ( " uworld -> " ) << g_ptr -> uworld << std::endl;
				std::cout << E ( " game_instance -> " ) << g_ptr -> game_instance << std::endl;
				std::cout << E ( " local_player -> " ) << g_ptr -> local_player << std::endl;
				std::cout << E ( " player_controller -> " ) << g_ptr -> player_controller << std::endl;
				std::cout << E ( " acknowledged_pawn -> " ) << g_ptr -> acknowledged_pawn << std::endl;
				std::cout << E ( " skeletal_mesh -> " ) << g_ptr -> skeletal_mesh << std::endl;
				std::cout << E ( " player_state -> " ) << g_ptr -> player_state << std::endl;
				std::cout << E ( " root_component -> " ) << g_ptr -> root_component << std::endl;
				std::cout << E ( " relative_location.X -> " ) << g_ptr -> relative_location.x << std::endl;
				std::cout << E ( " relative_location.Y -> " ) << g_ptr -> relative_location.y << std::endl;
				std::cout << E ( " relative_location.Z -> " ) << g_ptr -> relative_location.z << std::endl;
				std::cout << E ( " team_index -> " ) << g_ptr -> team_index << std::endl;
			}

			bool inlobby;

			if (g_ptr->acknowledged_pawn == NULL)
			{
				inlobby = true;
			}
			else
			{
				inlobby = false;
			}


			if ( !g_ptr->acknowledged_pawn )
			{
				globals::in_lobby = true;
			}
			else
			{
				globals::in_lobby = false;
			}
	
			if (g_ptr->acknowledged_pawn) {

				if (globals::g_weapon_cfg)
				{
					uint64_t player_weapon = read <uint64_t>(g_ptr->acknowledged_pawn + 0xA20); // 	struct AFortWeapon* CurrentWeapon;

					if (is_valid(player_weapon)) {

						uint64_t weapon_data =  read <uint64_t>(player_weapon + 0x4a8);	//struct UFortWeaponItemDefinition* WeaponData;

						if (is_valid(weapon_data)) {

							uint64_t ftext_ptr = read <uint64_t>(weapon_data + 0x90);

							if (is_valid(ftext_ptr)) {
								uint64_t ftext_data = read <uint64_t>(ftext_ptr + 0x28);
								int ftext_length = read <int>(ftext_ptr + 0x30);
								if (ftext_length > 0 && ftext_length < 50) {
									wchar_t* ftext_buf = new wchar_t[ftext_length];
									mem::read1 (ftext_data, ftext_buf, ftext_length * sizeof(wchar_t));

									wchar_t* WeaponName = ftext_buf;

									delete[] ftext_buf;

									if (wcsstr(WeaponName, E(L"Assault Rifle")) || wcsstr(WeaponName, E(L"Havoc Suppressed Assault Rifle")) || wcsstr(WeaponName, E(L"Red-Eye Assault Rifle"))
										|| wcsstr(WeaponName, E(L"Suppressed Assault Rifle")) || wcsstr(WeaponName, E(L"Striker Burst Rifle")) || wcsstr(WeaponName, E(L"Burst Assault Rifle"))
										|| wcsstr(WeaponName, E(L"Ranger Assault Rifle")) || wcsstr(WeaponName, E(L"Flapjack Rifle")) || wcsstr(WeaponName, E(L"Heavy Assault Rifle"))
										|| wcsstr(WeaponName, E(L"MK-Seven Assault Rifle")) || wcsstr(WeaponName, E(L"MK-Alpha Assault Rifle")) || wcsstr(WeaponName, E(L"Combat Assault Rifle"))
										|| wcsstr(WeaponName, E(L"Nemesis AR")) || wcsstr(WeaponName, E(L"Ambush Striker AR")) || wcsstr(WeaponName, E(L"Striker AR"))
										|| wcsstr(WeaponName, E(L"Tactical Assault Rifle")) || wcsstr(WeaponName, E(L"Hammer Assault Rifle")) || wcsstr(WeaponName, E(L"Sideways Rifle")) || wcsstr(WeaponName, E(L"Makeshift Rifle")) || wcsstr(WeaponName, E(L"Drum Gun"))) {
										HeldWeaponType = EFortWeaponType::Rifle;
										globals::g_aimbot = rifle::aimbot;
										globals::g_visible_check = rifle::visible_check;
										globals::g_target_line = rifle::target_line;
										globals::g_isdead = rifle::ignore_downed;
										globals::g_aimfov = rifle::aim_fov;
										globals::g_smooth = rifle::smooth;
										globals::g_hitbox = rifle::hitbox;
										aimkey = rifle::aimkey;
										if (debug_weapons)
										{
											std::cout << E("rifle") << std::endl;
										}
									}
									if (wcsstr(WeaponName, E(L"Shotgun")) || wcsstr(WeaponName, E(L"Frenzy Auto Shotgun")) || wcsstr(WeaponName, E(L"Iron Warrior Hammer Pump Shogtun")) || wcsstr(WeaponName, E(L"Peter Griffin's Pump Shotgun")) || wcsstr(WeaponName, E(L"PETER GRIFFIN'S PUMP SHOTGUN"))) {
										HeldWeaponType = EFortWeaponType::Shotgun;
										globals::g_aimbot = shotgun::aimbot;
										globals::g_visible_check = shotgun::visible_check;
										globals::g_target_line = shotgun::target_line;
										globals::g_isdead = rifle::ignore_downed;
										globals::g_aimfov = shotgun::aim_fov;
										globals::g_smooth = shotgun::smooth;
										globals::g_hitbox = shotgun::hitbox;
										aimkey = shotgun::aimkey;
										if (debug_weapons)
										{
											std::cout << E("shogtun") << std::endl;
										}
									}
									if (wcsstr(WeaponName, E(L"Smg")) || wcsstr(WeaponName, E(L"Ambush Hyper SMG")) || wcsstr(WeaponName, E(L"Submachine Gun")) || wcsstr(WeaponName, E(L"Combat Smg")) || wcsstr(WeaponName, E(L"Pistol")) || wcsstr(WeaponName, E(L"Machine Smg"))
										|| wcsstr(WeaponName, E(L"Scoped Burst SMG")) || wcsstr(WeaponName, E(L"Hyper SMG")) || wcsstr(WeaponName, E(L"Thunger Burst SMG"))) {
										HeldWeaponType = EFortWeaponType::Smg;
										globals::g_aimbot = smg::aimbot;
										globals::g_visible_check = smg::visible_check;
										globals::g_target_line = smg::target_line;
										globals::g_isdead = rifle::ignore_downed;
										globals::g_aimfov = smg::aim_fov;
										globals::g_smooth = smg::smooth;
										globals::g_hitbox = smg::hitbox;
										aimkey = smg::aimkey;
										if (debug_weapons)
										{
											std::cout << E("smg") << std::endl;
										}
									}
									if (wcsstr(WeaponName, E(L"Hunting Rifle")) || wcsstr(WeaponName, E(L"Heavy Sniper Rifle")) || wcsstr(WeaponName, E(L"Suppressed Sniper Rifle"))
										|| wcsstr(WeaponName, E(L"Storm Scout")) || wcsstr(WeaponName, E(L"Bolt-Action Sniper Rifle")) || wcsstr(WeaponName, E(L"Automatic Sniper Rifle"))
										|| wcsstr(WeaponName, E(L"DMR")) || wcsstr(WeaponName, E(L"Thermal DMR")) || wcsstr(WeaponName, E(L"Hunter Bolt-Action Sniper"))
										|| wcsstr(WeaponName, E(L"Reaper Sniper Rifle")) || wcsstr(WeaponName, E(L"Semi-Auto Sniper Rifle"))
										|| wcsstr(WeaponName, E(L"Crossbow")) || wcsstr(WeaponName, E(L"Mechanical Bow")) || wcsstr(WeaponName, E(L"Hand Cannon"))) {
										HeldWeaponType = EFortWeaponType::Sniper;
										globals::g_aimbot = sniper::aimbot;
										globals::g_visible_check = sniper::visible_check;
										globals::g_target_line = sniper::target_line;
										globals::g_isdead = rifle::ignore_downed;

										globals::g_aimfov = sniper::aim_fov;
										globals::g_smooth = sniper::smooth;
										globals::g_hitbox = sniper::hitbox;
										aimkey = sniper::aimkey;
										if (debug_weapons)
										{
											std::cout << ("sniper") << std::endl;
										}
									}
								}
							}
						}
					}
				}
			}

			g_ptr -> game_state = read <uintptr_t> ( g_ptr -> uworld + offset::game_state );
			g_ptr -> player_array = read <uintptr_t> ( g_ptr -> game_state + offset::player_array );
			g_ptr -> player_array_size = read <int> ( g_ptr -> game_state + ( offset::player_array + sizeof ( uintptr_t ) ) );

			for ( int i = 0; i < g_ptr -> player_array_size; ++i ) {
				auto player_state = read <uintptr_t> ( g_ptr -> player_array + (i * sizeof ( uintptr_t ) ) );
				auto current_actor = read <uintptr_t> ( player_state + offset::pawn_private );

				auto root_component = read <uintptr_t> ( current_actor + offset::root_component );

				auto relative_location = read <fvector> ( root_component + offset::relative_location) ;

				auto pawn_private = read <uintptr_t>(player_state + 0x308);

				fvector2d screen_location;
				screen_location = ue5->w2s ( relative_location );
				if ( !ue5->in_screen ( screen_location ) ) continue;

				auto skeletalmesh = read <uintptr_t> ( current_actor + offset::skeletal_mesh );

				auto is_despawning = ( read <char> ( current_actor + 0x93a) >> 3 );

				auto team_index = read <int> ( player_state + offset::team_index );
				if ( g_ptr -> team_index == team_index && g_ptr -> acknowledged_pawn ) continue;

				entity cached_actors{ };
				cached_actors.entity = current_actor;
				cached_actors.skeletal_mesh = skeletalmesh;
				cached_actors.root_component = root_component;
				cached_actors.relative_location = relative_location;
				cached_actors.player_state = player_state;
				cached_actors.team_index = team_index;

				temporary_entity_list.push_back( cached_actors );
			}

			entity_list.clear( );
			entity_list = temporary_entity_list;
			std::this_thread::sleep_for ( std::chrono::milliseconds (150) );

		}

		fvector2d head_box;
		fvector2d root_box;
		fvector2d root_box1;

		auto actor_loop( ) -> void {
			ImGui::PushFont( GameFont );

			ImDrawList* draw_list = ImGui::GetBackgroundDrawList( );
			float target_dist = FLT_MAX;
			uintptr_t target_entity = 0;


			if (globals::g_fps) {
				char fps[256]; // 64
				sprintf_s(fps, skCrypt("fps: %.3f"), ImGui::GetIO().Framerate);
				DrawString(15, 50, 50, ImColor(255, 255, 255, 255), false, true, fps);
			}


			const float centerWidth = screen_width / 2;
			const float centerHeight = screen_height / 2;

			for ( auto& cached : entity_list ) {
				auto root_bone = ue5->get_bone_3d ( cached.skeletal_mesh, bone::Root );
				root = ue5->w2s ( root_bone );

				root_box = ue5->w2s ( fvector ( root_bone.x, root_bone.y, root_bone.z + 30 ) );

				root_box1 = ue5->w2s ( fvector( root_bone.x, root_bone.y, root_bone.z - 15 ) );

				auto head_bone = ue5->get_bone_3d ( cached.skeletal_mesh, bone::Head );
				head = ue5->w2s ( head_bone );
				head_box = ue5->w2s ( fvector ( head_bone.x, head_bone.y, head_bone.z + 15 ) );

				float box_height = abs ( head.y - root_box1.y );
				float box_width = box_height * 0.41f;
				float distance = g_ptr->relative_location.distance ( root_bone ) / 100;

				auto pawn_private1 = read <uintptr_t>(player_state + 0x308);

				if (globals::g_isdead) {
					bool bIsDyingasd = (read <BYTE>(pawn_private1 + 0x758) & 0x10);
					bool isDBNO = (read <BYTE>(pawn_private1 + 0x93a) >> 4) & 1; // 
					if (isDBNO || bIsDyingasd)
						continue;
				}
	
				if ( distance > globals::g_render_distance && g_ptr->acknowledged_pawn ) continue;
				
				if ( globals::g_aimbot ) {

					auto dx = head.x - ( screen_width / 2 );
					auto dy = head.y - ( screen_height / 2 );
					auto dist = sqrtf ( dx * dx + dy * dy );

					if ( globals::g_visible_check ) {
						if ( ue5->is_visible ( cached.skeletal_mesh ) ) {
							if ( dist < globals::g_aimfov && dist < target_dist ) {
							
								target_dist = dist;
								target_entity = cached.entity;
							}
						}
					}
					else {
						if ( dist < globals::g_aimfov  && dist < target_dist ) {
				

							target_dist = dist;
							target_entity = cached.entity;
						}
					}
				}

				bool inlobby;

				if (g_ptr->acknowledged_pawn == NULL)
				{
					inlobby = true;
				}
				else
				{
					inlobby = false;
				}

				if (globals::g_render_fov) {

					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(screen_width / 2, screen_height / 2), globals::g_aimfov, ImColor(0, 0, 0), 64, 3);
					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(screen_width / 2, screen_height / 2), globals::g_aimfov, ImColor(255, 255, 255), 64, 1);
				}
				
				ImColor vis;
				ImColor invis;
				ImColor normal;

				vis = ImVec4 ( globals::g_color_Visible[0], globals::g_color_Visible[1], globals::g_color_Visible[2], 1.0f );
				invis = ImVec4 ( globals::g_color_invisible[0], globals::g_color_invisible[1], globals::g_color_invisible[2], 1.0f );
				normal = ImVec4 ( globals::g_color[0], globals::g_color[1], globals::g_color[2], 1.0f );

				ImColor visibleColor;
				if ( globals::g_visible_check )
				{
					 visibleColor = ue5->is_visible ( cached.skeletal_mesh ) ? ImColor( vis ) : ImColor( invis );
				}
				else
				{
					visibleColor =  ImColor ( normal );
				}

				if ( globals::g_line )
				{
					if ( globals::g_line_type == 0 ) {
						draw_list -> AddLine ( ImVec2 ( screen_width / 2, 0 ), ImVec2( head_box.x, head_box.y ), visibleColor, globals::g_line_thick );
					}

					if ( globals::g_line_type == 1 ) {
						draw_list -> AddLine ( ImVec2 ( screen_width /2 , screen_height / 2 ), ImVec2 ( head_box.x, head_box.y ), visibleColor, globals::g_line_thick );
					}

					if ( globals::g_line_type == 2 ) {
						draw_list -> AddLine ( ImVec2 ( screen_width / 2, screen_height - 5 ), ImVec2 ( head_box.x, head_box.y ), visibleColor, globals::g_line_thick );
					}
				}
			
				if ( globals::g_box_esp && globals::g_enable_esp ) {

					if ( globals::g_box_type == 0 )
					{					
						if ( globals::g_outline )
						{
							draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), head_box.y ), ImVec2 ( root.x + ( box_width / 2 ), head_box.y ), ImColor ( 0, 0, 0 ), globals::g_box_thick + 2 ); 
							draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), head_box.y ), ImVec2 ( head_box.x - ( box_width / 2 ), root.y ), ImColor ( 0,0,0 ), globals::g_box_thick + 2 );
							draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), root.y ), ImVec2 ( root.x + ( box_width / 2 ), root.y ), ImColor ( 0, 0, 0 ), globals::g_box_thick + 2 ); 
							draw_list -> AddLine ( ImVec2 ( root.x + ( box_width / 2 ), head_box.y ), ImVec2 ( root.x + ( box_width / 2 ), root.y ), ImColor ( 0, 0, 0 ), globals::g_box_thick + 2 );
						}

						draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), head_box.y ), ImVec2 ( root.x + ( box_width / 2), head_box.y ), visibleColor, globals::g_box_thick ); 
						draw_list -> AddLine ( ImVec2 ( head_box.x - ( box_width / 2 ), head_box.y ), ImVec2 ( head_box.x - ( box_width / 2), root.y ), visibleColor, globals::g_box_thick ); 
						draw_list -> AddLine ( ImVec2 ( head_box.x -  ( box_width / 2 ), root.y ), ImVec2 ( root.x + ( box_width / 2), root.y ), visibleColor, globals::g_box_thick ); 
						draw_list -> AddLine ( ImVec2 ( root.x +  ( box_width / 2 ), head_box.y ), ImVec2 ( root.x + ( box_width / 2), root.y ), visibleColor, globals::g_box_thick ); 
					}
					else if ( globals::g_box_type == 1 ) {
						if  ( globals::g_outline )
						{
							draw_list -> AddRect ( ImVec2 ( head_box.x - box_width / 2, head_box.y ), ImVec2 ( ( head_box.x - box_width / 2 ) + box_width, head_box.y + box_height ), ImColor ( 0, 0, 0 ) , 10, ImDrawCornerFlags_All, globals::g_box_thick + 2.0 );
						}

						draw_list -> AddRect ( ImVec2 ( head_box.x - box_width / 2, head_box.y ), ImVec2 ( ( head_box.x - box_width / 2 ) + box_width, head_box.y + box_height ), visibleColor, 10, ImDrawCornerFlags_All, globals::g_box_thick );				
					}
					else if ( globals::g_box_type == 2 )
					{
						if ( globals::g_outline )
						{
							DrawCorneredBox ( root.x - ( box_width / 2 ), head_box.y, box_width, box_height, ImColor ( 0, 0, 0 ), globals::g_box_thick + 2.0, 0, 0 );
						}

						DrawCorneredBox ( root.x - ( box_width / 2 ), head_box.y, box_width, box_height, visibleColor,globals::g_box_thick, 0, 0 );
					}
				}
					if ( globals::g_weapon_esp && globals::g_enable_esp )
					{
						if ( g_ptr->acknowledged_pawn )
						{

						WeaponInformation held_weapon{ };

						uint64_t player_weapon = read<uint64_t>( cached.entity + 0xa20);

						if ( is_valid ( player_weapon ) ) {
							held_weapon.ammo_count = read <int32_t> ( player_weapon + 0xdcc);

							uint64_t weapon_data = read <uint64_t> ( player_weapon + 0x4a8);

							if ( is_valid ( weapon_data ) ) {
								held_weapon.tier = read <BYTE> ( weapon_data + 0x73 );

								uint64_t ftext_ptr = read <uint64_t> ( weapon_data + 0x90 );

								if ( is_valid ( ftext_ptr ) ) {
									uint64_t ftext_data = read <uint64_t> ( ftext_ptr + 0x28 );
									int ftext_length = read <int> ( ftext_ptr + 0x30 );
									if ( ftext_length > 0 && ftext_length < 50  ) {
										wchar_t* ftext_buf = new wchar_t[ ftext_length ];

										mem::read1 ( ftext_data, ftext_buf, ftext_length * sizeof ( wchar_t ) );
										std::wstring wstr_buf ( ftext_buf );
										held_weapon.weapon_name = std::string( wstr_buf.begin( ), wstr_buf.end( ) );
										delete[] ftext_buf;
									}
								}

							}

							WeaponInfo = held_weapon;

							std::string final = ( "") + WeaponInfo.weapon_name + ("" );

							ImVec2 TextSize = ImGui::CalcTextSize ( final.c_str ( ) );

							ImVec2 text_size = ImGui::CalcTextSize ( final.c_str ( ) );
							int add;
							if ( globals::g_distance )
							{
								add = 25;
							}
							else
							{
								add = 5;
							}

							if ( globals::g_weapon_rarity )
							{
								if ( WeaponInfo.tier == 0 )
								{
									if ( strstr( WeaponInfo.weapon_name.c_str ( ), E ( "Pickaxe" ) ) != nullptr )
									{
										DrawString (15, ( root.x ) - (TextSize.x / 2), ( root.y + add ), ImColor ( 255, 255, 255 ), false, true, final.c_str ( ) );
									}
									else
									{
										std::string fina1l = ( "Building Plan" );
										ImVec2 TextSiz1e = ImGui::CalcTextSize ( fina1l.c_str ( ) );
										DrawString (15, ( root.x) - (TextSiz1e.x / 2 ), ( root.y + add ), ImColor ( 255, 255, 255 ), false, true, fina1l.c_str ( ) );
									}

								}
								if (WeaponInfo.tier == 1)
								{
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(170, 165, 169), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 2)
								{
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(30, 255, 0), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 3)
								{
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(0, 112, 221), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 4)
								{
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(163, 53, 238), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 5)
								{
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(255, 128, 0), false, true, final.c_str());

								}
								if (WeaponInfo.tier == 6)
								{
									DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), ImColor(255, 255, 0), false, true, final.c_str());

								}
							}
							else
							{
								if (WeaponInfo.tier == 0)
								{
									if (strstr(WeaponInfo.weapon_name.c_str(), E("Pickaxe")) != nullptr)
									{
										DrawString(15, (root.x) - (TextSize.x / 2), (root.y + add), visibleColor, false, true, final.c_str());
									}
									else
									{
										std::string fina1l = ("Building Plan");
										ImVec2 TextSiz1e = ImGui::CalcTextSize(fina1l.c_str());
										DrawString(15, (root.x) - (TextSiz1e.x / 2), (root.y + add), visibleColor, false, true, fina1l.c_str());
									}
								}
								else
								{
									DrawString(14, root.x - (text_size.x / 2), root.y + 20, visibleColor, false, true, final.c_str());
								}
							}
						}

						}
					}

					if (globals::g_username && globals::g_enable_esp) {

							std::string username_str = ue5->get_player_name(cached.player_state, inlobby);
							ImVec2 text_size = ImGui::CalcTextSize(username_str.c_str());
							DrawString(14, head_box.x - (text_size.x / 2), head_box.y - 20, ImColor(255, 255, 255), false, true, username_str.c_str());
						
					}
				
					if (globals::g_distance && globals::g_enable_esp) {
						std::string distance_str = (std::string)("") + std::to_string((int)distance) + (std::string)("m");
						ImVec2 text_size = ImGui::CalcTextSize(distance_str.c_str());

						DrawString(14, root.x - (text_size.x / 2), root.y + 5, ImColor(255, 255, 255), false, true, distance_str.c_str());
					}

					if (globals::g_skeleton && globals::g_enable_esp) {

						skeleton(cached.skeletal_mesh);

					}

					//if (ud::u_triggerbot) {
					//	if (distance < ud::u_maximum_distance) {

					//		auto targeted_fort_pawn = read<std::uintptr_t>(ud_cache->player_controller + 0x1870); // AFortPlayerController	TargetedFortPawn	AFortPawn*
					//		auto target_state = read<std::uintptr_t>(targeted_fort_pawn + offset::player_state);
					//		/*std::cout << ("TargetedPawn -> ") << targeted_fort_pawn << std::endl;*/
					//		auto target_team = read<int>(target_state + offset::team_index);
					//		if ((ud_cache->acknowledged_pawn) and (targeted_fort_pawn != 0) and (target_team != ud_cache->team_index)) {
					//			if (u_has_clicked) {
					//				u_tb_begin = std::chrono::steady_clock::now();
					//				u_has_clicked = 0;
					//			}
					//			u_tb_end = std::chrono::steady_clock::now();
					//			u_tb_time_since = std::chrono::duration_cast<std::chrono::milliseconds>(u_tb_end - u_tb_begin).count();
					//			if (u_tb_time_since >= ud::u_custom_delay) {
					//				move_mouse;
					//				u_has_clicked = 1;
					//			}
					//		}
					//	}
					//}

					if (globals::g_triggerbot && distance <= globals::g_maximum_distance && globals::g_triggerbot)
					{
						auto closest_mesh = read<std::uint64_t>(target_entity + offset::skeletal_mesh);
						fvector hitbox;
						switch (globals::g_hitbox) {
						case(0):
							hitbox = ue5->get_bone_3d(closest_mesh, bone::Head);
							break;
						case(1):
							hitbox = ue5->get_bone_3d(closest_mesh, bone::Neck);
							break;
						case(2):
							hitbox = ue5->get_bone_3d(closest_mesh, bone::Chest);
							break;
						case(3):
							hitbox = ue5->get_bone_3d(closest_mesh, bone::Pelvis);
							break;
						}
						if (globals::g_ignore_keybind) {
							if (ue5->is_shootable(read<fvector>(g_ptr->player_controller + offset::location_under_reticle), hitbox)) {
								if (globals::g_shotguns_only) {
									if (HeldWeaponType == EFortWeaponType::Shotgun) {
										if (globals::g_has_clicked) {
											globals::g_tb_begin = std::chrono::steady_clock::now();
											globals::g_has_clicked = 0;
										}
										globals::g_tb_end = std::chrono::steady_clock::now();
										globals::g_tb_time_since = std::chrono::duration_cast<std::chrono::milliseconds>(globals::g_tb_end - globals::g_tb_begin).count();
										if (globals::g_tb_time_since >= globals::g_custom_delay) {
											mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, 0, 0);
											mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, 0, 0);
											globals::g_has_clicked = 1;
										}
									}
								}
								else {
									if (globals::g_has_clicked) {
										globals::g_tb_begin = std::chrono::steady_clock::now();
										globals::g_has_clicked = 0;
									}
									globals::g_tb_end = std::chrono::steady_clock::now();
									globals::g_tb_time_since = std::chrono::duration_cast<std::chrono::milliseconds>(globals::g_tb_end - globals::g_tb_begin).count();
									if (globals::g_tb_time_since >= globals::g_custom_delay) {
										mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, 0, 0);
										mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, 0, 0);
										globals::g_has_clicked = 1;
									}
								}

							}
						}
						else {
							if (GetAsyncKeyState(VK_RBUTTON)) {
								if (ue5->is_shootable(read<fvector>(g_ptr->player_controller + offset::location_under_reticle), hitbox)) {
									if (globals::g_shotguns_only) {
										if (HeldWeaponType == EFortWeaponType::Shotgun) {
											if (globals::g_has_clicked) {
												globals::g_tb_begin = std::chrono::steady_clock::now();
												globals::g_has_clicked = 0;
											}
											globals::g_tb_end = std::chrono::steady_clock::now();
											globals::g_tb_time_since = std::chrono::duration_cast<std::chrono::milliseconds>(globals::g_tb_end - globals::g_tb_begin).count();
											if (globals::g_tb_time_since >= globals::g_custom_delay) {
												mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, 0, 0);
												mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, 0, 0);
												globals::g_has_clicked = 1;
											}
										}
									}
									else {
										if (globals::g_has_clicked) {
											globals::g_tb_begin = std::chrono::steady_clock::now();
											globals::g_has_clicked = 0;
										}
										globals::g_tb_end = std::chrono::steady_clock::now();
										globals::g_tb_time_since = std::chrono::duration_cast<std::chrono::milliseconds>(globals::g_tb_end - globals::g_tb_begin).count();
										if (globals::g_tb_time_since >= globals::g_custom_delay) {
											mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, 0, 0);
											mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, 0, 0);
											globals::g_has_clicked = 1;
										}
									}

								}
							}
						}
					}
			}
			

			

			if (target_entity && globals::g_aimbot) {

				auto closest_mesh = read<std::uint64_t>(target_entity + offset::skeletal_mesh);

				fvector hitbox;
				fvector2d hitbox_screen;

				switch (globals::g_hitbox) {
				case 0:
					hitbox_screen = ue5->w2s(ue5->get_bone_3d(closest_mesh, bone::Head));
					hitbox = ue5->get_bone_3d(closest_mesh, bone::Head);;
					break;
				case 1:
					hitbox_screen = ue5->w2s(ue5->get_bone_3d(closest_mesh, bone::Neck));
					hitbox = ue5->get_bone_3d(closest_mesh, bone::Neck);;
					break;
				case 2:
					hitbox_screen = ue5->w2s(ue5->get_bone_3d(closest_mesh, bone::Chest));
					hitbox = ue5->get_bone_3d(closest_mesh, bone::Chest);;
					break;
				case 3:
					hitbox_screen = ue5->w2s(ue5->get_bone_3d(closest_mesh, bone::Pelvis));
					hitbox = ue5->get_bone_3d(closest_mesh, bone::Pelvis);;
					break;
				}

				if (hitbox.x != 0 || hitbox.y != 0 && (get_cross_distance(hitbox.x, hitbox.y, screen_width / 2, screen_height / 2) <= globals::g_aimfov))
				{
					if (globals::g_target_line)
						draw_list->AddLine(ImVec2(centerWidth, centerHeight), ImVec2(hitbox_screen.x, hitbox_screen.y), ImColor(255, 0, 0), 2);

					if (GetAsyncKeyState_Spoofed(aimkey))
						input->move(hitbox_screen);
				}

			}
			else {
				target_dist = FLT_MAX;
				target_entity = NULL;
			}

			
			ImGui::PopFont();
		}

	};
} static g_loop::g_fn* g_main = new g_loop::g_fn();