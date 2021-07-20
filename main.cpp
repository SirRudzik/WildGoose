#include <GL/glew.h>
#include "include/CoreSystems/Window.h"
#include "include/Input/Input.h"
#include "include/Time/Clock.h"
#include "include/Graphics/Texture.h"
#include "include/Graphics/Mesh.h"
#include "include/Graphics/Rectangle.h"
#include "include/Graphics/Circle.h"
#include "glm/glm.hpp"

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    WG::Clock Zegar;
    WG::Input wejscie;
    WG::Window okno("test", 600, 600);
    Zegar.Start();
    okno.Init();
    okno.EnableGL();
    glEnable(GL_TEXTURE_2D);
    WG::Image image;
    image.Load("1.tga");
    WG::Texture tekstura(&image);
    tekstura.Bind();
    WG::Rectangle kwadrat(1.0, 1.0);

    while(!okno.IsClose())
    {
        double dt = 0.0f;
        static float rot = 0.0f;
        static float scale = 0.5f;
        static float fx, fy = 0.0f;

        Zegar.Tick();
        okno.CheckEvent();
        wejscie.Update(okno.GetHandle());

        if(wejscie.CheckKey(VK_ESCAPE) == WG::KEY_STATE::KEY_DOWN)
            okno.Close();

        dt = Zegar.GetDeltaTime(WG::TIME_UNIT::MILLI);
        rot += (0.0f * dt);

        glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPushMatrix();
        glTranslatef(fx, fy, 0.0f);
        glRotatef(-rot, 0.0f, 0.0f, 1.0f);
        glScalef(scale, scale, scale);
        glFrontFace(GL_CCW);
        glBegin(GL_TRIANGLES);
        for(std::uint32_t i = 0; i < kwadrat.GetTrianglesNumber() * 3; i++)
        {
        //    glTexCoord3f(kwadrat.GetVertices()[kwadrat.GetIndices()[i]].texCoord.x,
        //                kwadrat.GetVertices()[kwadrat.GetIndices()[i]].texCoord.y,
       //                 kwadrat.GetVertices()[kwadrat.GetIndices()[i]].texCoord.z);
            glColor3f(kwadrat.GetVertices()[kwadrat.GetIndices()[i]].color.r,
                      kwadrat.GetVertices()[kwadrat.GetIndices()[i]].color.g,
                      kwadrat.GetVertices()[kwadrat.GetIndices()[i]].color.b);
            glVertex3f(kwadrat.GetVertices()[kwadrat.GetIndices()[i]].pos.x,
                       kwadrat.GetVertices()[kwadrat.GetIndices()[i]].pos.y,
                       kwadrat.GetVertices()[kwadrat.GetIndices()[i]].pos.z);
        }
        glEnd();
        glPopMatrix();
        okno.SwapBuffer();
    }
    okno.DisableGL();
    return 0;
}
