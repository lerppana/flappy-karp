#include "game.hpp"

namespace lerppana::flappykarp::scenes
{
    void game::fixed_update(core::dt_t dt)
    {
        m_detect_player_hits();
    }

    void game::reset()
    {
        game_statesm = game_state::running;
        score = 0.0f;
        pipe_scroller->reset_system(*this);
    }

    void game::start()
    {
        if (!font_manager->fonts.contains("thaleah"))
        {
            font_manager->add_font(
                    "thaleah",
                    "fs1://fonts/ThaleahFat.ttf",
                    64);
        }

        reset();
    }

    void game::on_gui()
    {
        m_gui_draw_score();
        m_gui_draw_reset_button();
    }

    void game::update(core::dt_t dt)
    {
        score += (dt.count()/1000.0f);
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
                    common::console::log("hit!");
                    game_state = game_state::stopped;
                });
    }

    void game::m_gui_draw_score()
    {
        auto* font = font_manager->get_font("thaleah");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::FontScope font_scope{font};

        static auto width = 100.0f;
        ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() / 2 - width / 2,0.f));

        ImGui::GroupScope text_group;
        ImGui::Text("%d", (uint32_t)score);
        width = ImGui::GetItemRectSize().x;
    }

    void game::m_gui_draw_reset_button()
    {
        auto* font = font_manager->get_font("thaleah");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::FontScope font_scope{font};

        static auto width = 100.0f;
        const auto font_height = ImGui::GetFontSize();
        ImGui::SetCursorPos(ImVec2(
                ImGui::GetWindowWidth() / 2 - width / 2,
                ImGui::GetWindowHeight()/ 2 - font_height / 2));

        ImGui::GroupScope text_group;
        if (ImGui::Button("Reset"))
        {
            reset();
        }
        width = ImGui::GetItemRectSize().x;
    }
}
