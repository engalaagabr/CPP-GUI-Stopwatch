#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <chrono>
#include <iomanip>
#include <sstream>

bool running = false;
double elapsed = 0.0;
std::chrono::steady_clock::time_point startTime;

void startTimer()
{
    if (!running)
    {
        running = true;
        startTime = std::chrono::steady_clock::now();
    }
}

void stopTimer()
{
    if (running)
    {
        running = false;
        elapsed += std::chrono::duration<double>(
            std::chrono::steady_clock::now() - startTime).count();
    }
}

void resetTimer()
{
    running = false;
    elapsed = 0.0;
}

double getTime()
{
    if (!running) return elapsed;

    return elapsed + std::chrono::duration<double>(
        std::chrono::steady_clock::now() - startTime).count();
}

std::string formatTime(double seconds)
{
    int hrs = seconds / 3600;
    int mins = ((int)seconds % 3600) / 60;
    int secs = (int)seconds % 60;
    int ms = (seconds - (int)seconds) * 1000;

    std::stringstream ss;
    ss << std::setfill('0')
       << std::setw(2) << hrs << ":"
       << std::setw(2) << mins << ":"
       << std::setw(2) << secs << "."
       << std::setw(3) << ms;

    return ss.str();
}

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(1000, 600, "C++ GUI Stopwatch", NULL, NULL);
    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();

    io.Fonts->AddFontFromFileTTF(
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        42
    );

    ImGui::GetStyle().ScaleAllSizes(1.8f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("C++ Stopwatch Project");

        double t = getTime();

        ImVec2 window_size = ImGui::GetWindowSize();

        ImGui::SetCursorPosX(window_size.x * 0.25);
        // ImGui::Text("C++ GUI Stopwatch");

        ImGui::SetCursorPosX(window_size.x * 0.18);
        // ImGui::Text("Artificial Intelligence Programming Project");

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::SetCursorPosX(window_size.x * 0.20);

        ImGui::SetWindowFontScale(2.3f);
        ImGui::Text("%s", formatTime(t).c_str());
        ImGui::SetWindowFontScale(1.0f);

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::SetCursorPosX(window_size.x * 0.22);

        if (ImGui::Button("Start"))
            startTimer();

        ImGui::SameLine();

        if (ImGui::Button("Stop"))
            stopTimer();

        ImGui::SameLine();

        if (ImGui::Button("Reset"))
            resetTimer();

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SetCursorPosX(window_size.x * 0.12);
        ImGui::Text("Under supervision of Prof. Tamer Medhat");

        ImGui::SetCursorPosX(window_size.x * 0.20);
        ImGui::Text("Faculty of Artificial Intelligence");

        ImGui::End();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
}
