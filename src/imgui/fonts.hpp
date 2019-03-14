#pragma once
#include "../Common.hpp"
#include "font_awesome.hpp"
#include "font_material_design.hpp"
#include "font_kenney.hpp"

namespace Fonts
{
<<<<<<< HEAD
	void init()
	{
		ImGuiIO& io = ImGui::GetIO();
=======
	inline void init()
	{
		auto& io = ImGui::GetIO();
>>>>>>> a4a49d8... fafa
		io.Fonts->AddFontDefault();

		// merge in icons from Font Awesome
		static ImWchar icons_ranges_fa[] = {ICON_MIN_FA, ICON_MAX_FA, 0};
		ImFontConfig icons_config_fa; icons_config_fa.MergeMode = true; icons_config_fa.PixelSnapH = true;
		io.Fonts->AddFontFromFileTTF("res/fonts/Font Awesome.ttf", 16.0f, &icons_config_fa, icons_ranges_fa);

		// merge in icons from Material Design
		static ImWchar icons_ranges_md[] = {ICON_MIN_MD, ICON_MAX_MD, 0};
		ImFontConfig icons_config_md; icons_config_md.MergeMode = true; icons_config_md.PixelSnapH = true;
		io.Fonts->AddFontFromFileTTF("res/fonts/Material Design.ttf", 16.0f, &icons_config_md, icons_ranges_md);

		// BUG: Kenney font doesn't work
		//// merge in icons from Kenney
		//static ImWchar icons_ranges[] = { ICON_MIN_KI, ICON_MAX_KI, 0 };
		//ImFontConfig icons_config_ki; icons_config_ki.MergeMode = true; icons_config_ki.PixelSnapH = true;
		//io.Fonts->AddFontFromFileTTF ("res/fonts/Kenney.ttf", 16.0f, &icons_config_ki, icons_ranges);
	}
}
