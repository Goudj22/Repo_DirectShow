#include "Fonctionnalité.h"

using namespace std;

Fonctionnalité::Fonctionnalité()
{
}

Fonctionnalité::~Fonctionnalité()
{

}

void Fonctionnalité::Play()
{
    if (m_state != STATE_PAUSED && m_state != STATE_STOPPED)
    {
        return;
    }

    hr = pControl->Run();
    if (SUCCEEDED(hr))
    {
        m_state = STATE_RUNNING;
    }
}

void Fonctionnalité::Pause()
{
    if (m_state != STATE_RUNNING)
    {
        return;
    }

    hr = pControl->Pause();
    if (SUCCEEDED(hr))
    {
        m_state = STATE_PAUSED;
    }
}

void Fonctionnalité::FastForward()
{
    if (m_state != STATE_RUNNING)
    {
        return;
    }

    hr = pSeek->SetRate(2.0);
}

void Fonctionnalité::Restart()
{
    if (m_state == STATE_RUNNING)
    {
        Fonctionnalité::Pause();
    }
    rtNow = 2 * ONE_SECOND;
    hr = pSeek->SetPositions(&rtNow, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    hr = pControl->Run();
}

void Fonctionnalité::Quitter()
{
    if (m_state != STATE_RUNNING && m_state != STATE_PAUSED)
    {
        return;
    }

    hr = pControl->Stop();
    if (SUCCEEDED(hr))
    {
        m_state = STATE_STOPPED;
    }
}
