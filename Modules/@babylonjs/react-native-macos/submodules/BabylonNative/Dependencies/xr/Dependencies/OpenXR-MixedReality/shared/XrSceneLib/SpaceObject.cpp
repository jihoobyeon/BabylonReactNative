// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"
#include "SpaceObject.h"

namespace {

    class SpaceObject : public engine::Object {
    public:
        SpaceObject(xr::SpaceHandle space, bool hideWhenPoseInvalid)
            : m_space(std::move(space))
            , m_hideWhenPoseInvalid(hideWhenPoseInvalid) {
            assert(m_space.Get() != XR_NULL_HANDLE);
        }

        void Update(engine::Context& context, const engine::FrameTime& frameTime) override {
            XrSpaceLocation location{XR_TYPE_SPACE_LOCATION};
            CHECK_XRCMD(xrLocateSpace(m_space.Get(), context.AppSpace, frameTime.PredictedDisplayTime, &location));
            const bool poseValid = xr::math::Pose::IsPoseValid(location);
            if (poseValid) {
                Pose() = location.pose;
            }
            if (m_hideWhenPoseInvalid) {
                SetVisible(poseValid);
            }
        }

    private:
        xr::SpaceHandle m_space;
        const bool m_hideWhenPoseInvalid;
    };
} // namespace

namespace engine {
    std::shared_ptr<engine::Object> CreateSpaceObject(xr::SpaceHandle space, bool hideWhenPoseInvalid) {
        return std::make_shared<SpaceObject>(std::move(space), hideWhenPoseInvalid);
    }
} // namespace engine
