#include "game.hpp"

namespace lerppana::flappykarp::scenes
{
    void game::draw_start_button()
    {
        if (game_state != game_state::stopped)
        {
            return;
        }

        static auto is_active = false;

        ImGui::GroupScope text_group;
        if (m_draw_button("Flap!", 70.f, is_active))
        {
            audio_manager->play_clip("fs1://audio/Minimalist2.wav");
            reset();
        }

        static auto was_button_hovered = false;
        auto is_hovered = ImGui::IsItemHovered();
        if (!was_button_hovered && is_hovered)
        {
            was_button_hovered = true;
            audio_manager->play_clip("fs1://audio/Minimalist7.wav");
        }
        else if (was_button_hovered && !is_hovered)
        {
            was_button_hovered = false;
        }

        is_active = ImGui::IsItemActive();
    }

    void game::draw_exit_button()
    {
        if (game_state != game_state::stopped)
        {
            return;
        }

        static auto is_active = false;

        ImGui::GroupScope text_group;
        if (m_draw_button("Quit", -70.f, is_active))
        {
            scene_orchestrator_state->request_application_quit();
        }

        is_active = ImGui::IsItemActive();

        static auto was_button_hovered = false;
        auto is_hovered = ImGui::IsItemHovered();
        if (!was_button_hovered && is_hovered)
        {
            was_button_hovered = true;
            audio_manager->play_clip("fs1://audio/Minimalist7.wav");
        }
        else if (was_button_hovered && !is_hovered)
        {
            was_button_hovered = false;
        }
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
        game_state = game_state::stopped;
        pipe_scroller->enabled = false;
        player_controller->enabled = false;

        auto player_physics = objects->get_tagged_component<component::physics_3d>(core::tag::player_1);
        if (player_physics.get() == nullptr)
        {
            return;
        }

        auto* rigid_body = (btRigidBody*)player_physics.get();
        auto& tr = rigid_body->getWorldTransform();
        tr.setOrigin(btVector3{5.f, -3.f, 0.f});
        rigid_body->setWorldTransform(tr);
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
                    if (player_controller->can_splash())
                    {
                        player_controller->splash(*this, util::random_value(2.0f, 4.0f));
                    }
                });
    }

    bool game::m_draw_button(
            std::string_view button_text,
            float padding,
            bool is_active)
    {
        auto font_size = 1.0f;

        auto* font = font_manager->get_font("honeyblot");

        ImGui::FontScope font_scope{font};
        ImGui::SetWindowFontScale(font_size);

        static auto button_width = 100.0f;

        const auto font_height = ImGui::GetFontSize();

        auto window_width = ImGui::GetWindowWidth();
        auto window_height = ImGui::GetWindowHeight();

        auto x = window_width / 2 - button_width / 2;
        auto y = window_height / 2 - font_height / 2 - padding;
        auto window_pos = ImGui::GetWindowPos();

        ImGui::GetWindowDrawList()->AddRectFilled(
                ImVec2(window_pos.x + x, window_pos.y + y + 10.f),
                ImVec2(window_pos.x + x + 250.f, window_pos.y + y + 110.f),
                ImGui::ColorConvertFloat4ToU32(ImVec4(.2f, .2f, .2f, 1.f)),
                0.f);

        if (is_active)
        {
            y += 10.f;
        }

        ImGui::StyleVar style(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.5f, 0.75f));

        ImGui::StyleColorScope button_color(ImGuiCol_Button, ImVec4(0.3f, 0.6f, 0.8f, 1.0f));
        ImGui::StyleColorScope button_active(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.7f, 1.0f, 1.0f));
        ImGui::StyleColorScope button_hovered(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.7f, 0.9f, 1.0f));

        ImGui::SetCursorPos(ImVec2(x,y));
        auto is_clicked = ImGui::Button(button_text.data(), ImVec2(250.f, 100.f));

        button_width = ImGui::GetItemRectSize().x;

        return is_clicked;
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
