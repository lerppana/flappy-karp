#include "game.hpp"

namespace lerppana::flappykarp::scenes
{
    void game::start()
    {
        if (!font_manager->fonts.contains("thaleah"))
        {
            font_manager->add_font(
                    "thaleah",
                    "fs1://fonts/ThaleahFat.ttf",
                    128);
        }
    }

    void game::on_gui()
    {
        auto* font = font_manager->get_font("thaleah");
        ImGui::SetWindowFontScale(2.5f);
        ImGui::FontScope font_scope{font};

        static auto width = 100.0f;
        auto padding = 100.f;
        const auto font_height = ImGui::GetFontSize();
        ImGui::SetCursorPos(ImVec2(
                ImGui::GetWindowWidth() / 2 - width / 2,
                ImGui::GetWindowHeight() / 2 - font_height - padding));

        ImGui::GroupScope text_group;
        ImGui::Text("%d", (uint32_t)score);
        width = ImGui::GetItemRectSize().x;
    }

    void game::update(core::dt_t dt)
    {
        score += (dt.count()/1000.0f);
    }
}
