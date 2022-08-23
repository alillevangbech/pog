// Dear ImGui: standalone example application for GLFW + OpenGL2, using legacy fixed pipeline

// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

// **DO NOT USE THIS CODE IF YOUR CODE/ENGINE IS USING MODERN OPENGL (SHADERS, VBO, VAO, etc.)**
// **Prefer using the code in the example_glfw_opengl2/ folder**
// See imgui_impl_glfw.cpp for details.
//

// #define DDEBUG

#ifdef _WIN32
#include <windows.h>
auto handle = ShowWindow(GetConsoleWindow(), SW_HIDE); //SW_RESTORE to bring back
#endif

#include <cfloat>
#include <cstring>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>
#include "boxfilter.h"
#include "pog.h"
#include "launch.h"

#include "imgui_internal.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <filesystem>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#define SEARCH_BUFFER_SIZE 1024

#define WINDOW_SIZE_X 512
#define WINDOW_SIZE_Y 

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void glfwSetWindowCenter(GLFWwindow* window);

int main(int, char**)
{
	
	vector<pog_command_error> pog_errors;
	unordered_map<string, pog_command> pog_map;
	for (auto const& dir_entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
		if (dir_entry.path().extension() == ".pog") {
			parse_pog_file(dir_entry.path().string(), pog_map, pog_errors);
		}
	}

    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;


	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(520, 300, "Dear Emilie <3", NULL, NULL);
    if (window == NULL)
        return 1;

	glfwSetWindowCenter(window);
	glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init(); // Load Fonts - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit). - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call. - Read 'docs/FONTS.md' for more instructions and details. - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ ! io.Fonts->AddFontDefault(); io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f); io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f); io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f); io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);

    // Our state
    int initial_focus = 1;
	std::string name = "##Search";
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	std::vector<std::string> items;
	items.reserve(pog_map.size());
	for (auto kv : pog_map) items.push_back(kv.first + string(";") + kv.second.value);

    char pattern_buffer[256] = { '\0' };
	int* selected_item = new int(-1);
	int count = 0;

	
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoCollapse;
	window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	//window_flags |= ImGuiWindowFlags_NoDecoration;
	//window_flags |= ImGuiWindowFlags_NoBackground;

	bool use_work_area = false;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
	
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
		//ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f), ImGuiCond_Always, ImVec2(0.5f,0.5f));
#ifdef DDEBUG
	//	ImGui::SetNextWindowSize(ImVec2(512,1000 + 75 + 17 * count), ImGuiCond_Always);
#else 
		//ImGui::SetNextWindowSize(ImVec2(512,75 + 17 * count), ImGuiCond_Always);
#endif

	glfwSetWindowSize(window, 512, 75 + 17 * count);
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x, 75 + 17 * count));

        {
			ImGui::Begin("pog", NULL, window_flags);
			if (initial_focus > 0) {
				ImGui::SetKeyboardFocusHere();
				initial_focus--;
			}
			
			//ImGui::PushItemWidth(ImGui::GetWindowWidth()*0.95);
			ImGui::PushItemWidth(-FLT_MIN);
			if (ImGui::InputTextWithHint(name.c_str(), "Search...", pattern_buffer, 256))
				*selected_item = -1;
			count = ImGui::ApplyFilter(selected_item, pattern_buffer, items);
			ImGui::PopItemWidth();
	
#ifdef DDEBUG
			ImGuiContext& g = *GImGui;
			ImRect r = g.LastItemData.Rect;
			ImGui::Text("%s\n selected_item: %d\n shift key %d\n count: %d\n listbox size: min=(%0.1f, %0.1f), max=(%0.1f, %0.1f).\n changed %d",
						*selected_item < 0 ? "No item selected" : items[*selected_item].c_str(),
						*selected_item,
						io.KeyShift,
						count,
						r.Min.x, r.Min.y, r.Max.x, r.Max.y, 1);
#endif
			if (count == 0) {
				ImGui::Text("");
				ImGui::SameLine(ImGui::GetWindowWidth() - 168);
				ImGui::Text("MADE BY ALEXANDER BECH");
			}

			if (*selected_item != -1 && ImGui::IsKeyPressed(ImGuiKey_Enter)) {
				size_t idx = items[*selected_item].find_first_of(";");
				const char* s_const = pog_map[items[*selected_item].substr(0, idx)].value.c_str();
				char* s = strdup(s_const);

				ImGui::Text("Execute this file or url with a default program!\n %s", s);
				openFile(s);
				// launch
				free(s);
			}

			ImGui::End();


			if (!io.WantTextInput && ImGui::IsKeyPressed(ImGuiKey_Escape))
				glfwSetWindowShouldClose(window, 1);

			//ImGui::ShowMetricsWindow();
			//ImGui::ShowDemoWindow();
			//ImGui::ShowStyleEditor();

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
        //GLint last_program;
        //glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
        //glUseProgram(0);
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
        //glUseProgram(last_program);

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
	
	delete selected_item;

    return 0;
}


void glfwSetWindowCenter(GLFWwindow* window) {
    // Get window position and size
    int window_x, window_y;
    glfwGetWindowPos(window, &window_x, &window_y);

    int window_width, window_height;
    glfwGetWindowSize(window, &window_width, &window_height);

    // Halve the window size and use it to adjust the window position to the center of the window
    window_width *= 0.5;
    window_height *= 0.5;

    window_x += window_width;
    window_y += window_height;

    // Get the list of monitors
    int monitors_length;
    GLFWmonitor **monitors = glfwGetMonitors(&monitors_length);

    if(monitors == NULL) {
        // Got no monitors back
        return;
    }

    // Figure out which monitor the window is in
    GLFWmonitor *owner = NULL;
    int owner_x, owner_y, owner_width, owner_height;

    for(int i = 0; i < monitors_length; i++) {
        // Get the monitor position
        int monitor_x, monitor_y;
        glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

        // Get the monitor size from its video mode
        int monitor_width, monitor_height;
        GLFWvidmode *monitor_vidmode = (GLFWvidmode*) glfwGetVideoMode(monitors[i]);

        if(monitor_vidmode == NULL) {
            // Video mode is required for width and height, so skip this monitor
            continue;

        } else {
            monitor_width = monitor_vidmode->width;
            monitor_height = monitor_vidmode->height;
        }

        // Set the owner to this monitor if the center of the window is within its bounding box
        if((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
            owner = monitors[i];

            owner_x = monitor_x;
            owner_y = monitor_y;

            owner_width = monitor_width;
            owner_height = monitor_height;
        }
    }

    if(owner != NULL) {
        // Set the window position to the center of the owner monitor
        glfwSetWindowPos(window, owner_x + (owner_width * 0.5) - window_width, owner_y + (owner_height * 0.5) - window_height);
    }
}