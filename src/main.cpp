#include <catch2/catch2/catch_amalgamated.hpp>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Input/Input.h>

#include "AdvancedNetworking.h"
#include "Urho3D/RmlUI/RmlUI.h"

// This is probably always OK.
using namespace Urho3D;


class ShooterTemplateApplication : public Application
{
    // This macro defines some methods that every `Urho3D::Object` descendant should have.
    URHO3D_OBJECT(ShooterTemplateApplication, Application)

    ///
    SharedPtr<AdvancedNetworking> runningSample_;

public:
    // Likewise every `Urho3D::Object` descendant should implement constructor with single `Context*` parameter.
    ShooterTemplateApplication(Context* context)
        : Application(context)
    {
    }

    void Setup() override
    {
        // Engine is not initialized yet. Set up all the parameters now.
#if defined(NDEBUG) || defined (_DEBUG)
        engineParameters_[EP_FULL_SCREEN] = false;
        //engineParameters_[EP_WINDOW_HEIGHT] = 600;
        //engineParameters_[EP_WINDOW_WIDTH] = 800;
#else
        engineParameters_[EP_FULL_SCREEN] = true;
#endif
        // Resource prefix path is a list of semicolon-separated paths which will be checked for containing resource directories. They are relative to application executable file.
        
        auto args = GetArguments();
        if (args.empty())
        {
            engineParameters_[EP_RESOURCE_PREFIX_PATHS] = ".;..";
        }
        else
        {
            ea::string path;
            for (auto& s: args)
            {
                if (path.empty())
                    path = s;
                else
                    path = path + ";" + s;
            }
            engineParameters_[EP_RESOURCE_PREFIX_PATHS] = path;
        }
    }

    void Start() override
    {
        // At this point engine is initialized, but first frame was not rendered yet. Further setup should be done here. To make sample a little bit user friendly show mouse cursor here.
        GetSubsystem<Input>()->SetMouseVisible(true);

#if URHO3D_RMLUI
        auto* rmlUi = context_->GetSubsystem<RmlUI>();
        rmlUi->LoadFont("Fonts/NotoSans-Condensed.ttf", false);
        rmlUi->LoadFont("Fonts/NotoSans-CondensedBold.ttf", false);
        rmlUi->LoadFont("Fonts/NotoSans-CondensedBoldItalic.ttf", false);
        rmlUi->LoadFont("Fonts/NotoSans-CondensedItalic.ttf", false);
#endif

        runningSample_ = new AdvancedNetworking(context_);
        if (runningSample_)
            runningSample_->Start({});
    }

    void Stop() override
    {
        // This step is executed when application is closing. No more frames will be rendered after this method is invoked.
    }
};

// A helper macro which defines main function. Forgetting it will result in linker errors complaining about missing `_main` or `_WinMain@16`.
URHO3D_DEFINE_APPLICATION_MAIN(ShooterTemplateApplication);