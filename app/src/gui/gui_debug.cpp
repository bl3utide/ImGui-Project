#include "common.hpp"
#ifdef _DEBUG
#include "error.hpp"
#include "config/config.hpp"
#include "config/cv.hpp"
#include "config/section.hpp"
#include "gui/gui.hpp"
#include "gui/gui_font.hpp"
#include "logger.hpp"

// TODO change app namespace
namespace ImGuiProject
{
namespace Gui
{
namespace Debug
{

// private
bool show_debug_menu_bar_ = true;
bool show_demo_window_ = false;
bool show_debug_window_ = true;

void drawDebugMenuBar(const ImVec2 viewport_pos)
{
    GuiUtil::PushFont((int)FontDebug::Text);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.35f, 0.35f, 0.35f, 0.65f));
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(ImVec2(center.x - 140.0f, viewport_pos.y), ImGuiCond_Always);
    ImGui::Begin("debug_control", nullptr,
        ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12.0f, 3.0f));
        if (show_debug_menu_bar_)
        {
            if (ImGui::Button("_")) show_debug_menu_bar_ = false;
        }
        else
        {
            if (ImGui::Button(">")) show_debug_menu_bar_ = true;
        }
        GuiUtil::MouseCursorToHand();
        ImGui::PopStyleVar();

        if (show_debug_menu_bar_)
        {
            ImGui::Checkbox("demo", &show_demo_window_);
            GuiUtil::MouseCursorToHand();
            ImGui::SameLine();
            ImGui::Checkbox("debug", &show_debug_window_);
            GuiUtil::MouseCursorToHand();
        }
    }
    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopFont();
}

void pushDebugStyles() noexcept
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.282f, 0.282f, 0.282f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.034f, 0.035f, 0.086f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.034f, 0.035f, 0.086f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.034f, 0.035f, 0.086f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.111f, 0.178f, 0.301f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.111f, 0.178f, 0.301f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.111f, 0.178f, 0.301f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.09f, 0.09f, 0.12f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.24f, 0.24f, 0.28f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4(0.24f, 0.24f, 0.28f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.275f, 0.275f, 0.275f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.380f, 0.380f, 0.380f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.427f, 0.427f, 0.427f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, ImVec4(0.275f, 0.275f, 0.275f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.965f, 0.965f, 0.965f, 1.0f));
}

void popDebugStyles() noexcept
{
    ImGui::PopStyleColor(17);
    ImGui::PopStyleVar();
}

void drawDebugTabItemGeneral()
{
    if (ImGui::BeginTabItem("General"))
    {
        // TODO add general data

        ImGui::EndTabItem();
    }
}

void drawDebugTabItemConfig()
{
    if (ImGui::BeginTabItem("Config"))
    {
        ImGui::BeginChild("config_value_list", ImVec2(600, 300));
        {
            auto drawParamsRow = [](const Config::Key key)
            {
                const Config::Cv cv = Config::getCv(key);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%s", cv.section_name().c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%s", cv.key_name().c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%s", cv.type_str().c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%s", cv.cv().c_str());
            };

            ImGui::Text("Loaded config values");

            if (ImGui::BeginTable("config_values", 4, ImGuiTableFlags_Borders
                | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit))
            {
                ImGui::TableSetupColumn("Section", ImGuiTableColumnFlags_WidthFixed, 80.0f);
                ImGui::TableSetupColumn("Key", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 60.0f);
                ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);

                ImGui::TableHeadersRow();

                for (int key_i = 0; key_i < static_cast<int>(Config::Key::_COUNT_); ++key_i)
                {
                    drawParamsRow(static_cast<Config::Key>(key_i));
                }

                ImGui::EndTable();
            }
        }
        ImGui::EndChild();

        ImGui::EndTabItem();
    }
}

void drawDebugTabItemLogger()
{
    if (ImGui::BeginTabItem("Logger"))
    {
        std::unique_lock lock(Logger::dlog_mutex);

        if (Logger::dlog.size() > 0)
            ImGui::Text("%d logs", Logger::dlog.back().log_id + 1);
        else
            ImGui::Text("no logs");

        ImGui::BeginChild("logger_list", ImVec2(800, 430), false, 0);
        {
            int selected_index = 0;
            std::vector<Logger::DisplayFormattedDebugLog> dlog_copy = Logger::dlog;
            for (auto iter = dlog_copy.cbegin(); iter != dlog_copy.cend(); ++iter)
            {
                bool is_selected = selected_index == Logger::dlog_selected_index;
                if (ImGui::Selectable(StringUtil::format("%05d %s", iter->log_id, iter->text.c_str()).c_str(), is_selected))
                {
                    Logger::dlog_selected_index = selected_index;
                    Logger::dlog_selected = *iter;
                }
                GuiUtil::MouseCursorToHand();
                ++selected_index;
            }

            if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
                ImGui::SetScrollHereY(1.0f);
        }
        ImGui::EndChild();
        if (ImGui::IsItemHovered())
        {
            auto f = []()
            {
                auto idx = Logger::dlog_selected_index;
                Logger::dlog_selected = Logger::DisplayFormattedDebugLog(Logger::dlog[idx]);
            };

            if (GuiUtil::IsCustomKeyPressed(GuiUtil::ImGuiCustomKey::Up, true) && Logger::dlog_selected_index > 0)
            {
                --Logger::dlog_selected_index;
                f();
            }
            else if (GuiUtil::IsCustomKeyPressed(GuiUtil::ImGuiCustomKey::Down, true) && Logger::dlog_selected_index < Logger::dlog.size() - 1)
            {
                ++Logger::dlog_selected_index;
                f();
            }
        }

        ImGui::Separator();

        if (Logger::dlog_selected_index != -1)
        {
            ImGui::BeginChild("logger_detail", ImVec2(800, 70), false, 0);
            {
                ImGui::Text("Log ID %d [%s]", Logger::dlog_selected.log_id, Logger::dlog_selected.category.c_str());
                ImGui::Text("%s", Logger::dlog_selected.timestamp.c_str());
                ImGui::Text("%s (LINE %s)", Logger::dlog_selected.function.c_str(), Logger::dlog_selected.line.c_str());
                ImGui::Text("%s", Logger::dlog_selected.text.c_str());
            }
            ImGui::EndChild();
        }

        ImGui::EndTabItem();
    }
}

void drawDebugWindow(bool* open, const int window_w, const int window_h,
    const State current_state)
{
    pushDebugStyles();

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::Begin("debug", open,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoTitleBar);
    {
        ImGui::Text("%dx%d", window_w, window_h);
        ImGui::SameLine();
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Separator(); //--------------------------------------------------

        ImGui::Text("%-24s: %d / %d", "has_error / showing?", has_error ? 1 : 0, showing_error_message ? 1 : 0);

        if (0 <= static_cast<int>(current_state)
            && static_cast<int>(current_state) <= static_cast<int>(State::None))
        {
            ImGui::Text("%-24s: [%d]%s", "state",
                current_state, STATE_STR.at(current_state));
        }

        State next_state = getNextState();
        if (0 <= static_cast<int>(next_state)
            && static_cast<int>(next_state) <= static_cast<int>(State::None))
        {
            ImGui::Text("%-24s: [%d]%s", "next state",
                next_state, STATE_STR.at(next_state));
        }

        if (ImGui::BeginTabBar("DebugTab", ImGuiTabBarFlags_None))
        {
            drawDebugTabItemGeneral();
            drawDebugTabItemConfig();
            drawDebugTabItemLogger();
            ImGui::EndTabBar();
        }
    }
    ImGui::End();

    popDebugStyles();
}

void drawDebugWindows(const int window_w, const int window_h, const State current_state)
{
    GuiUtil::PushFont((int)FontDebug::Text);

    if (show_demo_window_)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
        ImGui::ShowDemoWindow(&show_demo_window_);
        ImGui::PopStyleVar();
    }

    if (show_debug_window_)
        drawDebugWindow(&show_debug_window_, window_w, window_h, current_state);

    ImGui::PopFont();
}

} // Debug
} // Gui
} // ImGuiApp
#endif
