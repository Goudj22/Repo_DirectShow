#include <dshow.h>
#include "Fonctionnalité.h"


int main(void)
{
    Fonctionnalité fonction;;

    // Initialize the COM library.
    fonction.hr = CoInitialize(NULL);
    if (FAILED(fonction.hr))
    {
        printf("ERROR - Could not initialize COM library");
        return 0;
    }

    // Create the filter graph manager and query for interfaces.
    fonction.hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
        IID_IGraphBuilder, (void**)&fonction.pGraph);
    if (FAILED(fonction.hr))
    {
        printf("ERROR - Could not create the Filter Graph Manager.");
        return 0;
    }

    // Build the graph. IMPORTANT: Change this string to a file on your system.
    fonction.hr = fonction.pGraph->RenderFile(L"C:\\Users\\fbgoudiaby\\Downloads\\Labo1DS\\Example.avi", NULL);

    fonction.hr = fonction.pGraph->QueryInterface(IID_IMediaControl, (void**)&fonction.pControl);
    fonction.hr = fonction.pGraph->QueryInterface(IID_IMediaEvent, (void**)&fonction.pEvent);
    fonction.hr = fonction.pGraph->QueryInterface(IID_IMediaSeeking, (void**)&fonction.pSeek);
    
    char choix;
    if (SUCCEEDED(fonction.hr))
    {
        // Run the graph.
        //hr = pControl->Run();
        fonction.Play();
        while (true)
        {
            std::cout << "Choisissez une des option suivante\n"
                << " P - Play  ou Pause  \n"
                << " A - Avance accélérée\n"
                << " R - Retour au début \n"
                << " Q - Quitter \n";
            std::cin >> choix;
            switch (choix)
            {
            case 'P':
                if (fonction.m_state == STATE_PAUSED)
                {
                    fonction.Play();
                }
                else if (fonction.m_state == STATE_RUNNING)
                {
                    fonction.Pause();
                }
                break;
            case 'A':
                fonction.FastForward();
                break;
            case 'R':
                fonction.Restart();
                break;
            case 'Q':
                fonction.Quitter();
                break;
            default:
                break;
            }
        }


        if (SUCCEEDED(fonction.hr))
        {
            // Wait for completion.
            long evCode;
            fonction.pEvent->WaitForCompletion(INFINITE, &evCode);

            // Note: Do not use INFINITE in a real application, because it
            // can block indefinitely.
        }
    }


    fonction.pControl->Release();
    fonction.pEvent->Release();
    fonction.pGraph->Release();
    CoUninitialize();
}