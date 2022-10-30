#include "load.hpp"

namespace lerppana::flappykarp::scenes
{


    void load::on_gui()
    {
        if (resource_loader->idle())
        {
            scene_orchestrator_state->request_scene_transition("fs1://scenes/game.scene");
        }

        auto* font = font_manager->get_font("honeyblot");

        ImGui::FontScope font_scope{font};
        ImGui::SetWindowFontScale(1.0f);

        static auto width = 100.0f;
        static auto padding = 70.f;
        const auto font_height = ImGui::GetFontSize();
        ImGui::SetCursorPos(ImVec2(
                ImGui::GetWindowWidth() / 2 - width / 2,
                ImGui::GetWindowHeight()/ 2 - font_height / 2 - padding));

        ImGui::GroupScope text_group;
        ImGui::StyleVar style(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.75f));

        ImGui::Text("loading...", ImVec2(250.f, 100.f));

        width = ImGui::GetItemRectSize().x;
    }

    void load::start()
    {
        resource_loader->request_load<resource::audio_resource>("fs1://audio/Minimalist2.wav");
        resource_loader->request_load<resource::audio_resource>("fs1://audio/Minimalist7.wav");

        resource_loader->request_load<resource::vk_mesh_resource>("fs1://models/ground.model.mesh");
        resource_loader->request_load<resource::texture_resource>("fs1://textures/ground.png");

        resource_loader->request_load<resource::vk_mesh_resource>("fs1://models/magikarp.model.mesh");
        resource_loader->request_load<resource::vertex_bone_data_resource>("fs1://models/magikarp.skin.mesh");
        resource_loader->request_load<resource::animation_resource>("fs1://models/magikarp.splash.anim");
        resource_loader->request_load<resource::texture_resource>("fs1://textures/magikarp.png");

        resource_loader->request_load<resource::vk_mesh_resource>("fs1://models/pipe.model.mesh");
        resource_loader->request_load<resource::texture_resource>("fs1://textures/pipe.png");

    }
}