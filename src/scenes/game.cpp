#include "game.hpp"

namespace lerppana::flappykarp::scenes
{
    void game::draw_start_button()
    {
        if (game_state != game_state::stopped)
        {
            return;
        }

        auto font_size = 1.0f;

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

        auto text = "Start";

        if (ImGui::Button(text, ImVec2(250.f, 100.f)))
        {
            audio_manager->play_clip("fs1://audio/Minimalist2.wav");
            reset();
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

    void game::draw_exit_button()
    {
        if (game_state != game_state::stopped)
        {
            return;
        }

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

    void game::fixed_update(core::dt_t dt)
    {
        m_detect_player_hits();
    }

    void game::reset()
    {
        auto player_physics = objects->get_tagged_component<component::physics_3d>(core::tag::player_1);
        auto* rigid_body = (btRigidBody*)player_physics.get();
        auto& tr = rigid_body->getWorldTransform();
        tr.setOrigin(btVector3{5.f, 8.f, 0.f});
        btQuaternion euler;
        euler.setEuler(glm::pi<float>(), 0.f, 0.f);
        tr.setRotation(euler);
        rigid_body->setWorldTransform(tr);

        game_state = game_state::running;
        score = 0.0f;
        pipe_scroller->reset_system(*this);
        pipe_scroller->enabled = true;
        player_controller->enabled = true;
    }

    void game::start()
    {
        reset();
    }

    void game::on_gui()
    {
        m_gui_draw_score();
        draw_start_button();
        draw_exit_button();
    }

    void game::update(core::dt_t dt)
    {
        if (game_state == running)
        {
            score += (dt.count()/1000.0f);
        }
    }

    void game::m_detect_player_hits()
    {
        if (!objects->is_tagged(core::tag::player_1))
        {
            return;
        }

        if (!objects->tagged_has_component<component::physics_3d>(core::tag::player_1))
        {
            return;
        }

        auto physics_component = objects->get_tagged_component<component::physics_3d>(core::tag::player_1);
        auto rigid_body = (btRigidBody*)physics_component.get();
        physics_world->contact_test(
                rigid_body,
                [&](const physics::contact_result_args& args)
                {
                    game_state = game_state::stopped;
                    pipe_scroller->enabled = false;
                    player_controller->enabled = false;
                });
    }

    void game::m_gui_draw_score()
    {
        auto* font = font_manager->get_font("honeyblot");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::FontScope font_scope{font};

        static auto width = 100.0f;
        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - width / 2,20.f));

        ImGui::GroupScope text_group;
        ImGui::Text("%d", (uint32_t)score);
        width = ImGui::GetItemRectSize().x;
    }
}
