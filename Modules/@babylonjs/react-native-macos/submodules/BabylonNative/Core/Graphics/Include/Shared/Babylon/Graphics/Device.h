#pragma once

#include <Babylon/JsRuntime.h>
#include <Babylon/Graphics/Platform.h>
#include <Babylon/Graphics/RendererType.h>

#include <future>
#include <memory>

namespace Babylon::Graphics
{
    struct PlatformInfo
    {
        DeviceT Device;
    };

    class Device;

    class DeviceUpdate
    {
    public:
        DeviceUpdate(const DeviceUpdate&) = default;
        DeviceUpdate& operator=(const DeviceUpdate&) = default;

        DeviceUpdate(DeviceUpdate&&) noexcept = default;
        DeviceUpdate& operator=(DeviceUpdate&&) noexcept = default;

        void Start()
        {
            m_start();
        }

        void RequestFinish(std::function<void()> onFinishCallback)
        {
            m_requestFinish(std::move(onFinishCallback));
        }

        void Finish()
        {
            std::promise<void> promise{};
            auto future = promise.get_future();
            RequestFinish([&promise] { promise.set_value(); });
            future.wait();
        }

    private:
        friend class Device;

        template<typename StartCallableT, typename RequestEndCallableT>
        DeviceUpdate(StartCallableT&& start, RequestEndCallableT&& requestEnd)
            : m_start{std::forward<StartCallableT>(start)}
            , m_requestFinish{std::forward<RequestEndCallableT>(requestEnd)}
        {
        }

        std::function<void()> m_start{};
        std::function<void(std::function<void()>)> m_requestFinish{};
    };

    class Device
    {
    public:
        ~Device();

        // Move semantics
        Device(Device&&) noexcept;
        Device& operator=(Device&&) noexcept;

        // Note: This API contract is subject to change in coming versions.
        // Features and functionalities will be added and
        // method and structure might change.

        static std::unique_ptr<Device> Create(const WindowConfiguration& config);
        static std::unique_ptr<Device> Create(const DeviceConfiguration& config);

        void UpdateWindow(const WindowConfiguration& config);
        void UpdateSize(size_t width, size_t height);
        void UpdateMSAA(uint8_t value);
        void UpdateAlphaPremultiplied(bool enabled);

        void AddToJavaScript(Napi::Env);
        Napi::Value CreateContext(Napi::Env);

        void EnableRendering();
        void DisableRendering();

        DeviceUpdate GetUpdate(const char* updateName);

        void StartRenderingCurrentFrame();
        void FinishRenderingCurrentFrame();

        void SetDiagnosticOutput(std::function<void(const char* output)> outputFunction);

        float GetHardwareScalingLevel();
        void SetHardwareScalingLevel(float level);

        float GetDevicePixelRatio() const;

        PlatformInfo GetPlatformInfo() const;

    private:
        Device();

        void UpdateContext(const DeviceConfiguration& config);

        class Impl;
        std::unique_ptr<Impl> m_impl{};
    };
}
