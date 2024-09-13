#include "pch.h"
#include "EngineView.h"
#include "EngineView.g.cpp"
#include "JSValueXaml.h"

using namespace winrt::Windows::Devices::Input;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::System::Threading;
using namespace winrt::Microsoft::UI::Input;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Input;
using namespace winrt::Microsoft::UI::Xaml::Media;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::ReactNative;

namespace winrt::BabylonReactNative::implementation {
    EngineView::EngineView() {

        _revokerData.SizeChangedRevoker = SizeChanged(winrt::auto_revoke, {this, &EngineView::OnSizeChanged});

        WorkItemHandler workItemHandler([weakThis{ this->get_weak() }](IAsyncAction const& /* action */)
        {
            if (auto trueThis = weakThis.get())
            {
                // TODO: port pointer events to WinUI 3
            };
        });

        // TODO: move to std::thread compared to consuming ThreadPool resources once engine lifecycle bugs are addressed and EngineView's destructor can be successfully invoked.
        _inputLoopWorker = ThreadPool::RunAsync(workItemHandler, WorkItemPriority::High, WorkItemOptions::TimeSliced);

        _revokerData.LoadedEventToken = Loaded(winrt::auto_revoke, [this, ref = get_weak()](auto const&, auto const&) {
                if (auto self = ref.get())
                {
                    self->_revokerData.RenderingRevoker = CompositionTarget::Rendering(
                        winrt::auto_revoke,
                        [weakThis{self->get_weak()}](auto const&, auto const&)
                        {
                            if (auto trueThis = weakThis.get())
                            {
                                trueThis->OnRendering();
                            }
                        });
                }
        });

        _revokerData.UnloadedEventToken = Unloaded(winrt::auto_revoke, [ref = get_weak()](auto const&, auto const&) {
            if (auto self = ref.get()) {
                self->_revokerData.RenderingRevoker.revoke();
            }
        });
    }

    void EngineView::OnSizeChanged(IInspectable const& /*sender*/, SizeChangedEventArgs const& args)
    {
        const auto size = args.NewSize();
        _width = static_cast<size_t>(size.Width);
        _height = static_cast<size_t>(size.Height);

        BabylonNative::UpdateView(static_cast<winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel>(*this), _width, _height);
    }

    void EngineView::OnPointerPressed(IInspectable const& /*sender*/, winrt::Microsoft::UI::Input::PointerEventArgs const& args)
    {
        
    }

    void EngineView::OnPointerMoved(IInspectable const& /*sender*/, winrt::Microsoft::UI::Input::PointerEventArgs const& args)
    {
        
    }

    void EngineView::OnPointerReleased(IInspectable const& /*sender*/, winrt::Microsoft::UI::Input::PointerEventArgs const& args)
    {
        
    }

    void EngineView::OnRendering()
    {
        BabylonNative::RenderView();
    }

    void EngineView::UpdateProperties(IJSValueReader const& reader)
    {
        auto const& propertyMap = JSValueObject::ReadFrom(reader);

        for (auto const& pair : propertyMap)
        {
            auto const& propertyName = pair.first;
            auto const& propertyValue = pair.second;

            if (propertyName == "isTransparent")
            {
                bool isTransparent = propertyValue.AsBoolean();
                BabylonNative::UpdateAlphaPremultiplied(isTransparent);
            } else if (propertyName == "antiAliasing")
            {
                auto value = propertyValue.AsUInt8();
                BabylonNative::UpdateMSAA(value);
            }
        }
    }
}