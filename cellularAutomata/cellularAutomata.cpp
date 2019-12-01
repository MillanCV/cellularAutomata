

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <iostream>
using namespace std;

class GameOfLife : public olc::PixelGameEngine
{
public:
    GameOfLife()
    {
        sAppName = "GameOfLife";
    }

private:
    int *m_output;
    int *m_state;



public:
    bool OnUserCreate() override
    {
        // allocate memory for output and state
        m_output = new int[ScreenWidth()*ScreenHeight()];
        m_state = new int[ScreenWidth()*ScreenHeight()];
        memset(m_output, 0, ScreenWidth()*ScreenHeight() * sizeof(int));
        memset(m_state, 0, ScreenWidth()*ScreenHeight() * sizeof(int));

        for (int i = 0; i < ScreenWidth()*ScreenHeight(); i++)
            m_state[i] = rand() % 2;

        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {

        //if (!GetKey(olc::Key::Q).bHeld)
        //    return true;
        
        this_thread::sleep_for(50ms);

        auto cell = [&](int x, int y)
        {
            return m_output[y*ScreenWidth() + x];
        };

        // Store output state
        for (int i = 0; i < ScreenWidth()*ScreenHeight(); i++)
            m_output[i] = m_state[i];

        for (int x=0; x< ScreenWidth()-1; x++)
            for (int y = 1; y < ScreenHeight() - 1; y++)
            {
                int nNeightbours = cell(x - 1, y - 1) + cell(x - 0, y - 1) + cell(x + 1, y - 1) +
                    cell(x - 1, y - 0) + 0 + cell(x + 1, y - 0) +
                    cell(x - 1, y + 1) + cell(x - 0, y + 1) + cell(x + 1, y + 1);
                if (cell(x, y) == 1)
                    m_state[y*ScreenWidth() + x] = nNeightbours == 2 || nNeightbours == 3;
                else
                    m_state[y*ScreenWidth() + x] = nNeightbours == 3 ;

                if (cell(x, y) == 1)
                    Draw(x, y, olc::BLUE);
                else
                    Draw(x, y, olc::WHITE);
            }


        return true;
    }
};


int main()
{
    GameOfLife demo;
    if (demo.Construct(100, 100, 4,4))
        demo.Start();

    return 0;
}