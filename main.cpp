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


GLFWwindow* window = glfwCreateWindow(1000, 600, "Stopwatch", NULL, NULL);
glfwMakeContextCurrent(window);

IMGUI_CHECKVERSION();
ImGui::CreateContext();

ImGuiIO& io = ImGui::GetIO();

io.Fonts->AddFontFromFileTTF(
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
    42
);

ImGui_ImplGlfw_InitForOpenGL(window, true);
ImGui_ImplOpenGL3_Init("#version 130");

while (!glfwWindowShouldClose(window))
{
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    /* FULLSCREEN UI */

    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

    ImGui::Begin("Main",
    NULL,
    ImGuiWindowFlags_NoDecoration |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoResize);

    ImVec2 window_size = ImGui::GetWindowSize();
    double t = getTime();

    /* CENTER TIMER */

    float centerY = window_size.y * 0.35f;
    ImGui::SetCursorPosY(centerY);

    ImGui::SetWindowFontScale(2.3f);

    std::string timeText = formatTime(t);
    float textWidth = ImGui::CalcTextSize(timeText.c_str()).x;

    ImGui::SetCursorPosX((window_size.x - textWidth) * 0.5f);
    ImGui::Text("%s", timeText.c_str());

    ImGui::SetWindowFontScale(1.0f);

    ImGui::Spacing();
    ImGui::Spacing();

    /* CENTER BUTTONS */

    float buttonWidth = 120;
    float spacing = 20;
    float totalWidth = buttonWidth * 3 + spacing * 2;

    ImGui::SetCursorPosX((window_size.x - totalWidth) * 0.5f);

    if (ImGui::Button("Start", ImVec2(buttonWidth,40)))
        startTimer();

    ImGui::SameLine(0, spacing);

    if (ImGui::Button("Stop", ImVec2(buttonWidth,40)))
        stopTimer();

    ImGui::SameLine(0, spacing);

    if (ImGui::Button("Reset", ImVec2(buttonWidth,40)))
        resetTimer();

    /* MOVE FOOTER TO BOTTOM */

    float footerStart = window_size.y - 120;
    ImGui::SetCursorPosY(footerStart);

    ImGui::Separator();
    ImGui::Spacing();
    /* SMALL FOOTER */

    ImGui::SetWindowFontScale(0.8f);

    const char* line1 = "Supervised by";
    const char* line2 = "Prof. Tamer Medhat";
    const char* line3 = "Faculty of Artificial Intelligence";

    float w1 = ImGui::CalcTextSize(line1).x;
    float w2 = ImGui::CalcTextSize(line2).x;
    float w3 = ImGui::CalcTextSize(line3).x;

    ImGui::SetCursorPosX((window_size.x - w1) * 0.5f);
    ImGui::Text("%s", line1);

    ImGui::SetCursorPosX((window_size.x - w2) * 0.5f);
    ImGui::Text("%s", line2);

    ImGui::SetCursorPosX((window_size.x - w3) * 0.5f);
    ImGui::Text("%s", line3);

    ImGui::SetWindowFontScale(1.0f);

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
