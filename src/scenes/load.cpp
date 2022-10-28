#include "load.hpp"

namespace lerppana::flappykarp::scenes
{
    void load::draw_exit_button()
    {
        auto loading = !resource_loader->idle();

        auto font_size = loading ? 0.5f : 1.0f;

        auto* font = font_manager->get_font("honeyblot");

        ImGui::FontScope font_scope{font};
        ImGui::SetWindowFontScale(font_size);

        static auto width = 100.0f;
        static auto padding = 70.f;
        const auto font_height = ImGui::GetFontSize();
        ImGui::SetCursorPos(ImVec2(
                ImGui::GetWindowWidth() / 2 - width / 2,
                ImGui::GetWindowHeight()/ 2 - font_height / 2 - padding));

        ImGui::GroupScope text_group;
        ImGui::StyleVar style(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.75f));

        auto text = loading ? "Loading" : "Start";

        if (loading)
        {
            ImGui::BeginDisabled();
        }

        if (ImGui::Button(text, ImVec2(250.f, 100.f)))
        {
            scene_orchestrator_state->request_scene_transition("fs1://scenes/game.scene");
            audio_manager->play_clip("fs1://audio/Minimalist2.wav");
        }

        if (loading)
        {
            ImGui::EndDisabled();
        }

        static auto was_button_hovered = false;
        auto is_hovered = ImGui::IsItemHovered();
        if (!was_button_hovered && is_hovered && !loading)
        {
            audio_manager->play_clip("fs1://audio/Minimalist7.wav");
            was_button_hovered = true;
        }
        else if (was_button_hovered && !is_hovered)
        {
            was_button_hovered = false;
        }

        width = ImGui::GetItemRectSize().x;
    }

    void load::draw_start_button()
    {
        auto* font = font_manager->get_font("honeyblot");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::FontScope font_scope{font};

        static auto width = 100.0f;
        static auto padding = 70.f;

        const auto font_height = ImGui::GetFontSize();
        ImGui::SetCursorPos(ImVec2(
                ImGui::GetWindowWidth() / 2 - width / 2,
                ImGui::GetWindowHeight()/ 2 - font_height / 2 + padding));

        ImGui::GroupScope text_group;
        ImGui::StyleVar style(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.75f));
        if (ImGui::Button("Quit", ImVec2(250.f, 100.f)))
        {
            scene_orchestrator_state->request_application_quit();
        }

        static auto was_button_hovered = false;
        auto is_hovered = ImGui::IsItemHovered();
        if (!was_button_hovered && is_hovered)
        {
            audio_manager->play_clip("fs1://audio/Minimalist7.wav");
            was_button_hovered = true;
        }
        else if (was_button_hovered && !is_hovered)
        {
            was_button_hovered = false;
        }

        width = ImGui::GetItemRectSize().x;
    }

    void load::on_gui()
    {
        draw_start_button();
        draw_exit_button();
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