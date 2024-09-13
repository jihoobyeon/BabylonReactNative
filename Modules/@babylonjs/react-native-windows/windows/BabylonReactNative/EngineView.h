#pragma once
#include "EngineView.g.h"
#include <unordered_set>

namespace winrt::BabylonReactNative::implementation {
    struct EngineView : EngineViewT<EngineView>
    {
    public:
        EngineView();

        void UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const& reader);
    private:
        void OnSizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& args);
        void OnPointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Input::PointerEventArgs const& args);
        void OnPointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Input::PointerEventArgs const& args);
        void OnPointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Input::PointerEventArgs const& args);
        void OnRendering();

        size_t _width{ 1 };
        size_t _height{ 1 };
        winrt::Windows::Foundation::IAsyncAction _inputLoopWorker{};
        std::unordered_set<uint32_t> _pressedMouseButtons{};
        winrt::Microsoft::UI::Input::InputPointerSource _inputSource{ nullptr };
        std::unordered_set<uint32_t> _pressedPointers{};

        struct RevokerData
        {
            winrt::Microsoft::UI::Xaml::FrameworkElement::SizeChanged_revoker SizeChangedRevoker{};
            winrt::Microsoft::UI::Xaml::FrameworkElement::Unloaded_revoker UnloadedEventToken{};
            winrt::Microsoft::UI::Xaml::FrameworkElement::Loaded_revoker LoadedEventToken{};
            winrt::Microsoft::UI::Xaml::Media::CompositionTarget::Rendering_revoker RenderingRevoker{};
        };
        RevokerData _revokerData{};
    };
}

namespace winrt::BabylonReactNative::factory_implementation {

struct EngineView : EngineViewT<EngineView, implementation::EngineView> {};

} // namespace winrt::BabylonReactNative::factory_implementation