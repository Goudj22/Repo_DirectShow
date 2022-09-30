#pragma once
#ifndef FONCTIONNALITE_H
#define FONCTIONNALITE_H
#include <iostream>
#include <new>
#include <windows.h>
#include <dshow.h>
#pragma comment(lib, "Strmiids.lib")
#define ONE_SECOND 10000000

enum PlaybackState
{
    STATE_NO_GRAPH,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED,
};

class Fonctionnalité
{
	public:
        HRESULT hr;
        IGraphBuilder* pGraph = NULL;
        IMediaControl* pControl = NULL;
        IMediaEvent* pEvent = NULL;
        IMediaSeeking* pSeek = NULL;
        PlaybackState   m_state = STATE_PAUSED;
        REFERENCE_TIME rtNow = 0;

        Fonctionnalité();
        ~Fonctionnalité();
        void Play();
        void Pause();
        void Quitter();
        void FastForward();
        void Restart();
        PlaybackState State() { return m_state; }
};

#endif