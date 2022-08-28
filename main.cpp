// Dear ImGui: standalone example application for GLFW + OpenGL2, using legacy fixed pipeline

// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the example_glfw_opengl2/ folder**
// See imgui_impl_glfw.cpp for details.

//#define DDEBUG

#ifdef _WIN32
#include <windows.h>
auto handle = ShowWindow(GetConsoleWindow(), SW_HIDE); // SW_RESTORE to bring back
#endif

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>
#include "imgui_internal.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <filesystem>
#include <cfloat>
#include <cstring>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

#include "filter.h"
#include "pog.h"
#include "launch.h"
#include "glfw_utils.h"

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

//#define DDEBUG

#define WINDOW_SIZE_X 512
#ifdef DDEBUG
#define WINDOW_SIZE_Y 1000
#else
#define WINDOW_SIZE_Y 65
#endif
#define WINDOW_SIZE_Y_INCREMENTS 17.5

#define RESET_VALUE -1
#define SEARCH_BUFFER_CAPACITY 256

int main(int, char **)
{
    vector<pog_command_error> pog_errors;
    unordered_map<string, pog_command> pog_map;
    for (auto const &dir_entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        if (dir_entry.path().extension() == ".pog")
        {
            parse_pog_file(dir_entry.path().string(), pog_map, pog_errors);
        }
    }

    // Setup window
    glfwSetErrorCallback(glfwUtilErrorCallback);
    if (!glfwInit())
        return 1;

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "Dear Emilie <3", NULL, NULL);
    if (window == NULL)
        return 1;

    glfwUtilSetWindowCenter(window);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
    io.ConfigViewportsNoDecoration = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init(); // Load Fonts - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit). - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call. - Read 'docs/FONTS.md' for more instructions and details. - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ ! io.Fonts->AddFontDefault(); io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f); io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f); io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f); io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    // IM_ASSERT(font != NULL);

    // Our state
    int initial_focus = 1;
    std::string name = "##Search";
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    std::vector<std::string> items;
    std::vector<std::pair<int, int>> items_inview;
    items.reserve(pog_map.size());
    items_inview.reserve(pog_map.size());
    for (auto kv : pog_map)
        items.push_back(kv.first + string(";") + kv.second.value);
    char pattern_buffer[SEARCH_BUFFER_CAPACITY] = {'\0'};
    int *selected_item = new int(RESET_VALUE);
    int *selected_item_inview = new int(RESET_VALUE);
    int count = 0;
    bool update_view = false;
    bool show_popup_error = false;
    char* popup_error_info = NULL;

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
    // end state

    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(viewport->WorkPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x, WINDOW_SIZE_Y + WINDOW_SIZE_Y_INCREMENTS * count), ImGuiCond_Always);
        {
            ImGui::Begin("pog", NULL, window_flags);
            if (initial_focus > 0)
            {
                ImGui::SetKeyboardFocusHere();
                initial_focus--;
            }

            ImGui::PushItemWidth(-FLT_MIN);
            if (update_view = ImGui::InputTextWithHint(name.c_str(), "Search...", pattern_buffer, SEARCH_BUFFER_CAPACITY))
            {
                *selected_item = RESET_VALUE;
                *selected_item_inview = RESET_VALUE;
            }

            count = ImGui::ApplyFilter(selected_item, selected_item_inview, pattern_buffer, items, items_inview, update_view);
            ImGui::PopItemWidth();

#ifdef DDEBUG
            ImGuiContext &g = *GImGui;
            ImRect r = g.LastItemData.Rect;
            ImGui::Text("%s\n selected_item value: %d\n selected_item_inview %d\n pogmap size %d\n count: %d\n listbox size: min=(%0.1f, %0.1f), max=(%0.1f, %0.1f)",
                        *selected_item == RESET_VALUE ? "No item selected" : items[items_inview[*selected_item].first].c_str(),
                        *selected_item,
                        *selected_item_inview,
                        pog_map.size(),
                        count,
                        r.Min.x, r.Min.y, r.Max.x, r.Max.y);
#endif
            if (*selected_item != RESET_VALUE && ImGui::IsKeyPressed(ImGuiKey_Enter))
            {
                size_t idx = items[*selected_item].find_first_of(";");
                const char *s_const = pog_map[items[*selected_item].substr(0, idx)].value.c_str();
                char *s = strdup(s_const);

                ImGui::Text("Execute this file or url with a default program!\n %s", s);

                openfile_error_info info = openFile(s);

                if (info.info[0] == '\0' || info.error_code == 0) {
                    free(s);
                    free(info.info);
                    glfwSetWindowShouldClose(window, 1);
                } else {
                    free(s);
                    show_popup_error = true;
                    popup_error_info = info.info;
                }


                // launch
            }

            if (show_popup_error) {
                ImGui::OpenPopup("ERROR");
            }
            if (ImGui::BeginPopupModal("ERROR", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize))
            {
                ImGui::Text("%s\n\n", popup_error_info);
                ImGui::Separator();
                size_t idx = items[*selected_item].find_first_of(";");
                const char *s_const = pog_map[items[*selected_item].substr(0, idx)].value.c_str();
                ImGui::Text("shortcut: %s\n", s_const);

                // static int unused_i = 0;
                // ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");
                ImGui::SetKeyboardFocusHere();
                if (ImGui::Button("Continue", ImVec2(145, 0)))
                {
                    ImGui::CloseCurrentPopup();
                    show_popup_error = false;
                    free(popup_error_info);
                    glfwHideWindow(window);
                    initial_focus++;
                }
                ImGui::SameLine();
                if (ImGui::Button("Exit application", ImVec2(145, 0)))
                {
                    ImGui::CloseCurrentPopup();
                    show_popup_error = false;
                    free(popup_error_info);
                    initial_focus++;
                    glfwSetWindowShouldClose(window, 1);
                }
                ImGui::EndPopup();
            }

            ImGui::End();

            if (!io.WantTextInput && ImGui::IsKeyPressed(ImGuiKey_Escape))
                glfwSetWindowShouldClose(window, 1);

            // ImGui::ShowMetricsWindow();
            ImGui::ShowDemoWindow();
            // ImGui::ShowStyleEditor();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        // If you are using this code with non-legacy OpenGL header/contexts (which you should not, prefer using imgui_impl_opengl3.cpp!!),
        // you may need to backup/reset/restore other state, e.g. for current shader using the commented lines below.
        // GLint last_program;
        // glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
        // glUseProgram(0);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        // glUseProgram(last_program);

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    delete selected_item;
    delete selected_item_inview;

    return 0;
}